#ifndef _TESTS_H_INCL
#define _TESTS_H_INCL
#include<cmath>
#include<iostream>
#include<vector>
bool isCorrect(double value, double target, double eps = 1.E-14);

bool TestYearFraction();

bool TestCurve();

bool TestRateCurve();

bool TestRateCurveLinInterpolation();

bool TestCurveStepIntegrartion();

bool TestGregDate();

bool TestSchedule();

bool TestFixedRateBondPricing();

bool TestIRSPricing();

bool TestSolver();

bool TestIntegral();

bool TestDiscountCurveCalibration();

bool TestLiborCurveCalibration();

bool TestMultiCurveCalibration();

bool TestTBS();

bool TestNormal();

bool TestBlackFormula();

bool TestCapFloorBF();

bool TestSwaptionBF();

bool TestG2PLUSPLUSZcVariance();

bool TestG2PLUSPLUSZcOptionVariance();

bool TestZeroCouponG2PLUSPLUS();

bool TestZeroCouponOptionG2PLUSPLUS();

bool TestCapFloorOptionG2PLUSPLUS();

#endif