#include<iostream>
#include<string>

/*
 * Anonymous struct and anonymous unions examples
 */

// Case 1
// anonymous struct inside anonymous union inside named struct
struct S
{
	union
	{
		struct
		{
			char c[4];
		};
		unsigned int intvalue;
	};
};

// Case 2
// anonymous struct inside a named union
union U
{
	struct
	{
		char c[4];
	};
	unsigned int intvalue;
};

// Case 3 :  anonymous struct inside anonymous union inside named struct with other members
struct S2
{
	std::string s;
	union
	{
		struct
		{
			char c[4];
		};
		unsigned int intvalue;
		void (*fn)(void);
	};

	int var1;
	std::string s22;
};


int main()
{
	// Case 1 :  anonymous struct inside anonymous union inside named struct
	S s;
	s.intvalue=0x474f4f44; // depends on endianness

	for(int x = 0 ; x<4 ; x++)
		std::cout<<s.c[x];
	std::cout<<'\n';

	// Case 2 : anonymous struct inside a named union
	U u;
	u.intvalue=0x474f4f44; // depends on endianness

	for(int x = 0 ; x<4 ; x++)
		std::cout<<u.c[x];

	std::cout<<"\n";

	// Case 3 :  anonymous struct inside anonymous union inside named union with other members
	S2 s2;
	s2.intvalue=0x474f4f44; // depends on endianness

	for(int x = 0 ; x<4 ; x++)
		std::cout<<s2.c[x];
	std::cout<<'\n';


	
	return 0;
}
