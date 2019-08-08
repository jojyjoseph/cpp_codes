#include "Base.h"
#include "Base_static.h"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


// new Base
Base * newBase(char * name, int id)
{
	Base * b = (Base*)malloc(sizeof(Base));
	strcpy(b->name,name);
	b->id=id;

	b->VirtualOverridenFunction=VirtualOverridenFunction;
	b->BaseNonVirtualFunction=BaseNonVirtualFunction;

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
