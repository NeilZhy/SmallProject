#ifndef BIGDATA_H_
#define BIGDATA_H_

using namespace std;

#include <string>
#include <limits.h>
#include <assert.h>

typedef long long INT64;

#define INT64_MAX "+9223372036854775807"
#define INT64_MIN "-9223372036854775808"

class BigData
{
public:
	BigData(INT64 value);

	BigData(const char* pStr);

	BigData operator + (const BigData& bigdata);

	BigData operator - (const BigData& bigdata);

	BigData operator * (const BigData& bigdata);

	BigData operator / (const BigData& bigdata);

	string Add(const string& Left, const string& Right);

	string Sub(const string& Left, const string& Right);

	string Mul(const string& Left, const string& Right);

	string Div(const string& Left, const string& Right);

	BigData& operator = (const BigData& bigdata);

	friend ostream& operator<<(ostream& _cout, const BigData& bigdata);

private:
	bool IsOverFlowINT64() const;

	bool IsLeftBig(char *Left, int LSize, char* Right, int RSize);

	char LoopSub(char *&Left, int& LSize, char* &Right, int RSize);

private:
	INT64   _value;
	string  _pData;
};

#endif