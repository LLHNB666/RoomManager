#ifndef VIP_H
#define VIP_H

#include<iostream>
#include<string.h>
using namespace std;


class VIP
{
	string name;//姓名
	string phone;//手机号
	string level;//等级
public:
	VIP(string n = "暂无", string p = "暂无",string l="暂无");
	void print();
	string get_name() const;
	string get_phone() const;
	string get_level() const;
};
#endif // !VIP_H
