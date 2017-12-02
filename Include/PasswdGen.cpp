#include "PasswdGen.h"

string PasswdGen::ShowPWD(string str)
{
	while (str.length() < pwdMinLen)
	{
		str = "0" + str;
	}

	return str;
}

string PasswdGen::CalcPWD(int sk)
{
	int len = charset_PWD.length();
	int k = sk;
	string s;
	do
	{
		k = k / len;
		if (k != 0)
		{
			s = charset_PWD[k % len] + s;
		}
		else
		{
			s = s + charset_PWD[sk % len];
		}
	} while (k != 0);

	if (s.length() > pwdMaxLen)
	{
		s = "-1";
		genStop = 1;
	}
	return s;
}

void PasswdGen::initDefValues()
{
	if (pwdMinLen < 0)
		pwdMinLen = 0;
	if (pwdMaxLen < 1)
		pwdMaxLen = 1;
	PASSWORD = 0;
}

PasswdGen::PasswdGen()
{
	initDefValues();
}

PasswdGen::PasswdGen(int MinPasswordLength, int MaxPasswordLength)
{
	pwdMinLen = MinPasswordLength;
	pwdMaxLen = MaxPasswordLength;
	initDefValues();
}

PasswdGen::PasswdGen(string Charset)
{
	charset_PWD = Charset;
	initDefValues();
}

string PasswdGen::getNextPWD()
{
	if (genStop == 0)
	{
		return ShowPWD(CalcPWD(PASSWORD++));
	}
	else
		return "err";
}


