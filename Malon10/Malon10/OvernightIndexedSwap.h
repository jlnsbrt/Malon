#ifndef _OIS_H_INCL
#define _OISS_H_INCL

#include"InterestRateSwap.h"

class OvernightIndexedSwap : public InterestRateSwap
{
public:
	OvernightIndexedSwap(unsigned int MaturityInMonths, DateInt Issue, double notional, double fixedRate, Frequency fixedFreq, Frequency floatFreq, YfConvention fixedconv, YfConvention floatconv, bool isFlReceived = true);
	OvernightIndexedSwap(const OvernightIndexedSwap & other);
	~OvernightIndexedSwap();
	virtual void SetLiborCurve(const RateCurve & lC);
};


inline OvernightIndexedSwap::OvernightIndexedSwap(unsigned int MaturityInMonths, DateInt Issue, double notional, double fixedRate, Frequency fixedFreq, Frequency floatFreq, YfConvention fixedconv, YfConvention floatconv, bool isFlReceived) :
InterestRateSwap(MaturityInMonths, Issue, notional, fixedRate, floatFreq, Daily, fixedconv, floatconv, isFlReceived){}

inline OvernightIndexedSwap::OvernightIndexedSwap(const OvernightIndexedSwap & other) : InterestRateSwap(other){}

inline OvernightIndexedSwap::~OvernightIndexedSwap() {}

inline void OvernightIndexedSwap::SetLiborCurve(const RateCurve & lC){}
#endif