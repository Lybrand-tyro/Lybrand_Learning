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

void restore(bookNode* pBook,userNode* pUser,string& idInput)//还书
{
	bool found=false;
	for(int i=0;i<pUser->data.unrestoredNum;i++)
	{
		if(pUser->data.unrestored[i].id==idInput)
		{
			found=true;
			pUser->data.unrestored.erase(pUser->data.unrestored.begin()+i);
			(pUser->data.unrestoredNum)--;
			(pBook->data.currentNum)++;
			ctrl.bookFout(ctrl.bookHead,"bookInfo.txt");
			ctrl.userFout(ctrl.userHead,"readerAccount.txt");
			break;
		}
	}
	if(!found)
	{
		cout<<"您当前未借阅此书，无法归还\n";
		return;	
	}
	else
	{
		retRecord(pBook->data.title,pBook->data.id);
		psReturn(pBook->data.title,pBook->data.id);
		cout<<"成功归还！\n";
		system("pause");
		return;
	}
}

void borrow(bookNode* pBook,userNode* pUser,string& idInput)//借书
{
	if(pBook->data.currentNum<1)
	{
		cout<<"暂无藏书\n";
		return;
	}
	else
	{
		for(int i=0;i<pUser->data.unrestoredNum;i++)
		{
			if(pUser->data.unrestored[i].id==idInput)
			{
				cout<<"您已借阅此书且当前未归还\n";
				return;
			}
		}
		(pBook->data.currentNum)--;
		ctrl.bookFout(ctrl.bookHead,"bookInfo.txt");
		(pUser->data.unrestoredNum)++;
		(pBook->data.loancount)++;
		// 确保向量大小足够
        if(pUser->data.unrestored.size()<pUser->data.unrestoredNum)
		{
            pUser->data.unrestored.resize(pUser->data.unrestoredNum);
        }
		pUser->data.unrestored[pUser->data.unrestoredNum-1]=(pBook->data);
		ctrl.userFout(ctrl.userHead,"readerAccount.txt");
		borRecord(pBook->data.title,pBook->data.id);
		psBorrow(pBook->data.title,pBook->data.id);
		cout<<"成功借阅！\n";
		system("pause");
		return;
	}
}

void ctrlChoice()//操作图书
{
    cout<<"***********\n";
    cout<<"您想要选中哪一本书进行借阅或归还？输入它的ISBN或ISSN\n";
    cout<<"***********\n";
    string idInput;
    getline(cin,idInput);
    bookNode* pBook=ctrl.lockBook(idInput);
    userNode* pUser=ctrl.lockUser(myAccount);
    char choice;
    while(true)
    {
    	cout<<"***********\n";
    	cout<<"您要进行借阅操作还是归还操作？\t(或按0返回)\n";
    	cout<<"1.借阅\n";
    	cout<<"2.归还\n";
    	cout<<"***********\n";
    	cin>>choice;
    	if(cin.fail())
		{
            cin.clear(); // 清除错误状态
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // 忽略错误输入
            cout<<"输入无效，请重新输入！\n";
            continue; // 重新开始循环
        }
    	switch(choice)
    	{
    		case '0':return;break;
    		case '1':borrow(pBook,pUser,idInput);break;
    		case '2':restore(pBook,pUser,idInput);break;
    		
    		default: cout<<"输入无效，请重新输入！\n";break;
		}
	}
}

void searchBookUI()//查找图书
{
	bool got=false;
	while(!got)
	{
        cout<<"***********\n";
        cout<<"选择搜索图书的方式：\t(或按0返回)\n";
        cout<<"1.按图书名称搜索\n";
        cout<<"2.按ISBN/ISSN搜索\n";
        cout<<"3.按作者搜索\n";
        cout<<"***********\n";

        char choice;
        cin>>choice;
        cin.ignore();

        switch(choice)
		{
            case '0':
            {
            	return;
            	break;// 返回上层菜单
			}
            case '1':
			{
                cout<<"请输入图书名称\n";
                string input;
                getline(cin,input);
                ctrl.searchBook("title",input);
                got=true;
                break;
            }
            case '2':
			{
                cout<<"请输入图书ISBN或ISSN\n";
                string input;
                getline(cin,input);
                ctrl.searchBook("id",input);
                got=true;
                break;
            }
            case '3':
			{
                cout<<"请输入图书作者\n";
                string input;
                getline(cin,input);
                ctrl.searchBook("author",input);
                got=true;
                break;
            } 
            default:
            {
                cout<<"输入无效，请重新输入！\n";
                break;// 重新进行循环
        	}
        }
    }
}

