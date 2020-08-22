#include<iostream>
#include<fstream>
#include<string>

int main()
{
	std::string file("inputFile1.txt");

	// create input file stream
	std::ifstream ifs;

	// Open file stream
	ifs.open("inputFile1.txt",std::ifstream::in);

	// check if the stream is good. It can be done in a while loop also.
	if(!ifs.good())
	{
		std::cout<<"File can'tbe open\n";
	}
	else
	{
		// putting the file reading logic here
		char c=ifs.get();
		std::cout<<"First char "<<c<<"\n";

		// check if the file has reached end of file
		std::string line;
		while(!ifs.eof())
		{
			std::getline(ifs,line);
			std::cout<<line<<"\n";
		}
	}


	return 0;
}
