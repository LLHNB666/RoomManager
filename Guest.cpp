//
//宾客类的实现
#include"Guest.h"

Guest::Guest(int guest_id, const string name, const string id_number, const string phone_number)
    : guest_id_(guest_id), name_(name), id_number_(id_number), phone_number_(phone_number) {}

int Guest::get_guest_id() const {
    return guest_id_;
}

string Guest::get_name() const {
    return name_;
}

string Guest::get_id_number() const {
    return id_number_;
}

string Guest::get_phone_number() const {
    return phone_number_;
}


void Guest::print() const
{
    cout << "顾客编号：" << guest_id_ << " 顾客姓名:" << name_ << " 手机号：" << phone_number_ << " 身份证号：" << id_number_ << endl;
}
