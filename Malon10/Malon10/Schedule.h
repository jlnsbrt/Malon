#ifndef _SCHEDULE_H_INCL
#define _SCHEDULE_H_INCL

#include"Define.h"
#include<map>
#include"GregDate.h"

struct Flow
{
	DateInt _FlowDate;
	DateInt _StartDate;
	DateInt _ResetDate;
	double _yf;
	double _value;
};

class Schedule
{
public:
	Schedule(const GregDate& MaturityDate, const GregDate&  IssueDate, const GregDate& CalcDate, Frequency freq, YfConvention yfconv);
	Schedule(const std::map<DateInt, double>& amortMap, DateInt CalcDate);
	Schedule(const Schedule& other);
	~Schedule(){}

	typedef std::map<DateInt, Flow> FlowMap;
	typedef std::map<DateInt, Flow>::const_iterator FlowMapConstIterator;
	typedef std::map<DateInt, Flow>::iterator FlowMapIterator;
	FlowMapConstIterator Begin() const;
	FlowMapConstIterator End() const;
	FlowMapIterator Begin();
	FlowMapIterator End();

	bool isCapital() const;
	double GetRemainingCapital(DateInt iDate)  const;

private:
	FlowMap m_FlowMap;
	YfConvention m_yfconv;
	DateInt m_CalcDate;
	bool _isInterest;
};

inline Schedule::FlowMapConstIterator Schedule::Begin() const
{
	return m_FlowMap.begin();
}

inline Schedule::FlowMapConstIterator Schedule::End() const
{
	return m_FlowMap.end();
}

inline Schedule::FlowMapIterator Schedule::Begin() 
{
	return m_FlowMap.begin();
}

inline Schedule::FlowMapIterator Schedule::End() 
{
	return m_FlowMap.end();
}

inline bool Schedule::isCapital() const
{
	return !_isInterest;
}

#endif
