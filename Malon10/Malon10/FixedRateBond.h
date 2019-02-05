#ifndef _FIXEDRATEBOND_H_INCL
#define _FIXEDRATEBOND_H_INCL


#include"Leg.h"

class FixedRateBond: public Leg
{
public:
	FixedRateBond(DateInt Maturity,  DateInt Issue, double notional, double couponRate,  Frequency freq,YfConvention cpnYfConv, bool capitalFlow = true);
	~FixedRateBond();
	FixedRateBond(const FixedRateBond& other);
	
	virtual void SetCurrentLibor(double);
	virtual void SetLiborCurve(RateCurve* rC); 
	void SetFixedRate(double fixedRate);

	double GetFixedRate() const;

	virtual void CalcSchedule();
private:
	double m_fixedRate;

};

inline FixedRateBond::FixedRateBond(DateInt Maturity, DateInt Issue, double notional, double couponRate, Frequency freq, YfConvention cpnYfConv, bool capitalFlow) :Leg(Maturity, Issue,notional, freq, cpnYfConv, capitalFlow), m_fixedRate(couponRate){}
inline FixedRateBond::~FixedRateBond(){}
inline FixedRateBond::FixedRateBond(const FixedRateBond& other) : Leg(other), m_fixedRate(other.m_fixedRate){}

inline void FixedRateBond::SetLiborCurve(RateCurve* rC) {}
inline void FixedRateBond::SetCurrentLibor(double) {}

inline double FixedRateBond::GetFixedRate() const
{
	return m_fixedRate;
}

inline void FixedRateBond::SetFixedRate(double fixedRate)
{
	m_fixedRate = fixedRate;
}


#endif