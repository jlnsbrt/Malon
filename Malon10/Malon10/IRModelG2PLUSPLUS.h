#ifndef _IRMODDELG2PLUSPLUS_H_INCL
#define _IRMODDELG2PLUSPLUS_H_INCL

#include"IRModel.h"
#include"Integral.h"


class IRModelG2PLUSPLUS : public IRModel
{
public:
	IRModelG2PLUSPLUS(double meanRev1, double vol1, double meanRev2, double vol2, double correl, const RateCurve& initialRateCurve,  YfConvention yf);
	~IRModelG2PLUSPLUS();

	virtual double zeroCouponBondPrice(DateInt calcDate, DateInt ZcMaturity, const std::vector<double>& x) const;
	virtual double zeroCouponBondOptionPrice(DateInt calcDate, DateInt optionMaturity, DateInt ZcMaturity, double strike, bool isCall,const std::vector<double>& x) const;
	double ZeroCouponVariance(DateInt calcDate, DateInt ZcMaturity) const;
	double ZeroCouponVariance(DateInt calcDate, DateInt ZcExpiry, DateInt ZcMaturity) const;
	double ZeroCouponVol(DateInt calcDate, DateInt ZcMaturity) const;
	double ZeroCouponVol(double yearFraction) const;
private:

	double B(double yearFraction, double mr) const;
	double B(DateInt calcDate, DateInt maturity, double mr) const;
	double PartialVariance(DateInt calcDate, DateInt ZcMaturity, double mr1, double mr2) const;
	double A(DateInt calcDate, DateInt maturity) const;
	double _mr1, _mr2, _v1, _v2, _rho;
	//std::auto_ptr<RateCurve> _pInitialRateCurve;
	//YfConvention _yfC;

	class ZcVarianceIntegration : public Integral
	{
	public:
		ZcVarianceIntegration() : Integral(Integral::Simpson, 100){}
		const IRModelG2PLUSPLUS*  m_pG2PP;
		double m_yfExpiry;
		double m_yfMaturity;
		virtual double f(double u) const
		{
			double res = m_pG2PP->ZeroCouponVol(m_yfExpiry - u) - m_pG2PP->ZeroCouponVol(m_yfMaturity - u);
			return res*res;
		}
	};
};

inline IRModelG2PLUSPLUS::IRModelG2PLUSPLUS(double meanRev1, double vol1, double meanRev2, double vol2, double correl, const RateCurve& initialRateCurve, YfConvention yf)
	:_mr1(meanRev1), _mr2(meanRev2), _v1(vol1), _v2(vol2), _rho(correl), IRModel(initialRateCurve, yf){}

inline IRModelG2PLUSPLUS::~IRModelG2PLUSPLUS(){}


#endif