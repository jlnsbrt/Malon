#include"YearFraction.h"
#include"GregDate.h"
#include<algorithm>

double Yf::yearFraction(DateInt beginDate, DateInt endDate, YfConvention yfconv)
{
	GregDate gBegin(beginDate);
	GregDate gEnd(endDate);
	int yearsInt = Years(gBegin, endDate);
	gEnd.AddMonth(-12 * yearsInt);
	double rest = Days(gBegin, gEnd, yfconv) / Basis(gEnd, yfconv);
	return yearsInt + rest;
}



int Yf::Years(GregDate begin, GregDate end)
{
	int beginYear = begin.Year();
	int endYear = end.Year();
	int beginMonth = begin.Month();
	int endMonth = end.Month();
	int beginDay = begin.Day();
	int endDay = end.Day();
	int res = endYear - beginYear;
	if ( endMonth < beginMonth)
	{
		res--;
	}
	if (endMonth == beginMonth && endDay < beginDay)
	{
		res--;
	}
	return res;
}


int Yf::Days(GregDate begin, GregDate end, YfConvention YfC)
{
	switch (YfC)
	{
	case Act36525:
	case Act365:
	case ActAct:
	{
		return end.GetSerialNum() - begin.GetSerialNum();
	}
	case _30360:
	{
		int D1 = std::min(begin.Day(), 30);
		int D2 = end.Day();
		if (D1 == 30)
		{
			D2 = std::min(D2, 30);
		}
		return  360 * (end.Year() - begin.Year()) + 30 * (end.Month() - begin.Month()) + (D2 - D1);
	}
	default:
		throw("Invalid year fracion convention");
	}
}

double Yf::Basis(GregDate pivot, YfConvention YfC)
{
	switch (YfC)
	{
	case Act36525:
		return 365.25;
	case Act365:
		return 365.;
	case _30360:
		return 360.;
	case ActAct:
	{
		GregDate g0(pivot);
		g0.AddYears(-1);
		return pivot.GetSerialNum() - g0.GetSerialNum();
	}
	default:
		throw("Invalid year fracion convention");
	}
}

