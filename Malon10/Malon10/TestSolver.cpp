#include"Tests.h"
#include"Solver.h"


class  ExpTest : public Solver
{
public:
	ExpTest(SolverMethod s) :Solver(s){}
	~ExpTest(){}
	virtual double f(double x) const
	{
		return std::exp(x) - 3;
	}
};


bool TestSolver()
{
	bool iscorrect(true);
	double sol = std::log(3.);
	double solBis = ExpTest(Solver::Bissection).Solve();
	double solNR = ExpTest(Solver::Newton_Raphson).Solve();
	iscorrect = iscorrect && isCorrect(sol, solBis, Solver::GetEps() );
	iscorrect = iscorrect && isCorrect(sol, solNR, Solver::GetEps());
	return iscorrect;
}


