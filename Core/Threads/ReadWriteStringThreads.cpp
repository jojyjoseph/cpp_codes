#include<thread>
#include<iostream>
#include<mutex>


std::mutex m;

struct my
{
	std::string str;
	bool change;
}my;

void writestr(std::string s)
{
	std::lock_guard<std::mutex> guard(m);
	my.str=s;
	my.change=true;
}

void print(void)
{
	while(1)
	{
		std::lock_guard<std::mutex> guard(m);
		if(my.change)
		{
			if(my.str=="break")
				break;
			std::cout<<my.str<<"\n";
			my.change=false;
		}
	}
}

void read(void)
{
	std::string s;
	while(std::cin>>s)
	{
		if(s=="break")
		{
			writestr(s);
			break;
		}
		else
			writestr(s);

		std::this_thread::yield();
	}
}


		
int main()
{
	std::thread t1(read);
	std::thread t2(print);

	t1.join();
	t2.join();


	return 0;
}
