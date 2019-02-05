#include"GregDate.h"
#include<algorithm>

int GregDate::_daysInMonths[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

GregDate::GregDate(int year, int month, int day) :_year(year), _month(month), _day(day), _updated(true)
{
	CalcSerialNum();
}


GregDate::GregDate(DateInt date) :_updated(true), _serialNum(date)
{
	CalcYMD();
}

bool GregDate::IsLeapYear() const
{
	if (_year % 4 != 0) return false;
	if (_year % 400 == 0) return true;
	if (_year % 100 == 0) return false;
	return true;
}


DateInt GregDate::GetSerialNum() 
{
	if (!_updated)
	{
		CalcSerialNum();
	}
	return _serialNum;
}

DateInt GregDate::GetSerialNumConst() const
{
	return _serialNum;
}


void GregDate::AddMonth(int n)
{
	int lastDayInMonth = GetDaysInMonth();
	bool isLastDayInMonth = _day == lastDayInMonth;
	_year = _year + n / 12;
	_month = _month + n % 12;
	if (_month > 12)
	{
		_year += 1;
		_month -= 12;
	}
	if (_month < 1)
	{
		_year -= 1;
		_month += 12;
	}
	lastDayInMonth = GetDaysInMonth();
	if (!isLastDayInMonth)// Last day of month maps to last day of result month
	{
		_day = std::min(_day, lastDayInMonth);
	}
	else
	{
		_day = lastDayInMonth;
	}
	_updated = false;
}

void GregDate::AddYears(int n)
{
	_year = _year + n;
	_updated = false;
}

void GregDate::CalcSerialNum()
{
	if (_month < 1 || _month > 12 || _day < 1 || _day > GetDaysInMonth())
	{
		throw("Invalid Date ");
	}
	if (_year / 2000 == 0)
	{
		throw("Invalid Date < year 2000");
	}
	int yearafter2000 = _year % 2000;
	int nbLeapYear = (yearafter2000 +3) / 4 ;
	_serialNum = 365 * yearafter2000 + nbLeapYear;
	int dfromMonths = 0;
	for (unsigned int i = 0; i < static_cast<unsigned int>(_month) - 1; ++i)
	{
		dfromMonths += _daysInMonths[i];
	}
	_serialNum += dfromMonths + _day + twoThousands;
	if (IsLeapYear() && _month >= 3)
	{
		_serialNum += 1;
	}
}

void GregDate::CalcYMD()
{
	int serialNumRem = _serialNum - twoThousands;
	if (serialNumRem <= 0)
	{
		throw("Invalid Date ");
	}
	_year = serialNumRem / 365;
	DateInt rawserialNum = GregDate(2000 + _year , 1, 1).GetSerialNum();
	if (_serialNum < rawserialNum)
	{
		_year--;
		rawserialNum = GregDate(2000 + _year, 1, 1).GetSerialNum();
	}
	_year += 2000;
	serialNumRem = _serialNum +1 - rawserialNum ;
	int daysInCurrentYear(0);
	unsigned int i = 1;
	while (i <= 12)
	{
		daysInCurrentYear += GetDaysInMonth(i);
		if (daysInCurrentYear >=serialNumRem)
		{
			daysInCurrentYear -= GetDaysInMonth(i);
			break;
		}
		++i;
	}
	_month = i ;
	_day = serialNumRem - daysInCurrentYear;
}


int GregDate::GetDaysInMonth(unsigned int i)
{
	if (i > 12  || i < 1)
	{
		throw("Invalid month");
	}
	int res = _daysInMonths[i - 1];
	if (IsLeapYear() && i == 2)
	{
		res++;
	}
	return res;
}

int GregDate::GetDaysInMonth()
{
	return GetDaysInMonth(_month);
}