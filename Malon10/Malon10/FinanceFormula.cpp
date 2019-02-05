#include"FinanceFormula.h"
#include"Normal.h"
#include"Define.h"
#include<cmath>

double BlackFormula::dplus(double forward,double strike,double variance)
{
	ThrowMessage(variance <= 0,"Negative variance in Black Formula");
	double stdDev = std::sqrt(variance);
	return std::log(forward/strike) / stdDev + 0.5 *  stdDev;
}
double BlackFormula::dminus(double forward,double strike,double variance)
{
	double stdDev = std::sqrt(variance);
	return dplus(forward,strike,variance) - stdDev;
}
double BlackFormula::callPrice(double forward,double strike,double varianceAtResetDate,double zeroCouponAtMaturityDate)
{
	double dp = dplus(forward,strike,varianceAtResetDate);
	double dm = dminus(forward,strike,varianceAtResetDate);
	double res = zeroCouponAtMaturityDate * ( forward * Normal::phi( dp) 
		- strike *  Normal::phi( dm) ); 
	return res; 
}
double BlackFormula::putPrice(double forward,double strike,double varianceAtResetDate,double zeroCouponAtMaturityDate)
{
	return callPrice(forward,strike,varianceAtResetDate,zeroCouponAtMaturityDate)  + (strike - forward) * zeroCouponAtMaturityDate;
}
double BlackFormula::optionPrice(double forward,double strike,double varianceAtResetDate,double zeroCouponAtMaturityDate, bool isCall)
{
	if ( isCall )
	{
		return callPrice(forward,strike,varianceAtResetDate,zeroCouponAtMaturityDate);
	}
	else
	{
		return putPrice(forward,strike,varianceAtResetDate,zeroCouponAtMaturityDate);
	}
}