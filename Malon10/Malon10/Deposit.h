#ifndef _DEPOSIT_H_INCL
#define _DEPOSIT_H_INCL

#include"Instrument.h"

class Deposit : public Instrument
{
public:
    Deposit(DateInt start, DateInt end, double rate, YfConvention yfC);
    ~Deposit ();
    virtual double price(const RateCurve & rateCurveObj, DateInt calcDate);
protected:
	DateInt m_StartDate;
    double m_Rate;
    YfConvention m_yfC;
};

inline Deposit::Deposit(DateInt start, DateInt end, double rate, YfConvention yfC) : m_StartDate(start), Instrument(end, 0), m_Rate(rate), m_yfC(yfC) {}

inline Deposit ::~Deposit ()
{
}


#endif