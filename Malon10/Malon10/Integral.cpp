#include"Integral.h"

double Integral::Calculate(double startX, double endX) const
{
	double eps = (endX - startX) / _numPoints;
	double integral(0.);
	unsigned int i = 0;
	double x1 = startX;
	double x2 = x1 + eps;
	while (i < _numPoints)
	{
		integral += elementIntegral(x1, x2);
		x1 = x2;
		x2 += eps;
		++i;
	}
	return integral;
}

double Integral::elementIntegral(double startX, double endX) const
{
	switch (_im)
	{
	case Integral::Rectangle:
		return f(startX + endX)* (endX - startX);
	case Integral::Trapez:
		return (f(startX) + f(endX)) * (endX - startX)/2.;
	case Integral::Simpson:
		return   (f(startX) + 4. * f( (startX + endX)/2.) + f(endX) )* (endX - startX) / 6.;
	default:
		throw("Invalid Imtegral method");
	}
}