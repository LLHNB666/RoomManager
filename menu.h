//���ļ���Ҫд�˵�����
#ifndef MENU_H
#define MENU_H
#include"Manager.h"
#include <stdexcept>


class Menu
{
public:
	Menu() {}
	void main_menu();//���˵�
	void Guest_menu(Manager& h);//���Ͳ˵�
	void Room_menu(Manager& h);//����˵�
	void aquire_income_menu(Manager& h);//�����ѯ����
	void find_menu(Manager& h);//��ѯ�˵�
	void VIP_menu(Manager& h);//��Ա����˵�
	void set_room_all_message(Manager& h);//���跿��������Ϣ����
	void set_room_resetPrice_menu(Manager& h);//���跿��۸����
	void set_room_menu(Manager& h);//���÷������
	void del_room_menu(Manager& h);//ɾ���������
	void add_Room2_menu(Manager& h);//�м���뷿�����
	void add_Room1_menu(Manager& h);//β����ӷ������
	void add_Room_menu(Manager& h);//��ӷ������


	
};

#endif // !MENU_H