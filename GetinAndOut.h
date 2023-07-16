#ifndef CHECKINANDOUT_H//���ļ�������ס���˷�������
#define CHECKINANDOUT_H
#include<iostream>
#include<string>

using namespace std;

class Date
{
    int year;
    int month;
    int day;
public:
    Date(int y=0, int m=0, int d=0);
    int get_year() const;
    int get_month() const;
    int get_day() const;
    friend istream& operator>>(istream& is, Date& date);
    friend ostream& operator<<(ostream& os, const Date& date);
    bool operator==(const Date&) const;
    friend bool isLeapYear(int year);//�ж�����
    friend bool isValidDate(int year, int month, int day);//�ж������Ƿ�Ϸ�
    friend bool isValidDate2(string, string, string);
    friend int cout_day(Date&, Date&);//�������ڲ�
};

class CheckIn {
public:
	CheckIn(int reservation_id=0, int guest_id=0,const string p="����", int room_number = 0, Date check_in_time = Date(0, 0, 0));
	int get_reservation_id() const;
	int get_guest_id() const;
	int get_room_number() const;
	Date get_check_in_time() const;
    int get_in_year() const;
    int get_in_month() const;
    int get_in_day() const;
    string get_phone() const;
    friend istream& operator>>(istream& is, CheckIn& );
    friend ostream& operator<<(ostream& os, const CheckIn& );
    virtual void print();
protected:
	int reservation_id_;//�������
	int guest_id_;//�˿ͱ��
    string phone;//�ֻ���
	int room_number_;//�����
	Date check_in_time_;//��ס����
};

class CheckOut:public CheckIn{
public:
    CheckOut(int reservation_id=0, int guest_id=0,const string number="����", int room_number = 0, Date check_in_time = Date(0, 0, 0), Date check_out_time = Date(0, 0, 0), double amount = 0.0);
    Date get_check_out_time() const;
    double get_amount() const;
    void print() ;
    int get_out_year() const;
    int get_out_month() const;
    int get_out_day() const;
    friend istream& operator>>(istream& is, CheckOut&);
    friend ostream& operator<<(ostream& os, const CheckOut&);
private:
    Date check_out_time_;//�˷�����
    double amount_;//ʵ���۸�
};

#endif