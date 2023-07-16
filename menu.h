//该文件主要写菜单声明
#ifndef MENU_H
#define MENU_H
#include"Manager.h"
#include <stdexcept>


class Menu
{
public:
	Menu() {}
	void main_menu();//主菜单
	void Guest_menu(Manager& h);//宾客菜单
	void Room_menu(Manager& h);//房间菜单
	void aquire_income_menu(Manager& h);//收入查询界面
	void find_menu(Manager& h);//查询菜单
	void VIP_menu(Manager& h);//会员管理菜单
	void set_room_all_message(Manager& h);//重设房间所有信息界面
	void set_room_resetPrice_menu(Manager& h);//重设房间价格界面
	void set_room_menu(Manager& h);//设置房间界面
	void del_room_menu(Manager& h);//删除房间界面
	void add_Room2_menu(Manager& h);//中间插入房间界面
	void add_Room1_menu(Manager& h);//尾部添加房间界面
	void add_Room_menu(Manager& h);//添加房间界面


	
};

#endif // !MENU_H