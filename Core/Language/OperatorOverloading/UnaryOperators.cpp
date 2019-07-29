/*
 * Unary operator overloading
 *  eg. X++, --X, !X etc
 *
 *  They can be prefix or postfix
 */


#include<iostream>

class X
{
	public:
		X(int value):m_value{value}{}
		virtual ~X(){}

		// Unary operator for prefix operator overloading
		X& operator++()
		{
			std::cout<<"X& operator++() - unary prefix operator\n";
			m_value++;
			return *this;
		}
		
		// Unary operator for postfix operator overloading 
		X operator++(int)	// int is dummy variable
		{
			std::cout<<"X& operator++(int) - unary postfix operator\n";
			X x_temp{m_value};
			m_value++;
			return x_temp;
		}
		
		/*
		 * 2 operators have predefine meanind
		 * X=X' (equality operator)
		 * &X (address of operator)
		 * , sequencing
		 * They can be deleted as shown below
		 */
		void operator=(const X&) = delete;
		void operator&() = delete;
		void operator,(const X&) = delete;

		// When the X can only be taken as a second argument, then this <<,>> can't be done as a member function
		// This has be to be done as non-member friend function
		friend std::ostream & operator<<(std::ostream &o, X &x);
		friend std::ostream & operator<<(std::ostream &o, X&& x);

		int getValue(){return m_value;}

	private:
		int m_value;
};

std::ostream & operator<<(std::ostream &o, X &x)
{
	return o<<x.getValue();
}

std::ostream & operator<<(std::ostream &o, X &&x)
{
	return o<<x.getValue();
}



int main()
{
	X x1{1};
	std::cout<<x1++<<"\n";	//prints 2
	std::cout<<++x1<<"\n";	//prints 2, but x1 value would be 3
	return 0;
}
