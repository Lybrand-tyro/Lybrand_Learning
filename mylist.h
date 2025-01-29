#ifndef _MYLIST_H
#define _MYLIST_H

using namespace std;

extern string myAccount;

struct bookInfo;
class bookNode;
struct userInfo;
class userNode;
class myFunc;

struct bookInfo
{    
    string id;//isbn_or_issn
    string title;//书名
    string author;//作者
    string publisher;//出版社
    string publishDate;//出版日期
    float price;//价格
    string pattern;//类型
    int currentNum=1;//当前藏书总数
    int loancount=0;//历史借阅次数
};
        
class bookNode
{
    private:
        bookInfo data;
    public:
        bookNode* next;
        
    friend class myFunc;
    friend void changeBook(bookNode* pBook);
    friend void restore(bookNode* pBook,userNode* pUser,string& idInput);
    friend void borrow(bookNode* pBook,userNode* pUser,string& idInput);
};

struct userInfo
{
    string account;//账号
    string password;//密码
    string identity;//身份
    int unrestoredNum=0;//未归还书数
    vector<bookInfo> unrestored;//未归还书籍信息
};
        
class userNode
{
	private:
        userInfo data;
    public:
        userNode* next;
        
    friend class myFunc;
    friend void restore(bookNode* pBook,userNode* pUser,string& idInput);
    friend void borrow(bookNode* pBook,userNode* pUser,string& idInput);
    friend void personalCenter();
};

class myFunc
{
	public:
		bookNode* bookHead;
        userNode* userHead;
        myFunc():bookHead(NULL),userHead(NULL){};
		
		bookNode* bookCreateHead();
        bookNode* bookCreateNode(bookInfo data);
        void bookInsert(bookNode* head,bookInfo data);
        void bookDelete(bookNode* head,bookNode* pBook);
        void bookPrint(bookNode* head);
        void currentBook(bookNode* pMove);
        void bookFin(bookNode* head,const string& filename);
        void bookFout(bookNode* head,const string& filename);
        static bool rankCmp(const bookInfo a,const bookInfo b);
        void rankName(vector<bookInfo> books);
        void searchBook(const string& way,string& input);
        bookNode* lockBook(string& input);//返回指向某图书的指针，用于更改信息
        static bool hotCmp(const bookInfo a,const bookInfo b);//静态成员函数
        void hotChart(bookNode* bookHead);
        static bool latestCmp(const bookInfo a,const bookInfo b);
        void latestChart(bookNode* bookHead);
        
        userNode* userCreateHead();
        userNode* userCreateNode(userInfo data);
        void userInsert(userNode* head,userInfo data);
        void userDelete(userNode* head,userNode* pUser);
        void userPrint(userNode* head);
        void currentUser(userNode* pMove);
        void userFin(userNode* head,const string& filename);
        void userFout(userNode* head,const string& filename);
        void searchUser(const string& user,string& input);//读者查看自己信息，管理员查找读者信息
        userNode* lockUser(string& input);//返回指向某用户的指针，用于更改信息
        void newPassword(userNode* pUser,const string& newP);
        void creditMark(userNode* pUser);
};

#endif //_MYLIST_H