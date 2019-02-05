#ifndef _GREGDATE_H_INCL
#define _GREGDATE_H_INCL

#include"Define.h"

class GregDate
{
public:
	GregDate(DateInt date);
	GregDate(int year, int month,  int day);
	GregDate(const GregDate& other);
	~GregDate(){}
	void AddMonth(int n);
	void AddYears(int n);
	DateInt GetSerialNum();
	DateInt GetSerialNumConst() const;
	int Year() const;
	int Month() const;
	int Day() const;
private:
	int _year;
	int _month;
	int _day;
	DateInt _serialNum;
	static int _daysInMonths[];// = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	bool IsLeapYear() const;
	int GetDaysInMonth();
	const static DateInt  twoThousands = 36525;
	void CalcSerialNum();
	void CalcYMD();
	bool _updated;
	int GetDaysInMonth(unsigned int i);
};


inline GregDate::GregDate(const GregDate& other) :_year(other._year), _month(other._month), _day(other._day), _serialNum(other._serialNum), _updated(other._updated){}


inline int GregDate::Year() const
{
	return _year;
}
inline int GregDate::Month() const
{
	return _month;
}
inline int GregDate::Day() const
{
	return _day;
}

#endif