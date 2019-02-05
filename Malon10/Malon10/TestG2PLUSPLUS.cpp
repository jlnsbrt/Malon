#include"Tests.h"
#include"IRModelG2PLUSPLUS.h"
#include"YearFraction.h"
#include"Integral.h"
#include"FinanceFormula.h"
#include"CapFloor.h"
#include<algorithm>
#include"InterestRateSwap.h"

bool TestG2PLUSPLUSZcVariance()
{
	bool isC(true);
	{
		double mr1(0.1);
		double mr2(0.2);
		double vol1(0.01);
		double vol2(0.03);
		double rho(0.5);
		RateCurve rc(_30360, LinearInterpolation, DfType);
		YfConvention yfC(_30360);
		IRModelG2PLUSPLUS g2pp(mr1, vol1, mr2, vol2, rho, rc, yfC);
		DateInt calcDate(40000);
		DateInt Maturity(41000);
		double yfCalc = 0.;
		double yfMat = Yf::yearFraction(calcDate, Maturity, yfC);
		double variance = g2pp.ZeroCouponVariance(calcDate, Maturity);

		double varApprox = (vol1*vol1 + vol2*vol2 + 2 * rho*vol1*vol2)*yfMat*yfMat*yfMat / 3.;

		double yearFraction = Yf::yearFraction(calcDate, Maturity, yfC);
		class VarianceIntegration : public Integral
		{
		public:
			VarianceIntegration() :Integral(Integral::Simpson, 100){}
			IRModelG2PLUSPLUS* m_pG2PP;
			double m_yf;
			virtual double f(double u) const
			{
				double res = m_pG2PP->ZeroCouponVol(m_yf - u);
				return res*res;
			}
		};

		VarianceIntegration vi;
		vi.m_pG2PP = &g2pp;
		vi.m_yf = yearFraction;
		double varianceNum = vi.Calculate(yfCalc, yfMat);
		isC = isC && isCorrect(variance, varianceNum, 1.0E-6);
	}
	{
		double mr1(0.000001);
		double mr2(0.000002);
		double vol1(0.01);
		double vol2(0.03);
		double rho(0.5);
		RateCurve rc(_30360, LinearInterpolation, DfType);
		YfConvention yfC(_30360);
		IRModelG2PLUSPLUS g2pp(mr1, vol1, mr2, vol2, rho, rc, yfC);
		DateInt calcDate(40000);
		DateInt Maturity(41000);
		double yfCalc = 0.;
		double yfMat = Yf::yearFraction(calcDate, Maturity, yfC);
		double variance = g2pp.ZeroCouponVariance(calcDate, Maturity);

		double varApprox = (vol1*vol1 + vol2*vol2 + 2 * rho*vol1*vol2)*yfMat*yfMat*yfMat / 3.;

		double yearFraction = Yf::yearFraction(calcDate, Maturity, yfC);
		class VarianceIntegration : public Integral
		{
		public:
			VarianceIntegration() :Integral(Integral::Simpson, 100){}
			IRModelG2PLUSPLUS* m_pG2PP;
			double m_yf;
			virtual double f(double u) const
			{
				double res = m_pG2PP->ZeroCouponVol(m_yf - u);
				return res*res;
			}
		};

		VarianceIntegration vi;
		vi.m_pG2PP = &g2pp;
		vi.m_yf = yearFraction;
		double varianceNum = vi.Calculate(yfCalc, yfMat);
		isC = isC && isCorrect(variance, varianceNum, 1.0E-4);
	}
	{
		double mr1(0.1);
		double mr2(0.0000008);
		double vol1(0.01);
		double vol2(0.03);
		double rho(0.5);
		RateCurve rc(_30360, LinearInterpolation, DfType);
		YfConvention yfC(_30360);
		IRModelG2PLUSPLUS g2pp(mr1, vol1, mr2, vol2, rho, rc, yfC);
		DateInt calcDate(40000);
		DateInt Maturity(41000);
		double yfCalc = 0.;
		double yfMat = Yf::yearFraction(calcDate, Maturity, yfC);
		double variance = g2pp.ZeroCouponVariance(calcDate, Maturity);

		double varApprox = (vol1*vol1 + vol2*vol2 + 2 * rho*vol1*vol2)*yfMat*yfMat*yfMat / 3.;

		double yearFraction = Yf::yearFraction(calcDate, Maturity, yfC);
		class VarianceIntegration : public Integral
		{
		public:
			VarianceIntegration() :Integral(Integral::Simpson, 100){}
			IRModelG2PLUSPLUS* m_pG2PP;
			double m_yf;
			virtual double f(double u) const
			{
				double res = m_pG2PP->ZeroCouponVol(m_yf - u);
				return res*res;
			}
		};

		VarianceIntegration vi;
		vi.m_pG2PP = &g2pp;
		vi.m_yf = yearFraction;
		double varianceNum = vi.Calculate(yfCalc, yfMat);
		isC = isC && isCorrect(variance, varianceNum, 1.0E-4);
	}

	return isC;
}

