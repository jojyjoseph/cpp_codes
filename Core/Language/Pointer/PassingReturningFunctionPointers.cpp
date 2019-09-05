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


// Passing Function pointers as arguments -- similarly can be applied to all variants
void passFunctionPointer( int (X::*fp_arg)(std::string) , X * x_arg)
{
	(x_arg->*fp_arg)(std::string{});
}


// Returning Function pointers as arguments -- Method 1 -use auto
auto returnFunctionPointer1(int (X::*fp_arg)(std::string))
{
	return fp_arg;
}
	
// Returning Function pointers as argument -- Method 2 - using typedef
typedef int (X::*fp_type)(std::string);
fp_type returnFunctionPointer2(int (X::*fp_arg)(std::string))
{
	return fp_arg;
}

// Returning Function pointer as argument -- Method 3 - complex 
int (*returnFunctionPointer3_1())(float f)
{
	return f;
}
int (*returnFunctionPointer3_2( int (*fp_arg)(float)))(float f)
{
	return fp_arg;
}
int (X::*returnFunctionPointer3_3())(std::string)
{
	return &X::f1;
}
int (X::*returnFunctionPointer3_4( int (X::*fp_arg)(std::string)  ))(std::string)
{
	return fp_arg;
}



// Main function
int main()
{
	// Object creation of type X
	X x;
	X* xp = &x;
	
	// Free Function pointer
	int (*fp)(float) = f;

	// Function pointers to non static member functions
	int (X::*fp1)(std::string)=&X::f1;

	passFunctionPointer( fp1 , xp);

	auto f1 = returnFunctionPointer3_1();
	f1(1.0);

	auto f2 = returnFunctionPointer3_2(f);
	f2(1.0);

	auto f3 = returnFunctionPointer3_3();
	(xp->*f3)(std::string{});

	auto f4 = returnFunctionPointer3_4(fp1);
	(xp->*f4)(std::string{});

	return 0;
}
