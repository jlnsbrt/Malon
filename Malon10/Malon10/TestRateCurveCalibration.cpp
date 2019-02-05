#include"Tests.h"
#include"MultiRateCurveCalibration.h"

bool TestDiscountCurveCalibration()
{
    bool iscorr(true);

    DateInt calcDate(43022);
    //Swaps Array
    irsTupleVec vecSwaps;
    vecSwaps.push_back(irsTuple(6, 43024, 0.0051, SemiAnnual, Quaterly, Act365, Act365));
    vecSwaps.push_back(irsTuple(12, 43024, 0.0092, SemiAnnual, Quaterly, Act365, Act365));
    vecSwaps.push_back(irsTuple(24, 43024, 0.0101, SemiAnnual, Quaterly, Act365, Act365));
    vecSwaps.push_back(irsTuple(36, 43024, 0.0152, SemiAnnual, Quaterly, Act365, Act365));
    vecSwaps.push_back(irsTuple(60, 43024, 0.0181, SemiAnnual, Quaterly, Act365, Act365));
    vecSwaps.push_back(irsTuple(120, 43024, 0.0224, SemiAnnual, Quaterly, Act365, Act365));

    depositsTupleVec vecDeps;
    vecDeps.push_back(depositsTuple(43022, 43023, 0.0012, Act365));
    vecDeps.push_back(depositsTuple(43023, 43024, 0.0015, Act365));

    DiscountCurveCalibration rcc(_30360, LinearInterpolation, Quaterly);
    rcc.SetIrs(vecSwaps);
    rcc.SetDeposits(vecDeps);
    rcc.SetCalcDate(calcDate);
    rcc.Calibrate();

    const RateCurve * rc = rcc.GetRateCurve();

    std::vector < std::unique_ptr<InterestRateSwap >> irsVec;
    irsVec.resize(6);
    irsVec[0].reset(new InterestRateSwap(6, 43024, 1, 0.0051, SemiAnnual, Quaterly, Act365, Act365));
    irsVec[1].reset(new InterestRateSwap(12, 43024, 1, 0.0092, SemiAnnual, Quaterly, Act365, Act365));
    irsVec[2].reset(new InterestRateSwap(24, 43024, 1, 0.0101, SemiAnnual, Quaterly, Act365, Act365));
    irsVec[3].reset(new InterestRateSwap(36, 43024, 1, 0.0152, SemiAnnual, Quaterly, Act365, Act365));
    irsVec[4].reset(new InterestRateSwap(60, 43024, 1, 0.0181, SemiAnnual, Quaterly, Act365, Act365));
    irsVec[5].reset(new InterestRateSwap(120, 43024, 1, 0.0224, SemiAnnual, Quaterly, Act365, Act365));

    for (std::vector < std::unique_ptr<InterestRateSwap >>::iterator it = irsVec.begin(); it != irsVec.end(); ++it)
    {
        double npv = it->get()->price(*rc, calcDate);
        iscorr = iscorr && isCorrect(npv, 0., 1.E-6);
    }

    return iscorr;
}

