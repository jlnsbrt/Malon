#ifndef _CAPFLOOR_H_INCL
#define _CAPFLOOR_H_INCL

#include"FloatLeg.h"

class CapFloor : public FloatLeg
{
public:
	enum PayOff
	{
		_Cap = 1,
		_Floor = 2
	};
	 CapFloor(unsigned int MaturityInMonths,  DateInt Issue, double Notional, Frequency freq, YfConvention cpnYfConv, double strikeRate, PayOff po);
	 ~CapFloor();
	 CapFloor(const CapFloor& other);
	 virtual double price(const RateCurve & rateCurveObj, DateInt calcDate);//throw an error. Cannot price with just a rate curve
	 double price(const RateCurve & rateCurveObj, double volatility, YfConvention volYfConv , DateInt calcDate);
	 double GetStrikeRate() const;
	 PayOff GetPayOff() const;
private:
	double m_Rate;
	PayOff m_po;
};


//////////////// inline functions ///////////////////

inline CapFloor::CapFloor(unsigned int MaturityInMonths,  DateInt Issue, double Notional, Frequency freq, YfConvention cpnYfConv, double strikeRate, PayOff po)
	:FloatLeg(CalcMaturity(MaturityInMonths,Issue),Issue,Notional,freq,cpnYfConv,false),m_Rate(strikeRate), m_po(po){}
inline CapFloor::~CapFloor(){}
inline CapFloor::CapFloor(const CapFloor& other):FloatLeg(other),m_Rate(other.m_Rate), m_po(other.m_po){}

inline double CapFloor::price(const RateCurve & rateCurveObj, DateInt calcDate)
{
	throw("Invalid pricing method for cap floor");
}

inline double CapFloor::GetStrikeRate() const
{
	return m_Rate;
}

inline CapFloor::PayOff CapFloor::GetPayOff() const
{
	return m_po;
}

#endif