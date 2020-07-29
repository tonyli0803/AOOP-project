#pragma once
#ifndef Decoration_H
#define Decoration_H

#include "moneyobject.h"
ref class Decoration :
public MoneyObject
{
	bool exist;
	int sort;
public:
	Decoration(void);
	Decoration(String^ input_name,int input_price, int input_sort,bool input_exist);
	///use default copy assignment ( because there is no pointer XD )
	bool getExist();
	int getSort();
	void setExist(bool input_state);
};
#endif

