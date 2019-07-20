#include<iostream>
#include<string>
#include<memory>

template<typename T>
class SmartPointer
{
	public:
		SmartPointer(T *p)
		:m_pointer{p}{delete p;}
		
		virtual ~SmartPointer(){}

		T& operator*(){return *m_pointer;}

		T* operator->() {return m_pointer;}

		T* get(){return m_pointer;}

	private:
		T * m_pointer;

};

class X
{
	public:
		// constructor1 : X()
		X(){std::cout<<"X() constructed\n";}
	
		// constructor2 : X(int i)
		X(int i):m_publicint{i}{std::cout<<"X(int i) constructor\n";}

		// destructor
		virtual ~X(){std::cout<<"X destructed\n";}

		int m_publicint;

		std::string getName(){ return "Class X";}
};

int main()
{
	// Scope 1
	std::cout<<"Scope1 starts\n";
	{
		SmartPointer<X> p(new X);
	}
	std::cout<<"Scope1 ends\n\nScope2 starts\n";

	// Scope 2
	{
		SmartPointer<X> p{new X{2}};
		// SmartPointer::operator*()
		auto & xr = *p;
		std::cout<<"X::m_publicint - "<<xr.m_publicint<<"\n";
		
		// SmartPointer::operator->()
		std::cout<<"X::operator->() - m_publicint "<<p->m_publicint<<"\n";
		std::cout<<"X::operator->() - getName "<<p->getName()<<"\n";

	}
	std::cout<<"Scope2 ends\n\nScope3 starts\n";

	// Scope 3
	{
		SmartPointer<int> p{new int{5}};
		auto & x = (*p=5);

		std::cout<<"int value - "<<x<<"\n";
	}
	std::cout<<"Scope3 ends\n";

	return 0;
}

	
	
