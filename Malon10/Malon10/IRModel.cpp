#include"IRModel.h"
#include"FixedRateBond.h"
#include"CapFloor.h"
#include<algorithm>


double IRModel::BondPrice(DateInt calcDate, FixedRateBond &frb, const std::vector<double>& x) const
{
	frb.SetCalcDate(calcDate);
	frb.CalcSchedule();
	double res = 0;
	for (Schedule::FlowMapIterator it = frb.GetInterestSchedule()->Begin(); it != frb.GetInterestSchedule()->End(); ++it)
	{
		res += it->second._value * zeroCouponBondPrice(calcDate, it->second._FlowDate, x);
	}
	if (frb.WithCapital())
	{
		for (Schedule::FlowMapIterator it = frb.GetCapitalSchedule()->Begin(); it != frb.GetCapitalSchedule()->End(); ++it)
		{
			res += it->second._value * zeroCouponBondPrice(calcDate, it->second._FlowDate, x);
		}
	}
	return res; 
}

double IRModel::CapFloorPrice(DateInt calcDate, CapFloor& cpflr, const std::vector<double>& x) const
{
	double res = 0.;
	DateInt YcStartDate = GetYcStartDate();
	if (calcDate < YcStartDate)
	{
		throw("Invalid calc date");
	}
	cpflr.SetCalcDate(calcDate);
	cpflr.Leg::CalcSchedule();
	double strikeRate = cpflr.GetStrikeRate();
	if (cpflr.IsMonoCurve())
	{
		for (Schedule::FlowMapIterator it = cpflr.GetInterestSchedule()->Begin(); it != cpflr.GetInterestSchedule()->End(); ++it)
		{
			if (it->second._ResetDate <  YcStartDate)			// current flow
			{
				double rate(0.);
				if (cpflr.GetPayOff() == CapFloor::_Cap)
				{
					rate = std::max(cpflr.GetCurrentLibor() - strikeRate, 0.);
				}
				else if (cpflr.GetPayOff() == CapFloor::_Floor)
				{
					rate = std::max(strikeRate - cpflr.GetCurrentLibor(), 0.);
				}
				else
				{
					throw("Invalid Cap Floor pay off");
				}
				res += it->second._yf * rate  *  zeroCouponBondPrice(calcDate, it->second._FlowDate, x)  * cpflr.GetRemainingCapital(it->second._FlowDate);
			}
			else //forward flow. We trannsform cap/floors into bond option
			{
				double yf = it->second._yf;
				double strike = 1. / (1 + yf * strikeRate);
				bool isCall(false);
				if (cpflr.GetPayOff() == CapFloor::_Floor)
				{
					isCall = true;
				}
				res += 1. / strike * cpflr.GetRemainingCapital(it->second._FlowDate) * zeroCouponBondOptionPrice(calcDate, it->second._ResetDate, it->second._FlowDate, strike, isCall, x);
			}
		}
	}
	return res;
}