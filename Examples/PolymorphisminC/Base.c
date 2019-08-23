#include "Base.h"
#include "Base_static.h"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


typedef struct vtables
{
	void (*VirtualOverridenFunction)(void *p);
	void (*BaseNonVirtualFunction)(void *p);
}_vtable;

static _vtable vtable;

// new Base
Base * newBase(char * name, int id)
{
	Base * b = (Base*)malloc(sizeof(Base));
	strcpy(b->name, name);
	b->id=id;
	b->vtable=&vtable;

#ifdef WITH_VTABLE
	//Update the local function pointers in Base to vtable of the Base object
	vtable.VirtualOverridenFunction = VirtualOverridenFunction;
	vtable.BaseNonVirtualFunction = BaseNonVirtualFunction;

	// update vtable to the actual function pointers
	b->VirtualOverridenFunction=((_vtable *)b->vtable)->VirtualOverridenFunction;
	b->BaseNonVirtualFunction=((_vtable *)b->vtable)->BaseNonVirtualFunction;
#else
	// Update the local function pointers to Actual function pointers
	b->VirtualOverridenFunction=VirtualOverridenFunction;
	b->BaseNonVirtualFunction=BaseNonVirtualFunction;
#endif
	return b;
}

//member function which can be called by Base and Derivative
static void VirtualOverridenFunction(void *p)
{
	Base * base = (Base*) p;
	printf("Base::VirtualOverridenFunction()\n");
	printf("Name : %s. ID : %i\n",base->name, base->id);
}

static void BaseNonVirtualFunction(void *p)
{
	Base * base = (Base*)p;
	printf("Base::BaseNonVirtualFunction(void *p)\n");
}
