#include<iostream>
#include<string>
#include <fstream>
#include <cstring>
using namespace std;
struct DB
{
    string hoten;
    string soDT;
};
struct node
{
    DB a;
    struct node* pLeft;
    struct node* pRight;
};
typedef struct node NODE;
typedef NODE* TREE;
void KhoiTaoCay(TREE& t)
{
    t = NULL;
}
string inHoa(string stringin)
{
    string a;
    for (int i = 0; i < stringin.size(); i++)
    {
        char letter;
        letter = toupper(stringin[i]);
        a = a + letter;
    }
    return a;
}
void ThemNodeVaoCay(TREE& t, DB x)
{
    if (t == NULL)
    {
        NODE* p = new NODE;
        p->a = x;
        p->pLeft = NULL;
        p->pRight = NULL;
        t = p;
    }
    else
    {
        if (inHoa(x.hoten) <inHoa(t->a.hoten))
        {
            ThemNodeVaoCay(t->pLeft, x);
        }
        else if (inHoa(x.hoten)> inHoa(t->a.hoten) )
        {
            ThemNodeVaoCay(t->pRight, x);
        }
    }
}
void XuatDB(TREE t)
{
    if (t != NULL)
    {
        XuatDB(t->pLeft);
        cout << t->a.hoten << " : " << t->a.soDT << endl;
        XuatDB(t->pRight);
    }
}
void NodeTheMang(TREE& X, TREE& Y) {
    if (Y->pLeft != NULL)
    {
        NodeTheMang(X, Y->pLeft);
    }
    else
    {
        X->a = Y->a;
        X = Y;
        Y = Y->pRight;
    }
}
void XoaNode(TREE& t, string x)
{

    if (t == NULL)
    {
        return;
    }
    else
    {
        if (inHoa(x)<inHoa( t->a.hoten))
        {
            XoaNode(t->pLeft, x);
        }
        else if (inHoa(x)>inHoa( t->a.hoten))
        {
            XoaNode(t->pRight, x);
        }
        else
        {
            NODE* X = t;
            if (t->pLeft == NULL)
            {
                t = t->pRight;
            }
            else if (t->pRight == NULL)
            {
                t = t->pLeft;
            }
            else
            {
                NodeTheMang(X, t->pRight);
            }
            delete X;
            return;
        }
    }
}
void XoaNodeTheosdt(TREE& t, string x)
{
    if (t == NULL)
    {
        return;
    }
    else
    {
        if (x == t->a.soDT)
        {
            NODE* Y = t;
            if (t->pLeft == NULL)
            {
                t = t->pRight;
            }
            else if (t->pRight == NULL)
            {
                t = t->pLeft;
            }
            else
            {
                NodeTheMang(Y, t->pRight);
            }
            delete Y;
            return;
        }
        XoaNodeTheosdt(t->pLeft, x);
        XoaNodeTheosdt(t->pRight, x);
    }

}
void SearchNode_Ten(TREE t, string x)
{
    if (t == NULL)
        return;
    int a = inHoa(t->a.hoten).find(inHoa(x));
    if(a<t->a.hoten.size())
        cout << t->a.hoten << ": " << t->a.soDT << endl;
     SearchNode_Ten(t->pLeft, x);
     SearchNode_Ten(t->pRight, x);
}
void SearchNode_SDT(TREE& t, string x)
{
    if (t == NULL)
        return;
    int a = t->a.soDT.find(x);
    if (a < t->a.soDT.size())
        cout << t->a.hoten << ": " << t->a.soDT << endl;
    SearchNode_SDT(t->pLeft, x);
    SearchNode_SDT(t->pRight, x);
}
TREE searchDB(TREE T, string ten)
{
    NODE* P = T;
    if (T != NULL)
    {
        if (inHoa(T->a.hoten)==inHoa( ten) )
        {
            cout << "Thong tin da tim thay trong danh ba\n";
            return P;
        }
        else if (inHoa(T->a.hoten)> inHoa(ten))
        {
            return searchDB(T->pLeft, ten);
        }
        else
            return searchDB(T->pRight, ten);
    }
    else
        return NULL;
}
TREE searchDB_sdt(TREE T, string sdt)
{
    NODE* P = T;
    if (T != NULL)
    {
        if (inHoa(T->a.soDT)==inHoa( sdt))
        {
            cout << "Thong tin da tim thay so dien thoai trong danh ba\n";
            return P;
        }
        searchDB_sdt(T->pLeft, sdt);
        searchDB_sdt(T->pRight, sdt);
    }
    else
        return NULL;
}
TREE SuaDB(TREE &P)
{
    cout << "SDT ban muon sua: ";
        getline(cin, P->a.soDT);

    return P;
}
TREE SuaDBtrung(TREE P)
{
        string x;
        cout << "Nhap vao so dien thoai can them: ";
        cin.ignore();
        getline(cin, x);
        P->a.soDT = P->a.soDT + " and " + x;
        return P;
}
NODE* turnRight(TREE& l)
{
    NODE* b = l->pLeft;
    NODE* d = b->pRight;
    b->pRight = l;
    l->pLeft = d;
    return b;
}
NODE* turnLeft(TREE& l)
{
    NODE* b = l->pRight;
    NODE* d = b->pLeft;
    b->pLeft = l;
    l->pRight = d;
    return b;
}
int AVL(NODE* d)
{
    if (d == NULL)
        return -1;
    return 1 + max(AVL(d->pLeft), AVL(d->pRight));
}
TREE kt(TREE& d)
{
    while (AVL(d->pLeft) - AVL(d->pRight) > 1)
    {
        d = turnRight(d);
        d->pLeft = kt(d->pLeft);
        d->pRight = kt(d->pRight);
    }
    while (AVL(d->pRight) - AVL(d->pLeft) > 1)
    {
        d = turnLeft(d);
        d->pLeft = kt(d->pLeft);
        d->pRight = kt(d->pRight);
    }
    return d;
}
void  ghifile(TREE& T)
{
    ofstream fileOutput;
    if (T != NULL) {
        fileOutput.open("danhba.txt", ios::app);
        fileOutput << T->a.hoten << endl;
        fileOutput << T->a.soDT << endl;
        ghifile(T->pLeft);
        ghifile(T->pRight);
        fileOutput.close();
    }
}
void docfile(TREE& T)
{
    ifstream fileInput("danhba.txt");
    if (fileInput.fail())
    {
        std::cout << "Cannot open file at " << "danhba.txt" << std::endl;
        return;
    }
    while (!fileInput.eof())
    {
        DB b;
        string line;
        getline(fileInput, line); string s = line;
        b.hoten= s.c_str();
        if (b.hoten == "")
            continue;
        getline(fileInput, line); string k = line;
        b.soDT= k.c_str();
        if (b.soDT == "")
            continue;
        ThemNodeVaoCay(T, b);
    }
}
void menu(TREE& t)
{
    cout << "------------ Chuong Trinh Quan Ly Danh Ba Bang Cay Nhi Phan ------------" << "\n\n";
    docfile(t);
    bool p = true;
    while (p == true)
    {
        system("cls");

        cout << "===========================Menu=========================" << endl;
        cout << "| 1.Them thong tin lien he vao cuoi danh ba.             |" << endl;
        cout << "| 2.Xuat thong tin lien he trong danh ba.                |" << endl;
        cout << "| 3.Xoa thong tin lien he trong danh ba theo ten.        |" << endl;
        cout << "| 4.Xoa thong tin lien he trong danh ba theo SDT.        |" << endl;
        cout << "| 5.Tim kiem thong tin lien he trong danh ba theo ten.   |" << endl;
        cout << "| 6.Tim kiem thong tin lien he trong danh ba theo SDT.   |" << endl;
        cout << "| 7.Sua thong tin lien he trong danh ba theo ten         |" << endl;
        cout << "| 8.Sua thong tin lien he trong danh ba theo SDT         |" << endl;
        cout << "| 0.Thoat                                                |" << endl;
        cout << "========================================================" << endl;
        cout << "Nhap lua chon: ";
        int luachon;
        cin >> luachon;
        switch (luachon)
        {
        case 1:
        {
            cin.ignore();
            DB b;
            cout << "nhap ho ten: ";
            getline(cin,b.hoten);

            TREE p = searchDB(t, b.hoten);
            if (p == NULL)
            {
                cout << "nhap so dien thoai: ";
                getline(cin, b.soDT);
                ThemNodeVaoCay(t, b);
            }
            else
            {
                cout << p->a.hoten << " : " << p->a.soDT << endl;
                cout << "Ban co muon them SDT vao ten danh ba da trung khong?(y/n)";
                string s;
                cin >> s;
                if (s=="y")
                {
                    SuaDBtrung(p);
                    XuatDB(t);
                }
            }
            system("pause");
            break;
        }
        case 0:
        {
            system("del QLSV.TXT");
            system("cls");
            cin.ignore();
            ofstream fileOutput("danhba.txt");
            if (fileOutput.fail())
            {
                std::cout << "Cannot open file at " << "danhba.txt" << std::endl;
                return;
            }    fileOutput.close();
            ghifile(t);
            cout << "Da Luu Du Lieu" << endl;
            p = false;
            break;
        }
        case 2:
        {
            //kt(t);
            XuatDB(t);
            system("pause");
            break;
        }
        case 3:
        {
            cin.ignore();
            string name;
            cout << "Nhap ten can xoa: ";
            getline(cin, name);
            XoaNode(t, name);
            system("pause");
            break;
        }
        case 4:
        {
            cin.ignore();
            string sdt;
            cout << "Nhap SDT can xoa: ";
            getline(cin, sdt);
            XoaNodeTheosdt(t, sdt);
            system("pause");
            break;
        }
        case 5:
        {
            cin.ignore();
            string name;
            cout << "Nhap ten can tim kiem: ";
            getline(cin, name);
            SearchNode_Ten(t, name);
            system("pause");
            break;
        }
        case 6:
        {
            cin.ignore();
            string sdt;
            cout << "Nhap SDT can tim kiem: ";
            getline(cin, sdt);
            SearchNode_SDT(t, sdt);
            system("pause");
            break;
        }
        case 7:
        {
            cin.ignore();
            string name;
            cout << "Nhap ten hoac de tim kiem thong tin: ";
            getline(cin, name);
            TREE p = searchDB(t, name);
            if (p != NULL)
            {
                SuaDB(p);
            }
            XuatDB(t);
            //SuaSDTtheoTen(t, name);
            system("pause");
            break;
        }
        case 8:
        {
            cin.ignore();

            DB b;
            cout << "Nhap SDT hoac de tim kiem thong tin: ";
            getline(cin, b.soDT);
            TREE p = searchDB_sdt(t, b.soDT);
            if (p != NULL)
            {
                cout << "Da tim thay so dien thoai thong tin danh ba"<<endl;
                XoaNodeTheosdt(t, b.soDT);
                cout << "nhap ho ten: ";
                getline(cin, b.hoten);
                ThemNodeVaoCay(t, b);
            }
            XuatDB(t);
            //SuaSDTtheoTen(t, name);
            system("pause");
            break;
        }
        default:
            break;
        }
    }
}

int main()
{
    TREE t;
    KhoiTaoCay(t);
    menu(t);
}