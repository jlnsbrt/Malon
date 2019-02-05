#include"Curve.h"
#include"YearFraction.h"

Curve::CurveMapConstIterator Curve::Before(DateInt date) const
{
	CurveMapConstIterator it = After(date);
	if (it != Begin())
	{
		--it;
	}
	return it;
	//if (Size() == 0)
	//{
	//	throw("Void Curve");
	//}
	//CurveMapConstIterator it = Begin();
	//if (date < it->first  )
	//{
	//	throw("Invalid Date");
	//}
	//while (it != End() && date >= it->first )
	//{
	//	if (date == it->first)
	//	{
	//		return it;
	//	}
	//	++it;		
	//}
	//--it;
	//return it;
}

Curve::CurveMapConstIterator Curve::After(DateInt date) const
{
	if (Size() == 0)
	{
		throw("Void Curve");
	}
	CurveMapConstIterator it = Begin();
	if (date < it->first)
	{
		throw("Invalid Date");
	}
	while (it != End() && date >= it->first)
	{
		if (date == it->first)
		{
			return it;
		}
		++it;
	}
	return it;
	//CurveMapConstIterator it = Before(date);
	//if (it != End())
	//{
	//	++it;
	//}
	//return it;
}

double Curve::GetValue(DateInt date) const
{
	CurveMapConstIterator bef = Before(date);
	CurveMapConstIterator aft = After(date);
	switch (m_interpMethod)
	{
	case StepInterpolation:
	{
		if (aft == End())
		{
			return bef->second;
		}
		return aft->second;
	}
	case LinearInterpolation:
	{
		if (aft == End() || aft == Begin() )
		{
			return bef->second;
		}
		else
		{
			double befEndYf = Yf::yearFraction(bef->first, aft->first, m_yfconv);
			double befDateYf = Yf::yearFraction(bef->first, date, m_yfconv);
			double a = befDateYf / befEndYf;
			double res = bef->second  + ( aft->second - bef->second )  * a;
			return res;
		}
	}
	default:
		throw("Invalid Interpolation method");
	}
}

void Curve::AddPoint(DateInt date, double value)
{
	m_curveMap[date] = value;
	return;
}

double Curve::StepIntegration::value(DateInt a, DateInt b) const
{
	if ( a == b )
	{
		return 0.;
	}
	if ( a > b )
	{
		return -value(b,a);
	}
	YfConvention yfConv = m_pCurve->GetYfConvention();
	CurveMapConstIterator AftA = m_pCurve->After(a);
	CurveMapConstIterator BefB = m_pCurve->Before(b);
	CurveMapConstIterator AftB = m_pCurve->After(b);	
	if ( AftA ==m_pCurve->End() )
	{
		return Yf::yearFraction(a,b,yfConv) * f ( BefB->second);
	}
	else
	{
		double res = Yf::yearFraction(a,AftA->first,yfConv) * f (AftA->second);
		CurveMapConstIterator it = AftA;
		while ( it != BefB)
		{
			DateInt tstart = it->first; 
			++it;
			res += Yf::yearFraction(tstart,it->first,yfConv) * f(it->second);
		}
		if ( AftB != m_pCurve->End() )
		{
			res += Yf::yearFraction(BefB->first,b,yfConv) * f( AftB->second);
		}
		else
		{
			res += Yf::yearFraction(BefB->first,b,yfConv) * f( BefB->second);
		}
		return res;
	}
}
	



