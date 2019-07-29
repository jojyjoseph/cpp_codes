/* Binary Operators
 *
 * for eg X1+X2 is a binary operator. *,-,+= etc are other examples.
 *  Can be described as non-static member function with arguments
 *  or non-member funtions taking two arguments
 */

#include<iostream>
#include<string>

class X
{
	public:
		X(int value):m_value{value}{}
		
		// Operator overloading as non-static member functions
		X & operator+(X &x)
		{
			std::cout<<"X::operator+()\n";
			m_value += x.getValue();
			return *this;
		}

		int getValue(){return m_value;}

	private:

	int m_value;
};

// Operator overloading as non-member functions
// invocation for  X+int
void operator+(X &x, int value)
{
	std::cout<<"operator(X,int)\n";
}

// invocation for int+X
void operator+(int value, X &x)
{
	std::cout<<"operator(int,X)\n";
}

int main()
{
	X x1{2},x2{3};

	x1=x1+x2; 	// invokes X.operator+()
	x1+4;	// invokes operator+(X,int)
	4+x1;	// invokes operator+(int,X)
	
	return 0;
}
	
