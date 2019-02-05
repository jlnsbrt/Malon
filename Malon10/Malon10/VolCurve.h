#ifndef _VOLCURVE_H_INCL
#define _VOLCURVE_H_INCL

#include"Curve.h"

class VolCurve : public Curve
{
public:
	VolCurve(const std::map<DateInt, double>& curveMap, YfConvention yfconv, InterpMethod im);
	VolCurve(  YfConvention yfconv, InterpMethod im);
	~VolCurve();

	double Variance(DateInt start, DateInt end) const;
private:

	class StepIntegrationVariance : public StepIntegration
	{
	public:
		StepIntegrationVariance(const Curve* curveObject);
		~StepIntegrationVariance();
		virtual double f(double v) const;
	};
};


inline	VolCurve::VolCurve(const std::map<DateInt, double>& curveMap, YfConvention yfconv, InterpMethod im)
	:Curve(curveMap,yfconv,im){}


inline	VolCurve::VolCurve(  YfConvention yfconv, InterpMethod im)
	:Curve(yfconv,im){}
inline	VolCurve::~VolCurve(){}


inline VolCurve::StepIntegrationVariance::StepIntegrationVariance(const Curve* curveObject): StepIntegration(curveObject){}
inline VolCurve::StepIntegrationVariance::~StepIntegrationVariance(){}

inline double VolCurve::StepIntegrationVariance::f(double v) const
{
	return v*v;
}
#endif