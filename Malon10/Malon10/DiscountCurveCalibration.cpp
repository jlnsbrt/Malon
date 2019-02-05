#include"DiscountCurveCalibration.h"

void DiscountCurveCalibration::CalibrateWithSwap()
{
	if (m_swapMap.empty())
	{
		return;
	}
    RateSolver rs(Solver::Newton_Raphson);
    rs.SetRateCurve(m_RateCurve.get());
	for (swapMapIterator it = swapBegin(); it != swapEnd(); ++it)
    {
        rs.SetInstrument(it->second.get());
        rs.SetQuotedPrice(0.);
        rs.Solve();
    }
}

void DiscountCurveCalibration::CalibrateWithFRAs()
{
	if (m_FraMap.empty())
	{
		return;
	}
    RateSolver rs(Solver::Newton_Raphson);
    rs.SetRateCurve(m_RateCurve.get());
	for (fraMapIterator it = FraBegin(); it != FraEnd(); ++it)
    {
        rs.SetInstrument(it->second.get());
        rs.SetQuotedPrice(0.);
        rs.Solve();
    }
}

