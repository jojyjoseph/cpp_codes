#ifndef _BASE_H_
#define _BASE_H_

#define WITH_VTABLE

typedef struct Base
{
	char 	name[20]; // member variable
	int 	id;	//member variable
	void * vtable;	// pointer to vtable

	// member functions as funcion pointers - this is what is called by the user.
	void (*VirtualOverridenFunction)(void *);
	void (*BaseNonVirtualFunction)(void *);
}Base;

// new operator equivalent for Base
Base * newBase(char *name, int id);

void init_Base(Base *base, char *name, int id);

#endif
