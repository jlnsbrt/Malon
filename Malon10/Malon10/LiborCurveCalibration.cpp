#include"LiborCurveCalibration.h"

void LiborCurveCalibration::SetLiborCurve(RateCurve* lC)
{
	Frequency tenor = lC->GetTenor();
	//ThrowMessage(tenor == m_Tenor, "You cannot set that Libor");
	for (swapMapIterator it = swapBegin(); it != swapEnd(); ++it)
	{
		InterestRateSwap* pSwap = it->second.get();
		ThrowMessage(NULL == pSwap, "Irs null pointer");
		Leg* pLeg = pSwap->GetLeg(tenor);
		if (NULL != pLeg)
		{
			pLeg->SetLiborCurve(lC);
		}
	}
	for (tbsMapIterator it = tbsBegin(); it != tbsEnd(); ++it)
	{
		TenorBasisSwap* pTbs = it->second.get();
		ThrowMessage(NULL == pTbs, "Tbs null pointer");
		Leg* pLeg = pTbs->GetLeg(tenor);
		if (NULL != pLeg)
		{
			pLeg->SetLiborCurve(lC);
		}
	}
	for (fraMapIterator it = FraBegin(); it != FraEnd(); ++it)
	{
		ForwardRateAgreement* pFra = it->second.get();
		ThrowMessage(NULL == pFra, "Fra null pointer");
		pFra->SetLiborCurve(lC);
	}
}

void LiborCurveCalibration::CalibrateWithSwap()
{
	if (m_swapMap.empty())
	{
		return;
	}
	LiborSolver rs(Solver::Newton_Raphson);
	rs.SetRateCurve(m_DiscountRateCurve);
	rs.SetLiborCurve(m_RateCurve.get());
	SetLiborCurve(m_RateCurve.get());
	for (swapMapIterator it = swapBegin(); it != swapEnd(); ++it)
	{
		rs.SetInstrument(it->second.get());
		rs.SetQuotedPrice(0.);
		rs.Solve();
	}
}

void LiborCurveCalibration::CalibrateWithFRAs()
{
	if (m_FraMap.empty())
	{
		return;
	}
	LiborSolver rs(Solver::Newton_Raphson);
	rs.SetRateCurve(m_DiscountRateCurve);
	rs.SetLiborCurve(m_RateCurve.get());
	SetLiborCurve(m_RateCurve.get());
	for (fraMapIterator it = FraBegin(); it != FraEnd(); ++it)
	{
		rs.SetInstrument(it->second.get());
		rs.SetQuotedPrice(0.);
		rs.Solve();
	}
}

void LiborCurveCalibration::CalibrateWithTbs()
{
	if (!m_swapMap.empty() || m_tbsMap.empty() )
	{
		return;
	}
	LiborSolver rs(Solver::Newton_Raphson);
	rs.SetRateCurve(m_DiscountRateCurve);
	rs.SetLiborCurve(m_RateCurve.get());
	SetLiborCurve(m_RateCurve.get());
	for (tbsMapIterator it = tbsBegin(); it != tbsEnd(); ++it)
	{
		rs.SetInstrument(it->second.get());
		rs.SetQuotedPrice(0.);
		rs.Solve();
	}
}

double LiborCurveCalibration::LiborSolver::f(double x) const
{
	DateInt Maturity = m_pInst->GetMaturity();
	m_pLiborCurve->AddPoint(Maturity, x);
	return m_pInst->price(*m_pRc, m_pRc->GetYcStartDate()) - m_quotedPrice;
}



