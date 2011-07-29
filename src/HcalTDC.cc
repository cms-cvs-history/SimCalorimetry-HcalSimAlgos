#include "SimCalorimetry/HcalSimAlgos/src/HcalTDC.h"


HcalTDC::HcalTDC() {}

void HcalTDC::timing(const CaloSamples & lf, HcalUpgradeDataFrame & digi)
{
  float TDC_Threshold = 100.;
  bool alreadyOn = false;
  int tdcBins = theTDCParameters.nbins();
  // start with a loop over 10 samples
  for(int ibin = 0; ibin < lf.size(); ++ibin) {
    /*
    If in a given 25ns bunch/time sample, the pulse is above TDC_Thresh  
    already, then TDC_RisingEdge=0
    and then one can still have a TDC_FallingEdge that is non-zero.  If  
    the pulse never falls below threshold having
    started above threshold, then TDC_FallingEdge=31.  If the pulse never  
    went above threshold, then
    TDC_RisingEdge=31 and TDC_FallingEdge=0.
    */
    int TDC_RisingEdge = alreadyOn ? 0 : tdcBins-1;
    int TDC_FallingEdge = alreadyOn ? tdcBins-1 : 0;
    int preciseBegin = ibin * tdcBins;
    int preciseEnd = preciseBegin + tdcBins;
    for(int i = preciseBegin; i < preciseEnd; ++i)
    { 
      if(alreadyOn)
      {
        if(lf.preciseAt(i) < TDC_Threshold)
        {
          alreadyOn = false;
          TDC_FallingEdge = i-preciseBegin;
        }
      }
      else 
      {
        if(lf.preciseAt(i) > TDC_Threshold)
        {
          alreadyOn = true;
          TDC_RisingEdge = i-preciseBegin;
          // the flag for hasn't gone low yet
          TDC_FallingEdge = tdcBins-1;
        }
      }
      int packedTDC = TDC_RisingEdge + tdcBins * TDC_FallingEdge;
      // for whatever reason, the UpgradeDigi setter takes relative samples
      // don't worry if it's negative; presamples will be added back in.
      int relativeSample = ibin - digi.presamples();
      digi.setSample(relativeSample, digi.adc(ibin), packedTDC, true);
    }
  } // loop over bunch crossing bins
}

