#include "ExpressionParser.h"
#define DEBUG


enum class Operation {
	ADD_OP,
	SUB_OP,
	MUL_OP,
	DIV_OP,
	REM_PAR_OP,
};

ExpressionParser::ExpressionParser(vector<Token> token_vec) : token_vec{ token_vec } {

}

void ExpressionParser::printFormatted() {
	for (auto token : token_vec) {

		if (token.type == TokenT::NUM) {
			std::cout << std::get<double>(token.t_value);
		}
		else {
			std::cout << std::get<string>(token.t_value);
		}
		std::cout << "";
	}
	std::cout << "\n";
}

template <class ForwardIt1, class ForwardIt2, class Value>
constexpr ForwardIt1 replaceSequenceWithValue(ForwardIt1 first, ForwardIt1 last,
	ForwardIt2 s_first, ForwardIt2 s_last,
	Value&& value) {
	auto seq_start = std::search(first, last, s_first, s_last);
	if (seq_start == last)
		return last; // return last if no seq was found

	*seq_start = std::forward<Value>(value);

	auto itemsToBeRemoved = std::distance(s_first, s_last) - 1;

	if (itemsToBeRemoved > 0)
		return std::remove_if(std::next(seq_start), last,
			[&itemsToBeRemoved](const auto&) { return itemsToBeRemoved-- > 0; });
	return last;
}


void ExpressionParser::handleUnary() {

	vector<Token> plusplus{ {TokenT::PLUS}, {TokenT::PLUS} };
	vector<Token> plusminus{ {TokenT::PLUS}, {TokenT::MINUS} };
	vector<Token> minusplus{ {TokenT::MINUS}, {TokenT::PLUS} };
	vector<Token> minusminus{ {TokenT::MINUS}, {TokenT::MINUS} };

	while (true) {

		#ifdef DEBUG
		printFormatted();
		#endif // DEBUG


		auto newEnd = replaceSequenceWithValue(token_vec.begin(), token_vec.end(), plusplus.begin(), plusplus.end(), Token(TokenT::PLUS, "+"));
		if (newEnd != token_vec.end()) {
			token_vec.erase(newEnd, token_vec.end());
			continue;
		}

		newEnd = replaceSequenceWithValue(token_vec.begin(), token_vec.end(), minusplus.begin(), minusplus.end(), Token(TokenT::MINUS, "-"));
		if (newEnd != token_vec.end()) {
			token_vec.erase(newEnd, token_vec.end());
			continue;
		}

		newEnd = replaceSequenceWithValue(token_vec.begin(), token_vec.end(), plusminus.begin(), plusminus.end(), Token(TokenT::MINUS, "-"));
		if (newEnd != token_vec.end()) {
			token_vec.erase(newEnd, token_vec.end());
			continue;
		}

		newEnd = replaceSequenceWithValue(token_vec.begin(), token_vec.end(), minusminus.begin(), minusminus.end(), Token(TokenT::PLUS, "+"));
		if (newEnd != token_vec.end()) {
			token_vec.erase(newEnd, token_vec.end());
			continue;
		}

		break;
	}
}

template <class ForwardIt1, class ForwardIt2>
constexpr ForwardIt1 replaceBinary(ForwardIt1 first, ForwardIt1 last,
	ForwardIt2 s_first, ForwardIt2 s_last, Operation op) {

	auto seq_start = std::search(first, last, s_first, s_last);
	if (seq_start == last)
		return last; // return last if no seq was found

	if (op==Operation::ADD_OP)
		*seq_start = Token{ TokenT::NUM, std::get<double>(seq_start->t_value) + std::get<double>((seq_start + 2)->t_value) };

	else if (op == Operation::SUB_OP)
		*seq_start = Token{ TokenT::NUM, std::get<double>(seq_start->t_value) - std::get<double>((seq_start + 2)->t_value) };

	else if (op == Operation::MUL_OP)
		*seq_start = Token{ TokenT::NUM, std::get<double>(seq_start->t_value) * std::get<double>((seq_start + 2)->t_value) };

	else if (op == Operation::DIV_OP)
		*seq_start = Token{ TokenT::NUM, std::get<double>(seq_start->t_value) / std::get<double>((seq_start + 2)->t_value) };

	else if (op == Operation::REM_PAR_OP)
		*seq_start = Token{ TokenT::NUM, std::get<double>((seq_start + 1)->t_value) };


	auto itemsToBeRemoved = std::distance(s_first, s_last) - 1;

	if (itemsToBeRemoved > 0)
		return std::remove_if(std::next(seq_start), last,
			[&itemsToBeRemoved](const auto&) { return itemsToBeRemoved-- > 0; });
	return last;
}

void ExpressionParser::handleBinary() {
	vector<Token> addition{ {TokenT::NUM}, {TokenT::PLUS}, {TokenT::NUM} };
	vector<Token> subtraction{ {TokenT::NUM}, {TokenT::MINUS}, {TokenT::NUM} };
	vector<Token> multiplication{ {TokenT::NUM}, {TokenT::MULT}, {TokenT::NUM} };
	vector<Token> division{ {TokenT::NUM}, {TokenT::DIV}, {TokenT::NUM} };
	vector<Token> remove_parentheses{ {TokenT::L_PAREN}, {TokenT::NUM}, {TokenT::R_PAREN} };

	while (true) {

		#ifdef DEBUG
		printFormatted();
		#endif // DEBUG

		auto newEnd = replaceBinary(token_vec.begin(), token_vec.end(), remove_parentheses.begin(), remove_parentheses.end(), Operation::REM_PAR_OP);
		if (newEnd != token_vec.end()) {
			token_vec.erase(newEnd, token_vec.end());
			continue;
		}

		newEnd = replaceBinary(token_vec.begin(), token_vec.end(), multiplication.begin(), multiplication.end(), Operation::MUL_OP);
		if (newEnd != token_vec.end()) {
			token_vec.erase(newEnd, token_vec.end());
			continue;
		}

		newEnd = replaceBinary(token_vec.begin(), token_vec.end(), division.begin(), division.end(), Operation::DIV_OP);
		if (newEnd != token_vec.end()) {
			token_vec.erase(newEnd, token_vec.end());
			continue;
		}

		newEnd = replaceBinary(token_vec.begin(), token_vec.end(), addition.begin(), addition.end(), Operation::ADD_OP);
		if (newEnd != token_vec.end()) {
			token_vec.erase(newEnd, token_vec.end());
			continue;
		}

		newEnd = replaceBinary(token_vec.begin(), token_vec.end(), subtraction.begin(), subtraction.end(), Operation::SUB_OP);
		if (newEnd != token_vec.end()) {
			token_vec.erase(newEnd, token_vec.end());
			continue;
		}

		break;
	}
};
