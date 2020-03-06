#include "WidgetB.h"
#include "Page.h"

#include<iostream>

void WidgetB_initialize(WidgetB * w)
{
	std::cout << "WidgetB initialize\n";
}

void WidgetB_update(WidgetB * w)
{
	std::cout << "WidgetB updated\n";

	// pull effect
	std::cout << "Initial varB1 " << w->varB1 << " ,";
	/*
	 * pull effect
	 * Data is pulled from whatever is connected to the input node(function pointer). Thus this can be changed dynamically. WidgetA pulls data from any suitable output node connected to it. The connection information lies with the parent.
	 */
	w->varB1 = w->input(w);
	std::cout << "Updated varB1 " << w->varB1 << "\n";

	/*
	 * push effect
	 * Data is pushed from the current widget variable to whatever is connected to the writer. writer is a function pointer (push node) which can be connected to anything appropriate. The parent knows who is connected to the writer. Thus the data is pushed from widgetA to WidgetB without widget A knowing implicitely who is connected to it.
	 */
	w->writer(w, w->varB2);
}

int WidgetB_Output_varB1(WidgetB * w)
{
	return w->varB1;
}


