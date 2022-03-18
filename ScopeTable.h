#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cassert>
#include <any>
#include <utility>
#include <algorithm>


using std::string;
using std::find;

enum class Type
{
	int_t,
	double_t,
	string_t,
	bool_t,
	unidentified_t,
};

class ScopeTable
{
private:
	std::vector <  std::map<string, std::pair<Type, std::any> >  > scope_table_vector{};
	size_t depth{};
	bool permit_reassignment{};
	std::pair<Type, std::any> search_tables(const string& variable_name) const;

public:
	
	ScopeTable(); //
	ScopeTable(const ScopeTable& other) = delete;  // no copying
	ScopeTable& operator=(const ScopeTable& other) = delete; //

	bool insert_value(string variable_name, Type variable_type, std::any variable_value); //
	std::pair<Type, std::any> get_value(const string& variable_name) const; //
	bool remove_value(const string& variable_name); //

	void print_tables();
	void extend_table();
	bool pop_table();
	void reassignable(bool reassign);
};

void print_var_pair(std::pair<Type, std::any> pair);
