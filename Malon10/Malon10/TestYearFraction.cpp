#include"YearFraction.h"
#include"Tests.h"
#include"GregDate.h"

bool TestYearFraction()
{
	bool isc(true);
	DateInt g1Num(40910);
	DateInt g2Num(40999);
	GregDate g1(g1Num);
	GregDate g2(g2Num);
	double yf365(0.), yf36525(0.),yf360(0.),yfAA(0.);
	double rest365 = (g2Num - g1Num) / 365.;
	double rest36525 = (g2Num - g1Num) / 365.25;
	double rest360 = (g2.Day() - g1.Day() + 30 * (g2.Month() - g1.Month()) + 360 * (g2.Year() - g1.Year())) / 360.;
	double restAA = (g2Num - g1Num) / 366.;
	double yfReplic365 = rest365;
	double yfReplic36525 = rest36525;
	double yfReplic360 = rest360;
	double yfReplicAA = restAA;
	for (unsigned int i = 0; i < 20; ++i)
	{
		g2Num = g2.GetSerialNum();
		yf365 =  Yf::yearFraction(g1Num, g2Num, Act365);
		yf36525 = Yf::yearFraction(g1Num, g2Num, Act36525);
		yf360 = Yf::yearFraction(g1Num, g2Num, _30360);
		yfAA = Yf::yearFraction(g1Num, g2Num, ActAct);
		yfReplic365 = rest365 + i;
		yfReplic36525 = rest36525 + i;
		yfReplic360 = rest360 + i;
		yfReplicAA = restAA + i;
		isc = isc && isCorrect(yf365, yfReplic365, 1.0E-10);
		isc = isc && isCorrect(yf36525, yfReplic36525, 1.0E-10);
		isc = isc && isCorrect(yf360, yfReplic360, 1.0E-10);
		isc = isc && isCorrect(yfAA, yfReplicAA, 1.0E-10);
		g2.AddYears(1);
	}
	return isc;
}