/*
 *
 * Data exchange has push and pull data model.
 * Widget B pulls the data into varB1.
 * Widget B pushs the data from varB2.
 * See WidgetB.cpp update function for more details.
 */

#include<iostream>
#include "Page.h"

int main()
{
	/*
	 *	Page
	 *	|-- WidgetA (child 1)
	 *	|-- WidgetB (child 2)
	 *
	 */
	Page p;

	/*
	 * initializes self and child recursively
	 */
	Page_initialize(&p);

	/*
	 * updates invokes self update and child update.
	 */
	Page_update(&p);
}
