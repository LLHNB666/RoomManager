#include"menu.h"


//主菜单
void Menu::main_menu()
{
	Manager h;
	h.The_First_Time();
	int loop = 1;
	string choice;
	while (loop)
	{
		system("cls");
		cout << "=================欢迎进入宾馆信息管理系统！=================" << endl;
		cout << "=================请输入以下操作指令进行操作:================" << endl;
		cout << "*****************1:客房数据管理界面*************************" << endl;
		cout << "*****************2:宾客管理界面*****************************" << endl;
		cout << "*****************3:收入查询*********************************" << endl;
		cout << "*****************4:VIP管理界面******************************" << endl;
		cout << "*****************0:退出程序*********************************" << endl;
		printf("============================================================\n");
		cin >> choice;//首先判断是否输入正确
		if (choice == "1")  Room_menu(h);
		else if (choice == "2")  Guest_menu(h);
		else if (choice == "3") aquire_income_menu(h);
		else if (choice == "4") VIP_menu(h);
		else if (choice == "0") { system("cls"); cout << "您即将登出系统\n"; loop = 0; }
		else { cout << "输入有误！请重试" << endl; system("pause"); }
	}
}


//以下为宾客相关管理界面
void Menu::Guest_menu(Manager& h) {
	int loop = 1;
	while (loop)
	{
		system("cls");
		cout<<"=================顾客管理菜单===============================\n";
		cout<<"=================请输入以下操作指令进行操作:================\n";
		cout<<"*****************1:顾客入住*********************************\n";
		cout<<"*****************2:顾客退房*********************************\n";
		cout<<"*****************3:已入住顾客信息***************************\n";
		cout<<"*****************4:已退房顾客信息***************************\n";
		cout<<"*****************5:历史所有顾客信息*************************\n";
		cout<<"*****************6:查询功能*********************************\n";
		cout<<"*****************0：返回主菜单******************************\n";
		cout<<"============================================================\n";
		string choice;
		cin >> choice;
			if (choice == "1") { h.check_in(); }
			else if (choice == "2") { h.check_out(); }
			else if (choice == "3") { h.print_all_check_in(); }
			else if (choice == "4") { h.print_all_check_out(); } 
			else if (choice == "5") { h.print_all_guests(); } 
			else if (choice == "6") { find_menu(h); }
			else if (choice == "0") { loop = 0; }
			else { system("cls"); printf("输入有误！请重试\n"); system("pause"); }
			
		
	}
}


//查询界面
void Menu::find_menu(Manager& h)
{
	ifstream file("guest.txt");
	if (!file)
	{
		cout << "无法打开guest.txt,可能由于当前暂无顾客入住过！";
	}
	int loop = 1;
	int choice = 0;
	while (loop)
	{
		system("cls");
		cout << "请输入您想要通过哪种途径来实现查询功能：" << endl;
		cout << "输入1:通过顾客姓名查询入住房间号:" << endl;
		cout << "输入2：通过入住时间查询入住信息:" << endl;
		cout << "输入0:返回上一界面" << endl;
		cin >> choice;
		if (choice == 1) h.find_room_by_guest_name();
		else if (choice == 2) h.find_check_in_by_time();
		else if (choice == 0) loop = 0;
		else { cout << "输入有误！请重试" << endl; system("pause"); }
	}
}


//以下为客房相关管理界面
void Menu::set_room_all_message(Manager& h) {
	int loop = 1;
	while (loop) {
		system("cls");
		cout << "请输入您需要修改的目标房间号,如果需要返回上一界面请输入0：";
		string num_str;
		cin >> num_str;
		try {
			int num =stoi(num_str);
			if (num == 0) {
				loop = 0;
				cout << "即将返回上一界面" << std::endl;
				system("pause");
				break;
			}
			if (h.find_target_room_num(num)) {
				h.reset_room_all_message(num);
				loop = 0;
			}
			else {
				cout << "该房间号不存在或在住！请重试" << endl;
				system("pause");
			}
		}
		catch (const invalid_argument& e) {
			cout << "输入错误！请输入一个有效的整数" << endl;
			system("pause");
		}
		catch (const out_of_range& e) {
			cout << "输入错误！请输入一个有效的整数" << endl;
			system("pause");
		}
	}
}
void Menu::set_room_resetPrice_menu(Manager& h)
{
	
	int loop = 1;
	
	while (loop)
	{
		system("cls");
		cout << "请输入需要修改价格的房间类型（输入单人间，双人间或家庭房,如果想要退出请按0并确认）：";
		string temp;
		cin >> temp;
		if (temp == "单人间" || temp == "双人间" || temp == "家庭房")
		{
			h.reset_room_price(temp); loop = 0;
			
			
		}
		else if (temp == "0") { loop = 0;  }
		else {
			cout << "输入错误！请按要求输入" << endl;
			system("pause");
		}
	}
}
void Menu::set_room_menu(Manager& h)
{
	int loop = 1;
	while (loop)
	{
		system("cls");
		cout << "请选择：" << endl;
		cout << "输入1：修改指定房间类型的价格。" << endl;
		cout << "输入2：修改指定房间的信息。(注意：我们无法修改不存在的房间)" << endl;
		cout << "输入0:返回上一界面" << endl;
		cout << "请输入：";
		string choice="0";
		cin >> choice;
		if (choice == "1") set_room_resetPrice_menu(h);
		else if (choice == "2") set_room_all_message(h);
		else if (choice == "0") { loop = 0; cout << "即将退出" << endl; system("pause"); }
		else { cout << "输入有误！请重试" << endl; system("pause"); }
		}
	}


