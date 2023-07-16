#include"menu.h"


//���˵�
void Menu::main_menu()
{
	Manager h;
	h.The_First_Time();
	int loop = 1;
	string choice;
	while (loop)
	{
		system("cls");
		cout << "=================��ӭ���������Ϣ����ϵͳ��=================" << endl;
		cout << "=================���������²���ָ����в���:================" << endl;
		cout << "*****************1:�ͷ����ݹ������*************************" << endl;
		cout << "*****************2:���͹������*****************************" << endl;
		cout << "*****************3:�����ѯ*********************************" << endl;
		cout << "*****************4:VIP�������******************************" << endl;
		cout << "*****************0:�˳�����*********************************" << endl;
		printf("============================================================\n");
		cin >> choice;//�����ж��Ƿ�������ȷ
		if (choice == "1")  Room_menu(h);
		else if (choice == "2")  Guest_menu(h);
		else if (choice == "3") aquire_income_menu(h);
		else if (choice == "4") VIP_menu(h);
		else if (choice == "0") { system("cls"); cout << "�������ǳ�ϵͳ\n"; loop = 0; }
		else { cout << "��������������" << endl; system("pause"); }
	}
}


//����Ϊ������ع������
void Menu::Guest_menu(Manager& h) {
	int loop = 1;
	while (loop)
	{
		system("cls");
		cout<<"=================�˿͹���˵�===============================\n";
		cout<<"=================���������²���ָ����в���:================\n";
		cout<<"*****************1:�˿���ס*********************************\n";
		cout<<"*****************2:�˿��˷�*********************************\n";
		cout<<"*****************3:����ס�˿���Ϣ***************************\n";
		cout<<"*****************4:���˷��˿���Ϣ***************************\n";
		cout<<"*****************5:��ʷ���й˿���Ϣ*************************\n";
		cout<<"*****************6:��ѯ����*********************************\n";
		cout<<"*****************0���������˵�******************************\n";
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
			else { system("cls"); printf("��������������\n"); system("pause"); }
			
		
	}
}


//��ѯ����
void Menu::find_menu(Manager& h)
{
	ifstream file("guest.txt");
	if (!file)
	{
		cout << "�޷���guest.txt,�������ڵ�ǰ���޹˿���ס����";
	}
	int loop = 1;
	int choice = 0;
	while (loop)
	{
		system("cls");
		cout << "����������Ҫͨ������;����ʵ�ֲ�ѯ���ܣ�" << endl;
		cout << "����1:ͨ���˿�������ѯ��ס�����:" << endl;
		cout << "����2��ͨ����סʱ���ѯ��ס��Ϣ:" << endl;
		cout << "����0:������һ����" << endl;
		cin >> choice;
		if (choice == 1) h.find_room_by_guest_name();
		else if (choice == 2) h.find_check_in_by_time();
		else if (choice == 0) loop = 0;
		else { cout << "��������������" << endl; system("pause"); }
	}
}


