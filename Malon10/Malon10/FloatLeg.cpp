#include"FloatLeg.h"


FloatLeg::FloatLeg(DateInt Maturity, DateInt Issue, double notional,  Frequency freq, YfConvention cpnYfConv, bool capitalFlow)
    : Leg(Maturity, Issue, notional, freq, cpnYfConv, capitalFlow),m_monocurve(true) , m_CurrentLibor(0.){}


bool FloatLeg::IsNextResetDate(DateInt calcDate, DateInt & nextResetDate)
{
    if (m_CalcDate != calcDate)
    {
        m_CalcDate = calcDate;
        CalcSchedule();
    }
    Schedule::FlowMapIterator it = m_pInterestSchedule->Begin();
    while (it != m_pInterestSchedule->End())
    {
        if (it->second._ResetDate > m_CalcDate)
        {
            nextResetDate = it->second._ResetDate;
            return true;
        }
        ++it;
    }
    return false;
}