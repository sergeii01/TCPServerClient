#pragma once
#include <iostream>
#include <string>

#define PWDMIN 3
#define PWDMAX 5

using namespace std;


class PasswdGen
{
private: string charset_PWD = "0123456789ABCDEFGHIJKLMNOPQARSTUVXWZabcdefghijklmnopqrstuvxwz!@#$%^&*()_+";
		 int pwdMinLen = PWDMIN;
		 int pwdMaxLen = PWDMAX;
		 int PASSWORD;
		 

		 string ShowPWD(string str);
		 string CalcPWD(int sk);
		 void initDefValues();

public: PasswdGen();
		PasswdGen(int MinPasswordLength, int MaxPasswordLength);
		PasswdGen(string Charset);
		string getNextPWD();
		string getNextPWD(int PWDCOUNT);
		int genStop = 0;
};