bool TestG2PLUSPLUSZcOptionVariance()
{
	bool isC(true);
	{
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
		RateCurve rC(rateMap, ActAct, LinearInterpolation, RateType);
		double mr1(0.1);
		double mr2(0.2);
		double vol1(0.01);
		double vol2(0.);
		double rho(0.5);
		YfConvention yfC(_30360);
		IRModelG2PLUSPLUS g2pp(mr1, vol1, mr2, vol2, rho, rC, yfC);
		DateInt calcDate(43022);
		DateInt OptionMaturity(43600);
		DateInt ZcMaturity(44000);
		double yfCalc = 0.;
		double yfOptionMat = Yf::yearFraction(calcDate, OptionMaturity, yfC);
		double yfOptionMatZcMat = Yf::yearFraction(OptionMaturity, ZcMaturity, yfC);

		double variance = g2pp.ZeroCouponVariance(calcDate, OptionMaturity, ZcMaturity);

		double varReplic = vol1 * vol1 * (1. - std::exp(-mr1 * yfOptionMatZcMat)) * (1. - std::exp(-mr1 * yfOptionMatZcMat)) * (1. - std::exp(-2. * mr1 * yfOptionMat)) / (2. * mr1 * mr1 * mr1);

		isC = isC && isCorrect(variance, varReplic, 1.0E-10);
	}
	return isC;
}

double B(double yf, double mr)
{
	return (1. - std::exp(-mr * yf) ) / mr;
}

bool TestZeroCouponG2PLUSPLUS()
{
	bool isC(true);
	{
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
		RateCurve rC(rateMap, ActAct, LinearInterpolation, RateType);
		double mr1(0.1);
		double mr2(0.2);
		double vol1(0.01);
		double vol2(0.0);
		double rho(0.5);
		YfConvention yfC(_30360);
		IRModelG2PLUSPLUS g2pp(mr1, vol1, mr2, vol2, rho, rC, yfC);
		DateInt initialDate(43022);
		DateInt calcDate(43600);
		DateInt ZcMaturity(44000);
		double x1(0.023), x2(-0.001);
		std::vector<double> x;
		x.push_back(x1);
		x.push_back(x2);
		double zcValue = g2pp.zeroCouponBondPrice(calcDate, ZcMaturity, x);

		double yfCalcToZcMat = Yf::yearFraction(calcDate, ZcMaturity, yfC);
		double zcReplic = std::exp(- B(yfCalcToZcMat, mr1) * x1  -B(yfCalcToZcMat, mr2) * x2);
		double A = g2pp.ZeroCouponVariance(calcDate, ZcMaturity) - g2pp.ZeroCouponVariance(initialDate, ZcMaturity) + g2pp.ZeroCouponVariance(initialDate, calcDate);
		A = std::exp(A / 2.);
		A = A * rC.GetForwardDf(calcDate, ZcMaturity);
		zcReplic *= A;
		isC = isC && isCorrect(zcValue, zcReplic, 1.0E-10);
	}
	return isC;
}

bool TestZeroCouponOptionG2PLUSPLUS()
{
	bool isC(true);
	{
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
		RateCurve rC(rateMap, ActAct, LinearInterpolation, RateType);
		double mr1(0.1);
		double mr2(0.2);
		double vol1(0.01);
		double vol2(0.);
		double rho(0.5);
		YfConvention yfC(_30360);
		IRModelG2PLUSPLUS g2pp(mr1, vol1, mr2, vol2, rho, rC, yfC);
		DateInt calcDate(43022);
		DateInt OptionMaturity(43600);
		DateInt ZcMaturity(44000);
		double x1(0.023), x2(-0.001);
		std::vector<double> x;
		x.push_back(x1);
		x.push_back(x2);
		double yfCalc = 0.;
		double yfOptionMat = Yf::yearFraction(calcDate, OptionMaturity, yfC);
		double yfOptionMatZcMat = Yf::yearFraction(OptionMaturity, ZcMaturity, yfC);
		double strike = 1.;
		//call
		double zcCallValue = g2pp.zeroCouponBondOptionPrice(calcDate,OptionMaturity, ZcMaturity, 1., true,x);

		DateInt YcStartDate = g2pp.GetYcStartDate();
		double forwardZc = rC.GetForwardDf(OptionMaturity, ZcMaturity);
		double Zc = rC.GetDf(OptionMaturity);
		double variance = g2pp.ZeroCouponVariance(YcStartDate, OptionMaturity, ZcMaturity);
		double zcCallReplic = BlackFormula::optionPrice(forwardZc, strike, variance, Zc, true);
		isC = isC && isCorrect(zcCallValue, zcCallReplic, 1.0E-10);
		//put
		double zcPutValue = g2pp.zeroCouponBondOptionPrice(calcDate,OptionMaturity, ZcMaturity, 1., false, x);
		double zcPutReplic = BlackFormula::optionPrice(forwardZc, strike, variance, Zc, false);
		isC = isC && isCorrect(zcPutValue, zcPutReplic, 1.0E-10);
		//Parity
		double forwardContract = Zc * (forwardZc - strike);
		double callPutParity = zcCallValue - zcPutValue;
		isC = isC && isCorrect(forwardContract, callPutParity, 1.0E-10);
	}
	return isC;
}


