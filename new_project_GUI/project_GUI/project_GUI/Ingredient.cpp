#include "StdAfx.h"
#include "Ingredient.h"

Ingredient::Ingredient(void){
	remaining = new int[DAY_MAX+1];
	sort=0;
	deadtime=0;
	for(int i=0;i<DAY_MAX+1;i++){
		remaining[i]=0;
	}
}
Ingredient::Ingredient(String^ input_name,int input_price,int input_sort,int input_deadtime):MoneyObject(input_name,input_price)
{
	remaining = new int[DAY_MAX+1];
	sort=input_sort;
	deadtime=input_deadtime;
	for(int i=0;i<DAY_MAX+1;i++){
		remaining[i]=0;
	}
}
void Ingredient::setRemaining(int day,int input){
	remaining[day]=input;
}
void Ingredient::addRemaining(int day,int input){
	remaining[day]+=input;
}
void Ingredient::subRemaining(int day,int input){
	remaining[day]-=input;
}

int Ingredient::get_remaining(int day){
	return remaining[day];///attention !!! our first day start from <<remaining[1]>>   n-th day == remaining [0+n]
}

int Ingredient::get_deadtime(){
	return deadtime;
}

int Ingredient::get_sort(){
	return sort;
}
