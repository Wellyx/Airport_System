/********************
* 版权所有 (C)2022, Yuxing Liu。
*
* 文件名称： passenger.cpp
* 文件标识：无
* 内容摘要：完成关于用户类事件的文件
* 其它说明：无
* 当前版本： V1.0
* 作 者：刘宇星 
* 完成日期： 2022-05-10 
********************/
#include <iostream>
#include "head.h"
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;
/*******************
* 功能描述：初始化用户
* 输入参数： 无
* 输出参数： 无
* 返回值： void
* 其它说明：无
********************/
void Init_passenger(passengernode *&c)//初始化用户
{
	c = (passengernode *)malloc(sizeof(passengernode));
	c->next = NULL;
}
/*******************
* 功能描述：载入用户信息
* 输入参数： 载入PassengerList.dat信息到链表
* 输出参数： 无
* 返回值： void
* 其它说明：无
********************/
void Load_passenger(passengernode *&c)//载入用户信息
{
	passengernode *p = c;
	passengernode *s;
	s = (passengernode *)malloc(sizeof(passengernode));
	ifstream infile("PassengerList.dat", ios::in);
	if (!infile)
	{
		cerr << "                  信息错误。";
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
* 功能描述：航班信息
* 输入参数：passenger的相关信息
			flight的相关信息
* 输出参数： 购票成功 or 失败
* 返回值： void
* 其它说明：如果余票不足还可以预定，如果有多余的票即可瞬间购买
********************/
void Book(flightnode *&h, passengernode *&c)//订票
{
	char start_place[20], end_place[20], flightnum[10];//航班信息
	flightnode *p = h->next, *q = h->next;
	passengernode *s, *r = c;
	char mark, check = '1';
	for (; r->next != NULL; r = r->next) {}
	s = (passengernode *)malloc(sizeof(passengernode));
	cout << "                  请输入您的姓名：";
	cin >> s->name;
	cout << "                  请输入您的证件号：";
	cin >> s->ID_num;
 
	cout << "                  请输入出发地：";
	cin >> start_place;
	cout << "                  请输入目的地：";
	cin >> end_place;
	cout << setw(25) << "航班号" << setw(15) << "起飞日期" << setw(15) << "出发地" << setw(15) << "目的地" << setw(15) << "价格" << setw(15) << "余票" << endl;
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
		cout << "                  没想相关的航班，";
		system("pause");
		return;
	}
	cout << "                  请输入您想要购买的航班号：";
	cin >> flightnum;
	while (q != NULL)
	{
		if (strcmp(q->flight_num, flightnum) == 0 && strcmp(q->start_place, start_place) == 0 && strcmp(q->end_place, end_place) == 0)
		{
			if (q->left == 0)
			{
				cout << "                  余票不足，请选择是否预约（是“y”/否“n”）";
				cin >> mark;
				if (mark == 'y')
				{
					s->full = 1;
					strcpy(s->flight_num, flightnum);
					cout << "                  预约成功！";
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
			//购票成功
			cout << "                  购票成功！" << endl;
			q->left--;
			cout << "                  ";
			system("pause");
			return;
		}
		else
			q = q->next;
	}
	cout << "                  航班号填入错误！" << endl;
	cout << "                  ";
	system("pause");
}
/*******************
* 功能描述：退票
* 输入参数：passenger的相关信息
* 输出参数： 退票成功 or 失败
* 返回值： void
* 其它说明：
********************/
void Qbook(flightnode *&h, passengernode *&c)//退票
{
	char name[30];
	char ID_num[30];
	flightnode *f = h->next;
	passengernode *p = c->next, *q = c, *t = c->next;
	cout << "                  请输入您的姓名：";
	cin >> name;
	cout << "                  请输入您的证件号：";
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
			cout << "                  退票成功！";
			return;
		}
		q = q->next;
		p = q->next;
	}
 
 
}
/*******************
* 功能描述：查询订票
* 输入参数：passenger的相关信息
* 输出参数： 所查用户订票的信息
* 返回值： void
* 其它说明：
********************/
void Check_book(passengernode *&c)//查询订票
{
	char name[30];
	char ID_num[30];
	passengernode *p = c->next;
	cout << "                  请输入您的姓名：";
	cin >> name;
	cout << "                  请输入您的证件号：";
	cin >> ID_num;
	cout << setw(25) << "姓名" << setw(15) << "航班号" << setw(15) << "起飞日期" << setw(15) << "出发地" << setw(15) << "目的地" << setw(15) << "价格" << setw(15) << endl;
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
	cout << setw(32) << "未查到任何信息。";
	system("pause");
}
/*******************
* 功能描述：保存用户信息
* 输入参数：无
* 输出参数：用户的信息到文件PassengerList.dat
* 返回值： void
* 其它说明：
********************/
void Save_passenger(passengernode *&c)//保存用户信息
{
	passengernode *p = c->next;
	ofstream outfile("PassengerList.dat", ios::trunc);
	if (!outfile)
	{
		cerr << "                  存储失败！";
		return;
	}
	while (p != NULL)
	{
		outfile << p->name << " " << p->ID_num << " " << p->flight_num << " " << p->time << " " << p->start_place << " " << p->end_place << " " << p->price << endl;
		p = p->next;
	}
	outfile.close();
}
