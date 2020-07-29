#pragma once

#include"Warehouse.h"
#include"Customer.h" 

namespace project_GUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Form2 的摘要
	/// </summary>
	public ref class Form2 : public System::Windows::Forms::Form
	{
	public:
		Form2(void)
		{
			InitializeComponent();
		}
		Form2(int x,int y,int width,int height,Warehouse^ w,Customer^ c,Form^ f,Timer^ ck,Label^ l1,Label^ l2)
		{
			InitializeComponent();
			//
			this->Location = System::Drawing::Point(x, y);
			currentwarehousestate=1;
			warehouse=w;
			customer=c;
			form1 = f;
			clock = ck;
			label_money =l1;
			label_customer = l2;
			if(warehouse->getHour()<=12){
				if(warehouse->getHour()>=10){
					if(warehouse->getMinute()>=10){
						this->label_time->Text = L"第"+warehouse->getDay()+"天 "+warehouse->getHour()+":"+warehouse->getMinute()+" A.M.";
					}else{
						this->label_time->Text = L"第"+warehouse->getDay()+"天 "+warehouse->getHour()+":0"+warehouse->getMinute()+" A.M.";
					}	
				}else{
					if(warehouse->getMinute()>=10){
						this->label_time->Text = L"第"+warehouse->getDay()+"天 0"+warehouse->getHour()+":"+warehouse->getMinute()+" A.M.";
					}else{
						this->label_time->Text = L"第"+warehouse->getDay()+"天 0"+warehouse->getHour()+":0"+warehouse->getMinute()+" A.M.";
					}	
				}					
			}else{
				if(warehouse->getMinute()>=10){
					this->label_time->Text = L"第"+warehouse->getDay()+"天 0"+(warehouse->getHour()-12)+":"+warehouse->getMinute()+" P.M.";
				}else{
					this->label_time->Text = L"第"+warehouse->getDay()+"天 0"+(warehouse->getHour()-12)+":0"+warehouse->getMinute()+" P.M.";
				}
			}	
			this->pictureBox_interface->BackgroundImage = Image::FromFile("img\\interface_normal.jpg");
			label_maxrecipe->Text = L"最大菜單數: "+warehouse->getRecipeN_forpay();
			label_currentrecipe->Text = L"目前菜單數: "+warehouse->getRecipeN_current();
			screencounter=0;

		/*	這邊預計必須讀出存檔裡的時間*/

			String^ input;
			StreamReader^ load;
			try{
			load = File::OpenText("savedata\\01.dat");
			load->ReadLine();
			input = load->ReadLine();
			button_data1->Text = L"data1\n\r"+input;
			load->ReadLine();
			load->ReadLine();
			input = load->ReadLine();
			button_data1->Text = button_data1->Text+"\\"+input;
			load->ReadLine();
			load->ReadLine();
			input = load->ReadLine();
			button_data1->Text = button_data1->Text+"\\"+input;

			load->Close();
			load = File::OpenText("savedata\\02.dat");
			load->ReadLine();
			input = load->ReadLine();
			button_data2->Text = L"data2\n\r"+input;
			load->ReadLine();
			load->ReadLine();
			input = load->ReadLine();
			button_data2->Text = button_data2->Text+"\\"+input;
			load->ReadLine();
			load->ReadLine();
			input = load->ReadLine();
			button_data2->Text = button_data2->Text+"\\"+input;

			load->Close();
			load = File::OpenText("savedata\\03.dat");
			load->ReadLine();
			input = load->ReadLine();
			button_data3->Text = L"data3\n\r"+input;
			load->ReadLine();
			load->ReadLine();
			input = load->ReadLine();
			button_data3->Text = button_data3->Text+"\\"+input;
			load->ReadLine();
			load->ReadLine();
			input = load->ReadLine();
			button_data3->Text = button_data3->Text+"\\"+input;

			load->Close();
			load = File::OpenText("savedata\\04.dat");
			load->ReadLine();
			input = load->ReadLine();
			button_data4->Text = L"data4\n\r"+input;
			load->ReadLine();
			load->ReadLine();
			input = load->ReadLine();
			button_data4->Text = button_data4->Text+"\\"+input;
			load->ReadLine();
			load->ReadLine();
			input = load->ReadLine();
			button_data4->Text = button_data4->Text+"\\"+input;
			load->Close();
			}catch(IOException^ e){
			}

			
	
			
			clock2->Enabled=true;
			button_data1->Visible=false;
			button_data2->Visible=false;
			button_data3->Visible=false;
			button_data4->Visible=false;
			label_interface->Visible=false;
			button_return->Visible=false;


			//
			this->recipelist->Enabled=true;
			addrow(recipelist,RECIPE_TYPE_MAX);
			for(int i=0;i<RECIPE_TYPE_MAX;i++){
				recipelist->Rows[i]->Cells[0]->Value = warehouse->getRecipe(i)->getName();
				recipelist->Rows[i]->Cells[1]->Value = warehouse->getRecipe(i)->getPrice();
				recipelist->Rows[i]->Cells[2]->Value = "";
				for(int j=0;j<INGREDIEDNT_TYPE_MAX;j++){
					if(warehouse->getRecipe(i)->get_ingredient_Demand(j)!=0){
						recipelist->Rows[i]->Cells[2]->Value = recipelist->Rows[i]->Cells[2]->Value+warehouse->getIngredient(j)->getName()+"x"+warehouse->getRecipe(i)->get_ingredient_Demand(j)+" ";
					}	
				}
				for(int j=0;j<TOOL_TYPE_MAX;j++){
					if(warehouse->getRecipe(i)->get_tool_Demand(j)){
						recipelist->Rows[i]->Cells[3]->Value = warehouse->getTool(j)->getName();
					}	
				}
				if( warehouse->getRecipe(i)->getExist()){
					recipelist->Rows[i]->Cells[4]->Value = "存";
				}else{
					recipelist->Rows[i]->Cells[4]->Value = "無";
				}
			}
			this->recipelist->Enabled=false;


			this->decorationlist->Enabled=true;
			this->toollist->Enabled=true;
			addrow(decorationlist,DECORATION_TYPE_MAX);
			addrow(toollist,TOOL_TYPE_MAX);



			for(int i=0;i<TOOL_TYPE_MAX;i++){
				toollist->Rows[i]->Cells[0]->Value = warehouse->getTool(i)->getName();
				toollist->Rows[i]->Cells[1]->Value = warehouse->getTool(i)->getPrice();
				
				if( warehouse->getTool(i)->getExist()){
					toollist->Rows[i]->Cells[2]->Value = "存";
				}else{
					toollist->Rows[i]->Cells[2]->Value = "無";
				}
			}
			for(int i=0;i<DECORATION_TYPE_MAX;i++){
				decorationlist->Rows[i]->Cells[0]->Value = warehouse->getDecoration(i)->getName();
				decorationlist->Rows[i]->Cells[1]->Value = warehouse->getDecoration(i)->getPrice();

				decorationlist->Rows[i]->Cells[2]->Value = "尚未設定說明";

				if( warehouse->getDecoration(i)->getExist()){
					decorationlist->Rows[i]->Cells[3]->Value = "存";
				}else{
					decorationlist->Rows[i]->Cells[3]->Value = "無";
				}
			}

			/*this->decorationlist->Enabled=false;
			this->toollist->Enabled=false;*/

			this->recipe_statistics_list->Enabled=true;
			addrow(recipe_statistics_list,RECIPE_TYPE_MAX);

			for(int i=0;i<RECIPE_TYPE_MAX;i++){
					recipe_statistics_list->Rows[i]->Cells[0]->Value = warehouse->getRecipe(i)->getName();
					recipe_statistics_list->Rows[i]->Cells[1]->Value = warehouse->getRecipe(i)->getCount();
			}

			this->recipe_statistics_list->Enabled=false;

			this->customer_statistics_list->Enabled=true;
			addrow(customer_statistics_list,id_amount);

			for(int i=0;i<id_amount;i++){
					customer->set_ID(i);
					customer_statistics_list->Rows[i]->Cells[0]->Value = customer->getName();
					customer_statistics_list->Rows[i]->Cells[1]->Value = ""+warehouse->getCustomer_count(i);
			}

			this->customer_statistics_list->Enabled=false;

			this->ingredientlist->Enabled=true;
			addrow(ingredientlist,INGREDIEDNT_TYPE_MAX);

			for(int i=0;i<INGREDIEDNT_TYPE_MAX;i++){
				ingredientlist->Rows[i]->Cells[0]->Value = warehouse->getIngredient(i)->getName();
				ingredientlist->Rows[i]->Cells[1]->Value = ""+warehouse->getIngredient(i)->get_deadtime()+"日";
				ingredientlist->Rows[i]->Cells[2]->Value = warehouse->getIngredient(i)->getPrice();
				ingredientlist->Rows[i]->Cells[13]->Value = "0";
				for(int j=1;j<=warehouse->getDay();j++){
					ingredientlist->Rows[i]->Cells[j+2]->Value = warehouse->getIngredient(i)->get_remaining(j);
				}
			};

			currentwarehousestate=1;
			this->BackgroundImage = Image::FromFile("img\\warehouse_ingredient.jpg");
			this->ingredientlist->Visible=true;
			this->ingredientlist->Enabled=true;
			this->button_ingredient->ForeColor = System::Drawing::Color::Yellow;
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~Form2()
		{
			clock->Enabled=true;
			label_money->Text = L"資金: "+warehouse->getFund()+"元";
			clock2->Enabled=false;
			//label_customer->Text = L"本日顧客: "+warehouse->getServed_customer(warehouse->getDay())+"人";
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^  ingredientlist;
	protected: 
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column15;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column14;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column5;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column6;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column7;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column8;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column9;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column10;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column11;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column12;
	private: System::Windows::Forms::DataGridViewButtonColumn^  Column13;

















	private: System::Windows::Forms::DataGridView^  toollist;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn15;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn16;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn17;
	private: System::Windows::Forms::DataGridViewButtonColumn^  dataGridViewButtonColumn2;
	private: System::Windows::Forms::DataGridViewButtonColumn^  dataGridViewButtonColumn3;
	private: System::Windows::Forms::DataGridView^  decorationlist;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn18;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn19;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn20;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column17;
	private: System::Windows::Forms::DataGridViewButtonColumn^  dataGridViewButtonColumn4;
	private: System::Windows::Forms::DataGridViewButtonColumn^  Column16;
	private: System::Windows::Forms::DataGridView^  customer_statistics_list;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn21;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn22;
	private: System::Windows::Forms::DataGridView^  recipe_statistics_list;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn23;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn24;
	private: System::Windows::Forms::Button^  button_history;
	private: System::Windows::Forms::Button^  button_recipe;
	private: System::Windows::Forms::Button^  button_tool_decoration;
	private: System::Windows::Forms::Button^  button_ingredient;
	private: System::Windows::Forms::Button^  button_torunning;

	private:
		/// <summary>
		/// 設計工具所需的變數。
		int currentwarehousestate;
		Warehouse^ warehouse;
		Customer^ customer;
		Form^ form1;
		Timer^ clock;
		Label^ label_money;
		Label^ label_customer;
		int screencounter;
	private: System::Windows::Forms::DataGridView^  recipelist;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn10;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn12;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn13;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column18;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn14;
	private: System::Windows::Forms::DataGridViewButtonColumn^  dataGridViewButtonColumn1;
	private: System::Windows::Forms::DataGridViewButtonColumn^  dataGridViewButtonColumn5;
private: System::Windows::Forms::Button^  button_save;
private: System::Windows::Forms::Button^  button_load;
private: System::Windows::Forms::Label^  label_time;
private: System::Windows::Forms::Label^  label_maxrecipe;
private: System::Windows::Forms::PictureBox^  pictureBox_interface;



private: System::Windows::Forms::Label^  label_currentrecipe;
private: System::Windows::Forms::Timer^  clock2;
private: System::Windows::Forms::Button^  button_data1;
private: System::Windows::Forms::Button^  button_data2;
private: System::Windows::Forms::Button^  button_data4;
private: System::Windows::Forms::Button^  button_data3;
private: System::Windows::Forms::Label^  label_interface;
private: System::Windows::Forms::Button^  button_return;
private: System::ComponentModel::IContainer^  components;




		 /// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
		/// 修改這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle7 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle4 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle5 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle6 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle8 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle9 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle14 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle10 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle11 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle12 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle13 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle15 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle16 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle21 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle17 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle18 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle19 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle20 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle22 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle23 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle25 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle24 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle26 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle27 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle29 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle28 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form2::typeid));
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle30 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle31 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle36 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle32 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle33 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle34 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle35 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->ingredientlist = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column15 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column14 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column7 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column8 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column9 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column10 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column11 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column12 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column13 = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
			this->toollist = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn15 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn16 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn17 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewButtonColumn2 = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
			this->dataGridViewButtonColumn3 = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
			this->decorationlist = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn18 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn19 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn20 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column17 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewButtonColumn4 = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
			this->Column16 = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
			this->customer_statistics_list = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn21 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn22 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->recipe_statistics_list = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn23 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn24 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->button_history = (gcnew System::Windows::Forms::Button());
			this->button_recipe = (gcnew System::Windows::Forms::Button());
			this->button_tool_decoration = (gcnew System::Windows::Forms::Button());
			this->button_ingredient = (gcnew System::Windows::Forms::Button());
			this->button_torunning = (gcnew System::Windows::Forms::Button());
			this->recipelist = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn10 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn12 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn13 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column18 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn14 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewButtonColumn1 = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
			this->dataGridViewButtonColumn5 = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
			this->button_save = (gcnew System::Windows::Forms::Button());
			this->button_load = (gcnew System::Windows::Forms::Button());
			this->label_time = (gcnew System::Windows::Forms::Label());
			this->label_maxrecipe = (gcnew System::Windows::Forms::Label());
			this->pictureBox_interface = (gcnew System::Windows::Forms::PictureBox());
			this->label_currentrecipe = (gcnew System::Windows::Forms::Label());
			this->clock2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->button_data1 = (gcnew System::Windows::Forms::Button());
			this->button_data2 = (gcnew System::Windows::Forms::Button());
			this->button_data4 = (gcnew System::Windows::Forms::Button());
			this->button_data3 = (gcnew System::Windows::Forms::Button());
			this->label_interface = (gcnew System::Windows::Forms::Label());
			this->button_return = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ingredientlist))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->toollist))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->decorationlist))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->customer_statistics_list))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->recipe_statistics_list))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->recipelist))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox_interface))->BeginInit();
			this->SuspendLayout();
			// 
			// ingredientlist
			// 
			this->ingredientlist->AllowUserToAddRows = false;
			this->ingredientlist->AllowUserToDeleteRows = false;
			this->ingredientlist->AllowUserToResizeColumns = false;
			this->ingredientlist->AllowUserToResizeRows = false;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			this->ingredientlist->AlternatingRowsDefaultCellStyle = dataGridViewCellStyle1;
			this->ingredientlist->BackgroundColor = System::Drawing::Color::White;
			this->ingredientlist->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::Raised;
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle2->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			dataGridViewCellStyle2->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::Color::White;
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->ingredientlist->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle2;
			this->ingredientlist->ColumnHeadersHeight = 30;
			this->ingredientlist->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->ingredientlist->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(15) {this->Column1, 
				this->Column15, this->Column14, this->Column2, this->Column3, this->Column4, this->Column5, this->Column6, this->Column7, this->Column8, 
				this->Column9, this->Column10, this->Column11, this->Column12, this->Column13});
			dataGridViewCellStyle7->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle7->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle7->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			dataGridViewCellStyle7->ForeColor = System::Drawing::Color::Blue;
			dataGridViewCellStyle7->SelectionBackColor = System::Drawing::Color::White;
			dataGridViewCellStyle7->SelectionForeColor = System::Drawing::Color::Blue;
			dataGridViewCellStyle7->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->ingredientlist->DefaultCellStyle = dataGridViewCellStyle7;
			this->ingredientlist->Enabled = false;
			this->ingredientlist->EnableHeadersVisualStyles = false;
			this->ingredientlist->GridColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->ingredientlist->Location = System::Drawing::Point(24, 78);
			this->ingredientlist->Name = L"ingredientlist";
			this->ingredientlist->RowHeadersVisible = false;
			this->ingredientlist->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->ingredientlist->RowTemplate->Height = 27;
			this->ingredientlist->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->ingredientlist->Size = System::Drawing::Size(919, 485);
			this->ingredientlist->TabIndex = 20;
			this->ingredientlist->Visible = false;
			this->ingredientlist->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form2::ingredientlist_CellClick);
			// 
			// Column1
			// 
			this->Column1->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			dataGridViewCellStyle3->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle3->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle3->SelectionBackColor = System::Drawing::Color::White;
			dataGridViewCellStyle3->SelectionForeColor = System::Drawing::Color::Black;
			this->Column1->DefaultCellStyle = dataGridViewCellStyle3;
			this->Column1->FillWeight = 110;
			this->Column1->HeaderText = L"";
			this->Column1->MaxInputLength = 10;
			this->Column1->Name = L"Column1";
			this->Column1->ReadOnly = true;
			this->Column1->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Column1->Width = 85;
			// 
			// Column15
			// 
			this->Column15->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->Column15->HeaderText = L"保鮮";
			this->Column15->MaxInputLength = 3;
			this->Column15->Name = L"Column15";
			this->Column15->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Column15->Width = 45;
			// 
			// Column14
			// 
			this->Column14->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			dataGridViewCellStyle4->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle4->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle4->SelectionBackColor = System::Drawing::Color::White;
			dataGridViewCellStyle4->SelectionForeColor = System::Drawing::Color::Black;
			this->Column14->DefaultCellStyle = dataGridViewCellStyle4;
			this->Column14->HeaderText = L"單價";
			this->Column14->MaxInputLength = 4;
			this->Column14->Name = L"Column14";
			this->Column14->ReadOnly = true;
			this->Column14->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Column14->Width = 45;
			// 
			// Column2
			// 
			this->Column2->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->Column2->FillWeight = 58.49207F;
			this->Column2->HeaderText = L"1日";
			this->Column2->MaxInputLength = 3;
			this->Column2->Name = L"Column2";
			this->Column2->ReadOnly = true;
			this->Column2->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Column2->Width = 40;
			// 
			// Column3
			// 
			this->Column3->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->Column3->FillWeight = 58.49207F;
			this->Column3->HeaderText = L"2日";
			this->Column3->MaxInputLength = 3;
			this->Column3->Name = L"Column3";
			this->Column3->ReadOnly = true;
			this->Column3->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Column3->Width = 40;
			// 
			// Column4
			// 
			this->Column4->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->Column4->FillWeight = 58.49207F;
			this->Column4->HeaderText = L"3日";
			this->Column4->MaxInputLength = 3;
			this->Column4->Name = L"Column4";
			this->Column4->ReadOnly = true;
			this->Column4->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Column4->Width = 40;
			// 
			// Column5
			// 
			this->Column5->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->Column5->FillWeight = 58.49207F;
			this->Column5->HeaderText = L"4日";
			this->Column5->MaxInputLength = 3;
			this->Column5->Name = L"Column5";
			this->Column5->ReadOnly = true;
			this->Column5->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Column5->Width = 40;
			// 
			// Column6
			// 
			this->Column6->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->Column6->FillWeight = 58.49207F;
			this->Column6->HeaderText = L"5日";
			this->Column6->MaxInputLength = 3;
			this->Column6->Name = L"Column6";
			this->Column6->ReadOnly = true;
			this->Column6->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Column6->Width = 40;
			// 
			// Column7
			// 
			this->Column7->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->Column7->FillWeight = 58.49207F;
			this->Column7->HeaderText = L"6日";
			this->Column7->MaxInputLength = 3;
			this->Column7->Name = L"Column7";
			this->Column7->ReadOnly = true;
			this->Column7->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Column7->Width = 40;
			// 
			// Column8
			// 
			this->Column8->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->Column8->FillWeight = 58.49207F;
			this->Column8->HeaderText = L"7日";
			this->Column8->MaxInputLength = 3;
			this->Column8->Name = L"Column8";
			this->Column8->ReadOnly = true;
			this->Column8->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Column8->Width = 40;
			// 
			// Column9
			// 
			this->Column9->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->Column9->FillWeight = 58.49207F;
			this->Column9->HeaderText = L"8日";
			this->Column9->MaxInputLength = 3;
			this->Column9->Name = L"Column9";
			this->Column9->ReadOnly = true;
			this->Column9->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Column9->Width = 40;
			// 
			// Column10
			// 
			this->Column10->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->Column10->FillWeight = 58.49207F;
			this->Column10->HeaderText = L"9日";
			this->Column10->MaxInputLength = 3;
			this->Column10->Name = L"Column10";
			this->Column10->ReadOnly = true;
			this->Column10->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Column10->Width = 40;
			// 
			// Column11
			// 
			this->Column11->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->Column11->FillWeight = 58.49207F;
			this->Column11->HeaderText = L"終日";
			this->Column11->MaxInputLength = 3;
			this->Column11->Name = L"Column11";
			this->Column11->ReadOnly = true;
			this->Column11->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Column11->Width = 45;
			// 
			// Column12
			// 
			this->Column12->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			dataGridViewCellStyle5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			dataGridViewCellStyle5->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			dataGridViewCellStyle5->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			dataGridViewCellStyle5->SelectionForeColor = System::Drawing::Color::Fuchsia;
			this->Column12->DefaultCellStyle = dataGridViewCellStyle5;
			this->Column12->FillWeight = 58.49207F;
			this->Column12->HeaderText = L"數量";
			this->Column12->MaxInputLength = 3;
			this->Column12->Name = L"Column12";
			this->Column12->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Column12->Width = 45;
			// 
			// Column13
			// 
			this->Column13->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			dataGridViewCellStyle6->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle6->ForeColor = System::Drawing::Color::Lime;
			dataGridViewCellStyle6->SelectionForeColor = System::Drawing::Color::Lime;
			this->Column13->DefaultCellStyle = dataGridViewCellStyle6;
			this->Column13->FillWeight = 58.49207F;
			this->Column13->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Column13->HeaderText = L"確認";
			this->Column13->Name = L"Column13";
			this->Column13->Resizable = System::Windows::Forms::DataGridViewTriState::True;
			this->Column13->Text = L"購買";
			this->Column13->UseColumnTextForButtonValue = true;
			this->Column13->Width = 45;
			// 
			// toollist
			// 
			this->toollist->AllowUserToAddRows = false;
			this->toollist->AllowUserToDeleteRows = false;
			this->toollist->AllowUserToResizeColumns = false;
			this->toollist->AllowUserToResizeRows = false;
			dataGridViewCellStyle8->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			this->toollist->AlternatingRowsDefaultCellStyle = dataGridViewCellStyle8;
			this->toollist->BackgroundColor = System::Drawing::Color::White;
			this->toollist->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::Raised;
			dataGridViewCellStyle9->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle9->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle9->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			dataGridViewCellStyle9->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle9->SelectionBackColor = System::Drawing::Color::White;
			dataGridViewCellStyle9->SelectionForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle9->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->toollist->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle9;
			this->toollist->ColumnHeadersHeight = 30;
			this->toollist->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->toollist->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {this->dataGridViewTextBoxColumn15, 
				this->dataGridViewTextBoxColumn16, this->dataGridViewTextBoxColumn17, this->dataGridViewButtonColumn2, this->dataGridViewButtonColumn3});
			dataGridViewCellStyle14->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle14->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle14->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			dataGridViewCellStyle14->ForeColor = System::Drawing::Color::Blue;
			dataGridViewCellStyle14->SelectionBackColor = System::Drawing::Color::White;
			dataGridViewCellStyle14->SelectionForeColor = System::Drawing::Color::Blue;
			dataGridViewCellStyle14->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->toollist->DefaultCellStyle = dataGridViewCellStyle14;
			this->toollist->Enabled = false;
			this->toollist->EnableHeadersVisualStyles = false;
			this->toollist->GridColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->toollist->Location = System::Drawing::Point(21, 196);
			this->toollist->Name = L"toollist";
			this->toollist->RowHeadersVisible = false;
			this->toollist->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->toollist->RowTemplate->Height = 27;
			this->toollist->ScrollBars = System::Windows::Forms::ScrollBars::None;
			this->toollist->Size = System::Drawing::Size(337, 376);
			this->toollist->TabIndex = 24;
			this->toollist->Visible = false;
			this->toollist->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form2::toollist_CellClick);
			// 
			// dataGridViewTextBoxColumn15
			// 
			this->dataGridViewTextBoxColumn15->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			dataGridViewCellStyle10->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle10->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle10->SelectionBackColor = System::Drawing::Color::White;
			dataGridViewCellStyle10->SelectionForeColor = System::Drawing::Color::Black;
			this->dataGridViewTextBoxColumn15->DefaultCellStyle = dataGridViewCellStyle10;
			this->dataGridViewTextBoxColumn15->FillWeight = 110;
			this->dataGridViewTextBoxColumn15->HeaderText = L"設備";
			this->dataGridViewTextBoxColumn15->MaxInputLength = 10;
			this->dataGridViewTextBoxColumn15->Name = L"dataGridViewTextBoxColumn15";
			this->dataGridViewTextBoxColumn15->ReadOnly = true;
			this->dataGridViewTextBoxColumn15->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->dataGridViewTextBoxColumn15->Width = 70;
			// 
			// dataGridViewTextBoxColumn16
			// 
			this->dataGridViewTextBoxColumn16->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			dataGridViewCellStyle11->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle11->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle11->SelectionBackColor = System::Drawing::Color::White;
			dataGridViewCellStyle11->SelectionForeColor = System::Drawing::Color::Black;
			this->dataGridViewTextBoxColumn16->DefaultCellStyle = dataGridViewCellStyle11;
			this->dataGridViewTextBoxColumn16->HeaderText = L"價格";
			this->dataGridViewTextBoxColumn16->MaxInputLength = 5;
			this->dataGridViewTextBoxColumn16->Name = L"dataGridViewTextBoxColumn16";
			this->dataGridViewTextBoxColumn16->ReadOnly = true;
			this->dataGridViewTextBoxColumn16->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->dataGridViewTextBoxColumn16->Width = 45;
			// 
			// dataGridViewTextBoxColumn17
			// 
			this->dataGridViewTextBoxColumn17->HeaderText = L"狀態";
			this->dataGridViewTextBoxColumn17->MaxInputLength = 4;
			this->dataGridViewTextBoxColumn17->Name = L"dataGridViewTextBoxColumn17";
			this->dataGridViewTextBoxColumn17->ReadOnly = true;
			this->dataGridViewTextBoxColumn17->Width = 45;
			// 
			// dataGridViewButtonColumn2
			// 
			this->dataGridViewButtonColumn2->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			dataGridViewCellStyle12->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle12->ForeColor = System::Drawing::Color::Lime;
			dataGridViewCellStyle12->SelectionForeColor = System::Drawing::Color::Lime;
			this->dataGridViewButtonColumn2->DefaultCellStyle = dataGridViewCellStyle12;
			this->dataGridViewButtonColumn2->FillWeight = 58.49207F;
			this->dataGridViewButtonColumn2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->dataGridViewButtonColumn2->HeaderText = L"購買";
			this->dataGridViewButtonColumn2->Name = L"dataGridViewButtonColumn2";
			this->dataGridViewButtonColumn2->Resizable = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridViewButtonColumn2->Text = L"購買";
			this->dataGridViewButtonColumn2->UseColumnTextForButtonValue = true;
			this->dataGridViewButtonColumn2->Width = 45;
			// 
			// dataGridViewButtonColumn3
			// 
			dataGridViewCellStyle13->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle13->ForeColor = System::Drawing::Color::Red;
			dataGridViewCellStyle13->SelectionForeColor = System::Drawing::Color::Red;
			this->dataGridViewButtonColumn3->DefaultCellStyle = dataGridViewCellStyle13;
			this->dataGridViewButtonColumn3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->dataGridViewButtonColumn3->HeaderText = L"販售";
			this->dataGridViewButtonColumn3->Name = L"dataGridViewButtonColumn3";
			this->dataGridViewButtonColumn3->Text = L"販售";
			this->dataGridViewButtonColumn3->UseColumnTextForButtonValue = true;
			this->dataGridViewButtonColumn3->Width = 45;
			// 
			// decorationlist
			// 
			this->decorationlist->AllowUserToAddRows = false;
			this->decorationlist->AllowUserToDeleteRows = false;
			this->decorationlist->AllowUserToResizeColumns = false;
			this->decorationlist->AllowUserToResizeRows = false;
			dataGridViewCellStyle15->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			this->decorationlist->AlternatingRowsDefaultCellStyle = dataGridViewCellStyle15;
			this->decorationlist->BackgroundColor = System::Drawing::Color::White;
			this->decorationlist->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::Raised;
			dataGridViewCellStyle16->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle16->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle16->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			dataGridViewCellStyle16->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle16->SelectionBackColor = System::Drawing::Color::White;
			dataGridViewCellStyle16->SelectionForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle16->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->decorationlist->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle16;
			this->decorationlist->ColumnHeadersHeight = 30;
			this->decorationlist->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->decorationlist->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(6) {this->dataGridViewTextBoxColumn18, 
				this->dataGridViewTextBoxColumn19, this->dataGridViewTextBoxColumn20, this->Column17, this->dataGridViewButtonColumn4, this->Column16});
			dataGridViewCellStyle21->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle21->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle21->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			dataGridViewCellStyle21->ForeColor = System::Drawing::Color::Blue;
			dataGridViewCellStyle21->SelectionBackColor = System::Drawing::Color::White;
			dataGridViewCellStyle21->SelectionForeColor = System::Drawing::Color::Blue;
			dataGridViewCellStyle21->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->decorationlist->DefaultCellStyle = dataGridViewCellStyle21;
			this->decorationlist->Enabled = false;
			this->decorationlist->EnableHeadersVisualStyles = false;
			this->decorationlist->GridColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->decorationlist->Location = System::Drawing::Point(364, 196);
			this->decorationlist->Name = L"decorationlist";
			this->decorationlist->RowHeadersVisible = false;
			this->decorationlist->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->decorationlist->RowTemplate->Height = 27;
			this->decorationlist->ScrollBars = System::Windows::Forms::ScrollBars::None;
			this->decorationlist->Size = System::Drawing::Size(577, 376);
			this->decorationlist->TabIndex = 25;
			this->decorationlist->Visible = false;
			this->decorationlist->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form2::decorationlist_CellClick);
			// 
			// dataGridViewTextBoxColumn18
			// 
			this->dataGridViewTextBoxColumn18->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			dataGridViewCellStyle17->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle17->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle17->SelectionBackColor = System::Drawing::Color::White;
			dataGridViewCellStyle17->SelectionForeColor = System::Drawing::Color::Black;
			this->dataGridViewTextBoxColumn18->DefaultCellStyle = dataGridViewCellStyle17;
			this->dataGridViewTextBoxColumn18->FillWeight = 110;
			this->dataGridViewTextBoxColumn18->HeaderText = L"裝飾物";
			this->dataGridViewTextBoxColumn18->MaxInputLength = 10;
			this->dataGridViewTextBoxColumn18->Name = L"dataGridViewTextBoxColumn18";
			this->dataGridViewTextBoxColumn18->ReadOnly = true;
			this->dataGridViewTextBoxColumn18->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->dataGridViewTextBoxColumn18->Width = 70;
			// 
			// dataGridViewTextBoxColumn19
			// 
			this->dataGridViewTextBoxColumn19->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			dataGridViewCellStyle18->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle18->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle18->SelectionBackColor = System::Drawing::Color::White;
			dataGridViewCellStyle18->SelectionForeColor = System::Drawing::Color::Black;
			this->dataGridViewTextBoxColumn19->DefaultCellStyle = dataGridViewCellStyle18;
			this->dataGridViewTextBoxColumn19->HeaderText = L"價格";
			this->dataGridViewTextBoxColumn19->MaxInputLength = 5;
			this->dataGridViewTextBoxColumn19->Name = L"dataGridViewTextBoxColumn19";
			this->dataGridViewTextBoxColumn19->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->dataGridViewTextBoxColumn19->Width = 45;
			// 
			// dataGridViewTextBoxColumn20
			// 
			this->dataGridViewTextBoxColumn20->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->dataGridViewTextBoxColumn20->HeaderText = L"說明";
			this->dataGridViewTextBoxColumn20->MaxInputLength = 200;
			this->dataGridViewTextBoxColumn20->Name = L"dataGridViewTextBoxColumn20";
			this->dataGridViewTextBoxColumn20->ReadOnly = true;
			this->dataGridViewTextBoxColumn20->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->dataGridViewTextBoxColumn20->Width = 180;
			// 
			// Column17
			// 
			this->Column17->HeaderText = L"狀態";
			this->Column17->MaxInputLength = 4;
			this->Column17->Name = L"Column17";
			this->Column17->ReadOnly = true;
			this->Column17->Width = 45;
			// 
			// dataGridViewButtonColumn4
			// 
			this->dataGridViewButtonColumn4->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			dataGridViewCellStyle19->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle19->ForeColor = System::Drawing::Color::Lime;
			dataGridViewCellStyle19->SelectionForeColor = System::Drawing::Color::Lime;
			this->dataGridViewButtonColumn4->DefaultCellStyle = dataGridViewCellStyle19;
			this->dataGridViewButtonColumn4->FillWeight = 58.49207F;
			this->dataGridViewButtonColumn4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->dataGridViewButtonColumn4->HeaderText = L"購買";
			this->dataGridViewButtonColumn4->Name = L"dataGridViewButtonColumn4";
			this->dataGridViewButtonColumn4->Resizable = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridViewButtonColumn4->Text = L"購買";
			this->dataGridViewButtonColumn4->UseColumnTextForButtonValue = true;
			this->dataGridViewButtonColumn4->Width = 45;
			// 
			// Column16
			// 
			dataGridViewCellStyle20->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle20->ForeColor = System::Drawing::Color::Red;
			dataGridViewCellStyle20->SelectionForeColor = System::Drawing::Color::Red;
			this->Column16->DefaultCellStyle = dataGridViewCellStyle20;
			this->Column16->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Column16->HeaderText = L"販售";
			this->Column16->Name = L"Column16";
			this->Column16->Text = L"販售";
			this->Column16->UseColumnTextForButtonValue = true;
			this->Column16->Width = 45;
			// 
			// customer_statistics_list
			// 
			this->customer_statistics_list->AllowUserToAddRows = false;
			this->customer_statistics_list->AllowUserToDeleteRows = false;
			this->customer_statistics_list->AllowUserToResizeColumns = false;
			this->customer_statistics_list->AllowUserToResizeRows = false;
			dataGridViewCellStyle22->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			this->customer_statistics_list->AlternatingRowsDefaultCellStyle = dataGridViewCellStyle22;
			this->customer_statistics_list->BackgroundColor = System::Drawing::Color::White;
			this->customer_statistics_list->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::Raised;
			dataGridViewCellStyle23->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle23->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle23->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			dataGridViewCellStyle23->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle23->SelectionBackColor = System::Drawing::Color::White;
			dataGridViewCellStyle23->SelectionForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle23->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->customer_statistics_list->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle23;
			this->customer_statistics_list->ColumnHeadersHeight = 30;
			this->customer_statistics_list->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->customer_statistics_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {this->dataGridViewTextBoxColumn21, 
				this->dataGridViewTextBoxColumn22});
			dataGridViewCellStyle25->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle25->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle25->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			dataGridViewCellStyle25->ForeColor = System::Drawing::Color::Blue;
			dataGridViewCellStyle25->SelectionBackColor = System::Drawing::Color::White;
			dataGridViewCellStyle25->SelectionForeColor = System::Drawing::Color::Blue;
			dataGridViewCellStyle25->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->customer_statistics_list->DefaultCellStyle = dataGridViewCellStyle25;
			this->customer_statistics_list->Enabled = false;
			this->customer_statistics_list->EnableHeadersVisualStyles = false;
			this->customer_statistics_list->GridColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->customer_statistics_list->Location = System::Drawing::Point(529, 96);
			this->customer_statistics_list->Name = L"customer_statistics_list";
			this->customer_statistics_list->RowHeadersVisible = false;
			this->customer_statistics_list->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->customer_statistics_list->RowTemplate->Height = 27;
			this->customer_statistics_list->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->customer_statistics_list->Size = System::Drawing::Size(282, 476);
			this->customer_statistics_list->TabIndex = 26;
			this->customer_statistics_list->Visible = false;
			// 
			// dataGridViewTextBoxColumn21
			// 
			this->dataGridViewTextBoxColumn21->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			dataGridViewCellStyle24->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle24->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle24->SelectionBackColor = System::Drawing::Color::White;
			dataGridViewCellStyle24->SelectionForeColor = System::Drawing::Color::Black;
			this->dataGridViewTextBoxColumn21->DefaultCellStyle = dataGridViewCellStyle24;
			this->dataGridViewTextBoxColumn21->FillWeight = 110;
			this->dataGridViewTextBoxColumn21->HeaderText = L"顧客族群";
			this->dataGridViewTextBoxColumn21->MaxInputLength = 10;
			this->dataGridViewTextBoxColumn21->Name = L"dataGridViewTextBoxColumn21";
			this->dataGridViewTextBoxColumn21->ReadOnly = true;
			this->dataGridViewTextBoxColumn21->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->dataGridViewTextBoxColumn21->Width = 85;
			// 
			// dataGridViewTextBoxColumn22
			// 
			this->dataGridViewTextBoxColumn22->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->dataGridViewTextBoxColumn22->HeaderText = L"來訪次數";
			this->dataGridViewTextBoxColumn22->MaxInputLength = 4;
			this->dataGridViewTextBoxColumn22->Name = L"dataGridViewTextBoxColumn22";
			this->dataGridViewTextBoxColumn22->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->dataGridViewTextBoxColumn22->Width = 110;
			// 
			// recipe_statistics_list
			// 
			this->recipe_statistics_list->AllowUserToAddRows = false;
			this->recipe_statistics_list->AllowUserToDeleteRows = false;
			this->recipe_statistics_list->AllowUserToResizeColumns = false;
			this->recipe_statistics_list->AllowUserToResizeRows = false;
			dataGridViewCellStyle26->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			this->recipe_statistics_list->AlternatingRowsDefaultCellStyle = dataGridViewCellStyle26;
			this->recipe_statistics_list->BackgroundColor = System::Drawing::Color::White;
			this->recipe_statistics_list->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::Raised;
			dataGridViewCellStyle27->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle27->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle27->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			dataGridViewCellStyle27->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle27->SelectionBackColor = System::Drawing::Color::White;
			dataGridViewCellStyle27->SelectionForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle27->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->recipe_statistics_list->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle27;
			this->recipe_statistics_list->ColumnHeadersHeight = 30;
			this->recipe_statistics_list->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->recipe_statistics_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {this->dataGridViewTextBoxColumn23, 
				this->dataGridViewTextBoxColumn24});
			dataGridViewCellStyle29->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle29->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle29->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			dataGridViewCellStyle29->ForeColor = System::Drawing::Color::Blue;
			dataGridViewCellStyle29->SelectionBackColor = System::Drawing::Color::White;
			dataGridViewCellStyle29->SelectionForeColor = System::Drawing::Color::Blue;
			dataGridViewCellStyle29->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->recipe_statistics_list->DefaultCellStyle = dataGridViewCellStyle29;
			this->recipe_statistics_list->Enabled = false;
			this->recipe_statistics_list->EnableHeadersVisualStyles = false;
			this->recipe_statistics_list->GridColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->recipe_statistics_list->Location = System::Drawing::Point(149, 96);
			this->recipe_statistics_list->Name = L"recipe_statistics_list";
			this->recipe_statistics_list->RowHeadersVisible = false;
			this->recipe_statistics_list->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->recipe_statistics_list->RowTemplate->Height = 27;
			this->recipe_statistics_list->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->recipe_statistics_list->Size = System::Drawing::Size(282, 476);
			this->recipe_statistics_list->TabIndex = 27;
			this->recipe_statistics_list->Visible = false;
			// 
			// dataGridViewTextBoxColumn23
			// 
			this->dataGridViewTextBoxColumn23->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			dataGridViewCellStyle28->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle28->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle28->SelectionBackColor = System::Drawing::Color::White;
			dataGridViewCellStyle28->SelectionForeColor = System::Drawing::Color::Black;
			this->dataGridViewTextBoxColumn23->DefaultCellStyle = dataGridViewCellStyle28;
			this->dataGridViewTextBoxColumn23->FillWeight = 110;
			this->dataGridViewTextBoxColumn23->HeaderText = L"餐點名稱";
			this->dataGridViewTextBoxColumn23->MaxInputLength = 10;
			this->dataGridViewTextBoxColumn23->Name = L"dataGridViewTextBoxColumn23";
			this->dataGridViewTextBoxColumn23->ReadOnly = true;
			this->dataGridViewTextBoxColumn23->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->dataGridViewTextBoxColumn23->Width = 85;
			// 
			// dataGridViewTextBoxColumn24
			// 
			this->dataGridViewTextBoxColumn24->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->dataGridViewTextBoxColumn24->HeaderText = L"累計點餐次數";
			this->dataGridViewTextBoxColumn24->MaxInputLength = 3;
			this->dataGridViewTextBoxColumn24->Name = L"dataGridViewTextBoxColumn24";
			this->dataGridViewTextBoxColumn24->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->dataGridViewTextBoxColumn24->Width = 110;
			// 
			// button_history
			// 
			this->button_history->BackColor = System::Drawing::Color::Transparent;
			this->button_history->FlatAppearance->BorderSize = 0;
			this->button_history->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->button_history->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->button_history->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_history->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_history->ForeColor = System::Drawing::Color::White;
			this->button_history->Location = System::Drawing::Point(765, 659);
			this->button_history->Name = L"button_history";
			this->button_history->Size = System::Drawing::Size(230, 50);
			this->button_history->TabIndex = 28;
			this->button_history->Text = L"統計資料";
			this->button_history->UseVisualStyleBackColor = false;
			this->button_history->Click += gcnew System::EventHandler(this, &Form2::button_history_Click);
			this->button_history->MouseEnter += gcnew System::EventHandler(this, &Form2::button_history_MouseEnter);
			this->button_history->MouseLeave += gcnew System::EventHandler(this, &Form2::button_history_MouseLeave);
			// 
			// button_recipe
			// 
			this->button_recipe->BackColor = System::Drawing::Color::Transparent;
			this->button_recipe->FlatAppearance->BorderSize = 0;
			this->button_recipe->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->button_recipe->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->button_recipe->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_recipe->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_recipe->ForeColor = System::Drawing::Color::White;
			this->button_recipe->Location = System::Drawing::Point(513, 658);
			this->button_recipe->Name = L"button_recipe";
			this->button_recipe->Size = System::Drawing::Size(230, 50);
			this->button_recipe->TabIndex = 29;
			this->button_recipe->Text = L"菜單";
			this->button_recipe->UseVisualStyleBackColor = false;
			this->button_recipe->Click += gcnew System::EventHandler(this, &Form2::button_recipe_Click);
			this->button_recipe->MouseEnter += gcnew System::EventHandler(this, &Form2::button_recipe_MouseEnter);
			this->button_recipe->MouseLeave += gcnew System::EventHandler(this, &Form2::button_recipe_MouseLeave);
			// 
			// button_tool_decoration
			// 
			this->button_tool_decoration->BackColor = System::Drawing::Color::Transparent;
			this->button_tool_decoration->FlatAppearance->BorderSize = 0;
			this->button_tool_decoration->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->button_tool_decoration->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->button_tool_decoration->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_tool_decoration->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_tool_decoration->ForeColor = System::Drawing::Color::White;
			this->button_tool_decoration->Location = System::Drawing::Point(259, 658);
			this->button_tool_decoration->Name = L"button_tool_decoration";
			this->button_tool_decoration->Size = System::Drawing::Size(230, 50);
			this->button_tool_decoration->TabIndex = 30;
			this->button_tool_decoration->Text = L"設備/裝飾品";
			this->button_tool_decoration->UseVisualStyleBackColor = false;
			this->button_tool_decoration->Click += gcnew System::EventHandler(this, &Form2::button_tool_decoration_Click);
			this->button_tool_decoration->MouseEnter += gcnew System::EventHandler(this, &Form2::button_tool_decoration_MouseEnter);
			this->button_tool_decoration->MouseLeave += gcnew System::EventHandler(this, &Form2::button_tool_decoration_MouseLeave);
			// 
			// button_ingredient
			// 
			this->button_ingredient->BackColor = System::Drawing::Color::Transparent;
			this->button_ingredient->FlatAppearance->BorderSize = 0;
			this->button_ingredient->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->button_ingredient->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->button_ingredient->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_ingredient->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_ingredient->ForeColor = System::Drawing::Color::White;
			this->button_ingredient->Location = System::Drawing::Point(3, 659);
			this->button_ingredient->Name = L"button_ingredient";
			this->button_ingredient->Size = System::Drawing::Size(230, 50);
			this->button_ingredient->TabIndex = 31;
			this->button_ingredient->Text = L"食材原料";
			this->button_ingredient->UseVisualStyleBackColor = false;
			this->button_ingredient->Click += gcnew System::EventHandler(this, &Form2::button_ingredient_Click);
			this->button_ingredient->MouseEnter += gcnew System::EventHandler(this, &Form2::button_ingredient_MouseEnter);
			this->button_ingredient->MouseLeave += gcnew System::EventHandler(this, &Form2::button_ingredient_MouseLeave);
			// 
			// button_torunning
			// 
			this->button_torunning->BackColor = System::Drawing::Color::Transparent;
			this->button_torunning->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button_torunning.BackgroundImage")));
			this->button_torunning->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_torunning->FlatAppearance->BorderSize = 0;
			this->button_torunning->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_torunning->Location = System::Drawing::Point(1286, 659);
			this->button_torunning->Name = L"button_torunning";
			this->button_torunning->Size = System::Drawing::Size(50, 50);
			this->button_torunning->TabIndex = 32;
			this->button_torunning->UseVisualStyleBackColor = false;
			this->button_torunning->Click += gcnew System::EventHandler(this, &Form2::button_torunning_Click);
			this->button_torunning->MouseEnter += gcnew System::EventHandler(this, &Form2::button_torunning_MouseEnter);
			this->button_torunning->MouseLeave += gcnew System::EventHandler(this, &Form2::button_torunning_MouseLeave);
			// 
			// recipelist
			// 
			this->recipelist->AllowUserToAddRows = false;
			this->recipelist->AllowUserToDeleteRows = false;
			this->recipelist->AllowUserToResizeColumns = false;
			this->recipelist->AllowUserToResizeRows = false;
			dataGridViewCellStyle30->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			this->recipelist->AlternatingRowsDefaultCellStyle = dataGridViewCellStyle30;
			this->recipelist->BackgroundColor = System::Drawing::Color::White;
			this->recipelist->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::Raised;
			dataGridViewCellStyle31->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle31->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle31->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			dataGridViewCellStyle31->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle31->SelectionBackColor = System::Drawing::Color::White;
			dataGridViewCellStyle31->SelectionForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle31->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->recipelist->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle31;
			this->recipelist->ColumnHeadersHeight = 30;
			this->recipelist->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->recipelist->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(7) {this->dataGridViewTextBoxColumn10, 
				this->dataGridViewTextBoxColumn12, this->dataGridViewTextBoxColumn13, this->Column18, this->dataGridViewTextBoxColumn14, this->dataGridViewButtonColumn1, 
				this->dataGridViewButtonColumn5});
			dataGridViewCellStyle36->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle36->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle36->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			dataGridViewCellStyle36->ForeColor = System::Drawing::Color::Blue;
			dataGridViewCellStyle36->SelectionBackColor = System::Drawing::Color::White;
			dataGridViewCellStyle36->SelectionForeColor = System::Drawing::Color::Blue;
			dataGridViewCellStyle36->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->recipelist->DefaultCellStyle = dataGridViewCellStyle36;
			this->recipelist->Enabled = false;
			this->recipelist->EnableHeadersVisualStyles = false;
			this->recipelist->GridColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->recipelist->Location = System::Drawing::Point(56, 98);
			this->recipelist->Name = L"recipelist";
			this->recipelist->RowHeadersVisible = false;
			this->recipelist->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->recipelist->RowTemplate->Height = 27;
			this->recipelist->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->recipelist->Size = System::Drawing::Size(860, 494);
			this->recipelist->TabIndex = 33;
			this->recipelist->Visible = false;
			this->recipelist->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form2::recipelist_CellClick);
			// 
			// dataGridViewTextBoxColumn10
			// 
			this->dataGridViewTextBoxColumn10->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			dataGridViewCellStyle32->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle32->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle32->SelectionBackColor = System::Drawing::Color::White;
			dataGridViewCellStyle32->SelectionForeColor = System::Drawing::Color::Black;
			this->dataGridViewTextBoxColumn10->DefaultCellStyle = dataGridViewCellStyle32;
			this->dataGridViewTextBoxColumn10->FillWeight = 110;
			this->dataGridViewTextBoxColumn10->HeaderText = L"菜單";
			this->dataGridViewTextBoxColumn10->MaxInputLength = 10;
			this->dataGridViewTextBoxColumn10->Name = L"dataGridViewTextBoxColumn10";
			this->dataGridViewTextBoxColumn10->ReadOnly = true;
			this->dataGridViewTextBoxColumn10->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->dataGridViewTextBoxColumn10->Width = 82;
			// 
			// dataGridViewTextBoxColumn12
			// 
			this->dataGridViewTextBoxColumn12->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			dataGridViewCellStyle33->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle33->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle33->SelectionBackColor = System::Drawing::Color::White;
			dataGridViewCellStyle33->SelectionForeColor = System::Drawing::Color::Black;
			this->dataGridViewTextBoxColumn12->DefaultCellStyle = dataGridViewCellStyle33;
			this->dataGridViewTextBoxColumn12->HeaderText = L"價格";
			this->dataGridViewTextBoxColumn12->MaxInputLength = 5;
			this->dataGridViewTextBoxColumn12->Name = L"dataGridViewTextBoxColumn12";
			this->dataGridViewTextBoxColumn12->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->dataGridViewTextBoxColumn12->Width = 45;
			// 
			// dataGridViewTextBoxColumn13
			// 
			this->dataGridViewTextBoxColumn13->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->dataGridViewTextBoxColumn13->HeaderText = L"食材需求";
			this->dataGridViewTextBoxColumn13->MaxInputLength = 200;
			this->dataGridViewTextBoxColumn13->Name = L"dataGridViewTextBoxColumn13";
			this->dataGridViewTextBoxColumn13->ReadOnly = true;
			this->dataGridViewTextBoxColumn13->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->dataGridViewTextBoxColumn13->Width = 250;
			// 
			// Column18
			// 
			this->Column18->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->Column18->HeaderText = L"設備需求";
			this->Column18->MaxInputLength = 200;
			this->Column18->Name = L"Column18";
			this->Column18->ReadOnly = true;
			this->Column18->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Column18->Width = 115;
			// 
			// dataGridViewTextBoxColumn14
			// 
			this->dataGridViewTextBoxColumn14->HeaderText = L"狀態";
			this->dataGridViewTextBoxColumn14->MaxInputLength = 4;
			this->dataGridViewTextBoxColumn14->Name = L"dataGridViewTextBoxColumn14";
			this->dataGridViewTextBoxColumn14->ReadOnly = true;
			this->dataGridViewTextBoxColumn14->Width = 45;
			// 
			// dataGridViewButtonColumn1
			// 
			this->dataGridViewButtonColumn1->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			dataGridViewCellStyle34->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle34->ForeColor = System::Drawing::Color::Lime;
			dataGridViewCellStyle34->SelectionForeColor = System::Drawing::Color::Lime;
			this->dataGridViewButtonColumn1->DefaultCellStyle = dataGridViewCellStyle34;
			this->dataGridViewButtonColumn1->FillWeight = 58.49207F;
			this->dataGridViewButtonColumn1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->dataGridViewButtonColumn1->HeaderText = L"設置";
			this->dataGridViewButtonColumn1->Name = L"dataGridViewButtonColumn1";
			this->dataGridViewButtonColumn1->Resizable = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridViewButtonColumn1->Text = L"設置";
			this->dataGridViewButtonColumn1->UseColumnTextForButtonValue = true;
			this->dataGridViewButtonColumn1->Width = 45;
			// 
			// dataGridViewButtonColumn5
			// 
			dataGridViewCellStyle35->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle35->ForeColor = System::Drawing::Color::Red;
			dataGridViewCellStyle35->SelectionForeColor = System::Drawing::Color::Red;
			this->dataGridViewButtonColumn5->DefaultCellStyle = dataGridViewCellStyle35;
			this->dataGridViewButtonColumn5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->dataGridViewButtonColumn5->HeaderText = L"卸除";
			this->dataGridViewButtonColumn5->Name = L"dataGridViewButtonColumn5";
			this->dataGridViewButtonColumn5->Text = L"卸除";
			this->dataGridViewButtonColumn5->UseColumnTextForButtonValue = true;
			this->dataGridViewButtonColumn5->Width = 45;
			// 
			// button_save
			// 
			this->button_save->BackColor = System::Drawing::Color::Transparent;
			this->button_save->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button_save.BackgroundImage")));
			this->button_save->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_save->FlatAppearance->BorderSize = 0;
			this->button_save->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_save->Location = System::Drawing::Point(1037, 652);
			this->button_save->Name = L"button_save";
			this->button_save->Size = System::Drawing::Size(102, 74);
			this->button_save->TabIndex = 35;
			this->button_save->UseVisualStyleBackColor = false;
			this->button_save->Click += gcnew System::EventHandler(this, &Form2::button_save_Click);
			this->button_save->MouseEnter += gcnew System::EventHandler(this, &Form2::button_save_MouseEnter);
			this->button_save->MouseLeave += gcnew System::EventHandler(this, &Form2::button_save_MouseLeave);
			// 
			// button_load
			// 
			this->button_load->BackColor = System::Drawing::Color::Transparent;
			this->button_load->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button_load.BackgroundImage")));
			this->button_load->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_load->FlatAppearance->BorderSize = 0;
			this->button_load->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_load->Location = System::Drawing::Point(1164, 652);
			this->button_load->Name = L"button_load";
			this->button_load->Size = System::Drawing::Size(102, 74);
			this->button_load->TabIndex = 36;
			this->button_load->UseVisualStyleBackColor = false;
			this->button_load->Click += gcnew System::EventHandler(this, &Form2::button_load_Click);
			this->button_load->MouseEnter += gcnew System::EventHandler(this, &Form2::button_load_MouseEnter);
			this->button_load->MouseLeave += gcnew System::EventHandler(this, &Form2::button_load_MouseLeave);
			// 
			// label_time
			// 
			this->label_time->AutoSize = true;
			this->label_time->BackColor = System::Drawing::Color::Transparent;
			this->label_time->Font = (gcnew System::Drawing::Font(L"標楷體", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_time->ForeColor = System::Drawing::Color::RoyalBlue;
			this->label_time->Location = System::Drawing::Point(1000, 55);
			this->label_time->Name = L"label_time";
			this->label_time->Size = System::Drawing::Size(282, 30);
			this->label_time->TabIndex = 37;
			this->label_time->Text = L"第一天 09:00 A.M.";
			// 
			// label_maxrecipe
			// 
			this->label_maxrecipe->AutoSize = true;
			this->label_maxrecipe->BackColor = System::Drawing::Color::Transparent;
			this->label_maxrecipe->Font = (gcnew System::Drawing::Font(L"標楷體", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_maxrecipe->ForeColor = System::Drawing::Color::RoyalBlue;
			this->label_maxrecipe->Location = System::Drawing::Point(1000, 108);
			this->label_maxrecipe->Name = L"label_maxrecipe";
			this->label_maxrecipe->Size = System::Drawing::Size(232, 30);
			this->label_maxrecipe->TabIndex = 38;
			this->label_maxrecipe->Text = L"最大菜單數: 20";
			// 
			// pictureBox_interface
			// 
			this->pictureBox_interface->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_interface->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox_interface.BackgroundImage")));
			this->pictureBox_interface->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox_interface->Location = System::Drawing::Point(979, 252);
			this->pictureBox_interface->Name = L"pictureBox_interface";
			this->pictureBox_interface->Size = System::Drawing::Size(368, 364);
			this->pictureBox_interface->TabIndex = 39;
			this->pictureBox_interface->TabStop = false;
			// 
			// label_currentrecipe
			// 
			this->label_currentrecipe->AutoSize = true;
			this->label_currentrecipe->BackColor = System::Drawing::Color::Transparent;
			this->label_currentrecipe->Font = (gcnew System::Drawing::Font(L"標楷體", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_currentrecipe->ForeColor = System::Drawing::Color::RoyalBlue;
			this->label_currentrecipe->Location = System::Drawing::Point(1000, 163);
			this->label_currentrecipe->Name = L"label_currentrecipe";
			this->label_currentrecipe->Size = System::Drawing::Size(232, 30);
			this->label_currentrecipe->TabIndex = 40;
			this->label_currentrecipe->Text = L"目前菜單數: 20";
			// 
			// clock2
			// 
			this->clock2->Tick += gcnew System::EventHandler(this, &Form2::clock2_Tick);
			// 
			// button_data1
			// 
			this->button_data1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(176)), 
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->button_data1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button_data1.BackgroundImage")));
			this->button_data1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_data1->FlatAppearance->BorderSize = 0;
			this->button_data1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_data1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_data1->ForeColor = System::Drawing::Color::MediumBlue;
			this->button_data1->Location = System::Drawing::Point(1016, 368);
			this->button_data1->Name = L"button_data1";
			this->button_data1->Size = System::Drawing::Size(138, 78);
			this->button_data1->TabIndex = 41;
			this->button_data1->Text = L"data1";
			this->button_data1->UseVisualStyleBackColor = false;
			this->button_data1->Click += gcnew System::EventHandler(this, &Form2::button_data1_Click);
			this->button_data1->MouseEnter += gcnew System::EventHandler(this, &Form2::button_data1_MouseEnter);
			this->button_data1->MouseLeave += gcnew System::EventHandler(this, &Form2::button_data1_MouseLeave);
			// 
			// button_data2
			// 
			this->button_data2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(176)), 
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->button_data2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button_data2.BackgroundImage")));
			this->button_data2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_data2->FlatAppearance->BorderSize = 0;
			this->button_data2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_data2->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_data2->ForeColor = System::Drawing::Color::MediumBlue;
			this->button_data2->Location = System::Drawing::Point(1174, 368);
			this->button_data2->Name = L"button_data2";
			this->button_data2->Size = System::Drawing::Size(138, 78);
			this->button_data2->TabIndex = 42;
			this->button_data2->Text = L"data2";
			this->button_data2->UseVisualStyleBackColor = false;
			this->button_data2->Click += gcnew System::EventHandler(this, &Form2::button_data2_Click);
			this->button_data2->MouseEnter += gcnew System::EventHandler(this, &Form2::button_data2_MouseEnter);
			this->button_data2->MouseLeave += gcnew System::EventHandler(this, &Form2::button_data2_MouseLeave);
			// 
			// button_data4
			// 
			this->button_data4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(176)), 
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->button_data4->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button_data4.BackgroundImage")));
			this->button_data4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_data4->FlatAppearance->BorderSize = 0;
			this->button_data4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_data4->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_data4->ForeColor = System::Drawing::Color::MediumBlue;
			this->button_data4->Location = System::Drawing::Point(1174, 472);
			this->button_data4->Name = L"button_data4";
			this->button_data4->Size = System::Drawing::Size(138, 78);
			this->button_data4->TabIndex = 44;
			this->button_data4->Text = L"data4";
			this->button_data4->UseVisualStyleBackColor = false;
			this->button_data4->Click += gcnew System::EventHandler(this, &Form2::button_data4_Click);
			this->button_data4->MouseEnter += gcnew System::EventHandler(this, &Form2::button_data4_MouseEnter);
			this->button_data4->MouseLeave += gcnew System::EventHandler(this, &Form2::button_data4_MouseLeave);
			// 
			// button_data3
			// 
			this->button_data3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(176)), 
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->button_data3->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button_data3.BackgroundImage")));
			this->button_data3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_data3->FlatAppearance->BorderSize = 0;
			this->button_data3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_data3->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_data3->ForeColor = System::Drawing::Color::MediumBlue;
			this->button_data3->Location = System::Drawing::Point(1016, 472);
			this->button_data3->Name = L"button_data3";
			this->button_data3->Size = System::Drawing::Size(138, 78);
			this->button_data3->TabIndex = 43;
			this->button_data3->Text = L"data3";
			this->button_data3->UseVisualStyleBackColor = false;
			this->button_data3->Click += gcnew System::EventHandler(this, &Form2::button_data3_Click);
			this->button_data3->MouseEnter += gcnew System::EventHandler(this, &Form2::button_data3_MouseEnter);
			this->button_data3->MouseLeave += gcnew System::EventHandler(this, &Form2::button_data3_MouseLeave);
			// 
			// label_interface
			// 
			this->label_interface->AutoSize = true;
			this->label_interface->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(176)), 
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->label_interface->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_interface->ForeColor = System::Drawing::Color::Fuchsia;
			this->label_interface->Location = System::Drawing::Point(1115, 302);
			this->label_interface->Name = L"label_interface";
			this->label_interface->Size = System::Drawing::Size(95, 38);
			this->label_interface->TabIndex = 45;
			this->label_interface->Text = L"SAVE";
			// 
			// button_return
			// 
			this->button_return->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(176)), 
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->button_return->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button_return.BackgroundImage")));
			this->button_return->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_return->FlatAppearance->BorderSize = 0;
			this->button_return->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_return->Location = System::Drawing::Point(1280, 551);
			this->button_return->Name = L"button_return";
			this->button_return->Size = System::Drawing::Size(34, 36);
			this->button_return->TabIndex = 46;
			this->button_return->UseVisualStyleBackColor = false;
			this->button_return->Click += gcnew System::EventHandler(this, &Form2::button_return_Click);
			this->button_return->MouseEnter += gcnew System::EventHandler(this, &Form2::button_return_MouseEnter);
			this->button_return->MouseLeave += gcnew System::EventHandler(this, &Form2::button_return_MouseLeave);
			// 
			// Form2
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1348, 721);
			this->Controls->Add(this->button_return);
			this->Controls->Add(this->label_interface);
			this->Controls->Add(this->button_data4);
			this->Controls->Add(this->button_data3);
			this->Controls->Add(this->button_data2);
			this->Controls->Add(this->button_data1);
			this->Controls->Add(this->label_currentrecipe);
			this->Controls->Add(this->pictureBox_interface);
			this->Controls->Add(this->label_maxrecipe);
			this->Controls->Add(this->label_time);
			this->Controls->Add(this->button_load);
			this->Controls->Add(this->button_save);
			this->Controls->Add(this->recipelist);
			this->Controls->Add(this->button_torunning);
			this->Controls->Add(this->button_ingredient);
			this->Controls->Add(this->button_tool_decoration);
			this->Controls->Add(this->button_recipe);
			this->Controls->Add(this->button_history);
			this->Controls->Add(this->recipe_statistics_list);
			this->Controls->Add(this->customer_statistics_list);
			this->Controls->Add(this->decorationlist);
			this->Controls->Add(this->toollist);
			this->Controls->Add(this->ingredientlist);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"Form2";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Form2";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ingredientlist))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->toollist))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->decorationlist))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->customer_statistics_list))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->recipe_statistics_list))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->recipelist))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox_interface))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
