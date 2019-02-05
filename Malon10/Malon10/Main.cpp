#include<iostream>
#include<string>
#include"Define.h"
#include"Tests.h"

int main()
{
    std::cout << "Hello World!" << std::endl;
	try		
    {
        if (!TestYearFraction())
        {
            std::cout << "TestYearFraction fails" << std::endl;
        }
        if (!TestCurve())
        {
            std::cout << "TestCurve fails" << std::endl;
        }
        if (!TestRateCurveLinInterpolation())
        {
            std::cout << "TestRateCurveLinInterpolation fails" << std::endl;
        }	
        if (!TestRateCurve())
        {
            std::cout << "TestRateCurve fails" << std::endl;
        }
        if (!TestCurveStepIntegrartion())
        {
            std::cout << "TestCurveStepIntegrartion fails" << std::endl;
        }	
        if (!TestGregDate())
        {
            std::cout << "TestGregDate fails" << std::endl;
        }
        if (!TestSchedule())
        {
            std::cout << "TestScheduleDate fails" << std::endl;
        }
        if (!TestFixedRateBondPricing())
        {
            std::cout << "TestFixedRateBondPricing fails" << std::endl;
        }
        if (!TestIRSPricing())
        {
            std::cout << "TestIRSPricing fails" << std::endl;
        }
        if (!TestSolver())
        {
            std::cout << "TestSolver fails" << std::endl;
        }
		if (!TestIntegral())
		{
			std::cout << "TestIntegral fails" << std::endl;
		}
        if (!TestDiscountCurveCalibration())
        {
            std::cout << "TestRateCurveCalibration fails" << std::endl;
        }
		if (!TestLiborCurveCalibration())
		{
			std::cout << "TestLiborCurveCalibration fails" << std::endl;
		}
		if (!TestMultiCurveCalibration())
		{
			std::cout << "TestRateCurveCalibration fails" << std::endl;
		}
		if (!TestTBS())
		{
			std::cout << "TestRateCurveCalibration fails" << std::endl;
		}
		if (!TestNormal())
		{
			std::cout << "TestNormal fails" << std::endl;
		}
		if (!TestBlackFormula())
		{
			std::cout << "TestBlackFormula fails" << std::endl;
		}
		if (!TestCapFloorBF())
		{
			std::cout << "TestCapFloorBF fails" << std::endl;
		}
		if (!TestSwaptionBF())
		{
			std::cout << "TestSwaptionBF fails" << std::endl;
		}
		if (!TestG2PLUSPLUSZcVariance())
		{
			std::cout << "TestG2PLUSPLUS fails" << std::endl;
		}	
		if (!TestG2PLUSPLUSZcOptionVariance())
		{
			std::cout << "TestG2PLUSPLUSZcOptionVariance fails" << std::endl;
		}
		if (!TestZeroCouponG2PLUSPLUS())
		{
			std::cout << "TestZeroCouponG2PLUSPLUS fails" << std::endl;
		}
		if (!TestZeroCouponOptionG2PLUSPLUS())
		{
			std::cout << "TestZeroCouponOptionG2PLUSPLUS fails" << std::endl;
		}
		if (!TestCapFloorOptionG2PLUSPLUS())
		{
			std::cout << "TestCapFloorOptionG2PLUSPLUS fails" << std::endl;
		}
    }
    catch (const std::string & c )
    {
        std::cout << "An exception occurred. Exception Nr. " << c << '\n';
    }
    return 0;
}