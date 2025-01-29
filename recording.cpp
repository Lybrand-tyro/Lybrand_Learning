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

void dispRec(const string& filename)//打印记录
{
	ifstream fin(filename);
    if(!fin)
    {
        cout<<"记录"<<filename<<"打开失败！\n";
        system("pause");
        return;
    }
    string line="";
    while(getline(fin,line))
    {
    	cout<<line<<"\n";
	}
	fin.close();
	system("pause");
	return;
}

void addHold(const string& title,const string& id)//添加馆藏书籍记录
{
	ofstream fout("holdRecord.txt",ios::app);
    if(!fout)
    {
        cout<<"馆藏记录holdRecord.txt打开失败！\n";
        system("pause");
        return;
    }
    fout<<"管理员"<<myAccount<<"新增图书"<<title<<","<<id<<"\n";
	fout.close();
	return;
}

void dltHold(const string& title,const string& id)//删除馆藏书籍记录
{
	ofstream fout("holdRecord.txt",ios::app);
    if(!fout)
    {
        cout<<"馆藏记录holdRecord.txt打开失败！\n";
        system("pause");
        return;
    }
    fout<<"管理员"<<myAccount<<"删除图书"<<title<<","<<id<<"\n";
	fout.close();
	return;
}

void borRecord(const string& title,const string& id)//借阅记录
{
	ofstream fout("borrowRecord.txt",ios::app);
    if(!fout)
    {
        cout<<"借阅记录borrowRecord.txt打开失败！\n";
        system("pause");
        return;
    }
    fout<<"读者"<<myAccount<<"借阅图书"<<title<<","<<id<<"\n";
	fout.close();
	return;
}

void retRecord(const string& title,const string& id)//归还记录
{
	ofstream fout("borrowRecord.txt",ios::app);
    if(!fout)
    {
        cout<<"借阅记录borrowRecord.txt打开失败！\n";
        system("pause");
        return;
    }
    fout<<"读者"<<myAccount<<"归还图书"<<title<<","<<id<<"\n";
	fout.close();
	return;
}

void psBorrow(const string& title,const string& id)//借阅记录（写入个人）
{
	vector<string> lines;
	string line;
	string newline="借阅图书"+title+","+id;
	ifstream fin("psRecord.txt");
	if(!fin)
	{
		cout<<"个人借阅记录psRecord.txt打开失败！\n";
        system("pause");
        return;
	}
	while(getline(fin,line))
	{
		if(line=="") lines.push_back("\n");
        else lines.push_back(line);
    }
    fin.close();
    
    for(size_t i=0;i<lines.size();++i)
    {
    	if(lines[i]==myAccount)
    	{
    		lines.insert(lines.begin()+i+1,newline);
    		break;
		}
	}
    
	ofstream fout("psRecord.txt",ios::trunc);
    if(!fout)
    {
        cout<<"个人借阅记录psRecord.txt打开失败！\n";
        system("pause");
        return;
    }
    for(size_t i=0;i<lines.size();++i)
    {
    	if(lines[i]!="\n") fout<<lines[i]<<"\n";
    	else fout<<"\n";
	}
	fout.close();
	
	return;
}

void psReturn(const string& title,const string& id)//归还记录（写入个人）
{
	vector<string> lines;
	string line;
	string newline="归还图书"+title+","+id;
	ifstream fin("psRecord.txt");
	if(!fin)
	{
		cout<<"个人借阅记录psRecord.txt打开失败！\n";
        system("pause");
        return;
	}
	while(getline(fin,line))
	{
        if(line=="") lines.push_back("\n");
        else lines.push_back(line);
    }
    fin.close();
    
    for(size_t i=0;i<lines.size();++i)
    {
    	if(lines[i]==myAccount)
    	{
    		lines.insert(lines.begin()+i+1,newline);
    		break;
		}
	}
    
	ofstream fout("psRecord.txt",ios::trunc);
    if(!fout)
    {
        cout<<"个人借阅记录psRecord.txt打开失败！\n";
        system("pause");
        return;
    }
    for(size_t i=0;i<lines.size();++i)
    {
    	if(lines[i]!="\n") fout<<lines[i]<<"\n";
    	else fout<<"\n";
	}
	fout.close();
	
	return;
}