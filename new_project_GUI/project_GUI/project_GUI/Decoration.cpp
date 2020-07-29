#include "StdAfx.h"
#include "Decoration.h"

Decoration::Decoration(void){
	exist = false;
	sort = 0;
}
Decoration::Decoration(String^ input_name,int input_price, int input_sort,bool input_exist):MoneyObject(input_name,input_price)
{
	exist=input_exist;
	sort=input_sort;
}
bool Decoration::getExist(){
	return exist;
}
int Decoration::getSort(){
	return sort;
}
void Decoration::setExist(bool input_state){
	exist=input_state;
}
