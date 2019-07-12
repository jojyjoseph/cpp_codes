#include<iostream>
#include<memory>


class X
{
	public:
		X(int i):m_i{i}{std::cout<<"X created\n";}
		~X(){std::cout<<"X destroyed\n";}

		std::shared_ptr<X> getSharedPtr()
		{
			if(m_ref.expired())
			{
				auto p=std::shared_ptr<X>(this);
				std::cout<<"weak pointer is in expired state - expired() = true\n";
				m_ref=p;
				return p;
			}
			else
			{
				std::cout<<"weak pointer is linked to an instance - Locked\n";
				return m_ref.lock();
			}
		}

		void show()
		{
			std::cout<<"X::show() , i : "<<m_i<<std::endl;
		}


	private:
		std::weak_ptr<X> m_ref;
		int m_i;
};

int main()
{
	auto xp=new X(4);
	xp->show();
	
	{
		std::shared_ptr<X> xs1=xp->getSharedPtr();
		xs1->show();

		std::shared_ptr<X> xs2=xs1->getSharedPtr();
		xs2->show();

	}
	
	if(xp)
	{
		std::cout<<"Raw pointers shows existence and thus dangerous to use raw pointers as it's not defined behaviour";
		xp->show();
	}


	std::cout<<"Program end\n";
	return 0;
}

