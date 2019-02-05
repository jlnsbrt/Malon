#ifndef _SOLVER_H_INCL
#define _SOLVER_H_INCL


class Solver
{
public:
	~Solver(){}
	enum SolverMethod
	{
		Bissection = 1,
		Newton_Raphson = 2
	};

	Solver(SolverMethod method);
	virtual double f(double x) const = 0;
	virtual double df(double x) const;
	double Solve() const;
	void SetBoundaries(double xMin, double xMax);
	void SetStartingPoint(double x0);
	static double GetEps();
private:
	SolverMethod m_SolverMethod;
	double m_xMin, m_xMax, m_x0;
	static double _Eps;
	static double _dfEps;

	double SolveWithBissection() const;
	double SolveWithNewton() const;
};


inline Solver::Solver(SolverMethod method) :m_SolverMethod(method), m_x0(0.000001), m_xMax(100.),m_xMin(-100.){}

inline void Solver::SetBoundaries(double xMin, double xMax)
{
	m_xMin = xMin;
	m_xMax = xMax;
}

inline void Solver::SetStartingPoint(double x0)
{
	m_x0 = x0;
}

inline double Solver::GetEps()
{
	return _Eps;
}


#endif