bool TestLiborCurveCalibration()
{
	bool iscorr(true);
	DateInt calcDate(43022);
	//Dc calib
	//Swaps Array
	irsTupleVec vecOIS;
	vecOIS.push_back(irsTuple(6, 43024, 0.0051, SemiAnnual, Quaterly, Act365, Act365));
	vecOIS.push_back(irsTuple(12, 43024, 0.0092, SemiAnnual, Quaterly, Act365, Act365));
	vecOIS.push_back(irsTuple(24, 43024, 0.0101, SemiAnnual, Quaterly, Act365, Act365));
	vecOIS.push_back(irsTuple(36, 43024, 0.0152, SemiAnnual, Quaterly, Act365, Act365));
	vecOIS.push_back(irsTuple(60, 43024, 0.0181, SemiAnnual, Quaterly, Act365, Act365));
	vecOIS.push_back(irsTuple(120, 43024, 0.0224, SemiAnnual, Quaterly, Act365, Act365));

	depositsTupleVec vecDeps;
	vecDeps.push_back(depositsTuple(43022, 43023, 0.0012, Act365));
	vecDeps.push_back(depositsTuple(43023, 43024, 0.0015, Act365));

	DiscountCurveCalibration rcc(_30360, LinearInterpolation, Daily);
	rcc.SetOis(vecOIS);
	rcc.SetDeposits(vecDeps);
	rcc.SetCalcDate(calcDate);
	rcc.Calibrate();

	RateCurve * rc = rcc.GetRateCurve();

	std::vector < std::unique_ptr<Swap >> oisVec;
	oisVec.resize(6);
	oisVec[0].reset(new OvernightIndexedSwap(6, 43024, 1, 0.0051, SemiAnnual, Quaterly, Act365, Act365));
	oisVec[1].reset(new OvernightIndexedSwap(12, 43024, 1, 0.0092, SemiAnnual, Quaterly, Act365, Act365));
	oisVec[2].reset(new OvernightIndexedSwap(24, 43024, 1, 0.0101, SemiAnnual, Quaterly, Act365, Act365));
	oisVec[3].reset(new OvernightIndexedSwap(36, 43024, 1, 0.0152, SemiAnnual, Quaterly, Act365, Act365));
	oisVec[4].reset(new OvernightIndexedSwap(60, 43024, 1, 0.0181, SemiAnnual, Quaterly, Act365, Act365));
	oisVec[5].reset(new OvernightIndexedSwap(120, 43024, 1, 0.0224, SemiAnnual, Quaterly, Act365, Act365));

	for (std::vector < std::unique_ptr<Swap >>::iterator it = oisVec.begin(); it != oisVec.end(); ++it)
	{
		double npv = it->get()->price(*rc, calcDate);
		iscorr = iscorr && isCorrect(npv, 0., 1.E-6);
	}

	//  Libor 3M calib
	irsTupleVec vecIRS;
	vecIRS.push_back(irsTuple(6, 43024, 0.0061, SemiAnnual, Quaterly, Act365, Act365));
	vecIRS.push_back(irsTuple(12, 43024, 0.0123, SemiAnnual, Quaterly, Act365, Act365));
	vecIRS.push_back(irsTuple(24, 43024, 0.0151, SemiAnnual, Quaterly, Act365, Act365));
	vecIRS.push_back(irsTuple(36, 43024, 0.02632, SemiAnnual, Quaterly, Act365, Act365));
	vecIRS.push_back(irsTuple(60, 43024, 0.0301, SemiAnnual, Quaterly, Act365, Act365));
	vecIRS.push_back(irsTuple(120, 43024, 0.0389, SemiAnnual, Quaterly, Act365, Act365));

	depositsTupleVec vec3MDeps;
	vec3MDeps.push_back(depositsTuple(43022, 43023, 0.0012, Act365));
	vec3MDeps.push_back(depositsTuple(43023, 43024, 0.0015, Act365));

	LiborCurveCalibration lcc3M(Act36525, LinearInterpolation, Quaterly);
	lcc3M.SetDiscountCurve(rc);
	lcc3M.SetIrs(vecIRS);
	lcc3M.SetDeposits(vec3MDeps);
	lcc3M.SetCalcDate(calcDate);
	lcc3M.Calibrate();
	RateCurve * lc3M = lcc3M.GetRateCurve();


	std::vector < std::unique_ptr<InterestRateSwap >> irsVec;
	irsVec.resize(6);
	irsVec[0].reset(new InterestRateSwap(6, 43024, 1, 0.0061, SemiAnnual, Quaterly, Act365, Act365));
	irsVec[1].reset(new InterestRateSwap(12, 43024, 1, 0.0123, SemiAnnual, Quaterly, Act365, Act365));
	irsVec[2].reset(new InterestRateSwap(24, 43024, 1, 0.0151, SemiAnnual, Quaterly, Act365, Act365));
	irsVec[3].reset(new InterestRateSwap(36, 43024, 1, 0.02632, SemiAnnual, Quaterly, Act365, Act365));
	irsVec[4].reset(new InterestRateSwap(60, 43024, 1, 0.0301, SemiAnnual, Quaterly, Act365, Act365));
	irsVec[5].reset(new InterestRateSwap(120, 43024, 1, 0.0389, SemiAnnual, Quaterly, Act365, Act365));

	for (std::vector < std::unique_ptr<InterestRateSwap >>::iterator it = irsVec.begin(); it != irsVec.end(); ++it)
	{
		it->get()->SetLiborCurve(lc3M);
		double npv = it->get()->price(*rc, calcDate);
		iscorr = iscorr && isCorrect(npv, 0., 1.E-6);
	}

	// Libor 6M calibration

	tbsTupleVec vecTBS;
	vecTBS.push_back(tbsTuple(6, 43024, 0.0005, Quaterly, SemiAnnual, Act365, Act365));
	vecTBS.push_back(tbsTuple(12, 43024, 0.0011, Quaterly, SemiAnnual, Act365, Act365));
	vecTBS.push_back(tbsTuple(24, 43024, 0.0015, Quaterly, SemiAnnual, Act365, Act365));
	vecTBS.push_back(tbsTuple(36, 43024, 0.0026, Quaterly, SemiAnnual, Act365, Act365));
	vecTBS.push_back(tbsTuple(60, 43024, 0.0042, Quaterly, SemiAnnual, Act365, Act365));
	vecTBS.push_back(tbsTuple(120, 43024, 0.0063, Quaterly, SemiAnnual, Act365, Act365));

	depositsTupleVec vec6MDeps;
	vec6MDeps.push_back(depositsTuple(43022, 43023, 0.0012, Act365));
	vec6MDeps.push_back(depositsTuple(43023, 43024, 0.0015, Act365));

	LiborCurveCalibration lcc6M(Act36525, LinearInterpolation, SemiAnnual);
	lcc6M.SetDiscountCurve(rc);
	lcc6M.SetTbs(vecTBS);
	lcc6M.SetDeposits(vec3MDeps);
	lcc6M.SetCalcDate(calcDate);
	lcc6M.SetLiborCurve(lc3M);
	lcc6M.Calibrate();
	RateCurve * lc6M = lcc6M.GetRateCurve();

	std::vector < std::unique_ptr<TenorBasisSwap >> tbsVec;
	tbsVec.resize(6);
	tbsVec[0].reset(new TenorBasisSwap(6, 43024, 1, 0.0005,0., Quaterly, SemiAnnual, Act365, Act365));
	tbsVec[1].reset(new TenorBasisSwap(12, 43024, 1, 0.0011, 0., Quaterly, SemiAnnual, Act365, Act365));
	tbsVec[2].reset(new TenorBasisSwap(24, 43024, 1, 0.0015, 0., Quaterly, SemiAnnual, Act365, Act365));
	tbsVec[3].reset(new TenorBasisSwap(36, 43024, 1, 0.0026, 0., Quaterly, SemiAnnual, Act365, Act365));
	tbsVec[4].reset(new TenorBasisSwap(60, 43024, 1, 0.0042, 0., Quaterly, SemiAnnual, Act365, Act365));
	tbsVec[5].reset(new TenorBasisSwap(120, 43024, 1, 0.0063, 0., Quaterly, SemiAnnual, Act365, Act365));

	for (std::vector < std::unique_ptr<TenorBasisSwap >>::iterator it = tbsVec.begin(); it != tbsVec.end(); ++it)
	{
		it->get()->SetPaidLiborCurve(lc6M);
		it->get()->SetReceivedLiborCurve(lc3M);
		double npv = it->get()->price(*rc, calcDate);
		iscorr = iscorr && isCorrect(npv, 0., 1.E-8);
	}

	return iscorr;
}


