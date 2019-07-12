#include<iostream>
#include<functional>
#include<vector>

int f1(char)
{
	return 1;
}

class f2
{
	public:
		int operator()(char c){return 2;}
};

auto f3 = [](char c)->int{return 3;};

class f4
{
	public:
		int nonstatfun(char c){return 4;}
		int static statfun(char){return 5;}
		int m_num;
		
		f4(int i):m_num{i}{};
		virtual ~f4(){}
};

int main()
{

/*
 * Usage of std::function and invocation
 */

	// function 
	std::function<int(char)> fn;
	fn=f1;
	std::cout<<"Free function "<<fn(100)<<"\n";

	//function object
	fn=f2();
	std::cout<<"Functor "<<fn(100)<<"\n";

	//lambda function
	fn=f3;
	std::cout<<"Lambda "<<fn(100)<<"\n";

	//non static class member function
	f4 fo(6);
	std::function<int(f4,char)> fn2 = &f4::nonstatfun;
	std::cout<<"class non static function "<<fn2(fo,100)<<"\n";

	//static class member function
	fn=&f4::statfun;
	std::cout<<"class static functioin "<<fn(100)<<"\n";

	//class member variable
	std::function<int(f4 &)> fn3=&f4::m_num;
	std::cout<<"Member accessor "<<fn3(fo)<<"\n";

/*
 * Usage of std::bind and invocation
 */
	// functions
	auto bf11=std::bind(f1,'c');
	std::cout<<"Bind function f1 to a char : "<<bf11()<<"\n";
	auto bf12=std::bind(f1,std::placeholders::_1);
	std::cout<<"Bind function f1 without an input : "<<bf12('c')<<"\n";

	// function object
	auto bf21=std::bind(f2(),'c');
	std::cout<<"Bind a function object f2 to a char : "<<bf21()<<"\n";

	// lambda function
	auto bf31=std::bind(f3,std::placeholders::_1);
	std::cout<<"Bind a lambda function to no input : "<<bf31('c')<<"\n";
	auto bf32=std::bind(f3,'c');
	std::cout<<"Bind a lambda function to char input : "<<bf32()<<"\n";

	// class static member function
	auto bf41=std::bind(&f4::statfun,std::placeholders::_1);
	std::cout<<"Bind a static member function to no input : "<<bf41('c')<<"\n";
	auto bf42=std::bind(&f4::statfun,'c');
	std::cout<<"Bind a static member function to char input : "<<bf42()<<"\n";


	//class non static member function
	auto bf43=std::bind(&f4::nonstatfun,&fo,std::placeholders::_1);
	std::cout<<"Bind a non static member function to no input : "<<bf43('c')<<"\n";
	auto bf44=std::bind(&f4::nonstatfun,&fo,'c');
	std::cout<<"Bind a non static member function to no input : "<<bf44()<<"\n";


	//class member variable
	auto bf51=std::bind(&f4::m_num,&fo);
	std::cout<<"Bind a member variable of an object : "<<bf51()<<"\n";


	/*
	 * create a container of function wrapper of type int fn(void)
	 */
	
	std::vector<std::function<int(void)>> vec_fn;
	vec_fn.push_back(std::move(bf11));
	vec_fn.push_back(bf21);
	vec_fn.push_back(bf32);
	vec_fn.push_back(bf42);
	vec_fn.push_back(bf44);
	vec_fn.push_back(bf51);

	std::cout<<"Looping over the set of bind functions\n";
	for(auto f : vec_fn)
	{
		std::cout<<"vec fn : "<<f()<<"\n";
	}


	std::cout<<"\n std::invoke examples\n";

	return 0;
}
	
