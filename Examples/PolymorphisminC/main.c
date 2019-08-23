
#include "Base.h"
#include "Derived.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	Base * b1 	= newBase("BaseClass1", 101);
	Derived *d1 	= newDerived("DerivedClass1", 201, "Derived Role");

	b1->VirtualOverridenFunction(b1);
	d1->VirtualOverridenFunction(d1);

	Base *b2 = (Base*)d1;
	b2->VirtualOverridenFunction((Base*)d1);

	b2->BaseNonVirtualFunction(b2);
	d1->BaseNonVirtualFunction(d1);



	return 0;
}
