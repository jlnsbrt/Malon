#include"MultiRateCurveCalibration.h"
#include<list>

void MultiRateCurveCalibration::Calibrate()
{
	CreateRateCurveCalibrations();
	m_MultiRateCurve.reset(new MultiRateCurve());
	m_DiscountCurveCalibration->Calibrate();
	m_MultiRateCurve->SetDiscountCurve(m_DiscountCurveCalibration->GetRateCurve());
	for (std::map<Frequency, std::unique_ptr<LiborCurveCalibration> >::iterator it = m_LiborCurveCalibrationMap.begin(); it != m_LiborCurveCalibrationMap.end(); ++it)
	{
		it->second->Calibrate();
		m_MultiRateCurve->SetLiborCurve(it->second->GetRateCurve());
	}
}

void MultiRateCurveCalibration::CreateRateCurveCalibrations()
{
	//DiscountCurveCalibration
	m_DiscountCurveCalibration.reset(new DiscountCurveCalibration(m_YfC, m_im, Daily));
	m_DiscountCurveCalibration->SetCalcDate(m_ycStartDate);
	m_DiscountCurveCalibration->SetDeposits(m_depositsTupleVec);
	m_DiscountCurveCalibration->SetOis(m_oisTupleVec);
	//LiborCurveCalibration
	//Calibration with IRS
	for (irsTupleVec::const_iterator itIrsTuple = m_irsTupleVec.begin(); itIrsTuple != m_irsTupleVec.end(); ++itIrsTuple)
	{
		Frequency tenor = std::get<4>(*itIrsTuple);
		if (m_LiborCurveCalibrationMap.find(tenor) == m_LiborCurveCalibrationMap.end())
		{
			m_LiborCurveCalibrationMap[tenor] = std::unique_ptr<LiborCurveCalibration>(new LiborCurveCalibration(m_YfC, m_im, tenor));
			m_LiborCurveCalibrationMap[tenor]->SetCalcDate(m_ycStartDate);
			m_LiborCurveCalibrationMap[tenor]->SetDeposits(m_depositsTupleVec);
			m_LiborCurveCalibrationMap[tenor]->SetDiscountCurve(m_DiscountCurveCalibration->GetRateCurve());
		}
		m_LiborCurveCalibrationMap[tenor]->SetIrs(*itIrsTuple);
	}
	//Calibration with Tbs
	CreateLiborCurveCalibrationsFromTbs();
	//Calibration with FRAs
	for (frasTupleVec::const_iterator itFRATuple = m_frasTupleVec.begin() ; itFRATuple != m_frasTupleVec.end() ;  ++itFRATuple  )
	{
		Frequency tenor = std::get<3>(*itFRATuple);
		if (m_LiborCurveCalibrationMap.find(tenor) != m_LiborCurveCalibrationMap.end())
		{
			m_LiborCurveCalibrationMap[tenor]->SetFRAs(*itFRATuple);
		}
	}
}

bool MultiRateCurveCalibration::CreateLiborCurveCalibrationsFromTbs()
{
	bool res = false;
	// Calibration with TBS 
	// For a given tenor if IRS exists IRS are chosen
	for (tbsTupleVec::const_iterator itTbsTuple = m_tbsTupleVec.begin(); itTbsTuple != m_tbsTupleVec.end(); ++itTbsTuple)
	{
		Frequency receivedTenor = std::get<3>(*itTbsTuple);
		Frequency paidTenor = std::get<4>(*itTbsTuple);
		if (m_LiborCurveCalibrationMap.find(paidTenor) == m_LiborCurveCalibrationMap.end() && m_LiborCurveCalibrationMap.find(receivedTenor) != m_LiborCurveCalibrationMap.end())
		{
			m_LiborCurveCalibrationMap[paidTenor] = std::unique_ptr<LiborCurveCalibration>(new LiborCurveCalibration(m_YfC, m_im, paidTenor));
			m_LiborCurveCalibrationMap[paidTenor]->SetCalcDate(m_ycStartDate);
			m_LiborCurveCalibrationMap[paidTenor]->SetDeposits(m_depositsTupleVec);
			m_LiborCurveCalibrationMap[paidTenor]->SetDiscountCurve(m_DiscountCurveCalibration->GetRateCurve());
			m_LiborCurveCalibrationMap[paidTenor]->SetOtherTbsTenor(receivedTenor);
			res = true;
		}
		if (m_LiborCurveCalibrationMap.find(paidTenor) != m_LiborCurveCalibrationMap.end() && m_LiborCurveCalibrationMap.find(receivedTenor) == m_LiborCurveCalibrationMap.end())
		{
			m_LiborCurveCalibrationMap[receivedTenor] = std::unique_ptr<LiborCurveCalibration>(new LiborCurveCalibration(m_YfC, m_im, receivedTenor));
			m_LiborCurveCalibrationMap[receivedTenor]->SetCalcDate(m_ycStartDate);
			m_LiborCurveCalibrationMap[receivedTenor]->SetDeposits(m_depositsTupleVec);
			m_LiborCurveCalibrationMap[receivedTenor]->SetDiscountCurve(m_DiscountCurveCalibration->GetRateCurve());
			m_LiborCurveCalibrationMap[receivedTenor]->SetOtherTbsTenor(paidTenor);
			res = true;
		}
		if (m_LiborCurveCalibrationMap.find(paidTenor) != m_LiborCurveCalibrationMap.end())
		{
			if (m_LiborCurveCalibrationMap[paidTenor]->GetOtherTbsTenor() == receivedTenor)
			{
				m_LiborCurveCalibrationMap[paidTenor]->SetTbs(*itTbsTuple);
			}
		}
		if (m_LiborCurveCalibrationMap.find(receivedTenor) != m_LiborCurveCalibrationMap.end())
		{
			if (m_LiborCurveCalibrationMap[receivedTenor]->GetOtherTbsTenor() == paidTenor)
			{
				m_LiborCurveCalibrationMap[receivedTenor]->SetTbs(*itTbsTuple);
			}
		}
	}
	if ( res == true )
	{
		CreateLiborCurveCalibrationsFromTbs();
	}
		
	// In LiborCalibration calibrated with TBS we set the other libor curve
	for (std::map<Frequency, std::unique_ptr<LiborCurveCalibration> >::iterator it = m_LiborCurveCalibrationMap.begin(); it != m_LiborCurveCalibrationMap.end(); ++it)
	{
		Frequency OtherTbsTenor = it->second->GetOtherTbsTenor();
		if (OtherTbsTenor != None) //calib with Tbs
		{
			std::map<Frequency, std::unique_ptr<LiborCurveCalibration> >::const_iterator otherLiborCalibration = m_LiborCurveCalibrationMap.find(OtherTbsTenor);
			ThrowMessage(otherLiborCalibration == m_LiborCurveCalibrationMap.end(), "Invalid Tbs calibration");
			RateCurve* plCOther = otherLiborCalibration->second->GetRateCurve();
			it->second->SetLiborCurve(plCOther);
		}
	}
	return false;
}