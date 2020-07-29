#pragma once
#ifndef Ingredient_H
#define Ingredient_H

#include "global.h"
#include "moneyobject.h"

ref class Ingredient :
public MoneyObject
{
	int *remaining;///remaining[the date when we buy this ingredient]
	int deadtime;///the time this ingredient rotten
	int sort;
public:
	Ingredient(void);
	Ingredient(String^ input_name,int input_price,int input_sort,int input_deadtime);
	void setRemaining(int day,int input);
	void addRemaining(int day,int input);
	void subRemaining(int day,int input);	
	int get_remaining(int day);
	int get_deadtime();
	int get_sort();
};

#endif