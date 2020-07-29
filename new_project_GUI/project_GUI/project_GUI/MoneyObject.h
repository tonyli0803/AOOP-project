#pragma once
#ifndef MoneyObject_H
#define MoneyObject_H

#include "nameobject.h"
ref class MoneyObject :
public NameObject
{
	int price;
public:
	MoneyObject(void);
	MoneyObject(int input_price);
	MoneyObject(String^ name,int input_price);
	void setPrice(int input_price);
	int getPrice(void);
};

#endif