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

X f1(X& x)
{
	return x;
}

X& f2(X& x)
{
	return x;
}

X&& f3(X& x)
{
	return std::move(x);
}

X f4(X& x)
{
	return std::move(x);
}

/* Not possible cases

Rvalue cannot bind to lvalue
X& f(X& x)
{
	return std::move(x);
}

Lvalue cannot bind to Rvalue
X&& f(X &x)
{
	return x;
}
*/
int main()
{
	std::cout<<"Function invocation alone\n";
	std::cout<<"\n1. ";	X x;		// Default constructors
	std::cout<<"\n2  ";	f1(x);		// Copy constructor to the return value
	std::cout<<"\n3. ";	f2(x);		// As reference return, no object created
	std::cout<<"\n4. ";	f3(x);		// As rvalue returned, x is moved state.
	std::cout<<"\n5. ";	x=X{};		// x now move assignment constructed
	std::cout<<"\n6. ";	X x_;		// Default constructor
	std::cout<<"\n7. ";	x=x_;		// or x can be copy assigned constructed
	std::cout<<"\n8. ";	f4(x);		// rvalue returned, x is moved constructed to the return value

/* Above example shows that if return type is X, an object is created by copy or move constructor which may not be preferred*/

	std::cout<<"\nConstructors \n"; 
	std::cout<<"\n9. ";	X x1;
	std::cout<<"\n10. ";	X x2=f1(x1);	// Copy constructor - Now the copy constructor on return value happens on x2
	std::cout<<"\n11. ";	X x3=f2(x1);	// Copy constructor - copy constructor on the x3;
	std::cout<<"\n12. ";	X x4=f3(x1);	// Move constructor - Now the move constructor on the return value happens on x4
	std::cout<<"\n13. ";	X x5=f4(x1);	// Move constructor - move constructor on the x5
	
	std::cout<<"\n Assignment operators\n";
	std::cout<<"\n14. ";	X x6;		// Default constructed
	std::cout<<"\n15. ";	x6=f1(x2);	// Copy constructed to the local variable and then move assign constructed from the local variable to the x6
	std::cout<<"\n16. "; 	x6=f2(x2);	// Copy assignment constructed
	std::cout<<"\n17. "; 	x6=f3(x2);	// Move assignment constructed
	std::cout<<"\n18. ";	x6=f4(x5);	// Move constructed to the local variable and then Move assignment constructed to the x6



	return 0;
}

	
