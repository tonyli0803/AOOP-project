#include "StdAfx.h"
#include "Recipe.h"

Recipe::Recipe(void){
	ingredient_Demand = new int[INGREDIEDNT_TYPE_MAX];
	toolDemand = new bool[TOOL_TYPE_MAX];
	sort=0;
	count=0;
	for(int i=0;i<INGREDIEDNT_TYPE_MAX;i++)		ingredient_Demand[i]=0;
	for(int i=0;i<TOOL_TYPE_MAX;i++)				toolDemand[i]=false;
}
Recipe::Recipe(String^ input_name,int input_price, int input_sort,bool exist,int ing[INGREDIEDNT_TYPE_MAX],bool tool[TOOL_TYPE_MAX]):MoneyObject(input_name,input_price)
{
	ingredient_Demand = new int[INGREDIEDNT_TYPE_MAX];
	toolDemand = new bool[TOOL_TYPE_MAX];
	sort=input_sort;
	count=0;
	this->exist=exist;
	for(int i=0;i<INGREDIEDNT_TYPE_MAX;i++)		ingredient_Demand[i]=ing[i];
	for(int i=0;i<TOOL_TYPE_MAX;i++)				toolDemand[i]=tool[i];
}

int Recipe::getSort(void){
	return sort;
}
void Recipe::set_ingredient_Demand(int type,int input){
	ingredient_Demand[type]=input;
}
int Recipe::get_ingredient_Demand(int type){
	return ingredient_Demand[type];
}
void Recipe::set_tool_Demand(int type,bool input){
	toolDemand[type]=input;
}
bool Recipe::get_tool_Demand(int type){
	return toolDemand[type];
}
int Recipe::getCount(){
	return count;
}
void Recipe::addCount(){
	count++;
}
void Recipe::setExist(bool input_state){
	exist=input_state;
}
bool Recipe::getExist(void){
	return exist;
}