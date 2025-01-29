#ifndef _ADMINPART_H
#define _ADMINPART_H
#include"mylist.h"

extern string myAccount;
extern myFunc ctrl;

void addUser();
void readerCtrl(userNode* pUser,string& account);
void readerUserManage();
void addBook();
void bookCtrl(bookNode* pBook,string& bookid);
void bookInfoManage();
void recordManage();
void adminMenu();

#endif //_ADMINPART_H