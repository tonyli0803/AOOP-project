#include "StdAfx.h"
#include "NameObject.h"

NameObject::NameObject(void){
	name="";
}
NameObject::NameObject(String^ input_name){
	name=input_name;
}
String^ NameObject::getName(void){
	return name;
}
void NameObject::setName(String^ input_name){
	name=input_name;
}