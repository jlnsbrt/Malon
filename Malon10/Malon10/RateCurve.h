#ifndef _RATECURVE_H_INCL
#define _RATECURVE_H_INCL

#include"Curve.h"


class RateCurve : public Curve
{
public:
    RateCurve(const std::map<DateInt, double> & rateMap, YfConvention yfconv, InterpMethod im, ZcType zcTypeEnum, Frequency tenor = None);
    RateCurve(YfConvention yfconv, InterpMethod im, ZcType zcTypeEnum, Frequency tenor = None);
	RateCurve(const RateCurve& other);
    ~RateCurve();

    virtual double GetValue(DateInt date) const;
    double GetDf(DateInt toDate) const;
    double GetForwardDf(DateInt fromDate, DateInt toDate) const;
    double GetForwardRate(DateInt fromDate, DateInt resetDate, DateInt toDate) const;
    double GetForwardRate(DateInt resetDate, DateInt toDate) const;
    double GetForwardContinuousRate(DateInt resetDate, DateInt toDate) const;
    double GetContinuousRate( DateInt toDate) const;
    DateInt GetYcStartDate() const;
    Frequency GetTenor() const;
    void SetYcStartDate(DateInt ycDtartDate);
    virtual void AddPoint(DateInt date, double value);
    void AddPoint(DateInt date, double value, ZcType zcTypeEnum);
private:
    ZcType m_ZcType;
    DateInt m_YcStartDate;
    Frequency m_Tenor;
};

inline RateCurve::~RateCurve() {}

inline double RateCurve::GetDf(DateInt toDate) const
{
    return GetValue(toDate);
}

inline double RateCurve::GetForwardDf(DateInt fromDate, DateInt toDate) const
{
    return GetDf(toDate) / GetDf(fromDate);
}

inline double RateCurve::GetForwardRate(DateInt resetDate, DateInt toDate) const
{
    return GetForwardRate(m_YcStartDate, resetDate, toDate);
}

inline double RateCurve::GetContinuousRate(DateInt toDate) const
{
    return GetForwardContinuousRate(m_YcStartDate, toDate);
}

inline  DateInt RateCurve::GetYcStartDate() const
{
    return m_YcStartDate;
}

inline void RateCurve::AddPoint(DateInt date, double value)
{
    return AddPoint(date, value, m_ZcType);
}

inline Frequency RateCurve::GetTenor() const
{
    return m_Tenor;
}

inline RateCurve::RateCurve(const RateCurve& other) :Curve(other), m_ZcType(other.m_ZcType), m_YcStartDate(other.m_YcStartDate), m_Tenor(other.m_Tenor){}

#endif