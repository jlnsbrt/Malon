#include"Tests.h"
#include"Integral.h"

bool TestIntegral()
{
	bool isC(true);
	class IntegralXCinq : public Integral
	{
	public:
		IntegralXCinq(IntegralMethod im = Trapez, unsigned int numPoints = 100) : Integral(im, numPoints){}
		~IntegralXCinq(){}
		virtual double f(double x) const
		{
			return x * x * x ;
		}
	};

	IntegralXCinq itrap(Integral::Trapez, 1000);
	double resValue = 2 * 2 * 2 * 2 / 4.;
	double resTrap = itrap.Calculate(0., 2.);
	isC = isC && isCorrect(resTrap, resValue, 1.0E-4);
	IntegralXCinq iSimp(Integral::Simpson, 100);
	double resSimp = iSimp.Calculate(0., 2.);
	isC = isC && isCorrect(resSimp, resValue, 1.0E-9);
	return isC;
}