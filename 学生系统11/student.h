#ifndef STUDENT_H
#define STUDENT_H

typedef struct _score
{
	float math;
	float english;
	float program;
	float grade;
	float ave;
}Score;

typedef struct _student
{
	long num;
	char nam[10];
	Score score;
	struct _student *next;
}Student;

void print1();
Student *creatlist();
void input(Student *p);
void output(Student *p);
void high(Student *head,Student *p);
void low(Student *head,Student *p);
Student *insert(Student *head,Student *p);
Student *delet(Student *head);
void update(Student *head);
void sort(Student* head);
void pingjun(Student *head);
void fangcha(Student *head);

#endif
