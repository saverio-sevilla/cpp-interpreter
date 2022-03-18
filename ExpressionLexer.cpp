#include "ExpressionLexer.h"

std::ostream& operator<<(std::ostream& out, const TokenT value) {
	static std::map<TokenT, std::string> strings;
	if (strings.size() == 0) {
		#define INSERT_ELEMENT(p) strings[p] = #p
		INSERT_ELEMENT(TokenT::PLUS);
		INSERT_ELEMENT(TokenT::MINUS);
		INSERT_ELEMENT(TokenT::MULT);
		INSERT_ELEMENT(TokenT::DIV);
		INSERT_ELEMENT(TokenT::NUM); // Number
		INSERT_ELEMENT(TokenT::STRING);
		INSERT_ELEMENT(TokenT::ID);
		INSERT_ELEMENT(TokenT::L_PAREN);
		INSERT_ELEMENT(TokenT::R_PAREN);
		INSERT_ELEMENT(TokenT::L_BRACE);
		INSERT_ELEMENT(TokenT::R_BRACE);
		INSERT_ELEMENT(TokenT::COMMA);
		INSERT_ELEMENT(TokenT::DOT);
		INSERT_ELEMENT(TokenT::SEMICOLON);
		INSERT_ELEMENT(TokenT::SLASH);
		INSERT_ELEMENT(TokenT::SEMICOLON);
		INSERT_ELEMENT(TokenT::NOT);
		INSERT_ELEMENT(TokenT::NOT_EQUAL);
		INSERT_ELEMENT(TokenT::ASSIGN);
		INSERT_ELEMENT(TokenT::EQUAL);
		INSERT_ELEMENT(TokenT::GREATER);
		INSERT_ELEMENT(TokenT::GREATER_EQUAL);


		#undef INSERT_ELEMENT
	}
	return out << strings[value];
}

void printTokenVector(std::vector<Token> token_vec) {
	for (auto token : token_vec) {
		std::cout << "Type: " << token.type;
		if (token.type == TokenT::NUM) {
			std::cout << ", Value: " << token.value;
		}
		std::cout << std::endl;
	}
}

void  ExpressionLexer::advance_high() {
	++high_ptr;
}

void  ExpressionLexer::advance_both() {
	++high_ptr;
	++low_ptr;
}

void  ExpressionLexer::catch_up() {
	low_ptr = high_ptr;
}

char ExpressionLexer::next_token() {
	if (high_ptr >= string_length - 2) {
		return '\0';
	}
	return static_cast<char>(source[high_ptr + 1]);
}

char ExpressionLexer::current_token() {
	return source[high_ptr];
}

void ExpressionLexer::number() {
	while (isdigit(current_token()) && high_ptr < string_length) {
		advance_high();
	}
	if (current_token() == '.' && isdigit(next_token())) {
		advance_high();
		while (isdigit(current_token()) && high_ptr < string_length) {
			advance_high();
		}
	}
	std::string num_str = source.substr(low_ptr, high_ptr - low_ptr);
	token_vector.push_back({ TokenT::NUM, std::stod(num_str) });
}

std::vector<Token> ExpressionLexer::parse() {
	while (high_ptr < string_length) {
		switch (current_token()) {
		case ' ':
		case '\t':
			advance_both();
			break;
		case '+':
			token_vector.push_back({ TokenT::PLUS });
			advance_both();
			break;
		case '-':
			token_vector.push_back({ TokenT::MINUS });
			advance_both();
			break;
		case '*':
			token_vector.push_back({ TokenT::MULT });
			advance_both();
			break;
		case '/':
			token_vector.push_back({ TokenT::DIV });
			advance_both();
			break;
		case '(':
			token_vector.push_back({ TokenT::L_PAREN });
			advance_both();
			break;
		case ')':
			token_vector.push_back({ TokenT::R_PAREN });
			advance_both();
			break;
		case '{':
			token_vector.push_back({ TokenT::L_BRACE });
			advance_both();
			break;
		case '}':
			token_vector.push_back({ TokenT::R_BRACE });
			advance_both();
			break;
		case ',':
			token_vector.push_back({ TokenT::COMMA });
			advance_both();
			break;
		case '.':
			token_vector.push_back({ TokenT::DOT });
			advance_both();
			break;
		case ';':
			token_vector.push_back({ TokenT::SEMICOLON });
			advance_both();
			break;
		case '\\':
			if (next_token() == '\\') {
				while (current_token() != '\n' && high_ptr < string_length - 1) {
					advance_both();
				}
			}
			else {
				token_vector.push_back({ TokenT::SLASH });
				advance_both();
			}
			break;

		case '!':
			if (next_token() == '=') {
				token_vector.push_back({ TokenT::NOT_EQUAL});
				advance_both();
				advance_both();
			}
			else {
				token_vector.push_back({ TokenT::NOT });
				advance_both();
			}
			break;

		case '=':
			if (next_token() == '=') {
				token_vector.push_back({ TokenT::EQUAL });
				advance_both();
				advance_both();
			}
			else {
				token_vector.push_back({ TokenT::ASSIGN });
				advance_both();
			}
			break;

		case '>':
			if (next_token() == '=') {
				token_vector.push_back({ TokenT::GREATER_EQUAL });
				advance_both();
				advance_both();
			}
			else {
				token_vector.push_back({ TokenT::GREATER });
				advance_both();
			}
			break;

		case '<':
			if (next_token() == '=') {
				token_vector.push_back({ TokenT::LESS_EQUAL });
				advance_both();
				advance_both();
			}
			else {
				token_vector.push_back({ TokenT::LESS });
				advance_both();
			}
			break;

		default:
			if (isdigit(current_token())) {
				number();
				catch_up();
			}
			else {
				advance_both();
			}
		}
	}

	low_ptr = high_ptr = 0;
	return token_vector;
}
