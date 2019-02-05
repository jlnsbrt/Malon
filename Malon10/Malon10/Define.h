#ifndef _DEFINE_H_INCL
#define _DEFINE_H_INCL
#include<string>
#include<vector>
#include<tuple>
typedef unsigned int DateInt;

void ThrowMessage(bool condition, const std::string& message);


enum YfConvention
{
    Act36525 = 36525,
    Act365 = 365,
    _30360 = 360,
    ActAct = 366
};

enum InterpMethod
{
    StepInterpolation = 0,
    LinearInterpolation = 1,
    CublicSpline = 2
};

enum ZcType
{
    DfType = 1,
    RateType = 2
};

enum Frequency
{
    Annual = 12,
    SemiAnnual = 6,
    Quaterly = 3,
    Monthly = 1,
    Daily = 0,
    None = 13
};

// IRS inputs: MonthMaturity, Issue Date, fixed Rate, fixed Leg frequency, float leg frequency, fixed yf convention, float yf convention
typedef std::tuple < unsigned int, DateInt, double, Frequency, Frequency, YfConvention, YfConvention > irsTuple;
typedef std::vector<irsTuple> irsTupleVec;
// TBS inputs: MonthMaturity, Issue Date, spread (on the received leg), received Leg frequency, paid leg frequency, received yf convention, paid yf convention
typedef std::tuple < unsigned int, DateInt, double, Frequency, Frequency, YfConvention, YfConvention > tbsTuple;
typedef std::vector<irsTuple> tbsTupleVec;
//Deposits inputs: Start , End , rate
typedef std::tuple < DateInt, DateInt, double, YfConvention > depositsTuple;
typedef std::vector<depositsTuple> depositsTupleVec;
//Fras inputs: Start  , rate, tenor
typedef std::tuple < DateInt,  double, YfConvention , Frequency > frasTuple;
typedef std::vector<frasTuple> frasTupleVec;

#endif