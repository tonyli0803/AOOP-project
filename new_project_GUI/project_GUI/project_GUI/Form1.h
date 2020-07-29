#pragma once
#include"Warehouse.h" 
#include"Customer.h" 
#include"Form2.h"
#include"Form3.h"
#include"Form0.h"
namespace project_GUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Reflection;

	/// <summary>
	/// Form1 ���K�n
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: �b���[�J�غc�禡�{���X
			srand(time(NULL));
			////
			warehouse = gcnew Warehouse();
			customer = gcnew Customer(warehouse->getLocation());

			form0 = gcnew Form0(this->Location.X,this->Location.Y,this->Size.Width,this->Size.Height, warehouse, customer,this,clock,label_money,label_shopname,label_customer);
			form0->Visible=true;	
			clock->Enabled=true;
			
			//���U�ȨӮɡA������ɶ��A���O�U��ready�ɡA�L�k�i�J�ܮw		
		}
	protected:
		/// <summary>
		/// �M������ϥΤ����귽�C
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Timer^  clock;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::Label^  label_money;
	private: System::Windows::Forms::Label^  label_customer;
	private: System::Windows::Forms::Label^  label_time;
	private: System::Windows::Forms::Label^  label_shopname;
	private: System::Windows::Forms::Button^  button_towarehouse;
	private: System::Windows::Forms::Button^  button_stop;







	private:
		/// <summary>
		/// �]�p�u��һݪ��ܼơC
		Form0^ form0;
		Form2^ form2;
		Form3^ form3;
		PropertyInfo^ info;
		Warehouse^ warehouse;
		Customer^ customer;
		int nextcustomer_timer;//���Ȼ����0�ɡA�N���ͤU�@���U�ȡC
		int screencounter;//�ΨӰO���e������s(�Ҧp�w����)
		int timecounter;//timecounter�C�p��10����1��A�í��s�k�s�C
		int minute;//�t�ήɶ�
		int hour;//�t�ήɶ�
		int day;//�t�ήɶ�

private: System::Windows::Forms::PictureBox^  picture_customer;
private: System::Windows::Forms::Label^  talk_label;
private: System::Windows::Forms::Panel^  talk_panel;

		 bool customer_enterflag;
		 bool customer_leaveflag;
		 bool customer_ready;//���U�ȧe�{�b�e���W�A�B��í�w���A��(������)�A���X�Ь�true
		 int talktype;//�M�w��ܪ��i�檬�p�A��talk��0�A��ܨS�������ܡA���ɤ���ܹ�ܮ�
		 int talkcount;
		 int customer_maxX;//�]�w�U�ȹϧ��ܧ󪺮y�жq�̲ש�F������
		 int dx;//�]�w�U�ȹϧΨC���ܧ󪺮y�жq
		 int dy;
		 int offset;//�U�ȹϧδN�w��� �P�ù��̥��䪺���Z
		 bool changeday_flag;//�קK���ȨӦs�b�ɶi�洫��Ұ����w��
		/// </summary>

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����]�p�u��䴩�һݪ���k - �ФŨϥε{���X�s�边
		/// �ק�o�Ӥ�k�����e�C
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->clock = (gcnew System::Windows::Forms::Timer(this->components));
			this->label_money = (gcnew System::Windows::Forms::Label());
			this->label_customer = (gcnew System::Windows::Forms::Label());
			this->label_time = (gcnew System::Windows::Forms::Label());
			this->label_shopname = (gcnew System::Windows::Forms::Label());
			this->button_towarehouse = (gcnew System::Windows::Forms::Button());
			this->button_stop = (gcnew System::Windows::Forms::Button());
			this->picture_customer = (gcnew System::Windows::Forms::PictureBox());
			this->talk_label = (gcnew System::Windows::Forms::Label());
			this->talk_panel = (gcnew System::Windows::Forms::Panel());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picture_customer))->BeginInit();
			this->talk_panel->SuspendLayout();
			this->SuspendLayout();
			// 
			// clock
			// 
			this->clock->Tick += gcnew System::EventHandler(this, &Form1::clock_Tick);
			// 
			// label_money
			// 
			this->label_money->AutoSize = true;
			this->label_money->BackColor = System::Drawing::Color::Transparent;
			this->label_money->Font = (gcnew System::Drawing::Font(L"�幩�������淢", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_money->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->label_money->Location = System::Drawing::Point(12, 69);
			this->label_money->Name = L"label_money";
			this->label_money->Size = System::Drawing::Size(157, 25);
			this->label_money->TabIndex = 10;
			this->label_money->Text = L"���: 3000��";
			// 
			// label_customer
			// 
			this->label_customer->AutoSize = true;
			this->label_customer->BackColor = System::Drawing::Color::Transparent;
			this->label_customer->Font = (gcnew System::Drawing::Font(L"�幩�������淢", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_customer->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->label_customer->Location = System::Drawing::Point(12, 39);
			this->label_customer->Name = L"label_customer";
			this->label_customer->Size = System::Drawing::Size(165, 25);
			this->label_customer->TabIndex = 9;
			this->label_customer->Text = L"�����U��: 0�H";
			// 
			// label_time
			// 
			this->label_time->AutoSize = true;
			this->label_time->BackColor = System::Drawing::Color::Transparent;
			this->label_time->Font = (gcnew System::Drawing::Font(L"�幩�������淢", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_time->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->label_time->Location = System::Drawing::Point(12, 9);
			this->label_time->Name = L"label_time";
			this->label_time->Size = System::Drawing::Size(197, 25);
			this->label_time->TabIndex = 8;
			this->label_time->Text = L"��1�� 09:00 A.M.";
			// 
			// label_shopname
			// 
			this->label_shopname->BackColor = System::Drawing::Color::Transparent;
			this->label_shopname->Font = (gcnew System::Drawing::Font(L"�з���", 48, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_shopname->ForeColor = System::Drawing::Color::Black;
			this->label_shopname->Location = System::Drawing::Point(409, 15);
			this->label_shopname->Name = L"label_shopname";
			this->label_shopname->Size = System::Drawing::Size(459, 79);
			this->label_shopname->TabIndex = 11;
			this->label_shopname->Text = L"�b�b�\�]";
			this->label_shopname->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// button_towarehouse
			// 
			this->button_towarehouse->BackColor = System::Drawing::Color::Transparent;
			this->button_towarehouse->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button_towarehouse.BackgroundImage")));
			this->button_towarehouse->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_towarehouse->FlatAppearance->BorderSize = 0;
			this->button_towarehouse->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->button_towarehouse->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->button_towarehouse->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_towarehouse->ForeColor = System::Drawing::Color::Transparent;
			this->button_towarehouse->Location = System::Drawing::Point(1276, 258);
			this->button_towarehouse->Name = L"button_towarehouse";
			this->button_towarehouse->Size = System::Drawing::Size(60, 60);
			this->button_towarehouse->TabIndex = 13;
			this->button_towarehouse->UseVisualStyleBackColor = false;
			this->button_towarehouse->Click += gcnew System::EventHandler(this, &Form1::button_towarehouse_Click);
			this->button_towarehouse->MouseEnter += gcnew System::EventHandler(this, &Form1::button_towarehouse_MouseEnter);
			this->button_towarehouse->MouseLeave += gcnew System::EventHandler(this, &Form1::button_towarehouse_MouseLeave);
			// 
			// button_stop
			// 
			this->button_stop->BackColor = System::Drawing::Color::Transparent;
			this->button_stop->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button_stop.BackgroundImage")));
			this->button_stop->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_stop->FlatAppearance->BorderSize = 0;
			this->button_stop->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->button_stop->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->button_stop->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_stop->ForeColor = System::Drawing::Color::Black;
			this->button_stop->Location = System::Drawing::Point(1276, 192);
			this->button_stop->Name = L"button_stop";
			this->button_stop->Size = System::Drawing::Size(60, 60);
			this->button_stop->TabIndex = 12;
			this->button_stop->UseVisualStyleBackColor = false;
			this->button_stop->Click += gcnew System::EventHandler(this, &Form1::button_stop_Click);
			this->button_stop->MouseEnter += gcnew System::EventHandler(this, &Form1::button_stop_MouseEnter);
			this->button_stop->MouseLeave += gcnew System::EventHandler(this, &Form1::button_stop_MouseLeave);
			// 
			// picture_customer
			// 
			this->picture_customer->BackColor = System::Drawing::Color::Transparent;
			this->picture_customer->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"picture_customer.BackgroundImage")));
			this->picture_customer->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->picture_customer->Location = System::Drawing::Point(-112, 67);
			this->picture_customer->Name = L"picture_customer";
			this->picture_customer->Size = System::Drawing::Size(608, 712);
			this->picture_customer->TabIndex = 25;
			this->picture_customer->TabStop = false;
			// 
			// talk_label
			// 
			this->talk_label->AutoSize = true;
			this->talk_label->BackColor = System::Drawing::Color::Transparent;
			this->talk_label->Font = (gcnew System::Drawing::Font(L"�L�n������", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->talk_label->ForeColor = System::Drawing::Color::White;
			this->talk_label->Location = System::Drawing::Point(58, 56);
			this->talk_label->Name = L"talk_label";
			this->talk_label->Size = System::Drawing::Size(0, 36);
			this->talk_label->TabIndex = 26;
			// 
			// talk_panel
			// 
			this->talk_panel->BackColor = System::Drawing::Color::Transparent;
			this->talk_panel->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"talk_panel.BackgroundImage")));
			this->talk_panel->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->talk_panel->Controls->Add(this->talk_label);
			this->talk_panel->Location = System::Drawing::Point(556, 97);
			this->talk_panel->Name = L"talk_panel";
			this->talk_panel->Size = System::Drawing::Size(366, 322);
			this->talk_panel->TabIndex = 27;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1348, 721);
			this->Controls->Add(this->talk_panel);
			this->Controls->Add(this->picture_customer);
			this->Controls->Add(this->button_towarehouse);
			this->Controls->Add(this->button_stop);
			this->Controls->Add(this->label_shopname);
			this->Controls->Add(this->label_money);
			this->Controls->Add(this->label_customer);
			this->Controls->Add(this->label_time);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picture_customer))->EndInit();
			this->talk_panel->ResumeLayout(false);
			this->talk_panel->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			 }

			 /*�]�p�v�ۭq����k*/
	private: void initialscreen(int startsrc){
				switch(startsrc){
					case 0:
						break;
					case 1:
						day=1;
						hour=9;
						minute=0;
					//	this->clock->Enabled = true;
						break;
					case 2:
						break;
					case 3:
						break;
					default:
						break;
				}
			 }
	
						/*label_money->Text = L"���: "+warehouse->getFund()+"��";
						label_customer->Text = L"�����U��: "+served_customer[day]+"�H";*/
	
		/*�]�p�v�ۭq����k����*/

	private: System::Void clock_Tick(System::Object^  sender, System::EventArgs^  e) {
								 
				 //���ե�
				 if(form0->Visible){
					 form0->Visible=false;
					 //����
					warehouse = gcnew Warehouse();
					customer = gcnew Customer(warehouse->getLocation());

					form0 = gcnew Form0(this->Location.X,this->Location.Y,this->Size.Width,this->Size.Height, warehouse, customer,this,clock,label_money,label_shopname,label_customer);
					form0->Visible=true;
					this->Visible=false;
					 customer_enterflag=false;
						customer_leaveflag=false;
						customer_ready=false;
							talktype=0;
						nextcustomer_timer=30;
							talk_panel->Visible=false;
						talk_label->Visible=false;
						changeday_flag=false;
	
					///���F�����Ϥ��@��}�l�X�{�b�ù��W�A���p���B�z
						this->picture_customer->Left=-800;
						initialscreen(1);

						clock->Enabled=false;
				 }
				



				 /*�O�_���Nwarehouse�̪��ɶ��൹form1*/
						if(warehouse->getData_updateflag()){
							warehouse->setData_updateflag(false);
							day=warehouse->getDay();
							hour=warehouse->getHour();
							minute=warehouse->getMinute();
							label_money->Text = L"���: "+warehouse->getFund()+"��";
							label_customer->Text = L"�����U��: "+warehouse->getServed_customer(warehouse->getDay())+"�H";
							label_shopname->Text = L""+warehouse->getName();
						}

					screencounter++;		
					timecounter++;
					//�U�ȶi���˼ƳB�z
					if(nextcustomer_timer>0){
						nextcustomer_timer--;
						if(nextcustomer_timer==0){
							customer = gcnew Customer(warehouse->getLocation());
							customer_enterflag=true;
							switch(customer->get_ID()){
								case 0:
									offset=10;
									this->picture_customer->BackgroundImage = Image::FromFile("img\\customer_0.png");
									this->picture_customer->Size.Width=378;
									this->picture_customer->Size.Height=655;
									this->picture_customer->Left= -this->picture_customer->Size.Width;
									this->picture_customer->Top= 731;
									customer_maxX= offset +this->picture_customer->Size.Width;
									dx= (offset+this->picture_customer->Size.Width)/10;
									dy= this->picture_customer->Size.Height/10;
									break;
								case 1:
									offset=-10;
									this->picture_customer->BackgroundImage = Image::FromFile("img\\customer_1.png");
									//this->picture_customer->Size.Width=491;
									this->picture_customer->Size.Width=550;
									this->picture_customer->Size.Height=806;
									this->picture_customer->Left= -this->picture_customer->Size.Width;
									this->picture_customer->Top= 731;
									customer_maxX= offset +this->picture_customer->Size.Width;
									dx= (offset+this->picture_customer->Size.Width)/10;
									dy= this->picture_customer->Size.Height/10;
									break;
								case 2:
									offset=-10;
									this->picture_customer->BackgroundImage = Image::FromFile("img\\customer_2.png");
									this->picture_customer->Size.Width=693;
									this->picture_customer->Size.Height=822;
									this->picture_customer->Left= -this->picture_customer->Size.Width;
									this->picture_customer->Top= 731;
									customer_maxX= offset +this->picture_customer->Size.Width;
									dx= (offset+this->picture_customer->Size.Width)/10;
									dy= this->picture_customer->Size.Height/10;
									break;
								case 3:
									offset=-10;
									this->picture_customer->BackgroundImage = Image::FromFile("img\\customer_3.png");
									this->picture_customer->Size.Width=700;
									this->picture_customer->Size.Height=819;
									this->picture_customer->Left= -this->picture_customer->Size.Width;
									this->picture_customer->Top= 731;
									customer_maxX= offset +this->picture_customer->Size.Width;
									dx= (offset+this->picture_customer->Size.Width)/10;
									dy= this->picture_customer->Size.Height/10;
									break;
								case 4:
									offset=30;
									this->picture_customer->BackgroundImage = Image::FromFile("img\\customer_4.png");
									this->picture_customer->Size.Width=332;
									this->picture_customer->Size.Height=761;
									this->picture_customer->Left= -this->picture_customer->Size.Width;
									this->picture_customer->Top= 731;
									customer_maxX= offset +this->picture_customer->Size.Width;
									dx= (offset+this->picture_customer->Size.Width)/10;
									dy= this->picture_customer->Size.Height/10;
									break;
								case 5:
									offset=30;
									this->picture_customer->BackgroundImage = Image::FromFile("img\\customer_5.png");
									this->picture_customer->Size.Width=400;
									this->picture_customer->Size.Height=754;
									this->picture_customer->Left= -this->picture_customer->Size.Width;
									this->picture_customer->Top= 731;
									customer_maxX= offset +this->picture_customer->Size.Width;
									dx= (offset+this->picture_customer->Size.Width)/10;
									dy= this->picture_customer->Size.Height/10;
									break;
							}
						}
					}

					//�U�ȶi�X���B�z
					Invalidate();//���_����ơA�i�H�����{�{!!
					if(customer_leaveflag){
						this->picture_customer->Left-=dx;
						this->picture_customer->Top+=dy;
						if(this->picture_customer->Left < -this->picture_customer->Size.Width){
							customer_ready=false;
							customer_leaveflag=false;

							nextcustomer_timer=100;
							for(int i=0;i<4;i++){
								if(warehouse->getLocation()==i && warehouse->getDecoration(i)->getExist()){
									nextcustomer_timer=25;
								}
							}
							
						}						
					}else if(customer_enterflag){
						this->picture_customer->Left+=dx;
						this->picture_customer->Top-=dy;
						if(this->picture_customer->Left > customer_maxX-this->picture_customer->Size.Width){
							customer_enterflag=false;
							customer_ready=true;
							talktype=1;
							talk_panel->Visible=true;
							talk_label->Visible=true;
							talk_panel->BackgroundImage = Image::FromFile("img\\talk.png");
							talk_label->Text = L"�z�n�A�w����{\n\rw(^o^)w";
							talkcount=30;
							warehouse->addCustomer_count(customer->get_ID());//�����U�Ⱥ����ƶq�[�@�A�]�t�y���H��
						}					
					}

					if(talktype!=0){
						talkcount--;
						if(talkcount==0){
							switch(talktype){
								case 1:
									talk_panel->BackgroundImage = Image::FromFile("img\\talk2.png");
									switch(customer->get_ID()){
										case 0:
											talk_label->Text = L"����...�ڭn�@��\n\r"+warehouse->getRecipe(customer->get_Decision())->getName();
											break;
										case 1:
											talk_label->Text = L"�·����ڷǳƤ@��\n\r"+warehouse->getRecipe(customer->get_Decision())->getName()+"�A����";
											break;
										case 2:
											talk_label->Text = L"�·е��ڤ@��\n\r"+warehouse->getRecipe(customer->get_Decision())->getName();
											break;
										case 3:
											talk_label->Text = L"�@��"+warehouse->getRecipe(customer->get_Decision())->getName()+"\n\r......";
											break;
										case 4:
											talk_label->Text = L"�p�n�A�ڭn�I�@��\n\r"+warehouse->getRecipe(customer->get_Decision())->getName()+"�A����";
											break;
										case 5:
											talk_label->Text = L"�ڭn�Ӥ@��\n\r"+warehouse->getRecipe(customer->get_Decision())->getName();
											break;
									}
									/*�W�[�\�I�Q�I����*/
									warehouse->getRecipe(customer->get_Decision())->addCount();
									talktype=2;
									talkcount=30;
									break;
								case 2:
									talk_panel->BackgroundImage = Image::FromFile("img\\talk.png");
									if(warehouse->getRecipe(customer->get_Decision())->getExist()){
										talk_label->Text = L"�n���A�еy�ݡC";
										talktype=3;
									}else{
										talk_label->Text = L"���n�N���A��\n\r�̩��̨S���o��\n\r�\�I......";
										talktype=6;
									}				
									talkcount=30;
									break;
								case 3:
									if(warehouse->examine_ingredient(customer->get_Decision())){
										talk_label->Text = L"�[���F�A\n\r�o�O�z���\�I!";
										talktype=4;
									}else{
										talk_label->Text = L"�z��A��p�A��\n\r���n�������F�O!";
										talktype=6;
									}					
									talkcount=30;
									break;
								case 4:
									talk_panel->BackgroundImage = Image::FromFile("img\\talk2.png");
									switch(customer->get_ID()){
										case 0:
											talk_label->Text = L"�n��A���©j�j�C";
											break;
										case 1:
											talk_label->Text = L"���W�p�F�C";
											break;
										case 2:
											talk_label->Text = L"�P�¡C";
											break;
										case 3:
											talk_label->Text = L"��C";
											break;
										case 4:
											talk_label->Text = L"�°�~Bye~";
											break;
										case 5:
											talk_label->Text = L"���¡C";
											break;
									}		
									talktype=5;
									talkcount=30;
									break;
								case 5:
									warehouse->sell_Food(customer->get_Decision());
									warehouse->addServed_customer(warehouse->getDay());
									//��s�e�����
									label_customer->Text = L"�����U��: "+warehouse->getServed_customer(warehouse->getDay())+"�H";
									label_money->Text = L"���: "+warehouse->getFund()+"��";
									talk_panel->BackgroundImage = Image::FromFile("img\\talk.png");							
									talk_label->Text = L"�w��A�ץ��{�C";
									talktype=20;//20��ܲפ�Ÿ��A����|�i�J��ܵ������A
									talkcount=20;
									break;
								case 6:
									talk_panel->BackgroundImage = Image::FromFile("img\\talk2.png");
									
									//�U�Ȭy���N�W�[�ĤH���
									warehouse->addEnemyfund(customer->get_ID());
									
									switch(customer->get_ID()){
										case 0:
											talk_label->Text = L"���...�n�a...��\n\r�ڥh�O���ݬݤF";
											break;
										case 1:
											talk_label->Text = L"�o�˰�...���S��\n\r�k�F......";
											break;
										case 2:
											talk_label->Text = L"���ڥu��h�O���F\n\r......";
											break;
										case 3:
											talk_label->Text = L"...........";
											break;
										case 4:
											talk_label->Text = L"��...�u�i���O! \n\r�n�a......";
											break;
										case 5:
											talk_label->Text = L"�ڪ��D�F�A\n\r���U���A���o...";
											break;
									}		
									talktype=7;
									talkcount=30;
									break;
								case 7:
									if(warehouse->getDecoration(0)->getExist()){
										this->BackgroundImage = Image::FromFile("img\\running_cry_0.jpg");
									}else if(warehouse->getDecoration(1)->getExist()){
										this->BackgroundImage = Image::FromFile("img\\running_cry_1.jpg");
									}else if(warehouse->getDecoration(2)->getExist()){
										this->BackgroundImage = Image::FromFile("img\\running_cry_2.jpg");
									}else if(warehouse->getDecoration(3)->getExist()){
										this->BackgroundImage = Image::FromFile("img\\running_cry_3.jpg");
									}else{
										this->BackgroundImage = Image::FromFile("img\\running_cry.jpg");
									}
									talk_panel->BackgroundImage = Image::FromFile("img\\talk.png");							
									talk_label->Text = L"�D�`��p!!!!!";
									talktype=21;//21��ܥ�����ѱM�βפ�Ÿ��A����|�i�J��ܵ������A
									talkcount=30;
									break;

								case 20:
									if(warehouse->getDecoration(0)->getExist()){
										this->BackgroundImage = Image::FromFile("img\\running_normal_0.jpg");
									}else if(warehouse->getDecoration(1)->getExist()){
										this->BackgroundImage = Image::FromFile("img\\running_normal_1.jpg");
									}else if(warehouse->getDecoration(2)->getExist()){
										this->BackgroundImage = Image::FromFile("img\\running_normal_2.jpg");
									}else if(warehouse->getDecoration(3)->getExist()){
										this->BackgroundImage = Image::FromFile("img\\running_normal_3.jpg");
									}else{
										this->BackgroundImage = Image::FromFile("img\\running_normal.jpg");
									}
									customer_leaveflag=true;
									talk_panel->Visible=false;
									talk_label->Visible=false;
									talktype=0;
									talkcount=0;
									break;
								case 21:
									if(warehouse->getDecoration(0)->getExist()){
										this->BackgroundImage = Image::FromFile("img\\running_normal_0.jpg");
									}else if(warehouse->getDecoration(1)->getExist()){
										this->BackgroundImage = Image::FromFile("img\\running_normal_1.jpg");
									}else if(warehouse->getDecoration(2)->getExist()){
										this->BackgroundImage = Image::FromFile("img\\running_normal_2.jpg");
									}else if(warehouse->getDecoration(3)->getExist()){
										this->BackgroundImage = Image::FromFile("img\\running_normal_3.jpg");
									}else{
										this->BackgroundImage = Image::FromFile("img\\running_normal.jpg");
									}
									customer_leaveflag=true;
									talk_panel->Visible=false;
									talk_label->Visible=false;
									talktype=0;
									talkcount=0;
									break;

							}
						
						
						}	
					}
					
					
					
					//�H���w���B�z
					if(talktype!=21){
						if(screencounter==45){
							if(warehouse->getDecoration(0)->getExist()){
								this->BackgroundImage = Image::FromFile("img\\running_closeeyes_0.jpg");
							}else if(warehouse->getDecoration(1)->getExist()){
								this->BackgroundImage = Image::FromFile("img\\running_closeeyes_1.jpg");
							}else if(warehouse->getDecoration(2)->getExist()){
								this->BackgroundImage = Image::FromFile("img\\running_closeeyes_2.jpg");
							}else if(warehouse->getDecoration(3)->getExist()){
								this->BackgroundImage = Image::FromFile("img\\running_closeeyes_3.jpg");
							}else{
								this->BackgroundImage = Image::FromFile("img\\running_closeeyes.jpg");
							}							
						}else if(screencounter>45){
							screencounter=0;
							if(warehouse->getDecoration(0)->getExist()){
								this->BackgroundImage = Image::FromFile("img\\running_normal_0.jpg");
							}else if(warehouse->getDecoration(1)->getExist()){
								this->BackgroundImage = Image::FromFile("img\\running_normal_1.jpg");
							}else if(warehouse->getDecoration(2)->getExist()){
								this->BackgroundImage = Image::FromFile("img\\running_normal_2.jpg");
							}else if(warehouse->getDecoration(3)->getExist()){
								this->BackgroundImage = Image::FromFile("img\\running_normal_3.jpg");
							}else{
								this->BackgroundImage = Image::FromFile("img\\running_normal.jpg");
							}
						}
					}
					//�����B�z
					if(timecounter==10){



						////////////
						//����P�_//
						////////////
						if(changeday_flag){
							if(!customer_ready && !customer_enterflag){
								this->clock->Enabled=false;
								warehouse->setDay(day);//����٨S��s���j��
								form3 = gcnew Form3(this->Location.X,this->Location.Y,this->Size.Width,this->Size.Height, warehouse, customer,this,clock,label_money,label_customer, form0);
								form3->Visible=true;

		
								day++;
								hour=9;
								minute=0;
								//warehouse->setDay(day);  ���i�H�b�o���s��l �n�bform3��s
								warehouse->setHour(hour);
								warehouse->setMinute(minute);
								changeday_flag=false;
							}
						}
						
						timecounter=0;
						minute++;
						if(minute==60){
							minute=0;
							hour++;
							if(hour==21){							
								changeday_flag=true;									
							}
						}
						if(hour<=12){
							if(hour>=10){
								if(minute>=10){
									this->label_time->Text = L"��"+day+"�� "+hour+":"+minute+" A.M.";
								}else{
									this->label_time->Text = L"��"+day+"�� "+hour+":0"+minute+" A.M.";
								}	
							}else{
								if(minute>=10){
									this->label_time->Text = L"��"+day+"�� 0"+hour+":"+minute+" A.M.";
								}else{
									this->label_time->Text = L"��"+day+"�� 0"+hour+":0"+minute+" A.M.";
								}	
							}					
						}else{
							if(minute>=10){
								this->label_time->Text = L"��"+day+"�� 0"+(hour-12)+":"+minute+" P.M.";
							}else{
								this->label_time->Text = L"��"+day+"�� 0"+(hour-12)+":0"+minute+" P.M.";
							}
						}	
					}
			 }
private: System::Void button_stop_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->button_stop->BackgroundImage = Image::FromFile("img\\stop_entermouse.png");
		 }
private: System::Void button_stop_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 if(this->clock->Enabled==true){
				 this->button_stop->BackgroundImage = Image::FromFile("img\\stop.png");
			 }
		 }
private: System::Void button_stop_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(this->clock->Enabled){
				this->clock->Enabled=false;
			 }else{
				 this->clock->Enabled=true;
			 }		 
		 }
private: System::Void button_towarehouse_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			 this->button_towarehouse->BackgroundImage = Image::FromFile("img\\towarehouse_entermouse.png");
		 }
private: System::Void button_towarehouse_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 this->button_towarehouse->BackgroundImage = Image::FromFile("img\\towarehouse.png");
		 }
private: System::Void button_towarehouse_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(!customer_ready && !customer_enterflag && !changeday_flag){
				this->clock->Enabled=false;
				warehouse->setDay(day);
				warehouse->setHour(hour);
				warehouse->setMinute(minute);
				form2 = gcnew Form2(this->Location.X,this->Location.Y,this->Size.Width,this->Size.Height, warehouse, customer,this,clock,label_money,label_customer);
				form2->Visible=true;
			 }		 
		 }

};

}

