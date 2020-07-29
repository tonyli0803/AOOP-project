#pragma once
#ifndef NameObject_H
#define NameObject_H
#include<iostream>
using namespace std;
using namespace System;

ref class NameObject
{
	String^ name;
public:
	NameObject(void);
	NameObject(String^ input_name);
    String^ getName(void);
	void setName(String^ input_name);
};
#endif

