#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<sstream>
#include<cstring>
#include"adminpart.h"
#include"readerpart.h"
#include"mylist.h"
#include"recording.h"

using namespace std;



/**********/

bookNode* myFunc::bookCreateHead()//创建链表
{
	bookNode* head=new bookNode;
	head->next=NULL;
	return head;
}

bookNode* myFunc::bookCreateNode(bookInfo data)//创建节点
{
	bookNode* newBook=new bookNode;
	newBook->data=data;
	newBook->next=NULL;
	return newBook;
}

void myFunc::bookInsert(bookNode* head,bookInfo data)//插入书
{
	bookNode* newBook=bookCreateNode(data);
	newBook->next=head->next;
	head->next=newBook;
}

void myFunc::bookDelete(bookNode* head,bookNode* pBook)//删书
{
	bookNode* leftBook=head;
	bookNode* posBook=head->next;
	while(posBook&&posBook!=pBook)
	{
		leftBook=posBook;
		posBook=leftBook->next;
	}
	if(!posBook)
	{
		cout<<"未找到此图书\n";
		system("pause");
		return;
	}
	else
	{
		currentBook(posBook);
		leftBook->next=posBook->next;
		dltHold(posBook->data.title,posBook->data.id);
		bookFout(bookHead,"bookInfo.txt");
		cout<<"删除成功\n";
		delete posBook;
		posBook=NULL;
	}
}

void myFunc::bookPrint(bookNode* head)//打印全链表图书
{
	bookNode* pMove=head->next;
	while(pMove)
	{
		cout<<"ISBN/ISSN: "<<pMove->data.id<<"\n"
            <<"书名: "<<pMove->data.title<<"\n"
            <<"作者: "<<pMove->data.author<<"\n"
            <<"出版社: "<<pMove->data.publisher<<"\n"
            <<"出版日期: "<< pMove->data.publishDate<<"\n"
            <<"定价: "<<pMove->data.price<<"\n"
            <<"类型: "<<pMove->data.pattern<<"\n"
            <<"当前藏书总量: "<<pMove->data.currentNum<<"\n"
            <<"被借阅次数: "<< pMove->data.loancount<<"\n\n";
        pMove=pMove->next; // 移动到下一个节点
	}
}

void myFunc::currentBook(bookNode* pMove)//打印当前图书
{
	cout<<"ISBN/ISSN: "<<pMove->data.id<<"\n"
        <<"书名: "<<pMove->data.title<<"\n"
        <<"作者: "<<pMove->data.author<<"\n"
        <<"出版社: "<<pMove->data.publisher<<"\n"
        <<"出版日期: "<< pMove->data.publishDate<<"\n"
        <<"定价: "<<pMove->data.price<<"\n"
        <<"类型: "<<pMove->data.pattern<<"\n"
        <<"当前藏书总量: "<<pMove->data.currentNum<<"\n"
        <<"被借阅次数: "<< pMove->data.loancount<<"\n\n";
}

void myFunc::bookFin(bookNode* head,const string& filename)//读取图书
{
    ifstream fin(filename);
    if(!fin)
	{
        cerr<<"无法打开文件进行读取"<<endl;
        return;
    }

    while(!fin.eof())
	{
        bookInfo data;
        getline(fin, data.id);
        if(data.id.empty()) break; // 如果遇到空行，则结束读取
        getline(fin,data.title);
        getline(fin,data.author);
        getline(fin,data.publisher);
        getline(fin,data.publishDate);
        fin>>data.price;
        fin.ignore(); // 忽略换行符
        getline(fin, data.pattern);
        fin>>data.currentNum>>data.loancount;
        fin.ignore();// 忽略换行符

        bookInsert(head,data); // 插入到链表中
    }

    fin.close();
}

void myFunc::bookFout(bookNode* head,const string& filename)//写入图书
{
    ofstream fout(filename);
    if(!fout)
	{
        cerr<<"无法打开文件进行写入"<<endl;
        return;
    }

    bookNode* current=head->next;// 从头节点的下一个开始
    while(current)
	{
        bookInfo data=current->data;
        fout<<data.id<<"\n" 
            <<data.title<<"\n"
            <<data.author<<"\n"
            <<data.publisher<<"\n"
            <<data.publishDate<<"\n"
            <<data.price<<"\n"
            <<data.pattern<<"\n"
            <<data.currentNum<<"\n"
            <<data.loancount<<"\n";
        current=current->next;// 移动到下一个节点
    }

    fout.close();
}

bool myFunc::rankCmp(const bookInfo a,const bookInfo b)//比较器
{
	return a.title<b.title;
}

void myFunc::rankName(vector<bookInfo> books)//按字典排序
{
	sort(books.begin(),books.end(),rankCmp);
	for(int i=0;i<books.size();i++)
	{
		cout<<"ISBN/ISSN: "<<books[i].id<<"\n"
        <<"书名: "<<books[i].title<<"\n"
        <<"作者: "<<books[i].author<<"\n"
        <<"出版社: "<<books[i].publisher<<"\n"
        <<"出版日期: "<<books[i].publishDate<<"\n"
        <<"定价: "<<books[i].price<<"\n"
        <<"类型: "<<books[i].pattern<<"\n"
        <<"当前藏书总量: "<<books[i].currentNum<<"\n"
        <<"被借阅次数: "<<books[i].loancount<<"\n\n";
	}
}

