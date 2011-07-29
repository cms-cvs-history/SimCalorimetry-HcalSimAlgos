#include "SimCalorimetry/HcalSimAlgos/interface/HcalSimParameterMap.h"
#include "SimCalorimetry/CaloSimAlgos/interface/CaloShapeIntegrator.h"
#include "SimCalorimetry/HcalSimAlgos/interface/HcalSiPMHitResponse.h"
#include "SimCalorimetry/HcalSimAlgos/interface/HcalSiPMShape.h"
#include "SimCalorimetry/HcalSimAlgos/src/HcalTDC.h"

int main() {
  // assumes 32 bins
  HcalSimParameterMap parameterMap;
  HcalSiPMShape shape;
  CaloShapeIntegrator integratedShape(&shape);
  HcalSiPMHitResponse hitResponse(&parameterMap, &shape, &integratedShape);
  HcalDetId hb1(HcalBarrel, 1, 1, 1);
  CaloSamples signal(hitResponse.makeBlankSignal(hb1));
  // do a short signal and a long one
  int i;
  for(i=100; i < 110; ++i) {
    signal.preciseAtMod(i) = 200.;
  }

  for(i=200; i < 300; ++i) {
    signal.preciseAtMod(i) = 200.;
  }

  HcalTDC tdc;
  HcalUpgradeDataFrame digi(hb1, 0, 10, 2);
  tdc.timing(signal, digi);
  // the first three samples, bins 0-95,
  // should be TDC_Rising=31, TDC_Falling=0
  assert(digi.tdc(0) == 31);
  assert(digi.tdc(1) == 31);
  assert(digi.tdc(2) == 31);
  // next bin should turn on at 4 (bin 100)
  // and off at 14
  assert(digi.tdc(3) == 4 + 14*32);
  assert(digi.tdc(4) == 31);
  assert(digi.tdc(5) == 31);
  // next signal starts at 8 in sample 6 (200=32*6+8))
  // and ends at 12 in sample 9 (300)
  // so first one TDC_Rising = 8, TDC_Falling=31
  assert(digi.tdc(6) == 8 + 31*32);
  // stays on, TDC_RISING=0, falling=31
  assert(digi.tdc(7) == 31*32);
  assert(digi.tdc(8) == 31*32);
  // for sample 9, starts on, falls at sample 12
  assert(digi.tdc(9) == 12*32);

  return 0;
}

