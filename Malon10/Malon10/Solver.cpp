#include"Solver.h"
#include<cmath>

double Solver::_Eps = 1.0E-9;
double Solver::_dfEps = 1.0E-4;

double Solver::df(double x) const
{
	return (f(x + _dfEps) - f(x - _dfEps)) / (2. * _dfEps);
}

double Solver::Solve() const
{
	switch(m_SolverMethod)
	{
	case Bissection:
	{
		return SolveWithBissection();
	}
	break;
	case Newton_Raphson:
	{
		return SolveWithNewton();
	}
	break;
	default:
		throw("Solver method not supported");
	}
}

double Solver::SolveWithBissection() const
{
	double a = m_xMin;
	double b = m_xMax;
	if (f(a) * f(b) > 0)
	{
		throw("Invalid Bissection solver inputs");
	}
	double c = a;
	unsigned int count = 0;
	while (b - a > _Eps)
	{
		if (count > 100)
		{
			throw("The solver Bissection has failed");
		}
		c = (a + b) / 2.;
		if (f(a) * f(c) <= 0)
		{
			b = c;
		}
		else if (f(c) * f(b) <= 0)
		{
			a = c;
		}
		else
		{
			throw("The solver Bissection has failed");
		}
		++count;
	}
	return (a + b) / 2.;
}


double Solver::SolveWithNewton() const
{
	double x0 = m_x0;
	double x1 = x0 + 2 * _Eps;
	unsigned int count = 0;
	double f0(0.), df0(1.);
	while (std::abs(x1 - x0) > _Eps)
	{
		x0 = x1;
		if (count > 100)
		{
			throw("The solver Newton has failed");
		}
		df0 = df(x0);
		f0 = f(x0);
		if (std::abs(df0) < 1.0E-7)
		{
			throw("The solver Newton has failed");
		}
		x1 = x0 - f0 / df0;
		++count;
	}
	return x1;
}