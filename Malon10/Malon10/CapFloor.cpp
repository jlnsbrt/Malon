#include"CapFloor.h"
#include"YearFraction.h"
#include"FinanceFormula.h"
#include<algorithm>

double CapFloor::price(const RateCurve & rateCurveObj, double volatility, YfConvention volYfConv , DateInt calcDate)
{
	m_CalcDate = calcDate;
	Leg::CalcSchedule();
	double res = 0.;
    if (m_monocurve)
    {
        for (Schedule::FlowMapIterator it = m_pInterestSchedule->Begin(); it != m_pInterestSchedule->End(); ++it)
        {
			if (  it->second._ResetDate <  calcDate )			// current flow
			{
				res += it->second._yf * std::max(  m_CurrentLibor - m_Rate , 0.)  *  rateCurveObj.GetForwardDf(calcDate,it->second._FlowDate) * GetRemainingCapital(it->second._FlowDate);
			}
			else //forward flow
			{
				double yf =  it->second._yf;
				double forward = rateCurveObj.GetForwardRate(calcDate,it->second._ResetDate, it->second._FlowDate);
				double variance = volatility * volatility * Yf::yearFraction(calcDate,it->second._ResetDate,volYfConv);
				double zeroCouponAtMaturityDate = rateCurveObj.GetForwardDf(calcDate,it->second._FlowDate);
				double expflow(0.);
				switch(m_po)
				{
				case _Cap:
					{
						expflow= it->second._yf * BlackFormula::callPrice(forward,m_Rate,variance,zeroCouponAtMaturityDate);  
					}
					break;
				case _Floor:
					{
						expflow= it->second._yf * BlackFormula::putPrice(forward,m_Rate,variance,zeroCouponAtMaturityDate);
					}
					break;
				default:
					{
						throw("Invalid cap floor pay off");
					}
				}
				res += expflow *  GetRemainingCapital(it->second._FlowDate);
			}
		}
	}
	return res;
}