#include"VIP.h"

VIP::VIP(string n, string p,string l) :name(n), phone(p),level(l) {}

string VIP::get_level() const
{
	return level;
}



string VIP::get_name() const
{
	return name;
}

string VIP::get_phone() const
{
	return phone;
}

void VIP::print()
{
	cout <<"姓名:" << name << " 手机号:" << phone << " 会员等级:"<<level<<endl;
}
