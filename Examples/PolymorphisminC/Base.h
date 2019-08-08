#ifndef _BASE_H_
#define _BASE_H_

typedef struct Base
{
	char 	name[20];
	int 	id;

	// member functions as funcion pointers
	void (*VirtualOverridenFunction)(void *);
	void (*BaseNonVirtualFunction)(void *);
}Base;

// new operator equivalent for Base
Base * newBase(char *name, int id);

void init_Base(Base *base, char *name, int id);

#endif
