#include"Tests.h"
#include"Normal.h"
#include"FinanceFormula.h"

bool TestNormal()
{
	bool isC(true);

    // Select a few input values
    double x[] = 
    {
        -3, 
        -1, 
        0.0, 
        0.5, 
        2.1 
    };

    // Output computed by Mathematica
    // y = Phi[x]
    double y[] = 
    { 
        0.00134989803163, 
        0.158655253931, 
        0.5, 
        0.691462461274, 
        0.982135579437 
    };

    int numTests = sizeof(x)/sizeof(double);

    double maxError = 0.0;
    for (int i = 0; i < numTests; ++i)
    {
        double error = fabs(y[i] - Normal::phi(x[i]));
        if (error > maxError)
            maxError = error;
    }
	isC = isC && isCorrect(maxError, 0.,1.0E-7);
	return isC;
}


bool TestBlackFormula()
{
	bool isC(true);
	{
		double zc = 0.951229425;
		double forward = 102. /zc;
		double strike = 100. ;
		double variance = 0.0625;
		double callP = BlackFormula::callPrice(forward,strike,variance,zc);
		double putP  = BlackFormula::putPrice(forward,strike,variance,zc);
		isC = isC && isCorrect(  callP , 13.6206 ,1.0E-4) &&  isCorrect(  putP , 6.7436 ,1.0E-4);
	}
	{
		double zc = 0.904837418;
		double forward = 1. /zc;
		double strike = 100. ;
		double variance = 0.00125;
		double callP = BlackFormula::callPrice(forward,strike,variance,zc);
		double putP  = BlackFormula::putPrice(forward,strike,variance,zc);
		isC = isC && isCorrect(  callP , 0. ,1.0E-6) &&  isCorrect(  putP , (strike -forward) * zc  ,1.0E-6);
	}
	{
		double zc = 0.904837418;
		double forward = 102. /zc;
		double strike = 1. ;
		double variance = 0.00125;
		double callP = BlackFormula::callPrice(forward,strike,variance,zc);
		double putP  = BlackFormula::putPrice(forward,strike,variance,zc);
		isC = isC && isCorrect(  callP , (forward - strike ) * zc ,1.0E-6) &&  isCorrect(  putP , 0.  ,1.0E-6);
	}
	return isC;
}

