#include"Tests.h"

bool isCorrect(double value, double target, double eps )
{
	return std::abs(value - target) < eps;
}