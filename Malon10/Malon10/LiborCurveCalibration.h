#ifndef _LIBORCURVECALIB_H_INCL
#define _LIBORCURVECALIB_H_INCL

#include"RateCurveCalibration.h"

// class that calibrates a libor curve (in the multicurve context)
class LiborCurveCalibration : public RateCurveCalibration
{
public:
    LiborCurveCalibration(YfConvention yfconv, InterpMethod im, Frequency tenor);
    ~LiborCurveCalibration();
	 
	//  Set a libor curve ( the tenor of this libor and the tenor of the libor curve we wish to calibrate must be different)
	void SetLiborCurve(RateCurve* lC);
	//  Set the discount curve
	void SetDiscountCurve(RateCurve* dC);

	void SetOtherTbsTenor(Frequency tenor);
	Frequency GetOtherTbsTenor() const;
private:
    virtual void CalibrateWithSwap();
	virtual void CalibrateWithFRAs();
	virtual void CalibrateWithTbs();
	RateCurve* m_DiscountRateCurve;
	// Solver tools
	class LiborSolver : public RateSolver
	{
	public:
		LiborSolver(SolverMethod meth); 
		void SetLiborCurve(RateCurve* plC);
		virtual double f(double x) const;
	private:
		RateCurve* m_pLiborCurve;
	};

	Frequency m_OtherTenor;
};

/////////////////// inline methods ///////////////////////////

inline LiborCurveCalibration::LiborCurveCalibration(YfConvention yfconv, InterpMethod im, Frequency tenor) : RateCurveCalibration(yfconv, im, tenor) , m_OtherTenor(None) {}
inline LiborCurveCalibration::~LiborCurveCalibration() {}

inline void LiborCurveCalibration::SetDiscountCurve(RateCurve* dC)
{
	m_DiscountRateCurve = dC;
}

inline LiborCurveCalibration::LiborSolver::LiborSolver(SolverMethod meth) : RateSolver(meth)  {}

inline void LiborCurveCalibration::LiborSolver::SetLiborCurve(RateCurve* plC)
{
	m_pLiborCurve = plC;
}

inline void LiborCurveCalibration::SetOtherTbsTenor(Frequency tenor)
{
	m_OtherTenor = tenor;
}

inline Frequency LiborCurveCalibration::GetOtherTbsTenor() const
{
	return m_OtherTenor;
}

#endif
