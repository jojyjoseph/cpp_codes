#include "Derived.h"
#include "Derived_static.h"

#include<string.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct vtables
{
	void (*VirtualOverridenFunction)(void *p);
	void (*BaseNonVirtualFunction)(void *p);
}_vtable;

static _vtable vtable;

Derived * newDerived(char *name, int id, char *role)
{
	Derived * d = (Derived*)malloc(sizeof(Derived));
	d->base = *(newBase(name,id));
	strcpy(d->role, role);
	d->vtable=&vtable;

	
#ifdef WITH_VTABLE
	// update the vtable of the Derived to the actual functions to be invoked
	
	// virtual overridden functions point to the local static function pointer
	vtable.VirtualOverridenFunction = VirtualOverridenFunction;	
	// non virtual inherited functions point to the vtable of the base
	vtable.BaseNonVirtualFunction =((_vtable *)d->base.vtable)->BaseNonVirtualFunction;
	
	// Update the local function pointers to the vtable. This is the function pointers called by the user.
	d->VirtualOverridenFunction=((_vtable *)d->vtable)->VirtualOverridenFunction;
	d->BaseNonVirtualFunction=((_vtable *)d->vtable)->BaseNonVirtualFunction;
#else

	// update the local function pointers of the Derived to the Actual functions 
	d->VirtualOverridenFunction=VirtualOverridenFunction;		//function pointer for the Derived class equal to Derived VirtualOverridenFunction function
	d->base.VirtualOverridenFunction=VirtualOverridenFunction;	//polymorphism function pointer for the Base class equal to Derived VirtualOverridenFunction function
	d->BaseNonVirtualFunction=d->base.BaseNonVirtualFunction;
#endif
	return d;
}
	
static void VirtualOverridenFunction(void * p)
{
	Derived *d = (Derived *) p;
	printf("Derived::VirtualOverridenFunction()\n");
	printf("Derived class - Name : %s, ID : %i, Role : %s\n", d->base.name, d->base.id, d->role);
}




