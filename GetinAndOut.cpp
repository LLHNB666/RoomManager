

#include"GetinAndOut.h"//入房退房类的实现


Date::Date(int y, int m, int d) :year(y), month(m), day(d) {}

int Date::get_year() const { return year; }
int Date::get_month() const { return month; }
int Date::get_day() const {return day; }


bool Date::operator==(const Date& date) const
{
    return (year == date.year && month == date.month && day == date.day);
}


istream& operator>>(istream& is, Date& date)
{
    is >> date.year;
    is >> date.month;
    is >> date.day;
    return is;
}

ostream& operator<<(ostream& os, const Date& date)
{
    os << date.year<< ' ';
    os << date.month << ' ';
    os << date.day << ' ';
    return os;
}

int cout_day(Date& day1,Date& day2)
    {
        int y1 = day1.get_year();
        int m1 = day1.get_month();
        int d1 = day1.get_day();
        int y2 = day2.get_year();
        int m2 = day2.get_month();
        int d2 = day2.get_day();
        int i, j, k, t1, t2, q, y, sum = 0;
        int a[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };//数组中第一个元素直接赋值为0，其他天数与月份相对应
        for (i = y1; i <= y2; i++)   //外层循环，从开始年到输入的年份    
        {
            if (i == y1)
                t1 = m1;   //起始月份赋给t1 
            else t1 = 1;   //当年份自增后  月份开始赋值为1（除起始年份和目标年份外 ）
            if (i == y2)
                t2 = m2;  //当i自增到目标月份时 将目标月份的值赋给t2
            else t2 = 12;
            for (j = t1; j <= t2; j++)  //t1,t2用来计算相应的月份差
            {
                if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0)//判断是否为闰年
                    a[2] = 29;
                else a[2] = 28;
                if (i == y1 && j == m1)
                    q = d1;
                else q = 1;
                if (i == y1 && j == m2)
                    y = d2;
                else y = a[j];
                for (k = q; k <= y; k++)
                {
                    sum++;       //算每个月份相差多少天
                }
            }
        }

        return sum - 1;   //得到天数 
    }


CheckIn::CheckIn(int reservation_id, int guest_id,const string p, int room_number, Date check_in_time) : reservation_id_(reservation_id), guest_id_(guest_id),phone(p), room_number_(room_number), check_in_time_(check_in_time)
{}

int CheckIn::get_reservation_id() const {
    return reservation_id_;
}

int CheckIn::get_guest_id() const {
    return guest_id_;
}

int CheckIn::get_room_number() const {
    return room_number_;
}

Date CheckIn::get_check_in_time() const {
    return check_in_time_;
}

int CheckIn::get_in_year() const
{
    return check_in_time_.get_year();
}

int CheckIn::get_in_month() const
{
    return check_in_time_.get_month();
}

int CheckIn::get_in_day() const
{
    return check_in_time_.get_day();
}

string CheckIn::get_phone() const
{
    return phone;
}

istream& operator>>(istream& is, CheckIn& in)
{
    is >> in.reservation_id_ >> in.guest_id_ >>in.phone>> in.room_number_ >> in.check_in_time_;
    return is;
}
ostream& operator<<(ostream& os, const CheckIn& in)
{
    os << in.reservation_id_ << ' ';
    os << in.guest_id_ << ' ';
    os << in.phone << ' ';
    os << in.room_number_ << ' ';
    os << in.check_in_time_ << ' ';
    return os;
}




void CheckIn::print() {
    // 打印入住信息
    cout << "订房编号: " << reservation_id_ << "  顾客编号: " << guest_id_ << " 手机号:"<<phone<<"  房间号: " << room_number_ << endl;
        cout<< "入住时间: " << check_in_time_.get_year() << "年"<< check_in_time_.get_month() << "月" << check_in_time_.get_day() << "号" << endl;
}

CheckOut::CheckOut(int reservation_id, int guest_id,const string number, int room_number, Date check_in_time, Date check_out_time, double amount): CheckIn(reservation_id, guest_id,number, room_number,check_in_time), check_out_time_(check_out_time), amount_(amount) {}



int CheckOut::get_out_year() const
{
    return check_out_time_.get_year();
}


int CheckOut::get_out_month() const
{
    return check_out_time_.get_month();
}
int CheckOut::get_out_day() const
{
    return check_out_time_.get_day();
}

Date CheckOut::get_check_out_time() const {
    return check_out_time_;
}

double CheckOut::get_amount() const {
    return amount_;
}

void CheckOut::print()
{
    cout << "订房编号: " << reservation_id_ << "  顾客编号: " << guest_id_ << "  房间号: " << room_number_ << endl;
    cout << "手机号：" << phone;
    cout << " 入住时间: " << check_in_time_.get_year() << "年" << check_in_time_.get_month() << "月" << check_in_time_.get_day() << "号" << endl;
    cout << "退房时间：" << check_out_time_.get_year() << "年" << check_out_time_.get_month() << "月" << check_out_time_.get_day() << "日";
    cout << "实付价格为:" << amount_<< endl;
}


istream& operator>>(istream& is, CheckOut& on)
{
    is >> on.reservation_id_ >> on.guest_id_ >> on.phone>>on.room_number_ >> on.check_in_time_ >> on.check_out_time_>>on.amount_;
    return is;
}

ostream& operator<<(ostream& os, const CheckOut& on)
{

    os << on.reservation_id_ << ' ';
    os << on.guest_id_ << ' ';
    os << on.phone << ' ';
    os << on.room_number_ << ' ';
    os << on.check_in_time_ << ' ';
    os << on.check_out_time_ << ' ';
    os << on.amount_;
    return os;
}



