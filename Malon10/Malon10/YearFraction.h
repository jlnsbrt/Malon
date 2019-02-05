#ifndef _YF_H_INCL
#define _YF_H_INCL
#include"Define.h"
class GregDate;

//bug30360

class Yf
{
public:
	Yf(){}
	~Yf(){}

	static double yearFraction(DateInt beginDate, DateInt EndDate, YfConvention yfconv);

private:
	static int Years(GregDate begin, GregDate end);
	static int Days(GregDate begin, GregDate end, YfConvention YfC);
	static double Basis(GregDate pivot, YfConvention YfC);
};

 #endif