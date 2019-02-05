#ifndef _TENORBASIS_H_INCL
#define _TENORBASIS_H_INCL

#include"FloatingRateNote.h"
#include"Swap.h"

class TenorBasisSwap : public Swap
{
public:
	TenorBasisSwap(unsigned int MaturityInMonths, DateInt Issue, double notional, double receivedSpread, double paidSpread, Frequency receivedFreq, Frequency paidFreq, YfConvention receivedconv, YfConvention paidconv);
	TenorBasisSwap(const TenorBasisSwap& other);
	~TenorBasisSwap();
	void SetReceivedCurrentLibor(double currentLibor);
	void SetPaidCurrentLibor(double currentLibor);
	virtual void SetReceivedLiborCurve(RateCurve * lC);
	virtual void SetPaidLiborCurve(RateCurve * lC);
	virtual Leg* GetLeg(Frequency tenor) const;
};

inline TenorBasisSwap::~TenorBasisSwap(){}

#endif