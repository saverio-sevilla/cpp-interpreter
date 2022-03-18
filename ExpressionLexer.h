#pragma once

#include <string>
#include <vector>
#include <cctype>
#include <iostream>
#include <map>
#include <variant>

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
	AND, 
	CLASS, 
	ELSE, 
	FALSE, 
	FUN, 
	FOR, 
	IF, 
	NIL, 
	OR,
	PRINT, 
	RETURN,
	SUPER, 
	THIS, 
	TRUE, 
	VAR, 
	WHILE,
};


struct Token {
	TokenT type;
	std::variant<double, string> t_value;

	bool operator==(const Token& other);
	bool operator!=(const Token& other);
};

std::ostream& operator<<(std::ostream& out, const TokenT value);
void printTokenVector(std::vector<Token> token_vec);

class ExpressionLexer
{
private:
	string source{};
	std::map<string, TokenT> identifiers;
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
	void identifier();
	void string_parse();

public:

	ExpressionLexer(string source);

	void replace_source(string new_source) {
		source = new_source;
		string_length = source.length();
	}

	std::vector<Token> parse();

};