private: System::Void button_torunning_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->button_torunning->BackgroundImage = Image::FromFile("img\\torunning_entermouse.png");
		 }
private: System::Void button_torunning_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 this->button_torunning->BackgroundImage = Image::FromFile("img\\torunning.png");
		 }
private: System::Void button_torunning_Click(System::Object^  sender, System::EventArgs^  e) {
			label_money->Text = L"資金: "+warehouse->getFund()+"元";
			this->Visible=false;
			clock->Enabled=true;
			clock2->Enabled=false;
		 }
private: System::Void button_ingredient_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->button_ingredient->ForeColor = System::Drawing::Color::Yellow;
		 }
private: System::Void button_ingredient_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 if(currentwarehousestate!=1){
				this->button_ingredient->ForeColor = System::Drawing::Color::White;
			 }			 
		 }
private: System::Void button_tool_decoration_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->button_tool_decoration->ForeColor = System::Drawing::Color::Yellow;
		 }
private: System::Void button_tool_decoration_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 if(currentwarehousestate!=2){
				this->button_tool_decoration->ForeColor = System::Drawing::Color::White;
			 }
		 }
private: System::Void button_recipe_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->button_recipe->ForeColor = System::Drawing::Color::Yellow;
		 }
private: System::Void button_recipe_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 if(currentwarehousestate!=3){
				this->button_recipe->ForeColor = System::Drawing::Color::White;
			 }
		 }
