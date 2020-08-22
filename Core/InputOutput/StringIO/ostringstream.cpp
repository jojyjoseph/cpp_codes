#include<iostream>
#include<string>
#include<sstream>

/*
 * ostringstream - performs output operation on string
 */

int main()
{
	// create ostringstream object and perform output operations like cout
	std::ostringstream oss;
	oss<<7;
	oss<<"\n";
	oss<<"Hello world\n";

	std::cout<<oss.str()<<"\n";

	// support move operations
	decltype(oss) oss2{std::move(oss)};
	std::cout<<oss2.str()<<"\n";

	return 0;
}
