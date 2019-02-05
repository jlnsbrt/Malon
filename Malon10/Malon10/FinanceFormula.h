#ifndef _FINANCEFORMULA_H_INCL
#define _FINANCEFORMULA_H_INCL


// Black formula for options on forwards
class BlackFormula
{
public:
	static double optionPrice(double forward,double strike,double varianceAtResetDate,double zeroCouponAtMaturityDate, bool isCall);
	static double callPrice(double forward,double strike,double varianceAtResetDate,double zeroCouponAtMaturityDate);
	static double putPrice(double forward,double strike,double varianceAtResetDate,double zeroCouponAtMaturityDate);
private:
	static double dplus(double forward,double strike,double variance);
	static double dminus(double forward,double strike,double variance);
};

#endif