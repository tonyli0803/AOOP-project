#pragma once
#ifndef Warehouse_H
#define Warehouse_H

#include"Ingredient.h"
#include"Tool.h"
#include"Decoration.h"
#include"Recipe.h"
#include<fstream>
#include<iomanip>
using namespace System::IO;
ref class Warehouse :
public NameObject
{
	int currentday;//currentday ����@�Ӧb�ܮw��K�p�� �i�H�Q�� �ܮw�̭����\��� ��o���ثe���ĴX�� 
	int currenthour;
	int currentminute;
	int fund;
	int *served_customer;//�y���H�Ƥ��]�t�b��
	int toolNumber;///for Max number restriction
	int decorationNumber;///for Max number restriction
	int location;//�}���a�I
	int *customer_count;//�]�t�y���H��
	int prefund;//�O���e�@�Ѹ��

	int *enemyfund;//��L���a����� �@�@�|�� �����a�I�s��

	int recipeN_forpay;//��鴿�]�m�L�̦h�����ƶq
	int recipeN_current;//�ثe�]�m�����ƶq

	bool data_updateflag;//�i�Dform1�O�_�ӧ�s��warehouse�����

	array<Ingredient ^>^ ingredient;
	array<Tool ^>^ tool;
	array<Decoration ^>^ decoration;
	array<Recipe ^>^ recipe;
public:
	Warehouse(void);
	/*��l�ƨ��*/
	void initial();
	void reseting(int targetarrary[]);//����Ƥ����ӳQ�~���I�s �Ȩ�initial()�ϥ� 
	void resettool(bool targetarrary[]);//����Ƥ����ӳQ�~���I�s �Ȩ�initial()�ϥ� 

	Ingredient^  getIngredient(int Type);
	Tool^  getTool(int Type);
	Decoration^  getDecoration(int Type);
	Recipe^  getRecipe(int Type);

	int getFund();
	int getLocation();
	void setLocation(int input);

	void addCustomer_count(int ID);
	int getCustomer_count(int ID);
	void setFund(int inputFund);
	void addFund(int increment);
	void subFund(int consume);
 	
 	bool setRecipe(int Type);/*�]�m��� �|�ˬd�����]�ƬO�_�֦�*/

 	bool resetRecipe(int Type);/*�M�U��� ���������ˬd*/ 
 	
	bool sell_Food(int Type);
	bool examine_ingredient(int Type);/*���\�I�e�Ψ��ˬd��ƬO�_���������  const */
	
	bool sell_Tool(int Type);
	
	bool sell_Decoration(int Type);
	
	bool buy_ingredient(int Type,int number);
	bool buy_Tool(int Type);
	bool buy_Decoration(int Type);	

	int getDay();
	int getMinute();
	int getHour();
	int getServed_customer(int day);
	void addServed_customer(int day);
	void setDay(int day);
	void setHour(int hour);
	void setMinute(int minute);

	int getRecipeN_forpay();
	int getRecipeN_current();
	void setRecipeN_forpay(int input);
	void setRecipeN_current(int input);

	bool getData_updateflag();
	void setData_updateflag(bool input);

	int getPrefund();
	void setPrefund(int input);

	int getCookpay();//���o���p�v����

	void addEnemyfund(int Type);//�ھڶ�J���U�Ⱥ����A�M�w�n�W�[���@�ӼĤ話�a����� �H�Υ[�h��
	int getEnemyfund(int enemytype);
	
	void ingredient_dead();//�B�z�L������


	/*�s�ɬ������*/
	void save(int target);
	void load(int source);
};
#endif
