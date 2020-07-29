#pragma once
#ifndef Tool_H
#define Tool_H

#include "moneyobject.h"
ref class Tool :
public MoneyObject
{
	bool exist;
	int sort;
public:
	Tool(void);
	Tool(String^ input_name,int input_price, int input_sort,bool input_exist);
	///use default copy assignment ( because there is no pointer XD ) 	
	bool getExist(void);
	int getSort(void);
	void setExist(bool input_state);
};
#endif
