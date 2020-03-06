#pragma once


struct WidgetA
{
	void * owner;

	WidgetA(int a1, int a2)
		:varA1(a1), varA2{a2}
	{}

	// member variable
	int varA1;

	int varA2;

	// input function pointer
	int(*input)(WidgetA * w);
};

void WidgetA_initialize(WidgetA * w);
void WidgetA_update(WidgetA * w);

int widgetA_output(WidgetA * w);
void WidgetA_setVarA2(WidgetA * w, int value);