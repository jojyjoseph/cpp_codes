#include "WidgetA.h"

#include<iostream>

void WidgetA_initialize(WidgetA * w)
{
	std::cout << "WidgetA initialize\n";
}

void WidgetA_update(WidgetA * w)
{
	w->signalA1(w);
	w->signalA2(w);
	std::cout << "WidgetA updated\n";
}

int widgetA_output(WidgetA * w)
{
	return w->varA1;
}

void WidgetA_setVarA2(WidgetA * w, int value)
{
	w->varA2 = value;
}
