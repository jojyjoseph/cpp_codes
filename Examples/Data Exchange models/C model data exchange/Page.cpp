#include"Page.h"
#include "WidgetA.h"
#include "WidgetB.h"

#include<iostream>

void Page_initialize(Page * page)
{
	std::cout << "Page initialize\n";
	page->wa.owner = page;
	page->wb.owner = page;
	page->wb.input = Page_WidgetB_inputProperty;
	page->wb.writer = Page_WidgetB_writer_WidgetA_varA2;
	WidgetA_initialize(&page->wa);
	WidgetB_initialize(&page->wb);
}

void Page_update(Page * page)
{
	std::cout << "Page updated\n";
	WidgetA_update(&page->wa);
	WidgetB_update(&page->wb);
}

int Page_WidgetB_inputProperty(WidgetB * w)
{
	Page * page = (Page *) w->owner;
	return widgetA_output(&page->wa);
}

void Page_WidgetB_writer_WidgetA_varA2(WidgetB *w, int value)
{
	Page * page = (Page *)w->owner;
	WidgetA_setVarA2(&page->wa, value);
}