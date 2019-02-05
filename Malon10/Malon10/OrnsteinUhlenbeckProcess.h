#ifndef _ORNSTEINUHLENBECKPROCESS_H_INCL
#define _ORNSTEINUHLENBECKPROCESS_H_INCL
#include"Process.h"
#include"Curve.h"

class OrnsteinUhlenbeckProcess : public Process
{
public:
	OrnsteinUhlenbeckProcess(double meanRev, const std::map<DateInt, double>& volMap, YfConvention yf);
	~OrnsteinUhlenbeckProcess();
private:

	double B(DateInt startDate, DateInt endDate) const;

	double _meanReversion;
	Curve _volatility;
	YfConvention _yf;
};

inline OrnsteinUhlenbeckProcess::OrnsteinUhlenbeckProcess(double meanRev, const std::map<DateInt, double>& volMap, YfConvention yf)
	:_meanReversion(meanRev), _volatility(volMap, Act365, StepInterpolation), _yf(yf){}

inline OrnsteinUhlenbeckProcess::~OrnsteinUhlenbeckProcess(){}


#endif