//����Ϊ�ͷ���ع������
void Menu::set_room_all_message(Manager& h) {
	int loop = 1;
	while (loop) {
		system("cls");
		cout << "����������Ҫ�޸ĵ�Ŀ�귿���,�����Ҫ������һ����������0��";
		string num_str;
		cin >> num_str;
		try {
			int num =stoi(num_str);
			if (num == 0) {
				loop = 0;
				cout << "����������һ����" << std::endl;
				system("pause");
				break;
			}
			if (h.find_target_room_num(num)) {
				h.reset_room_all_message(num);
				loop = 0;
			}
			else {
				cout << "�÷���Ų����ڻ���ס��������" << endl;
				system("pause");
			}
		}
		catch (const invalid_argument& e) {
			cout << "�������������һ����Ч������" << endl;
			system("pause");
		}
		catch (const out_of_range& e) {
			cout << "�������������һ����Ч������" << endl;
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
		cout << "��������Ҫ�޸ļ۸�ķ������ͣ����뵥�˼䣬˫�˼���ͥ��,�����Ҫ�˳��밴0��ȷ�ϣ���";
		string temp;
		cin >> temp;
		if (temp == "���˼�" || temp == "˫�˼�" || temp == "��ͥ��")
		{
			h.reset_room_price(temp); loop = 0;
			
			
		}
		else if (temp == "0") { loop = 0;  }
		else {
			cout << "��������밴Ҫ������" << endl;
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
		cout << "��ѡ��" << endl;
		cout << "����1���޸�ָ���������͵ļ۸�" << endl;
		cout << "����2���޸�ָ���������Ϣ��(ע�⣺�����޷��޸Ĳ����ڵķ���)" << endl;
		cout << "����0:������һ����" << endl;
		cout << "�����룺";
		string choice="0";
		cin >> choice;
		if (choice == "1") set_room_resetPrice_menu(h);
		else if (choice == "2") set_room_all_message(h);
		else if (choice == "0") { loop = 0; cout << "�����˳�" << endl; system("pause"); }
		else { cout << "��������������" << endl; system("pause"); }
		}
	}


void Menu::del_room_menu(Manager& h)
{
	cout << "������Ŀ�귿��ţ�";
	int num;
	cin >> num;
	h.delete_room(num);
}
void Menu::add_Room2_menu(Manager& h) {
	system("cls");
	cout << "������Ŀ�귿��ţ�";
	int num;
	cin >> num;
	h.add_rooms2(num);
}
void Menu::add_Room1_menu(Manager& h) {
	int num;
	system("cls");
	cout << "��������Ҫ���Ӷ��ٸ����䣿:";
	cin >> num;
	if (num == 0) {
		cout << "������������0���޷����ӷ��䡣" << endl;
	}
	else {
		cout << "����Ҫ����ʲô���͵ķ��䣿��";
		string temp;
		cin >> temp;
		double price;
		if (temp == "����") {
			price = 100.0;
		}
		else if (temp == "˫��") {
			price = 120.0;
		}
		else if (temp == "��ͥ") {
			price = 150.0;
		}
		else {
			cout << "��Ч�ķ������͡�" << endl;
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
		cout << "��������Ҫֱ�����ӻ��ǲ��룿" << endl;
		cout << "1ֱ������" << endl;
		cout << "2����" << endl;
		cout << "0������һ����" << endl;
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "�������������һ������\n";
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
		printf("ע��:����ѡ���޸��ض��������ݣ��������ķ�������Ӱ�쵽��ס�˿͵ģ������˷�֮ǰ�ù˿͵�������۸񲻱䣺\n");
		printf("=================�������˵�===============================\n");
		printf("*****************�밴���²�������***************************\n");
		printf("*****************1:��ӡ�������з�������*********************\n");
		printf("*****************2:�޸ķ�������*****************************\n");
		printf("*****************3:���ӷ���*********************************\n");
		printf("*****************4:ɾ������*********************************\n");
		printf("*****************5:��ʼ������*******************************\n");
		printf("*****************0:������һ����*****************************\n");
		printf("============================================================\n");
		cin >> choice;//�����ж��Ƿ�������ȷ
		if (choice == "1") { system("cls"); h.print_rooms(); }
		else if (choice == "2") { system("cls"); set_room_menu(h); }
		else if (choice == "3") { add_Room_menu(h); }
		else if (choice == "4") { del_room_menu(h); }
		else if (choice == "5") { h.initialize_room_message(); }
		else if(choice=="0")    loop = 0;
		else { cout << "��������������" << endl; system("pause"); }
		}
	}


//����������
void Menu::aquire_income_menu(Manager& h)
{
	system("cls");
	ifstream file("check_out.txt");
	if (!file)
	{
		cout << "�޷���check_out�ļ������������Ϊû�й˿��˷����µģ������ԣ�" << endl;
		system("pause");
		return;
	}
	file.close();
	int loop = 1;
	while (loop)
	{
		system("cls");
		cout << "������ָ���Լ�������:" << endl;
		cout << "1:��ѯָ�����ڵ�����" << endl;
		cout << "2:��ѯĳ�µ�����" << endl;
		cout << "3:��ѯ������" << endl;
		cout << "������ָ��:" << endl;
		string choice = "0";
		cin >> choice;
		if (choice == "1") h.aquire_day_income();
		else if (choice == "2") h.aquire_month_income();
		else if (choice == "3") h.aquire_all_income();
		else if (choice == "0") loop = 0;
		else {
			cout << "��������������" << endl;
			system("pause");
		}
	}
}


//VIP�������
void Menu::VIP_menu(Manager& h)
{
	int loop = 1;
	while (loop)
	{
		system("cls");
		printf("ע��:����ѡ���޸��ض��������ݣ��������ķ�������Ӱ�쵽��ס�˿͵ģ������˷�֮ǰ�ù˿͵�������۸񲻱䣺\n");
		printf("=================VIP����˵�===============================\n");
		printf("*****************�밴���²�������***************************\n");
		printf("*****************1:���VIP*********************\n");
		printf("*****************2:ɾ��VIP*****************************\n");
		printf("*****************3:��ʾĿǰ����VIP��Ϣ*********************************\n");
		printf("*****************0:������һ����*****************************\n");
		printf("============================================================\n");
		string choice;
		cin >> choice;
		if (choice == "1") h.add_VIP();
		else if (choice == "2") h.del_VIP();
		else if (choice == "3") h.print_all_VIP();
		else if (choice == "0") loop = 0;
		else {
			cout << "��������������" << endl;
			system("pause");
		}
	}
}



	