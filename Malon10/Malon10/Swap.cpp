#include"Swap.h"


Swap::Swap(unsigned int MaturityInMonths, DateInt Issue)
{
	DateInt Maturity = CalcMaturity(MaturityInMonths, Issue);
	m_Maturity = Maturity;
	m_Issue = Issue;
}

double Swap::price(const RateCurve& rateCurveObj, DateInt calcDate)
{
	return  m_ReceivedLeg->price(rateCurveObj, calcDate) - m_PaidLeg->price(rateCurveObj, calcDate);
}