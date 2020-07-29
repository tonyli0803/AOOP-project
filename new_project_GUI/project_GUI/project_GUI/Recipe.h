#pragma once
#ifndef Recipe_H
#define Recipe_H

#include "global.h"
#include "moneyobject.h"

ref class Recipe :
public MoneyObject
{
	int *ingredient_Demand;//[INGREDIEDNT_TYPE_MAX];//what ingredient we needs to make it
	bool *toolDemand;//[TOOL_TYPE_MAX];//what tools we needs to make it
	int sort;	
	int count;//餐點被點次數
	bool exist;
public:
	Recipe(void);
	Recipe(String^ input_name,int input_price, int input_sort,bool exist,int ing[INGREDIEDNT_TYPE_MAX],bool tool[TOOL_TYPE_MAX]);
	int getSort();
	void set_ingredient_Demand(int type,int input);//ingredientDemand[]	
	int get_ingredient_Demand(int type);
	void set_tool_Demand(int type,bool input);
	bool get_tool_Demand(int type);
	bool getExist();
	int getCount();
	void addCount();
	void setExist(bool input_state);
};
#endif
