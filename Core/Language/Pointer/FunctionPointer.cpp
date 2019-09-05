#include<iostream>
#include<string>
#include<functional>

int f(float f)
{
	std::cout<<"Free function - int f(float)\n";
}

class X
{
	public:
		X(){}
		virtual ~X(){}
		
		// non static member functions
		int f1(std::string s){std::cout<<"int f1(std::string)\n";}
		int f2(const std::string s){std::cout<<"int f2(const std::string)\n";}
		const int f3(const std::string s){std::cout<<"const int f3(const std::string)\n";}
		const int f4(const std::string s) const {std::cout<<"const int f4(const std::string s) const\n";}
		
		// overloaded non static member function
		int f1(char c){std::cout<<"int f1(char)\n";}

		// static member function
		static int f5(std::string s){std::cout<<"static int X::f5)(std::string)\n";}

		// Member variable
		int m_membervariable{10};

}x;

int main()
{
	// Object creation of type X
	X x;
	X* xp = &x;
	
	// Demonstrations
	int (*fp)(float) = f;
	fp(1.0);
	(*fp)(1.0);

	// Function pointers to non static member functions
	int (X::*fp1)(std::string)=&X::f1;
	xp->f1(std::string{});
	(x.*fp1)(std::string{});
	(xp->*fp1)(std::string{});

	int (X::*fp2)(std::string)=&X::f2;	// can also add const qualifier. It works.
	xp->f2(std::string{});
	(x.*fp2)(std::string{});
	(xp->*fp2)(std::string{});

	const int (X::*fp3)(std::string)=&X::f3;
	xp->f3(std::string{});
	(x.*fp3)(std::string{});
	(xp->*fp3)(std::string{});

	const int (X::*fp4)(std::string) const =&X::f4;
	xp->f4(std::string{});
	(x.*fp4)(std::string{});
	(xp->*fp4)(std::string{});

	// overloaded non static member function
	int (X::*fp1_1)(char)=&X::f1;
	xp->f1('a');
	(x.*fp1_1)('a');
	(xp->*fp1_1)('a');

	// static member function pointer are just like normal function pointers
	int (*fp5)(std::string)=&X::f5;
	X::f5(std::string{});
	fp5(std::string{});
	(*fp5)(std::string{});

	// pointers to member variables
	int X::*v = &X::m_membervariable;
	std::cout<<"Member variable : "<<xp->m_membervariable<<"\n";
	std::cout<<"Member variable : "<<xp->*v<<"\n";
	std::cout<<"Member variable : "<<x.*v<<"\n";
	

	return 0;
}
