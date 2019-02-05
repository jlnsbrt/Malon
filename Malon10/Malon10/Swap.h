#ifndef _SWAP_H_INCL
#define _SWAP_H_INCL
#include"Leg.h"
#include<memory>

class Swap : public Instrument
{
public:
	Swap(unsigned int MaturityInMonths, DateInt Issue);
	Swap(const Swap& other){}
	virtual double price(const RateCurve& rateCurveObj, DateInt calcDate);
	virtual Leg* GetLeg(Frequency tenor)  const = 0; 

protected:
	std::unique_ptr<Leg> m_ReceivedLeg;
	std::unique_ptr<Leg> m_PaidLeg;
};



#endif