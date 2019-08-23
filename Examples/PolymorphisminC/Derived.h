#ifndef _DERIVED_H_
#define _DERIVED_H_

#include "Base.h"

typedef struct Derived
{
	// parent class
	Base base; 

	void *vtable;// pointer to vtable
	
	// member function
	void (*VirtualOverridenFunction)(void*);
	void (*BaseNonVirtualFunction)(void *);
	
	// member variables for Derived
	char role[20];
}Derived;

Derived * newDerived(char *name, int id, char *role);

#endif
