#include<iostream>
#include<string>
#include<vector>
#include<type_traits>

class Variant
{
	public:

		Variant(){}

		Variant(int value)
			:
			m_pointer{new int{value}}, 
			m_TypeEnum{Type::Int},
			m_type{"int"}
		{}
		
		Variant(float value)
			:
			m_pointer{new float{value}}, 
			m_TypeEnum{Type::Float},
			m_type{"float"}
		{}

		Variant(std::string str)
			:
			m_pointer{new std::string{str}}, 
			m_TypeEnum{Type::String},
			m_type{"std::string"}
		{}

		enum Type
		{
			Invalid,
			Userdefined,
			Int,
			Float,
			String
		};

		void clear()
		{
			switch(m_TypeEnum)
			{
				case Type::Int:
					delete (int *)m_pointer;
					break;

				case Type::Float:
					delete (float *)m_pointer;
					break;

				case Type::String:
					delete (std::string *)m_pointer;
					break;

				case Type::Userdefined:
					break;

				case Type::Invalid:
					break;
			}
		}

		int toInt()
		{
			if (m_TypeEnum == Type::Int)
			{
				return *((int*)m_pointer);
			}
			return 0;
		}

		float toFloat()
		{
			if (m_TypeEnum == Type::Float)
			{
				return *((float *)m_pointer);
			}

			return float();
		}

		template<typename T>
		T value()
		{
			if(std::is_same<T,int>::value)
				return *((T *)m_pointer);
			else if (std::is_same<T,float>::value)
				return *((T *)m_pointer);
			else if(std::is_same<T,std::string>::value)
			{
				return *((T *)m_pointer); 
			}
			else
				return T{};
		}
			
			
		std::string toString()
		{
			if (m_TypeEnum == Type::String)
			{
				return *((std::string *)m_pointer);
			}

			return std::string();
		}

		Variant::Type type() const
		{
			return m_TypeEnum;
		}



	private:
		void * 	m_pointer{nullptr};
		Type	m_TypeEnum{Invalid};
		std::string m_type;
};

int main()
{
	Variant v1{int{111}}, v2{float{1}}, v3{std::string{"String"}};
	
	std::cout<<"v1 to int :"<<v1.toInt()<<'\n';
	std::cout<<"v1 to float : "<<v1.toFloat()<<'\n';
	std::cout<<"v3 to string :"<<v3.toString()<<'\n';
	std::cout<<"v2 to string : "<<v2.toString()<<'\n';

	v1.type();

	std::cout<<"v1 value :"<<v1.value<int>()<<"\n";

	return 0;
}
