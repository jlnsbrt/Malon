#include"Instrument.h"
#include"GregDate.h"

unsigned int Instrument::NbMonths(Frequency tenor)
{
	switch(tenor)
	{
	case Monthly:
		return 1;
	case Quaterly:
		return 3;
	case SemiAnnual:
		return 6;
	case Annual:
		return 12;
	default:
		throw("Invalid Frequency");

	}
}


DateInt Instrument::CalcMaturity(unsigned int MaturityInMonths, DateInt Issue)
{
	GregDate MaturityDate = GregDate(Issue);
	MaturityDate.AddMonth(MaturityInMonths);
	return MaturityDate.GetSerialNum();
}

