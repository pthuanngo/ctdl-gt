#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

struct Sach
{
    string ma, ten, tac_gia, nha_xb;
    int nam_xb;
    string the_loai;
};
Sach Nhap()
{
    Sach a;
    cout << "Nhap thong tin sach\n";
    cout << "Nhap ma: ";
    cin >> a.ma;
    cout << "Nhap ten: ";
    cin.ignore();
    getline(cin, a.ten);
    cout << "Nhap ten tac gia: ";
    getline(cin, a.tac_gia);
    cout << "Nhap nha xuat ban: ";
    getline(cin, a.nha_xb);
    cout << "Nhap nam xuat ban: ";
    cin >> a.nam_xb;
    cout << "Nhap the loai: ";
    cin.ignore();
    getline(cin, a.the_loai);
    return a;
}
string ToString(Sach a, bool ngang = true)
{
    stringstream out;
    if (ngang)
    {
        out << left << setw(10) << a.ma << setw(30) << a.ten << setw(20) << a.tac_gia << setw(20) << a.nha_xb << setw(15) << a.nam_xb << setw(20) << a.the_loai;
    }
    else
    {
        out << "Thong tin sach\n";
        out << "Ma sach: " << a.ma << endl;
        out << "Ten sach: " << a.ten << endl;
        out << "Tac gia: " << a.tac_gia << endl;
        out << "Nha xuat ban: " << a.nha_xb << endl;
        out << "Nam xuat ban: " << a.nam_xb << endl;
        out << "The loai: " << a.the_loai << endl;
    }
    return out.str();
}
struct Node
{
    Sach data;
    Node *next;
};
Node *New_Node(Sach x)
{
    Node *p = new Node;
    p->data = x;
    p->next = NULL;
    return p;
}
string Xuat_DS(Node *head)
{
    stringstream out;
    out << setw(55) << "DANH SACH HIEN CO\n";
    out << left << setw(10) << "STT" << setw(10) << "Ma sach" << setw(30) << "Ten sach" << setw(20) << "Ten tac gia" << setw(20) << "Nha xuat ban" << setw(15) << "Nam xuat ban" << setw(20) << "The loai" << endl;
    int j = 1;
    for (Node *i = head; i != NULL; i = i->next, j++)
        out << left << setw(10) << j << ToString(i->data) << endl;
    return out.str();
}
int Size(Node *head)
{
    int count = 0;
    for (Node *i = head; i != NULL; i = i->next)
        count++;
    return count;
}
Node *Search(Node *head, string ma)
{
    Node *i = head;
    while (i != NULL)
    {
        if (i->data.ma == ma)
            return i;
        i = i->next;
    }
    return NULL;
}
bool Push(Node *&head, Sach x, bool insert_head = false)
{
    if (Search(head, x.ma))
        return false;
    if (insert_head)
    {
        Node *p = New_Node(x);
        p->next = head;
        head = p;
        return true;
    }
    if (head == NULL)
    {
        head = New_Node(x);
        return true;
    }
    Node *i = head;
    while (i->next != NULL)
        i = i->next;
    i->next = New_Node(x);
    return true;
}
bool Delete(Node *&head, string ma)
{
    if (head->data.ma == ma)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
        return true;
    }
    else
    {
        for (Node *i = head; i->next != NULL; i = i->next)
            if (i->next->data.ma == ma)
            {
                Node *temp = i->next;
                i->next = i->next->next;
                delete temp;
                return true;
            }
    }
    return false;
}
void Sort(Node *head)
{
    if (head == NULL || head->next == NULL)
        return;
    for (Node *i = head; i->next != NULL; i = i->next)
        for (Node *j = i->next; j != NULL; j = j->next)
            if (i->data.the_loai > j->data.the_loai || (i->data.the_loai == j->data.the_loai && i->data.ma > j->data.ma))
            {
                Sach t = i->data;
                i->data = j->data;
                j->data = t;
            }
}
bool Insert(Node *&head, Sach x)
{
    if (Search(head, x.ma))
        return false;
    if (head == NULL || head->data.the_loai > x.the_loai || (head->data.the_loai == x.the_loai && head->data.ma > x.ma))
    {
        Node *p = New_Node(x);
        p->next = head;
        head = p;
        return true;
    }
    Node *i = head;
    while (i->next->data.the_loai > x.the_loai || (i->next->data.the_loai == x.the_loai && i->next->data.ma > x.ma))
        i = i->next;
    Node *p = New_Node(x);
    p->next = i->next;
    i->next = p;
    return true;
}
void Thong_Ke_SL_NXB_Cua_TG(Node *head, string TG)
{
    Node *ArrList[100];
    for (int i = 0; i < 100; i++)
        ArrList[i] = NULL;
    int n = 0;
    for (Node *i = head; i != NULL; i = i->next)
        if (i->data.tac_gia == TG)
        {
            int index = 0;
            for (index = 0; index < n; index++)
                if (ArrList[index]->data.nha_xb == i->data.nha_xb)
                {
                    Push(ArrList[index], i->data);
                    break;
                }
            if (index == n)
            {
                Push(ArrList[index], i->data);
                n++;
            }
        }
    cout << "\nTac gia " << TG << " co " << n << " NXB hoat dong bao gom:\n";
    for (int i = 0; i < n; i++)
        cout << " + " << Size(ArrList[i]) << " " << ArrList[i]->data.nha_xb << endl;
}
void Thong_Ke_Sach_Cua_NXB(Node *head)
{
    Node *ArrList[100];
    for (int i = 0; i < 100; i++)
        ArrList[i] = NULL;
    int n = 0;
    for (Node *i = head; i != NULL; i = i->next)
    {
        int index = 0;
        for (index = 0; index < n; index++)
            if (ArrList[index]->data.nha_xb == i->data.nha_xb)
            {
                Push(ArrList[index], i->data);
                break;
            }
        if (index == n)
        {
            Push(ArrList[index], i->data);
            n++;
        }
    }
    int index = -1;
    int min;
    cout << "\n\t\t\tTHONG KE SO SACH CUA NXB\n";
    cout << left << setw(25) << "Ten nha xuat ban" << setw(15) << "So luong sach\n";
    for (int i = 0; i < n; i++)
    {
        int size = Size(ArrList[i]);
        cout << left << setw(25) << ArrList[i]->data.nha_xb << setw(15) << size << endl;
        if (index == -1 || (min > size))
        {
            index = i;
            min = size;
        }
    }
    cout << "Nha xuat ban co it sach nhat: " << ArrList[index]->data.nha_xb << " voi " << min << " cuon\n";
}
void Thong_Ke_Sach_Theo_Nam_Cua_NXB(Node *head, int year)
{
    Node *ArrList[100];
    for (int i = 0; i < 100; i++)
        ArrList[i] = NULL;
    int n = 0;
    for (Node *i = head; i != NULL; i = i->next)
        if (i->data.nam_xb == year)
        {
            int index = 0;
            for (index = 0; index < n; index++)
                if (ArrList[index]->data.nha_xb == i->data.nha_xb)
                {
                    Push(ArrList[index], i->data);
                    break;
                }
            if (index == n)
            {
                Push(ArrList[index], i->data);
                n++;
            }
        }
    int index = -1;
    cout << "\n\t\t\tTHONG KE SO SACH CUA NXB\n";
    for (int i = 0; i < n; i++)
    {
        cout << "\nNha xuat ban: " << ArrList[i]->data.nha_xb << ":\n";
        cout << Xuat_DS(ArrList[i]) << endl;
    }
}
void Thong_Ke_Sach_Theo_The_Loai(Node *head, string theLoai)
{
    cout << "\n\t\tDANH SACH " << theLoai << "\n";
    int n = 0;
    for (Node *i = head; i != NULL; i = i->next)
        if (i->data.the_loai == theLoai)
        {
            cout << ToString(i->data) << endl;
            n++;
        }
    cout << "Tong trong kho co: " << n << " cuon.\n";
}
void Thong_Ke_Sach_20(Node *head, string ten)
{
    cout << "\n\t\tDANH SACH " << ten << "\n";
    int n = 0;
    for (Node *i = head; i != NULL; i = i->next)
        if (i->data.ten.find(ten) != -1 && (i->data.nha_xb == "NXB DHQG" || i->data.nha_xb == "NXB KHKT"))
        {
            cout << ToString(i->data) << endl;
            n++;
        }
    cout << "Tong trong kho co: " << n << " cuon.\n";
}
Node *Init(string s)
{
    ifstream in(s.c_str());
    Node *head = NULL;
    while (true)
    {
        Sach a;
        if (!(in >> a.ma))
            break;
        in.ignore();
        getline(in, a.ten);
        getline(in, a.tac_gia);
        getline(in, a.nha_xb);
        in >> a.nam_xb;
        in.ignore();
        getline(in, a.the_loai);
        Push(head, a);
    }
    in.close();
    return head;
}
void Export(Node *head, string s)
{
    ofstream out(s.c_str());
    out << Xuat_DS(head);
    out.close();
}
int Menu()
{
    cout << "\n\t\t\tMENU\n";
    cout << "1. Them sach" << endl;
    cout << "2. Xoa sach" << endl;
    cout << "3. Sap xep sach theo the loai" << endl;
    cout << "4. Chen sach" << endl;
    cout << "5. Thong ke sach trong tung NXB cua tac gia" << endl;
    cout << "6. Thong ke sach cua NXB" << endl;
    cout << "7. Thong ke sach theo nam cua NXB" << endl;
    cout << "8. Thong ke sach theo the loai" << endl;
    cout << "9. Thong ke sach theo ten cua NXB DHQG va NXB KHKT xuat ban" << endl;
    cout << "10. Xuat danh sach" << endl;
    cout << "0. Thoat" << endl;
    cout << "Chuc nang: ";
    int d;
    cin >> d;
    return d;
}
int main()
{
    Node *head = Init("./input.txt");
    int chuc_nang;
    while (true)
    {
        chuc_nang = Menu();
        switch (chuc_nang)
        {
        case 1:
        {
            Sach x = Nhap();
            if (Push(head, x))
                cout << "Them thanh cong!\n";
            else
                cout << "Them that bai. Ma da co trong danh sach!\n";
            break;
        }
        case 2:
        {
            string ma;
            cout << "Nhap ma muon xoa: ";
            cin >> ma;
            if (Delete(head, ma))
                cout << "Xoa thanh cong!\n";
            else
                cout << "Ma khong co trong danh sach. Xoa that bai!\n";
        }
        case 3:
        {
            Sort(head);
            cout << "Sap xep xong vui long thuc hien chuc nang 10 de hien thi!\n";
            break;
        }
        case 4:
        {
            Sach x = Nhap();
            if (Insert(head, x))
                cout << "Them thanh cong!\n";
            else
                cout << "Them that bai. Ma da co trong danh sach!\n";
            break;
        }
        case 5:
        {
            cout << "Nhap ten tac gia: ";
            string s;
            cin.ignore();
            getline(cin, s);
            Thong_Ke_SL_NXB_Cua_TG(head, s);
            break;
        }
        case 6:
        {
            Thong_Ke_Sach_Cua_NXB(head);
            break;
        }
        case 7:
        {
            int year;
            cout << "Nhap nam: ";
            cin >> year;
            Thong_Ke_Sach_Theo_Nam_Cua_NXB(head, year);
            break;
        }
        case 8:
        {
            string s;
            cout << "Nhap the loai: ";
            cin.ignore();
            getline(cin, s);
            Thong_Ke_Sach_Theo_The_Loai(head, s);
            break;
        }
        case 9:
        {
            string s;
            cout << "Nhap ten sach: ";
            cin.ignore();
            getline(cin, s);
            Thong_Ke_Sach_20(head, s);
            break;
        }
        case 10:
        {
            cout << Xuat_DS(head) << endl;
            break;
        }
        case 0:
        {
            cout << "Tam biet!\n";
            Export(head, "output.txt");
            return 0;
        }
        default:
            cout << "Thao tac khong hop le!\n";
            break;
        }
    }
    return 0;
}