#ifndef HcalSimAlgos_HcalTDC_h
#define HcalSimAlgos_HcalTDC_h

#include "CalibFormats/CaloObjects/interface/CaloSamples.h"
#include "DataFormats/HcalDigi/interface/HcalUpgradeDataFrame.h"
#include "SimCalorimetry/HcalSimAlgos/src/HcalTDCParameters.h"

class HcalTDC 
{
public:
  HcalTDC();

  void timing(const CaloSamples & lf, HcalUpgradeDataFrame & digi);

private:
  HcalTDCParameters theTDCParameters;
};

#endif

