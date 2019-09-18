#include<iostream>
#include<fstream>
#include<string>

bool commentSection = false;


// process one line at a time. Will return the output of the processed line. This function is also recursively called.
std::string processLine(std::string &line)
{
	std::string processedLine;

	// Check if the code is already under /* spell
	if (commentSection)
	{
		for (std::string::size_type pos = 0; pos < line.length(); pos++)
		{
			if (line[pos] == '*' && line[pos + 1] == '/')
			{
				// */ detected , thus the code section can be end
				commentSection = false;

				// The string following the end of code section needs to be analysed again for comments
				std::string substr = line.substr(pos + 2, line.length());
				processedLine += processLine(substr);

				// current loop of analysis can be closed as the same analysis is done in the previous command
				break;
			}
		}
	}
	else
	{

		// search for // or /* to signal beginning of comment mode
		for (std::string::size_type pos = 0; pos < line.length(); pos++)
		{
			if (line[pos] == '/')
			{
				// detect for //
				if (line[pos + 1] == '/') // beginning of line comment
				{
					// all the following chars after the line are irrelevant, So only take what is before that.
					pos = line.length(); // shift position to end
				}
				// detect for /*
				else if (line[pos + 1] == '*') // beginning of comment section
				{
					// since /* is encountered, any future occurance of chars till */ is irrelevant , so turn on a flag
					commentSection = true;
					// Do the string following /* in the string following.
					std::string substr = line.substr(pos, line.length());
					processedLine += processLine(substr);

					// No need to continue as the remainging analysis is done in the previous statement
					break;
				}
				else
				{
					//normal behavior, so add to the processedLine a valid char
					processedLine += line.at(pos);
				}
			}
			else
			{
				// normal behaviour
				processedLine += line.at(pos);
			}
		}
		// once the processing is done. Add the end of line. ( still needs changes, gives multiple end of line when processLine recursively called)
		processedLine += "\n";
	}

	return processedLine;
}

// master function for removing comments
int removeComments(std::ifstream & in, std::ofstream & out)
{
	std::string line;
	while (!in.eof())
	{
		std::getline(in, line);
		out << processLine(line);
	}

	return 0;
}



int main()
{
	// open file stream ( in file and out file)
	std::ifstream in("sample.cpp");
	std::ofstream out("out.cpp");

	if (!in.is_open())
		std::cout << "Error opening the file\n";

	// call remove comments master function
	removeComments(in, out);

	// close both the file streams
	in.close();
	out.close();

	return 0;
}


