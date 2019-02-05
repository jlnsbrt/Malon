#ifndef _CURVE_H_INCL
#define _CURVE_H_INCL

#include<map>
#include"Define.h"


class Curve
{
public:
	Curve(const std::map<DateInt, double>& curveMap, YfConvention yfconv, InterpMethod im);
	Curve(  YfConvention yfconv, InterpMethod im);
	~Curve(){}
	Curve(const Curve& curveObject);
	virtual double GetValue(DateInt date) const;
	virtual void AddPoint(DateInt date, double value);
	void Clear();

	YfConvention GetYfConvention() const;

	class StepIntegration
	{
	public:
		StepIntegration(const Curve* curveObject);
		~StepIntegration();
		double value(DateInt a, DateInt b) const;
		virtual double f(double v) const = 0;
	private:
		const Curve* m_pCurve;
	};
protected:
	typedef std::map<DateInt, double> CurveMap;
	typedef CurveMap::iterator CurveMapIterator;
	typedef CurveMap::const_iterator CurveMapConstIterator;
	CurveMapConstIterator Before(DateInt date) const;
	CurveMapConstIterator After(DateInt date) const;

	CurveMapIterator Begin();
	CurveMapConstIterator Begin() const;
	CurveMapIterator End();
	CurveMapConstIterator End() const;
	unsigned int Size() const;

	InterpMethod m_interpMethod;
	YfConvention m_yfconv;
	CurveMap m_curveMap;


};

inline Curve::Curve(const Curve& curveObject) :m_curveMap(curveObject.m_curveMap), m_interpMethod(curveObject.m_interpMethod), m_yfconv(curveObject.m_yfconv){}

inline Curve::Curve(const std::map<DateInt, double>& curveMap, YfConvention yfconv, InterpMethod im) : m_curveMap(curveMap), m_yfconv(yfconv), m_interpMethod(im)
{}


inline Curve::Curve( YfConvention yfconv, InterpMethod im) :  m_yfconv(yfconv), m_interpMethod(im)
{}

inline void Curve::Clear()
{
	m_curveMap.clear();
}

inline YfConvention Curve::GetYfConvention() const
{
	return m_yfconv;
}

inline Curve::CurveMapIterator Curve::Begin()
{
	return m_curveMap.begin();
}
inline Curve::CurveMapConstIterator Curve::Begin() const
{
	return m_curveMap.begin();
}
inline Curve::CurveMapIterator Curve::End()
{
	return m_curveMap.end();
}
inline Curve::CurveMapConstIterator Curve::End() const
{
	return m_curveMap.end();
}
inline unsigned int Curve::Size() const
{
	return m_curveMap.size();
}


inline Curve::StepIntegration::StepIntegration(const Curve* curveObject):m_pCurve(curveObject){}
inline Curve::StepIntegration::~StepIntegration(){}

#endif