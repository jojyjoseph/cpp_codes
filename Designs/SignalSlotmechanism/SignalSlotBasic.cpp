#include<iostream>
#include<set>
#include<functional>
#include<map>


//fwd declaration
class Signal;
class Slot;

std::multimap<Signal*,Slot*> signalslotmap;

class Slot
{
	public:
		Slot()
		{}
		virtual ~Slot()
		{}

		void operator()(void)
		{
			m_f();
		}

		void execute(){m_f();}
		void assign(std::function<void(void)> f){m_f = f;}

		std::function<void(void)> m_f;
};


class Signal
{
	public:
		Signal()
		{}
		virtual ~Signal()
		{}

		void execute(){m_f();}

		void operator()(void)
		{
			m_f();
			auto range = signalslotmap.equal_range(this);
			
			for(auto it = range.first ; it != range.second ; it++)
			{
				(*it->second)();
			}
		}


		void assign(std::function<void(void)> f){m_f = f;}

		std::function<void(void)> m_f;
};


class ObjectNode
{
	public:
		ObjectNode()
		{}

		virtual ~ObjectNode()
		{}

};

class Object1 : public ObjectNode
{
	public:
		Object1()
		{}
		virtual ~Object1()
		{}

		Signal m_signal1;
		Signal m_signal2;
};

class Object2 : public ObjectNode
{
	public:
		Object2()
		{}
		virtual ~Object2()
		{}

		Slot m_slot1;
		Slot m_slot2;
};

void connect(Signal &signal, Slot &slot)
{
	signalslotmap.insert(std::pair<Signal*,Slot*>(&signal,&slot));
}

int main()
{
	// Create Objects of signal type and slot type
	Object1 * signalObject1	=new Object1;
	Object1 * signalObject2	=new Object1;
	Object2 * slotObject1 	=new Object2;
	Object2 * slotObject2 	=new Object2;

	// initialize the std::function associated with the signal and slot object. Though the function 
	// could have been kept separate from the Signal and Slot classes. The std::functions are associated later
	signalObject1->m_signal1.assign([]()->void{std::cout<<"signal function#1 for signalObject1\n";});
	signalObject1->m_signal2.assign([]()->void{std::cout<<"signal function#2 for signalObject1\n";});
	signalObject2->m_signal1.assign([]()->void{std::cout<<"signal function#1 for signalObject2\n";});
	signalObject2->m_signal2.assign([]()->void{std::cout<<"signal function#2 for signalObject2\n";});

	slotObject1->m_slot1.assign([]()->void{std::cout<<"slot function#1 for slotObject1\n";});
	slotObject1->m_slot2.assign([]()->void{std::cout<<"slot function#2 for slotObject1\n";});
	slotObject2->m_slot1.assign([]()->void{std::cout<<"slot function#1 for slotObject2\n";});
	slotObject2->m_slot2.assign([]()->void{std::cout<<"slot function#2 for slotObject2\n";});

	//connect signal and slots
	connect(signalObject1->m_signal1, slotObject2->m_slot1);	
	connect(signalObject1->m_signal1, slotObject2->m_slot2);	
	connect(signalObject2->m_signal2, slotObject1->m_slot2);
	connect(signalObject2->m_signal1, slotObject2->m_slot1);

	// invoke signals
	signalObject1->m_signal1();
	signalObject2->m_signal1();
	signalObject2->m_signal2();

	return 0;
}
