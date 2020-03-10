#include "WidgetB.h"
#include "Page.h"

#include<iostream>

// dummy No operation function in case if nothing is connected to the writer
void WidgetB_writer_Noop(WidgetB * w, int value)
{
	;
}

void WidgetB_initialize(WidgetB * w)
{
	/*
	 * Widget writer is iniitialized to the default function which can be overridden by the parent/owner
	 */
	w->writer = WidgetB_writer_Noop;

	std::cout << "WidgetB initialize\n";
	/*
	 *Slot signal initialization
	 * internal to the widget, the slot may invoke a number of function, all the 
	 */
	w->SlotSignalB1=WidgetB_internalFunc1;

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

void WidgetB_internalFunc1(WidgetB * w)
{
	std::cout<<"Internal WidgetB function\n";
}

void WidgetB_SlotSignalB1(WidgetB * w)
{
	WidgetB_internalFunc1(w);
}



