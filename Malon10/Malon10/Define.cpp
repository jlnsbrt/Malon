#include"Define.h"

void ThrowMessage(bool condition, const std::string& message)
{
	if (condition)
	{
		throw(message);
	}
}