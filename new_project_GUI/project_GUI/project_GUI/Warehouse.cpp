#include "StdAfx.h"
#include "Warehouse.h"

Warehouse::Warehouse(void){///maybe we'll type every data here!!!

	ingredient = gcnew array<Ingredient ^>(INGREDIEDNT_TYPE_MAX);
	for(int i=0;i<INGREDIEDNT_TYPE_MAX;i++)
		ingredient[i]=gcnew Ingredient();
	tool = gcnew array<Tool ^>(TOOL_TYPE_MAX);
	for(int i=0;i<TOOL_TYPE_MAX;i++)
		tool[i]=gcnew Tool();
	decoration = gcnew array<Decoration ^>(DECORATION_TYPE_MAX);
	for(int i=0;i<DECORATION_TYPE_MAX;i++)
		decoration[i]=gcnew Decoration();
	recipe = gcnew array<Recipe ^>(RECIPE_TYPE_MAX);
	for(int i=0;i<RECIPE_TYPE_MAX;i++)
		recipe[i]=gcnew Recipe();
	setName("�²��\�]");
	fund=0;
	toolNumber=0;
	decorationNumber=0;
	currentday=1;
	currenthour=9;
	currentminute=0;
	data_updateflag=false;
	toolNumber=0;
	location=0;
	customer_count = new int[id_amount];
	for(int i=0;i<id_amount;i++){
		customer_count[i]=0;	
	}
	served_customer = new int[DAY_MAX+1];
	for(int i=0;i<DAY_MAX+1;i++){
		served_customer[i]=0;	
	}
	enemyfund = new int[4];
	for(int i=0;i<4;i++){
		enemyfund[i]= 50000+rand()%15000;
	}
	recipeN_forpay=0;
	recipeN_current=0;
	initial();
}

Ingredient^  Warehouse::getIngredient(int Type){
	return ingredient[Type];
}
Tool^  Warehouse::getTool(int Type){
	return tool[Type];
}
Decoration^  Warehouse::getDecoration(int Type){
	return decoration[Type];
}
Recipe^  Warehouse::getRecipe(int Type){
	return recipe[Type];
}

void Warehouse::addCustomer_count(int ID){
	customer_count[ID]++;
};
int Warehouse::getCustomer_count(int ID){
	return customer_count[ID];
};
int Warehouse::getFund(){
	return fund;
}

int Warehouse::getLocation(){
	return location;
}



void Warehouse::setFund(int inputFund){
	fund=inputFund;
}

void Warehouse::addFund(int increment){
	fund+=increment;
}

void Warehouse::subFund(int consume){
	fund-=consume;
}

///-------------------V     not complete
/// the discount is writen in sell function
bool Warehouse::examine_ingredient(int Type){//const
	int tempsum=0,demand;
	bool enoughflag=false;
	bool finalflag=true;
	for(int i=0;i<INGREDIEDNT_TYPE_MAX;i++){
		demand=recipe[Type]->get_ingredient_Demand(i);
		if(demand != 0){
			for(int j=1;j<=currentday;j++){
				tempsum+=ingredient[i]->get_remaining(j);				
			}
			if(tempsum>= demand){
				enoughflag=true;
			}
			if(enoughflag==false){
				finalflag=false;
				break;
			}
			enoughflag=false;
			tempsum=0;				
		}
	}
	return finalflag;
}
 
bool Warehouse::sell_Food(int Type){///test at last	
	int j=1,demand;
	if(recipe[Type]->getExist()){
		if(examine_ingredient(recipe[Type]->getSort())){
			fund+=recipe[Type]->getPrice();
		/*��������*/
			for(int i=0;i<INGREDIEDNT_TYPE_MAX;i++){
				demand=recipe[Type]->get_ingredient_Demand(i);
				while(demand != 0){
						if(ingredient[i]->get_remaining(j) <= demand){
							demand-=ingredient[i]->get_remaining(j);
							ingredient[i]->setRemaining(j,0);
						}else{
							ingredient[i]->subRemaining(j,demand);
							demand=0;	
						}						
					j++;//�o�����M�S���ˬd�O�_�j��ثe�Ѽ� ���z�פW���|�X���D �]���w�g�ϥιL�ˬd��ƤF 
				}
				j=1;	
			}
			return true;
		}else{
			cout<<"��Ƥ���"<<endl<<endl;
			return false;
		}	
			
	}	
	else			
		return false;
}

bool Warehouse::sell_Decoration(int Type){///if fail to sell   return false
	///you can sell it only if you have one
	if(decoration[Type]->getExist()){
		fund+= (int)(decoration_discount * decoration[Type]->getPrice());
		decoration[Type]->setExist(false);
		decorationNumber--;
		return true;
	}	
	else			
		return false;
}

