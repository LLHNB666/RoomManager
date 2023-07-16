//实现管理员类的操作

#include"Manager.h"

bool if_open_ifstream(string filename)//判断文件能否打开，同时可以判断有无顾客入住退房等
{
    ifstream file(filename);
    if (!file)
    {
        cout << "无法打开" << filename << "!请检查是否保存过该文件" << endl;
        system("pause");
        return false;
    }
    file.close();
    return true;
}

bool if_open_ofstream(string filename)//判断文件能否被打开
{
    ofstream file(filename);
    if (!file)
    {
        cout << "无法打开" << filename << endl;
        system("pause");
        return false;
    }
    file.close();
    return true;
}

bool isLeapYear(int year) {//是否是闰年
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {
        return true;
    }
    return false;
}

bool isValidDate(int year, int month, int day) {
    if (year < 1 || month < 1 || month > 12 || day < 1) {
        return false;
    }
    int daysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (isLeapYear(year)) {
        daysInMonth[2] = 29;
    }
    if (day > daysInMonth[month]) {
        return false;
    }
    return true;
}

bool isValidDate2(string year, string month, string day)//日期是否合法
{
    int loop = 1;
    for (char c : year) {
        if (!isdigit(c)) {
            cout << "输入不合法" << endl;
            loop = 0;
            system("pause");
            return false;
        }
    }
    for (char c : month) {
        if (!isdigit(c)) {
            cout << "输入不合法" << endl;
            loop = 0;
            system("pause");
            return false;
        }
    }
    for (char c : day) {
        if (!isdigit(c)) {
            cout << "输入不合法" << endl;
            loop = 0;
            system("pause");
            return false;
        }
    }
    if (!loop) return false;
    // 将字符串转换为整数
    int y1 = stoi(year);
    int m1 = stoi(month);
    int d1 = stoi(day);
    return isValidDate(y1, m1, d1);
}

