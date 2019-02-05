#include"OrnsteinUhlenbeckProcess.h"
#include"YearFraction.h"

double OrnsteinUhlenbeckProcess::B(DateInt startDate, DateInt endDate) const
{
	double yearFraction = Yf::yearFraction(startDate, endDate, _yf);
	if (_meanReversion != 0)
	{
		return (1. - exp(-_meanReversion* yearFraction)) / _meanReversion;
	}
	else
	{
		return _meanReversion;
	}
}
