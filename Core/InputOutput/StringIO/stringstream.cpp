#include<iostream>
#include<string>
#include<sstream>

/*
 * stringstream is for both input and output
 * stringstream is subclass of iostream, thus inherits the <<operator
 */

int main()
{
	// create string stream
	std::stringstream ss;

	// insert formated data into stream
	ss<<7<<" "<<49<<" "<<"print, Hello World";
	
	// string stream can be converted to string
	std::cout<<ss.str()<<"\n";

	int n;
	ss>>n;
	std::cout<<"Value of n = "<<n<<"\n";
	ss>>n;
	std::cout<<"Value of n = "<<n<<"\n";	

	std::string s1;
	ss>>s1;
	std::cout<<"s1 = "<<s1<<"\n";

	std::getline(ss,s1);
	std::cout<<"Read the whole remaining line : "<<s1<<"\n";



	return 0;

}
