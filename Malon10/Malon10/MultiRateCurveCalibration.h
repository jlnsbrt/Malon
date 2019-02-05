#ifndef _MULTIRATECURVECALIB_H_INCL
#define _MULTIRATECURVECALIB_H_INCL

#include"MultiRateCurve.h"
#include"DiscountCurveCalibration.h"
#include"LiborCurveCalibration.h"

class MultiRateCurveCalibration
{
public:
	// structor.  yfconv : year fraction convention of the calibrated yield curves , im: interpolation method of the calibrated yield curves
	MultiRateCurveCalibration(YfConvention yfconv, InterpMethod im);
	~MultiRateCurveCalibration();

	// Method to set the calibration instruments
	void SetIrs(const irsTupleVec & irsVec);
	void SetOis(const irsTupleVec & irsVec);
	void SetTbs(const tbsTupleVec & tbsVec);
	void SetDeposits(const depositsTupleVec & depVec);
	void SetFRAs(const frasTupleVec& fraVec);
	// to The yc start date of the calibratted cuve
	void SetCalcDate(DateInt calcDate);

	//Method that makes the calibration
	void Calibrate();

	//To get the calibrated multi rate curve
	MultiRateCurve* GetMultiRateCurve();


private:
	MultiRateCurveCalibration(const MultiRateCurveCalibration&);
	void CreateRateCurveCalibrations();
	bool CreateLiborCurveCalibrationsFromTbs();

	std::unique_ptr<MultiRateCurve> m_MultiRateCurve;
	std::unique_ptr<DiscountCurveCalibration> m_DiscountCurveCalibration;
	std::map<Frequency, std::unique_ptr<LiborCurveCalibration> > m_LiborCurveCalibrationMap;
	YfConvention m_YfC;
	InterpMethod m_im;
	irsTupleVec m_irsTupleVec;
	irsTupleVec m_oisTupleVec;
	tbsTupleVec m_tbsTupleVec;
	frasTupleVec m_frasTupleVec;
	depositsTupleVec m_depositsTupleVec;
	DateInt m_ycStartDate;
};


/////////////////// inline methods ///////////////////////////

inline MultiRateCurveCalibration::MultiRateCurveCalibration(YfConvention yfconv, InterpMethod im) :m_YfC(yfconv), m_im(im)
{
}

inline MultiRateCurveCalibration::~MultiRateCurveCalibration()
{
}

inline void MultiRateCurveCalibration::SetIrs(const irsTupleVec & irsVec)
{
	m_irsTupleVec = irsVec;
}

inline void MultiRateCurveCalibration::SetOis(const irsTupleVec & oisVec)
{
	m_oisTupleVec = oisVec;
}

inline void MultiRateCurveCalibration::SetTbs(const tbsTupleVec & tbsVec)
{
	m_tbsTupleVec = tbsVec;
}

inline void MultiRateCurveCalibration::SetDeposits(const depositsTupleVec & depVec)
{
	m_depositsTupleVec = depVec;
}

inline void MultiRateCurveCalibration::SetFRAs(const frasTupleVec& fraVec)
{
	m_frasTupleVec = fraVec;
}

inline void MultiRateCurveCalibration::SetCalcDate(DateInt calcDate)
{
	m_ycStartDate = calcDate;
}

inline  MultiRateCurve* MultiRateCurveCalibration::GetMultiRateCurve()
{
	return m_MultiRateCurve.get();
}
#endif