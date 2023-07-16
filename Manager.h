#ifndef MANAGER_H//该声明文件用于界面的变换
#define MANAGER_H
#include"Guest.h"
#include"Room.h"
#include"GetinAndOut.h"
#include"VIP.h"
#include<fstream>
#include<vector>

class Manager {
public:

    //房间类操作
    void add_rooms(const vector<Room>& new_rooms);//从尾部增加
    void add_rooms2(int target_room_number);//从中间插入（包括从头）
    void delete_room(int room_number);//删除指定房间
    void reset_room_price(string&);//修改特定类型房间价格
    void reset_room_all_message(int);//修改指定房间信息
    void initialize_room_message();//初始化房间数据



    //宾客类操作
  
    void add_guest(const string,const string,const string);//添加信息到guest.txt
    void check_in();//入住操作
    void add_check_in_message(int, int, const string,int, Date);//加载信息到checkin并更新相应的房间状态  
    void check_out();//退房操作



    //会员类操作
    void add_VIP();//增加会员操作;
    void del_VIP();//删除会员操作;


    //打印操作
    template <typename T>
    void print_rooms_by_type(const T& room_type) const;//按种类打印房间信息
    template <typename T>
    void print_rest_rooms_by_type(const T& room_type) const;//按种类打印空闲房间信息
    void print_rooms();//按种类打印各类房间
    void print_all_guests();//打印所有顾客信息
    void print_all_check_in();//打印已入住顾客信息
    void print_all_check_out();//打印已退房顾客信息
    void print_all_VIP();//打印所有VIP信息



    //查询操作
    void find_room_by_guest_name() ;
    void find_check_in_by_time();

    //收入查询
    void aquire_day_income();
    void aquire_month_income();
    void aquire_all_income();


    //文件操作
    friend bool if_open_ifstream(string filename);//判断读取能不能打开
    friend bool if_open_ofstream(string filename);//判断保存能不能打开
    void The_First_Time();//如果第一次使用系统，则进行初始化，否则读取文件。
    void load_Room_message();//加载客房文件
    void save_Room_message();//用于保存房间的数据
    void save_guest_message();//保存宾客的信息
    void load_guest_message();//读取宾客信息
    void save_check_in_message();//保存入住信息
    void load_check_in_message();//加载入住信息
    void save_check_out_message();//保存退房信息
    void load_check_out_message();//加载退房信息
    int load_last_guest_id();//得到最后一位已保存文件里的最后一位顾客编码
    void save_last_guest_id();//用于保存顾客编号
    void save_VIP_message();//用于保存会员信息
    void load_VIP_message();//用于加载会员信息

    //其他操作
    bool find_target_room_num(int);//判断目标房间号存不存在
    vector<Room>::iterator find_room(int target_room_number);//用来找到目标房间在容器里的位置并返回迭代器，如果没找到返回end()
    

    vector<Room>rooms;
    vector<Guest>guests;
    vector<CheckIn>checkins;
    vector<CheckOut>checkouts;
    vector<VIP>vips;
};

#endif