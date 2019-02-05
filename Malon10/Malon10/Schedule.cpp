#include"Schedule.h"
#include"YearFraction.h"

Schedule::Schedule(const Schedule& other) : m_FlowMap(other.m_FlowMap), m_yfconv(other.m_yfconv), m_CalcDate(other.m_CalcDate), _isInterest(other._isInterest)
{}

Schedule::Schedule(const GregDate& MaturityDate, const GregDate&  IssueDate, const GregDate& CalcDate, Frequency freq, YfConvention yfconv) :m_yfconv(yfconv)
{
	_isInterest = true;
	int period(12);
	switch (freq)
	{
	case Annual:
		period = 12;
		break;
	case SemiAnnual:
		period = 6;
		break;
	case Quaterly:
		period = 3;
		break;
	case Monthly:
		period = 1;
		break;
	default:
		break;
	}
	DateInt CalcDateNum = CalcDate.GetSerialNumConst();
	GregDate FlowDate(MaturityDate);
	DateInt FlowDateNum = FlowDate.GetSerialNum();
	DateInt IssueDateNum = IssueDate.GetSerialNumConst();
	while (FlowDateNum > IssueDateNum && FlowDateNum > CalcDateNum)
	{
		Flow f;
		f._FlowDate = FlowDateNum;
		FlowDate.AddMonth(-period);
		FlowDateNum = FlowDate.GetSerialNum();
		if (FlowDateNum < IssueDateNum)
		{
			f._StartDate = IssueDateNum;
			f._ResetDate = IssueDateNum;
			f._yf = Yf::yearFraction(f._StartDate, f._FlowDate, m_yfconv);
		}
		else
		{
			f._StartDate = FlowDateNum;
			f._ResetDate = FlowDateNum;
			f._yf =  static_cast<double>(period) / 12.;
		}
		f._value = 0.;
		m_FlowMap[f._FlowDate] = f;
	}
}

Schedule::Schedule(const std::map<DateInt, double>& amortMap, DateInt CalcDate)
{
	_isInterest = false;
	for (std::map<DateInt, double>::const_iterator it = amortMap.begin(); it != amortMap.end(); ++it)
	{
		DateInt CapitalDate = it->first;
		if (CapitalDate > CalcDate)
		{
			Flow f;
			f._FlowDate = CapitalDate;
			f._value = it->second;
			m_FlowMap[CapitalDate] = f;
		}
	}
}

double Schedule::GetRemainingCapital(DateInt iDate) const
{
	double res = 0.;
	for (FlowMap::const_reverse_iterator itrev = m_FlowMap.rbegin(); itrev != m_FlowMap.rend(); ++itrev)
	{
		if (itrev->first >= iDate)
		{
			res += itrev->second._value;
		}
		else
		{
			break;
		}
	}
	return res;
}