private: System::Void button_history_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->button_history->ForeColor = System::Drawing::Color::Yellow;
		 }
private: System::Void button_history_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 if(currentwarehousestate!=4){
				this->button_history->ForeColor = System::Drawing::Color::White;
			 }
		 }
private: System::Void button_ingredient_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(currentwarehousestate!=1){
				gotowarehousestate(1);
			 }
		 }	
private: System::Void ingredientlist_CellClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			 if(e->ColumnIndex==14){
				 if(e->RowIndex>-1){
					 try{
						warehouse->buy_ingredient(e->RowIndex, Int32::Parse(this->ingredientlist->Rows[e->RowIndex]->Cells[13]->Value->ToString()));	
						this->ingredientlist->Rows[e->RowIndex]->Cells[warehouse->getDay()+2]->Value = warehouse->getIngredient(e->RowIndex)->get_remaining(warehouse->getDay());
					 }catch(Exception^ e){
					 }catch(FormatException^ e){
					 }
				}		 
			 }
		 }

private: System::Void toollist_CellClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			 if(e->ColumnIndex==3){
				 if(e->RowIndex>-1){
					 warehouse->buy_Tool(e->RowIndex);
					if( warehouse->getTool(e->RowIndex)->getExist()){
						toollist->Rows[e->RowIndex]->Cells[2]->Value = "存";
					}else{
						toollist->Rows[e->RowIndex]->Cells[2]->Value = "無";
					}			
				 }		 
			 }

			 if(e->ColumnIndex==4){
				 if(e->RowIndex>-1){
					 warehouse->sell_Tool(e->RowIndex);
					if( warehouse->getTool(e->RowIndex)->getExist()){
						toollist->Rows[e->RowIndex]->Cells[2]->Value = "存";
					}else{
						toollist->Rows[e->RowIndex]->Cells[2]->Value = "無";
					}	


					this->recipelist->Enabled=true;
					for(int i=0;i<RECIPE_TYPE_MAX;i++){
						if( warehouse->getRecipe(i)->getExist()){
							recipelist->Rows[i]->Cells[4]->Value = "存";
							}else{
						recipelist->Rows[i]->Cells[4]->Value = "無";
					}
					}
					this->recipelist->Enabled=false;

				 }		 
			 }

			label_maxrecipe->Text = L"最大菜單數: "+warehouse->getRecipeN_forpay();
			label_currentrecipe->Text = L"目前菜單數: "+warehouse->getRecipeN_current();
		 }