bool Warehouse::sell_Tool(int Type){
	///you can sell it only if you have one
	if(tool[Type]->getExist()){
		fund+=(int)(tool_discount * tool[Type]->getPrice());
		tool[Type]->setExist(false);
		toolNumber--;
		
		//�����������//
		for(int i=0;i<RECIPE_TYPE_MAX;i++){
			if(recipe[i]->getExist()){
				if(recipe[i]->get_tool_Demand(Type)){
					recipe[i]->setExist(false);
					//��s��e���]�m���ƶq
					recipeN_current--;
				}
			}
		} 
		return true;
	}	
	else			
		return false;
}

bool Warehouse::buy_ingredient(int Type,int number){///sort_number= how many Types you want to buy
	///you can buy it if you have enough money     and it will add to current day  position	
	if(number<0)
		return false;
	if(fund>(number*ingredient[Type]->getPrice())){
		
		if(ingredient[Type]->get_remaining(currentday)+number<=999){
			fund-=number*ingredient[Type]->getPrice();
			ingredient[Type]->addRemaining(currentday,number);
			return true;
		}else{
			fund-= (999-ingredient[Type]->get_remaining(currentday)) *ingredient[Type]->getPrice();
			ingredient[Type]->addRemaining(currentday, 999-ingredient[Type]->get_remaining(currentday));
			return false;
		}
		
	}
	return false;
}

bool Warehouse::buy_Decoration(int Type){
	///you can buy it if you have enough money and you don't have it	
	if(fund>decoration[Type]->getPrice() && !(decoration[Type]->getExist()) && (decorationNumber<decorationNumber_max) )
	{
		fund-=decoration[Type]->getPrice();
		decoration[Type]->setExist(true);
		decorationNumber++;
		return true;
	}
	else
		return false;///if fail to buy it return false	
}

bool Warehouse::buy_Tool(int Type){	
	if(fund>tool[Type]->getPrice() && !(tool[Type]->getExist()) && (toolNumber<toolNumber_max))
	{
		fund-=tool[Type]->getPrice(); 
		tool[Type]->setExist(true);	
		toolNumber++;
		return true;
	}
	else
		return false;///if fail to buy it return false
}

bool Warehouse::setRecipe(int Type)
{
	if(!recipe[Type]->getExist()){
		for(int i=0;i<TOOL_TYPE_MAX;i++){
			if(recipe[Type]->get_tool_Demand(i)){
				if(!tool[i]->getExist()){
					
					//cout<<"���֦������]�� �]�m��楢��"<<endl<<endl; 
					return false;
					/*�]�i�b�o�䰵�X�B�~ ���ѳB�z*/
				}					
			}
		}	
		//�ˬd���� �}�l�]�m���
		recipe[Type]->setExist(true);
		//��s��e���]�m���ƶq
		recipeN_current++;
		if(recipeN_current>recipeN_forpay)
			recipeN_forpay=recipeN_current;

		return true;
	}else{
		return false;//�w�g�]�m��� �L�k�A���]�m 
	}
	
}/*�]�m��� �|�ˬd�����]�ƬO�_�֦�*/
bool Warehouse::resetRecipe(int Type)
{
	if(recipe[Type]->getExist()){
		//��s��e���]�m���ƶq
		recipeN_current--;
	}
	recipe[Type]->setExist(false);
	
	return true;
}/*�M�U���*/ 


