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

myFunc ctrl;

string myAccount="";

bool checkAccount(string password,const string filename)//比对账号密码
{
    cout<<"尝试打开用户存储文件"<<filename<<"...\n";
    cout<<"***********\n";
    ifstream fin(filename);
    if(!fin)
    {
        cout<<"用户存储文件"<<filename<<"打开失败！\n";
        system("pause");
        exit(0);
    }
    string line; 
    cin.ignore();
    while(getline(fin,line))
    {
        if(line.substr(0,line.find(','))==myAccount&&line.substr(line.find(',')+1)==password)
        {
            fin.close();
            return true;
        }
    }
    fin.close();
    cout<<"账号或密码错误！\n"; 
    return false;
}

void adminLogin()//管理员登录
{
    cout<<"***********\n";
    cout<<"您选择以管理员身份登录\n";
    cout<<"***********\n";
    string password="";
    while(true)
    {
        cout<<"请输入管理员账号：";
        cin>>myAccount;
        cout<<"***********\n";
        cout<<"请输入管理员密码：";
        cin>>password;
        cout<<"***********\n";
        if(checkAccount(password,"adminAccount.txt"))
        {
        	cout<<"登录成功！\n";
        	break;
		}
        else
        {
        	cout<<"登录失败！\n";
        	system("pause");
        	return;
		}
    }
    adminMenu();
}

void readerLogin()//读者登录
{
    cout<<"***********\n";
    cout<<"您选择以读者身份登录\n";
    cout<<"***********\n";
    string password="";
    while(true)
    {
        cout<<"请输入读者账号：";
        cin>>myAccount;
        cout<<"***********\n";
        cout<<"请输入读者密码：";
        cin>>password;
        cout<<"***********\n";
        if(checkAccount(password,"readerAccount.txt"))
        {
        	cout<<"登录成功！\n";
        	break;
		}
        else
        {
        	cout<<"登录失败！\n";
        	system("pause");
        	return;
		}
        break;
    }
    readerMenu();
}

void adminRegister()//管理员注册
{
	string account="",password="";
    
    ifstream fin("adminAccount.txt");
    if(!fin)
    {
        cout<<"用户存储文件adminAccount.txt打开失败！\n";
        system("pause");
        return;
    }
    cout<<"***********\n";
    cout<<"输入新账号\n";
    cin>>account;
    string line; 
    cin.ignore();
    while(getline(fin,line))
    {
        if(line.substr(0,line.find(','))==account&&account!="0")
        {
        	cout<<"账号已存在！\n";
        	system("pause");
        	return;
        }
        else break;
    }
    fin.close();
    
    cout<<"***********\n";
    cout<<"设置密码\t(或输入0返回)\n";
    cin>>password;
    if(password=="0") return;
    else
    {
		ofstream fout("adminAccount.txt",ios::app);
		if(!fout)
    	{
        	cout<<"用户存储文件adminAccount.txt打开失败！\n";
        	system("pause");
        	return;
    	}
    	fout<<account<<","<<password<<"\n";
    	fout.close();
    	
    	cout<<"新管理员账号已注册成功，即将回到登录页面！\n";
    	system("pause");
    	return;
	}  
}

void readerRegister()//读者注册
{
	string account="",password="";
    
    ifstream fin("readerAccount.txt");
    if(!fin)
    {
        cout<<"用户存储文件readerAccount.txt打开失败！\n";
        system("pause");
        return;
    }
    cout<<"***********\n";
    cout<<"输入新账号\n";
    cin>>account;
    string line; 
    cin.ignore();
    while(getline(fin,line))
    {
        if(line.substr(0,line.find(','))==account&&account!="0")
        {
        	cout<<"账号已存在！\n";
        	system("pause");
        	return;
        }
        else break;
    }
    fin.close();
    
    cout<<"***********\n";
    cout<<"设置密码\t(或输入0返回)\n";
    cin>>password;
    if(password=="0") return;
    else
    {
    	//写入账号密码存储文件
		ofstream fout("readerAccount.txt",ios::app);
		if(!fout)
    	{
        	cout<<"用户存储文件readerAccount.txt打开失败！\n";
        	system("pause");
        	return;
    	}
    	fout<<account<<","<<password<<"\n"
			<<"读者\n"
			<<"0\n";
    	fout.close();
    	//写入个人借阅记录文件
    	ofstream pfout("psRecord.txt",ios::app);
    	if(!pfout)
    	{
        cout<<"个人借阅记录psRecord.txt打开失败！\n";
        system("pause");
        return;
    	}
    	pfout<<"\n"<<account<<"\n";
		pfout.close();
		
    	cout<<"新读者账号已注册成功，即将回到登录页面！\n";
		system("pause");
    	return;
	}
}

void start()//开始界面
{
	while(true)
	{
    	cout<<"***********\n";
    	cout<<"欢迎使用图书管理系统\n";
    	cout<<"***********\n";
    	cout<<"请选择登录身份\t(或按0退出系统)\n";
    	cout<<"1.管理员登录\n";
    	cout<<"2.读者登录\n";
    	cout<<"3.管理员注册\n";
    	cout<<"4.读者注册\n";
    	cout<<"你的选择:";
    	char choice;
    	cin>>choice;
    	switch(choice)
    	{
    		case '0': exit(0);break;
        	case '1': adminLogin();break;
        	case '2': readerLogin();break;
        	case '3': adminRegister();return;break;
        	case '4': readerRegister();return;break;
        	default: cout<<"输入无效，请重新输入！\n";start();break;
    	}
	}
}

int main()//主函数
{
    while(true)
    {
    	ctrl.bookHead=ctrl.bookCreateHead();
		ctrl.userHead=ctrl.userCreateHead();
    
		ctrl.bookFin(ctrl.bookHead,"bookInfo.txt");
		ctrl.userFin(ctrl.userHead,"readerAccount.txt");
		
		myAccount="";
		
        start();
        system("cls");
    }
    
    ctrl.bookFout(ctrl.bookHead,"bookInfo.txt");
    ctrl.userFout(ctrl.userHead,"userAccount.txt");
    return 0;
}