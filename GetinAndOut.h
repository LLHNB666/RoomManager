#ifndef CHECKINANDOUT_H//该文件用于入住和退房的声明
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
    friend bool isLeapYear(int year);//判断闰年
    friend bool isValidDate(int year, int month, int day);//判断日期是否合法
    friend bool isValidDate2(string, string, string);
    friend int cout_day(Date&, Date&);//计算日期差
};

class CheckIn {
public:
	CheckIn(int reservation_id=0, int guest_id=0,const string p="暂无", int room_number = 0, Date check_in_time = Date(0, 0, 0));
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
	int reservation_id_;//订房编号
	int guest_id_;//顾客编号
    string phone;//手机号
	int room_number_;//房间号
	Date check_in_time_;//入住日期
};

class CheckOut:public CheckIn{
public:
    CheckOut(int reservation_id=0, int guest_id=0,const string number="暂无", int room_number = 0, Date check_in_time = Date(0, 0, 0), Date check_out_time = Date(0, 0, 0), double amount = 0.0);
    Date get_check_out_time() const;
    double get_amount() const;
    void print() ;
    int get_out_year() const;
    int get_out_month() const;
    int get_out_day() const;
    friend istream& operator>>(istream& is, CheckOut&);
    friend ostream& operator<<(ostream& os, const CheckOut&);
private:
    Date check_out_time_;//退房日期
    double amount_;//实付价格
};

#endif