private: System::Void decorationlist_CellClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			 if(e->ColumnIndex==4){
				 if(e->RowIndex>-1){
					 warehouse->buy_Decoration(e->RowIndex);
					 if( warehouse->getDecoration(e->RowIndex)->getExist()){
						decorationlist->Rows[e->RowIndex]->Cells[3]->Value = "存";
					}else{
						decorationlist->Rows[e->RowIndex]->Cells[3]->Value = "無";
					}	
				 }		 
			 }

			  if(e->ColumnIndex==5){
				 if(e->RowIndex>-1){
					 warehouse->sell_Decoration(e->RowIndex);
					 if( warehouse->getDecoration(e->RowIndex)->getExist()){
						decorationlist->Rows[e->RowIndex]->Cells[3]->Value = "存";
					}else{
						decorationlist->Rows[e->RowIndex]->Cells[3]->Value = "無";
					}	
				 }		 
			 }

			  if(warehouse->getDecoration(0)->getExist()){
					form1->BackgroundImage = Image::FromFile("img\\running_normal_0.jpg");
				}else if(warehouse->getDecoration(1)->getExist()){
					form1->BackgroundImage = Image::FromFile("img\\running_normal_1.jpg");
				}else if(warehouse->getDecoration(2)->getExist()){
					form1->BackgroundImage = Image::FromFile("img\\running_normal_2.jpg");
				}else if(warehouse->getDecoration(3)->getExist()){
					form1->BackgroundImage = Image::FromFile("img\\running_normal_3.jpg");
				}else{
					form1->BackgroundImage = Image::FromFile("img\\running_normal.jpg");
				}
		 }