void myFunc::searchBook(const string& way,string& input)//宽泛可供浏览，查找图书
{
	vector<bookInfo> books;
	
	transform(input.begin(),input.end(),input.begin(),::tolower);//忽略大小写
	
	bookNode* pMove=bookHead->next;//从头节点的下一个开始遍历
    	bool found=false;
		while(pMove)
		{
			string cur;
			if(way=="id") cur=pMove->data.id;
			else if(way=="title") cur=pMove->data.title;
			else if(way=="author") cur=pMove->data.author;
			else return;
			transform(cur.begin(),cur.end(),cur.begin(),::tolower);
			if(input==cur.substr(0,input.length()))//搜索精度
			{
				found=true;
        		books.push_back(pMove->data);
    		}
    		pMove = pMove->next;
    	}
    	if(!found)
		{
        	cout<<"没有找到匹配的书籍\n";
    	}
    	else
    	{
    		rankName(books);
    		ctrlChoice();
		}
}
	
bookNode* myFunc::lockBook(string& input)//返回指向某书指针
{
	bookNode* pMove=bookHead->next;
	while(pMove)
	{
		if(input==pMove->data.id)
		{
			return pMove;
		}
		pMove=pMove->next;
	}
	cout<<"未查询到此图书，请检查输入\n";
	return NULL;
}

bool myFunc::hotCmp(const bookInfo a,const bookInfo b)//比较器
{
	return a.loancount>b.loancount;
}	
	
void myFunc::hotChart(bookNode* bookHead)//借阅次数最多榜
{
	bookNode* pMove=bookHead;
	vector<bookInfo> chart;
	int i=0;
	while(pMove)
	{
		chart.push_back(pMove->data);
		pMove=pMove->next;
	}
	sort(chart.begin(),chart.end(),hotCmp);
	cout<<"热度榜单——借阅次数最多榜\n";
	int num=min(10,static_cast<int>(chart.size()));//size_t类型转为int
	for(int i=0;i<num;i++)
	{
		cout<<"No"<<i+1<<"."
			<<chart[i].title<<"\t\t"
			<<chart[i].author<<"\t\t"
			<<chart[i].publisher<<"\t\t"
			<<chart[i].id<<"\n";
		cout<<"No"<<i+1<<"借阅次数："<<chart[i].loancount<<"\n";
	}
}

bool myFunc::latestCmp(const bookInfo a,const bookInfo b)//比较器
{
	return a.publishDate>b.publishDate;
}

void myFunc::latestChart(bookNode* bookHead)//出版时间最新榜
{
	bookNode* pMove=bookHead;
	vector<bookInfo> chart;
	int i=0;
	while(pMove)
	{
		chart.push_back(pMove->data);
		pMove=pMove->next;
	}
	sort(chart.begin(),chart.end(),latestCmp);
	cout<<"新书榜单——出版时间最新榜\n";
	int num=min(10,static_cast<int>(chart.size()));
	for(int i=0;i<num;i++)
	{
		cout<<"No"<<i+1<<"."
			<<chart[i].title<<"\t\t"
			<<chart[i].author<<"\t\t"
			<<chart[i].publisher<<"\t\t"
			<<chart[i].id<<"\n";
		cout<<"No"<<i+1<<"出版日期："<<chart[i].publishDate<<"\n";
	}
}

/**************************/
/**************************/
userNode* myFunc::userCreateHead()//创建链表
{
	userNode* head=new userNode;
	head->next=NULL;
	return head;
}

userNode* myFunc::userCreateNode(userInfo data)//创建节点
{
	userNode* newUser=new userNode;
	newUser->data=data;
	newUser->next=NULL;
	return newUser;
}

void myFunc::userInsert(userNode* head,userInfo data)//插入读者
{
	userNode* newUser=userCreateNode(data);
	newUser->next=head->next;
	head->next=newUser;
}

void myFunc::userDelete(userNode* head,userNode* pUser)//删读者
{
	userNode* leftUser=head;
	userNode* posUser=head->next;
	while(posUser&&posUser!=pUser)
	{
		leftUser=posUser;
		posUser=leftUser->next;
	}
	if(!posUser)
	{
		cout<<"未查询到此用户";
		system("pause");
	}
	else
	{
		currentUser(posUser);
		leftUser->next=posUser->next;
		cout<<"删除成功\n";
		delete posUser;
		posUser=NULL;
	}
}

