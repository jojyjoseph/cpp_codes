/*
* Shared pointer implementation example
* Shared pointer allows copying of Smartpointer. Thus unlink unique_ptr, SharedPointers can have multiple copies.
* On the destruction of the last existing SharedPointer, the resource is freed.
* SharedPointer has an extra Control Block for its implemented.
*/

#include <iostream>

template<typename T>
class ControlBlock
{
public:
	ControlBlock(T * t)
		:m_pointer{ t }, m_count{ 1 }
	{
		std::cout << "Control Block created\n";
	}

	int getCount() { return m_count; }
	void increaseCount() { m_count++; }
	void decreaseCount() { m_count--; }

	virtual ~ControlBlock()
	{
		std::cout << "Control Block destroyed\n";
	}

	T* getPointer() { return m_pointer; }
	
private:
	T* m_pointer;
	int m_count;
};

template<typename T>
class SharedPointer
{
public:
	SharedPointer(T* t)
		:m_cb{new ControlBlock<T>{t}}
	{
		std::cout << "New Shared Pointer created\n";
	}

	SharedPointer(SharedPointer<T> & sp)
	{
		std::cout << "SharedPointer copy constructor\n";
		m_cb = sp->getControlBlock();
		m_cb->increaseCount();
	}

	SharedPointer<T>* operator->() { return this; }

	ControlBlock<T>* getControlBlock()
	{
		return m_cb;
	}

	virtual ~SharedPointer()
	{
		std::cout << "Shared POinter destroyed\n";
		m_cb->decreaseCount();
		if (m_cb->getCount() == 0)
		{
			delete m_cb->getPointer();
			delete m_cb;
		}
	}

private:
	ControlBlock<T>* m_cb;

};

class X {
public:
	X() { std::cout << "X created\n"; }

	virtual ~X() { std::cout << "X destroyed\n"; }
};

int main()
{
	{
		SharedPointer<X> sp(new X{});

		SharedPointer<X> sp1{ sp };
	}
	
	return 0;
}