#pragma once

#include <string>
#include <vector>
#include <cctype>
#include <iostream>
#include <map>

using std::string;
using std::vector;

enum class TokenT {
	PLUS,
	MINUS,
	MULT,
	DIV,
	NUM,

	L_PAREN, 
	R_PAREN, 
	L_BRACE, 
	R_BRACE,
	COMMA,
	DOT,
	SEMICOLON, 
	SLASH, //
	NOT, 
	NOT_EQUAL,
	ASSIGN, 
	EQUAL,
	GREATER, 
	GREATER_EQUAL,
	LESS, 
	LESS_EQUAL,
	STRING,
	ID,

};


struct Token {
	TokenT type;
	double value{};
};

std::ostream& operator<<(std::ostream& out, const TokenT value);
void printTokenVector(std::vector<Token> token_vec);

class ExpressionLexer
{
private:
	string source{};
	string::size_type low_ptr;
	string::size_type high_ptr;
	string::size_type string_length;
	std::vector<Token> token_vector{};


	void advance_high();
	void advance_both();
	void catch_up();
	char next_token();
	char current_token();
	void number();

public:

	ExpressionLexer(string source) : source{ source } {
		low_ptr = high_ptr = 0;
		string_length = source.length();
	}

	void replace_source(string new_source) {
		source = new_source;
		string_length = source.length();
	}

	std::vector<Token> parse();

};


