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
	int currentday;//currentday 先放一個在倉庫放便計算 可以想成 倉庫裡面有擺日歷 能得知目前為第幾天 
	int currenthour;
	int currentminute;
	int fund;
	int *served_customer;//流失人數不包含在內
	int toolNumber;///for Max number restriction
	int decorationNumber;///for Max number restriction
	int location;//開店地點
	int *customer_count;//包含流失人數
	int prefund;//記錄前一天資金

	int *enemyfund;//其他店家的資金 一共四個 對應地點編號

	int recipeN_forpay;//當日曾設置過最多的菜單數量
	int recipeN_current;//目前設置的菜單數量

	bool data_updateflag;//告訴form1是否該更新成warehouse的日期

	array<Ingredient ^>^ ingredient;
	array<Tool ^>^ tool;
	array<Decoration ^>^ decoration;
	array<Recipe ^>^ recipe;
public:
	Warehouse(void);
	/*初始化函數*/
	void initial();
	void reseting(int targetarrary[]);//此函數不應該被外部呼叫 僅供initial()使用 
	void resettool(bool targetarrary[]);//此函數不應該被外部呼叫 僅供initial()使用 

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
 	
 	bool setRecipe(int Type);/*設置菜單 會檢查相關設備是否擁有*/

 	bool resetRecipe(int Type);/*撤下菜單 不做任何檢查*/ 
 	
	bool sell_Food(int Type);
	bool examine_ingredient(int Type);/*賣餐點前用來檢查原料是否足夠的函數  const */
	
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

	int getCookpay();//取得當日廚師成本

	void addEnemyfund(int Type);//根據填入的顧客種類，決定要增加哪一個敵方店家的資金 以及加多少
	int getEnemyfund(int enemytype);
	
	void ingredient_dead();//處理過期食材


	/*存檔相關函數*/
	void save(int target);
	void load(int source);
};
#endif
