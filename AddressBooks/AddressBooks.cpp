#include "AddressBooks.h"
#define MAX 1000 

using namespace std;


void HideScrollBar()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    csbi.dwSize.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    csbi.dwSize.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    SetConsoleScreenBufferSize(hConsole, csbi.dwSize);
}

void SetConsoleColor(int foreColor, int backColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (backColor << 4) | foreColor);
}

void InitConsole()
{
    SetConsoleTitleA("【通讯录管理系统】");
    SetConsoleColor(7, 0);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowRect = { 0, 0, 59, 29 }; 
    SetConsoleWindowInfo(hConsole, TRUE, &windowRect);

    HideScrollBar(); 
}

struct Person
{
    string m_Name;       
    int m_Sex;           
    int m_Age;           
    string m_Phone;      
    string m_Address;    
};

struct AddressBooks
{
    Person PersonArray[MAX];  
    int m_SizeOfPerson;       
};

void showMenu()
{
    system("cls"); 
    SetConsoleColor(6, 0); 
    cout << "===========================================================" << endl;
    SetConsoleColor(14, 0); 
    cout << "                      【通讯录管理系统】                    " << endl;
    SetConsoleColor(6, 0);
    cout << "===========================================================" << endl;
    SetConsoleColor(15, 0); 

    cout << "  1、新建联系人" << "\t\t" << "2、显示联系人" << endl;
    cout << "  3、删除联系人" << "\t\t" << "4、查找联系人" << endl;
    cout << "  5、修改联系人" << "\t\t" << "6、清空联系人" << endl;
    cout << "  0、退出通讯录" << "\t\t" << endl;

    SetConsoleColor(6, 0);
    cout << "===========================================================" << endl;
    SetConsoleColor(7, 0); 
    cout << "  请选择功能（0-6）：";
}

int FindPersonIndex(AddressBooks* abs, string name)
{
    for (int i = 0; i < abs->m_SizeOfPerson; i++)
    {
        if (abs->PersonArray[i].m_Name == name)
        {
            return i; 
        }
    }
    return -1; 
}

void AddPerson(AddressBooks* abs)
{
    if (abs->m_SizeOfPerson == MAX)
    {
        SetConsoleColor(12, 0); 
        cout << "===========================================================" << endl;
        cout << "                      通讯录容量已达到上限，无法添加！                      " << endl;
        cout << "===========================================================" << endl;
        SetConsoleColor(7, 0);
        system("pause");
        system("cls");
        return;
    }

    string name;
    cout << "请输入联系人姓名：";
    cin >> name;
    abs->PersonArray[abs->m_SizeOfPerson].m_Name = name;

    int sex = 0;
    cout << "请输入联系人性别（1-男性，2-女性）：";
    while (true)
    {
        cin >> sex;
        if (sex == 1 || sex == 2)
        {
            abs->PersonArray[abs->m_SizeOfPerson].m_Sex = sex;
            break;
        }
        SetConsoleColor(12, 0);
        cout << "输入错误！请重新输入（1-男性，2-女性）：";
        SetConsoleColor(7, 0);
    }

    int age = 0;
    cout << "请输入联系人年龄：";
    while (true)
    {
        cin >> age;
        if (age >= 0 && age <= 120)
        {
            abs->PersonArray[abs->m_SizeOfPerson].m_Age = age;
            break;
        }
        SetConsoleColor(12, 0);
        cout << "输入错误！年龄范围0-120，请重新输入：";
        SetConsoleColor(7, 0);
    }

    string phone;
    cout << "请输入联系人电话：";
    cin >> phone;
    abs->PersonArray[abs->m_SizeOfPerson].m_Phone = phone;

    string address;
    cout << "请输入联系人地址：";
    cin.ignore(); 
    getline(cin, address);
    abs->PersonArray[abs->m_SizeOfPerson].m_Address = address;

    abs->m_SizeOfPerson++;

    SetConsoleColor(10, 0);
    cout << "\n===========================================================" << endl;
    cout << "                      联系人添加成功！                      " << endl;
    cout << "===========================================================" << endl;
    SetConsoleColor(7, 0);

    system("pause");
    system("cls"); 
}