private: System::Void recipelist_CellClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			 if(e->ColumnIndex==5){
				 if(e->RowIndex>-1){
					 warehouse->setRecipe(e->RowIndex);
					 if( warehouse->getRecipe(e->RowIndex)->getExist()){
						recipelist->Rows[e->RowIndex]->Cells[4]->Value = "存";
					}else{
						recipelist->Rows[e->RowIndex]->Cells[4]->Value = "無";
					}	
				 }		 
			 }
			 if(e->ColumnIndex==6){
				 if(e->RowIndex>-1){
					 warehouse->resetRecipe(e->RowIndex);
					 if( warehouse->getRecipe(e->RowIndex)->getExist()){
						recipelist->Rows[e->RowIndex]->Cells[4]->Value = "存";
					}else{
						recipelist->Rows[e->RowIndex]->Cells[4]->Value = "無";
					}	
				 }		 
			 }

			label_maxrecipe->Text = L"最大菜單數: "+warehouse->getRecipeN_forpay();
			label_currentrecipe->Text = L"目前菜單數: "+warehouse->getRecipeN_current();
			 
		 }

private: System::Void button_history_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(currentwarehousestate!=4){
				gotowarehousestate(4);
			 }
		 }
private: System::Void button_tool_decoration_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(currentwarehousestate!=2){
				gotowarehousestate(2);
			 }
		 }
