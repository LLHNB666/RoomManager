//房间类的实现
#include"Room.h"

Room::Room(int room_number, const string room_type, double price)
    : room_number_(room_number), room_type_(room_type), price_(price), status_("空闲") {}

int Room::get_room_number() const {
    return room_number_;
}

string Room::get_room_type() const {
    return room_type_;
}

double Room::get_price() const {
    return price_;
}

string Room::get_status() const {
    return status_;
}

void Room::set_status(const string& status) {
    status_ = status;
}
void Room::set_room_number(int num) {
    room_number_ = num;
}

void Room::set_price(int money) {
    price_ = money;
}

void Room::set_type(const string& p)
{
    room_type_ = p;
}