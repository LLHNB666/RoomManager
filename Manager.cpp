//ʵ�ֹ���Ա��Ĳ���

#include"Manager.h"

bool if_open_ifstream(string filename)//�ж��ļ��ܷ�򿪣�ͬʱ�����ж����޹˿���ס�˷���
{
    ifstream file(filename);
    if (!file)
    {
        cout << "�޷���" << filename << "!�����Ƿ񱣴�����ļ�" << endl;
        system("pause");
        return false;
    }
    file.close();
    return true;
}

bool if_open_ofstream(string filename)//�ж��ļ��ܷ񱻴�
{
    ofstream file(filename);
    if (!file)
    {
        cout << "�޷���" << filename << endl;
        system("pause");
        return false;
    }
    file.close();
    return true;
}

bool isLeapYear(int year) {//�Ƿ�������
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

bool isValidDate2(string year, string month, string day)//�����Ƿ�Ϸ�
{
    int loop = 1;
    for (char c : year) {
        if (!isdigit(c)) {
            cout << "���벻�Ϸ�" << endl;
            loop = 0;
            system("pause");
            return false;
        }
    }
    for (char c : month) {
        if (!isdigit(c)) {
            cout << "���벻�Ϸ�" << endl;
            loop = 0;
            system("pause");
            return false;
        }
    }
    for (char c : day) {
        if (!isdigit(c)) {
            cout << "���벻�Ϸ�" << endl;
            loop = 0;
            system("pause");
            return false;
        }
    }
    if (!loop) return false;
    // ���ַ���ת��Ϊ����
    int y1 = stoi(year);
    int m1 = stoi(month);
    int d1 = stoi(day);
    return isValidDate(y1, m1, d1);
}

//����Ϊ�ͷ������غ�������
void Manager::The_First_Time()
{
    ifstream file("room.txt");
    if (file) {
        // ���ļ��ж�ȡ������Ϣ
        load_Room_message();
    }
    else {
        cout << "��⵽���ǵ�һ��ʹ�ø�ϵͳ�����ǽ����з���ĳ�ʼ��" << endl;
        system("pause");
        system("cls");
        // �����·���
        for (int floor = 1; floor <= 10; ++floor) {
            for (int number = 1; number <= 10; ++number) {
                int room_number = floor * 100 + number;
                string room_type;
                double price;
                if (number <= 4) {
                    room_type = "���˼�";
                    price = 100.0;
                }
                else if (number <= 8) {
                    room_type = "˫�˼�";
                    price = 120.0;
                }
                else {
                    room_type = "��ͥ��";
                    price = 150.0;
                }
                rooms.emplace_back(room_number, room_type, price);
                rooms.back().set_status("����");
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
void Manager::add_rooms(const vector<Room>& new_rooms) {//β����ӷ���
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
    cout << "��ӳɹ���" << endl; system("pause");
}
void Manager::add_rooms2(int target_room_number) {//�м���ӷ���
    // �ж�Ŀ�귿��Ŵ治����
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
        cout << "�������󣡷��䲻����" << endl;
        system("pause");
        return;
    }
    // �������ӣ�ע�����㷿����Ϣ��Ҫ��
    string room_type;
    cout << "���뷿������(˫�˼䣬���˼䣬��ͥ��): ";
    cin >> room_type;

    double price;
    if (room_type == "���˼�") {
        price = 100;
    }
    else if (room_type == "˫�˼�") {
        price = 120;
    }
    else if (room_type == "��ͥ��") {
        price = 150;
    }
    else {
        cout << "�������Ͳ����ڣ�������" << endl;
        system("pause");
        return;
    }


    int num_rooms_to_add;
    cout << "������Ҫ���ӵ���Ŀ: ";
    cin >> num_rooms_to_add;
    //���Ƚ���ԭ����ĸ���
    int new_room_num;
    int the_first;
    for (auto it2 = it; it2 != rooms.end(); ++it2) {
        new_room_num = it2->get_room_number() + num_rooms_to_add;
        int floor = new_room_num / 100;
        int first_num = new_room_num % 10;
        if (new_room_num% 100 > 10 ) {//����·���ź���λ����10����Ҫת��¥��
            int need_to_add_floor = new_room_num % 100 / 10;
            floor=floor+need_to_add_floor;
        }
        if (first_num == 0)//���統�·����Ϊ300ʱ��Ҫ��Ϊ210
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
            if (floor != 1)//����0XX�������
                new_num = (floor - 1) * 100 + 10;
            else new_num = floor * 100 + 10;
        }
        else {
           new_num = floor * 100 + first_num;
        }
        Room new_room(new_num, room_type, price);
        new_room.set_status("����");
        its = rooms.emplace(its, new_room);
        its++;
    }

    save_Room_message();
    cout << "����ɹ���" << endl;
    system("pause");
}
void Manager::reset_room_price(string& temp)
{
    rooms.clear();
    load_Room_message();
    cout << "����������Ҫ�޸ĳɶ���Ǯ��";
        int money=0;
    cin >> money;
    for (auto it = rooms.begin(); it != rooms.end(); it++)
    {
        if (it->get_room_type() == temp&&it->get_status()=="����")
            it->set_price(money);
    }
    save_Room_message();
    cout << "����ɹ���" << endl;
    system("pause");
}

bool Manager::find_target_room_num(int n)//Ŀ�귿���Ƿ����
{
    bool t = false;
    for (auto it = rooms.begin(); it != rooms.end(); it++)
    {
        if (it->get_room_number() == n&&it->get_status()=="����")
        {
            t = true; return t;
        }
    }
    return t;
}
vector<Room>::iterator Manager::find_room(int target_room_number)//�ҵ�Ŀ���������е�λ��
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
        
        cout << "����������Ҫ�޸ĵ�����(�����Ҫ������һ��������0)��" << endl;
        cout << "�·�������(���˼䣬˫�˼���ͥ��)��";
        string temp;
        cin >> temp;
        if (temp == "0")
        {
            loop = 0; break;
        }
        else if (temp != "���˼�" &&temp != "˫�˼�" && temp != "��ͥ��")
        {
            cout << "��������������" << endl;
            system("pause");
            system("cls");
            continue;
        }
        it->set_type(temp);
        cout << "�Ƿ�ϣ�����÷���ļ۸�ͬʱ����ΪĬ��ֵ��" << endl;
        cout << "����Ϊ100��˫��120����ͥ150" << endl;
        cout << "�Ƿ����ΪĬ��ֵ��(�����ǻ��߲���)��";
        string temp2;
        cin >> temp2;
        if (temp2 == "��")
        {
            if (temp == "���˼�") it->set_price(100);
            else if (temp == "˫�˼�") it->set_price(120);
            else it->set_price(150);
        }
        else if (temp2 == "����")
        {
            int money;
            cout << "��������Ҫ����Ϊ���٣�";
            cin >> money;
            it->set_price(money);
        }
        else
        {
            cout << "��������������" << endl;
            system("pause");
            system("cls");
            continue;
        }

        save_Room_message();
        cout << "����ɹ���" << endl;

        loop = 0;
        system("pause");
    }
}


void Manager::delete_room(int room_number) {//ɾ������
    rooms.clear();
    load_Room_message();
    for (auto it = rooms.begin(); it != rooms.end(); ++it) {//����һ��������it����ʼ��ָ���һ��Ԫ��,��ͷ��ʼ�ҵ�Ŀ�귿��š�
        if (it->get_room_number() == room_number) {
            if (it->get_status() != "����") { cout << "�÷���Ŀǰ��ס�ˣ�" << endl; system("pause"); return; }
            it = rooms.erase(it);

            // ������Ӱ��ķ����
            while (it != rooms.end()) {
                it->set_room_number(it->get_room_number() - 1);
                it++;
            }

            save_Room_message();
            cout << "�ɹ�����" << endl;
            system("pause");
            break;
        }
    }
}

void Manager::initialize_room_message()//��ʼ����������
{
    system("cls");
    ifstream file("check_in.txt");
    if (file)
    {
        if (file.peek() != EOF)
        {
            cout << "Ŀǰ���й˿���ס�������й˿��˷�֮����д˲���" << endl;
            system("pause");
            return;
        }
    }
    cout << "�������з������ݳ�ʼ���������Ҫ����������0,���������밴�س�" << endl;
    string choice = "0";
    cin.ignore(); // ����������еĻس���
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
                    room_type = "���˼�";
                    price = 100.0;
                }
                else if (number <= 8) {
                    room_type = "˫�˼�";
                    price = 120.0;
                }
                else {
                    room_type = "��ͥ��";
                    price = 150.0;
                }
                rooms.emplace_back(room_number, room_type, price);
                rooms.back().set_status("����");
            }
        }
        save_Room_message();
        cout << "��ʼ����ɣ�" << endl;
        system("pause");

    }
    else { cout << "��������������" << endl; system("pause"); }
}