private: System::Void button_recipe_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(currentwarehousestate!=3){
				gotowarehousestate(3);
			 }
		 }
private: void addrow(System::Windows::Forms::DataGridView^ datagridview, int input) {
					for(int i=1;i<=input;i++)
					  datagridview->Rows->Add();
		 }
private: void gotowarehousestate(int targetstate){
				 
				 switch(currentwarehousestate){
					case 1:
						this->ingredientlist->Enabled=false;
						this->ingredientlist->Visible=false;
						this->button_ingredient->ForeColor = System::Drawing::Color::White;
						break;
					case 2:
						this->toollist->Enabled=false;
						this->decorationlist->Enabled=false;
						this->toollist->Visible=false;
						this->decorationlist->Visible=false;
						this->button_tool_decoration->ForeColor = System::Drawing::Color::White;
						break;
					case 3:
						this->recipelist->Enabled=false;
						this->recipelist->Visible=false;
						this->button_recipe->ForeColor = System::Drawing::Color::White;
						break;
					case 4:
						this->recipe_statistics_list->Enabled=false;
						this->customer_statistics_list->Enabled=false;
						this->recipe_statistics_list->Visible=false;
						this->customer_statistics_list->Visible=false;
						this->button_history->ForeColor = System::Drawing::Color::White;
						break;
				 }
				 
				 switch(targetstate){
					case 1:
						currentwarehousestate=1;
						this->BackgroundImage = Image::FromFile("img\\warehouse_ingredient.jpg");
						this->ingredientlist->Visible=true;
						this->ingredientlist->Enabled=true;
						this->button_ingredient->ForeColor = System::Drawing::Color::Yellow;
						break;
					case 2:
						currentwarehousestate=2;
						this->BackgroundImage = Image::FromFile("img\\warehouse_tool_decoration.jpg");
						this->toollist->Visible=true;
						this->decorationlist->Visible=true;
						this->toollist->Enabled=true;
						this->decorationlist->Enabled=true;
						this->button_tool_decoration->ForeColor = System::Drawing::Color::Yellow;
						break;
					case 3:
						currentwarehousestate=3;
						this->BackgroundImage = Image::FromFile("img\\warehouse_recipe.jpg");
						this->recipelist->Visible=true;
						this->recipelist->Enabled=true;
						this->button_recipe->ForeColor = System::Drawing::Color::Yellow;
						break;
					case 4:
						currentwarehousestate=4;
						this->BackgroundImage = Image::FromFile("img\\warehouse_statistics.jpg");
						this->recipe_statistics_list->Visible=true;
						this->customer_statistics_list->Visible=true;
						this->recipe_statistics_list->Enabled=true;
						this->customer_statistics_list->Enabled=true;
						this->button_history->ForeColor = System::Drawing::Color::Yellow;
						break;
				 }
			 }



