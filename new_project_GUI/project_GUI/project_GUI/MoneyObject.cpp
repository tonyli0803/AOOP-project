#include "StdAfx.h"
#include "MoneyObject.h"

MoneyObject::MoneyObject(void){
	price=0;
}

MoneyObject::MoneyObject(int intput_price){
	price=intput_price;
}

MoneyObject::MoneyObject(String^ name,int input_price):NameObject(name)
{
	price=input_price;
}

int MoneyObject::getPrice(void){
	return price;
}

void MoneyObject::setPrice(int input_price){
	price=input_price;
}