#include"MultiRateCurve.h"

MultiRateCurve::MultiRateCurve(const MultiRateCurve& other) :m_Currency(other.m_Currency)
{
	m_DiscountCurve.reset(new RateCurve(*(other.m_DiscountCurve)));
	for (std::map < Frequency, std::unique_ptr<RateCurve> >::const_iterator it = other.m_LiborCurveMap.begin(); it != other.m_LiborCurveMap.end(); ++it)
	{
		m_LiborCurveMap[it->first] = std::unique_ptr<RateCurve>(new RateCurve(*(it->second)));
	}	
}

RateCurve* MultiRateCurve::GetLiborCurve(Frequency tenor)
{
	std::map<Frequency, std::unique_ptr<RateCurve> >::const_iterator it = m_LiborCurveMap.find(tenor);
	if (it != m_LiborCurveMap.end())
	{
		return it->second.get();
	}
	else
	{
		return NULL;
	}
}

void MultiRateCurve::SetLiborCurve(RateCurve* dc)
{
	m_LiborCurveMap[dc->GetTenor()] = std::unique_ptr<RateCurve>(new RateCurve(*dc));
}

double MultiRateCurve::CalcSurvivalProbability(Frequency tenor,DateInt fromDate, DateInt toDate) 
{
	RateCurve* lC = GetLiborCurve(tenor);
	ThrowMessage(NULL == lC,"Invalid tenor in the multicurve object");
	RateCurve* dC = GetDiscountCurve();
	ThrowMessage(NULL == dC,"Discount curve not defined in the multicurve object");
	return lC->GetForwardDf(fromDate,toDate)/dC->GetForwardDf(fromDate,toDate);
}
