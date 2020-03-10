#pragma once

#include "WidgetA.h"
#include "WidgetB.h"

struct Page
{
	void * owner;
	Page():
		wa{ 5, 15 }, wb{ 10, 25 }
	{}

	WidgetA wa;
	WidgetB wb;
};

void Page_initialize(Page * page);
void Page_update(Page * page);

int Page_WidgetB_inputProperty(WidgetB * w);
void Page_WidgetB_writer_WidgetA_varA2(WidgetB *w, int value);
void Page_WidgetA_signalA1_default(WidgetA *w);
void Page_WidgetA_signalA2(WidgetA *w);
void Page_WidgetB_slotB1(WidgetB *w);

