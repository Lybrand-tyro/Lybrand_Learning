# ifndef _READERPART_H
# define _READERPART_H
#include"mylist.h"

extern string myAccount;
extern myFunc ctrl;

void restore(bookNode* pBook,userNode* pUser,string& idInput);
void borrow(bookNode* pBook,userNode* pUser,string& idInput);
void ctrlChoice();
void searchBookUI();
void personalCenter();
void readerMenu();

# endif //_READERPART_H