void personalCenter()//个人中心
{
	userNode* p=NULL;
	p=ctrl.lockUser(myAccount);
	if(p->data.identity=="低信用读者")
	{
		cout<<"您已被标记为低信用读者！\n";
		system("pause");
	}
	cout<<p->data.account;
	ctrl.currentUser(p);
	cout<<"选择你的操作：\t(或按0返回)\n";
	cout<<"1.归还书籍\n";
	cout<<"2.更改密码\n";
	cout<<"3.查看个人借阅记录\n";
	char choice;
	cin>>choice;
	cin.ignore();
	switch(choice)
	{
		case '0':return;break;
		case '1':
			{
				cout<<"输入需归还的书籍ISBN或ISSN\n";
				string idInput;
				getline(cin,idInput);
				bookNode* pBook=ctrl.lockBook(idInput);
    			userNode* pUser=ctrl.lockUser(myAccount);
				restore(pBook,pUser,idInput);
				break;
			}
    	case '2':
			{
				userNode* pUser=ctrl.lockUser(myAccount);
				cout<<"输入新密码\n";
				string newP="";
				getline(cin,newP);
    			ctrl.newPassword(pUser,newP);
    			cout<<"新密码设置成功\n";
    			break;
    		}
    	case '3':
    		{
    			ifstream fin("psRecord.txt");
    			if(!fin)
    			{
        			cout<<"个人借阅记录psRecord.txt打开失败！\n";
        			system("pause");
        			return;
    			}
    			string line="";
    			bool got=false;
    			while(getline(fin,line))
    			{
    				if(line==myAccount)
    				{
    					got=true;
    					while(getline(fin,line)&&!line.empty())
    					{
    						cout<<line<<"\n";
						}
					}
				}
				if(got==false) cout<<"未查找到您的记录\n";
				fin.close();
				system("pause");
				break;
			}
    	
    	default: cout<<"输入无效，请重新输入！\n";personalCenter();
	}
}

void bookChart()//查看榜单
{
	while(true)
	{
		cout<<"***********\n";
		cout<<"选择你要查看的榜单：\t(或按0返回)\n";
		cout<<"1.热度榜单——借阅次数最多榜\n";
		cout<<"2.新书榜单——出版时间最新榜\n";
		cout<<"***********\n";
		char choice;
		cin>>choice;
		switch(choice)
    	{
    		case '0':
    		{
    			return;
    			break;
			}
        	case '1':
			{
        		ctrl.hotChart(ctrl.bookHead);
				break;
			}
        	case '2': 
			{
				ctrl.latestChart(ctrl.bookHead);
				break;
			}
        	default:
        	{
       			cout<<"输入无效，请重新输入！\n";
				break;
			}
    	}
    	system("pause");
    }
}

void readerMenu()
{
	while(true)
	{
    	cout<<"***********\n";
    	cout<<"欢迎您，读者"<<myAccount<<"!\n";
    	cout<<"***********\n";
    	cout<<"请选择操作：\t(或按0返回)\n";
    	cout<<"1.搜索图书\n";
    	cout<<"2.个人中心（查看借阅情况）\n";
    	cout<<"3.查看榜单\n";
    	char choice;
    	cin>>choice;
    	switch(choice)
    	{
    		case '0':
    		{
    			return;
    			break;
			}
        	case '1':
			{
        		searchBookUI();
				break;
			}
        	case '2': 
			{
				personalCenter();
				break;
			}
			case '3':
			{
				bookChart();
				break;
			}
        	default:
        	{
       			cout<<"输入无效，请重新输入！\n";
				break;
			}
    	}
	}
}