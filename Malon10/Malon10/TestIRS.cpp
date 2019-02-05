#include"Tests.h"
#include"InterestRateSwap.h"

bool TestIRSPricing()
{
    bool res = true;
    {
        DateInt CalcDate = 43022;
        ///////////// rateCurve ////////////
        std::map<DateInt, double> rateMap;
        rateMap[43022] = 0.0009;
        rateMap[43053] = 0.0012;
        rateMap[43083] = 0.0015;
        rateMap[43114] = 0.0035;
        rateMap[43204] = 0.0056;
        rateMap[43387] = 0.0054;
        rateMap[43752] = 0.0069;
        rateMap[44118] = 0.0125;
        rateMap[44848] = 0.0156;
        rateMap[46674] = 0.0216;
        RateCurve rC(rateMap, Act36525, LinearInterpolation, RateType);
        ////////////// IRS at issue ///////
        {
            unsigned int Maturity = 60;
            DateInt Issue = 43024;
            double couponRate = 0.012;
            Frequency Fixedfreq = SemiAnnual;
            Frequency Floatfreq = SemiAnnual;
            YfConvention fixedconv = Act365;
            YfConvention floatconv = Act365;
            double notional = 100.;

            InterestRateSwap irs(Maturity, Issue, notional, couponRate, Fixedfreq, Floatfreq, fixedconv, floatconv);
            double npv = irs.price(rC, CalcDate);
            ///////
            GregDate MaturityDate(Issue);
            MaturityDate.AddMonth(Maturity);
            DateInt Mat = MaturityDate.GetSerialNum();
            FixedRateBond frb(Mat, Issue, 1., couponRate, Fixedfreq, fixedconv, false);
            double fixedLegNpv = frb.price(rC, Issue);
            double floatLegNpv = 1. - rC.GetForwardDf(Issue, Mat);
            double repNpv = notional * (floatLegNpv - fixedLegNpv);
            repNpv = repNpv * rC.GetDf(Issue);
            res = res && isCorrect(npv, repNpv);
			///////////// par rate
			double parRate = irs.ParRate(rC,CalcDate);
			double parRateReplic = floatLegNpv / (fixedLegNpv / couponRate);
			res = res && isCorrect(parRate, parRateReplic);
        }
        ///////////  IRS value after the issue  /////////////
        {
            unsigned int Maturity = 12;
            DateInt Issue = 42964;
            double couponRate = 0.008;
            Frequency Fixedfreq = SemiAnnual;
            Frequency Floatfreq = SemiAnnual;
            YfConvention fixedconv = Act365;
            YfConvention floatconv = Act365;
            double notional = 100.;
            double currentLibor = 0.005;



            InterestRateSwap irs(Maturity, Issue, notional, couponRate, Fixedfreq, Floatfreq, fixedconv, floatconv);
            irs.SetCurrentLibor(currentLibor);
            double npv = irs.price(rC, CalcDate);
            ///////
            GregDate MaturityDate(Issue);
            MaturityDate.AddMonth(Maturity);
            GregDate NextCouponDate(Issue);
            NextCouponDate.AddMonth(6);
            DateInt NextCoupon = NextCouponDate.GetSerialNum();
            DateInt Mat = MaturityDate.GetSerialNum();
            FixedRateBond frb(Mat, Issue, 1., couponRate, Fixedfreq, fixedconv, false);
            double fixedLegNpv = frb.price(rC, CalcDate);
            double floatLegNpv = currentLibor / 2. * rC.GetForwardDf(CalcDate, NextCoupon) + rC.GetForwardDf(CalcDate, NextCoupon) - rC.GetForwardDf(CalcDate, Mat);
            double repNpv = notional * (floatLegNpv - fixedLegNpv);
            res = res && isCorrect(npv, repNpv);
        }
        ///IRS Multicurve
        {


            unsigned int Maturity = 60;
            DateInt Issue = 43024;
            double couponRate = 0.03;
            Frequency Fixedfreq = SemiAnnual;
            Frequency Floatfreq = SemiAnnual;
            YfConvention fixedconv = Act365;
            YfConvention floatconv = Act365;
            double notional = 100.;

            ///////////// LiborCurve ////////////
            std::map<DateInt, double> LiborMap;
            LiborMap[43022] = 0.0052;
            LiborMap[43053] = 0.0063;
            LiborMap[43083] = 0.0078;
            LiborMap[43114] = 0.0135;
            LiborMap[43204] = 0.0142;
            LiborMap[43387] = 0.0154;
            LiborMap[43752] = 0.0165;
            LiborMap[44118] = 0.0252;
            LiborMap[44848] = 0.0323;
            LiborMap[46674] = 0.0402;
            RateCurve lC(LiborMap, Act36525, LinearInterpolation, RateType);

            InterestRateSwap irs(Maturity, Issue, notional, couponRate, Fixedfreq, Floatfreq, fixedconv, floatconv);
            irs.SetLiborCurve(&lC);
            double npv = irs.price(rC, CalcDate);
            ///////
            GregDate MaturityDate(Issue);
            MaturityDate.AddMonth(Maturity);
            DateInt Mat = MaturityDate.GetSerialNum();
            FixedRateBond frb(Mat, Issue, 1., couponRate, Fixedfreq, fixedconv, false);
            double fixedLegNpv = frb.price(rC, Issue) * rC.GetDf(Issue);


            double floatLegNpv = 0.;
            GregDate cpnDate(MaturityDate);
            DateInt cpnDateInt = cpnDate.GetSerialNum();
            GregDate resetDate(cpnDate);
            resetDate.AddMonth(-6);
            DateInt resetDateInt = resetDate.GetSerialNum();
            while (true)
            {
                GregDate resetDate(cpnDate);
                resetDate.AddMonth(-6);
                resetDateInt = resetDate.GetSerialNum();
                if (resetDateInt < CalcDate)
                {
                    break;
                }
                double forward = lC.GetForwardRate(resetDateInt, cpnDateInt);
                floatLegNpv += forward / 2. * rC.GetDf(cpnDateInt);
                cpnDate.AddMonth(-6);
                cpnDateInt = resetDateInt;
            }
            double repNpv = notional * (floatLegNpv - fixedLegNpv);
            repNpv = repNpv;
            res = res && isCorrect(npv, repNpv);
        }
    }

    return res;
}

