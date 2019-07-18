#include<iostream>
#include<memory>
#include<string>

/*
 * Base class
 */
class Base
{
	public:
		Base(std::string name):m_name{name}{}
		virtual ~Base(){}

		void show(){std::cout<<"Base::show()\n";}
		virtual void work(){std::cout<<"Base::work()\n";}

		std::string getName(){return m_name;}

		std::string m_name;
};

/*
 * Derived1 class
 */
class Derived1 : public Base
{
	public:
		Derived1(std::string name):Base{name}{}
		virtual ~Derived1(){}
		void show(){std::cout<<"Derived1::show()\n";}
		virtual void work() override{std::cout<<"Derived1::work()\n";}

};

/*
 * Derived2 class
 */
class Derived2 : public Base
{
	public:
		Derived2(std::string name):Base{name}{}
		virtual ~Derived2(){}
		void show(){std::cout<<"Derived2::show()\n";}
		virtual void work() override{std::cout<<"Derived2::work()\n";}

};

int main()
{
	// Default behavior of Base class
	std::shared_ptr<Base> base_sp=std::make_shared<Base>("Base Object");
	std::cout<<"Expected default behaviour of Base shared pointers -\n";
	base_sp->show();
	base_sp->work();
	std::cout<<"\n";

	// Default behavior of Derived1 class
	std::shared_ptr<Derived1> derived1_sp=std::make_shared<Derived1>("Derived1 Object");
	std::cout<<"Expected default behaviour of Derived1 shared pointers -\n";
	derived1_sp->show();
	derived1_sp->work();
	std::cout<<"\n";

	// Default behavior of Derived2 class
	std::shared_ptr<Derived2> derived2_sp=std::make_shared<Derived2>("Derived2 Object");
	std::cout<<"Expected default behaviour of Derived2 shared pointers -\n";
	derived2_sp->show();
	derived2_sp->work();
	std::cout<<"\n";
/*
 * Study of static_cast and dynamic_cast on raw pointers
 */
	std::cout<<"Before moving ahead, the behavior of static_cast and dynamic_cast on raw pointers are observed-\n\n";
	Base * b_p= new Base("Base X");
	Derived1 * d1_p = new Derived1("Derived1 X");
	Derived2 * d2_p = new Derived2("Derived2 X");

	Base * b_p1 = static_cast<Base*>(d1_p);
	if(b_p1)
		std::cout<<"Upcasting of Derived1 raw pointer to Base pointer using static_cast possible\n";

	Base * b_p2 = dynamic_cast<Base*>(d1_p);
	if(b_p2)
		std::cout<<"Upcasting of Derived1 raw pointer to Base pointer using dynamic_cast possible\n";
	
	Derived1 * d_p2 = static_cast<Derived1*>(b_p1);
	if(d_p2)
		std::cout<<"Downcasting of Base to Derived1 using static_cast - Not recommended as no safety checks performed by static_cast during downcasting\n";

	Derived1 * d_p3 = static_cast<Derived1*>(b_p);
	if(d_p3)
		std::cout<<"Invalid Downcasting of Base to Derived1 using static cast because the pointer not Derived object pointer. Not recommended - undefined behavoir - static_cast doesn't do safety checks. \n";

	std::cout<<"Recommended to use dynamic_cast rather static_cast for downcasting\n";

	Derived1 * d_p4 = dynamic_cast<Derived1*>(b_p1);
	if(d_p3)
		std::cout<<"valid downcasting using dynamic_cast\n";
	
	Derived1 * d_p5 = dynamic_cast<Derived1*>(b_p);
	if(!d_p5)
		std::cout<<"invalid downcasting using dynamic_cast returns nullptr\n";

	std::cout<<"\n";



/*
 * Study of static_pointer_cast and dynamic_pointer_cast on shared_ptr
 */

	std::cout<<"Moving ahead, the behaviour of static_pointer_cast and dynamic_pointer_cast are observed as follows-\n";


	// Upcasting - static_cast on shared pointers
	std::shared_ptr<Base> base_sp2=std::static_pointer_cast<Base>(derived1_sp);
	std::cout<<"Upcasting : Applying static_pointer_cast on Derived1 shared pointers -\n";
	base_sp2->show();
	base_sp2->work();
	std::cout<<"Count of "<<derived1_sp->getName()<<" shared pointers - "<<base_sp2.use_count()<<"\n";
	std::cout<<"\n";

	// Upcasting - dynamic_cast on shared pointers - same as static_pointer_cast
	std::shared_ptr<Base> base_sp3=std::dynamic_pointer_cast<Base>(derived1_sp);
	std::cout<<"Upcasting : Applying dynamic_pointer_cast on Derived1 shared pointers -\n";
	base_sp3->show();
	base_sp3->work();
	std::cout<<"Count of "<<derived1_sp->getName()<<" shared pointers - "<<base_sp3.use_count()<<"\n";
	std::cout<<"This is same count on derived1_sp also - Count "<<derived1_sp.use_count()<<"\n";
	std::cout<<"\n";

	// Downcasting - static_pointer_cast - Not recommended as no safety check performed
	std::shared_ptr<Derived1> derived1_sp1=std::static_pointer_cast<Derived1>(base_sp);
	if(derived1_sp1)
		std::cout<<"Invalid downcasting possible using static_pointer_cast - Not recommended to use static_pointer_cast for downcasting \n";
	else
		std::cout<<"Downcasting not possible for "<<base_sp->getName()<<"\n";
	std::cout<<"\n";

	// Downcasting - dynamic_pointer_cast on a shared pointer - Recommended
	std::shared_ptr<Derived1> derived1_sp2=std::dynamic_pointer_cast<Derived1>(base_sp);
	if(!derived1_sp2)
		std::cout<<"Downcasting valid check using dynamic_pointer_cast - returns nullptr\n";
	std::cout<<"\n";

	// Downcasting - static_pointer_cast on shared pointers - Recommended
	std::shared_ptr<Derived1> derived1_sp3=std::dynamic_pointer_cast<Derived1>(base_sp2);
	if(derived1_sp3)
	{
		std::cout<<"Downcasting valid check using dynamic_pointer_cast - returns a valid pointer\n";
		derived1_sp3->show();
		derived1_sp3->work();
	}

	return 0;
}


