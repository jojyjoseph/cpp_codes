#include<iostream>

/*
 * Example using anonymous union to merge function pointer array with function pointers structs
 *
 * Advantage - function pointer array can be loop and individual function pointers can be assigned as needed
 */

// function declaration
void DummyStart(void);
void DummyUpdate(void);
void DummyRender(void);
void DummyWait(void);
void DummyEnd(void);


// Type def the function pointer
using funcPointer = void(*)(void);

struct X
{
	int var1;
	int var2;

	union
	{
		funcPointer op[5];
		
		struct
		{
			void(*start)(void);
			void(*update)(void);
			void(*render)(void);
			void(*wait)(void);
			void(*end)(void);
		};
	};
};

int main()
{
	X x;

	// initialize the function pointers
	x.start=DummyStart;
	x.update=DummyUpdate;
	x.render=DummyRender;
	x.wait=DummyWait;
	x.end=DummyEnd;

	// call the function pointer array
	for(int y=0 ; y<5 ; y++)
	{
		x.op[y]();
	}

	return 0;
}



// Dummy function definitions
void DummyStart(void)
{
	std::cout<<"Dummy Start\n";
}

void DummyUpdate(void)
{
	std::cout<<"Dummy Update\n";
}

void DummyRender(void)
{
	std::cout<<"Dummy Render\n";
}

void DummyWait(void)
{
	std::cout<<"Dummy Wait\n";
}

void DummyEnd(void)
{
	std::cout<<"Dummy End\n";
}


