#include <string>
#include <vector>
#include <cmath>
#include <cctype>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <atlstr.h>

#pragma once

struct Expression {
	Expression(std::string token) : token(token) {}
	Expression(std::string token, Expression a) : token(token), args{ a } {}
	Expression(std::string token, Expression a, Expression b) : token(token), args{ a, b } {}

	std::string token;
	std::vector<Expression> args;
};

class Parser {
public:
	explicit Parser(CString inputstr,double x) : Cstrinput(inputstr), ValueX(x)
	{
		strcpy_s(buff, CT2A(Cstrinput));
		int i = 0;
		while (buff[i] != '\0') {
			buff[i] = tolower(buff[i]);
			i++;
		}
		input = buff;
	}
	Expression parse();
	double eval(const Expression& e);
private:
	std::string parse_token();
	Expression parse_simple_expression();
	Expression parse_binary_expression(int min_priority);
	char buff[1024];
	const char* input;
	CString Cstrinput;
public:
	double ValueX;
};