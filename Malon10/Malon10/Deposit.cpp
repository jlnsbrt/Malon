#include"Deposit.h"
#include"RateCurve.h"
#include"YearFraction.h"

double Deposit::price(const RateCurve & rateCurveObj, DateInt calcDate)
{
    return rateCurveObj.GetForwardDf(calcDate, m_StartDate) * exp(-m_Rate * Yf::yearFraction(m_StartDate, m_Maturity, m_yfC));
}

