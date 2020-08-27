#include<iostream>


class Base
{
	public:
		Base()
//			:m_staticPrivateInt{1}
		{

			// private static variable can be initialized in the C'tor, 
			// But it can be initialized outside the class or in the C'tor
			m_staticPrivateInt =1;
			

			// Like above, Same with public static member variable
			m_staticPublicInt = 4;
		}

		virtual ~Base()
		{

		}


		void updateStaticPublicInt(int i){ m_staticPublicInt = i;}

		void static publicStaticFunction(void)
		{
			std::cout<<"Base::publicStaticFunction(void)\n";
			// static member functions can access static member variables
			m_staticPrivateInt=1;


			// static member functions Can't access non static member variables and non static member functions
			//m_nonStaticPrivateInt = 1;
			//publicNonStaticFunction();
			
		}

		void publicNonStaticFunction(void)
		{
			// Non static member function can access static member variables and static member functions
			std::cout<<"Base::publicNonStaticFunction(void)\n";
			publicStaticFunction();
			m_staticPrivateInt = 8;
		}

		
		static int m_staticPublicInt;

	private:
		// private static variable. Can be initialized only by the class functions. Can't be defined outside the class
		static int m_staticPrivateInt;

		// const static variable private. Can be initialized in the Class
		const static int m_constStaticPrivateInti=6;

		// non static private variable
		int m_nonStaticPrivateInt;
};


// Better to initialize the static outside with default values.
// private static variables can be defined outside the scope. This will be the value even without the class instantiation
int Base::m_staticPrivateInt = 2;
// Same as above
int Base::m_staticPublicInt = 3;

// const static member variables can also be initialized like as below, but not both together
//const int Base::m_constStaticPrivateInt = 5;
//
class Derived : public Base
{
	public:
		Derived()
			:Base()
		{}

		virtual ~Derived(){}
};


int main()
{
	Base base;
	Derived derived;
	
	// private static can't be accessed as expected.
	//std::cout<<derived.m_staticPrivateInt<<"\n";
	

	// public static variable - can be called in 3 ways
	std::cout<<"Base::m_staticPublicInt "<<Base::m_staticPublicInt<<"\n";
	std::cout<<"Derived::m_staticPublicInt "<<Derived::m_staticPublicInt<<"\n";
	std::cout<<"Derived.m_staticPublicInt "<<derived.m_staticPublicInt<<"\n";

	Base::publicStaticFunction();
	base.publicNonStaticFunction();

	return 0;
}
