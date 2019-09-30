#include<iostream>

int main()
{

	auto lambda1 = []()->void{
		std::cout<<"lambda1\n";
		return;
	};
	lambda1();

	class Lambda1
	{
		public:
			void operator()(){std::cout<<"Lambda1\n";}
	};

	Lambda1 lambda1_1;
	lambda1_1();


	auto lambda2 = []()->int{std::cout<<"lambda2\n";return 2;};
	std::cout<<"lambda2 return value : "<<lambda2()<<'\n';

	class Lambda2
	{
		public:
			int operator()(){std::cout<<"Lambda2\n";return 2;}
	};
	Lambda2 lambda2_1;
	std::cout<<"Lambda2 return value : "<<lambda2_1()<<'\n';

	auto lambda3=[](int i)->int{std::cout<<"lambda3\n";return 3;};
	std::cout<<"lambda3 return value : "<<lambda3(1)<<'\n';

	class Lambda3
	{
		public:
			int operator()(int i){std::cout<<"Lambda3\n";return 3;}
	};
	Lambda3 lambda3_1;
	std::cout<<"Lambda3 return value "<<Lambda3()(1)<<'\n';

	int global=10;
	auto lambda4=[&global](int i)->int{std::cout<<"Lambda4\n";return ++global;};
	std::cout<<"lamdba4 return value : "<<lambda4(2)<<'\n';

	class Lambda4
	{
		public:
			Lambda4(int &global):m_global{global}{}
			int operator()(int i){std::cout<<"Lambda4\n"; return ++m_global;}
		private:
			int &m_global;
	};

	std::cout<<"Lambda4 return value : "<<Lambda4(global)(1)<<'\n';
			

	return 0;
}
