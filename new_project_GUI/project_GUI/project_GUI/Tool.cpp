#include "StdAfx.h"
#include "Tool.h"

Tool::Tool(void){
	exist = false;
	sort = 0;
}
Tool::Tool(String^ input_name,int input_price, int input_sort,bool input_exist):MoneyObject(input_name,input_price)	
{
	exist=input_exist;
	sort=input_sort;
}
bool Tool::getExist(void){
	return exist;
}
int Tool::getSort(void){
	return sort;
}

void Tool::setExist(bool input_state){
	exist=input_state;
}