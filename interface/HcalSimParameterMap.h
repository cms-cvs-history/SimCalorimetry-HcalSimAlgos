#ifndef HcalSimAlgos_HcalSimParameterMap_h
#define HcalSimAlgos_HcalSimParameterMap_h

#include "SimCalorimetry/CaloSimAlgos/interface/CaloVSimParameterMap.h"
#include "SimCalorimetry/CaloSimAlgos/interface/CaloSimParameters.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"

class HcalSimParameterMap : public CaloVSimParameterMap
{
public:
  /// hardcoded default parameters
  HcalSimParameterMap();
  /// configurable parameters
  HcalSimParameterMap(const edm::ParameterSet & p);

  virtual ~HcalSimParameterMap() {}

  virtual const CaloSimParameters & simParameters(const DetId & id) const;

  /// accessors
  CaloSimParameters hbParameters() const {return theHBParameters;}
  CaloSimParameters heParameters() const {return theHEParameters;}
  CaloSimParameters hoParameters() const  {return theHOParameters;}
  CaloSimParameters hfParameters1() const  {return theHFParameters1;}
  CaloSimParameters hfParameters2() const  {return theHFParameters2;}

  /// might move out of here eventually
  double samplingFactor(const HcalDetId & detId) const;

private:
  CaloSimParameters theHBParameters;
  CaloSimParameters theHEParameters;
  CaloSimParameters theHOParameters;
  CaloSimParameters theHFParameters1;
  CaloSimParameters theHFParameters2;

  std::vector<double> theSamplingFactors;
  double theSamplingFactorHF1;
  double theSamplingFactorHF2;
};


#endif

