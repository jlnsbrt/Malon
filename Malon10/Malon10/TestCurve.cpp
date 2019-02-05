#include"Tests.h"
#include"RateCurve.h"
#include"YearFraction.h"
#include<iostream>

bool TestCurve()
{
	{
		bool correct = true;
		std::map<DateInt, double> m;
		m[43020] = 0.001;
		m[43051] = 0.0009;
		m[43081] = 0.0011;
		m[43112] = 0.0014;

		Curve cStep(m,Act36525, StepInterpolation);
		Curve cLin(m, Act36525, LinearInterpolation);
		for (std::map<DateInt, double>::const_iterator it  = m.begin() ;  it!= m.end() ; ++it)
		{
			DateInt d0 = it->first;
			double v0 = it->second;
			//////////////////////////////
			double val = cStep.GetValue(d0);
			double valLin = cLin.GetValue(d0);
			correct = correct &&  isCorrect(val,v0);
			correct = correct &&  isCorrect(valLin, v0);
			///////////////////////////////
			DateInt d = d0  + 10 + d0%3;
			val = cStep.GetValue(d);
			valLin = cLin.GetValue(d);
			++it;
			double v = v0;
			double v1 = v0;
			if (it != m.end())
			{
				DateInt d1 = it->first;
				v1 = it->second;
				double a = Yf::yearFraction(d0, d, Act36525) / Yf::yearFraction(d0, d1, Act36525);
				v = v0 * (1 - a) + v1* a;
			}
			correct = correct &&  isCorrect(val, v1);
			correct = correct &&  isCorrect(valLin, v);
			--it;
		}
		return correct;
	}
}

bool TestRateCurveLinInterpolation()
{
	bool correct = true;
	std::map<DateInt, double> rateMap;
	rateMap[43022] = 0.0009;
	rateMap[43053] = 0.0012;
	rateMap[43083] = 0.0015;
	rateMap[43114] = 0.0035;
	rateMap[43204] = 0.0056;
	rateMap[43387] = 0.0054;
	rateMap[43752] = 0.0069;
	rateMap[44118] = 0.0125;
	rateMap[44848] = 0.0156;
	rateMap[46674] = 0.0216;
	RateCurve rC(rateMap, ActAct, LinearInterpolation, RateType);
	DateInt YcStartDate = rC.GetYcStartDate();
	DateInt date = YcStartDate;
	unsigned int step = 10;
	for (unsigned int i = 0; i < 320; ++i)
	{
		//std::cout << "Date = " << date << " DF = " << rC.GetDf(date) << std::endl;
		date += step;
	}


	for (std::map<DateInt, double>::const_iterator it = rateMap.begin(); it != rateMap.end(); ++it)
	{
		DateInt d0 = it->first;
		double r0 = it->second;
		//////////////////////////////
		double df = rC.GetDf(d0);
		double yf = Yf::yearFraction(YcStartDate, d0, ActAct);
		double dfManual = std::exp(-r0*yf);
		correct = correct &&  isCorrect(df, dfManual);
		///////////////////////////////
		DateInt d = d0 + 10 + d0 % 3;
		df = rC.GetDf(d);
		yf = Yf::yearFraction(YcStartDate, d, ActAct);
		++it;
		double r1 = r0;
		DateInt d1 = d0;
		if (it != rateMap.end())
		{
			d1 = it->first;
			r1 = it->second;		
		}
		double r = r0;
		if ( d1 != d0 )
		{
			double yf0 = Yf::yearFraction(d0, d, ActAct);
			double yfS = Yf::yearFraction(d0, d1, ActAct);
			r = r0 +  (r1 -r0) * yf0/yfS;
		}
		--it;
		dfManual = std::exp(-r*yf);
		correct = correct &&  isCorrect(df, dfManual);
	}

	return correct;
}

