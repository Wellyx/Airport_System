/********************
* ��Ȩ���� (C)2022, Yuxing Liu��
*
* �ļ����ƣ� passenger.cpp
* �ļ���ʶ����
* ����ժҪ����ɹ����û����¼����ļ�
* ����˵������
* ��ǰ�汾�� V1.0
* �� �ߣ������� 
* ������ڣ� 2022-05-10 
********************/
#include <iostream>
#include "head.h"
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;
/*******************
* ������������ʼ���û�
* ��������� ��
* ��������� ��
* ����ֵ�� void
* ����˵������
********************/
void Init_passenger(passengernode *&c)//��ʼ���û�
{
	c = (passengernode *)malloc(sizeof(passengernode));
	c->next = NULL;
}
/*******************
* ���������������û���Ϣ
* ��������� ����PassengerList.dat��Ϣ������
* ��������� ��
* ����ֵ�� void
* ����˵������
********************/
void Load_passenger(passengernode *&c)//�����û���Ϣ
{
	passengernode *p = c;
	passengernode *s;
	s = (passengernode *)malloc(sizeof(passengernode));
	ifstream infile("PassengerList.dat", ios::in);
	if (!infile)
	{
		cerr << "                  ��Ϣ����";
		return;
	}
	while (1)
	{
		infile >> s->name >> s->ID_num >> s->flight_num >> s->time >> s->start_place >> s->end_place >> s->price;
		if (!infile.eof())
		{
			p->next = s;
			p = p->next;
			s = (passengernode *)malloc(sizeof(passengernode));
		}
		else
			break;
	}
	p->next = NULL;
	free(s);
}
/*******************
* ����������������Ϣ
* ���������passenger�������Ϣ
			flight�������Ϣ
* ��������� ��Ʊ�ɹ� or ʧ��
* ����ֵ�� void
* ����˵���������Ʊ���㻹����Ԥ��������ж����Ʊ����˲�乺��
********************/
void Book(flightnode *&h, passengernode *&c)//��Ʊ
{
	char start_place[20], end_place[20], flightnum[10];//������Ϣ
	flightnode *p = h->next, *q = h->next;
	passengernode *s, *r = c;
	char mark, check = '1';
	for (; r->next != NULL; r = r->next) {}
	s = (passengernode *)malloc(sizeof(passengernode));
	cout << "                  ����������������";
	cin >> s->name;
	cout << "                  ����������֤���ţ�";
	cin >> s->ID_num;
 
	cout << "                  ����������أ�";
	cin >> start_place;
	cout << "                  ������Ŀ�ĵأ�";
	cin >> end_place;
	cout << setw(25) << "�����" << setw(15) << "�������" << setw(15) << "������" << setw(15) << "Ŀ�ĵ�" << setw(15) << "�۸�" << setw(15) << "��Ʊ" << endl;
	while (p != NULL)
	{
		if (strcmp(p->start_place, start_place) == 0 && strcmp(p->end_place, end_place) == 0)
		{
			cout << setw(25) << p->flight_num << setw(15) << p->time << setw(15) << p->start_place << setw(15) << p->end_place << setw(15) << p->price << setw(15) << p->left << endl;
			check = '0';
		}
		p = p->next;
	}
	if (check == '1')
	{
		cout << "                  û����صĺ��࣬";
		system("pause");
		return;
	}
	cout << "                  ����������Ҫ����ĺ���ţ�";
	cin >> flightnum;
	while (q != NULL)
	{
		if (strcmp(q->flight_num, flightnum) == 0 && strcmp(q->start_place, start_place) == 0 && strcmp(q->end_place, end_place) == 0)
		{
			if (q->left == 0)
			{
				cout << "                  ��Ʊ���㣬��ѡ���Ƿ�ԤԼ���ǡ�y��/��n����";
				cin >> mark;
				if (mark == 'y')
				{
					s->full = 1;
					strcpy(s->flight_num, flightnum);
					cout << "                  ԤԼ�ɹ���";
					r->next = s;
					r = s;
					r->next = NULL;
					system("pause");
					return;
				}
				else
					return;
			}
			strcpy(s->flight_num, flightnum);
			strcpy(s->start_place, start_place);
			strcpy(s->end_place, end_place);
			strcpy(s->time, q->time);
			s->price = q->price;
			r->next = s;
			r = s;
			r->next = NULL;
			//��Ʊ�ɹ�
			cout << "                  ��Ʊ�ɹ���" << endl;
			q->left--;
			cout << "                  ";
			system("pause");
			return;
		}
		else
			q = q->next;
	}
	cout << "                  ������������" << endl;
	cout << "                  ";
	system("pause");
}
/*******************
* ������������Ʊ
* ���������passenger�������Ϣ
* ��������� ��Ʊ�ɹ� or ʧ��
* ����ֵ�� void
* ����˵����
********************/
void Qbook(flightnode *&h, passengernode *&c)//��Ʊ
{
	char name[30];
	char ID_num[30];
	flightnode *f = h->next;
	passengernode *p = c->next, *q = c, *t = c->next;
	cout << "                  ����������������";
	cin >> name;
	cout << "                  ����������֤���ţ�";
	cin >> ID_num;
	while (p != NULL)
	{
		if (strcmp(p->name, name) == 0 && strcmp(p->ID_num, ID_num) == 0)
		{
			while (f != NULL)
			{
				if (strcmp(p->flight_num, f->flight_num) == 0)
				{
					f->left++;
					while (t != NULL)
					{
						if (strcmp(t->flight_num, p->flight_num) == 0 && t->full == 1)
						{
							strcpy(t->start_place, p->start_place);
							strcpy(t->end_place, p->end_place);
							strcpy(t->time, p->time);
							t->price = p->price;
							f->left--;
							break;
						}
						t = t->next;
					}
					break;
				}
				f = f->next;
			}
			q->next = p->next;
			free(p);
			cout << "                  ��Ʊ�ɹ���";
			return;
		}
		q = q->next;
		p = q->next;
	}
 
 
}
/*******************
* ������������ѯ��Ʊ
* ���������passenger�������Ϣ
* ��������� �����û���Ʊ����Ϣ
* ����ֵ�� void
* ����˵����
********************/
void Check_book(passengernode *&c)//��ѯ��Ʊ
{
	char name[30];
	char ID_num[30];
	passengernode *p = c->next;
	cout << "                  ����������������";
	cin >> name;
	cout << "                  ����������֤���ţ�";
	cin >> ID_num;
	cout << setw(25) << "����" << setw(15) << "�����" << setw(15) << "�������" << setw(15) << "������" << setw(15) << "Ŀ�ĵ�" << setw(15) << "�۸�" << setw(15) << endl;
	while (p != NULL)
	{
		if (strcmp(p->name, name) == 0 && strcmp(p->ID_num, ID_num) == 0)
		{
			cout << setw(25) << p->name << setw(15) << p->flight_num << setw(15) << p->time << setw(15) << p->start_place << setw(15) << p->end_place << setw(15) << p->price << setw(15) << endl;
			cout << "                  ";
			system("pause");
			return;
		}
		else
			p = p->next;
	}
	cout << setw(32) << "δ�鵽�κ���Ϣ��";
	system("pause");
}
/*******************
* ���������������û���Ϣ
* �����������
* ����������û�����Ϣ���ļ�PassengerList.dat
* ����ֵ�� void
* ����˵����
********************/
void Save_passenger(passengernode *&c)//�����û���Ϣ
{
	passengernode *p = c->next;
	ofstream outfile("PassengerList.dat", ios::trunc);
	if (!outfile)
	{
		cerr << "                  �洢ʧ�ܣ�";
		return;
	}
	while (p != NULL)
	{
		outfile << p->name << " " << p->ID_num << " " << p->flight_num << " " << p->time << " " << p->start_place << " " << p->end_place << " " << p->price << endl;
		p = p->next;
	}
	outfile.close();
}
