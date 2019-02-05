#ifndef _INTEGRAL_H_INCL
#define _INTEGRAL_H_INCL


class Integral
{
public:
	~Integral(){}
	enum IntegralMethod
	{
		Rectangle = 1,
		Trapez = 2,
		Simpson = 3
	};

	Integral(IntegralMethod im = Trapez, unsigned int numPoints = 100);

	virtual double f(double x) const  = 0;

	double Calculate(double startX, double endX) const;

private:
	IntegralMethod _im;
	unsigned int _numPoints;

	double elementIntegral(double startX, double endX) const;
};


inline Integral::Integral(IntegralMethod im, unsigned int numPoints) : _im(im), _numPoints(numPoints){}

#endif