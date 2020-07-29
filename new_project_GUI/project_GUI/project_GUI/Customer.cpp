#include "StdAfx.h"
#include "Customer.h"

Customer::Customer(void)
{
	/*identity = 0;
	decision = 0;
	count = 0;
	name = "Willy";*/
}

Customer::Customer(int location)
{

	decision = new int[2];
	/// summation is 20 for a location   學校 體育館 百貨公司 醫院
	int key_person[id_amount][location_num]={	{3,1,3,2},
					 				   			{2,2,2,2},
					 				   			{1,2,2,5},
					 							{1,6,1,1},
					 							{5,2,4,1},
					 							{3,2,4,2}};
					 							
	int i, j, sum=0, spot;
	
	
	int favor[menu_amount][id_amount]={	{ 10, 10, 10, 10, 10, 10},
										{ 10, 10, 10, 10, 10, 10},
										{ 10, 10, 10, 10, 10, 10},
										{ 10, 10, 10, 10, 10, 10},
										{ 10, 10, 10, 10, 10, 10},
										{ 10, 10, 10, 10, 10, 10},
										{ 10, 10, 10, 10, 10, 10},
										{ 10, 10, 10, 10, 10, 10},
										{ 10, 10, 10, 10, 10, 10},
										{ 10, 10, 10, 10, 10, 10},
										{ 10, 10, 10, 10, 10, 10},
										{ 10, 10, 10, 10, 10, 10},
										{ 10, 10, 10, 10, 10, 10},
										{ 10, 10, 10, 10, 10, 10},
										{ 10, 10, 10, 10, 10, 10},
										{ 10, 10, 10, 10, 10, 10},
										{ 10, 10, 10, 10, 10, 10},
										{ 10, 10, 10, 10, 10, 10},
										{ 10, 10, 10, 10, 10, 10},
										{ 10, 10, 10, 10, 10, 10},
										{ 10, 10, 10, 10, 10, 10},
										{ 10, 10, 10, 10, 10, 10},
										{ 10, 10, 10, 10, 10, 10},
										{ 10, 10, 10, 10, 10, 10},
										{ 10, 10, 10, 10, 10, 10},
										{ 5,  10, 5, 5, 5, 5},
										{ 5,  10, 5, 5, 5, 5},
										{ 5,  10, 5, 5, 5, 5},
										{ 5,  10, 5, 5, 5, 5},
										{ 5,  10, 5, 5, 5, 5}};
					 					 
	int top10[6][30] = {{24,23,22,21,20,49,48,47,46,45,74,73,72,71,70,99,98,97,96,95,94,16,17,18,20,21,22, 7, 8, 6},
						{ 5, 6, 7, 8, 9,30,31,32,33,34,80,81,82,83,84,55,56,57,58,59,39,89,64,94,95, 0,25,75,50,77},
						{30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,88,89,90,82,83,84,66,67,68,69,29,28,27,26,25},
						{80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,38,39,40,30,31,32,10,11,12,16,79,78,77,76,75},
						{55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,91,92,93,94,35,36,37,38,88,89,54,53,52,51,50},
						{ 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,55,56,57,58, 5, 6, 7, 8, 5, 6, 4, 3, 2, 1, 0}};
//identity	
	
	for(i = 0;i < id_amount;i++)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
		sum+=key_person[i][location];
	
	spot = rand()%sum +1;
	i = 0;
	while((spot > 0)&&(i < id_amount))
	{		
		spot-=key_person[i][location];
		i++;
	}
	identity = i - 1;
	sum = 0;
	spot = 0;
//decision 1
	
	for(i = 0;i < menu_amount;i++)
		sum+=favor[i][identity];
	
	spot = rand()%sum +1;
	i = 0;
	while((spot > 0)&&(i < menu_amount))
	{
		spot-=favor[i][identity];
		i++;		
	}
	decision[0] = i - 1;	

	/*
	sum = 0;
	spot = 0;
	*/	

	///////
	count = 1;
	
	//提取正確菜單 
	decision[0]=top10[identity][decision[0]];

		
	//設定顧客名稱
	set_ID(identity);
}

//回傳客人的ID 
int Customer::get_ID()
{
	return identity;
}

//回傳客人餐點 
int Customer::get_Decision()
{
	return decision[0];
}
int Customer::get_Decision2()
{
	return decision[1];
}
void Customer::set_ID(int id){
	identity=id;
	switch(identity){
		case 0:
			setName("小學生");
			break;
		case 1:
			setName("老師");
			break;
		case 2:
			setName("醫生");
			break;
		case 3:
			setName("運動員");
			break;
		case 4:
			setName("高中生");
			break;
		case 5:
			setName("媽媽");
			break;
	}
};
int Customer::get_Count()
{
	return count;
}