//以下为客房类的相关函数定义
void Manager::The_First_Time()
{
    ifstream file("room.txt");
    if (file) {
        // 从文件中读取房间信息
        load_Room_message();
    }
    else {
        cout << "检测到您是第一次使用该系统，我们将进行房间的初始化" << endl;
        system("pause");
        system("cls");
        // 创建新房间
        for (int floor = 1; floor <= 10; ++floor) {
            for (int number = 1; number <= 10; ++number) {
                int room_number = floor * 100 + number;
                string room_type;
                double price;
                if (number <= 4) {
                    room_type = "单人间";
                    price = 100.0;
                }
                else if (number <= 8) {
                    room_type = "双人间";
                    price = 120.0;
                }
                else {
                    room_type = "家庭房";
                    price = 150.0;
                }
                rooms.emplace_back(room_number, room_type, price);
                rooms.back().set_status("空闲");
            }
        }
        save_Room_message();
    }
}
void Manager::load_Room_message() {
    if (!if_open_ifstream("room.txt")) return;
    ifstream file("room.txt");
    int room_number;
    string room_type;
    double price;
    string status;
    rooms.clear();
    while (file >> room_number >> room_type >> price >> status) {
        rooms.emplace_back(room_number, room_type, price);
        rooms.back().set_status(status);
    }
}
void Manager::save_Room_message()
{
    if (!if_open_ofstream("room.txt")) return;
    ofstream file("room.txt");
    for (const auto& room : rooms) {
        file << room.get_room_number() << ' '
            << room.get_room_type() << ' '
            << room.get_price() << ' '
            << room.get_status() <<endl;
    }
    file.close();
}
void Manager::add_rooms(const vector<Room>& new_rooms) {//尾部添加房间
    int max_floor = 0;
    int max_room_number = 0;
    rooms.clear();
    load_Room_message();
    for (const auto& room : rooms) {
        int floor = room.get_room_number() / 100;
        max_floor = max(max_floor, floor);
        max_room_number = max(max_room_number, room.get_room_number());
    }

    int count = (max_room_number % 100) + 1;
    for (const auto& room : new_rooms) {
        if (count > 10) {
            count = 1;
            max_floor++;
        }
        int room_number = max_floor * 100 + count;
        string room_type = room.get_room_type();
        double price = room.get_price();
        string status = room.get_status();
        rooms.emplace_back(room_number, room_type, price);
        rooms.back().set_status(status);
        count++;
    }
    save_Room_message();
    cout << "添加成功！" << endl; system("pause");
}
void Manager::add_rooms2(int target_room_number) {//中间添加房间
    // 判断目标房间号存不存在
    vector<Room>::iterator it;
    vector<Room>::iterator its;
    rooms.clear();
    load_Room_message();
    bool found = false;
    for (it = rooms.begin(); it != rooms.end(); ++it) {
        if (it->get_room_number() == target_room_number) {
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "输入有误！房间不存在" << endl;
        system("pause");
        return;
    }
    // 进行增加（注意满足房间信息的要求）
    string room_type;
    cout << "输入房间类型(双人间，单人间，家庭房): ";
    cin >> room_type;

    double price;
    if (room_type == "单人间") {
        price = 100;
    }
    else if (room_type == "双人间") {
        price = 120;
    }
    else if (room_type == "家庭房") {
        price = 150;
    }
    else {
        cout << "房间类型不存在！请重试" << endl;
        system("pause");
        return;
    }


    int num_rooms_to_add;
    cout << "输入想要增加的数目: ";
    cin >> num_rooms_to_add;
    //首先进行原房间的更新
    int new_room_num;
    int the_first;
    for (auto it2 = it; it2 != rooms.end(); ++it2) {
        new_room_num = it2->get_room_number() + num_rooms_to_add;
        int floor = new_room_num / 100;
        int first_num = new_room_num % 10;
        if (new_room_num% 100 > 10 ) {//如果新房间号后两位大于10，则要转换楼层
            int need_to_add_floor = new_room_num % 100 / 10;
            floor=floor+need_to_add_floor;
        }
        if (first_num == 0)//比如当新房间号为300时，要变为210
        {
            floor--;
            new_room_num = floor * 100 + 10;
        }
        else {
            new_room_num = floor * 100 + first_num;
        }
        it2->set_room_number(new_room_num);
        if (it2 == it) {
            the_first = new_room_num;
        }
    }
    for (its = rooms.begin(); its != rooms.end(); its++) {
        if (its->get_room_number() == the_first) {
            break;
        }
    }

    for (int i = target_room_number; i < target_room_number + num_rooms_to_add; i++) {
        int new_num = i;
        int floor = new_num /100;
        int first_num = new_num % 10;
        if (new_num % 100 >10) {
          int  need_to_add_floor = new_num % 100 / 10;
            floor+=need_to_add_floor;
        }
        if (first_num == 0)
        {
            if (floor != 1)//避免0XX情况出现
                new_num = (floor - 1) * 100 + 10;
            else new_num = floor * 100 + 10;
        }
        else {
           new_num = floor * 100 + first_num;
        }
        Room new_room(new_num, room_type, price);
        new_room.set_status("空闲");
        its = rooms.emplace(its, new_room);
        its++;
    }

    save_Room_message();
    cout << "保存成功！" << endl;
    system("pause");
}
void Manager::reset_room_price(string& temp)
{
    rooms.clear();
    load_Room_message();
    cout << "请输入您想要修改成多少钱：";
        int money=0;
    cin >> money;
    for (auto it = rooms.begin(); it != rooms.end(); it++)
    {
        if (it->get_room_type() == temp&&it->get_status()=="空闲")
            it->set_price(money);
    }
    save_Room_message();
    cout << "保存成功！" << endl;
    system("pause");
}

bool Manager::find_target_room_num(int n)//目标房间是否存在
{
    bool t = false;
    for (auto it = rooms.begin(); it != rooms.end(); it++)
    {
        if (it->get_room_number() == n&&it->get_status()=="空闲")
        {
            t = true; return t;
        }
    }
    return t;
}
vector<Room>::iterator Manager::find_room(int target_room_number)//找到目标在容器中的位置
{
    vector<Room>::iterator it;
    for (it = rooms.begin(); it < rooms.end(); it++)
    {
        if (it->get_room_number() == target_room_number)
            return it;
    }
    return it;
}
void Manager::reset_room_all_message(int num)
{
    int loop = 1;
    rooms.clear();
    load_Room_message();
    vector<Room>::iterator it = find_room(num);
    while (loop)
    {
        
        cout << "请输入您想要修改的内容(如果需要返回上一界面输入0)：" << endl;
        cout << "新房间类型(单人间，双人间或家庭房)：";
        string temp;
        cin >> temp;
        if (temp == "0")
        {
            loop = 0; break;
        }
        else if (temp != "单人间" &&temp != "双人间" && temp != "家庭房")
        {
            cout << "输入有误！请重试" << endl;
            system("pause");
            system("cls");
            continue;
        }
        it->set_type(temp);
        cout << "是否希望将该房间的价格同时更新为默认值？" << endl;
        cout << "单人为100，双人120，家庭150" << endl;
        cout << "是否更新为默认值？(输入是或者不是)：";
        string temp2;
        cin >> temp2;
        if (temp2 == "是")
        {
            if (temp == "单人间") it->set_price(100);
            else if (temp == "双人间") it->set_price(120);
            else it->set_price(150);
        }
        else if (temp2 == "不是")
        {
            int money;
            cout << "请输入需要更新为多少：";
            cin >> money;
            it->set_price(money);
        }
        else
        {
            cout << "输入有误！请重试" << endl;
            system("pause");
            system("cls");
            continue;
        }

        save_Room_message();
        cout << "保存成功！" << endl;

        loop = 0;
        system("pause");
    }
}


void Manager::delete_room(int room_number) {//删除房间
    rooms.clear();
    load_Room_message();
    for (auto it = rooms.begin(); it != rooms.end(); ++it) {//定义一个迭代器it并初始化指向第一个元素,从头开始找到目标房间号。
        if (it->get_room_number() == room_number) {
            if (it->get_status() != "空闲") { cout << "该房间目前在住人！" << endl; system("pause"); return; }
            it = rooms.erase(it);

            // 更新受影响的房间号
            while (it != rooms.end()) {
                it->set_room_number(it->get_room_number() - 1);
                it++;
            }

            save_Room_message();
            cout << "成功保存" << endl;
            system("pause");
            break;
        }
    }
}

void Manager::initialize_room_message()//初始化房间数据
{
    system("cls");
    ifstream file("check_in.txt");
    if (file)
    {
        if (file.peek() != EOF)
        {
            cout << "目前仍有顾客入住！请所有顾客退房之后进行此操作" << endl;
            system("pause");
            return;
        }
    }
    cout << "即将进行房间数据初始化，如果想要返回请输入0,继续操作请按回车" << endl;
    string choice = "0";
    cin.ignore(); // 清除缓冲区中的回车符
    getline(cin, choice);
    if (choice == "0") return;
    else if (choice == "")
    {
        rooms.clear();
        for (int floor = 1; floor <= 10; ++floor) {
            for (int number = 1; number <= 10; ++number) {
                int room_number = floor * 100 + number;
                string room_type;
                double price;
                if (number <= 4) {
                    room_type = "单人间";
                    price = 100.0;
                }
                else if (number <= 8) {
                    room_type = "双人间";
                    price = 120.0;
                }
                else {
                    room_type = "家庭房";
                    price = 150.0;
                }
                rooms.emplace_back(room_number, room_type, price);
                rooms.back().set_status("空闲");
            }
        }
        save_Room_message();
        cout << "初始化完成！" << endl;
        system("pause");

    }
    else { cout << "输入有误！请重试" << endl; system("pause"); }
}



//以下为宾客类的操作
void Manager::check_in()
{
    int L1 = 1;
    int f = 1;
    int room_num;
    while (L1)
    {
        system("cls");
        Guest custom;
        cout << "请输入该顾客的基本信息,如果想要退出请输入0：" << endl;
        cout << "请输入该顾客的姓名:";
        string name;
        cin >> name;
        if (name == "0")
        {
            cout << "即将退出" << endl;
            system("pause");
            break;
        }

        string number;
        cout << "请输入手机号：";
        cin >> number;

        ifstream file("check_in.txt");
        if (file)
        {
            if (file.peek() != EOF)
            {
                file.close();
                load_check_in_message();
                for (auto it = checkins.begin(); it != checkins.end(); it++)
                {
                    if (it->get_phone() == number)
                    {
                        cout << "该顾客已经入住！请重试！" << endl;
                        system("pause");
                        return;
                    }
                }
            }
        }

        cout << "请输入该顾客的顾客身份证号" << endl;
        string ID;
        cin >> ID;
        int loo = 1;
        if (ID.length() != 18) {//判断ID是否合法
            loo = 0;
        }
        for (int i = 0; i < ID.length(); i++) {
            if (!isdigit(ID[i])) {
                loo = 0;
            }
        }
        if (!loo) {
            cout << "该ID不合法，请重新操作." << endl;
            system("pause");
            continue;
        }

        int L2 = 1;

        while (L2)
        {
            system("cls");
            print_rest_rooms_by_type("单人间");
            cout << endl << endl << endl;
            print_rest_rooms_by_type("双人间");
            cout << endl << endl << endl;
            print_rest_rooms_by_type("家庭房");
            cout << endl << endl << endl;
            cout << "请输入该顾客的客房号,如果需要退出请输入0：" << endl;
            string num_str;
            vector<Room>::iterator it;
            cin >> num_str;
            int num = stoi(num_str);
            try {
                
                if (num == 0) {
                    L2 = 0;
                    cout << "即将返回上一界面" << endl;
                    f = 0;
                    system("pause");
                    break;
                }

                if (find_target_room_num(num)) {
                    it = find_room(num);
                    if (it->get_status() == "在住")
                    {
                        cout << "该房间有房客在住！请重试" << endl;
                        system("pause");
                        continue;
                    }
                   
                }
                else {
                    cout << "该房间号不存在！请重试" << endl;
                    system("pause");
                    continue;
                }
            }
            catch (const invalid_argument& e) {
                cout << "输入错误！请输入一个有效的整数" << endl;
                system("pause");
                continue;
            }
            catch (const out_of_range& e) {
                cout << "输入错误！请输入一个有效的整数" << endl;
                system("pause");
                continue;
            }
            room_num = num;
            break;
        }
        if (!f)  break;
        int L = 1;
        int y, m, d;
        while (L)
        {
            cout << "请输入入住的日期（年，月，日之间用空格隔开，如2023年6月4日输入为：2023 6 4）：";
            string year, month, day;
            cin >> year >> month >> day;
            if (isValidDate2(year, month, day)) { L = 0;
            y = stoi(year);
            m = stoi(month);
            d = stoi(day);
            break; }
            else { cout << "输入有误！请重试" << endl; system("pause"); continue; }
        }
        Date date(y, m, d);
        add_guest(name, ID, number);
        int last_guest_id = load_last_guest_id();
        int room_id = date.get_year() * 100 + date.get_month() * 10 + date.get_day() * 10 + last_guest_id;
        add_check_in_message(room_id,last_guest_id,number,room_num,date);
        system("cls");
        cout << "保存成功！" << endl;
        cout << "以下为该顾客的入住信息：" << endl;
        cout << "姓名：" << name << "  手机号:" << number << " 身份证号：" << ID << endl;
        cout << "入住日期:" << date.get_year() << "年" << date.get_month() << "月" << date.get_day() << "日" << endl;
        system("pause");
        L1 = 0;
    }
}
void Manager::save_check_in_message()
{
    if (!if_open_ofstream("check_in.txt")) return;
    ofstream file("check_in.txt");
    for (const auto& checkin : checkins) {
        file << checkin << endl;
    }
    file.close();
}
void Manager::load_check_in_message()
{
    if (!if_open_ifstream("check_in.txt")) return;
    ifstream file("check_in.txt");
    CheckIn in;
    checkins.clear();
    while (file >> in)
    {
        checkins.emplace_back(in);
    }
    file.close();
}
void Manager::add_check_in_message(int room_id, int last_guest_id,const string number, int room_num, Date date)//添加入住信息
{
    //更新房间信息
    for (auto it = rooms.begin(); it != rooms.end(); it++)
    {
        if (it->get_room_number() == room_num)
            it->set_status("在住");

    }
    save_Room_message();

    if (last_guest_id == 1)
    {
        checkins.clear();
        checkins.emplace_back(room_id, last_guest_id,number, room_num, date);
    }
    else
    {
        load_check_in_message();
        checkins.emplace_back(room_id, last_guest_id, number,room_num, date);
    }
    save_check_in_message();
} //以上处理checkin
void Manager::add_guest(const string name, const string ID, const string number)
{
    ifstream file("guest.txt");
    if (!file)
    {
        int guest_id = 1;
        guests.emplace_back(guest_id, name, ID, number);
       
    }
    else
    {
        file.close();
        load_guest_message();
        int last_id = load_last_guest_id();
        guests.emplace_back(last_id+1, name, ID, number);
      
    }
    save_guest_message();
    save_last_guest_id();
}
void Manager::save_guest_message()
{
    if (!if_open_ofstream("guest.txt")) return;
    ofstream file("guest.txt");
    for (const auto& guest : guests) {
        file << guest.get_guest_id() << ' '
            << guest.get_name() << ' '
            << guest.get_id_number() << ' '
            <<guest.get_phone_number()<< '\n';
    }
    file.close();

}
void Manager::load_guest_message()
{
    if (!if_open_ifstream("guest.txt")) return;
    ifstream file("guest.txt");
    int guest_id;
    string name;
    string ID;
    string phone;
    guests.clear();
    while (file >> guest_id >> name >> ID >> phone)
    {
        guests.emplace_back(guest_id, name,ID,phone);
    }
    file.close();
}
int  Manager::load_last_guest_id()
{
 
    int last_id = 0;
    ifstream file("last_guest_id.txt");
    if (file.is_open()) {
        file >> last_id;
        file.close();
    }
    return last_id;
}


void Manager::check_out()
{
    ifstream file("check_in.txt");
    if (!file)
    {
        cout << "目前暂未顾客入住！" << endl;
        return;
    }
    if(file.peek()==EOF)
    {
        cout << "目前暂未顾客入住！" << endl;
        system("pause");
        file.close();
        return;
    }
    file.close();
    checkouts.clear();
    load_check_in_message();
    load_guest_message();

    int guest_id = 0;//得到目标顾客编号
    string name="暂无";//用于得到姓名
    int L1=0;//用来判断能否找到手机号
            system("cls");
            cout << "请输入需要退房顾客的手机号,若需要退出请输入0：";
            string phone_number;
            cin >> phone_number;
            if (phone_number == "0") { cout << "即将退出！\n"; system("pause"); return; }
           
        for (auto it = checkins.begin(); it !=checkins.end(); it++)
        {
            
            if (it->get_phone() == phone_number)
            {
                guest_id = it->get_guest_id();
                L1 = 1;
                for (auto it2 = guests.begin(); it2!= guests.end(); it2++)
                {
                    if (it2->get_guest_id() == guest_id)
                    {
                        name = it2->get_name();
                    }
                }
                int room_num = it->get_room_number();//通过顾客编号找到房间号

                double price=0.0;
                for (auto it2 = rooms.begin(); it2 != rooms.end(); it2++)
                {
                    if (it2->get_room_number() == room_num)
                    {
                        price = it2->get_price();
                        it2->set_status("空闲");
                        save_Room_message();

                        break;
                    }
                }
                cout << "请输入退房日期（2023年6月5日输入为2023 6 5）:";
                int y, m, d;
                cin >> y >> m >> d;
                if (cin.fail()) {//判断输入是否合法
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "输入错误！请输入一个整数\n";
                    system("pause");
                }
                Date date2(y, m, d);
                Date date1(it->get_in_year(), it->get_in_month(), it->get_in_day());
                int day = cout_day(date1, date2);
                double discount = 1;
                ifstream file("VIP.txt");
                if (file)
                {
                    file.close();
                    load_VIP_message();
                    for (auto it2 = vips.begin(); it2 != vips.end(); it2++)
                    {
                        if (it2->get_name() == name && it2->get_phone() == phone_number)
                        {
                            if (it2->get_level() == "月度大会员")
                            {
                                cout << endl << "该顾客为月度大会员！打8.8折" << endl;
                                discount = 0.88;
                            }
                            else if (it2->get_level() == "季度大会员")
                            {
                                cout << endl << "该顾客为季度大会员！打7.7折" << endl;
                                discount = 0.77;
                            }
                            else
                            {
                                cout << endl << "该顾客为年度大会员！打5折" << endl;
                                discount = 0.5;
                            }
                        }
                    }
                }
                double amount = day * price;
                double amount2 = day * price*discount;
                ifstream file2("check_out.txt");
                if (!file2)
                {
                    checkouts.clear();
                    checkouts.emplace_back(it->get_reservation_id(), guest_id,phone_number, it->get_room_number(), date1, date2, amount2);

                }
                else
                {
                    file2.close();
                    load_check_out_message();
                    checkouts.emplace_back(it->get_reservation_id(), guest_id,phone_number, it->get_room_number(), date1, date2, amount2);
               
                }
                cout << "以下为该客户退房信息：" << endl;
                cout << "应付价格为：" << amount << "元" << endl;
                checkouts.back().print();
                checkins.erase(it);
                save_check_in_message();
                save_check_out_message();
                cout << "退房成功！" << endl;
                system("pause");
                break;
            }
            {
                if (!L1) cout << "手机号不存在！请重试" << endl;
                system("pause"); return;
            }
        }
     
}
void Manager::save_check_out_message()
{
    if (!if_open_ofstream("check_out.txt")) return;
    ofstream file("check_out.txt");
    for (const auto& checkout : checkouts) {
        file << checkout << endl;
    }
    file.close();
}
void Manager::load_check_out_message()
{
    {
        if (!if_open_ifstream("check_out.txt")) return;
        ifstream file("check_out.txt");
        CheckOut on;
        checkouts.clear();
        while (file >> on)
        {
            checkouts.emplace_back(on);
        }
        file.close();
    }
}
void Manager::save_last_guest_id()
{
    if (!if_open_ofstream("last_guest_id.txt")) return;
    ofstream file("last_guest_id.txt");
    file << guests.back().get_guest_id();
    file.close();
}




//以下为查询操作
void Manager::find_room_by_guest_name()//通过姓名查找房间
{
    system("cls");
    ifstream file("guest.txt");
    if (!file)
    {
        cout << "无法打开guest.txt文件！请检查是否有顾客入住过" << endl;
        system("pause");
        return;
    }
    cout << "请输入您需要查询的姓名：";
    string name;
    cin >> name;
    int loop = 0;//用来判定是否已经关闭文件
    int loop2 = 0;//用来判定是否找到目标
    load_guest_message();
    for (auto it = guests.begin(); it != guests.end(); it++)
    {
        if (it->get_name() == name)
        {
            loop2 = 1;
            int guest_id = it->get_guest_id();
            if (file.peek() != EOF)
            {
                file.close();
                loop = 1;
                load_check_in_message();
                for (auto it3 = checkins.begin(); it3 != checkins.end(); it++)
                {
                    if (it3->get_guest_id() == guest_id)
                    {
                        cout << "该顾客入住的房间号为" << it3->get_room_number() << "入住时候手机号码为" << it->get_phone_number() << endl;
                        cout << "入住时间为" << it3->get_in_year() << "年" << it3->get_in_month() << "月" << it3->get_in_day() << "日,暂未退房" << endl;
                        cout << endl << endl;
                    }
                }
            }
            if (!loop) file.close();
            ifstream file2("check_out.txt");
            if (file2)
            {
                load_check_out_message();
                for (auto it2 = checkouts.begin(); it2 < checkouts.end(); it2++)
                {
                    if (it2->get_guest_id() == guest_id)
                    {
                        cout << "该顾客入住的房间号为" << it2->get_room_number() << "入住时候房间号码为" << it->get_phone_number() << endl;
                        cout << "入住时间为" << it2->get_in_year() << "年" << it2->get_in_month() << "月" << it2->get_in_day() << "日" << endl;
                        cout << "退房时间为" << it2->get_out_year() << "年" << it2->get_out_month() << "月" << it2->get_out_day() << "日,共计花费" << it2->get_amount() << "元" << endl;
                        cout << endl << endl;
                    }
                }

            }
        }
    }
    
    if (!loop2)
        cout << "无法找到！请重试" << endl;
    system("pause");
}
void Manager::find_check_in_by_time()//通过入住日期找到入住信息
{
   
    system("cls");
    ifstream file("guest.txt");
    if (!file)
    {
        cout << "无法打开guest.txt文件！请检查是否有顾客入住过" << endl;
        system("pause");
        return;
    }
    system("cls");
    cout << "请输入想要查询的时间(2023年6月4日输入2023 6 4)：";
    string year;
    string month;
    string day;
    int loop = 0;//判断文件是否关闭
    int loop2 = 0;//判断是否找到
    cin >> year >> month >> day;

    // 检查输入的日期是否包含字母等非法字符
    if (!isValidDate2(year, month, day))
        return;
    int y = stoi(year);
    int m = stoi(month);
    int d = stoi(day);
    if (file.peek() != EOF)
    {
        file.close();
        loop = 1;
        load_check_in_message();
        for (auto it = checkins.begin(); it != checkins.end(); it++)
        {
            if (it->get_in_year() ==y&&it->get_in_month()==m&&it->get_in_day()== d)
            {
                loop2 = 1;
                it->print();
                cout << endl << endl;
                
            }
        }
    }
    if (!loop) file.close();
    ifstream file2("check_out.txt");
    if (file2)
    {
        load_check_out_message();
        for (auto it2 = checkouts.begin(); it2 != checkouts.end(); it2++)
        {
            if (it2->get_in_year() == y && it2->get_in_month() == m && it2->get_in_day() == d)
            {
                loop2 = 1;
                it2->print();
                cout << endl << endl;
            }
        }
    }
    if (!loop2)
    {
        cout << "该日期没有入住！" << endl;
    }
 
    system("pause");
}

//以下为VIP相关操作
void Manager::add_VIP()//添加VIP
{
    system("cls");
    cout << "请该顾客的相关信息" << endl;
    string name=" ";
    cout << "请输入该顾客的姓名:" << endl;
    cin >> name;
    string phone=" ";
    cout << "请输入手机号:" << endl;
   cin >> phone;
   int loop = 1;
   string level = " ";
   while (loop)
   {
       cout << "请输入该会员的等级(月度大会员结算打8.8折，季度大会员打7.7折，年度大会员打5折):";
       cin >> level;
       if (level != "月度大会员" && level != "季度大会员" && level != "年度大会员")
       {
           cout << "输入有误！请重试" << endl; continue;
       }
       loop = 0;
   }
    ifstream file("VIP.txt");
    if (file)
    {
        file.close();
        load_VIP_message();
        vips.emplace_back(name, phone, level);
    }
    else
    {
        vips.clear();
        vips.emplace_back(name, phone, level);
    }
    save_VIP_message();
    cout << "保存成功！"<<endl;
    system("pause");
}
void Manager::load_VIP_message()
{
    if (!if_open_ifstream("VIP.txt")) return;
    ifstream file("VIP.txt");
    string name;
    string phone;
    string level;
    vips.clear();
    while (file >> name >> phone >> level)
    {
        vips.emplace_back(name, phone, level);
    }
}
void Manager::save_VIP_message()
{
    if (!if_open_ofstream("VIP.txt")) return;
    ofstream file("VIP.txt");
    for (const auto & vip:vips)
    {
        file << vip.get_name() << ' ' << vip.get_phone() << ' ' << vip.get_level() << endl;;
    }
}
void Manager::del_VIP()//删除VIP
{
    system("cls");
    if (!if_open_ifstream("VIP.txt")) return;
    cout << "请输入需要删除的姓名和手机号" << endl;
    cout << "请输入姓名:";
    string name;
    cin >> name;
    cout << "请输入手机号:";
    string phone;
    cin >> phone;
    load_VIP_message();
    int loop = 0;
    for (auto it = vips.begin(); it != vips.end(); it++)
    {
        if (it->get_name() == name && it->get_phone() == phone)
        {
            loop = 1;
            it = vips.erase(it);
            save_VIP_message();
            cout << "保存成功！" << endl;
            break;
        }
    }
    if (!loop) cout << "该会员不存在！" << endl;
    system("pause");
}
void Manager::print_all_VIP()
{
    system("cls");
    if (!if_open_ifstream("VIP.txt")) return;
    load_VIP_message();
    for (auto it=vips.begin();it!=vips.end();it++)
    {
        it->print();
    }
    system("pause");
}





//以下为打印的操作

template <typename T>
void Manager::print_rooms_by_type(const T& room_type) const {
    cout << "以下为" << room_type << "的信息：\n";
    for (auto it = rooms.begin(); it != rooms.end();it++) {
        if (it->get_room_type() == room_type) {
            cout << "房间号: " << it->get_room_number() << ", 价格: " << it->get_price() << ", 状态: " << it->get_status() << endl;
        }
    }

    cout << endl;
}
template<typename T>
void Manager::print_rest_rooms_by_type(const T& room_type) const
{
    int num = 0;
    cout << "以下为" << room_type << "的空余房间的信息：\n";
    for (const auto& room : rooms) {
        if (room.get_room_type() == room_type && room.get_status() == "空闲") {
            cout << "房间号: " << room.get_room_number() << ", 价格: " << room.get_price() << ", 状态: " << room.get_status() << endl;
            num++;
        }
    }
    cout << "目前" << room_type << "类空余数量为：" << num;
}
void Manager::print_rooms()  {
    rooms.clear();
    load_Room_message();
    print_rooms_by_type("单人间");
    cout << endl << endl << endl;
    print_rooms_by_type("双人间");
    cout << endl << endl << endl;
    print_rooms_by_type("家庭房");
    system("pause");
}

void Manager::print_all_check_in()
{
    system("cls");
    if (!if_open_ifstream("check_in.txt")) return;
    ifstream file("check_in.txt");
    if (file.peek() == EOF)
    {
        cout << "checkin.txt文件为空！" << endl;
        system("pause");
        file.close();
        return;
    }
    file.close();
    load_check_in_message();
   
    for (auto it=checkins.begin();it!=checkins.end();it++)
    {
      
        it->print();
    }
    system("pause");
}
void Manager::print_all_check_out() 
{
    system("cls");
    if (!if_open_ifstream("check_out.txt")) return;
    load_check_out_message();

    for (auto it = checkouts.begin(); it != checkouts.end(); it++)
    {

        it->print();
        cout << endl;
    }
    system("pause");
}
void Manager::print_all_guests() 
{
    system("cls");
    if (!if_open_ifstream("guest.txt")) return;
    load_guest_message();
    for (auto it=guests.begin();it!=guests.end();it++)
    {
        it->print();
        cout << endl;
    }
    system("pause");
}

//以下为查询收入操作
void Manager::aquire_day_income()
{
    system("cls");
    cout << "请输入日期(2023年6月5日输入为2023 6 5):"<<endl;
    string year;
    string month;
    string day;
    cin >> year >> month >> day;
    if (!isValidDate2(year, month, day))
        return;
    int y = stoi(year);
    int m = stoi(month);
    int d = stoi(day);
    load_check_out_message();
    double amount = 0.0;
    for (auto it = checkouts.begin(); it != checkouts.end(); it++)
    {
        if (it->get_out_day() == d && it->get_out_month() == m && it->get_out_year() == y)
        {
            amount += it->get_amount();
        }
    }
    cout << "收入为" << amount << "元" << endl;
    system("pause");
    system("cls");
}

void Manager::aquire_month_income()
{
    system("cls");
    cout << "请输入月份(2023年6月输入为2023 6):" << endl;
    int year;
    int month;
    cin >> year>>month;
    load_check_out_message();
    double amount = 0.0;
    for (auto it = checkouts.begin(); it != checkouts.end(); it++)
    {
        if (it->get_out_month() == month && it->get_out_year() == year)
        {
            amount += it->get_amount();
        }
    }
    cout << "该月收入为" << amount << "元" << endl;
    system("pause");
    system("cls");
}

void Manager::aquire_all_income()
{
    system("cls");
    load_check_out_message();
    double amount = 0.0;
    for (auto it = checkouts.begin(); it != checkouts.end(); it++)
    {
        amount += it->get_amount();
    }
    cout << "总收入为" << amount << "元" << endl;
    system("pause");
    system("cls");
}





