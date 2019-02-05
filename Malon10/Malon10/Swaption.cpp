#include"Swaption.h"
#include"FinanceFormula.h"
#include"YearFraction.h"

Swaption::Swaption(unsigned int MaturityInMonths, DateInt swapStartDate,DateInt optionDate, double notional, double fixedRate, Frequency fixedFreq, Frequency floatFreq, YfConvention fixedconv, YfConvention floatconv, bool isFlReceived )
	:m_optionDate(optionDate), m_pIRS(new InterestRateSwap(MaturityInMonths,swapStartDate,notional,fixedRate,fixedFreq,floatFreq,fixedconv,floatconv,isFlReceived))
{
	m_Maturity = CalcMaturity(MaturityInMonths,swapStartDate);
}

double Swaption::price(const RateCurve & rateCurveObj, double volatility, YfConvention volYfConv , DateInt calcDate)
{
	double strike = m_pIRS->GetFixedRate();
	double swapRate = m_pIRS->ParRate(rateCurveObj,calcDate);
	double annuity =m_pIRS->Annuity(rateCurveObj,calcDate);
	double variance = volatility * volatility * Yf::yearFraction(calcDate,m_optionDate,volYfConv);
	double npv = BlackFormula::optionPrice(swapRate,strike,variance,1.,m_pIRS->IsFlReceived());
	npv *= annuity;
	return npv;
}
