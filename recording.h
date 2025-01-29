#ifndef RECORDING_H
#define RECORDING_H

extern string myAccount;

void dispRec(const string& filename);
void addHold(const string& title,const string& id);
void dltHold(const string& title,const string& id);
void borRecord(const string& title,const string& id);
void retRecord(const string& title,const string& id);
void psBorrow(const string& title,const string& id);
void psReturn(const string& title,const string& id);

#endif //RECORDING_H