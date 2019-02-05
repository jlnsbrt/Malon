#ifndef _RATECURVECALIB_H_INCL
#define _RATECURVECALIB_H_INCL

#include"OvernightIndexedSwap.h"
#include"TenorBasisSwap.h"
#include"Deposit.h"
#include"ForwardRateAgreement.h"
#include"RateCurve.h"
#include<map>
#include<memory>
#include<tuple>
#include<vector>
#include"Solver.h"

// abstract class
class RateCurveCalibration
{
public:
	// structor.  yfconv : year fraction convention of the calibrated yield curve , im: interpolation method of the calibrated yield curve
	// tenor : tenor of the calibrated yield curve
    RateCurveCalibration(YfConvention yfconv, InterpMethod im, Frequency tenor);
    ~RateCurveCalibration();
	// Method to set the calibration instruments
	void SetIrs(const irsTuple & irs);
	void SetOis(const irsTuple & irs);
	void SetDeposits(const depositsTuple & dep);
	void SetFRAs(const frasTuple& fra);
	void SetTbs(const tbsTuple & tbs);
    void SetIrs(const irsTupleVec & irsVec);
	void SetOis(const irsTupleVec & irsVec);
    void SetDeposits(const depositsTupleVec & depVec);
	void SetFRAs(const frasTupleVec& fraVec);
	void SetTbs(const tbsTupleVec & tbsVec); 
	// to The yc start date of the calibratted cuve
    void SetCalcDate(DateInt calcDate);

	//Method that makes the calibration
    virtual void Calibrate();

	// To get the calibrated curve
    RateCurve  * const  GetRateCurve() const;

protected:
    void Init();
    virtual void CalibrateWithSwap() = 0;
	virtual void CalibrateWithTbs() = 0;
    virtual void CalibrateWithDeposits();
    virtual void CalibrateWithFRAs() = 0;

    typedef irsTupleVec::const_iterator irsTupleConstIterator;
    typedef depositsTupleVec::const_iterator depositsTupleConstIterator;
    typedef frasTupleVec::const_iterator frasTupleConstIterator;
    typedef std::map<DateInt, std::unique_ptr< InterestRateSwap> > swapMap;
    typedef swapMap::const_iterator swapMapConstIterator;
    typedef swapMap::iterator swapMapIterator;
	typedef std::map < DateInt, std::unique_ptr< TenorBasisSwap>> tbsMap;
	typedef tbsMap::const_iterator tbsMapConstIterator;
	typedef tbsMap::iterator tbsMapIterator;
    typedef std::map<DateInt, std::unique_ptr< Deposit> > depositMap;
    typedef depositMap::const_iterator depositMapConstIterator;
    typedef depositMap::iterator depositMapIterator;
    typedef std::map<DateInt, std::unique_ptr< ForwardRateAgreement> > fraMap;
    typedef fraMap::const_iterator fraMapConstIterator;
    typedef fraMap::iterator fraMapIterator;

    Frequency m_Tenor;
    swapMap m_swapMap;
	tbsMap m_tbsMap;
    depositMap m_DepositMap;
	fraMap m_FraMap;
    std::unique_ptr<RateCurve> m_RateCurve;

	swapMapConstIterator swapBegin() const;
	swapMapConstIterator swapEnd() const;
	swapMapIterator swapBegin();
	swapMapIterator swapEnd();
	tbsMapConstIterator tbsBegin() const;
	tbsMapConstIterator tbsEnd() const;
	tbsMapIterator tbsBegin();
	tbsMapIterator tbsEnd();
	depositMapConstIterator DepBegin() const;
	depositMapConstIterator DepEnd() const;
	depositMapIterator DepBegin();
	depositMapIterator DepEnd();
	fraMapConstIterator FraBegin() const;
	fraMapConstIterator FraEnd() const;
	fraMapIterator FraBegin();
	fraMapIterator FraEnd();
	//// Solver tool
	class RateSolver : public Solver
	{
	public:
		RateSolver(SolverMethod meth); 
		~RateSolver(); 
		void SetInstrument(Instrument * pInst);
		void SetRateCurve(RateCurve * pRc);
		void SetQuotedPrice(double price);
		virtual double f(double x) const;