bool TestMultiCurveCalibration()
{
	bool iscorr(true);

	DateInt calcDate(43022);

	//Instruments Array
	//OIS
	irsTupleVec vecOIS;
	vecOIS.push_back(irsTuple(3, 43024, 0.0021, Monthly, Quaterly, Act365, Act365));
	vecOIS.push_back(irsTuple(6, 43024, 0.0051, Quaterly, Quaterly, Act365, Act365));
	vecOIS.push_back(irsTuple(12, 43024, 0.0092, Quaterly, Quaterly, Act365, Act365));
	vecOIS.push_back(irsTuple(24, 43024, 0.0101, Quaterly, Quaterly, Act365, Act365));
	vecOIS.push_back(irsTuple(36, 43024, 0.0152, Quaterly, Quaterly, Act365, Act365));
	vecOIS.push_back(irsTuple(60, 43024, 0.0181, Quaterly, Quaterly, Act365, Act365));
	vecOIS.push_back(irsTuple(120, 43024, 0.0224, Quaterly, Quaterly, Act365, Act365));

	//deposits
	depositsTupleVec vecDeps;
	vecDeps.push_back(depositsTuple(43022, 43023, 0.0012, Act365));
	vecDeps.push_back(depositsTuple(43023, 43024, 0.0015, Act365));

	//FRA
	frasTupleVec vecFRAs;
	// 3M
	vecFRAs.push_back(frasTuple(43085,0.0035,Act365,Quaterly));
	vecFRAs.push_back(frasTuple(43175,0.0045,Act365,Quaterly));
	//6M
	vecFRAs.push_back(frasTuple(43085,0.0043,Act365,SemiAnnual));
	//IRS
	irsTupleVec vecIRS;
	// IRS 1M
	vecIRS.push_back(irsTuple(6, 43024, 0.0055, Quaterly, Monthly, Act365, Act365));
	vecIRS.push_back(irsTuple(12, 43024, 0.0102, Quaterly, Monthly, Act365, Act365));
	vecIRS.push_back(irsTuple(24, 43024, 0.0124, Quaterly, Monthly, Act365, Act365));
	vecIRS.push_back(irsTuple(36, 43024, 0.0263, Quaterly, Monthly, Act365, Act365));
	vecIRS.push_back(irsTuple(60, 43024, 0.0295, Quaterly, Monthly, Act365, Act365));
	// IRS 3M
	vecIRS.push_back(irsTuple(12, 43024, 0.0123, SemiAnnual, Quaterly, Act365, Act365));
	vecIRS.push_back(irsTuple(24, 43024, 0.0151, SemiAnnual, Quaterly, Act365, Act365));
	vecIRS.push_back(irsTuple(36, 43024, 0.02632, SemiAnnual, Quaterly, Act365, Act365));
	vecIRS.push_back(irsTuple(60, 43024, 0.0301, SemiAnnual, Quaterly, Act365, Act365));
	vecIRS.push_back(irsTuple(120, 43024, 0.0389, SemiAnnual, Quaterly, Act365, Act365));
	//TBS
	tbsTupleVec vecTBS;
	//TBS 6M 1Y
	vecTBS.push_back(tbsTuple(12,43024, 0.0021 , SemiAnnual, Annual, Act365, Act365));
	vecTBS.push_back(tbsTuple(24,43024, 0.0042 , SemiAnnual, Annual, Act365, Act365));
	vecTBS.push_back(tbsTuple(36,43024, 0.0075 , SemiAnnual, Annual, Act365, Act365));
	vecTBS.push_back(tbsTuple(60,43024, 0.0102 , SemiAnnual, Annual, Act365, Act365));
	//TBS 3M 6M
	vecTBS.push_back(tbsTuple(12,43024, 0.0014 , Quaterly, SemiAnnual, Act365, Act365));
	vecTBS.push_back(tbsTuple(24,43024, 0.0022 , Quaterly, SemiAnnual, Act365, Act365));
	vecTBS.push_back(tbsTuple(36,43024, 0.0041 , Quaterly, SemiAnnual, Act365, Act365));
	vecTBS.push_back(tbsTuple(60,43024, 0.0055 , Quaterly, SemiAnnual, Act365, Act365));

	MultiRateCurveCalibration Mrcc(Act365, LinearInterpolation);
	Mrcc.SetIrs(vecIRS);
	Mrcc.SetDeposits(vecDeps);
	Mrcc.SetOis(vecOIS);
	Mrcc.SetTbs(vecTBS);
	Mrcc.SetFRAs(vecFRAs);
	Mrcc.SetCalcDate(calcDate);
	Mrcc.Calibrate();

	MultiRateCurve* pMrc = Mrcc.GetMultiRateCurve();
	RateCurve * dc = pMrc->GetDiscountCurve();
	RateCurve * lc3m = pMrc->GetLiborCurve(Quaterly);
	RateCurve * lc1m = pMrc->GetLiborCurve(Monthly);
	RateCurve * lc6m = pMrc->GetLiborCurve(SemiAnnual);
	RateCurve * lc1Y = pMrc->GetLiborCurve(Annual);

	//Repricing
	std::vector < std::unique_ptr<InterestRateSwap >> oisVec;
	oisVec.resize(7);
	oisVec[0].reset(new OvernightIndexedSwap(6, 43024, 1, 0.0051, Quaterly, Quaterly, Act365, Act365));
	oisVec[1].reset(new OvernightIndexedSwap(12, 43024, 1, 0.0092, Quaterly, Quaterly, Act365, Act365));
	oisVec[2].reset(new OvernightIndexedSwap(24, 43024, 1, 0.0101, Quaterly, Quaterly, Act365, Act365));
	oisVec[3].reset(new OvernightIndexedSwap(36, 43024, 1, 0.0152, Quaterly, Quaterly, Act365, Act365));
	oisVec[4].reset(new OvernightIndexedSwap(60, 43024, 1, 0.0181, Quaterly, Quaterly, Act365, Act365));
	oisVec[5].reset(new OvernightIndexedSwap(120, 43024, 1, 0.0224, Quaterly, Quaterly, Act365, Act365));
	oisVec[6].reset(new OvernightIndexedSwap(3, 43024, 1, 0.0021, Monthly, Quaterly, Act365, Act365));
	for (std::vector < std::unique_ptr<InterestRateSwap >>::iterator it = oisVec.begin(); it != oisVec.end(); ++it)
	{
		double npv = it->get()->price(*dc, calcDate);
		iscorr = iscorr && isCorrect(npv, 0., 1.E-9);
	}

	std::vector< std::unique_ptr<ForwardRateAgreement> > fraVec3m;
	fraVec3m.resize(2);
	fraVec3m[0].reset(new ForwardRateAgreement(43085,1.,0.0035,Quaterly,Act365) );
	fraVec3m[1].reset(new ForwardRateAgreement(43175,1.,0.0045,Quaterly,Act365) );
	for (std::vector < std::unique_ptr<ForwardRateAgreement >>::iterator it = fraVec3m.begin(); it != fraVec3m.end(); ++it)
	{
		it->get()->SetLiborCurve(lc3m);
		double npv = it->get()->price(*dc, calcDate);
		iscorr = iscorr && isCorrect(npv, 0., 1.E-9);
	}

	std::vector< std::unique_ptr<ForwardRateAgreement> > fraVec6m;
	fraVec6m.resize(1);
	fraVec6m[0].reset(new ForwardRateAgreement(43085,1.,0.0043,SemiAnnual,Act365) );
	for (std::vector < std::unique_ptr<ForwardRateAgreement >>::iterator it = fraVec6m.begin(); it != fraVec6m.end(); ++it)
	{
		it->get()->SetLiborCurve(lc6m);
		double npv = it->get()->price(*dc, calcDate);
		iscorr = iscorr && isCorrect(npv, 0., 1.E-9);
	}


	std::vector < std::unique_ptr<InterestRateSwap >> irsVec3m;
	irsVec3m.resize(5);
	irsVec3m[0].reset(new InterestRateSwap(12, 43024, 1, 0.0123, SemiAnnual, Quaterly, Act365, Act365));
	irsVec3m[1].reset(new InterestRateSwap(24, 43024, 1, 0.0151, SemiAnnual, Quaterly, Act365, Act365));
	irsVec3m[2].reset(new InterestRateSwap(36, 43024, 1, 0.02632, SemiAnnual, Quaterly, Act365, Act365));
	irsVec3m[3].reset(new InterestRateSwap(60, 43024, 1, 0.0301, SemiAnnual, Quaterly, Act365, Act365));
	irsVec3m[4].reset(new InterestRateSwap(120, 43024, 1, 0.0389, SemiAnnual, Quaterly, Act365, Act365));

	for (std::vector < std::unique_ptr<InterestRateSwap >>::iterator it = irsVec3m.begin(); it != irsVec3m.end(); ++it)
	{
		it->get()->SetLiborCurve(lc3m);
		double npv = it->get()->price(*dc, calcDate);
		iscorr = iscorr && isCorrect(npv, 0., 1.E-9);
	}

	std::vector < std::unique_ptr<InterestRateSwap >> irsVec1m;
	irsVec1m.resize(5);
	irsVec1m[0].reset(new InterestRateSwap(6, 43024, 1, 0.0055, Quaterly, Monthly, Act365, Act365));
	irsVec1m[1].reset(new InterestRateSwap(12, 43024, 1, 0.0102, Quaterly, Monthly, Act365, Act365));
	irsVec1m[2].reset(new InterestRateSwap(24, 43024, 1, 0.0124, Quaterly, Monthly, Act365, Act365));
	irsVec1m[3].reset(new InterestRateSwap(36, 43024, 1, 0.0263, Quaterly, Monthly, Act365, Act365));
	irsVec1m[4].reset(new InterestRateSwap(60, 43024, 1, 0.0295, Quaterly, Monthly, Act365, Act365));

	for (std::vector < std::unique_ptr<InterestRateSwap >>::iterator it = irsVec1m.begin(); it != irsVec1m.end(); ++it)
	{
		it->get()->SetLiborCurve(lc1m);
		double npv = it->get()->price(*dc, calcDate);
		iscorr = iscorr && isCorrect(npv, 0., 1.E-8);
	}

	std::vector < std::unique_ptr<TenorBasisSwap >> tbsVec3m6m;
	tbsVec3m6m.resize(4);
	tbsVec3m6m[0].reset(new TenorBasisSwap(12,43024,1,0.0014,0,Quaterly,SemiAnnual,Act365,Act365));
	tbsVec3m6m[1].reset(new TenorBasisSwap(24,43024,1,0.0022,0,Quaterly,SemiAnnual,Act365,Act365));
	tbsVec3m6m[2].reset(new TenorBasisSwap(36,43024,1,0.0041,0,Quaterly,SemiAnnual,Act365,Act365));
	tbsVec3m6m[3].reset(new TenorBasisSwap(60,43024,1,0.0055,0,Quaterly,SemiAnnual,Act365,Act365));

	for (std::vector < std::unique_ptr<TenorBasisSwap >>::iterator it = tbsVec3m6m.begin(); it != tbsVec3m6m.end(); ++it)
	{
		it->get()->SetReceivedLiborCurve(lc3m);
		it->get()->SetPaidLiborCurve(lc6m);
		double npv = it->get()->price(*dc, calcDate);
		iscorr = iscorr && isCorrect(npv, 0., 1.E-8);
	}

	std::vector < std::unique_ptr<TenorBasisSwap >> tbsVec6m12m;
	tbsVec6m12m.resize(4);
	tbsVec6m12m[0].reset(new TenorBasisSwap(12,43024,1,0.0021,0,SemiAnnual,Annual,Act365,Act365));
	tbsVec6m12m[1].reset(new TenorBasisSwap(24,43024,1,0.0042,0,SemiAnnual,Annual,Act365,Act365));
	tbsVec6m12m[2].reset(new TenorBasisSwap(36,43024,1,0.0075,0,SemiAnnual,Annual,Act365,Act365));
	tbsVec6m12m[3].reset(new TenorBasisSwap(60,43024,1,0.0102,0,SemiAnnual,Annual,Act365,Act365));

	for (std::vector < std::unique_ptr<TenorBasisSwap >>::iterator it = tbsVec6m12m.begin(); it != tbsVec6m12m.end(); ++it)
	{
		it->get()->SetReceivedLiborCurve(lc6m);
		it->get()->SetPaidLiborCurve(lc1Y);
		double npv = it->get()->price(*dc, calcDate);
		iscorr = iscorr && isCorrect(npv, 0., 1.E-8);
	}

	double survProb(1.);
	for (DateInt curveDate = calcDate ; curveDate < calcDate + 1000 ; curveDate += 100)
	{
		survProb = pMrc->CalcSurvivalProbability(Quaterly,calcDate,curveDate);
	}

	return iscorr;
}