bool TestRateCurve()
{
	bool correct = true;
	std::map<DateInt, double> rateMap;
	rateMap[43022] = 0.0009;
	rateMap[43053] = 0.0012;
	rateMap[43083] = 0.0015;
	rateMap[43114] = 0.0035;
	rateMap[43204] = 0.0056;
	rateMap[43387] = 0.0054;
	rateMap[43752] = 0.0069;
	rateMap[44118] = 0.0125;
	rateMap[44848] = 0.0156;
	rateMap[46674] = 0.0216;
	RateCurve rC(rateMap, Act36525, StepInterpolation, RateType);
	DateInt YcStartDate = rC.GetYcStartDate();
	DateInt date = YcStartDate;
	unsigned int step = 10;
	for (unsigned int i = 0; i < 320; ++i)
	{
		//std::cout << "Date = " << date << " DF = " << rC.GetDf(date) << std::endl;
		date += step;
	}


	for (std::map<DateInt, double>::const_iterator it = rateMap.begin(); it != rateMap.end(); ++it)
	{
		DateInt d0 = it->first;
		double r0 = it->second;
		//////////////////////////////
		double df = rC.GetDf(d0);
		double yf = Yf::yearFraction(YcStartDate, d0, Act36525);
		double dfManual = std::exp(-r0*yf);
		correct = correct &&  isCorrect(df, dfManual);
		///////////////////////////////
		DateInt d = d0 + 10 + d0 % 3;
		df = rC.GetDf(d);
		yf = Yf::yearFraction(YcStartDate, d, Act36525);
		++it;
		if (it != rateMap.end())
		{
			r0 = it->second;		
		}
		--it;
		dfManual = std::exp(-r0*yf);
		correct = correct &&  isCorrect(df, dfManual);
	}

	return correct;
}

bool TestCurveStepIntegrartion()
{
	bool correct = true;
	YfConvention Yfc(Act365);
	Curve c(Yfc,StepInterpolation);
	DateInt d1(40000), d2(41200), d3(41300) , d4(41500);
	double v1(1.),v2(2.3), v3(3.2) , v4(4.1);
	c.AddPoint(d1,v1);
	c.AddPoint(d2,v2);
	c.AddPoint(d3,v3);
	c.AddPoint(d4,v4);

	class ExpIntegration : public Curve::StepIntegration
	{
	public:

		ExpIntegration(const Curve* curveObject):StepIntegration(curveObject){}
		virtual double f(double v) const
		{
			return std::exp(v*0.05);
		}
	};
	{
		DateInt inf = 40100;
		DateInt sup = 41250;
		ExpIntegration IntegObj(&c);
		double integral = IntegObj.value(inf,sup);

		double integralRep = Yf::yearFraction(inf,d2,Yfc) *IntegObj.f (v2 ) + 
		+ Yf::yearFraction(d2,sup,Yfc) *IntegObj.f(v3);
		correct = correct && isCorrect(integral,integralRep,1.0E-8);
	}
	{
		DateInt inf = 40100;
		DateInt sup = 41330;
		ExpIntegration IntegObj(&c);
		double integral = IntegObj.value(inf,sup);

		double integralRep = Yf::yearFraction(inf,d2,Yfc) *IntegObj.f (v2 ) + 
		+ Yf::yearFraction(d2,d3,Yfc) *IntegObj.f(v3)
		+Yf::yearFraction(d3,sup,Yfc) *IntegObj.f(v4);
		correct = correct && isCorrect(integral,integralRep,1.0E-8);
	}
	{
		DateInt inf = 40100;
		DateInt sup = 41620;
		ExpIntegration IntegObj(&c);
		double integral = IntegObj.value(inf,sup);

		double integralRep = Yf::yearFraction(inf,d2,Yfc) *IntegObj.f (v2 ) + 
		+ Yf::yearFraction(d2,d3,Yfc) *IntegObj.f(v3)
		+Yf::yearFraction(d3,d4,Yfc) *IntegObj.f(v4)
		+Yf::yearFraction(d4,sup,Yfc) *IntegObj.f(v4);
		correct = correct && isCorrect(integral,integralRep,1.0E-8);
	}
	{
		DateInt inf = 41220;
		DateInt sup = 41450;
		ExpIntegration IntegObj(&c);
		double integral = IntegObj.value(inf,sup);

		double integralRep = Yf::yearFraction(inf,d3,Yfc) *IntegObj.f (v3 ) + 
		+Yf::yearFraction(d3,sup,Yfc) *IntegObj.f(v4);
		correct = correct && isCorrect(integral,integralRep,1.0E-8);
	}
	{
		DateInt inf = 41630;
		DateInt sup = 41820;
		ExpIntegration IntegObj(&c);
		double integral = IntegObj.value(inf,sup);
		double integralRep = Yf::yearFraction(inf,sup,Yfc) *IntegObj.f (v4 );
		correct = correct && isCorrect(integral,integralRep,1.0E-8);
	}
	return correct;
}