void Menu::del_room_menu(Manager& h)
{
	cout << "请输入目标房间号：";
	int num;
	cin >> num;
	h.delete_room(num);
}
void Menu::add_Room2_menu(Manager& h) {
	system("cls");
	cout << "请输入目标房间号：";
	int num;
	cin >> num;
	h.add_rooms2(num);
}
void Menu::add_Room1_menu(Manager& h) {
	int num;
	system("cls");
	cout << "请问您需要增加多少个房间？:";
	cin >> num;
	if (num == 0) {
		cout << "由于您输入了0，无法增加房间。" << endl;
	}
	else {
		cout << "您需要增加什么类型的房间？：";
		string temp;
		cin >> temp;
		double price;
		if (temp == "单人") {
			price = 100.0;
		}
		else if (temp == "双人") {
			price = 120.0;
		}
		else if (temp == "家庭") {
			price = 150.0;
		}
		else {
			cout << "无效的房间类型。" << endl;
			return;
		}
		vector<Room> new_rooms;
		for (int i = 0; i < num; i++) {
			new_rooms.emplace_back(0, temp, price);
		}
		h.add_rooms(new_rooms);
	}
}
void Menu::add_Room_menu(Manager& h)
{
	int loop = 1;
	int choice;
	while (loop)
	{
		system("cls");
		cout << "请问您需要直接增加还是插入？" << endl;
		cout << "1直接增加" << endl;
		cout << "2插入" << endl;
		cout << "0返回上一界面" << endl;
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "输入错误！请输入一个整数\n";
			system("pause");
		}
		else {
			switch (choice) {
			case 1:add_Room1_menu(h); break;
			case 2:add_Room2_menu(h); break;
			case 0:loop = 0;
			}
		}
	}
}
void Menu::Room_menu(Manager& h)
{
	int loop = 1;
	string choice;
	while (loop)
	{
		system("cls");
		system("cls");
		printf("注意:除非选择修改特定房间数据，其他更改房间数据影响到在住顾客的，则在退房之前该顾客的类型与价格不变：\n");
		printf("=================房间管理菜单===============================\n");
		printf("*****************请按以下操作进行***************************\n");
		printf("*****************1:打印现有所有房间数据*********************\n");
		printf("*****************2:修改房间数据*****************************\n");
		printf("*****************3:增加房间*********************************\n");
		printf("*****************4:删减房间*********************************\n");
		printf("*****************5:初始化房间*******************************\n");
		printf("*****************0:返回上一界面*****************************\n");
		printf("============================================================\n");
		cin >> choice;//首先判断是否输入正确
		if (choice == "1") { system("cls"); h.print_rooms(); }
		else if (choice == "2") { system("cls"); set_room_menu(h); }
		else if (choice == "3") { add_Room_menu(h); }
		else if (choice == "4") { del_room_menu(h); }
		else if (choice == "5") { h.initialize_room_message(); }
		else if(choice=="0")    loop = 0;
		else { cout << "输入有误！请重试" << endl; system("pause"); }
		}
	}


//收入管理界面
void Menu::aquire_income_menu(Manager& h)
{
	system("cls");
	ifstream file("check_out.txt");
	if (!file)
	{
		cout << "无法打开check_out文件，这可能是因为没有顾客退房导致的，请重试！" << endl;
		system("pause");
		return;
	}
	file.close();
	int loop = 1;
	while (loop)
	{
		system("cls");
		cout << "请输入指令以继续操作:" << endl;
		cout << "1:查询指定日期的收入" << endl;
		cout << "2:查询某月的收入" << endl;
		cout << "3:查询总输入" << endl;
		cout << "请输入指令:" << endl;
		string choice = "0";
		cin >> choice;
		if (choice == "1") h.aquire_day_income();
		else if (choice == "2") h.aquire_month_income();
		else if (choice == "3") h.aquire_all_income();
		else if (choice == "0") loop = 0;
		else {
			cout << "输入有误！请重试" << endl;
			system("pause");
		}
	}
}


//VIP管理界面
void Menu::VIP_menu(Manager& h)
{
	int loop = 1;
	while (loop)
	{
		system("cls");
		printf("注意:除非选择修改特定房间数据，其他更改房间数据影响到在住顾客的，则在退房之前该顾客的类型与价格不变：\n");
		printf("=================VIP管理菜单===============================\n");
		printf("*****************请按以下操作进行***************************\n");
		printf("*****************1:添加VIP*********************\n");
		printf("*****************2:删减VIP*****************************\n");
		printf("*****************3:显示目前所有VIP信息*********************************\n");
		printf("*****************0:返回上一界面*****************************\n");
		printf("============================================================\n");
		string choice;
		cin >> choice;
		if (choice == "1") h.add_VIP();
		else if (choice == "2") h.del_VIP();
		else if (choice == "3") h.print_all_VIP();
		else if (choice == "0") loop = 0;
		else {
			cout << "输入有误！请重试" << endl;
			system("pause");
		}
	}
}



	