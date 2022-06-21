/********************
* ��Ȩ���� (C)2022, Yuxing Liu��
*
* �ļ����ƣ� flight.cpp
* �ļ���ʶ����
* ����ժҪ����ɹ��ں������¼����ļ�
* ����˵������
* ��ǰ�汾�� V1.0
* �� �ߣ������� 
* ������ڣ� 2022-05-10 
********************/
#include <iostream>
#include"head.h"
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;
/*******************
* ������������ʼ������
* ��������� ��
* ��������� ��
* ����ֵ�� void
* ����˵������
********************/
void Init_flight(flightnode *&h)//��ʼ������
{
	h = (flightnode *)malloc(sizeof(flightnode));
	h->next = NULL;
}
/*******************
* �������������뺽����Ϣ
* ��������� ����FlightList.dat��Ϣ������
* ��������� ��
* ����ֵ�� void
* ����˵������
********************/
void Load_flight(flightnode *&h)//���뺽��
{
	flightnode *f = h;
	flightnode *s;
	s = (flightnode *)malloc(sizeof(flightnode));
	ifstream infile("FlightList.dat", ios::in);
	if (!infile)
	{
		cerr << "                  ��Ϣ����";
		return;
	}
	while (1)
	{
		infile >> s->flight_num >> s->time >> s->start_place >> s->end_place >> s->price >> s->left;
		if (!infile.eof())
		{
			f->next = s;
			f = f->next;
			s = (flightnode *)malloc(sizeof(flightnode));
		}
		else
			break;
	}
	f->next = NULL;
	free(s);
}
/*******************
* ������������Ӻ���
* ��������� ����������Ϣ
* ��������� ��ӳɹ�����ѡ��������
* ����ֵ�� void
* ����˵������
********************/
void Add_flight(flightnode *&h)//��Ӻ���
{
	char mark = 'y';
	flightnode *s, *r;
	r = h;
	for (; r->next != NULL; r = r->next) {}
	while (mark == 'y')
	{
		s = (flightnode *)malloc(sizeof(flightnode));
		cout << "                  �����뺽��ţ�";
		cin >> s->flight_num;
		cout << "                  ���������ʱ�䣺";
		cin >> s->time;
		cout << "                  �����������:";
		cin >> s->start_place;
		cout << "                  ������Ŀ�ĵأ�";
		cin >> s->end_place;
		cout << "                  ������۸�";
		cin >> s->price;
		cout << "                  ��������Ʊ��";
		cin >> s->left;
 
		r->next = s;
		r = s;
		cout << "                  ��ӳɹ���" << endl;
		cout << "                  �Ƿ������ӣ����ǡ�y��/��n������";
		cin >> mark;
	}
	r->next = NULL;
}
/*******************
* �������������Һ���
* ��������� ѡ����ҷ�ʽ
* ��������� ������غ������в��ҹ���
* ����ֵ�� void
* ����˵������
********************/
void Check_flight(flightnode *&h)//���Һ���
{
	system("cls");
	int i;
	cout << "                  �������������������������������������������������������������������������������� " << endl;
	cout << "                            ��    �� ���ҷ�ʽ ��    �� " << endl;
	cout << "                 ��                                        �� " << endl;
	cout << "                            ��     1.�������       �� " << endl;
	cout << "                 ��                                        �� " << endl;
	cout << "                            ��    2.��ʼ�ز���      �� " << endl;
	cout << "                 ��                                        �� " << endl;
	cout << "                            ��   3.���ȫ������     �� " << endl;
	cout << "                 ��                                        �� " << endl;
	cout << "                  �������������������������������������������������������������������������������� " << endl;
	cout << "                  ��������ҷ�ʽ��";
	cin >> i;
	if (i == 1)
		Check_flightnum(h);
	else if (i == 2)
		Check_seplace(h);
	else if (i == 3)
		Check_all(h);
}
/*******************
* ��������������Ų���
* ��������� �����
* ��������� ����������Ϣ
* ����ֵ�� void
* ����˵������
********************/
void Check_flightnum(flightnode *&h)//����Ų���
{
 
	char flightnum[10];
	flightnode *p = h;
	cout << setw(32) << "�����뺽��ţ�";
	cin >> flightnum;
	cout << setw(25) << "�����" << setw(15) << "�������" << setw(15) << "������" << setw(15) << "Ŀ�ĵ�" << setw(15) << "�۸�" << setw(15) << "��Ʊ" << endl;
	while (p != NULL)
	{
		if (strcmp(p->flight_num, flightnum) == 0)
		{
			cout << setw(25) << p->flight_num << setw(15) << p->time << setw(15) << p->start_place << setw(15) << p->end_place << setw(15) << p->price << setw(15) << p->left << endl;
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
* ������������ʼ�ز���
* ��������� ��ʼ��
* ��������� ����������Ϣ
* ����ֵ�� void
* ����˵������
********************/
void Check_seplace(flightnode *&h)//��ʼ�ز���
{
	char start_place[20], end_place[20];
	cout << "                  ����������أ�";
	cin >> start_place;
	cout << "                  ������Ŀ�ĵأ�";
	cin >> end_place;
	flightnode *p = h->next;
	cout << setw(25) << "�����" << setw(15) << "�������" << setw(15) << "������" << setw(15) << "Ŀ�ĵ�" << setw(15) << "�۸�" << setw(15) << "��Ʊ" << endl;
	while (p != NULL)
	{
		if (strcmp(p->start_place, start_place) == 0 && strcmp(p->end_place, end_place) == 0)
		{
			cout << setw(25) << p->flight_num << setw(15) << p->time << setw(15) << p->start_place << setw(15) << p->end_place << setw(15) << p->price << setw(15) << p->left << endl;
			cout << setw(32);
			system("pause");
			return;
		}
		p = p->next;
	}
	cout << setw(32) << "δ�鵽�κ���Ϣ";
	system("pause");
}
/*******************
* �������������ȫ������
* ��������� 
* ��������� ����������Ϣ
* ����ֵ�� void
* ����˵������
********************/
void Check_all(flightnode *&h)//���ȫ������
{
 
	flightnode *p = h->next;
	cout << setw(25) << "�����" << setw(15) << "�������" << setw(15) << "������" << setw(15) << "Ŀ�ĵ�" << setw(15) << "�۸�" << setw(15) << "��Ʊ" << endl;
	while (p != NULL)
	{
		cout << setw(25) << p->flight_num << setw(15) << p->time << setw(15) << p->start_place << setw(15) << p->end_place << setw(15) << p->price << setw(15) << p->left << endl;
		p = p->next;
	}
}
/*******************
* �����������޸ĺ�����Ϣ
* ���������ѡ���޸ķ�ʽ
* ��������� ������غ�������ʵ��
* ����ֵ�� void
* ����˵������
********************/
void Revise_flight(flightnode *&h)//�޸ĺ�����Ϣ
{
	flightnode *f = h->next;
	int i;
	cout << "                  �������������������������������������������������������������������������������� " << endl;
	cout << "                            ��    �� �޸ķ�ʽ ��    �� " << endl;
	cout << "                 ��                                        �� " << endl;
	cout << "                            ��     1.ɾ������       �� " << endl;
	cout << "                 ��                                        �� " << endl;
	cout << "                            ��    2.�޸����ʱ��    �� " << endl;
	cout << "                 ��                                        �� " << endl;
	cout << "                            ��    3.�޸ĺ���۸�    �� " << endl;
	cout << "                 ��                                        �� " << endl;
	cout << "                            ��       4.����         �� " << endl;
	cout << "                 ��                                        �� " << endl;
	cout << "                  �������������������������������������������������������������������������������� " << endl;
	cout << "                  ��������ҷ�ʽ��";
	cin >> i;
	if (i == 1)
		Delete_flight(h);
	else if (i == 2)
		Revise_time(h);
	else if (i == 3)
		Revise_price(h);
	else if (i == 4)
		return;
}
/*******************
* ����������ɾ������
* ��������������
* ��������� ɾ���ɹ�
* ����ֵ�� void
* ����˵������
********************/
void Delete_flight(flightnode *&h)//ɾ������
{
	flightnode *p = h->next, *q = h;
	char flightnum[10];
	cout << "                  ����������Ҫ�޸ĵĺ���ţ�";
	cin >> flightnum;
	while (p != NULL)
	{
		if (strcmp(p->flight_num, flightnum) == 0)
		{
			q->next = p->next;
			free(p);
			cout << "                  ɾ���ɹ���";
			return;
		}
		q = q->next;
		p = q->next;
 
	}
}
/*******************
* �����������޸���ɵִ�ʱ��
* �������������ţ��µĺ����
* ��������� �޸ĳɹ�
* ����ֵ�� void
* ����˵������
********************/
void Revise_time(flightnode *&h)//�޸���ɵִ�ʱ��
{
	char flightnum[10];
	flightnode *p = h->next;
	cout << "                  ����������Ҫ�޸ĵĺ���ţ�";
	cin >> flightnum;
	while (p != NULL)
	{
		if (strcmp(p->flight_num, flightnum) == 0)
		{
			cout << "          �������µ����ʱ�䣺";
			cin >> p->time;
			cout << "          �޸ĳɹ���";
			return;
		}
	}
	cout << "                  û������Ҫ�޸ĵĺ����!";
	system("pause");
}
/*******************
* �����������޸ļ۸�
* �������������ţ��µļ۸�
* ��������� �޸ĳɹ�
* ����ֵ�� void
* ����˵������
********************/
void Revise_price(flightnode *&h)//�޸ļ۸�
{
	char flightnum[10];
	flightnode *p = h->next;
	cout << "                  ����������Ҫ�޸ĵĺ���ţ�";
	cin >> flightnum;
	while (p != NULL)
	{
		if (strcmp(p->flight_num, flightnum) == 0)
		{
			cout << "          �������µļ۸�";
			cin >> p->price;
			cout << "          �޸ĳɹ���	";
			return;
		}
	}
	cout << "                  û������Ҫ�޸ĵĺ����!";
	system("pause");
}
/*******************
* �������������溽����Ϣ
* �����������
* ����������û�����Ϣ���ļ�FlightList.dat
* ����ֵ�� void
* ����˵����
********************/
void Save_flight(flightnode *&h)//���溽����Ϣ
{
	flightnode *f = h->next;
	ofstream outfile("FlightList.dat", ios::trunc);
	if (!outfile)
	{
		cerr << "                  �洢ʧ�ܣ�";
		return;
	}
	while (f != NULL)
	{
		outfile << f->flight_num << " " << f->time << " " << f->start_place << " " << f->end_place << " " << f->price << " " << f->left << endl;
		f = f->next;
	}
	outfile.close();
}
