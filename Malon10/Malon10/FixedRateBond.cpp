#include"FixedRateBond.h"
#include"Schedule.h"

void FixedRateBond::CalcSchedule()
{
	Leg::CalcSchedule();
	for (Schedule::FlowMapIterator it = m_pInterestSchedule->Begin(); it != m_pInterestSchedule->End(); ++it)
	{
		it->second._value = m_fixedRate * it->second._yf * GetRemainingCapital(it->second._FlowDate);
	}
}

