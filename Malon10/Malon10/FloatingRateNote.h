#ifndef _FLOATINGRATENOTE_H_INCL
#define _FLOATINGRATENOTE_H_INCL

#include"FloatLeg.h"
#include<memory>
#include"RateCurve.h"

class FloatingRateNote : public FloatLeg
{
public:
    FloatingRateNote(DateInt Maturity, DateInt Issue, double notional, double spread, Frequency freq, YfConvention cpnYfConv, bool capitalFlow = true); //monocurve constructor
    FloatingRateNote(const FloatingRateNote & other);
    ~FloatingRateNote();
    virtual double price(const RateCurve & rateCurveObj, DateInt calcDate);

	virtual void CalcSchedule();
protected:
    double m_Spread;
};

inline FloatingRateNote::FloatingRateNote(const FloatingRateNote & other) : FloatLeg(other), m_Spread(other.m_Spread) {}

inline FloatingRateNote::~FloatingRateNote() {}



#endif