void ShowPerson(AddressBooks* abs)
{
    system("cls");
    SetConsoleColor(14, 0);
    cout << "===========================================================" << endl;
    cout << "                      联系人列表                     " << endl;
    cout << "===========================================================" << endl;
    SetConsoleColor(7, 0);

    if (abs->m_SizeOfPerson == 0)
    {
        SetConsoleColor(12, 0);
        cout << "                      通讯录为空，暂无联系人信息！                      " << endl;
        SetConsoleColor(7, 0);
    }
    else
    {
        SetConsoleColor(11, 0);
        cout << "  姓名\t\t性别\t年龄\t电话\t\t地址" << endl;
        SetConsoleColor(7, 0);
        cout << "-----------------------------------------------------------" << endl;

        for (int i = 0; i < abs->m_SizeOfPerson; i++)
        {
            cout << "  " << abs->PersonArray[i].m_Name << "\t\t"
                << (abs->PersonArray[i].m_Sex == 1 ? "男性" : "女性") << "\t"
                << abs->PersonArray[i].m_Age << "\t"
                << abs->PersonArray[i].m_Phone << "\t"
                << abs->PersonArray[i].m_Address << endl;
            cout << "-----------------------------------------------------------" << endl;
        }
        SetConsoleColor(14, 0);
        cout << "当前通讯录共有 " << abs->m_SizeOfPerson << " 位联系人" << endl;
        SetConsoleColor(7, 0);
    }

    SetConsoleColor(6, 0);
    cout << "===========================================================" << endl;
    SetConsoleColor(7, 0);
    system("pause");
    system("cls");
}

void DeletePerson(AddressBooks* abs)
{
    system("cls");
    SetConsoleColor(14, 0);
    cout << "===========================================================" << endl;
    cout << "                      [删除] 联系人                     " << endl;
    cout << "===========================================================" << endl;
    SetConsoleColor(7, 0);

    if (abs->m_SizeOfPerson == 0)
    {
        SetConsoleColor(12, 0);
        cout << "                      通讯录为空，无联系人可删除！                      " << endl;
        SetConsoleColor(7, 0);
        system("pause");
        system("cls");
        return;
    }

    string name;
    cout << "请输入要删除的联系人姓名：";
    cin >> name;

    int index = FindPersonIndex(abs, name);
    if (index == -1)
    {
        SetConsoleColor(12, 0);
        cout << "未找到名为 \"" << name << "\" 的联系人！" << endl;
        SetConsoleColor(7, 0);
    }
    else
    {
        for (int i = index; i < abs->m_SizeOfPerson - 1; i++)
        {
            abs->PersonArray[i] = abs->PersonArray[i + 1];
        }
        abs->m_SizeOfPerson--; 

        SetConsoleColor(10, 0);
        cout << "联系人 \"" << name << "\" 删除成功！" << endl;
        SetConsoleColor(7, 0);
    }

    SetConsoleColor(6, 0);
    cout << "===========================================================" << endl;
    SetConsoleColor(7, 0);
    system("pause");
    system("cls");
}

void FindPerson(AddressBooks* abs)
{
    system("cls");
    SetConsoleColor(14, 0);
    cout << "===========================================================" << endl;
    cout << "                      [查找] 联系人                    " << endl;
    cout << "===========================================================" << endl;
    SetConsoleColor(7, 0);

    if (abs->m_SizeOfPerson == 0)
    {
        SetConsoleColor(12, 0);
        cout << "                      通讯录为空，无联系人可查找！                      " << endl;
        SetConsoleColor(7, 0);
        system("pause");
        system("cls");
        return;
    }

    string name;
    cout << "请输入要查找的联系人姓名：";
    cin >> name;

    int index = FindPersonIndex(abs, name);
    if (index == -1)
    {
        SetConsoleColor(12, 0);
        cout << "未找到名为 \"" << name << "\" 的联系人！" << endl;
        SetConsoleColor(7, 0);
    }
    else
    {
        SetConsoleColor(11, 0);
        cout << "-----------------------------------------------------------" << endl;
        cout << "查找结果：" << endl;
        cout << "-----------------------------------------------------------" << endl;
        SetConsoleColor(7, 0);
        cout << "  姓名：" << abs->PersonArray[index].m_Name << endl;
        cout << "  性别：" << (abs->PersonArray[index].m_Sex == 1 ? "男性" : "女性") << endl;
        cout << "  年龄：" << abs->PersonArray[index].m_Age << " 岁" << endl;
        cout << "  电话：" << abs->PersonArray[index].m_Phone << endl;
        cout << "  地址：" << abs->PersonArray[index].m_Address << endl;
        SetConsoleColor(11, 0);
        cout << "-----------------------------------------------------------" << endl;
        SetConsoleColor(7, 0);
    }

    SetConsoleColor(6, 0);
    cout << "===========================================================" << endl;
    SetConsoleColor(7, 0);
    system("pause");
    system("cls");
}

