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

void addUser()//添加读者
{	
	userInfo newUser;
	cout<<"请输入【账号】\n";
	getline(cin,newUser.account);
	cout<<"请输入【初始密码】\n";
	getline(cin,newUser.password);
	newUser.identity="读者";
	newUser.unrestoredNum=0;
	ctrl.userInsert(ctrl.userHead,newUser);
	ctrl.userFout(ctrl.userHead,"readerAccount.txt");
}

void readerCtrl(userNode* pUser,string& account)//管理读者
{
    cout<<"请输入您要进行的操作：\t(或按0返回)\n";
    cout<<"1.修改密码\n";
	cout<<"2.重置密码为默认密码\n";
	cout<<"3.删除用户\n";
	cout<<"4.标记读者信用\n";
	cout<<"***********\n";
	char op;
	cin>>op;
	cin.ignore();
	switch(op)
	{
		case '0':{return;break;}
		case '1':
		{
			string newP;
			cout<<"请输入新密码：\n";
			getline(cin,newP);
			ctrl.newPassword(pUser,newP);
			cout<<"密码修改成功！\n";
			system("pause");
			break;
		}
		case '2':
		{
			ctrl.newPassword(pUser,"123456");
			cout<<"密码已重置为123456！\n";
			system("pause");
			break;
		}
		case '3':
		{
			ctrl.userDelete(ctrl.userHead,pUser);
			cout<<"用户删除成功！\n";
			system("pause");
			break;
		}
		case '4':
		{
			ctrl.creditMark(pUser);
			system("pause");
			break;
		}
		default:{cout<<"输入无效，请重新输入！\n";}
	}
}

void readerUserManage()//增，删，改，查，重置默认密码
{
	while(true)
    {
		cout<<"***********\n";
    	cout<<"请选择操作：\t(或按0返回)\n";
    	cout<<"***********\n";
    	cout<<"1.添加读者\n";
    	cout<<"2.搜索并操作读者\n";//精确搜索
    	cout<<"***********\n";
    	char choice;
    	cin>>choice;
    	cin.ignore();
    	switch(choice)
    	{
    		case '0':
			{
				return;
				break;
			}
        	case '1':
			{
				addUser();
				cout<<"新增读者成功\n";
				break;//增
			}
        	case '2':
			{
				cout<<"请输入读者账号\n";
				string input;
        		getline(cin,input);
				userNode* pUser=ctrl.lockUser(input);//查，删，改
				if(pUser)
				{
					ctrl.currentUser(pUser);
					readerCtrl(pUser,input);
				}
				break;
			}
        	default:{cout<<"输入无效，请重新输入！\n";break;}
		}
    }
}

void addBook()//添加图书
{
	bookInfo newBook;
	cout<<"请输入【ISBN/ISSN】\n";
	getline(cin,newBook.id);
	cout<<"请输入【书名】\n";
	getline(cin,newBook.title);
	cout<<"请输入【作者】\n";
	getline(cin,newBook.author);
	cout<<"请输入【出版社】\n";
	getline(cin,newBook.publisher);
	cout<<"请输入【出版日期】\n";
	getline(cin,newBook.publishDate);
	cout<<"请输入【定价】\n";
	cin>>newBook.price;
	cin.ignore();
	cout<<"请输入【类型】\n";
	getline(cin,newBook.pattern);
	cout<<"请输入【当前藏书总量】\n";
	cin>>newBook.currentNum;
	newBook.loancount=0;
	ctrl.bookInsert(ctrl.bookHead,newBook);
	ctrl.bookFout(ctrl.bookHead,"bookInfo.txt");
	addHold(newBook.title,newBook.id);
}

