#include <iostream>
#include "ScopeTable.h"

ScopeTable::ScopeTable() {
	assert(scope_table_vector.size() == 0);
	std::map<string, std::pair<Type, std::any> > global_table;
	scope_table_vector.push_back(global_table);
	depth = 1;
	permit_reassignment = false;
}


bool ScopeTable::insert_value(string variable_name, Type variable_type, std::any variable_value) {
	if (scope_table_vector.size() == 0) {
		return false;
	}
	auto& table = scope_table_vector.back();
	if (!permit_reassignment) {
		table.insert({ variable_name, std::make_pair(variable_type, variable_value) });
	}
	else {
		table[variable_name] = std::make_pair(variable_type, variable_value);
	}
	return true;
}

std::pair<Type, std::any> ScopeTable::get_value(string variable_name) {
	const auto& table = scope_table_vector.back();
	auto it = table.find(variable_name);

	if (it != table.end()) {
		return (*it).second;
	}

	return search_tables(variable_name);
}

std::pair<Type, std::any> ScopeTable::search_tables(const string& variable_name) {
	for (auto table : scope_table_vector) {
		auto it = table.find(variable_name);
		if (it != table.end()) {
			return (*it).second;
		}
	}

	std::any a0;
	return { Type::unidentified_t, a0 };
}

bool ScopeTable::remove_value(const string& variable_name) {
	auto& table = scope_table_vector.back();
	auto erased = table.erase(variable_name);
	if (erased > 0) {
		return true;
	}
	return false;
}

void ScopeTable::extend_table() {
	std::map<string, std::pair<Type, std::any> > new_table;
	scope_table_vector.push_back(new_table);
	++depth;
}

bool ScopeTable::pop_table() {
	if (scope_table_vector.size() == 0) {
		return false;
	}
	scope_table_vector.pop_back();
	--depth;
	return true;
}

void ScopeTable::reassignable(bool reassign) {
	permit_reassignment = reassign;
}


void ScopeTable::print_tables() {
	std::cout << "---- layers of scope table: " << depth << " ----\n";
	std::cout << "----------------------------------\n";
	for (auto table : scope_table_vector) {


		if (table.empty()) {
			std::cout << "The table is empty\n";
			return;
		}

		for (auto const& pair : table) {
			std::cout << "{" << pair.first << "}: ";
			auto value = pair.second.second;

			auto type = pair.second.first;
			try {
				switch (type) {
				case (Type::int_t):
					std::cout << std::any_cast<int>(value) << '\n';
					break;
				case (Type::double_t):
					std::cout << std::any_cast<double>(value) << '\n';
					break;
				case (Type::bool_t):
					std::cout << std::any_cast<string>(value) << '\n';
					break;
				case (Type::string_t):
					std::cout << std::any_cast<string>(value) << '\n';
					break;
				default:
					std::cout << "Unidentified type\n";
				}
			}
			catch (std::bad_any_cast&) {
				std::cout << "Bad any cast\n";
			}

		}

		std::cout << "-------------------------------\n";
	}
}

void print_type_enum(Type t) {
	switch (t) {
	case(Type::int_t):
		std::cout << "int: ";
		break;
	case(Type::double_t):
		std::cout << "double: ";
		break;
	case(Type::bool_t):
		std::cout << "bool: ";
		break;
	case(Type::string_t):
		std::cout << "string: ";
		break;
	case(Type::unidentified_t):
		std::cout << "unidentified type: ";
		break;
	default:
		std::cout << "[type not recognized] ";
		break;
	}
}


void print_var_pair(std::pair<Type, std::any> pair) {
	auto type = pair.first;
	auto value = pair.second;

	print_type_enum(type);

	try {
		switch (type) {
		case (Type::int_t):
			std::cout << std::any_cast<int>(value) << '\n';
			break;
		case (Type::double_t):
			std::cout << std::any_cast<double>(value) << '\n';
			break;
		case (Type::bool_t):
			std::cout << std::any_cast<string>(value) << '\n';
			break;
		case (Type::string_t):
			std::cout << std::any_cast<string>(value) << '\n';
			break;
		default:
			std::cout << "Unidentified type\n";
		}
	}
	catch (std::bad_any_cast&) {
		std::cout << "Bad any cast\n";
	}
}


