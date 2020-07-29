#pragma once
#include"Warehouse.h"
#include"Customer.h" 
#include"Form0.h"
namespace project_GUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Form3 ���K�n
	/// </summary>
	public ref class Form3 : public System::Windows::Forms::Form
	{
	public:
		Form3(void)
		{
			InitializeComponent();
			//
			//TODO: �b���[�J�غc�禡�{���X
			//
		}
		Form3(int x,int y,int width,int height,Warehouse^ w,Customer^ c,Form^ f,Timer^ ck,Label^ l1,Label^ l2, Form0^ ff){
			InitializeComponent();
			//
			this->Location = System::Drawing::Point(x, y);
			warehouse=w;
			customer=c;
			form1 = f;
			clock = ck;
			label_money =l1;
			label_customer = l2;
			screencounter=0;
			ranksort = new int[5];
			label6->Visible=false;
			label7->Visible=false;
			picture_winner->Visible=false;
			form0 = ff;

			ranksort = new int[5];
			tempsort = new int[5];
			//���ե�
			for(int i=0;i<5;i++){
				ranksort[i]=i;
			}

			int temp=0;
			for(int i=1;i<=warehouse->getDay();i++){
				temp+=warehouse->getServed_customer(i);
			}//temp�O�֭p�A�ȤH��

			////label��l��////
			warehouse->subFund(warehouse->getCookpay());//�����p�v����
			warehouse->ingredient_dead();//�P���L������
			label1->Text = L"����p�v�~��: -"+ warehouse->getCookpay() +"��";
			label2->Text = L"����������: "+ (warehouse->getFund() - warehouse->getPrefund()) +"��"; //�w�g�����p�v����
			label3->Text = L"���馨�\�A�ȤH��: "+ warehouse->getServed_customer(warehouse->getDay()) +"�H";
			label4->Text = L"�֭p�A�ȤH��: "+ temp +"�H";
			label5->Text = L"�L�������N�۰ʾP���A�Яd�N�C";

			//�s�@�ʵe�ݭn
			label1->Left=-800;
			label2->Left=-800;
			label3->Left=-800;
			label4->Left=-800;
			label5->Left=-800;
			clock2->Enabled=true;

			warehouse->setPrefund(warehouse->getFund());//�Nprefund��s
			warehouse->setRecipeN_forpay(warehouse->getRecipeN_current());//�N�̤j�]�m���^�_����e���ƶq
			warehouse->setDay(warehouse->getDay()+1);//��s���
		}
	protected:
		/// <summary>
		/// �M������ϥΤ����귽�C
		/// </summary>
		~Form3()
		{
			clock2->Enabled=false;	
			label_money->Text = L"���: "+warehouse->getFund()+"��";
			label_customer->Text = L"�����U��: "+warehouse->getServed_customer(warehouse->getDay())+"�H";
			clock->Enabled=true;
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// �]�p�u��һݪ��ܼơC
		int screencounter;//�ʵe�ݭn
		int *ranksort;//�ΨӨM�w�ƦW���� �V�C��N��V������ index 0 �N��Ĥ@�W
		int *tempsort;
		Warehouse^ warehouse;
		Customer^ customer;
		Form^ form1;
		Form0^ form0;
		Timer^ clock;
		Label^ label_money;
		Label^ label_customer;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  button_return;
	private: System::Windows::Forms::Timer^  clock2;
	private: System::Windows::Forms::PictureBox^  picture_winner;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::ComponentModel::IContainer^  components;

			 /// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����]�p�u��䴩�һݪ���k - �ФŨϥε{���X�s�边
		/// �ק�o�Ӥ�k�����e�C
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form3::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->button_return = (gcnew System::Windows::Forms::Button());
			this->clock2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->picture_winner = (gcnew System::Windows::Forms::PictureBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picture_winner))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"�L�n������", 22.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label1->ForeColor = System::Drawing::Color::Fuchsia;
			this->label1->Location = System::Drawing::Point(61, 87);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(747, 79);
			this->label1->TabIndex = 13;
			this->label1->Text = L"�b�b�\�]";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label2
			// 
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"�L�n������", 22.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label2->ForeColor = System::Drawing::Color::Fuchsia;
			this->label2->Location = System::Drawing::Point(61, 189);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(747, 79);
			this->label2->TabIndex = 14;
			this->label2->Text = L"�b�b�\�]";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label3
			// 
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"�L�n������", 22.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label3->ForeColor = System::Drawing::Color::Fuchsia;
			this->label3->Location = System::Drawing::Point(61, 299);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(747, 79);
			this->label3->TabIndex = 15;
			this->label3->Text = L"�b�b�\�]";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label4
			// 
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"�L�n������", 22.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label4->ForeColor = System::Drawing::Color::Fuchsia;
			this->label4->Location = System::Drawing::Point(61, 421);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(747, 79);
			this->label4->TabIndex = 16;
			this->label4->Text = L"�b�b�\�]";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label5
			// 
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->Font = (gcnew System::Drawing::Font(L"�L�n������", 22.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label5->ForeColor = System::Drawing::Color::Red;
			this->label5->Location = System::Drawing::Point(61, 527);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(747, 79);
			this->label5->TabIndex = 17;
			this->label5->Text = L"�b�b�\�]";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// button_return
			// 
			this->button_return->BackColor = System::Drawing::Color::Transparent;
			this->button_return->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button_return.BackgroundImage")));
			this->button_return->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_return->FlatAppearance->BorderSize = 0;
			this->button_return->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_return->Location = System::Drawing::Point(1286, 657);
			this->button_return->Name = L"button_return";
			this->button_return->Size = System::Drawing::Size(50, 52);
			this->button_return->TabIndex = 47;
			this->button_return->UseVisualStyleBackColor = false;
			this->button_return->Click += gcnew System::EventHandler(this, &Form3::button_return_Click);
			this->button_return->MouseEnter += gcnew System::EventHandler(this, &Form3::button_return_MouseEnter);
			this->button_return->MouseLeave += gcnew System::EventHandler(this, &Form3::button_return_MouseLeave);
			// 
			// clock2
			// 
			this->clock2->Tick += gcnew System::EventHandler(this, &Form3::clock2_Tick);
			// 
			// picture_winner
			// 
			this->picture_winner->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"picture_winner.BackgroundImage")));
			this->picture_winner->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->picture_winner->Location = System::Drawing::Point(928, 159);
			this->picture_winner->Name = L"picture_winner";
			this->picture_winner->Size = System::Drawing::Size(388, 420);
			this->picture_winner->TabIndex = 48;
			this->picture_winner->TabStop = false;
			this->picture_winner->Visible = false;
			// 
			// label6
			// 
			this->label6->BackColor = System::Drawing::Color::Transparent;
			this->label6->Font = (gcnew System::Drawing::Font(L"�з���", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label6->ForeColor = System::Drawing::Color::Red;
			this->label6->Location = System::Drawing::Point(1053, 113);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(183, 43);
			this->label6->TabIndex = 49;
			this->label6->Text = L"�Ĥ@�W";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->label6->Visible = false;
			// 
			// label7
			// 
			this->label7->BackColor = System::Drawing::Color::Transparent;
			this->label7->Font = (gcnew System::Drawing::Font(L"�з���", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label7->ForeColor = System::Drawing::Color::Red;
			this->label7->Location = System::Drawing::Point(928, 593);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(388, 43);
			this->label7->TabIndex = 50;
			this->label7->Text = L"�§b�\�]";
			this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label7->Visible = false;
			// 
			// Form3
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1348, 721);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->picture_winner);
			this->Controls->Add(this->button_return);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"Form3";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Form3";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picture_winner))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	
private: System::Void button_return_Click(System::Object^  sender, System::EventArgs^  e) {
			if(warehouse->getDay()!=11 && screencounter==5){
				label_money->Text = L"���: "+warehouse->getFund()+"��";
				label_customer->Text = L"�����U��: "+warehouse->getServed_customer(warehouse->getDay())+"�H";
				this->Visible=false;
				clock->Enabled=true;
				clock2->Enabled=false;
			}else if(screencounter==5){
				//��s�e���B�z
				this->BackgroundImage = Image::FromFile("img\\winlist.jpg");
				label1->Top += 50;
				label2->Top += 40;
				label3->Top += 30;
				label4->Top += 10;
				label5->ForeColor = System::Drawing::Color::Fuchsia;
				
				int temp;
				//�i��ƦW�p�����ܱƦW���G
				for(int i=0;i<4;i++){
					tempsort[i] = warehouse->getEnemyfund(i);
				}
				tempsort[4]=warehouse->getFund();

				for(int i=0;i<4;i++){
					for(int j=i+1;j<5;j++){
						if(tempsort[j]>tempsort[i]){
							temp=tempsort[j];
							tempsort[j]=tempsort[i];
							tempsort[i]=temp;
						}
					}
				}
				for(int i=0;i<5;i++){
					if(tempsort[i]==warehouse->getEnemyfund(0)){
						ranksort[i]=0;
					}else if(tempsort[i]==warehouse->getEnemyfund(1)){
						ranksort[i]=1;
					}else if(tempsort[i]==warehouse->getEnemyfund(2)){
						ranksort[i]=2;
					}else if(tempsort[i]==warehouse->getEnemyfund(3)){
						ranksort[i]=3;
					}else{
						ranksort[i]=4;
					}
				}
				////�K���\�](��0) �����\�](��1) �����}���\�](�q2) ��U��(��3)
				for(int i=0;i<5;i++){
					switch(i){
						case 0:
							switch(ranksort[i]){
								case 0:
									label1->Text = L"�K���\�]"+ ": " + warehouse->getEnemyfund(0) + "��";
									label7->Text = L"�K���\�]";
									picture_winner->BackgroundImage = Image::FromFile("img\\enemy0.jpg");
									break;
								case 1:
									label1->Text = L"�����\�]"+ ": " + warehouse->getEnemyfund(1) + "��";
									label7->Text = L"�����\�]";
									picture_winner->BackgroundImage = Image::FromFile("img\\enemy1.jpg");
									break;
								case 2:
									label1->Text = L"�����}���\�]"+ ": " + warehouse->getEnemyfund(2) + "��";
									label7->Text = L"�����}���\�]";
									picture_winner->BackgroundImage = Image::FromFile("img\\enemy2.jpg");
									break;
								case 3:
									label1->Text = L"��U��"+ ": " + warehouse->getEnemyfund(3) + "��";
									label7->Text = L"��U��";
									picture_winner->BackgroundImage = Image::FromFile("img\\enemy3.jpg");
									break;
								case 4:
									label1->Text = L""+warehouse->getName()+ ": " + warehouse->getFund() + "��";
									label7->Text = L""+warehouse->getName();
									picture_winner->BackgroundImage = Image::FromFile("img\\interface_normal.jpg");
									break;
							}
							break;
						case 1:
							switch(ranksort[i]){
								case 0:
									label2->Text = L"�K���\�]"+ ": " + warehouse->getEnemyfund(0) + "��";
									break;
								case 1:
									label2->Text = L"�����\�]"+ ": " + warehouse->getEnemyfund(1) + "��";
									break;
								case 2:
									label2->Text = L"�����}���\�]"+ ": " + warehouse->getEnemyfund(2) + "��";
									break;
								case 3:
									label2->Text = L"��U��"+ ": " + warehouse->getEnemyfund(3) + "��";
									break;
								case 4:
									label2->Text = L""+warehouse->getName()+ ": " + warehouse->getFund() + "��";
									break;
							}
							break;
						case 2:
							switch(ranksort[i]){
								case 0:
									label1->Text = L"�K���\�]"+ ": " + warehouse->getEnemyfund(0) + "��";
									break;
								case 1:
									label3->Text = L"�����\�]"+ ": " + warehouse->getEnemyfund(1) + "��";
									break;
								case 2:
									label3->Text = L"�����}���\�]"+ ": " + warehouse->getEnemyfund(2) + "��";
									break;
								case 3:
									label3->Text = L"��U��"+ ": " + warehouse->getEnemyfund(3) + "��";
									break;
								case 4:
									label3->Text = L""+warehouse->getName()+ ": " + warehouse->getFund() + "��";
									break;
							}
							break;
						case 3:
							switch(ranksort[i]){
								case 0:
									label4->Text = L"�K���\�]"+ ": " + warehouse->getEnemyfund(0) + "��";
									break;
								case 1:
									label4->Text = L"�����\�]"+ ": " + warehouse->getEnemyfund(1) + "��";
									break;
								case 2:
									label4->Text = L"�����}���\�]"+ ": " + warehouse->getEnemyfund(2) + "��";
									break;
								case 3:
									label4->Text = L"��U��"+ ": " + warehouse->getEnemyfund(3) + "��";
									break;
								case 4:
									label4->Text = L""+warehouse->getName()+ ": " + warehouse->getFund() + "��";
									break;
							}
							break;
						case 4:
							switch(ranksort[i]){
								case 0:
									label5->Text = L"�K���\�]"+ ": " + warehouse->getEnemyfund(0) + "��";
									break;
								case 1:
									label5->Text = L"�����\�]"+ ": " + warehouse->getEnemyfund(1) + "��";
									break;
								case 2:
									label5->Text = L"�����}���\�]"+ ": " + warehouse->getEnemyfund(2) + "��";
									break;
								case 3:
									label5->Text = L"��U��"+ ": " + warehouse->getEnemyfund(3) + "��";
									break;
								case 4:
									label5->Text = L""+warehouse->getName()+ ": " + warehouse->getFund() + "��";
									break;
							}
							break;
					}
				}
				label1->Text= L"1. "+label1->Text;
				label2->Text= L"2. "+label2->Text;
				label3->Text= L"3. "+label3->Text;
				label4->Text= L"4. "+label4->Text;
				label5->Text= L"5. "+label5->Text;
				picture_winner->Visible=true;
				label6->Visible=true;
				label7->Visible=true;

				screencounter=100;
			}else if(screencounter==100){
				
			/*warehouse = gcnew Warehouse();
			customer = gcnew Customer(warehouse->getLocation());*/
			//////////////
			//form1->Visible=true;
			form0->Visible=true;//�u�n��form0�i�H�Q�ݨ� ���U��form1 �|�ۦ��l��
			this->Visible=false;
			clock->Enabled=true;
			///////////////
			}
		 }
private: System::Void button_return_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
			  button_return->BackgroundImage = Image::FromFile("img\\torunning_entermouse.png");
		 }
private: System::Void button_return_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			  button_return->BackgroundImage = Image::FromFile("img\\torunning.png");
		 }
private: System::Void clock2_Tick(System::Object^  sender, System::EventArgs^  e) {
			 switch(screencounter){
				case 0:
					Invalidate();//���_����ơA�i�H�����{�{!!
					label1->Left+=100;
					if(label1->Left>=61){
						label1->Left=61;
						screencounter++;
					}					
					break;
				case 1:
					Invalidate();//���_����ơA�i�H�����{�{!!
					label2->Left+=100;
					if(label2->Left>=61){
						label2->Left=61;
						screencounter++;
					}					
					break;
				case 2:
					Invalidate();//���_����ơA�i�H�����{�{!!
					label3->Left+=100;
					if(label3->Left>=61){
						label3->Left=61;
						screencounter++;
					}					
					break;
				case 3:
					Invalidate();//���_����ơA�i�H�����{�{!!
					label4->Left+=100;
					if(label4->Left>=61){
						label4->Left=61;
						screencounter++;
					}					
					break;
				case 4:
					Invalidate();//���_����ơA�i�H�����{�{!!
					label5->Left+=100;
					if(label5->Left>=61){
						label5->Left=61;
						screencounter++;
					}					
					break;
				case 5:
					clock2->Enabled=false;		
					break;
			 }
		 }
};
}