//����Ϊ������Ĳ���
void Manager::check_in()
{
    int L1 = 1;
    int f = 1;
    int room_num;
    while (L1)
    {
        system("cls");
        Guest custom;
        cout << "������ù˿͵Ļ�����Ϣ,�����Ҫ�˳�������0��" << endl;
        cout << "������ù˿͵�����:";
        string name;
        cin >> name;
        if (name == "0")
        {
            cout << "�����˳�" << endl;
            system("pause");
            break;
        }

        string number;
        cout << "�������ֻ��ţ�";
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
                        cout << "�ù˿��Ѿ���ס�������ԣ�" << endl;
                        system("pause");
                        return;
                    }
                }
            }
        }

        cout << "������ù˿͵Ĺ˿����֤��" << endl;
        string ID;
        cin >> ID;
        int loo = 1;
        if (ID.length() != 18) {//�ж�ID�Ƿ�Ϸ�
            loo = 0;
        }
        for (int i = 0; i < ID.length(); i++) {
            if (!isdigit(ID[i])) {
                loo = 0;
            }
        }
        if (!loo) {
            cout << "��ID���Ϸ��������²���." << endl;
            system("pause");
            continue;
        }

        int L2 = 1;

        while (L2)
        {
            system("cls");
            print_rest_rooms_by_type("���˼�");
            cout << endl << endl << endl;
            print_rest_rooms_by_type("˫�˼�");
            cout << endl << endl << endl;
            print_rest_rooms_by_type("��ͥ��");
            cout << endl << endl << endl;
            cout << "������ù˿͵Ŀͷ���,�����Ҫ�˳�������0��" << endl;
            string num_str;
            vector<Room>::iterator it;
            cin >> num_str;
            int num = stoi(num_str);
            try {
                
                if (num == 0) {
                    L2 = 0;
                    cout << "����������һ����" << endl;
                    f = 0;
                    system("pause");
                    break;
                }

                if (find_target_room_num(num)) {
                    it = find_room(num);
                    if (it->get_status() == "��ס")
                    {
                        cout << "�÷����з�����ס��������" << endl;
                        system("pause");
                        continue;
                    }
                   
                }
                else {
                    cout << "�÷���Ų����ڣ�������" << endl;
                    system("pause");
                    continue;
                }
            }
            catch (const invalid_argument& e) {
                cout << "�������������һ����Ч������" << endl;
                system("pause");
                continue;
            }
            catch (const out_of_range& e) {
                cout << "�������������һ����Ч������" << endl;
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
            cout << "��������ס�����ڣ��꣬�£���֮���ÿո��������2023��6��4������Ϊ��2023 6 4����";
            string year, month, day;
            cin >> year >> month >> day;
            if (isValidDate2(year, month, day)) { L = 0;
            y = stoi(year);
            m = stoi(month);
            d = stoi(day);
            break; }
            else { cout << "��������������" << endl; system("pause"); continue; }
        }
        Date date(y, m, d);
        add_guest(name, ID, number);
        int last_guest_id = load_last_guest_id();
        int room_id = date.get_year() * 100 + date.get_month() * 10 + date.get_day() * 10 + last_guest_id;
        add_check_in_message(room_id,last_guest_id,number,room_num,date);
        system("cls");
        cout << "����ɹ���" << endl;
        cout << "����Ϊ�ù˿͵���ס��Ϣ��" << endl;
        cout << "������" << name << "  �ֻ���:" << number << " ���֤�ţ�" << ID << endl;
        cout << "��ס����:" << date.get_year() << "��" << date.get_month() << "��" << date.get_day() << "��" << endl;
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
void Manager::add_check_in_message(int room_id, int last_guest_id,const string number, int room_num, Date date)//�����ס��Ϣ
{
    //���·�����Ϣ
    for (auto it = rooms.begin(); it != rooms.end(); it++)
    {
        if (it->get_room_number() == room_num)
            it->set_status("��ס");

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
} //���ϴ���checkin
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
        cout << "Ŀǰ��δ�˿���ס��" << endl;
        return;
    }
    if(file.peek()==EOF)
    {
        cout << "Ŀǰ��δ�˿���ס��" << endl;
        system("pause");
        file.close();
        return;
    }
    file.close();
    checkouts.clear();
    load_check_in_message();
    load_guest_message();

    int guest_id = 0;//�õ�Ŀ��˿ͱ��
    string name="����";//���ڵõ�����
    int L1=0;//�����ж��ܷ��ҵ��ֻ���
            system("cls");
            cout << "��������Ҫ�˷��˿͵��ֻ���,����Ҫ�˳�������0��";
            string phone_number;
            cin >> phone_number;
            if (phone_number == "0") { cout << "�����˳���\n"; system("pause"); return; }
           
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
                int room_num = it->get_room_number();//ͨ���˿ͱ���ҵ������

                double price=0.0;
                for (auto it2 = rooms.begin(); it2 != rooms.end(); it2++)
                {
                    if (it2->get_room_number() == room_num)
                    {
                        price = it2->get_price();
                        it2->set_status("����");
                        save_Room_message();

                        break;
                    }
                }
                cout << "�������˷����ڣ�2023��6��5������Ϊ2023 6 5��:";
                int y, m, d;
                cin >> y >> m >> d;
                if (cin.fail()) {//�ж������Ƿ�Ϸ�
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "�������������һ������\n";
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
                            if (it2->get_level() == "�¶ȴ��Ա")
                            {
                                cout << endl << "�ù˿�Ϊ�¶ȴ��Ա����8.8��" << endl;
                                discount = 0.88;
                            }
                            else if (it2->get_level() == "���ȴ��Ա")
                            {
                                cout << endl << "�ù˿�Ϊ���ȴ��Ա����7.7��" << endl;
                                discount = 0.77;
                            }
                            else
                            {
                                cout << endl << "�ù˿�Ϊ��ȴ��Ա����5��" << endl;
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
                cout << "����Ϊ�ÿͻ��˷���Ϣ��" << endl;
                cout << "Ӧ���۸�Ϊ��" << amount << "Ԫ" << endl;
                checkouts.back().print();
                checkins.erase(it);
                save_check_in_message();
                save_check_out_message();
                cout << "�˷��ɹ���" << endl;
                system("pause");
                break;
            }
            {
                if (!L1) cout << "�ֻ��Ų����ڣ�������" << endl;
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




//����Ϊ��ѯ����
void Manager::find_room_by_guest_name()//ͨ���������ҷ���
{
    system("cls");
    ifstream file("guest.txt");
    if (!file)
    {
        cout << "�޷���guest.txt�ļ��������Ƿ��й˿���ס��" << endl;
        system("pause");
        return;
    }
    cout << "����������Ҫ��ѯ��������";
    string name;
    cin >> name;
    int loop = 0;//�����ж��Ƿ��Ѿ��ر��ļ�
    int loop2 = 0;//�����ж��Ƿ��ҵ�Ŀ��
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
                        cout << "�ù˿���ס�ķ����Ϊ" << it3->get_room_number() << "��סʱ���ֻ�����Ϊ" << it->get_phone_number() << endl;
                        cout << "��סʱ��Ϊ" << it3->get_in_year() << "��" << it3->get_in_month() << "��" << it3->get_in_day() << "��,��δ�˷�" << endl;
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
                        cout << "�ù˿���ס�ķ����Ϊ" << it2->get_room_number() << "��סʱ�򷿼����Ϊ" << it->get_phone_number() << endl;
                        cout << "��סʱ��Ϊ" << it2->get_in_year() << "��" << it2->get_in_month() << "��" << it2->get_in_day() << "��" << endl;
                        cout << "�˷�ʱ��Ϊ" << it2->get_out_year() << "��" << it2->get_out_month() << "��" << it2->get_out_day() << "��,���ƻ���" << it2->get_amount() << "Ԫ" << endl;
                        cout << endl << endl;
                    }
                }

            }
        }
    }
    
    if (!loop2)
        cout << "�޷��ҵ���������" << endl;
    system("pause");
}
void Manager::find_check_in_by_time()//ͨ����ס�����ҵ���ס��Ϣ
{
   
    system("cls");
    ifstream file("guest.txt");
    if (!file)
    {
        cout << "�޷���guest.txt�ļ��������Ƿ��й˿���ס��" << endl;
        system("pause");
        return;
    }
    system("cls");
    cout << "��������Ҫ��ѯ��ʱ��(2023��6��4������2023 6 4)��";
    string year;
    string month;
    string day;
    int loop = 0;//�ж��ļ��Ƿ�ر�
    int loop2 = 0;//�ж��Ƿ��ҵ�
    cin >> year >> month >> day;

    // �������������Ƿ������ĸ�ȷǷ��ַ�
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
        cout << "������û����ס��" << endl;
    }
 
    system("pause");
}