void myFunc::userPrint(userNode* head)//打印整个链表读者
{
	userNode* pMove=head->next;
	while(pMove)
	{
		cout<<"账号: "<<pMove->data.account<<"\n"
            <<"密码: "<<pMove->data.password<<"\n"
            <<"身份："<<pMove->data.identity<<"\n"
            <<"未归还书目数: "<<pMove->data.unrestoredNum<<"\n"
            <<"未归还书目: \n";
            if(pMove->data.unrestoredNum==0) cout<<"\n\n";
            else
            {
             	for(int i=0;i<pMove->data.unrestoredNum;i++)
             	{
             		cout<<"ISBN/ISSN: "<<pMove->data.unrestored[i].id<<"\n"
             		<<"书名: "<<pMove->data.unrestored[i].title<<"\n"
             		<<"作者: "<<pMove->data.unrestored[i].author<<"\n"
             		<<"出版社: "<<pMove->data.unrestored[i].publisher<<"\n";
				}
				cout<<"\n";
			}
        pMove=pMove->next; // 移动到下一个节点
	}
}

void myFunc::currentUser(userNode* pMove)//打印当前读者
{
	cout<<"账号: "<<pMove->data.account<<"\n"
        <<"密码: "<<pMove->data.password<<"\n"
        <<"身份："<<pMove->data.identity<<"\n"
        <<"未归还书目数: "<<pMove->data.unrestoredNum<<"\n"
        <<"未归还书目: \n";
        if(pMove->data.unrestoredNum==0) cout<<"\n\n";
        else
        {
            for(int i=0;i<pMove->data.unrestoredNum;i++)
            {
             	cout<<"ISBN/ISSN: "<<pMove->data.unrestored[i].id<<"\n"
             		<<"书名: "<<pMove->data.unrestored[i].title<<"\n"
             		<<"作者: "<<pMove->data.unrestored[i].author<<"\n"
             		<<"出版社: "<<pMove->data.unrestored[i].publisher<<"\n";
			}
			cout<<"\n";
		}	
}

void myFunc::userFin(userNode* head,const string& filename)//读取读者
{
    ifstream fin(filename);
    if(!fin)
	{
        cerr<<"无法打开文件进行读取"<<endl;
        return;
    }

    while(!fin.eof())
	{
        userInfo data;
        string line;//格式为第一行 账号,密码\n
        getline(fin,line);
        if(line.empty()) break;// 如果遇到空行，则结束读取
        stringstream ss(line);
        getline(ss,data.account,','); // 以逗号为分隔符分割账号和密码
        getline(ss,data.password);
        getline(fin,data.identity);
        fin>>data.unrestoredNum;
        data.unrestored.resize(data.unrestoredNum); // 调整动态数组大小***大坑
        fin.ignore();
        // 读取未归还书籍信息
        for(int i=0;i<data.unrestoredNum;++i)
		{
            getline(fin,data.unrestored[i].id);
            getline(fin,data.unrestored[i].title);
            getline(fin,data.unrestored[i].author);
            getline(fin,data.unrestored[i].publisher);
            // 根据需要继续读取书籍的其他属性
        }
        userInsert(userHead,data); // 插入到链表中
    }

    fin.close();
}

void myFunc::userFout(userNode* head,const string& filename)//写入读者
{
    ofstream fout(filename);
    if(!fout)
	{
        cerr<<"无法打开文件进行写入"<<endl;
        return;
    }

    userNode* current=head->next;// 从头节点的下一个开始
    while(current)
	{
        userInfo data=current->data;
        fout<<data.account<<','
            <<data.password<<"\n"
            <<data.identity<<"\n"
            <<data.unrestoredNum<<"\n";
        for(int i=0;i<data.unrestoredNum;++i)
		{
            fout<<data.unrestored[i].id<<"\n"
            	<<data.unrestored[i].title<<"\n"
            	<<data.unrestored[i].author<<"\n"
            	<<data.unrestored[i].publisher<<"\n";
        }
        current=current->next;// 移动到下一个节点
    }

    fout.close();
}

void myFunc::searchUser(const string& user,string& input)//查找读者
{
	userNode* pMove=userHead->next;//从头节点的下一个开始遍历
		bool found=false;
		while(pMove)
		{
			if(user=="admin"?input==pMove->data.account.substr(0,input.length()):input==pMove->data.account)//搜索精度不知道咋控制好
			{
				found=true;
        		currentUser(pMove);
    		}
    		pMove = pMove->next;
    	}
    	if(!found)
		{
			cout<<"没有找到匹配的用户\n";
			return;
		}
	
}

userNode* myFunc::lockUser(string& input)//返回指向读者指针
{
	userNode* pMove=userHead->next;
	while(pMove)
	{
		if(input==pMove->data.account)
		{
			return pMove;		
		}
		pMove=pMove->next;
	}
	cout<<"没有找到匹配的用户\n";
	return NULL;
}

void myFunc::newPassword(userNode* pUser,const string& newP)//设置密码
{
	(pUser->data.password)=newP;
	userFout(userHead,"readerAccount.txt");
	cout<<"新密码设置成功！\n";
}

void myFunc::creditMark(userNode* pUser)//标记信用
{
	if(pUser->data.identity=="读者")
	{
		pUser->data.identity="低信用读者";
		userFout(userHead,"readerAccount.txt");
		cout<<"已标记为低信用读者\n";
	}
	else
	{
		pUser->data.identity="读者";
		userFout(userHead,"readerAccount.txt");
		cout<<"已标记为读者\n";
	}
}


