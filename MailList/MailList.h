#ifndef __MAILLIST_H__
#define __MAILLIST_H__

#define NAME_MAX 10
#define SEX_MAX 5
#define TEL_MAX 12
#define ADDRESS_MAX 15
#define MAX 100


typedef struct PeoInfo
{
	char name[NAME_MAX];
	char sex[SEX_MAX];
	int age;
	char tel[TEL_MAX];
	char address[ADDRESS_MAX];
}PeoInfo;

typedef struct MailList
{
	PeoInfo maillist[MAX];
	int count;
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


#endif