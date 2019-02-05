#include"RateCurve.h"
#include"YearFraction.h"

RateCurve::RateCurve(const std::map<DateInt, double> & rateMap, YfConvention yfconv, InterpMethod im, ZcType zcTypeEnum, Frequency tenor) : Curve(rateMap, yfconv, im), m_ZcType(zcTypeEnum), m_Tenor(tenor)
{
    if (Size() > 1)
    {
        CurveMapIterator it = Begin();
        m_YcStartDate = it->first;
        if (DfType == m_ZcType)
        {
            for (; it != End(); ++it)
            {
                if (it != Begin())
                {
                    double Zc = it->second;
                    it->second = -std::log(Zc) / Yf::yearFraction(m_YcStartDate, it->first, m_yfconv);
                }
            }
            it = Begin();
            ++it;
            double firstRate = it->second;
            --it;
            it->second = firstRate;
        }
    }
}

RateCurve::RateCurve(YfConvention yfconv, InterpMethod im, ZcType zcTypeEnum, Frequency tenor) : Curve(yfconv, im), m_ZcType(zcTypeEnum), m_Tenor(tenor) {}

double RateCurve::GetValue(DateInt date) const
{
	double res(1.);
    if (date == m_YcStartDate)
    {
        return 1;
    }
    if (Size() <= 1)
    {
        throw ("Invalid RateCurve");
    }
    double value = Curve::GetValue(date);
    res =  std::exp(-value * Yf::yearFraction(m_YcStartDate, date, m_yfconv));
	return res;
}

double RateCurve::GetForwardRate(DateInt fromDate, DateInt resetDate, DateInt toDate) const
{
	double res(0.);
    double RateYf = Yf::yearFraction(resetDate, toDate, m_yfconv);
    res =  (GetForwardDf(fromDate, resetDate) / GetForwardDf(fromDate, toDate) - 1.) / RateYf;
	return res;
}

double RateCurve::GetForwardContinuousRate(DateInt resetDate, DateInt toDate) const
{
    double RateYf = Yf::yearFraction(resetDate, toDate, m_yfconv);
    if (RateYf <= 0)
    {
        throw ("resetDate after to Date");
    }
    return -std::log(GetForwardDf(resetDate, toDate)) / RateYf;
}

void RateCurve::SetYcStartDate(DateInt ycDtartDate)
{
    Clear();
    m_YcStartDate = ycDtartDate;
    Curve::AddPoint(m_YcStartDate, 0.);
}

void RateCurve::AddPoint(DateInt date, double value, ZcType zcTypeEnum)
{
    if (date < m_YcStartDate)
    {
        throw ("Rate Curve date lower than the Yc start date");
    }
    if (DfType == zcTypeEnum)
    {
        value = -std::log(value) / Yf::yearFraction(m_YcStartDate, date, m_yfconv);
    }
    Curve::AddPoint(date, value);
}


