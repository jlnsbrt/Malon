#include"TenorBasisSwap.h"

TenorBasisSwap::TenorBasisSwap(unsigned int MaturityInMonths, DateInt Issue, double notional, double receivedSpread, double paidSpread, Frequency receivedFreq, Frequency paidFreq, YfConvention receivedconv, YfConvention paidconv) :Swap(MaturityInMonths, Issue)
{
	m_PaidLeg.reset(new FloatingRateNote(m_Maturity, Issue, notional, paidSpread, paidFreq, paidconv, false));
	m_ReceivedLeg.reset(new FloatingRateNote(m_Maturity, Issue, notional, receivedSpread, receivedFreq, receivedconv, false));
}

TenorBasisSwap::TenorBasisSwap(const TenorBasisSwap& other) :Swap(other)
{
	m_PaidLeg.reset(new FloatingRateNote(*dynamic_cast<FloatingRateNote*>(other.m_PaidLeg.get())));
	m_ReceivedLeg.reset(new FloatingRateNote(*dynamic_cast<FloatingRateNote*>(other.m_ReceivedLeg.get())));
}

void TenorBasisSwap::SetReceivedCurrentLibor(double currentLibor)
{
	ThrowMessage(m_ReceivedLeg == NULL, "Received Leg not set");
	m_ReceivedLeg->SetCurrentLibor(currentLibor);
}

void TenorBasisSwap::SetPaidCurrentLibor(double currentLibor)
{
	ThrowMessage(m_PaidLeg == NULL, "Paid Leg not set");
	m_PaidLeg->SetCurrentLibor(currentLibor);
}

void TenorBasisSwap::SetReceivedLiborCurve(RateCurve * lC)
{
	ThrowMessage(m_ReceivedLeg == NULL, "Float Leg not set");
	m_ReceivedLeg->SetLiborCurve(lC);
}

void TenorBasisSwap::SetPaidLiborCurve(RateCurve * lC)
{
	ThrowMessage(m_PaidLeg == NULL, "Float Leg not set");
	m_PaidLeg->SetLiborCurve(lC);
}

Leg* TenorBasisSwap::GetLeg(Frequency tenor) const
{
	ThrowMessage(m_ReceivedLeg == NULL, "Float Leg not set");
	ThrowMessage(m_PaidLeg == NULL, "Float Leg not set");
	ThrowMessage(m_ReceivedLeg->GetTenor() == m_PaidLeg->GetTenor(), "Float Leg not set");
	if (m_ReceivedLeg->GetTenor() == tenor)
	{
		return m_ReceivedLeg.get();
	}
	if (m_PaidLeg->GetTenor() == tenor)
	{
		return m_PaidLeg.get();
	}
	return NULL;
}