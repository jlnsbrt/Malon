#include"RateCurveCalibration.h"

void RateCurveCalibration::SetIrs(const irsTuple & irs)
{
	unsigned int months = std::get<0>(irs);
	DateInt Issue = std::get<1>(irs);
	DateInt Maturity = InterestRateSwap::CalcMaturity(months, Issue);
	m_swapMap[Maturity] = std::unique_ptr<InterestRateSwap>(new InterestRateSwap(std::get<0>(irs), std::get<1>(irs), 1., std::get<2>(irs), std::get<3>(irs), std::get<4>(irs), std::get<5>(irs), std::get<6>(irs)));
}
void RateCurveCalibration::SetOis(const irsTuple & irs)
{
	unsigned int months = std::get<0>(irs);
	DateInt Issue = std::get<1>(irs);
	DateInt Maturity = InterestRateSwap::CalcMaturity(months, Issue);
	m_swapMap[Maturity] = std::unique_ptr<InterestRateSwap>(new OvernightIndexedSwap(std::get<0>(irs), std::get<1>(irs), 1., std::get<2>(irs), std::get<3>(irs), std::get<4>(irs), std::get<5>(irs), std::get<6>(irs)));
}
void RateCurveCalibration::SetTbs(const tbsTuple & tbs)
{
	unsigned int months = std::get<0>(tbs);
	DateInt Issue = std::get<1>(tbs);
	DateInt Maturity = InterestRateSwap::CalcMaturity(months, Issue);
	m_tbsMap[Maturity] = std::unique_ptr<TenorBasisSwap>(new TenorBasisSwap(std::get<0>(tbs), std::get<1>(tbs), 1., std::get<2>(tbs), 0, std::get<3>(tbs), std::get<4>(tbs), std::get<5>(tbs), std::get<6>(tbs)));
}
void RateCurveCalibration::SetDeposits(const depositsTuple & dep)
{
	DateInt issue = std::get<0>(dep);
	DateInt mat = std::get<1>(dep);
	double rate = std::get<2>(dep);
	YfConvention yfC = std::get<3>(dep);
	m_DepositMap[mat] = std::unique_ptr<Deposit>(new Deposit(issue, mat, rate, yfC));
}

void RateCurveCalibration::SetFRAs(const frasTuple & fra)
{
	DateInt issue = std::get<0>(fra);
	double rate = std::get<1>(fra);
	YfConvention yfC = std::get<2>(fra);
	Frequency ten = std::get<3>(fra);
	unsigned int months = Instrument::NbMonths(ten);
	DateInt Maturity = InterestRateSwap::CalcMaturity(months, issue);
	m_FraMap[Maturity] = std::unique_ptr<ForwardRateAgreement>(new ForwardRateAgreement(issue,1.,rate,ten,yfC));
}

void RateCurveCalibration::SetIrs(const irsTupleVec & irsVec)
{
    for (irsTupleConstIterator it = irsVec.begin(); it != irsVec.end(); ++it)
    {
		SetIrs(*it);
    }
}

void RateCurveCalibration::SetOis(const irsTupleVec & oisVec)
{
	for (irsTupleConstIterator it = oisVec.begin(); it != oisVec.end(); ++it)
	{
		SetOis(*it);
	}
}

void RateCurveCalibration::SetTbs(const tbsTupleVec & tbsVec)
{
	for (irsTupleConstIterator it = tbsVec.begin(); it != tbsVec.end(); ++it)
	{
		SetTbs(*it);
	}
}

void RateCurveCalibration::SetDeposits(const depositsTupleVec & depVec)
{
    for ( depositsTupleConstIterator it = depVec.begin(); it !=  depVec.end(); ++it)
    {
		SetDeposits(*it);
    }
}

void RateCurveCalibration::SetFRAs(const frasTupleVec & fraVec)
{
    for ( frasTupleConstIterator it = fraVec.begin(); it !=  fraVec.end(); ++it)
    {
		SetFRAs(*it);
    }
}

void RateCurveCalibration::Init()
{
    fraMapConstIterator it = FraBegin();
    if (it != FraEnd())
    {
		ThrowMessage(it->second->GetIssueDate() < m_RateCurve->GetYcStartDate(), "Invalid deposit dates");
		DateInt firstSwapMaturity(0);
		swapMapConstIterator itswap = swapBegin();
		if (itswap == swapEnd())
		{
			tbsMapConstIterator itTbs = tbsBegin();
			if (itTbs == tbsEnd())
			{
				return;
			}
			firstSwapMaturity = itTbs->second->GetMaturity();
		}
		else
		{
			firstSwapMaturity = itswap->second->GetMaturity();
		}
        for (; it != FraEnd(); ++it)
        {
            DateInt FraMaturity = it->first;
			if (FraMaturity > firstSwapMaturity)
            {
                m_FraMap.erase(FraMaturity);
            }
        }
    }
}

void RateCurveCalibration::Calibrate()
{
    Init();
    CalibrateWithDeposits();
    CalibrateWithFRAs();
    CalibrateWithSwap();
	CalibrateWithTbs();
}


void RateCurveCalibration::CalibrateWithDeposits()
{
    depositMapConstIterator it = DepBegin();
    if (it != DepEnd())
    {
        for (; it != DepEnd(); ++it)
        {
            double df = it->second->price(*m_RateCurve, m_RateCurve->GetYcStartDate());
            m_RateCurve->AddPoint(it->second->GetMaturity(), df, DfType);
        }
    }
}

double RateCurveCalibration::RateSolver::f(double x) const
{
	DateInt Maturity = m_pInst->GetMaturity();
	m_pRc->AddPoint(Maturity, x);
	return m_pInst->price(*m_pRc, m_pRc->GetYcStartDate()) - m_quotedPrice;
}
