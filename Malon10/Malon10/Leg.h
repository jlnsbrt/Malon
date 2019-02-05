#ifndef _LEG_H_INCL
#define _LEG_H_INCL

#include"Instrument.h"
#include<memory>
#include<map>
#include"Schedule.h"

class Leg : public Instrument
{
public:
	Leg(DateInt Maturity,  DateInt Issue, double Notional, Frequency freq, YfConvention cpnYfConv, bool capitalFlow);
	Leg(const Leg& other);
	~Leg();
	virtual double price(const RateCurve& rateCurveObj, DateInt calcDate);
	virtual void SetCurrentLibor(double) = 0; 
	virtual void SetLiborCurve(RateCurve* rC) = 0; 
	Frequency GetTenor() const;
	virtual void CalcSchedule();
	Schedule* GetInterestSchedule();
	Schedule* GetCapitalSchedule();
	bool WithCapital() const;
	double GetRemainingCapital(DateInt iDate) const;
protected:


	std::unique_ptr<Schedule> m_pInterestSchedule;
	std::unique_ptr<Schedule> m_pCapitalSchedule;
	std::map<DateInt, double> m_AmortMap;
	Frequency m_freq;
	YfConvention m_conv;
	bool m_capitalFlow;
};


inline Leg::~Leg(){}
inline Frequency Leg::GetTenor() const
{
	return m_freq;
}

inline double Leg::GetRemainingCapital(DateInt iDate) const
{
 return m_pCapitalSchedule->GetRemainingCapital(iDate);
}

inline Schedule* Leg::GetInterestSchedule()
{
	return m_pInterestSchedule.get();
}
inline Schedule* Leg::GetCapitalSchedule()
{
	return m_pCapitalSchedule.get();
}

inline bool Leg::WithCapital() const
{
	return m_capitalFlow;
}

#endif