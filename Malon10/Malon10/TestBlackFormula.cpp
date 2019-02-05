#include"Tests.h"
#include"CapFloor.h"
#include"Swaption.h"
#include"YearFraction.h"
#include"Normal.h"
#include<algorithm>

bool TestCapFloorBF()
{
		bool isCorr(true);
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
        RateCurve rC(rateMap, Act365, LinearInterpolation, RateType);
		/////////////// volatility /////////////
		double volatility = 0.15;
		YfConvention yf =  _30360;

		// Forward caplet
		{
			unsigned int monthsMaturity = 60;
			DateInt Issue = 43005;
			double Notional = 100.;
			Frequency freq = SemiAnnual;
			YfConvention cpnYfConv = _30360;
			double strikeRate = 0.005;
			CapFloor::PayOff po = CapFloor::_Cap;
			CapFloor oCap(monthsMaturity,Issue,Notional,freq,cpnYfConv,strikeRate,po);
			double currentLibor = 0.0052;
			oCap.SetCurrentLibor(currentLibor);
			double price = oCap.price(rC,volatility,yf,CalcDate);
			
			double priceRep = 0;
			unsigned int period = Instrument::NbMonths(freq);
			unsigned int Size = monthsMaturity/period;
			GregDate Flowdate(Issue);
			Flowdate.AddMonth(period);
			GregDate Resetdate(Issue);
			double yfFlow = double(period)/12.;
			for ( unsigned int i = 0 ; i < Size ; ++i )
			{
				DateInt FlowdateInt = Flowdate.GetSerialNum();
				DateInt ResetdateInt = Resetdate.GetSerialNum();
				double zc = rC.GetForwardDf(CalcDate,FlowdateInt);
				if ( ResetdateInt > CalcDate ) //forward flows
				{
					double forward = rC.GetForwardRate(CalcDate,ResetdateInt,FlowdateInt);
					double stddev = std::sqrt(Yf::yearFraction(CalcDate,ResetdateInt,yf)) * volatility;
					double dp = std::log( forward/strikeRate) / stddev + stddev/2.;
					double dm = dp - stddev;
					priceRep += yfFlow * zc * (  forward * Normal::phi(dp) - strikeRate * Normal::phi(dm));
				}
				else
				{
					priceRep += yfFlow * std::max( currentLibor - strikeRate, 0.) * zc;
				}
				Flowdate.AddMonth(period);
				Resetdate.AddMonth(period);
			}
			priceRep *=Notional;
			isCorr = isCorr && isCorrect(price,priceRep,1.0E-7);
		}
		return isCorr;
}

bool TestSwaptionBF()
{
		bool isCorr(true);
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
        RateCurve rC(rateMap, Act365, LinearInterpolation, RateType);
		/////////////// volatility /////////////
		double volatility = 0.15;
		YfConvention yf =  _30360;
		
		{
			unsigned int monthsMaturity = 60;
			DateInt swapStartDate = 43258;
			DateInt optionDate = 43256;
			double Notional = 100.;
			Frequency fixedfreq = SemiAnnual;
			YfConvention fixedYfConv = _30360;
			Frequency floatfreq = Quaterly;
			YfConvention floatfreqtYfConv = _30360;
			double strikeRate = 0.0165;
			bool isReceived = true;
			Swaption swn(monthsMaturity,swapStartDate,optionDate,Notional,strikeRate,fixedfreq,floatfreq,fixedYfConv,floatfreqtYfConv,isReceived);
			double price = swn.price(rC,volatility,yf,CalcDate);

			InterestRateSwap irs(monthsMaturity,swapStartDate,Notional,strikeRate,fixedfreq,floatfreq,fixedYfConv,floatfreqtYfConv,isReceived);
			double annuity = irs.Annuity(rC,CalcDate);
			double swapRate = irs.ParRate(rC,CalcDate);
			double stdDev = volatility  * std::sqrt( Yf::yearFraction(CalcDate,optionDate,yf));


			double dp = std::log(swapRate/strikeRate) / stdDev + stdDev /2.;
			double dm = dp - stdDev;
			double priceRep = annuity * ( swapRate * Normal::phi(dp) - strikeRate * Normal::phi(dm) );
			isCorr = isCorr && isCorrect(price,priceRep,1.0E-7);
		}
		return isCorr;

}
