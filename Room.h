#ifndef ROOM_H//���ļ����ڷ����������
#define ROOM_H
#include <iostream>
#include<string>
using namespace std;



class Room {
public:
    Room(int room_number=0, const string room_type="����", double price=0.0);
    int get_room_number() const;
    string get_room_type() const;
    double get_price() const;
    string get_status() const;

    void set_status(const string& status);
    void set_room_number(int num);
    void set_price(int money);
    void set_type(const string&);

private:
    int room_number_;
    string room_type_;
    double price_;
    string status_;
};


#endif