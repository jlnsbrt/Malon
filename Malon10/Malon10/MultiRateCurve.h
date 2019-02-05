#ifndef _MULTIRATECURVE_H_INCL
#define _MULTIRATECURVE_H_INCL


#include"RateCurve.h"
#include<string>
#include<memory>

class MultiRateCurve
{
public:
	MultiRateCurve();
	~MultiRateCurve();
	MultiRateCurve(const MultiRateCurve& other);
	//The currency of the curve
	const std::string& GetCurrency();
	// The discount curve (collateralized in its own currency)
	RateCurve* GetDiscountCurve();
	// The libor curve 
	RateCurve* GetLiborCurve(Frequency tenor);
	double CalcSurvivalProbability(Frequency tenor,DateInt fromDate, DateInt toDate);


	void SetDiscountCurve(RateCurve* dc);
	void SetLiborCurve(RateCurve* dc);

private:
	std::string m_Currency;
	std::unique_ptr<RateCurve> m_DiscountCurve;
	std::map<Frequency, std::unique_ptr<RateCurve> > m_LiborCurveMap;

};

/////////////////// inline methods ///////////////////////////

inline MultiRateCurve::MultiRateCurve() : m_Currency(""){}

inline MultiRateCurve::~MultiRateCurve(){}

inline const std::string& MultiRateCurve::GetCurrency()
{
	return m_Currency;
}

inline RateCurve* MultiRateCurve::GetDiscountCurve()
{
	return m_DiscountCurve.get();
}

inline void MultiRateCurve::SetDiscountCurve(RateCurve* dc)
{
	m_DiscountCurve.reset(new RateCurve(*dc));
}


#endif