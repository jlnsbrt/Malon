#include"VolCurve.h"


double VolCurve::Variance(DateInt start, DateInt end) const
{
	StepIntegrationVariance stepInteg(this);
	return stepInteg.value(start,end);
}