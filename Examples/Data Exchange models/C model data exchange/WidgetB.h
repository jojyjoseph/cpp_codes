#pragma once


struct WidgetB
{
	void * owner;

	WidgetB(int b1, int b2)
		:varB1{b1}, varB2{b2}
	{}

	// input function pointer
	int(*input)(WidgetB *w);

	// writer function pointer
	void(*writer)(WidgetB * w, int value);

	// Slot
	void (*SlotSignalB1)(WidgetB *w);

	// variable
	int varB1;
	int varB2;
};

void WidgetB_initialize(WidgetB *w);
void WidgetB_update(WidgetB * w);
int WidgetB_Output_varB1(WidgetB * w);
void WidgetB_internalFunc1(WidgetB * w);
void WidgetB_SlotSignalB1(WidgetB * w);