/*���եΪ�l�ܨ��*/
void Warehouse::initial()
{

	fund=30000;
	prefund=fund;

	int ingarr[INGREDIEDNT_TYPE_MAX]={0};
	bool toolarr[TOOL_TYPE_MAX]={0};
//Ingredient	Ingredient	Ingredient	Ingredient	Ingredient	Ingredient	Ingredient	Ingredient	Ingredient	//
	ingredient[0]= gcnew Ingredient("���J",10,0,2);
	ingredient[1]= gcnew Ingredient("�A��",10,1,2);
	ingredient[2]= gcnew Ingredient("��",  10,2,4);
	ingredient[3]= gcnew Ingredient("�ѯ�",  10,3,4);
	ingredient[4]= gcnew Ingredient("�ѱ�",10,4,4);

	ingredient[5]= gcnew Ingredient("�e�ѱ�",10,5,4);
	ingredient[6]= gcnew Ingredient("�q���ѱ�",10,6,6);
	ingredient[7]= gcnew Ingredient("�z��",10,7,4);
	ingredient[8]= gcnew Ingredient("���R��",10,8,4);
	ingredient[9]= gcnew Ingredient("�Ťߵ�",  10,9,4);


	ingredient[10]= gcnew Ingredient("���޵�",10,10,4);
	ingredient[11]= gcnew Ingredient("�͵�",10,11,4);
	ingredient[12]= gcnew Ingredient("�v��",10,12,4);
	ingredient[13]= gcnew Ingredient("��",10,13,6);
	ingredient[14]= gcnew Ingredient("��ۣ",10,14,4);


	ingredient[15]= gcnew Ingredient("�J�ڽ�",10,15,6);
	ingredient[16]= gcnew Ingredient("�ŹT",10,16,6);
	ingredient[17]= gcnew Ingredient("�@��",10,17,4);
	ingredient[18]= gcnew Ingredient("���o",10,18,4);
	ingredient[19]= gcnew Ingredient("�_�h��",10,19,4);

	ingredient[20]= gcnew Ingredient("���G",10,20,4);
	ingredient[21]= gcnew Ingredient("�����",10,21,4);
	ingredient[22]= gcnew Ingredient("�n��",20,22,4);
	ingredient[23]= gcnew Ingredient("�ɦ�",20,23,4);
	ingredient[24]= gcnew Ingredient("ī�G",20,24,4);

	ingredient[25]= gcnew Ingredient("�f�X",20,25,4);
	ingredient[26]= gcnew Ingredient("���a��",10,26,4);
	ingredient[27]= gcnew Ingredient("��Ħ",10,27,4);
	ingredient[28]= gcnew Ingredient("���a",10,28,4);
	ingredient[29]= gcnew Ingredient("���x��",20,29,4);

	ingredient[30]= gcnew Ingredient("���ĥ�",10,30,4);
	ingredient[31]= gcnew Ingredient("���l",10,31,4);
	ingredient[32]= gcnew Ingredient("����",10,32,4);
	ingredient[33]= gcnew Ingredient("����",50,33,2);
	ingredient[34]= gcnew Ingredient("�D��",50,34,2);

	ingredient[35]= gcnew Ingredient("��M��",50,35,2);
	ingredient[36]= gcnew Ingredient("����",50,36,2);
	ingredient[37]= gcnew Ingredient("����",50,37,2);
	ingredient[38]= gcnew Ingredient("�{��",50,38,2);
	ingredient[39]= gcnew Ingredient("���",10,39,2);

	ingredient[40]= gcnew Ingredient("�z��",50,40,2);
	ingredient[41]= gcnew Ingredient("�Ҥ���",50,41,4);
	ingredient[42]= gcnew Ingredient("����",50,42,2);
	ingredient[43]= gcnew Ingredient("�ަ�",50,43,2);
	ingredient[44]= gcnew Ingredient("����",50,44,2);
	ingredient[45]= gcnew Ingredient("�Ϧ�",50,45,2);

	ingredient[46]= gcnew Ingredient("�n��",50,46,2);
	ingredient[47]= gcnew Ingredient("����",10,47,4);
	ingredient[48]= gcnew Ingredient("�³���",10,48,6);
	ingredient[49]= gcnew Ingredient("���b",50,49,4);
	

//Tool  Tool  Tool  Tool  Tool  Tool  Tool  Tool  Tool  Tool  Tool  Tool  Tool  Tool  //	
	tool[0]= gcnew Tool("�֪���", 10000,0,false);
	tool[1]= gcnew Tool("����",12000,1,false);
	tool[2]= gcnew Tool("����",2000,2,false);
	tool[3]= gcnew Tool("������",12000,3,false);
	tool[4]= gcnew Tool("�N�c",10000,4,false);
	tool[5]= gcnew Tool("�N�[",2000,5,false);
	tool[6]= gcnew Tool("�]Ţ",2000,5,false);



//Decoration  Decoration  Decoration  Decoration  Decoration  Decoration  Decoration  Decoration  Decoration    ////	
	decoration[0]= gcnew Decoration("�֥d�C",2000,0,false);
	decoration[1]= gcnew Decoration("�G���q��",3000,1,false);
	decoration[2]= gcnew Decoration("�X�R�R��",4000,2,false);
	decoration[3]= gcnew Decoration("���ŭ��T",3000,3,false);
//Recipe  Recipe  Recipe  Recipe  Recipe  Recipe  Recipe  Recipe  Recipe  Recipe  Recipe  Recipe  ////	
	ingarr[42]=4;  
	toolarr[3]=true;
	recipe[0]= gcnew Recipe("�a�����p��",600,0,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);	

	ingarr[42]=4;  
	toolarr[3]=true;
	recipe[1]= gcnew Recipe("��O����",620,1,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[43]=4;    
	toolarr[4]=true;
	recipe[2]= gcnew Recipe("�N�޸}",680,2,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[33]=4;    
	toolarr[3]=true;
	recipe[3]= gcnew Recipe("�ĳ�",600,3,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[45]=4;      
	toolarr[3]=true;
	recipe[4]= gcnew Recipe("�k���p�ϱ�",580,4,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[44]=3; 
	toolarr[3]=true;
	recipe[5]= gcnew Recipe("�[�����L��",380,5,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);	
////////////////////////
	ingarr[0]=4;ingarr[3]=5;ingarr[18]=4; 
	toolarr[4]=true;
	recipe[6]= gcnew Recipe("��u�ѥ]",370,6,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[26]=13;
	toolarr[2]=true;
	recipe[7]= gcnew Recipe("������",380,7,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[12]=13; 
	toolarr[2]=true;
	recipe[8]= gcnew Recipe("���v����",360,8,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[11]=13;  
	recipe[9]= gcnew Recipe("�͵�F��",320,9,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[49]=1;ingarr[42]=2;
	toolarr[1]=true;
	recipe[10]= gcnew Recipe("���s�L����",450,10,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);	

	ingarr[46]=3; 
	toolarr[4]=true;
	recipe[11]= gcnew Recipe("�p�N�n��",460,11,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[42]=3;   
	toolarr[3]=true;
	recipe[12]= gcnew Recipe("�F�Ԥ���",450,12,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[36]=3; 
	toolarr[5]=true;
	recipe[13]= gcnew Recipe("���N���O��",420,13,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[43]=3;  
	toolarr[5]=true;
	recipe[14]= gcnew Recipe("���t���z",390,14,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);


	ingarr[22]=6; 
	toolarr[1]=true;
	recipe[15]= gcnew Recipe("�n�ʴ�",320,15,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);	

	ingarr[23]=3;ingarr[3]=5;ingarr[18]=2; ingarr[15]=2; 
	toolarr[1]=true;
	recipe[16]= gcnew Recipe("�p�ֿ@��",350,16,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[23]=6;ingarr[15]=2;  
	toolarr[1]=true;
	recipe[17]= gcnew Recipe("�ɦ̿@��",300,17,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[16]=5; ingarr[1]=8;
	recipe[18]= gcnew Recipe("�ٯ����T",300,18,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[27]=13;
	recipe[19]= gcnew Recipe("�ٯ���",300,19,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);

	ingarr[24]=6;
	recipe[20]= gcnew Recipe("���G�B��",200,20,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);	

	ingarr[1]=6;    
	recipe[21]= gcnew Recipe("�B���K",200,21,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[1]=6; 
	recipe[22]= gcnew Recipe("�J�}����",200,22,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[24]=3;
	toolarr[4]=true;
	recipe[23]= gcnew Recipe("ī�G��",200,23,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[49]=2;
	recipe[24]= gcnew Recipe("���b",200,24,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	///////////////////////////////
	ingarr[43]=2;ingarr[2]=2;
	toolarr[0]=true;
	recipe[25]= gcnew Recipe("�F�Y�׻\��",380,25,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);	

	ingarr[34]=3;
	toolarr[2]=true;
	recipe[26]= gcnew Recipe("�D�����U��",370,26,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[41]=2;
	recipe[27]= gcnew Recipe("�Ҥ���",360,27,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[35]=2;ingarr[2]=2;   
	toolarr[6]=true;
	recipe[28]= gcnew Recipe("��M���]��",400,28,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[35]=3;
	toolarr[5]=true;
	recipe[29]= gcnew Recipe("�N����M��",400,29,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);

	ingarr[2]=4;ingarr[28]=4;
	recipe[30]= gcnew Recipe("���إq",250,30,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);	

	ingarr[2]=3;ingarr[28]=3;ingarr[31]=2;  
	recipe[31]= gcnew Recipe("�ܱ����{",220,31,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[4]=6;ingarr[28]=2;  
	toolarr[1]=true; 
	recipe[32]= gcnew Recipe("��o����",200,32,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[0]=2;ingarr[2]=5;ingarr[18]=1;  
	toolarr[0]=true;
	recipe[33]= gcnew Recipe("�j�[����",300,33,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[43]=2;  
	toolarr[2]=true;
	recipe[34]= gcnew Recipe("�馡���ޱ�",250,34,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);

	ingarr[4]=6;ingarr[28]=2;  
	toolarr[1]=true;
	recipe[35]= gcnew Recipe("�Q�s�N��",220,35,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);	

	ingarr[36]=2;
	toolarr[4]=true;
	recipe[36]= gcnew Recipe("�Q�N����",250,36,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[37]=1;ingarr[34]=1;  
	recipe[37]= gcnew Recipe("��X�ͳ���",260,37,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[37]=1; ingarr[2]=3; 
	toolarr[5]=true;
	recipe[38]= gcnew Recipe("������",300,38,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[11]=2; ingarr[12]=2; ingarr[3]=4;
	toolarr[3]=true;
	recipe[39]= gcnew Recipe("����λ�",250,39,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);

	ingarr[40]=2;  
	toolarr[5]=true;
	recipe[40]= gcnew Recipe("���N�z��",300,40,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);	
	
	ingarr[27]=4;ingarr[20]=4; 
	toolarr[1]=true;
	recipe[41]= gcnew Recipe("������",200,41,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[0]=3;ingarr[44]=1;
	toolarr[3]=true;
	recipe[42]= gcnew Recipe("�ˤl�d",250,42,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[11]=8;   
	recipe[43]= gcnew Recipe("�M���F��",250,43,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[38]=2;  
	toolarr[5]=true;
	recipe[44]= gcnew Recipe("��N�{��",270,44,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
//////////////////////////////////		
	ingarr[2]=3;ingarr[28]=1;   
	recipe[45]= gcnew Recipe("���w��",120,45,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);	

	ingarr[39]=4;  
	toolarr[1]=true;
	recipe[46]= gcnew Recipe("��Ĵ�",100,46,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[32]=3; ingarr[2]=1; 
	recipe[47]= gcnew Recipe("���ֹإq",100,47,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[0]=2; ingarr[2]=2;
	toolarr[4]=true;
	recipe[48]= gcnew Recipe("�M�J�إq",100,48,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[2]=4;
	recipe[49]= gcnew Recipe("��إq",130,49,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	////////////////////////////////////////////////////////
	ingarr[36]=3;
	toolarr[4]=true;
	recipe[50]= gcnew Recipe("�q���ȥ]��",400,50,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);	

	ingarr[46]=3; 
	toolarr[4]=true;
	recipe[51]= gcnew Recipe("���N�X�n",400,51,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[30]=4;ingarr[25]=2; ingarr[17]=4;
	toolarr[4]=true;
	recipe[52]= gcnew Recipe("Calzone",400,52,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[16]=4;ingarr[17]=4;ingarr[6]=4; 
	toolarr[1]=true;
	recipe[53]= gcnew Recipe("�@�����T�N��",330,53,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[48]=2;ingarr[42]=2;  
	toolarr[1]=true;
	recipe[54]= gcnew Recipe("�³��ĿL��",320,54,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
		
	ingarr[44]=2;   
	toolarr[4]=true;
	recipe[55]= gcnew Recipe("���e�N���L",280,55,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);	

	ingarr[8]=3;ingarr[42]=1; 
	toolarr[1]=true;
	recipe[56]= gcnew Recipe("�A���L����",270,56,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[0]=4;ingarr[19]=4;
	toolarr[3]=true;
	recipe[57]= gcnew Recipe("�q���کi�J",220,57,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[11]=2;ingarr[2]=6;
	toolarr[3]=true;
	recipe[58]= gcnew Recipe("ù�ǫC��L��",250,58,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[25]=2;ingarr[6]=4;
	toolarr[3]=true;
	recipe[59]= gcnew Recipe("�f�X������",220,59,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);

	ingarr[14]=4;ingarr[2]=4;  
	toolarr[3]=true;
	recipe[60]= gcnew Recipe("��ۣ�L��",220,60,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);	

	ingarr[29]=2;ingarr[5]=4;
	toolarr[3]=true;
	recipe[61]= gcnew Recipe("���x�ߵu����",220,61,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[30]=8;  
	toolarr[3]=true;
	recipe[62]= gcnew Recipe("�������",200,62,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[25]=1;ingarr[30]=6;  
	toolarr[3]=true;
	recipe[63]= gcnew Recipe("������S����",200,63,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[3]=8;  
	toolarr[1]=true;
	recipe[64]= gcnew Recipe("�q���Ѫ��D",280,64,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
		
	ingarr[24]=4;
	toolarr[1]=true;
	recipe[65]= gcnew Recipe("�e���Lī�G",300,65,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);	

	ingarr[6]=8; 
	toolarr[1]=true;
	recipe[66]= gcnew Recipe("�q�����N��",260,66,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[0]=4;ingarr[3]=4;   
	toolarr[3]=true;
	recipe[67]= gcnew Recipe("�q���J��",200,67,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[6]=8; 
	toolarr[4]=true;
	recipe[68]= gcnew Recipe("�d�h��",200,68,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[18]=4;ingarr[26]=4;
	toolarr[4]=true;
	recipe[69]= gcnew Recipe("�q�����o����",250,69,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
//////////////////////////////////		
	ingarr[0]=4;  
	toolarr[4]=true;
	recipe[70]= gcnew Recipe("�q���N�J",120,70,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);	

	ingarr[3]=4;  
	toolarr[4]=true;
	recipe[71]= gcnew Recipe("�۳�����",120,71,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[26]=1;ingarr[19]=2;
	toolarr[4]=true;
	recipe[72]= gcnew Recipe("�K�N���a��",150,72,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[11]=4;  
	toolarr[1]=true;
	recipe[73]= gcnew Recipe("�q�������",130,73,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[6]=4;  
	toolarr[3]=true;
	recipe[74]= gcnew Recipe("�q�j�Q��",120,74,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	/////////////////////////////////////////	
	ingarr[20]=15;  
	toolarr[0]=true;
	recipe[75]= gcnew Recipe("���߳±C���G",450,75,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);	

	ingarr[43]=3;  
	toolarr[0]=true;
	recipe[76]= gcnew Recipe("�����B�L��",440,76,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[4]=12;ingarr[22]=3;  
	toolarr[3]=true;
	recipe[77]= gcnew Recipe("�sŽ��",500,77,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[3]=5;ingarr[34]=2;  
	recipe[78]= gcnew Recipe("��ͬK��",420,78,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[33]=2;ingarr[21]=5;
	toolarr[6]=true;
	recipe[79]= gcnew Recipe("�@�s��l",450,79,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);

	ingarr[13]=5;ingarr[42]=1;
	toolarr[0]=true;
	recipe[80]= gcnew Recipe("���z���h",300,80,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);	

	ingarr[4]=5;ingarr[42]=1;  
	toolarr[1]=true;
	recipe[81]= gcnew Recipe("���N������",300,81,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[43]=1;ingarr[2]=5;
	recipe[82]= gcnew Recipe("�|�׶�",250,82,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[44]=2; 
	toolarr[0]=true;
	recipe[83]= gcnew Recipe("�T�M��",320,83,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[43]=1;ingarr[20]=5; 
	toolarr[6]=true;
	recipe[84]= gcnew Recipe("��l�Y",250,84,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
		
	ingarr[43]=2;
	toolarr[0]=true;
	recipe[85]= gcnew Recipe("�}�L�ư�",300,85,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);	

	ingarr[43]=1;ingarr[3]=5; 
	toolarr[0]=true;
	recipe[86]= gcnew Recipe("���o����",320,86,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[20]=10;  
	toolarr[0]=true;
	recipe[87]= gcnew Recipe("�±C���G",290,87,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[8]=10; 
	toolarr[0]=true;
	recipe[88]= gcnew Recipe("�����R��",250,88,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[9]=10; 
	toolarr[0]=true;
	recipe[89]= gcnew Recipe("���Ťߵ�",250,89,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);

	ingarr[10]=10;
	toolarr[0]=true;
	recipe[90]= gcnew Recipe("�����޵�",200,90,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);	

	ingarr[4]=10;  
	toolarr[1]=true;
	recipe[91]= gcnew Recipe("���K��",220,91,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[43]=1;ingarr[3]=5;
	toolarr[6]=true;
	recipe[92]= gcnew Recipe("�ʨ��]�l",280,92,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[47]=2;ingarr[2]=2;
	toolarr[0]=true; 
	recipe[93]= gcnew Recipe("���ڪ���",300,93,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[0]=3;ingarr[3]=5;ingarr[39]=2;
	toolarr[3]=true;
	recipe[94]= gcnew Recipe("�H�J��",250,94,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	//////////////////////////////////			
	ingarr[7]=5;
	toolarr[6]=true;
	recipe[95]= gcnew Recipe("��l",120,95,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);	

	ingarr[3]=5;
	toolarr[2]=true;
	recipe[96]= gcnew Recipe("���C�Y",120,96,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[21]=5;
	toolarr[6]=true;
	recipe[97]= gcnew Recipe("�]����",140,97,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[4]=5;
	toolarr[1]=true;
	recipe[98]= gcnew Recipe("����",130,98,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);
	
	ingarr[0]=2;ingarr[27]=3;
	toolarr[1]=true;
	recipe[99]= gcnew Recipe("�J���",150,99,false,ingarr,toolarr);reseting(ingarr);resettool(toolarr);	
	
}
void Warehouse::reseting(int target[])
{
	for(int i=0;i<INGREDIEDNT_TYPE_MAX;i++)
		target[i]=0;
}
void Warehouse::resettool(bool target[])
{
	for(int i=0;i<TOOL_TYPE_MAX;i++)
		target[i]=false;
}

int Warehouse::getDay(){
	return currentday;
}
int Warehouse::getMinute(){
	return currentminute;
}
int Warehouse::getHour(){
	return currenthour;
}
int  Warehouse::getServed_customer(int day){
	return  served_customer[day];
}
void Warehouse::addServed_customer(int day){
	served_customer[day]++;
}
void Warehouse::setDay(int day){
	currentday=day;
}
void Warehouse::setHour(int hour){
	currenthour=hour;
}
void Warehouse::setMinute(int minute){
	currentminute=minute;
}

void Warehouse::save(int target){
	StreamWriter^ writer;
	switch(target){
		case 1:
			writer = gcnew StreamWriter("savedata\\01.dat", false);
			break;
		case 2:
			writer = gcnew StreamWriter("savedata\\02.dat", false);
			break;
		case 3:
			writer = gcnew StreamWriter("savedata\\03.dat", false);
			break;
		case 4:
			writer = gcnew StreamWriter("savedata\\04.dat", false);
			break;
	}
	
	///saving initial data
	writer->WriteLine("currentday");
	writer->WriteLine(currentday);
	writer->WriteLine();
   
	writer->WriteLine("currenthour");
	writer->WriteLine(currenthour);
	writer->WriteLine();

	writer->WriteLine("currentminute");
	writer->WriteLine(currentminute);
	writer->WriteLine();

	writer->WriteLine("fund");
	writer->WriteLine(fund);
	writer->WriteLine();

	writer->WriteLine("recipeN_forpay");
	writer->WriteLine(recipeN_forpay);
	writer->WriteLine();

	writer->WriteLine("recipeN_current");
	writer->WriteLine(recipeN_current);
	writer->WriteLine();

	writer->WriteLine("location");
	writer->WriteLine(location);
	writer->WriteLine();

	writer->WriteLine("ingredient");
	for(int i=0;i<10;i++){
        writer->Write(" ");
		writer->Write((i+": "));
        for(int j=1;j<DAY_MAX+1;j++){
			writer->Write(""+ingredient[i]->get_remaining(j));
			writer->Write(" ");
        }
        writer->WriteLine();
    }
	for(int i=10;i<INGREDIEDNT_TYPE_MAX;i++){
		writer->Write((i+": "));
        for(int j=1;j<DAY_MAX+1;j++){
			writer->Write(""+ingredient[i]->get_remaining(j));
			writer->Write(" ");
        }
        writer->WriteLine();
    }
	writer->WriteLine();

	writer->WriteLine("tool");
	for(int i=0;i<TOOL_TYPE_MAX;i++){
		writer->Write((tool[i]->getExist()?(""+1):(""+0)));
		writer->Write(" ");
    }
	writer->WriteLine();
	writer->WriteLine();
	
	writer->WriteLine("decoration");
	for(int i=0;i<DECORATION_TYPE_MAX;i++){
		writer->Write((decoration[i]->getExist()?(""+1):(""+0)));
		writer->Write(" ");
    }
	writer->WriteLine();
	writer->WriteLine();

	writer->WriteLine("recipe");
	for(int i=0;i<RECIPE_TYPE_MAX;i++){
		writer->Write((recipe[i]->getExist()?(""+1):(""+0)));
		writer->Write(" ");
    }
	writer->WriteLine();
	writer->WriteLine();

	writer->WriteLine("served_customer");
	for(int i=1;i<DAY_MAX+1;i++){
		writer->Write(""+served_customer[i]);
		writer->Write(" ");
	}
	writer->WriteLine();
	writer->WriteLine();

	writer->WriteLine("customer_count");
	for(int i=0;i<id_amount;i++){
		writer->Write(""+customer_count[i]);
		writer->Write(" ");
	}
	writer->WriteLine();
	writer->WriteLine();

	writer->WriteLine("prefund");
	writer->WriteLine(""+prefund);
	writer->WriteLine();

	writer->WriteLine("enemyfund");
	for(int i=0;i<4;i++){
		writer->Write(""+enemyfund[i]);
		writer->Write(" ");
	}
	writer->WriteLine();
	writer->WriteLine();

	writer->WriteLine("Name");
	writer->WriteLine(getName());
	
	writer->Close();
}
void Warehouse::load(int source){
	String^ input;
	StreamReader^ load;
	switch(source){
		case 1:
			load = File::OpenText("savedata\\01.dat");
			break;
		case 2:
			load = File::OpenText("savedata\\02.dat");
			break;
		case 3:
			load = File::OpenText("savedata\\03.dat");
			break;
		case 4:
			load = File::OpenText("savedata\\04.dat");
			break;
	}
	try
	{
		load->ReadLine();
		input = load->ReadLine();
		currentday=Int32::Parse(input);
		load->ReadLine();

		load->ReadLine();
		input = load->ReadLine();
		currenthour=Int32::Parse(input);
		load->ReadLine();

		load->ReadLine();
		input = load->ReadLine();
		currentminute=Int32::Parse(input);
		load->ReadLine();

		load->ReadLine();
		input = load->ReadLine(); 
		fund=Int32::Parse(input);
		load->ReadLine();

		load->ReadLine();
		input = load->ReadLine();
		recipeN_forpay=Int32::Parse(input);
		load->ReadLine();

		load->ReadLine();
		input = load->ReadLine();
		recipeN_current=Int32::Parse(input);
		load->ReadLine();

		load->ReadLine();
		input = load->ReadLine();
		location=Int32::Parse(input);
		load->ReadLine();
		/////
		int	j=4,count=0,temp=0;//count=10�N����
		load->ReadLine();
		for(int i=0;i<INGREDIEDNT_TYPE_MAX;i++){
			input = load->ReadLine();
			while(count!=10){
				if(input[j]!=' '){
					temp=temp*10+input[j]-48;
				}else{
					ingredient[i]->setRemaining(count+1,temp);
					temp=0;
					count++;
				}
				j++;
			}
			j=4;
			count=0;
		}
		load->ReadLine();
		
		j=0;
		load->ReadLine();
		input = load->ReadLine();///load tool
		for(int i=0;i<TOOL_TYPE_MAX;i++){
			(input[j]=='0')?tool[i]->setExist(false):tool[i]->setExist(true);
			j+=2;
		}
		load->ReadLine();

		j=0;
		load->ReadLine();
		input = load->ReadLine();
		for(int i=0;i<DECORATION_TYPE_MAX;i++){
			(input[j]=='0')?decoration[i]->setExist(false):decoration[i]->setExist(true);
			j+=2;
		}
		load->ReadLine();

		j=0;
		load->ReadLine();
		input = load->ReadLine();
		for(int i=0;i<RECIPE_TYPE_MAX;i++){
			(input[j]=='0')?recipe[i]->setExist(false):recipe[i]->setExist(true);
			j+=2;
		}
		load->ReadLine();

		j=0,count=0,temp=0;
		load->ReadLine();
		input = load->ReadLine();///load served_customer
		while(count!=DAY_MAX){
			if(input[j]!=' '){
				temp=temp*10+input[j]-48;
			}else{
				served_customer[count+1]=temp;
				temp=0;
				count++;
			}
			j++;
		}
		load->ReadLine();

		j=0,count=0,temp=0;///
		load->ReadLine();
		input = load->ReadLine();///load customer_count
		while(count<id_amount){
			if(input[j]!=' '){
				temp=temp*10+input[j]-48;
			}else{
				customer_count[count]=temp;
				temp=0;
				count++;
			}
			j++;
		}
		load->ReadLine();	

		load->ReadLine();
		input = load->ReadLine();
		prefund=Int32::Parse(input);
		load->ReadLine();

		j=0,count=0,temp=0;///
		load->ReadLine();
		input = load->ReadLine();///load customer_count
		while(count!=4){
			if(input[j]!=' '){
				temp=temp*10+input[j]-48;
			}else{
				enemyfund[count]=temp;
				temp=0;
				count++;
			}
			j++;
		}
		load->ReadLine();

		load->ReadLine();
		input = load->ReadLine();
		setName(input);
		//load->ReadLine();

	}catch(IOException^ e){
	}
	
    load->Close();
}

int Warehouse::getRecipeN_forpay(){
	return recipeN_forpay;
}
int Warehouse::getRecipeN_current(){
	return recipeN_current;
}

bool Warehouse::getData_updateflag(){
	return data_updateflag;
}
void Warehouse::setData_updateflag(bool input){
	data_updateflag=input;
}

int Warehouse::getPrefund(){
	return prefund;
}
void Warehouse::setPrefund(int input){
	prefund = input;
}
int Warehouse::getCookpay(){
	if(recipeN_forpay<=30){
		return 	1000;
	}else if(recipeN_forpay<=40){
		return 	1000+(recipeN_forpay-30)*50;
	}else if(recipeN_forpay<=50){
		return 	1500+(recipeN_forpay-40)*100;
	}else{
		return 	2500+(recipeN_forpay-50)*150;
	}
}
void Warehouse::setRecipeN_forpay(int input){
	recipeN_forpay=input;
}
void Warehouse::setRecipeN_current(int input){
	recipeN_current=input;
}
void Warehouse::ingredient_dead(){
	for(int i=0;i<INGREDIEDNT_TYPE_MAX;i++){
		for(int j=1;j<=currentday;j++){
			if((currentday+1-j) >= ingredient[i]->get_deadtime()){
				ingredient[i]->setRemaining(j,0);
			}
		}
	}
}

void Warehouse::addEnemyfund(int Type){
	/*�ھ��U�Ⱥ����M�w�n�[���@�ө��a �H�Υ[�h��*/
	switch(Type){
		case 0:
			enemyfund[0]+=150;
			break;
		case 1:
			enemyfund[3]+=300;
			break;
		case 2:
			enemyfund[1]+=250;
			break;
		case 3:
			enemyfund[3]+=300;
			break;
		case 4:
			enemyfund[2]+=250;
			break;
		case 5:
			enemyfund[0]+=400;
			break;
	}
}
int Warehouse::getEnemyfund(int enemytype){
	return enemyfund[enemytype];
}

void Warehouse::setLocation(int input){
	location=input;
}