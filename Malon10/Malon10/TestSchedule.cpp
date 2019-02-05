#include"Tests.h"
#include"Schedule.h"

bool TestSchedule()
{
	bool isCorrect(true);
	{

		DateInt FlDts[] = {  43100, 43281, 43465, 43646, 43830, 44012, 44196, 44377, 44561 };
		std::vector<DateInt> FlDtVec(FlDts, FlDts + sizeof(FlDts) / sizeof(DateInt));
		//std::cout << "First Schedule" << std::endl;
		GregDate M1(2021, 12, 31);
		GregDate I1(2015, 12, 31);
		GregDate CalcDate(2017, 10, 15);
		Frequency fr = SemiAnnual;
		YfConvention yfc(Act365);
		Schedule sch(M1, I1, CalcDate, fr, yfc);
		unsigned int i = 0;
		for (Schedule::FlowMapConstIterator it = sch.Begin(); it != sch.End(); ++it)
		{
			//std::cout << "FlowDate = " << it->second._FlowDate << " StartDate = " << it->second._StartDate << " yf = " << it->second._yf << std::endl;
			if (it->second._FlowDate != FlDtVec[i])
			{
				isCorrect = false;
			}
			if (!isCorrect) break;
			++i;
		}
	}
	{
		DateInt FlDts[] = {
			43283, 43375, 43467, 43557, 43648, 43740, 43832, 43923, 44014, 44106, 44198, 44288, 44379, 44471, 44563, 44653,
			44744, 44836, 44928, 45018, 45109, 45201, 45293, 45384, 45475, 45567, 45659, 45749 };
		std::vector<DateInt> FlDtVec(FlDts, FlDts + sizeof(FlDts) / sizeof(DateInt));
		//std::cout << "Second Schedule" << std::endl;
		GregDate M1(2025, 4, 2);
		GregDate I1(2018, 4, 2);
		GregDate CalcDate(2017, 10, 15);
		Frequency fr = Quaterly;
		YfConvention yfc(Act365);
		Schedule sch(M1, I1, CalcDate, fr, yfc);
		unsigned int i = 0;
		for (Schedule::FlowMapConstIterator it = sch.Begin(); it != sch.End(); ++it)
		{
			//std::cout << "FlowDate = " << it->second._FlowDate << " StartDate = " << it->second._StartDate << " yf = " << it->second._yf << std::endl;
			if (it->second._FlowDate != FlDtVec[i])
			{
				isCorrect = false;
			}
			if (!isCorrect) break;
			++i;
		}
	}
	return isCorrect;
}