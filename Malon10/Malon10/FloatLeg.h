#ifndef _FLOATLEG_H_INCL
#define _FLOATLEG_H_INCL

#include"Leg.h"
#include<memory>
#include"RateCurve.h"

class FloatLeg : public Leg
{
public:
    FloatLeg(DateInt Maturity, DateInt Issue, double notional, Frequency freq, YfConvention cpnYfConv, bool capitalFlow); //monocurve constructor  //capitalFlow
    FloatLeg(const FloatLeg & other);
    ~FloatLeg();
    virtual void SetCurrentLibor(double currentLibor);
	double GetCurrentLibor() const;
    virtual void SetLiborCurve(RateCurve * rC);
	bool IsMonoCurve() const;
protected:
    bool IsNextResetDate(DateInt calcDate, DateInt & nextResetDate);
    double m_CurrentLibor;
    double m_NextResetDate;
    RateCurve* m_LiborCurve;
	bool m_monocurve;
};

inline FloatLeg::FloatLeg(const FloatLeg & other) : Leg(other), m_CurrentLibor(other.m_CurrentLibor), m_NextResetDate(other.m_NextResetDate), m_monocurve(other.m_monocurve) {}

inline FloatLeg::~FloatLeg() {}

inline void FloatLeg::SetCurrentLibor(double currentLibor)
{
    m_CurrentLibor = currentLibor;
}

inline void FloatLeg::SetLiborCurve(RateCurve * lC)
{
    m_monocurve = false;
	m_LiborCurve = lC;
}

inline bool FloatLeg::IsMonoCurve() const
{
	return m_monocurve;
}

inline double FloatLeg::GetCurrentLibor() const
{
	return m_CurrentLibor;
}


#endif