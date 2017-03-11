#include <iostream>
using namespace std;
#include "BigData.h"
#include <iomanip>

void FunTest()
{
	//BigData big("9223372036854775807");  //Max
	//BigData big("-9223372036854775808");  //Min
	 
	BigData big("11111111111111111111111111111100000000000000000000000");  //BigData

	//BigData big("0000011111111111111111111111111111100000000000000000000000"); //前置0

	//BigData big("-0000011111111111111111111111111111100000000000000000000000");  //带符号
	//BigData big("+0000011111111111111111111111111111100000000000000000000000");

	//BigData big("+000001111111aa1111111111111111111111100000000000000000000000"); //有非数字的字符

	//BigData big("9223372036854775808");  //边界溢出
	//BigData big("-9223372036854775810");

	//BigData big("a9223372036854775807");   //前置有非数字字符
	BigData big1("0");
	big1 = big;
	cout << big1 << endl;
	cout << big << endl;
}

void OperationFunTest()
{
    BigData big1("-9223372036854775807");
	BigData big2("2");

	//BigData big2((INT64)(0 -9223372036854775808));  

	//BigData big1("9999000000099");
	//BigData big2("33");

	//BigData big1("2222222222222222222222222222222222");
	//BigData big2("33");

	cout << big1  / big2<< endl;
}

int main()
{
	FunTest();

	OperationFunTest();
	system("pause");
	return 0;
}