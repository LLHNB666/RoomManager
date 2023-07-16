#ifndef MANAGER_H//�������ļ����ڽ���ı任
#define MANAGER_H
#include"Guest.h"
#include"Room.h"
#include"GetinAndOut.h"
#include"VIP.h"
#include<fstream>
#include<vector>

class Manager {
public:

    //���������
    void add_rooms(const vector<Room>& new_rooms);//��β������
    void add_rooms2(int target_room_number);//���м���루������ͷ��
    void delete_room(int room_number);//ɾ��ָ������
    void reset_room_price(string&);//�޸��ض����ͷ���۸�
    void reset_room_all_message(int);//�޸�ָ��������Ϣ
    void initialize_room_message();//��ʼ����������



    //���������
  
    void add_guest(const string,const string,const string);//�����Ϣ��guest.txt
    void check_in();//��ס����
    void add_check_in_message(int, int, const string,int, Date);//������Ϣ��checkin��������Ӧ�ķ���״̬  
    void check_out();//�˷�����



    //��Ա�����
    void add_VIP();//���ӻ�Ա����;
    void del_VIP();//ɾ����Ա����;


    //��ӡ����
    template <typename T>
    void print_rooms_by_type(const T& room_type) const;//�������ӡ������Ϣ
    template <typename T>
    void print_rest_rooms_by_type(const T& room_type) const;//�������ӡ���з�����Ϣ
    void print_rooms();//�������ӡ���෿��
    void print_all_guests();//��ӡ���й˿���Ϣ
    void print_all_check_in();//��ӡ����ס�˿���Ϣ
    void print_all_check_out();//��ӡ���˷��˿���Ϣ
    void print_all_VIP();//��ӡ����VIP��Ϣ



    //��ѯ����
    void find_room_by_guest_name() ;
    void find_check_in_by_time();

    //�����ѯ
    void aquire_day_income();
    void aquire_month_income();
    void aquire_all_income();


    //�ļ�����
    friend bool if_open_ifstream(string filename);//�ж϶�ȡ�ܲ��ܴ�
    friend bool if_open_ofstream(string filename);//�жϱ����ܲ��ܴ�
    void The_First_Time();//�����һ��ʹ��ϵͳ������г�ʼ���������ȡ�ļ���
    void load_Room_message();//���ؿͷ��ļ�
    void save_Room_message();//���ڱ��淿�������
    void save_guest_message();//������͵���Ϣ
    void load_guest_message();//��ȡ������Ϣ
    void save_check_in_message();//������ס��Ϣ
    void load_check_in_message();//������ס��Ϣ
    void save_check_out_message();//�����˷���Ϣ
    void load_check_out_message();//�����˷���Ϣ
    int load_last_guest_id();//�õ����һλ�ѱ����ļ�������һλ�˿ͱ���
    void save_last_guest_id();//���ڱ���˿ͱ��
    void save_VIP_message();//���ڱ����Ա��Ϣ
    void load_VIP_message();//���ڼ��ػ�Ա��Ϣ

    //��������
    bool find_target_room_num(int);//�ж�Ŀ�귿��Ŵ治����
    vector<Room>::iterator find_room(int target_room_number);//�����ҵ�Ŀ�귿�����������λ�ò����ص����������û�ҵ�����end()
    

    vector<Room>rooms;
    vector<Guest>guests;
    vector<CheckIn>checkins;
    vector<CheckOut>checkouts;
    vector<VIP>vips;
};

#endif