void changeBook(bookNode* pBook)//修改图书信息
{
	while(true)
	{
		cout<<"请输入您要修改的信息：\t(或按0返回)\n";
    	cout<<"1.ISBN/ISSN\n";
		cout<<"2.书名\n";
		cout<<"3.作者\n";
		cout<<"4.出版社\n";
		cout<<"5.出版日期\n";
		cout<<"6.定价\n";
		cout<<"7.类型\n";
		cout<<"8.当前藏书总量\n";
		cout<<"9.被借阅次数\n";
		cout<<"***********\n";
		char op;
		cin>>op;
		cin.ignore();
		switch(op)
		{
			case '0':return;break;
			case '1':
			{
				cout<<"请输入图书ISBN/ISSN\n";
				string input="";
				getline(cin,input);
				pBook->data.id=input;
				break;
			}
			case '2':
			{
				cout<<"请输入图书名称\n";
				string input="";
				getline(cin,input);
				pBook->data.title=input;
				break;
			}
			case '3':
			{
				cout<<"请输入图书作者\n";
				string input="";
				getline(cin,input);
				pBook->data.author=input;
				break;
			}
			case '4':
			{
				cout<<"请输入图书出版社\n";
				string input="";
				getline(cin,input);
				pBook->data.publisher=input;
				break;
			}
			case '5':
			{
				cout<<"请输入图书出版日期\n";
				string input="";
				getline(cin,input);
				pBook->data.publishDate=input;
				break;
			}
			case '6':
			{
				cout<<"请输入图书定价\n";
				float input=0;
				cin>>pBook->data.price;
				cin.ignore();
				pBook->data.price=input;
				break;
			}
			case '7':
			{
				cout<<"请输入图书类型\n";
				string input="";
				getline(cin,input);
				pBook->data.pattern=input;
				break;
			}
			case '8':
			{
				cout<<"请输入图书当前藏书总量\n";
				int input=0;
				cin>>input;
				cin.ignore();
				pBook->data.currentNum=input;
				break;
			}
			case '9':
			{
				cout<<"请输入图书被借阅次数\n";
				int input=0;
				cin>>input;
				cin.ignore();
				pBook->data.loancount=input;
				break;
			}
			default:{cout<<"输入无效，请重新输入！\n";}
		}
		ctrl.bookFout(ctrl.bookHead,"bookInfo.txt");
	}
}

void bookCtrl(bookNode* pBook,string& bookid)//操作图书
{
	cout<<"请输入您要进行的操作：\t(或按0返回)\n";
    cout<<"1.更改图书信息\n";
	cout<<"2.删除图书\n";
	cout<<"***********\n";
	char op;
	cin>>op;
	cin.ignore();
	switch(op)
	{
		case '0':{return;break;}
		case '1':
		{
			changeBook(pBook);
			cout<<"图书信息修改成功！\n";
			break;
		}
		case '2':
		{
			ctrl.bookDelete(ctrl.bookHead,pBook);
			break;
		}
		default:{cout<<"输入无效，请重新输入！\n";}
	}
}

void bookInfoManage()//管理图书
{
	while(true)
	{
		cout<<"***********\n";
    	cout<<"请选择操作：\t(或按0返回)\n";
    	cout<<"***********\n";
    	cout<<"1.添加图书\n";
    	cout<<"2.搜索并操作图书\n";
    	cout<<"***********\n";
    	char choice;
    	cin>>choice;
    	cin.ignore();
    	switch(choice)
    	{
    		case '0':
			{
				return;
				break;
			}
        	case '1':
			{
				addBook();
				cout<<"新增图书成功\n";
				break;//增
			}
        	case '2':
			{
				cout<<"请输入图书ISBN/ISSN\n";
				string input;
        		getline(cin,input);
				bookNode* pBook=ctrl.lockBook(input);//查，删，改
				if(pBook)
				{
					ctrl.currentBook(pBook);
					bookCtrl(pBook,input);
				}
				break;
			}
        	default:{cout<<"输入无效，请重新输入！\n";break;}
		}
	}
}

void recordManage()//查看记录
{
	while(true)
	{
		cout<<"***********\n";
    	cout<<"请选择操作：\t(或按0返回)\n";
    	cout<<"***********\n";
    	cout<<"1.查看馆藏记录\n";
    	cout<<"2.查看借阅记录\n";
    	cout<<"***********\n";
    	char choice;
    	cin>>choice;
    	cin.ignore();
    	switch(choice)
    	{
    		case '0':
			{
				return;
				break;
			}
        	case '1':
			{
				dispRec("holdRecord.txt");
				break;
			}
        	case '2':
			{
				dispRec("borrowRecord.txt");
				break;
			}
        	default:{cout<<"输入无效，请重新输入！\n";break;}
		}
	}
}

void adminMenu()//管理员菜单
{
	while(true)
	{
    	cout<<"***********\n";
    	cout<<"欢迎您，管理员"<<myAccount<<"!\n";
    	cout<<"***********\n";
    	cout<<"请选择操作：\t(或按0返回)\n";
    	cout<<"1.读者用户管理\n";
    	cout<<"2.书籍信息管理\n";
    	cout<<"3.查看记录\n";
    	cout<<"***********\n";
    	char choice;
    	cin>>choice;
    	switch(choice)
    	{
    		case '0': return;break;
        	case '1': readerUserManage();break;
        	case '2': bookInfoManage();break;
        	case '3': recordManage();break;
        	default: cout<<"输入无效，请重新输入！\n";break;
    	}
	}
}