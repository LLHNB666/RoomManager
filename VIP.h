#ifndef VIP_H
#define VIP_H

#include<iostream>
#include<string.h>
using namespace std;


class VIP
{
	string name;//����
	string phone;//�ֻ���
	string level;//�ȼ�
public:
	VIP(string n = "����", string p = "����",string l="����");
	void print();
	string get_name() const;
	string get_phone() const;
	string get_level() const;
};
#endif // !VIP_H
