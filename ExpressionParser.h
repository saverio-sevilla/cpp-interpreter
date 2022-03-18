#pragma once

#include "ExpressionLexer.h"
#include <string>
#include <vector>
#include <cctype>
#include <iostream>
#include <map>
#include <variant>
#include <algorithm>

using std::vector;
using std::cout;

class ExpressionParser
{
private:
	vector<Token> token_vec;

public:
	ExpressionParser(vector<Token> token_vec);
	void printFormatted();
	void handleUnary();
	void handleBinary();
};

