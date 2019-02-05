#include"IRModelG2PLUSPLUS.h"
#include"YearFraction.h"
#include"FinanceFormula.h"
#include"FixedRateBond.h"
#include<cmath>

double IRModelG2PLUSPLUS::zeroCouponBondPrice(DateInt calcDate, DateInt ZcMaturity, const std::vector<double>& x) const
{
	if (x.size() != 2)
	{
		throw("Invalid state parameters in IRModelG2PLUSPLUS");
	}
	DateInt YcStartDate = GetYcStartDate();
	if (calcDate < YcStartDate)
	{
		throw("Invalid calc date");
	}
	if (calcDate == YcStartDate)
	{
		return _pInitialRateCurve->GetDf(ZcMaturity);
	}
	else if (calcDate > YcStartDate)
	{
		return A(calcDate, ZcMaturity) * std::exp( -B(calcDate, ZcMaturity, _mr1) * x[0] - B(calcDate, ZcMaturity, _mr2) * x[1]);
	}
	throw("CalcDate before Yc start date");
}

double IRModelG2PLUSPLUS::zeroCouponBondOptionPrice(DateInt calcDate, DateInt optionMaturity, DateInt ZcMaturity, double strike, bool isCall, const std::vector<double>& x) const
{
	DateInt ycStartDate = GetYcStartDate();
	double zCMaturity = zeroCouponBondPrice(calcDate, optionMaturity, x);
	double forward = zeroCouponBondPrice(calcDate, ZcMaturity, x) / zCMaturity;
	double variance = ZeroCouponVariance(ycStartDate, optionMaturity, ZcMaturity);
	double res = BlackFormula::optionPrice(forward, strike, variance, zCMaturity, isCall);
	return res;
}

double IRModelG2PLUSPLUS::ZeroCouponVariance(DateInt calcDate, DateInt ZcMaturity) const
{
	double res1 = _v1 * _v1 * PartialVariance(calcDate, ZcMaturity, _mr1, _mr1);
	double res2 = _v2 * _v2 * PartialVariance(calcDate, ZcMaturity, _mr2, _mr2);
	double res12 = 2. * _rho *_v1 * _v2 * PartialVariance(calcDate, ZcMaturity, _mr1, _mr2);
	return res1 + res2 + res12;
}

double IRModelG2PLUSPLUS::PartialVariance(DateInt calcDate, DateInt ZcMaturity, double mr1, double mr2) const
{
	double yearFraction = Yf::yearFraction(calcDate, ZcMaturity, _yfC);
	if (mr1  < 1.0E-5 && mr2  < 1.0E-5)
	{
		return   yearFraction *yearFraction *yearFraction / 3.;
	}
	else if (mr1 < 1.0E-5){
		return (yearFraction *yearFraction / 2. - B(yearFraction, mr2) / (mr1 + mr2) + yearFraction * std::exp(-mr2 * yearFraction) / (mr1 + mr2)) / mr2;
	}
	else if (mr2 < 1.0E-5){
		return (yearFraction *yearFraction / 2. - B(yearFraction, mr1) / (mr1 + mr2) + yearFraction * std::exp(-mr1 * yearFraction) / (mr1 + mr2)) / mr1;
	}
	else {
		return (yearFraction - B(yearFraction, mr1) - B(yearFraction, mr2) + B(yearFraction, mr1 + mr2)) / (mr1*mr2);
	}
}

double IRModelG2PLUSPLUS::ZeroCouponVol(double yearFraction) const
{
	double res = B(yearFraction, _mr1)*B(yearFraction, _mr1) * _v1* _v1 + B(yearFraction, _mr2)*B(yearFraction, _mr2) * _v2* _v2
		+ 2 * _rho * B(yearFraction, _mr1)*B(yearFraction, _mr2) * _v1* _v2;
	return std::sqrt(res);
}

double IRModelG2PLUSPLUS::ZeroCouponVol(DateInt calcDate, DateInt ZcMaturity) const
{
	double yearFraction = Yf::yearFraction(calcDate, ZcMaturity, _yfC);
	return ZeroCouponVol(yearFraction);
}


double IRModelG2PLUSPLUS::B(double yearFraction, double mr) const
{
	if (mr != 0)
	{
		return (1. - exp(-mr* yearFraction)) / mr;
	}
	else
	{
		return yearFraction;
	}
}

double IRModelG2PLUSPLUS::B(DateInt calcDate, DateInt maturity, double mr) const
{
	double yearFraction = Yf::yearFraction(calcDate, maturity, _yfC);
	return B(yearFraction, mr);
}

double IRModelG2PLUSPLUS::A(DateInt calcDate, DateInt maturity) const
{
	DateInt YcStartDate = GetYcStartDate();
	double zC = _pInitialRateCurve->GetForwardDf(calcDate, maturity);
	double var = 0.5 * (ZeroCouponVariance(calcDate, maturity) - ZeroCouponVariance(YcStartDate, maturity) + ZeroCouponVariance(YcStartDate, calcDate));
	return zC * std::exp(var);
}

double IRModelG2PLUSPLUS::ZeroCouponVariance(DateInt calcDate, DateInt ZcExpiry, DateInt ZcMaturity) const
{
	ZcVarianceIntegration zcvI;
	double yearFractionExpiry = Yf::yearFraction(calcDate, ZcExpiry, _yfC);
	double yearFractionMaturity = Yf::yearFraction(calcDate, ZcMaturity, _yfC);
	zcvI.m_yfExpiry = yearFractionExpiry;
	zcvI.m_yfMaturity = yearFractionMaturity;
	zcvI.m_pG2PP = this;
	double res = zcvI.Calculate(0., yearFractionExpiry);
	return res;
}