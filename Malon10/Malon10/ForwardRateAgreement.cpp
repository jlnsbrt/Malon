#include"ForwardRateAgreement.h"
#include"YearFraction.h"
#include"RateCurve.h"


ForwardRateAgreement::ForwardRateAgreement(DateInt start,double notional, double rate, Frequency tenor,YfConvention yfC, bool isFlReceived)
	:InterestRateSwap(NbMonths(tenor),start,notional,rate,tenor,tenor,yfC,yfC,isFlReceived),m_Tenor(tenor){}





//double ForwardRateAgreement::GetDfAtMaturity(const RateCurve & rateCurveObj, DateInt calcDate)
//{
//	double res = rateCurveObj.GetForwardDf(calcDate,m_StartDate);
//	double yf = Yf::yearFraction(m_StartDate,GetMaturity(),m_yfC);
//	return res/(1+ m_Rate * yf);
//}