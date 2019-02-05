#include"InterestRateSwap.h"


InterestRateSwap::InterestRateSwap(unsigned int MaturityInMonths, DateInt Issue, double notional, double fixedRate, Frequency fixedFreq, Frequency floatFreq, YfConvention fixedconv, YfConvention floatconv, bool isFlReceived) :m_isFlRec(isFlReceived), Swap(MaturityInMonths,Issue)
{
	if (m_isFlRec)
	{
		m_PaidLeg.reset(new FixedRateBond(m_Maturity, Issue, notional, fixedRate, fixedFreq, fixedconv, false));
		m_ReceivedLeg.reset(new FloatingRateNote(m_Maturity, Issue, notional, 0., floatFreq, floatconv, false));
	}
	else
	{
		m_ReceivedLeg.reset(new FixedRateBond(m_Maturity, Issue, notional, fixedRate, fixedFreq, fixedconv, false));
		m_PaidLeg.reset(new FloatingRateNote(m_Maturity, Issue, notional, 0., floatFreq, floatconv, false));
	}
}

InterestRateSwap::InterestRateSwap(const InterestRateSwap& other) :m_isFlRec(other.m_isFlRec), Swap(other)
{
	if (m_isFlRec)
	{
		if (dynamic_cast<FloatingRateNote*>(m_ReceivedLeg.get()))
		{
			m_ReceivedLeg.reset(new FloatingRateNote(*dynamic_cast<FloatingRateNote*>(m_ReceivedLeg.get())));
		}
		if (dynamic_cast<FixedRateBond*>(m_PaidLeg.get()))
		{
			m_PaidLeg.reset(new FixedRateBond(*dynamic_cast<FixedRateBond*>(m_PaidLeg.get())));
		}
	}
	else 
	{
		if (dynamic_cast<FloatingRateNote*>(m_PaidLeg.get()))
		{
			m_PaidLeg.reset(new FloatingRateNote(*dynamic_cast<FloatingRateNote*>(m_PaidLeg.get())));
		}
		if (dynamic_cast<FixedRateBond*>(m_ReceivedLeg.get()))
		{
			m_ReceivedLeg.reset(new FixedRateBond(*dynamic_cast<FixedRateBond*>(m_ReceivedLeg.get())));
		}
	}
}

FixedRateBond* InterestRateSwap::GetFixedLeg() const
{
	if (m_isFlRec)
	{
		return dynamic_cast<FixedRateBond*>(m_PaidLeg.get());
	}
	else
	{
		return dynamic_cast<FixedRateBond*>(m_ReceivedLeg.get());
	}	
}

FloatingRateNote* InterestRateSwap::GetFloatLeg() const
{
	if (m_isFlRec)
	{
		return dynamic_cast<FloatingRateNote*>(m_ReceivedLeg.get());
	}
	else
	{
		return dynamic_cast<FloatingRateNote*>(m_PaidLeg.get());
	}
}

void InterestRateSwap::SetCurrentLibor(double currentLibor)
{
	FloatingRateNote* pFlLeg = GetFloatLeg();
	ThrowMessage(pFlLeg == NULL, "Float Leg not set");
	pFlLeg->SetCurrentLibor(currentLibor);
}

void InterestRateSwap::SetLiborCurve(RateCurve* lC)
{
	FloatingRateNote* pFlLeg = GetFloatLeg();
	ThrowMessage(pFlLeg == NULL, "Float Leg not set");
	pFlLeg->SetLiborCurve(lC);
}

Leg* InterestRateSwap::GetLeg(Frequency tenor) const  
{
	FloatingRateNote* pFlLeg = GetFloatLeg();
	ThrowMessage(pFlLeg == NULL, "Float Leg not set");
	if (pFlLeg->GetTenor() == tenor)
	{
			return pFlLeg;
	}
	return NULL;
}

double InterestRateSwap::GetFixedRate() const
{
	FixedRateBond* pfixedLeg = GetFixedLeg();
	ThrowMessage(pfixedLeg == NULL, "Fixed Leg not set");
	return pfixedLeg->GetFixedRate();
}

double InterestRateSwap::Annuity(const RateCurve& rateCurveObj, DateInt calcDate)
{
	FixedRateBond* pfixedLeg = GetFixedLeg();
	ThrowMessage(pfixedLeg == NULL, "Fixed Leg not set");
	double fixedRate = pfixedLeg->GetFixedRate();
	pfixedLeg->SetFixedRate(1.);
	double annuity = pfixedLeg->price(rateCurveObj,calcDate);
	pfixedLeg->SetFixedRate(fixedRate);
	return annuity;
}

double InterestRateSwap::ParRate(const RateCurve& rateCurveObj, DateInt calcDate)
{
	double annuity = Annuity(rateCurveObj,calcDate);
	ThrowMessage(annuity == 0, "Annuity is zero");
	FloatingRateNote* pFlLeg = GetFloatLeg();
	ThrowMessage(pFlLeg == NULL, "Float Leg not set");
	return pFlLeg->price(rateCurveObj,calcDate) / annuity;
}
