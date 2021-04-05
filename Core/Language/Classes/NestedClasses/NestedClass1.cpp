#include<iostream>

template<typename T>
class EnclosingClass{
	public:
		// Member Class
		class NestedClass{
			public:
				T v;

				NestedClass(T _v)
					:v{_v}
				{}

				virtual ~NestedClass(){}

				void NC_mf(EnclosingClass *ec){
					// add
					std::cout<<
						//(v + m_v) -- m_v can't be refered directly
						v + ec->m_v	// can only be refered
						<<"\n";
				}
		};


		// Ctor
		EnclosingClass(T t1, T t2)
			:m_v{t1}, m_nc{t2}
		{}

		virtual ~EnclosingClass()
		{}

		// Member function
		void invoke_NC_mf(){
			m_nc.NC_mf(this);	// Lesson : need to pass Enclosing class pointer of self or other object
		}

		void EC_mf(){
			std::cout<<
				// v - Can't access Nested class members
				m_nc.v
				<<"\n";
		}


	private:
		using value_type=T;

		// member variable
		T m_v;

		NestedClass m_nc;
};

int main()
{
	EnclosingClass<int> ec{1, 2};
	ec.invoke_NC_mf();
	ec.EC_mf();
	return 0;
}