	protected:
		Instrument * m_pInst;
		RateCurve * m_pRc;
		double m_quotedPrice;
	};
};

/////////////////// inline methods ///////////////////////////

inline RateCurveCalibration::RateCurveCalibration(YfConvention yfconv, InterpMethod im, Frequency tenor) : m_Tenor(tenor)
{
	m_RateCurve.reset(new RateCurve(yfconv, im, RateType,tenor));
}

inline RateCurveCalibration::~RateCurveCalibration() {}

inline void RateCurveCalibration::SetCalcDate(DateInt calcDate)
{
	m_RateCurve->SetYcStartDate(calcDate);
}

inline RateCurve  * const  RateCurveCalibration::GetRateCurve() const
{
	return m_RateCurve.get();
}

inline RateCurveCalibration::swapMapConstIterator RateCurveCalibration::swapBegin() const
{
	return m_swapMap.begin();
}

inline RateCurveCalibration::swapMapConstIterator RateCurveCalibration::swapEnd() const
{
	return m_swapMap.end();
}

inline RateCurveCalibration::swapMapIterator RateCurveCalibration::swapBegin()
{
	return m_swapMap.begin();
}

inline RateCurveCalibration::swapMapIterator RateCurveCalibration::swapEnd()
{
	return m_swapMap.end();
}

inline RateCurveCalibration::tbsMapConstIterator RateCurveCalibration::tbsBegin() const
{
	return m_tbsMap.begin();
}

inline RateCurveCalibration::tbsMapConstIterator RateCurveCalibration::tbsEnd() const
{
	return m_tbsMap.end();
}

inline RateCurveCalibration::tbsMapIterator RateCurveCalibration::tbsBegin()
{
	return m_tbsMap.begin();
}

inline RateCurveCalibration::tbsMapIterator RateCurveCalibration::tbsEnd()
{
	return m_tbsMap.end();
}

inline RateCurveCalibration::depositMapConstIterator RateCurveCalibration::DepBegin() const
{
	return m_DepositMap.begin();
}

inline RateCurveCalibration::depositMapConstIterator RateCurveCalibration::DepEnd() const
{
	return m_DepositMap.end();
}

inline RateCurveCalibration::depositMapIterator RateCurveCalibration::DepBegin()
{
	return m_DepositMap.begin();
}

inline RateCurveCalibration::depositMapIterator RateCurveCalibration::DepEnd()
{
	return m_DepositMap.end();
}

inline RateCurveCalibration::fraMapConstIterator RateCurveCalibration::FraBegin() const
{
	return m_FraMap.begin();
}

inline RateCurveCalibration::fraMapConstIterator RateCurveCalibration::FraEnd() const
{
	return m_FraMap.end();
}

inline RateCurveCalibration::fraMapIterator RateCurveCalibration::FraBegin()
{
	return m_FraMap.begin();
}

inline RateCurveCalibration::fraMapIterator RateCurveCalibration::FraEnd() 
{
	return m_FraMap.end();
}


inline RateCurveCalibration::RateSolver::RateSolver(SolverMethod meth) : Solver(meth) {}

inline RateCurveCalibration::RateSolver::~RateSolver(){}

inline void RateCurveCalibration::RateSolver::SetInstrument(Instrument * pInst)
{
	m_pInst = pInst;
}
inline void RateCurveCalibration::RateSolver::SetRateCurve(RateCurve * pRc)
{
	m_pRc = pRc;
}
inline void RateCurveCalibration::RateSolver::SetQuotedPrice(double price)
{
	m_quotedPrice = price;
}

#endif
