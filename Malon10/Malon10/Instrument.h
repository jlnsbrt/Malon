#ifndef _INSTRUMENT_H_INCL
#define _INSTRUMENT_H_INCL

#include"Define.h"

class RateCurve;

class Instrument
{
public:
    Instrument() {}
    Instrument(DateInt Maturity,  DateInt Issue);
    ~Instrument();
    Instrument(const Instrument & other);
    virtual double price(const RateCurve & rateCurveObj, DateInt calcDate) = 0;
	
    void SetCalcDate(DateInt calcDate);

    DateInt GetMaturity() const;
    DateInt GetIssueDate() const;

	static unsigned int NbMonths(Frequency tenor);
	static DateInt CalcMaturity(unsigned int MaturityInMonths, DateInt Issue);
protected:
    DateInt m_Maturity;
    DateInt m_Issue;
    DateInt m_CalcDate;
};

inline Instrument::Instrument(DateInt Maturity,  DateInt Issue) : m_Maturity(Maturity), m_Issue(Issue)
{
}

inline Instrument::Instrument(const Instrument & other) : m_Maturity(other.m_Maturity), m_Issue(other.m_Issue), m_CalcDate(other.m_CalcDate)
{}

inline Instrument::~Instrument() {}

inline void Instrument::SetCalcDate(DateInt calcDate)
{
    m_CalcDate = calcDate;
}

inline DateInt Instrument::GetMaturity() const
{
    return m_Maturity;
}

inline DateInt Instrument::GetIssueDate() const
{
    return m_Issue;
}

#endif
