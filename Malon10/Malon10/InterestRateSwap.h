#ifndef _IRS_H_INCL
#define _IRS_H_INCL

#include"FixedRateBond.h"
#include"FloatingRateNote.h"
#include"Swap.h"

class InterestRateSwap : public Swap
{
public:
    InterestRateSwap(unsigned int MaturityInMonths, DateInt Issue, double notional, double fixedRate, Frequency fixedFreq, Frequency floatFreq, YfConvention fixedconv, YfConvention floatconv, bool isFlReceived = true);
    InterestRateSwap(const InterestRateSwap & other);
    ~InterestRateSwap();
    void SetCurrentLibor(double currentLibor);
    virtual void SetLiborCurve(RateCurve * lC);
	virtual Leg* GetLeg(Frequency tenor) const;
	FixedRateBond* GetFixedLeg() const;
	FloatingRateNote* GetFloatLeg() const;
	bool IsFlReceived() const;
	double GetFixedRate() const;

	double Annuity(const RateCurve& rateCurveObj, DateInt calcDate);
	double ParRate(const RateCurve& rateCurveObj, DateInt calcDate);
private:
    bool m_isFlRec;
};

inline InterestRateSwap::~InterestRateSwap() {}



inline bool InterestRateSwap::IsFlReceived() const
{
	return m_isFlRec;
}

#endif