private: System::Void button_save_Click(System::Object^  sender, System::EventArgs^  e) {
			 clock2->Enabled=false;
			 this->pictureBox_interface->BackgroundImage = Image::FromFile("img\\interface_save.png");	
			 label_interface->Text = L"SAVE";
			 this->button_data1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(176)), 
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			 this->button_data2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(176)), 
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			 this->button_data3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(176)), 
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			 this->button_data4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(176)), 
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			 this->label_interface->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(176)), 
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			 this->button_return->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(176)), 
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			 button_data1->Visible=true;
			 button_data2->Visible=true;
			 button_data3->Visible=true;
			 button_data4->Visible=true;
			 label_interface->Visible=true;
			 button_return->Visible=true;
			 //warehouse->save(1);
		 }
private: System::Void button_load_Click(System::Object^  sender, System::EventArgs^  e) {
			 clock2->Enabled=false;
			 this->pictureBox_interface->BackgroundImage = Image::FromFile("img\\interface_load.png");	
			 label_interface->Text = L"LOAD";
			 this->button_data1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			 this->button_data2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			 this->button_data3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			 this->button_data4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			 this->label_interface->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			 this->button_return->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			 button_data1->Visible=true;
			 button_data2->Visible=true;
			 button_data3->Visible=true;
			 button_data4->Visible=true;
			 label_interface->Visible=true;
			 button_return->Visible=true;
			 //warehouse->load(4);
		 }