//����ΪVIP��ز���
void Manager::add_VIP()//���VIP
{
    system("cls");
    cout << "��ù˿͵������Ϣ" << endl;
    string name=" ";
    cout << "������ù˿͵�����:" << endl;
    cin >> name;
    string phone=" ";
    cout << "�������ֻ���:" << endl;
   cin >> phone;
   int loop = 1;
   string level = " ";
   while (loop)
   {
       cout << "������û�Ա�ĵȼ�(�¶ȴ��Ա�����8.8�ۣ����ȴ��Ա��7.7�ۣ���ȴ��Ա��5��):";
       cin >> level;
       if (level != "�¶ȴ��Ա" && level != "���ȴ��Ա" && level != "��ȴ��Ա")
       {
           cout << "��������������" << endl; continue;
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
    cout << "����ɹ���"<<endl;
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
void Manager::del_VIP()//ɾ��VIP
{
    system("cls");
    if (!if_open_ifstream("VIP.txt")) return;
    cout << "��������Ҫɾ�����������ֻ���" << endl;
    cout << "����������:";
    string name;
    cin >> name;
    cout << "�������ֻ���:";
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
            cout << "����ɹ���" << endl;
            break;
        }
    }
    if (!loop) cout << "�û�Ա�����ڣ�" << endl;
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





//����Ϊ��ӡ�Ĳ���

template <typename T>
void Manager::print_rooms_by_type(const T& room_type) const {
    cout << "����Ϊ" << room_type << "����Ϣ��\n";
    for (auto it = rooms.begin(); it != rooms.end();it++) {
        if (it->get_room_type() == room_type) {
            cout << "�����: " << it->get_room_number() << ", �۸�: " << it->get_price() << ", ״̬: " << it->get_status() << endl;
        }
    }

    cout << endl;
}
template<typename T>
void Manager::print_rest_rooms_by_type(const T& room_type) const
{
    int num = 0;
    cout << "����Ϊ" << room_type << "�Ŀ��෿�����Ϣ��\n";
    for (const auto& room : rooms) {
        if (room.get_room_type() == room_type && room.get_status() == "����") {
            cout << "�����: " << room.get_room_number() << ", �۸�: " << room.get_price() << ", ״̬: " << room.get_status() << endl;
            num++;
        }
    }
    cout << "Ŀǰ" << room_type << "���������Ϊ��" << num;
}
void Manager::print_rooms()  {
    rooms.clear();
    load_Room_message();
    print_rooms_by_type("���˼�");
    cout << endl << endl << endl;
    print_rooms_by_type("˫�˼�");
    cout << endl << endl << endl;
    print_rooms_by_type("��ͥ��");
    system("pause");
}

void Manager::print_all_check_in()
{
    system("cls");
    if (!if_open_ifstream("check_in.txt")) return;
    ifstream file("check_in.txt");
    if (file.peek() == EOF)
    {
        cout << "checkin.txt�ļ�Ϊ�գ�" << endl;
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

//����Ϊ��ѯ�������
void Manager::aquire_day_income()
{
    system("cls");
    cout << "����������(2023��6��5������Ϊ2023 6 5):"<<endl;
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
    cout << "����Ϊ" << amount << "Ԫ" << endl;
    system("pause");
    system("cls");
}

void Manager::aquire_month_income()
{
    system("cls");
    cout << "�������·�(2023��6������Ϊ2023 6):" << endl;
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
    cout << "��������Ϊ" << amount << "Ԫ" << endl;
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
    cout << "������Ϊ" << amount << "Ԫ" << endl;
    system("pause");
    system("cls");
}





