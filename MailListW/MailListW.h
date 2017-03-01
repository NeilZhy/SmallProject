#ifndef __MAILLISTW_H__
#define __MAILLISTW_H__

#define NAME_MAX 10
#define SEX_MAX 5
#define TEL_MAX 12
#define ADDRESS_MAX 15
#define ALLMAX 2
#define ADDMAX 3



typedef struct PeoInfo
{
	char name[NAME_MAX];
	char sex[SEX_MAX];
	char age[5];
	char tel[TEL_MAX];
	char address[ADDRESS_MAX];
}PeoInfo;

typedef struct MailList
{
	//PeoInfo maillist[ALLMAX];
	PeoInfo *maillist;
	int count;
	int MAX;
}MailList, *pMailList;

void menu();
void test();
void InitMailList(pMailList pmail);
void add(pMailList pmail);
void del(pMailList pmail);
void Dprint(pMailList pmail, int i);
int search(pMailList pmail);
void del(pMailList pmail);
void show(pMailList pmail);
void empty(pMailList pmail);
void change(pMailList pmail);
void sort(pMailList pmail);
void Read(pMailList pmail);
void save(pMailList pmail);


#endif  //__MAILLISTW_H__