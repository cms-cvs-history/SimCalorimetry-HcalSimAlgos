#ifndef HcalTriggerPrimitiveAlgo_h
#define HcalTriggerPrimitiveAlgo_h

#include "DataFormats/HcalDetId/interface/HcalTrigTowerDetId.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "CalibFormats/HcalObjects/interface/HcalNominalCoder.h"
#include "Geometry/HcalTowerAlgo/interface/HcalTrigTowerGeometry.h"
#include <map>
#include <vector>
class CaloGeometry;
class CaloSamples;

class HcalTriggerPrimitiveAlgo {
public:
  HcalTriggerPrimitiveAlgo();
  ~HcalTriggerPrimitiveAlgo();

  void run(const HBHEDigiCollection & hbheDigis,
           const HFDigiCollection & hfDigis,
           HcalTrigPrimRecHitCollection & result);

private:

  /// adds the signal to the map
  void addSignal(const HBHEDataFrame & frame);
  void addSignal(const HFDataFrame & frame);
  void addSignal(const CaloSamples & samples);

  /// changes the signal to be in ET instead of E
  void transverseComponent(CaloSamples & samples, const  HcalTrigTowerDetId & id) const;

  /// adds the actual RecHits
  void analyze(const CaloSamples & samples, HcalTrigPrimRecHitCollection & result) const;

  std::vector<HcalTrigTowerDetId> towerIds(const HcalDetId & id) const;

  HcalNominalCoder theCoder;
  HcalTrigTowerGeometry theTrigTowerGeometry;
  // counts from 1
  double theSinThetaTable[33];

  typedef std::map<HcalTrigTowerDetId, CaloSamples> SumMap;
  SumMap theSumMap;  

  double theThreshold;
  double theHBHECalibrationConstant;
  double theHFCalibrationConstant;
};

#endif
