#include<string>
#include<iostream>
#include<sstream>

/*
 * istringstream -- apply input operation on string stream
 */

int main()
{
	std::string str{"The sky is blue"};	
	std::istringstream iss{str};

	// get string content
	std::cout<<iss.str()<<"\n";


	// perform input operation on string stream
	std::string word;
	while(iss>>word)
	{
		std::cout<<word<<"\n";
	}

	return 0;
}

