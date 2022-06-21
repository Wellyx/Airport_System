/********************
* 版权所有 (C)2022, Yuxing Liu。
*
* 文件名称： flight.cpp
* 文件标识：无
* 内容摘要：完成关于航班类事件的文件
* 其它说明：无
* 当前版本： V1.0
* 作 者：刘宇星 
* 完成日期： 2022-05-10 
********************/
#include <iostream>
#include"head.h"
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;
/*******************
* 功能描述：初始化航班
* 输入参数： 无
* 输出参数： 无
* 返回值： void
* 其它说明：无
********************/
void Init_flight(flightnode *&h)//初始化航班
{
	h = (flightnode *)malloc(sizeof(flightnode));
	h->next = NULL;
}
/*******************
* 功能描述：载入航班信息
* 输入参数： 载入FlightList.dat信息到链表
* 输出参数： 无
* 返回值： void
* 其它说明：无
********************/
void Load_flight(flightnode *&h)//载入航班
{
	flightnode *f = h;
	flightnode *s;
	s = (flightnode *)malloc(sizeof(flightnode));
	ifstream infile("FlightList.dat", ios::in);
	if (!infile)
	{
		cerr << "                  信息错误。";
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
* 功能描述：添加航班
* 输入参数： 航班的相关信息
* 输出参数： 添加成功或者选择继续添加
* 返回值： void
* 其它说明：无
********************/
void Add_flight(flightnode *&h)//添加航班
{
	char mark = 'y';
	flightnode *s, *r;
	r = h;
	for (; r->next != NULL; r = r->next) {}
	while (mark == 'y')
	{
		s = (flightnode *)malloc(sizeof(flightnode));
		cout << "                  请输入航班号：";
		cin >> s->flight_num;
		cout << "                  请输入起飞时间：";
		cin >> s->time;
		cout << "                  请输入出发地:";
		cin >> s->start_place;
		cout << "                  请输入目的地：";
		cin >> s->end_place;
		cout << "                  请输入价格：";
		cin >> s->price;
		cout << "                  请输入余票：";
		cin >> s->left;
 
		r->next = s;
		r = s;
		cout << "                  添加成功！" << endl;
		cout << "                  是否继续添加？（是“y”/否“n”）：";
		cin >> mark;
	}
	r->next = NULL;
}
/*******************
* 功能描述：查找航班
* 输入参数： 选择查找方式
* 输出参数： 进入相关函数进行查找功能
* 返回值： void
* 其它说明：无
********************/
void Check_flight(flightnode *&h)//查找航班
{
	system("cls");
	int i;
	cout << "                  ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅ " << endl;
	cout << "                            ┇    ≡ 查找方式 ≡    ┇ " << endl;
	cout << "                 ┇                                        ┇ " << endl;
	cout << "                            ┇     1.航班查找       ┇ " << endl;
	cout << "                 ┇                                        ┇ " << endl;
	cout << "                            ┇    2.起始地查找      ┇ " << endl;
	cout << "                 ┇                                        ┇ " << endl;
	cout << "                            ┇   3.浏览全部航班     ┇ " << endl;
	cout << "                 ┇                                        ┇ " << endl;
	cout << "                  ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅ " << endl;
	cout << "                  请输入查找方式：";
	cin >> i;
	if (i == 1)
		Check_flightnum(h);
	else if (i == 2)
		Check_seplace(h);
	else if (i == 3)
		Check_all(h);
}
/*******************
* 功能描述：航班号查找
* 输入参数： 航班号
* 输出参数： 航班的相关信息
* 返回值： void
* 其它说明：无
********************/
void Check_flightnum(flightnode *&h)//航班号查找
{
 
	char flightnum[10];
	flightnode *p = h;
	cout << setw(32) << "请输入航班号：";
	cin >> flightnum;
	cout << setw(25) << "航班号" << setw(15) << "起飞日期" << setw(15) << "出发地" << setw(15) << "目的地" << setw(15) << "价格" << setw(15) << "余票" << endl;
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
	cout << setw(32) << "未查到任何信息。";
	system("pause");
}
/*******************
* 功能描述：起始地查找
* 输入参数： 起始地
* 输出参数： 航班的相关信息
* 返回值： void
* 其它说明：无
********************/
void Check_seplace(flightnode *&h)//起始地查找
{
	char start_place[20], end_place[20];
	cout << "                  请输入出发地：";
	cin >> start_place;
	cout << "                  请输入目的地：";
	cin >> end_place;
	flightnode *p = h->next;
	cout << setw(25) << "航班号" << setw(15) << "起飞日期" << setw(15) << "出发地" << setw(15) << "目的地" << setw(15) << "价格" << setw(15) << "余票" << endl;
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
	cout << setw(32) << "未查到任何信息";
	system("pause");
}
/*******************
* 功能描述：浏览全部航班
* 输入参数： 
* 输出参数： 航班的相关信息
* 返回值： void
* 其它说明：无
********************/
void Check_all(flightnode *&h)//浏览全部航班
{
 
	flightnode *p = h->next;
	cout << setw(25) << "航班号" << setw(15) << "起飞日期" << setw(15) << "出发地" << setw(15) << "目的地" << setw(15) << "价格" << setw(15) << "余票" << endl;
	while (p != NULL)
	{
		cout << setw(25) << p->flight_num << setw(15) << p->time << setw(15) << p->start_place << setw(15) << p->end_place << setw(15) << p->price << setw(15) << p->left << endl;
		p = p->next;
	}
}
/*******************
* 功能描述：修改航班信息
* 输入参数：选择修改方式
* 输出参数： 调用相关函数进行实现
* 返回值： void
* 其它说明：无
********************/
void Revise_flight(flightnode *&h)//修改航班信息
{
	flightnode *f = h->next;
	int i;
	cout << "                  ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅ " << endl;
	cout << "                            ┇    ≡ 修改方式 ≡    ┇ " << endl;
	cout << "                 ┇                                        ┇ " << endl;
	cout << "                            ┇     1.删除航班       ┇ " << endl;
	cout << "                 ┇                                        ┇ " << endl;
	cout << "                            ┇    2.修改起飞时间    ┇ " << endl;
	cout << "                 ┇                                        ┇ " << endl;
	cout << "                            ┇    3.修改航班价格    ┇ " << endl;
	cout << "                 ┇                                        ┇ " << endl;
	cout << "                            ┇       4.返回         ┇ " << endl;
	cout << "                 ┇                                        ┇ " << endl;
	cout << "                  ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅ " << endl;
	cout << "                  请输入查找方式：";
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
* 功能描述：删除航班
* 输入参数：航班号
* 输出参数： 删除成功
* 返回值： void
* 其它说明：无
********************/
void Delete_flight(flightnode *&h)//删除航班
{
	flightnode *p = h->next, *q = h;
	char flightnum[10];
	cout << "                  请输入您想要修改的航班号：";
	cin >> flightnum;
	while (p != NULL)
	{
		if (strcmp(p->flight_num, flightnum) == 0)
		{
			q->next = p->next;
			free(p);
			cout << "                  删除成功！";
			return;
		}
		q = q->next;
		p = q->next;
 
	}
}
/*******************
* 功能描述：修改起飞抵达时间
* 输入参数：航班号，新的航班号
* 输出参数： 修改成功
* 返回值： void
* 其它说明：无
********************/
void Revise_time(flightnode *&h)//修改起飞抵达时间
{
	char flightnum[10];
	flightnode *p = h->next;
	cout << "                  请输入您想要修改的航班号：";
	cin >> flightnum;
	while (p != NULL)
	{
		if (strcmp(p->flight_num, flightnum) == 0)
		{
			cout << "          请输入新的起飞时间：";
			cin >> p->time;
			cout << "          修改成功！";
			return;
		}
	}
	cout << "                  没有您想要修改的航班号!";
	system("pause");
}
/*******************
* 功能描述：修改价格
* 输入参数：航班号，新的价格
* 输出参数： 修改成功
* 返回值： void
* 其它说明：无
********************/
void Revise_price(flightnode *&h)//修改价格
{
	char flightnum[10];
	flightnode *p = h->next;
	cout << "                  请输入您想要修改的航班号：";
	cin >> flightnum;
	while (p != NULL)
	{
		if (strcmp(p->flight_num, flightnum) == 0)
		{
			cout << "          请输入新的价格：";
			cin >> p->price;
			cout << "          修改成功！	";
			return;
		}
	}
	cout << "                  没有您想要修改的航班号!";
	system("pause");
}
/*******************
* 功能描述：保存航班信息
* 输入参数：无
* 输出参数：用户的信息到文件FlightList.dat
* 返回值： void
* 其它说明：
********************/
void Save_flight(flightnode *&h)//保存航班信息
{
	flightnode *f = h->next;
	ofstream outfile("FlightList.dat", ios::trunc);
	if (!outfile)
	{
		cerr << "                  存储失败！";
		return;
	}
	while (f != NULL)
	{
		outfile << f->flight_num << " " << f->time << " " << f->start_place << " " << f->end_place << " " << f->price << " " << f->left << endl;
		f = f->next;
	}
	outfile.close();
}
