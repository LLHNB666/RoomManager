#ifndef GUEST_H//���ļ����ڱ����������
#define GUEST_H
#include <iostream>
#include<string>
using namespace std;


class Guest {
public:
    Guest(int guest_id=0, const string name="����", const string id_number="����", const string phone_number="����");
    int get_guest_id() const;
    string get_name() const;
    string get_id_number() const;
    string get_phone_number() const;
    void print() const;
private:
    int guest_id_;//�˿ͱ��
    string name_;//����
    string id_number_;//���֤��
    string phone_number_;//�ֻ���
};



#endif


