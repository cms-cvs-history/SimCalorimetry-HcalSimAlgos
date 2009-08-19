#ifndef HcalSimAlgos_HcalBaseSignalGenerator_h
#define HcalSimAlgos_HcalBaseSignalGenerator_h

#include "SimCalorimetry/CaloSimAlgos/interface/CaloVNoiseSignalGenerator.h"
#include "SimCalorimetry/HcalSimAlgos/interface/HcalSimParameterMap.h"

class HcalBaseSignalGenerator : public CaloVNoiseSignalGenerator
{
public:
  HcalBaseSignalGenerator()
  : theParameterMap(0) {}

  virtual ~HcalBaseSignalGenerator() {}

  void setParameterMap(HcalSimParameterMap * map) {theParameterMap = map;}

protected:

  void fC2pe(CaloSamples & samples) const
  {
    assert(theParameterMap != 0);
    float factor = 1./theParameterMap->simParameters(samples.id()).photoelectronsToAnalog(samples.id());
    std::cout << "fC2PEPU " << factor << std::endl;
    samples *= factor;
  }

  HcalSimParameterMap * theParameterMap;
};

#endif



