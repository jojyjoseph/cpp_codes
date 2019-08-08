#include "Derived.h"
#include "Derived_static.h"

#include<string.h>
#include<stdlib.h>
#include<stdio.h>


Derived * newDerived(char *name, int id, char *role)
{
	Derived * d = (Derived*)malloc(sizeof(Derived));

	d->base = *(newBase(name,id));
	
	// update the VirtualOverridenFunction function pointer to the VirtualOverridenFunction function
	d->VirtualOverridenFunction=VirtualOverridenFunction;		//function pointer for the Derived class equal to Derived VirtualOverridenFunction function
	d->base.VirtualOverridenFunction=VirtualOverridenFunction;	//polymorphism function pointer for the Base class equal to Derived VirtualOverridenFunction function
	d->BaseNonVirtualFunction=d->base.BaseNonVirtualFunction;
	strcpy(d->role, role);

	return d;
}
	
static void VirtualOverridenFunction(void * p)
{
	Derived *d = (Derived *) p;
	printf("Derived::VirtualOverridenFunction()\n");
	printf("Derived class - Name : %s, ID : %i, Role : %s\n", d->base.name, d->base.id, d->role);
}




