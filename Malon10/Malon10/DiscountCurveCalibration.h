#ifndef _DISCOUNTCURVECALIB_H_INCL
#define _DISCOUNTCURVECALIB_H_INCL

#include"RateCurveCalibration.h"

// class that calibrates a discount curve
class DiscountCurveCalibration : public RateCurveCalibration
{
public:
    DiscountCurveCalibration(YfConvention yfconv, InterpMethod im, Frequency tenor);
    ~DiscountCurveCalibration();

private:
	virtual void CalibrateWithSwap(); 
	virtual void CalibrateWithTbs();
	virtual void CalibrateWithFRAs();
};

/////////////////// inline methods ///////////////////////////

inline DiscountCurveCalibration::DiscountCurveCalibration(YfConvention yfconv, InterpMethod im, Frequency tenor) : RateCurveCalibration(yfconv, im, tenor) {}
inline DiscountCurveCalibration::~DiscountCurveCalibration() {}
inline void DiscountCurveCalibration::CalibrateWithTbs(){}

#endif