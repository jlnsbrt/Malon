#include"Leg.h"
#include"Schedule.h"
#include"RateCurve.h"

Leg::Leg(DateInt Maturity, DateInt Issue, double Notional, Frequency freq, YfConvention cpnYfConv, bool capitalFlow) :Instrument(Maturity, Issue), m_freq(freq), m_conv(cpnYfConv), m_capitalFlow(capitalFlow)
{
	m_AmortMap[Maturity] = Notional;
}

Leg::Leg(const Leg& other) : Instrument(other), m_freq(other.m_freq), m_conv(other.m_conv), m_capitalFlow(other.m_capitalFlow), m_AmortMap(other.m_AmortMap)
{
	if (other.m_pCapitalSchedule.get())
	{
		m_pCapitalSchedule.reset(new Schedule(*other.m_pCapitalSchedule));
	}
	if (other.m_pInterestSchedule.get())
	{
		m_pInterestSchedule.reset(new Schedule(*other.m_pInterestSchedule));
	}
}

void Leg::CalcSchedule()
{
	const GregDate MaturityDate(m_Maturity);
	const GregDate  IssueDate(m_Issue);
	const GregDate CalcDate(m_CalcDate);
	m_pInterestSchedule.reset(new Schedule(MaturityDate, IssueDate, CalcDate, m_freq, m_conv));
	m_pCapitalSchedule.reset(new Schedule(m_AmortMap,m_CalcDate));
}

double Leg::price(const RateCurve& rateCurveObj, DateInt calcDate)
{
	m_CalcDate = calcDate;
	CalcSchedule();
	double res = 0;
	for (Schedule::FlowMapIterator it = m_pInterestSchedule->Begin(); it != m_pInterestSchedule->End(); ++it)
	{
		res += it->second._value * rateCurveObj.GetForwardDf(m_CalcDate, it->second._FlowDate);
	}
	if (m_capitalFlow)
	{
		for (Schedule::FlowMapIterator it = m_pCapitalSchedule->Begin(); it != m_pCapitalSchedule->End(); ++it)
		{
			res += it->second._value * rateCurveObj.GetForwardDf(m_CalcDate, it->second._FlowDate);
		}
	}
	return res;
}