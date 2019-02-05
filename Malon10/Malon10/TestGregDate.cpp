#include"Tests.h"
#include"GregDate.h"
#include<vector>
#include<iostream>

bool TestGregDate()
{
	bool isCorrect = true;
	std::vector < GregDate > ;
	GregDate g0(2025, 8, 3);
	DateInt g0Num = g0.GetSerialNum();
	isCorrect = isCorrect && g0Num == 45872;
	GregDate g1(2032, 2, 29);
	DateInt g1Num = g1.GetSerialNum();
	isCorrect = isCorrect && g1Num == 48273;
	GregDate g2(2000, 1, 1);
	DateInt g2Num = g2.GetSerialNum();
	isCorrect = isCorrect && g2Num == 36526;
	GregDate g3(2002, 3, 29);
	DateInt g3Num = g3.GetSerialNum();
	isCorrect = isCorrect && g3Num == 37344;

	GregDate g1bis(g1Num);
	GregDate g0bis(g0Num);
	GregDate g2bis(g2Num);
	GregDate g3bis(g3Num);

	g0.AddMonth(15);
	g0Num = g0.GetSerialNum();

	///////////////////
	DateInt d(44705);
	GregDate GregD(d);
	DateInt dBis = GregD.GetSerialNum();
	isCorrect = isCorrect && d == dBis;
	//////////////////////
	//GregDate calcDate(2017, 10, 15);
	//DateInt cacDateNum = calcDate.GetSerialNum();
	//std::vector < GregDate > gregDatesVec;
	//gregDatesVec.push_back(GregDate(2042, 3, 24));
	//gregDatesVec.push_back(GregDate(2028, 12, 31));
	//gregDatesVec.push_back(GregDate(2032, 2, 29));
	//gregDatesVec.push_back(GregDate(2044, 7, 30));
	//std::vector<int> period;
	//period.push_back(1);
	//period.push_back(3);
	//period.push_back(6);
	//period.push_back(12);


	//for (unsigned int i = 0; i < gregDatesVec.size(); ++i)
	//{
	//	std::cout << "Maturity = " << gregDatesVec[i].GetSerialNum() << std::endl;
	//	for (unsigned int j = 0; j < period.size(); ++j)
	//	{
	//		GregDate g(gregDatesVec[i]);
	//		DateInt gNum = g.GetSerialNum();
	//		while (gNum > cacDateNum)
	//		{
	//			std::cout << "Date = " << gNum << std::endl;
	//			g.AddMonth(-period[j]);
	//			gNum = g.GetSerialNum();
	//		}
	//		std::cout << "    " << std::endl;
	//	}
	//	std::cout << "    " <<  std::endl;
	//}
	return isCorrect;
}