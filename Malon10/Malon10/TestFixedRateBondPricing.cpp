#include"Tests.h"
#include"FixedRateBond.h"
#include"RateCurve.h"

bool TestFixedRateBondPricing()
{
	bool iscorrect = true;

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
	RateCurve rC(rateMap, _30360, LinearInterpolation, RateType);
	////////////// Fixed Rate Bond ///////
	DateInt Maturity = 44705;
	DateInt Issue = 42148;
	double couponRate = 0.008;
	Frequency freq = SemiAnnual;
	YfConvention conv = Act365;
	double notional = 100.;
	FixedRateBond frb(Maturity, Issue, notional, couponRate, freq, conv);
	double price = frb.price(rC, CalcDate);
	double yf = 1./ 2.;
	std::map<DateInt, double> flows;
	flows[44705] = couponRate * yf * notional + notional;
	flows[44524] = couponRate * yf * notional;
	flows[44340] = couponRate * yf * notional;
	flows[44159] = couponRate * yf * notional;
	flows[43975] = couponRate * yf * notional;
	flows[43793] = couponRate * yf * notional;
	flows[43609] = couponRate * yf * notional;
	flows[43428] = couponRate * yf * notional;
	flows[43244] = couponRate * yf * notional;
	flows[43063] = couponRate * yf * notional;
	double priceReplic = 0.;
	for (std::map < DateInt, double >::const_iterator it = flows.begin(); it != flows.end(); ++it)
	{
		priceReplic += it->second * rC.GetDf(it->first);
	}
	iscorrect = iscorrect && isCorrect(price, priceReplic,1.0E-10);
	return iscorrect;
}