#ifndef _DERIVED_H_
#define _DERIVED_H_

#include "Base.h"

typedef struct Derived
{
	// parent clas
	Base base;
	
	// member function
	void (*VirtualOverridenFunction)(void*);
	void (*BaseNonVirtualFunction)(void *);
	
	// member variables
	char role[20];
}Derived;

Derived * newDerived(char *name, int id, char *role);

#endif
