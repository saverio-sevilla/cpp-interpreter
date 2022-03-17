#include <iostream>
#include "ScopeTable.h"


int main() {

	std::any a0 = std::string("Hello world");
	std::any a1 = 123;
	std::any a2 = 22.43;

	ScopeTable test_table;
	test_table.reassignable(false);
	test_table.insert_value("Message", Type::string_t, std::string("Hello world"));
	test_table.insert_value("Int", Type::int_t, a1);
	test_table.insert_value("Dbl", Type::double_t, a2);
	test_table.insert_value("Dbl", Type::string_t, a0);

	test_table.extend_table();
	std::any a3 = 42;
	std::any a4 = 42.42;
	test_table.insert_value("Another int", Type::int_t, a3);
	test_table.insert_value("Another Dbl", Type::double_t, a4);

	test_table.extend_table();
	test_table.insert_value("Last int", Type::int_t, 420);

	print_var_pair(test_table.get_value("Int"));

	test_table.print_tables();

}