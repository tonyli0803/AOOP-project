#pragma once
#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "nameobject.h"
#include "global.h"
#include <time.h>
#include <stdlib.h>

ref class Customer :
public NameObject
{
	int identity;//1. student 2. Teacher 3. The rich 4. The poor 5. The young(age under 5) 6. Housekeeper(mostly are women) 7. Engineer 8. people in Israel 9. boss 10. professor
	int *decision;//choose from menu
	int count;//�M�w�n�I�X�D�� �i�ର1��2
public:
	Customer(void);
	Customer(int);

	int get_Decision();
	int get_Decision2();

	void set_ID(int id);//�Ψӱj��]�wid
	//void show_Decision();
		
	//void set_Menu_N_ID();

	//void show_Menu();		
		
	int get_Count();
	int get_ID();
};

#endif