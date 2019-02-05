#ifndef _IRMODDEL_H_INCL
#define _IRMODDEL_H_INCL
#include"Model.h"
#include"RateCurve.h"
#include<memory>
#include<vector>

class FixedRateBond;
class CapFloor;

class IRModel
{
public:
	IRModel(const RateCurve& initialRateCurve, YfConvention yf);
	~IRModel();

	virtual double zeroCouponBondPrice(DateInt calcDate, DateInt ZcMaturity,const std::vector<double>& x) const = 0;
	virtual double zeroCouponBondOptionPrice(DateInt calcDate, DateInt optionMaturity, DateInt ZcMaturity, double strike, bool isCall, const std::vector<double>& x) const = 0;
	virtual double BondPrice(DateInt calcDate, FixedRateBond &frb, const std::vector<double>& x) const;
	virtual double CapFloorPrice(DateInt calcDate, CapFloor& cpflr, const std::vector<double>& x) const;
	DateInt GetYcStartDate() const;
protected:
	std::auto_ptr<RateCurve> _pInitialRateCurve;
	YfConvention _yfC;

};

inline IRModel::IRModel(const RateCurve& initialRateCurve, YfConvention yf) :_yfC(yf), _pInitialRateCurve(new RateCurve(initialRateCurve))
{}

inline IRModel::~IRModel(){}

inline  DateInt IRModel::GetYcStartDate() const
{
	return _pInitialRateCurve->GetYcStartDate();
}

#endif