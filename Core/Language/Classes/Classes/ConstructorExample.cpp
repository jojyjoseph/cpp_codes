#include <iostream>
#include <string>
class X
{
	public:
		// Default constructor
		X()
		{
			std::cout<<"Default constructor : X{}\n";
			m_id = 0;
		}

		// copy constructor
		X(const X&x)
		{
			std::cout<<"Copy constructor : X(const X&x)\n";
			m_id=1;
		}

		// copy assignment operator
		X& operator=(const X&x)
		{
			std::cout<<"Copy assignment operator : X& operator=(const X&x)\n";
			m_id=2;
		}

		// move constructor
		X(const X&&x)
		{
			std::cout<<"Move constructor : X(const X&& x)\n";
			m_id=3;
		}

		// move assignment operator
		X& operator=(const X&&x)
		{
			std::cout<<"Move assignment operator : X& operator=(const X&& x)\n";
			m_id=4;
		}

		// methods
		int getID(void){return m_id;}

	private:
		int m_id;
};

void printID(std::string s, X&x)
{
	std::cout<<s<<" id : "<<x.getID()<<"\n";
}

X& f1(X& x)
{
	return x;
}

X f2(X& x)
{
	return x;
}

int main()
{
	std::cout<<"\nDefault Ctor examples\n"; 
	// Default constructor
	X x1;
	printID("x1", x1);

	X x2{};
	printID("x2", x2);

	std::cout<<"\nCopy constructor examples\n";
	// copy constructor - when new objects are created
	X x3=x1;
	printID("x3", x3);

	X x4=f1(x1);
	printID("x4", x4);

	X x5=f2(x1);
	printID("x5", x5);
		

	std::cout<<"\nCopy assignment operator examples\n";
	// copy assignment constructor. When existing object are overwritten
	X x6;
	x6=x1;
	printID("x6", x6);


	// Move constructor example. Creating new objects 
	std::cout<<"\nMove constructor examples\n";
	X x7(std::move(x1));
	printID("x7", x7);
	X x8=std::move(x2);
	printID("x8", x8);


	// Move assignment operator example. Overwriting existing objects
	std::cout<<"\nMove assignment operator example\n";
	X x9;
	x9=std::move(x3);
	printID("x9", x9);
	
	return 0;
}

	