bool TestCapFloorOptionG2PLUSPLUS()
{
	bool isC(true);
	{
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
		RateCurve rC(rateMap, ActAct, LinearInterpolation, RateType);
		double currentLibor(0.001);
		double mr1(0.1);
		double mr2(0.2);
		double vol1(0.01);
		double vol2(0.);
		double rho(0.5);
		YfConvention yfC(_30360);
		IRModelG2PLUSPLUS g2pp(mr1, vol1, mr2, vol2, rho, rC, yfC);
		DateInt calcDate(43022);
		DateInt OptionMaturity(43600);
		DateInt ZcMaturity(44000);

		double x1(0.023), x2(-0.001);
		std::vector<double> x;
		x.push_back(x1);
		x.push_back(x2);
		double yfCalc = 0.;
		double yfOptionMat = Yf::yearFraction(calcDate, OptionMaturity, yfC);
		double yfOptionMatZcMat = Yf::yearFraction(OptionMaturity, ZcMaturity, yfC);
		DateInt Issue = 42800;
		double strike = 0.01;
		unsigned int MaturityInMonths = 60;
		double Notional(10000.);
		Frequency freq = SemiAnnual;
		//cap

		{
			CapFloor cap1(MaturityInMonths, Issue, Notional, freq, yfC, strike, CapFloor::_Cap);
			cap1.SetCurrentLibor(currentLibor);
			double capValue = g2pp.CapFloorPrice(calcDate, cap1, x);
			//replication
			unsigned int period(6);
			unsigned int flowsSize = MaturityInMonths / period;
			GregDate ResetGregDate(Issue);
			GregDate CouponGregDate(Issue);
			CouponGregDate.AddMonth(period);
			double yf = period / 12.;
			double res = 0.;
			double strikeZc = 1. / (1. + strike * yf);
			for (unsigned int i = 0; i < flowsSize; ++i)
			{
				if (CouponGregDate.GetSerialNum() > calcDate)
				{
					if (ResetGregDate.GetSerialNum() < calcDate)
					{
						res += Notional* yf * std::max(currentLibor - strike, 0.) *  rC.GetDf(CouponGregDate.GetSerialNum());
					}
					else
					{

						res += Notional  * (1. / strikeZc) *
							g2pp.zeroCouponBondOptionPrice(calcDate, ResetGregDate.GetSerialNumConst(), CouponGregDate.GetSerialNum(), strikeZc, false, x);
					}
				}
				ResetGregDate.AddMonth(period);
				CouponGregDate.AddMonth(period);
			}
			isC = isC && isCorrect(capValue, res, 1.0E-10);
		}
		{
			//put
			CapFloor put1(MaturityInMonths, Issue, Notional, freq, yfC, strike, CapFloor::_Floor);
			put1.SetCurrentLibor(currentLibor);
			double floorValue = g2pp.CapFloorPrice(calcDate, put1, x);
			//replication
			unsigned int period(6);
			unsigned int flowsSize = MaturityInMonths / period;
			GregDate ResetGregDate(Issue);
			GregDate CouponGregDate(Issue);
			CouponGregDate.AddMonth(period);
			double yf = period / 12.;
			double res = 0.;
			double strikeZc = 1. / (1. + strike * yf);
			for (unsigned int i = 0; i < flowsSize; ++i)
			{
				if (CouponGregDate.GetSerialNum() > calcDate)
				{
					if (ResetGregDate.GetSerialNum() < calcDate)
					{
						res += Notional* yf * std::max(strike - currentLibor, 0.) * rC.GetDf(CouponGregDate.GetSerialNum());
					}
					else
					{

						res += Notional  * (1. / strikeZc) *
							g2pp.zeroCouponBondOptionPrice(calcDate, ResetGregDate.GetSerialNumConst(), CouponGregDate.GetSerialNum(), strikeZc, true, x);
					}
				}
				ResetGregDate.AddMonth(period);
				CouponGregDate.AddMonth(period);
			}
			isC = isC && isCorrect(floorValue, res, 1.0E-10);
		}
		{			
				CapFloor cap1(MaturityInMonths, Issue, Notional, freq, yfC, strike, CapFloor::_Cap);
				cap1.SetCurrentLibor(currentLibor);
				CapFloor put1(MaturityInMonths, Issue, Notional, freq, yfC, strike, CapFloor::_Floor);
				put1.SetCurrentLibor(currentLibor);
				double capminusfloor = g2pp.CapFloorPrice(calcDate, cap1, x) - g2pp.CapFloorPrice(calcDate, put1, x);
				InterestRateSwap irs(MaturityInMonths, Issue, Notional, strike, freq, freq, yfC, yfC, true);
				irs.SetCurrentLibor(currentLibor);
				double irsValue = irs.price(rC, calcDate);
				isC = isC && isCorrect(capminusfloor, irsValue, 1.0E-10);
		}

	}
	return isC;
}