private: System::Void button_save_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 button_save->BackgroundImage = Image::FromFile("img\\save_entermouse.png");
		 }
private: System::Void button_load_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 button_load->BackgroundImage = Image::FromFile("img\\load_entermouse.png");
		 }
private: System::Void button_save_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 button_save->BackgroundImage = Image::FromFile("img\\save.png");
		 }
private: System::Void button_load_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 button_load->BackgroundImage = Image::FromFile("img\\load.png");
		 }
private: System::Void clock2_Tick(System::Object^  sender, System::EventArgs^  e) {
			 screencounter++;

			 //人物眨眼處理
			if(screencounter==45){
				this->pictureBox_interface->BackgroundImage = Image::FromFile("img\\interface_closeeyes.jpg");			
			}else if(screencounter>45){
				screencounter=0;
				this->pictureBox_interface->BackgroundImage = Image::FromFile("img\\interface_normal.jpg");
			}		
		 }
private: System::Void button_data1_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(label_interface->Text->ToString() == "SAVE")
				warehouse->save(1);
			 else{
				warehouse->load(1);
				warehouse->setData_updateflag(true);
			 }
			this->Visible=false;
			clock->Enabled=true;
		 }
private: System::Void button_data2_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(label_interface->Text->ToString() == "SAVE")
				warehouse->save(2);
			 else{
				warehouse->load(2);
				warehouse->setData_updateflag(true);
			 }
			this->Visible=false;
			clock->Enabled=true;
		 }
private: System::Void button_data3_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(label_interface->Text->ToString() == "SAVE")
				warehouse->save(3);
			 else{
				warehouse->load(3);
				warehouse->setData_updateflag(true);
			 }
			this->Visible=false;
			clock->Enabled=true;
		 }
private: System::Void button_data4_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(label_interface->Text->ToString() == "SAVE")
				warehouse->save(4);
			 else{
				warehouse->load(4);
				warehouse->setData_updateflag(true);
			 }
			this->Visible=false;
			clock->Enabled=true;
		 }
private: System::Void button_data1_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			  button_data1->BackgroundImage = Image::FromFile("img\\button_savedata2.png");
			  this->button_data1->ForeColor = System::Drawing::Color::Red;
		 }
private: System::Void button_data1_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 button_data1->BackgroundImage = Image::FromFile("img\\button_savedata1.png");
			 this->button_data1->ForeColor = System::Drawing::Color::MediumBlue;
		 }
private: System::Void button_data2_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 button_data2->BackgroundImage = Image::FromFile("img\\button_savedata2.png");
			 this->button_data2->ForeColor = System::Drawing::Color::Red;
		 }
private: System::Void button_data2_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 button_data2->BackgroundImage = Image::FromFile("img\\button_savedata1.png");
			 this->button_data2->ForeColor = System::Drawing::Color::MediumBlue;
		 }
private: System::Void button_data3_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 button_data3->BackgroundImage = Image::FromFile("img\\button_savedata2.png");
			 this->button_data3->ForeColor = System::Drawing::Color::Red;
		 }
private: System::Void button_data3_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 button_data3->BackgroundImage = Image::FromFile("img\\button_savedata1.png");
			 this->button_data3->ForeColor = System::Drawing::Color::MediumBlue;
		 }
private: System::Void button_data4_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 button_data4->BackgroundImage = Image::FromFile("img\\button_savedata2.png");
			 this->button_data4->ForeColor = System::Drawing::Color::Red;
		 }
private: System::Void button_data4_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 button_data4->BackgroundImage = Image::FromFile("img\\button_savedata1.png");
			 this->button_data4->ForeColor = System::Drawing::Color::MediumBlue;
		 }
private: System::Void button_return_Click(System::Object^  sender, System::EventArgs^  e) {
			 button_data1->Visible=false;
			 button_data2->Visible=false;
			 button_data3->Visible=false;
			 button_data4->Visible=false;
			 label_interface->Visible=false;
			 button_return->Visible=false;
			 pictureBox_interface->BackgroundImage = Image::FromFile("img\\interface_normal.jpg");	
			 clock2->Enabled=true;
		 }
private: System::Void button_return_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 button_return->BackgroundImage = Image::FromFile("img\\torunning_entermouse.png");
		 }
private: System::Void button_return_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 button_return->BackgroundImage = Image::FromFile("img\\torunning.png");
		 }
};
	
}
