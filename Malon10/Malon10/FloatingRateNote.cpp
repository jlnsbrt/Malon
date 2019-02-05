#include"FloatingRateNote.h"


FloatingRateNote::FloatingRateNote(DateInt Maturity, DateInt Issue, double notional, double spread, Frequency freq, YfConvention cpnYfConv, bool capitalFlow)
    : FloatLeg(Maturity, Issue, notional, freq, cpnYfConv, capitalFlow), m_Spread(spread)  {}


void FloatingRateNote::CalcSchedule()
{
    Leg::CalcSchedule();
    if (m_monocurve)
    {
        for (Schedule::FlowMapIterator it = m_pInterestSchedule->Begin(); it != m_pInterestSchedule->End(); ++it)
        {
            if (it->second._ResetDate < m_CalcDate)
            {
                it->second._value = (m_CurrentLibor + m_Spread) * it->second._yf * GetRemainingCapital(it->second._FlowDate);
            }
            else if ( m_Spread > 0)
            {
                it->second._value =   m_Spread * it->second._yf * GetRemainingCapital(it->second._FlowDate);
            }
			else
			{
				break;
			}
        }
    }
    else
    {
        for (Schedule::FlowMapIterator it = m_pInterestSchedule->Begin(); it != m_pInterestSchedule->End(); ++it)
        {
            if (it->second._ResetDate < m_CalcDate)
            {
                it->second._value = (m_CurrentLibor + m_Spread) * it->second._yf * GetRemainingCapital(it->second._FlowDate);
            }
            else
            {
                double forward = m_LiborCurve->GetForwardRate(it->second._ResetDate, it->second._FlowDate);
                it->second._value = (forward + m_Spread) * it->second._yf * GetRemainingCapital(it->second._FlowDate);
            }
        }
    }
}

double FloatingRateNote::price(const RateCurve & rateCurveObj, DateInt calcDate)
{
    if (!m_monocurve)
    {
        return Leg::price(rateCurveObj, calcDate);
    }
    m_CalcDate = calcDate;
    CalcSchedule(); 
    double res = 0;
    for (Schedule::FlowMapIterator it = m_pInterestSchedule->Begin(); it != m_pInterestSchedule->End(); ++it)
    {
        res += it->second._value * rateCurveObj.GetForwardDf(m_CalcDate, it->second._FlowDate);
    }
    DateInt nextResetDate(0);
    if (IsNextResetDate(m_CalcDate, nextResetDate))
    {
        res += GetRemainingCapital(nextResetDate) * rateCurveObj.GetForwardDf(m_CalcDate, nextResetDate);
        if (!m_capitalFlow)
        {
            res -= GetRemainingCapital(m_Maturity) * rateCurveObj.GetForwardDf(m_CalcDate, m_Maturity);
        }
    }
    else
    {
        if (m_capitalFlow)
        {
            res += GetRemainingCapital(m_Maturity) * rateCurveObj.GetForwardDf(m_CalcDate, m_Maturity);
        }
    }
    return res;
}

