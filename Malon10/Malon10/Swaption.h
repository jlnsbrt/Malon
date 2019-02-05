#ifndef _SWAPTION_H_INCL
#define _SWAPTION_H_INCL

#include"InterestRateSwap.h"
#include<memory>

class Swaption : public Instrument
{
public:
	Swaption(unsigned int MaturityInMonths, DateInt swapStartDate,DateInt optionDate, double notional, double fixedRate, Frequency fixedFreq, Frequency floatFreq, YfConvention fixedconv, YfConvention floatconv, bool isFlReceived );
	~Swaption();
	virtual double price(const RateCurve & rateCurveObj, DateInt calcDate);//throw an error. Cannot price with just a rate curve
	double price(const RateCurve & rateCurveObj, double volatility, YfConvention volYfConv , DateInt calcDate);
private:
	std::unique_ptr<InterestRateSwap> m_pIRS;
	DateInt m_optionDate;
};


inline Swaption::~Swaption(){}


inline double Swaption::price(const RateCurve & rateCurveObj, DateInt calcDate)
{
	throw("Invalid pricing method for swaption");
}
#endif