void ChangePerson(AddressBooks* abs)
{
    system("cls");
    SetConsoleColor(14, 0);
    cout << "===========================================================" << endl;
    cout << "                      [修改] 联系人                     " << endl;
    cout << "===========================================================" << endl;
    SetConsoleColor(7, 0);

    if (abs->m_SizeOfPerson == 0)
    {
        SetConsoleColor(12, 0);
        cout << "                      通讯录为空，无联系人可修改！                      " << endl;
        SetConsoleColor(7, 0);
        system("pause");
        system("cls");
        return;
    }

    string name;
    cout << "请输入要修改的联系人姓名：";
    cin >> name;

    int index = FindPersonIndex(abs, name);
    if (index == -1)
    {
        SetConsoleColor(12, 0);
        cout << "未找到名为 \"" << name << "\" 的联系人！" << endl;
        SetConsoleColor(7, 0);
        system("pause");
        system("cls");
        return;
    }

    string newName;
    cout << "请输入新的姓名（原姓名：" << abs->PersonArray[index].m_Name << "）：";
    cin >> newName;
    abs->PersonArray[index].m_Name = newName;

    int newSex = 0;
    cout << "请输入新的性别（1-男性，2-女性，原性别：" << (abs->PersonArray[index].m_Sex == 1 ? "男性" : "女性") << "）：";
    while (true)
    {
        cin >> newSex;
        if (newSex == 1 || newSex == 2)
        {
            abs->PersonArray[index].m_Sex = newSex;
            break;
        }
        SetConsoleColor(12, 0);
        cout << "输入错误！请重新输入（1-男性，2-女性）：";
        SetConsoleColor(7, 0);
    }

    int newAge = 0;
    cout << "请输入新的年龄（原年龄：" << abs->PersonArray[index].m_Age << "）：";
    while (true)
    {
        cin >> newAge;
        if (newAge >= 0 && newAge <= 120)
        {
            abs->PersonArray[index].m_Age = newAge;
            break;
        }
        SetConsoleColor(12, 0);
        cout << "输入错误！年龄范围0-120，请重新输入：";
        SetConsoleColor(7, 0);
    }

    string newPhone;
    cout << "请输入新的电话（原电话：" << abs->PersonArray[index].m_Phone << "）：";
    cin >> newPhone;
    abs->PersonArray[index].m_Phone = newPhone;

    string newAddress;
    cout << "请输入新的地址（原地址：" << abs->PersonArray[index].m_Address << "）：";
    cin.ignore();
    getline(cin, newAddress);
    abs->PersonArray[index].m_Address = newAddress;

    SetConsoleColor(10, 0);
    cout << "\n===========================================================" << endl;
    cout << "                      联系人信息修改成功！                      " << endl;
    cout << "===========================================================" << endl;
    SetConsoleColor(7, 0);

    system("pause");
    system("cls");
}

void ClearPerson(AddressBooks* abs)
{
    system("cls");
    SetConsoleColor(14, 0);
    cout << "===========================================================" << endl;
    cout << "                      [清空] 联系人                     " << endl;
    cout << "===========================================================" << endl;
    SetConsoleColor(7, 0);

    if (abs->m_SizeOfPerson == 0)
    {
        SetConsoleColor(12, 0);
        cout << "                      通讯录已为空，无需清空！                      " << endl;
        SetConsoleColor(7, 0);
        system("pause");
        system("cls");
        return;
    }

    char confirm;
    SetConsoleColor(12, 0); 
    cout << "警告：此操作将删除所有联系人，不可恢复！" << endl;
    SetConsoleColor(7, 0);
    cout << "确认要清空所有联系人吗？（y/Y-确认，其他-取消）：";
    cin >> confirm;
    if (confirm == 'y' || confirm == 'Y')
    {
        abs->m_SizeOfPerson = 0;
        SetConsoleColor(10, 0);
        cout << "通讯录已清空！" << endl;
        SetConsoleColor(7, 0);
    }
    else
    {
        cout << "取消清空操作！" << endl;
    }

    SetConsoleColor(6, 0);
    cout << "===========================================================" << endl;
    SetConsoleColor(7, 0);
    system("pause");
    system("cls");
}

int main()
{
    InitConsole();

    AddressBooks abs;
    abs.m_SizeOfPerson = 0; 

    int select = 0;
    while (true)
    {
        showMenu(); 
        cin >> select;

        switch (select)
        {
        case 1: // 新建联系人
            AddPerson(&abs);
            break;
        case 2: // 显示联系人
            ShowPerson(&abs);
            break;
        case 3: // 删除联系人
            DeletePerson(&abs);
            break;
        case 4: // 查找联系人
            FindPerson(&abs);
            break;
        case 5: // 修改联系人
            ChangePerson(&abs);
            break;
        case 6: // 清空联系人
            ClearPerson(&abs);
            break;
        case 0: // 退出通讯录
            system("cls");
            SetConsoleColor(14, 0);
            cout << "===========================================================" << endl;
            cout << "                      感谢使用，欢迎下次光临！                      " << endl;
            cout << "===========================================================" << endl;
            SetConsoleColor(7, 0);
            system("pause");
            return 0;
            break;
        default:
            SetConsoleColor(12, 0);
            cout << "输入错误！请选择0-6之间的选项" << endl;
            SetConsoleColor(7, 0);
            system("pause");
            system("cls");
            break;
        }
    }

    system("pause");
    return 0;
}