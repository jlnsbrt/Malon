#include"Tests.h"
#include"TenorBasisSwap.h"



bool TestTBS()
{
	bool isC(true);
	DateInt CalcDate = 43022;
	///////////// rateCurve ////////////
	std::map<DateInt, double> rateMap;
	rateMap[43022] = 0.0009;
	rateMap[43053] = 0.0012;
	rateMap[43083] = 0.0015;
	rateMap[43114] = 0.0035;
	rateMap[43204] = 0.0056;
	rateMap[43387] = 0.0054;
	rateMap[43752] = 0.0069;
	rateMap[44118] = 0.0125;
	rateMap[44848] = 0.0156;
	rateMap[46674] = 0.0216;
	RateCurve rC(rateMap, Act36525, LinearInterpolation, RateType);

	//Instrument
	unsigned int Maturity = 60;
	DateInt Issue = 43024;
	double spread = 0.004;
	Frequency Receivedfreq = Quaterly;
	Frequency Paidfreq = SemiAnnual;
	YfConvention receivedconv = Act365;
	YfConvention paidconv = Act365;
	double notional = 100.;

	///////////// LiborCurves ////////////
	std::map<DateInt, double> ReceivedLiborMap;
	ReceivedLiborMap[43022] = 0.0052;
	ReceivedLiborMap[43053] = 0.0063;
	ReceivedLiborMap[43083] = 0.0078;
	ReceivedLiborMap[43114] = 0.0135;
	ReceivedLiborMap[43204] = 0.0142;
	ReceivedLiborMap[43387] = 0.0154;
	ReceivedLiborMap[43752] = 0.0165;
	ReceivedLiborMap[44118] = 0.0252;
	ReceivedLiborMap[44848] = 0.0323;
	ReceivedLiborMap[46674] = 0.0402;
	RateCurve lCR(ReceivedLiborMap, Act36525, StepInterpolation, RateType);

	std::map<DateInt, double> PaidLiborMap;
	PaidLiborMap[43022] = 0.0062;
	PaidLiborMap[43053] = 0.0078;
	PaidLiborMap[43083] = 0.0101;
	PaidLiborMap[43114] = 0.0165;
	PaidLiborMap[43204] = 0.0172;
	PaidLiborMap[43387] = 0.0195;
	PaidLiborMap[43752] = 0.0215;
	PaidLiborMap[44118] = 0.0304;
	PaidLiborMap[44848] = 0.0375;
	PaidLiborMap[46674] = 0.0468;
	RateCurve lCP(PaidLiborMap, Act36525, StepInterpolation, RateType);

	TenorBasisSwap tbs(Maturity, Issue, notional, spread, 0, Receivedfreq,Paidfreq, receivedconv, paidconv);
	tbs.SetReceivedLiborCurve(&lCR);
	tbs.SetPaidLiborCurve(&lCP);

	double npv = tbs.price(rC, CalcDate);
	///////
	GregDate MaturityDate(Issue);
	MaturityDate.AddMonth(Maturity);
	DateInt Mat = MaturityDate.GetSerialNum();

	double ReceivedLegNpv = 0.;
	{
		GregDate cpnDate(MaturityDate);
		DateInt cpnDateInt = cpnDate.GetSerialNum();
		GregDate resetDate(cpnDate);
		resetDate.AddMonth(-3);
		DateInt resetDateInt = resetDate.GetSerialNum();
		while (true)
		{
			GregDate resetDate(cpnDate);
			resetDate.AddMonth(-3);
			resetDateInt = resetDate.GetSerialNum();
			if (resetDateInt < CalcDate)
			{
				break;
			}
			double forward = lCR.GetForwardRate(resetDateInt, cpnDateInt);
			ReceivedLegNpv += (forward + spread) / 4. * rC.GetDf(cpnDateInt);
			cpnDate.AddMonth(-3);
			cpnDateInt = resetDateInt;
		}
	}

	double PaidLegNpv = 0.;
	{
		GregDate cpnDate(MaturityDate);
		DateInt cpnDateInt = cpnDate.GetSerialNum();
		GregDate resetDate(cpnDate);
		resetDate.AddMonth(-6);
		DateInt resetDateInt = resetDate.GetSerialNum();
		while (true)
		{
			GregDate resetDate(cpnDate);
			resetDate.AddMonth(-6);
			resetDateInt = resetDate.GetSerialNum();
			if (resetDateInt < CalcDate)
			{
				break;
			}
			double forward = lCP.GetForwardRate(resetDateInt, cpnDateInt);
			PaidLegNpv += (forward + 0.) / 2. * rC.GetDf(cpnDateInt);
			cpnDate.AddMonth(-6);
			cpnDateInt = resetDateInt;
		}
	}
	double repNpv = notional * (ReceivedLegNpv - PaidLegNpv);
	isC= isC && isCorrect(npv, repNpv);
	return isC;
}

