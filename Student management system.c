#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <windows.h>

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

void print1()
{
	printf("***\t��ʾ\t***\n");
	printf("����1--��ѯ�ܷ���߷�ѧ����Ϣ\n");
	printf("����2--��ѯC���Բ�����ѧ����Ϣ\n");
	printf("����3--���ܳɼ���������ѧ����Ϣ\n");
	printf("����4--ͳ������C���Գɼ�ƽ����\n");
	printf("����5--ͳ������C���Գɼ�����\n");
	printf("����6--����ѧ����Ϣ\n");
	printf("����7--��ѧ��ɾ��һ��ѧ����Ϣ\n");
	printf("����8--��ѧ�Ų��Ҳ��޸ĸ�ѧ����Ϣ\n");
	printf("����0--�˳�\n");
}

void input(Student *p)//����ѧ����Ϣ
{
	system("cls");
	printf("������ѧ��:");
	scanf("%ld", &p->num);
	printf("����������:");
	scanf("%s", &p->nam);
	printf("����������ɼ�:");
	scanf("%f", &p->score.math);
	printf("������Ӣ��ɼ�:");
	scanf("%f", &p->score.english);
	printf("������C���Գɼ�:");
	scanf("%f", &p->score.program);
	p->score.grade = (p->score.math) + (p->score.english) + (p->score.program);
	p->score.ave = p->score.grade / 3;
	system("cls");
}

Student *creatlist()
{
	Student *p, *head;
	int i, m;
	head = NULL;
	m = 0;
	printf("\n��Ҫ�洢��ѧ����Ϣ����Ϊ:");
	scanf("%d", &m);

	for (i = 0; i<m; i++)
	{
		p = (Student *)malloc(sizeof(Student));
		memset(p, 0, sizeof(Student));//��ʼ��Ϊ0
		input(p);
		p->next = head;
		head = p;
	}

	return head;
}



void output(Student *p)//��ʾѧ���ɼ���Ϣ
{
	printf("ѧ��:%ld\t", p->num);
	printf("����:%12s\t", p->nam);
	printf("�����ɼ�:%3.2f\t", p->score.math);
	printf("Ӣ��ɼ�:%3.2f\t", p->score.english);
	printf("C���Գɼ�:%3.2f\t", p->score.program);
	printf("�ܳɼ�:%3.2f\t", p->score.grade);
	printf("ƽ����:%3.2f\n", p->score.ave);
}


void high(Student *head, Student *p)//�����ܷ���߷�
{
	Student *a, *b;
	a = head;
	b = head;//p=head->next
	while (NULL != b)
	{
		if (a->score.grade< b->score.grade)
			a = b;
		b = b->next;
	}
	output(a);
}


void low(Student *head, Student *p)//����c���Բ�����ѧ���ɼ�
{
	Student *c;
	c = head;
	//	p=head;
	while (NULL != c)
	{
		if (c->score.program<60)
			output(c);
		c = c->next;
	}
}

void pingjun(Student *head)
{
	Student *p;
	int u = 0;
	float sum = 0, ave1;
	p = head;
	while (p != NULL)
	{
		u++;
		sum = sum + p->score.program;
		p = p->next;
	}
	ave1 = sum / u;
	printf("C���Ե�ƽ����Ϊ��%3.2f", ave1);
	printf("\n");
}


void fangcha(Student *head)
{
	Student *p, *w;
	int u = 0;
	float sum = 0, ave1, ave2;
	p = head;
	while (p != NULL)
	{
		u++;
		sum = sum + p->score.program;
		p = p->next;
	}
	ave1 = sum / u;
	u = 0;
	sum = 0.0;
	w = head;
	while (w != NULL)
	{
		u++;
		sum = sum + (w->score.program - ave1)*(w->score.program - ave1);
		w = w->next;
	}
	ave2 = sum / u;
	printf("C���Եķ����Ϊ��%3.2f", ave2);
	printf("\n");

}

Student *insert(Student *head, Student *p)//���ڿ�ͷ����һ��ѧ����Ϣ
{
	p = (Student *)malloc(sizeof(Student));
	p->next = head;
	head = p;
	printf("����������Ҫ�����ѧ����Ϣ��\n");
	input(head);
	return head;
}


Student *delet(Student *head)//��ѧ��ɾ��һ��ѧ����Ϣ
{
	Student *p, *q, *w;
	p = head;
	q = head;
	long num1;
	printf("����������Ҫɾ����ѧ����ѧ�ţ�\n");
	scanf("%ld", &num1);
	if (head->num == num1)
	{
		p = head->next;
		free(head);
		return p;
	}

	else
	{
		while (NULL != q)
		{
			if (q->next->num == num1)
			{
				w = q->next;
				q->next = q->next->next;
				free(w);
				printf("ѧ����Ϣ��ɾ��\n");
				return p;
			}
			q = q->next;
		}
		return p;//return NULL;
	}
}

void update(Student *head)//����ѧ�Ÿ�������
{
	Student *p;
	long q;
	p = head;
	printf("��������Ҫ���ҵ�ѧ��ѧ��");
	scanf("%ld", &q);
	while (NULL != p)
	{
		if (p->num == q)
		{
			output(p);
			system("pause");
			printf("\n");
			printf("������������Ҫ�޸ĵ�ѧ����Ϣ��\n");
			input(p);
		}
		p = p->next;
	}
	p = NULL;

}

void sort(Student* head)//���ܳɼ�����
{
	Student *m = head, *pt, *temp;
	temp = (Student *)malloc(sizeof(Student));;
	while (m != NULL)
	{
		pt = m;
		while (pt != NULL)
		{
			if (m->score.grade < pt->score.grade)
			{
				temp->num = m->num;
				strcpy(temp->nam, m->nam);
				temp->score.math = m->score.math;
				temp->score.english = m->score.english;
				temp->score.program = m->score.program;
				temp->score.grade = m->score.grade;

				m->num = pt->num;
				strcpy(m->nam, pt->nam);
				m->score.math = pt->score.math;
				m->score.english = pt->score.english;
				m->score.program = pt->score.program;
				m->score.grade = pt->score.grade;

				pt->num = temp->num;
				strcpy(pt->nam, temp->nam);
				pt->score.math = temp->score.math;
				pt->score.english = temp->score.english;
				pt->score.program = temp->score.program;
				pt->score.grade = temp->score.grade;

			}
			pt = pt->next;
		}
		m = m->next;
	}
	m = head;
	while (NULL != m)
	{
		output(m);
		m = m->next;
	}
	m = head;
}



int main()
{
	int m, n = 1;//����
	Student *head = NULL;
	Student *p = NULL;

	printf("����������ѧ����Ϣ\n");//����
	head = creatlist();//����������ȡ����
	print1();//����


	while (n != 0)
	{
		scanf("%d", &m);
		switch (m)
		{
		case 1:high(head, p); break;
		case 2:low(head, p); break;
		case 3:sort(head); break;
		case 4:pingjun(head); break;
		case 5:fangcha(head); break;
		case 6:head = insert(head, p); break;
		case 7:head = delet(head); break;
		case 8:update(head); break;
		default:printf("лл����ʹ�ã�����ر�\n�������Ǵ˴������ѧ����Ϣ��\n");
		}
		n = m;
	}
	sort(head);
	return 0;
}


