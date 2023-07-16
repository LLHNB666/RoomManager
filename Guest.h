#ifndef GUEST_H//该文件用于宾客类的声明
#define GUEST_H
#include <iostream>
#include<string>
using namespace std;


class Guest {
public:
    Guest(int guest_id=0, const string name="暂无", const string id_number="暂无", const string phone_number="暂无");
    int get_guest_id() const;
    string get_name() const;
    string get_id_number() const;
    string get_phone_number() const;
    void print() const;
private:
    int guest_id_;//顾客编号
    string name_;//姓名
    string id_number_;//身份证号
    string phone_number_;//手机号
};



#endif


