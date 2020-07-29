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
	/// Form0 的摘要
	/// </summary>
	public ref class Form0 : public System::Windows::Forms::Form
	{
	public:
		Form0(void)
		{
			InitializeComponent();
			//
			//TODO: 在此加入建構函式程式碼
			//
		}
		Form0(int x,int y,int width,int height,Warehouse^ w,Customer^ c,Form^ f,Timer^ ck,Label^ l1,Label^ l2,Label^ l3){
			InitializeComponent();
			//
			this->Location = System::Drawing::Point(x, y);
			warehouse=w;
			customer=c;
			form1 = f;
			clock = ck;
			label_money =l1;
			label_shopname = l2;
			label_customer =l3;
			form1->Visible=false;
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~Form0()
		{
			 form1->Visible=true;
			 clock->Enabled=true;
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected: 
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;

	private:
		/// <summary>
		/// 設計工具所需的變數。
		Warehouse^ warehouse;
		Customer^ customer;
		Form^ form1;
		Timer^ clock;
		Label^ label_money;
		Label^ label_shopname;
		Label^ label_customer;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox1;
			 /// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
		/// 修改這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form0::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button1->ForeColor = System::Drawing::Color::Blue;
			this->button1->Location = System::Drawing::Point(554, 183);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(210, 72);
			this->button1->TabIndex = 0;
			this->button1->Text = L"學校";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form0::button1_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button2->ForeColor = System::Drawing::Color::Blue;
			this->button2->Location = System::Drawing::Point(554, 296);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(210, 72);
			this->button2->TabIndex = 1;
			this->button2->Text = L"體育館";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form0::button2_Click);
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button3->ForeColor = System::Drawing::Color::Blue;
			this->button3->Location = System::Drawing::Point(554, 422);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(210, 72);
			this->button3->TabIndex = 2;
			this->button3->Text = L"百貨公司";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form0::button3_Click);
			// 
			// button4
			// 
			this->button4->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button4->ForeColor = System::Drawing::Color::Blue;
			this->button4->Location = System::Drawing::Point(554, 544);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(210, 72);
			this->button4->TabIndex = 3;
			this->button4->Text = L"醫院";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form0::button4_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label1->Location = System::Drawing::Point(276, 669);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(242, 31);
			this->label1->TabIndex = 4;
			this->label1->Text = L"請輸入店名(4字為限):";
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->textBox1->Location = System::Drawing::Point(554, 667);
			this->textBox1->MaxLength = 4;
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(210, 29);
			this->textBox1->TabIndex = 5;
			this->textBox1->Text = L"呆呆餐館";
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// Form0
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1336, 709);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->DoubleBuffered = true;
			this->Name = L"Form0";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Form0";
			this->Load += gcnew System::EventHandler(this, &Form0::Form0_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Form0_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 warehouse->setLocation(0);
			 warehouse->setName(textBox1->Text->ToString());
			 label_shopname->Text = L""+warehouse->getName();
			label_money->Text = L"資金: "+warehouse->getFund()+"元";
			label_customer->Text = L"本日顧客: "+warehouse->getServed_customer(warehouse->getDay())+"人";
			 form1->Visible=true;
			 this->Visible=false;
			 clock->Enabled=true;
		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 warehouse->setLocation(1);
			 warehouse->setName(textBox1->Text->ToString());
			 label_shopname->Text = L""+warehouse->getName();
			 label_money->Text = L"資金: "+warehouse->getFund()+"元";
			label_customer->Text = L"本日顧客: "+warehouse->getServed_customer(warehouse->getDay())+"人";
			 form1->Visible=true;
			 this->Visible=false;
			 clock->Enabled=true;
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 warehouse->setLocation(2);
			 warehouse->setName(textBox1->Text->ToString());
			 label_shopname->Text = L""+warehouse->getName();
			 label_money->Text = L"資金: "+warehouse->getFund()+"元";
			label_customer->Text = L"本日顧客: "+warehouse->getServed_customer(warehouse->getDay())+"人";
			 form1->Visible=true;
			 this->Visible=false;
			 clock->Enabled=true;
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 warehouse->setLocation(3);
			 warehouse->setName(textBox1->Text->ToString());
			 label_shopname->Text = L""+warehouse->getName();
			 label_money->Text = L"資金: "+warehouse->getFund()+"元";
			label_customer->Text = L"本日顧客: "+warehouse->getServed_customer(warehouse->getDay())+"人";
			 form1->Visible=true;
			 this->Visible=false;
			 clock->Enabled=true;
		 }
};
}
