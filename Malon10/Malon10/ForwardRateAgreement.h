#ifndef _FRA_H_INCL
#define _FRA_H_INCL

#include"InterestRateSwap.h"

class ForwardRateAgreement : public InterestRateSwap
{
public:
	ForwardRateAgreement(DateInt start,double notional, double rate, Frequency Tenor,YfConvention yfC, bool isFlReceived = true);
	~ForwardRateAgreement();
	Frequency GetTenor() const;
	

private:
	Frequency m_Tenor;
};



inline ForwardRateAgreement::~ForwardRateAgreement(){}

inline Frequency ForwardRateAgreement::GetTenor() const
{
	return m_Tenor;
}

#endif