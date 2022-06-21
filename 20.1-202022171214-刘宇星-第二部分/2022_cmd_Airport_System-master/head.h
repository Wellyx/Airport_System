/********************
* 版权所有 (C)2022, Yuxing Liu。
*
* 文件名称： head.cpp
* 文件标识：无
* 内容摘要：定义航班和用户的信息，完成各个函数的声明
* 其它说明：无
* 当前版本： V1.0
* 作 者：刘宇星 
* 完成日期： 2022-05-10
********************/
#include <bits/stdc++.h>
using namespace std;
typedef struct flightnode
{
	char flight_num[10];//航班号
	char plane_num[10];//飞机号 
	char time[20];//起飞时间
	char date[20];//日期 
	char start_place[20];//出发地
	char end_place[20];//目的地
	int left;//余票
	int now_seat_num = 0;//当前的座次号 
	float price;//价格
	flightnode *next;
}flightnode;
typedef struct administrator
{
	char name[20];
	char password[20];
	administrator *next;
	administrator *pre;
}administrator;
typedef struct passengernode
{
	char name[30];//名字
	char ID_num[30];//证件号
	char flight_num[10];//航班号 
	char time[20];//起飞时间
	char start_place[20];//出发地
	char end_place[20];//目的地
	float price;//价格
	int full = 0;//是否处于候补状态 
	int seat_num;//座次号 
	passengernode *next;
}passengernode;
class Airline
{
	public:
		flightnode *head_of_flight;
		flightnode *tail_of_flight;
		passengernode *head_of_passenger;
		passengernode *tail_of_passenger;
		administrator *head_of_root;
		administrator *tail_of_root;
		char root_name[20] = "Yuxing_Liu";
		char root_password[20] = "20020316";
		void Init_flight();//初始化航班
		void Load_flight();//载入航班
		void Add_flight();//添加航班
		void Check_flight();//查找航班
		void Check_flightnum();//航班号查找
		void Check_seplace();//起始地查找
		void Check_all();//浏览全部航班
		void Check_ed();
		void Revise_flight();//修改航班信息
		void Delete_flight();//删除航班
		void Revise_time();//修改起飞抵达时间
		void Revise_price();//修改价格
		void Save_flight();//保存航班信息
		///用户信息
		void passenger_display();//用户信息展示 
		void Init_passenger();//初始化用户
		void Load_passenger();//载入用户信息
		void Book();//定票
		void Qbook();//退票
		void Check_book();//查询订单
		void Save_passenger();//保存用户信息	
		//管理员模式
		int check();//能否获得超级管理员权限 
		void root_display();//管理员展示 
		void root_save();//管理员信息保存 
		void root_load();//管理员信息载入
		void root_init();//管理员初始化 
		void root_reset();//管理员清空 
		void root_add();//添加管理员
		void root_del();//删除管理员
		int root_right();//管理员权限
		void root_mode();//管理员 
};
/*
////航班类信息
void Init_flight(flightnode *&);//初始化航班
void Load_flight(flightnode *&);//载入航班
void Add_flight(flightnode *&);//添加航班
void Check_flight(flightnode *&);//查找航班
void Check_flightnum(flightnode *&);//航班号查找
void Check_seplace(flightnode *&);//起始地查找
void Check_all(flightnode *&);//浏览全部航班
void Revise_flight(flightnode *&);//修改航班信息
void Delete_flight(flightnode *&);//删除航班
void Revise_time(flightnode*&);//修改起飞抵达时间
void Revise_price(flightnode *&);//修改价格
void Save_flight(flightnode *&);//保存航班信息
///用户信息
void Init_passenger(passengernode *&);//初始化用户
void Load_passenger(passengernode *&);//载入用户信息
void Book(flightnode *&, passengernode *&);//定票
void Qbook(flightnode *&, passengernode *&);//退票
void Check_book(passengernode *&);//查询订单
void Save_passenger(passengernode *&);//保存用户信息
*/
/*******************
* 功能描述：初始化航班
* 输入参数： 无
* 输出参数： 无
* 返回值： void
* 其它说明：无
********************/
void Airline::Init_flight()//初始化航班
{
	flightnode* h = (flightnode *)malloc(sizeof(flightnode));
	head_of_flight = tail_of_flight = h;
	h -> next = NULL;
}
/*******************
* 功能描述：载入航班信息
* 输入参数： 载入FlightList.dat信息到链表
* 输出参数： 无
* 返回值： void
* 其它说明：无
********************/
void Airline::Load_flight()//载入航班
{
	flightnode *s;
	s = (flightnode *)malloc(sizeof(flightnode));
	ifstream infile("FlightList.dat", ios::in);//将文件载入 
	if (!infile)
	{
		cerr << "                  信息错误。";//如果文件名错误的话，填写信息错误 
		return;
	}
	while (1)//读入相关的信息 
	{
		infile >> s -> flight_num >> s -> plane_num >> s -> date >> s -> time >> s -> start_place >> s -> end_place >> s -> price >> s -> left >> s -> now_seat_num;
		if (!infile.eof())
		{
			tail_of_flight -> next = s;//不断更新尾结点和中间节点 
			tail_of_flight = s;//不断更新尾结点和中间节点 
			s = (flightnode *)malloc(sizeof(flightnode));//申请一个新的指针空间 
		}
		else
			break;
	}
	tail_of_flight -> next = NULL;//最终让尾指针指向NULL 
	free(s);//将s指针的空间释放 
}
/*******************
* 功能描述：添加航班
* 输入参数： 航班的相关信息
* 输出参数： 添加成功或者选择继续添加
* 返回值： void
* 其它说明：无
********************/
void Airline::Add_flight()//添加航班
{
	char mark = 'y';
	while (mark == 'y')
	{
		flightnode* s = (flightnode *)malloc(sizeof(flightnode));//新的航班生命节点空间 
		cout << "                  请输入航班号：";
		cin >> s -> flight_num;
		cout << "                  请输入飞机号：";
		cin >> s -> plane_num;
		cout << "                  请输入日期：";
		cin >> s -> date;  
		cout << "                  请输入起飞时间：";
		cin >> s -> time;
		cout << "                  请输入出发地:";
		cin >> s -> start_place;
		cout << "                  请输入目的地：";
		cin >> s -> end_place;
		cout << "                  请输入价格：";
		cin >> s -> price;
		cout << "                  请输入余票：";
		cin >> s -> left;
		s -> now_seat_num = 0;//当前的座次号 
		tail_of_flight -> next = s;//更新中间节点 
		tail_of_flight = s;//更新尾结点 
		cout << "                  添加成功！" << endl;
		cout << "                  是否继续添加？（是“y”/否“n”)：";
		cin >> mark;//判断是否需要继续添加 
		cout << endl;
	}
	tail_of_flight -> next = NULL;//最后让尾节点指向NULL，方便判断终止条件 
}
/*******************
* 功能描述：查找航班
* 输入参数： 选择查找方式
* 输出参数： 进入相关函数进行查找功能
* 返回值： void
* 其它说明：无
********************/
void Airline::Check_flight()//查找航班
{
	system("cls");
	int i;
	cout << "                  ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅ " << endl;
	cout << "                            ┇    ≡ 查找方式 ≡    ┇ " << endl;
	cout << "                 ┇                                        ┇ " << endl;
	cout << "                            ┇    1.航班号查找      ┇ " << endl;
	cout << "                 ┇                                        ┇ " << endl;
	cout << "                            ┇    2.起始地查找      ┇ " << endl;
	cout << "                 ┇                                        ┇ " << endl;
	cout << "                            ┇     3.终点查找       ┇ " << endl;
	cout << "                 ┇                                        ┇ " << endl;
	cout << "                            ┇   4.浏览全部航班     ┇ " << endl;
	cout << "                 ┇                                        ┇ " << endl;
	cout << "                  ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅ " << endl;
	cout << "                  请输入查找方式：";
	cin >> i;
	if (i == 1)
		Check_flightnum();//通过航班号查找 
	else if (i == 2)
		Check_seplace();//通过起始地查找 
	else if(i == 3)
		Check_ed();//终点查找 
	else if (i == 4)
		Check_all();//浏览全部航班 
}
/*******************
* 功能描述：航班号查找
* 输入参数： 航班号
* 输出参数： 航班的相关信息
* 返回值： void
* 其它说明：无
********************/
void Airline::Check_flightnum()//航班号查找
{
 
	char flightnum[10];
	flightnode *p = head_of_flight -> next;//定义p为头节点的下一个节点，这样的话就是第一个数据 
	cout << setw(32) << "请输入航班号：";
	cin >> flightnum;//读取航班号 
	cout << setw(25) << "航班号" << setw(12) << "飞机号" << setw(12) << "日期" << setw(12) << "起飞时间" << setw(12) << "出发地" << setw(12) << "目的地" << setw(12) << "价格" << setw(12) << "余票" << endl;
	while (p != NULL)//如果p没有到达终点 
	{
		if (strcmp(p->flight_num, flightnum) == 0)//看能否匹配航班号 
		{
			cout << setw(25) << p -> flight_num << setw(12) << p -> plane_num << setw(12) << p -> date << setw(12) << p -> time << setw(12) << p -> start_place << setw(12) << p -> end_place << setw(12) << p->price << setw(12) << p->left << endl;
			cout << "                  ";//缩进处理 
			system("pause");
			return;
		}
		else
			p = p -> next;//否则就继续往下找 
	}
	cout << setw(32) << "未查到任何信息。";//处理缩进 
	system("pause");
}
/*******************
* 功能描述：起始地查找
* 输入参数： 起始地
* 输出参数： 航班的相关信息
* 返回值： void
* 其它说明：无
********************/
void Airline::Check_seplace()//起始地查找
{
	char start_place[20], end_place[20];//起始地的字符串 
	cout << "                  请输入出发地：";
	cin >> start_place;//输入起点 
	cout << "                  请输入目的地：";
	cin >> end_place;//输入终点 
	flightnode *p = head_of_flight -> next;//p为头指针的下一个指针，即第一个存放数据的指针 
	cout << setw(25) << "航班号" << setw(12) << "飞机号" << setw(12) << "日期" << setw(12) <<  "起飞日期" << setw(12) << "出发地" << setw(12) << "目的地" << setw(12) << "价格" << setw(12) << "余票" << endl;
	int flag = 0;
	while (p != NULL)//如果没有将所有的航班遍历完 
	{
		if (strcmp(p -> start_place, start_place) == 0 && strcmp(p -> end_place, end_place) == 0)//看起点和终点能否分别匹配 
		{
			flag = 1;//标记为1 
			cout << setw(25) << p -> flight_num << setw(12) << p -> plane_num << setw(12) << p -> date << setw(12) << p -> time << setw(12) << p->start_place << setw(12) << p->end_place << setw(12) << p->price << setw(12) << p->left << endl;
		}
		p = p -> next;
	}
	if(!flag)
	cout << setw(32) << "未查到任何信息" << endl;//如果没有被标记的话，就输出 
	cout << setw(32);//缩进 
	system("pause");
}
/*******************
* 功能描述：根据目的地查询航班
* 输入参数： 无 
* 输出参数： 输出航班的相关信息 
* 返回值： void 
* 其它说明：无
********************/
void Airline::Check_ed()
{
	char end_place[20];//终点站的字符串名字 
	cout << "                  请输入目的地：";
	cin >> end_place;//读入终点站 
	cout << setw(25) << "航班号" << setw(12) << "飞机号" << setw(12) << "日期" << setw(12) << "起飞日期" << setw(12) << "出发地" << setw(12) << "目的地" << setw(12) << "价格" << setw(12) << "余票" << endl;
	flightnode *p = head_of_flight -> next;//航班头结点的下一个节点 
	int flag = 0;//判断是否能查找到相关信息 
	while (p != NULL)
	{
		if (strcmp(p -> end_place, end_place) == 0)//如果能够匹配的话 
		{
			cout << setw(25) << p -> flight_num << setw(12) << p -> plane_num << setw(12) << p -> date << setw(12) << p -> time << setw(12) << p->start_place << setw(12) << p->end_place << setw(12) << p->price << setw(12) << p->left << endl;
			flag = 1;//认为能找到对应的航班 
		}
		p = p -> next;//继续往下找 
	}
	if(!flag) 	cout << setw(32) << "未查到任何信息" << endl;//如果查找不到任何信息的话 
	cout << setw(32);//处理缩进 
	system("pause");
}
/*******************
* 功能描述：浏览全部航班
* 输入参数： 无 
* 输出参数： 航班的相关信息
* 返回值： void
* 其它说明：无
********************/
void Airline::Check_all()//浏览全部航班
{
 
	flightnode *p = head_of_flight -> next;//p节点的下一个节点 
	cout << setw(25) << "航班号" << setw(12) << "飞机号" << setw(12) << "日期" << setw(12) <<  "起飞日期" << setw(12) << "出发地" << setw(12) << "目的地" << setw(12) << "价格" << setw(12) << "余票" << endl;
	while (p != NULL)//如果还没到尾结点 
	{
		cout << setw(25) << p -> flight_num << setw(12) << p -> plane_num << setw(12) << p -> date << setw(12) << p -> time << setw(12) << p -> start_place << setw(12) << p->end_place << setw(12) << p->price << setw(12) << p->left << endl;
		p = p -> next;//继续往后找 
	}
}
/*******************
* 功能描述：修改航班信息
* 输入参数：无 
* 输出参数： 调用相关函数进行实现
* 返回值： void
* 其它说明：无
********************/
void Airline::Revise_flight()//修改航班信息
{
	flightnode *f = head_of_flight -> next;//首节点的下一个节点，第一个存有数据的指针节点 
	int i;
	cout << "                  ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅ " << endl;
	cout << "                            ┇    ≡ 修改方式 ≡    ┇ " << endl;
	cout << "                 ┇                                        ┇ " << endl;
	cout << "                            ┇    1.删除航班       ┇ " << endl;
	cout << "                 ┇                                        ┇ " << endl;
	cout << "                            ┇    2.添加航班        ┇ " << endl;
	cout << "                 ┇                                        ┇ " << endl;
	cout << "                            ┇    3.修改起飞时间    ┇ " << endl;
	cout << "                 ┇                                        ┇ " << endl;
	cout << "                            ┇    4.修改航班价格    ┇ " << endl;
	cout << "                 ┇                                        ┇ " << endl;
	cout << "                            ┇       5.返回         ┇ " << endl;
	cout << "                 ┇                                        ┇ " << endl;
	cout << "                  ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅ " << endl;
	cout << "                  请输入查找方式：";
	cin >> i;
	if (i == 1)
		Delete_flight();//删除航班 
	else if (i == 2)
		Add_flight();//添加航班 
	else if(i == 3) 
		Revise_time();//修改起飞时间 
	else if (i == 4)
		Revise_price();//修改航班价格 
	else if (i == 5)//否则返回 
		return;
}
/*******************
* 功能描述：删除航班
* 输入参数：航班号
* 输出参数： 删除成功
* 返回值： void
* 其它说明：无
********************/
void Airline::Delete_flight()//删除航班
{
	flightnode *p = head_of_flight -> next, *q = head_of_flight;//q用来代表当前节点的前一个节点 
	char flightnum[10];//航班号 
	cout << "                  请输入您想要修改的航班号：";//输入想要修改的航班号 
	cin >> flightnum;
	while (p != NULL)//从前到后找到这个 
	{
		if (strcmp(p -> flight_num, flightnum) == 0)//匹配航班号 
		{
			if(p -> next == NULL)//如果尾结点是最后一个节点 
			{
				tail_of_flight = q;//那么就将尾结点往前移一个 
				q -> next = NULL;//尾结点的下一个节点为NULL 
			}
			else
			{
				q -> next = p -> next;//更新当前节点的前一个节点 
			}
			vector<passengernode *> v;
			passengernode *ptr1 = head_of_passenger -> next;
			passengernode *ptr2 = head_of_passenger;
			for(; ptr1 != NULL;)//删除这个航班对应的所有乘客信息 
			{
				if(strcmp(ptr1 -> flight_num, flightnum) == 0)//如果航班号能够匹配 
				{
					if(ptr1 -> next == NULL)//航班节点的尾结点 
					{
						tail_of_passenger = ptr2;//更新乘客节点的尾结点 
						ptr2 -> next = NULL;//节点的下一个节点为NULL 
					}
					else
					{
						ptr2 -> next = ptr1 -> next;//更新前一个节点的下一个节点为当前节点的下一个节点 
					}
					v.push_back(ptr1);//放入动态数组当中 
					ptr1 = ptr2 -> next;//继续往下走 
				}
				else
				{
					ptr1 = ptr1 -> next;//否则两个节点都往后走 
					ptr2 = ptr2 -> next;//继续遍历节点 
				}
			}
			for(auto ptr : v)//枚举所有的指针节点 
			{
				free(ptr);//释放内存空间 
			}
			free(p);//释放当前节点的空间 
			cout << "                  删除成功！"; 
			return;
		}
		q = q -> next;//同时往后走 
		p = q -> next;//同时往后走 
	}
}
/*******************
* 功能描述：修改起飞抵达时间
* 输入参数：航班号，新的航班号
* 输出参数： 修改成功
* 返回值： void
* 其它说明：无
********************/
void Airline::Revise_time()//修改起飞抵达时间
{
	char flightnum[10];
	flightnode *p = head_of_flight -> next;//航班头节点的下一个节点 
	cout << "                  请输入您想要修改的航班号：";
	cin >> flightnum;//航班号 
	while (p != NULL)//如果p节点不是尾结点 
	{
		if (strcmp(p -> flight_num, flightnum) == 0)//如果能够匹配航班号 
		{
			cout << "                  请输入新的起飞时间：";
			cin >> p -> time;
			cout << "                  修改成功！";
			return;
		}
		p = p -> next;//向后遍历节点 
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
void Airline::Revise_price()//修改价格
{
	char flightnum[10];
	flightnode *p = head_of_flight -> next;//p节点是头结点的下一个节点 
	cout << "                  请输入您想要修改的航班号：";
	cin >> flightnum;//读入航班号 
	while (p != NULL)//如果p指针不是尾指针的话 
	{
		if (strcmp(p -> flight_num, flightnum) == 0)//flight_num和flightnum能够对应起来 
		{
			cout << "                  输入新的价格：";
			cin >> p -> price;
			cout << "                  修改成功！	";
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
void Airline::Save_flight()//保存航班信息
{
	flightnode *f = head_of_flight -> next;//f为头结点的下一个节点 
	ofstream outfile("FlightList.dat", ios::trunc);//倒入节点的相关信息 
	if (!outfile)//如果打开失败的话 
	{
		cerr << "                  存储失败！";//输出存储失败 
		return;
	}
	while (f != NULL)//如果f节点不是尾结点的话 
	{
		outfile << f -> flight_num << " " << f -> plane_num << " " << f -> date << " " << f -> time << " " << f -> start_place << " " << f -> end_place << " " << f -> price << " " << f -> left << " " << f -> now_seat_num << endl;
		f = f -> next;//更新f节点的下一个节点 
	}
	outfile.close();//关闭输出文件 
}
/*******************
* 功能描述：初始化用户
* 输入参数： 无
* 输出参数： 无
* 返回值： void
* 其它说明：无
********************/
void Airline::Init_passenger()//初始化用户
{
	passengernode* c = (passengernode *)malloc(sizeof(passengernode));//新的节点声明 
	head_of_passenger = tail_of_passenger = c;//头结点等于尾结点等于c 
	c -> next = NULL;//更新节点的下一个节点为NULL 
}
/********************
* 功能描述：用户信息展示
* 输入参数：无
* 输出参数：无
* 其他说明：无 
********************/ 
void Airline::passenger_display()//用户信息展示 
{
	passengernode *p = head_of_passenger -> next;//p节点为头结点的下一个节点 
	cout << setw(25) << "预约状态？" << setw(12) << "乘客姓名" << setw(12) << "乘客ID" << setw(12) << "乘坐航班号" << setw(12) << "座次" << setw(12) << "航班时间" << setw(12) << "始发点" << setw(12) << "终点" << setw(12) << "票价" << endl; 
	for(p; p != NULL; p = p -> next)//遍历链表中的节点 
	{
		cout << setw(25) << p -> full << setw(12) << p -> name << setw(12) << p -> ID_num << setw(12) << p -> flight_num << setw(12) << p -> seat_num << setw(12) << p -> time << setw(12) << p -> start_place << setw(12) << p -> end_place << setw(12) << p -> price << endl;				
	}
	return;//输出后返回即可 
} 
/*******************
* 功能描述：载入用户信息
* 输入参数： 载入PassengerList.dat信息到链表
* 输出参数： 无
* 返回值： void
* 其它说明：无
********************/
void Airline::Load_passenger()//载入用户信息
{
	passengernode *s;//定义这个乘客节点s 
	s = (passengernode *)malloc(sizeof(passengernode));//为新的节点申请命名空间 
	ifstream infile("PassengerList.dat", ios::in);//载入这个信息 
	if (!infile)//如果读取不到这个文件的话 
	{
		cerr << "                  信息错误。";//认为信息错误 
		return;
	}
	while (1)
	{
		infile >> s -> name >> s -> ID_num >> s -> flight_num >> s -> seat_num >> s -> time >> s -> start_place >> s -> end_place >> s -> price;
		if (!infile.eof())//读入相关的数据 
		{
			tail_of_passenger -> next = s;//乘客节点的下一个节点为s 
			tail_of_passenger = s;//更新尾结点 
			s = (passengernode *)malloc(sizeof(passengernode));//声明一个新的节点 
		}
		else
			break;
	}
	tail_of_passenger -> next = NULL;//节点的后一个节点为NULL
	free(s);//释放这个节点 
}
/*******************
* 功能描述：航班信息
* 输入参数：passenger的相关信息
			flight的相关信息
* 输出参数： 购票成功 or 失败
* 返回值： void
* 其它说明：如果余票不足还可以预定，如果有多余的票即可瞬间购买
********************/
void Airline::Book()//订票
{
	char start_place[20], end_place[20], flightnum[10];//航班信息
	flightnode *p = head_of_flight -> next, *q = head_of_flight -> next;//两个节点 
	passengernode *s;//客户节点 
	char mark, check = '1';//界面是否重复展示 
	s = (passengernode *)malloc(sizeof(passengernode));//新的乘客节点 
	cout << "                  请输入您的姓名："; 
	cin >> s -> name;
	cout << "                  请输入您的证件号："; 
	cin >> s -> ID_num;
	cout << "                  请输入出发地:";
	cin >> start_place;
	cout << "                  请输入目的地:";
	cin >> end_place;
	cout << setw(25) << "航班号" << setw(12) << "起飞日期" << setw(12) << "出发地" << setw(12) << "目的地" << setw(12) << "价格" << setw(12) << "余票" << endl;
	while (p != NULL)//如果不是终点 
	{
		if (strcmp(p -> start_place, start_place) == 0 && strcmp(p -> end_place, end_place) == 0)
		{
			cout << setw(25) << p -> flight_num << setw(12) << p -> time << setw(12) << p -> start_place << setw(12) << p->end_place << setw(12) << p->price << setw(12) << p->left << endl;
			check = '0';//说明找到了 
		}
		p = p -> next;
	}
	if (check == '1')//否则说明没有找到qaq 
	{
		cout << "                  没有相关的航班，";
		system("pause");
		cout << "                  请问是否需要查看其他能够到达同一目的地的航班(是 y / 否 n)";
		cin >> mark;//如果继续添加的话 
		if(mark == 'y')
		{
			p = head_of_flight -> next;//头结点的下一个节点 
			cout << setw(25) << "航班号" << setw(12) << "起飞日期" << setw(12) << "出发地" << setw(12) << "目的地" << setw(12) << "价格" << setw(12) << "余票" << endl;
			while(p != NULL)//指针不等于NULL 
			{
				if(strcmp(p -> end_place, end_place) == 0)//匹配一下终点站 
				{
					cout << setw(25) << p -> flight_num << setw(12) << p -> time << setw(12) << p -> start_place << setw(12) << p -> end_place << setw(12) << p -> price << setw(12) << p -> left << endl;
				}
				p = p -> next;//向后遍历节点 
			}
			cout << "                  ";//输出缩进 
			system("pause");
			return;
		}
		else
		return;//返回节点 
	}
	cout << "                  请输入您想要购买的航班号：";
	cin >> flightnum;//航班号 
	puts("");
	while (q != NULL)//q不是NULL节点 
	{
		if (strcmp(q -> flight_num, flightnum) == 0 && strcmp(q -> start_place, start_place) == 0 && strcmp(q->end_place, end_place) == 0)//匹配起始点是否相同 
		{
			if (q -> left == 0)//如果余票为0了 
			{
				cout << "                  余票不足，请选择是否预约（是 y / 否 n）";//输出余票不足 
				cin >> mark;//读入指令 
				if (mark == 'y')//如果指令为y的话 
				{
					s -> price = q -> price;//价格更新 
					s -> seat_num = 0;//座次号更新 
					s -> full = 1;//表示在预约状态 
					strcpy(s -> start_place, start_place);//复制起点 
					strcpy(s -> end_place, end_place);//复制终点 
					strcpy(s -> time, q -> time);//复制时间 
					strcpy(s -> flight_num, flightnum);//复制航班号 
					cout << "                  预约成功！" << endl; 
					tail_of_passenger -> next = s;//乘客的下一个节点为s 
					tail_of_passenger = s;//乘客节点更新为s 
					tail_of_passenger -> next = NULL;//乘客节点的尾结点为 
					cout << "                  ";
					system("pause");//系统停止一会 
					return;
				}
				else
					return;
			}
			/*
				char name[30];//名字
				char ID_num[30];//证件号
				char flight_num[10];//航班号 
				char time[20];//起飞时间
				char start_place[20];//出发地
				char end_place[20];//目的地
				float price;//价格
				int full = 0;//是否处于候补状态 
				int seat_num;//座次号
			*/
			strcpy(s -> flight_num, flightnum);//复制航班号 
			strcpy(s -> start_place, start_place);//复制起始地点 
			strcpy(s -> end_place, end_place);//复制终止地点 
			strcpy(s -> time, q->time);//复制时间 
			s -> full = 0; //处于订票状态 
			s -> price = q -> price;//价格更新 
			s -> seat_num = q -> now_seat_num + 1;//座次号更新 
			tail_of_passenger -> next = s;//更新尾节点 
			tail_of_passenger = s; //乘客的尾结点 
			tail_of_passenger -> next = NULL;//最后一个节点的next为NULL 
			//购票成功
			cout << "                  购票成功！" << endl; 
			q -> left --;//余票减一 
			q -> now_seat_num ++;//当前的座次号+1 
			cout << "                  ";
			system("pause");
			return;
		}
		else
			q = q -> next;
	}
	cout << "                  航班号填入错误\n";
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
void Airline::Qbook()//退票
{
	char name[30];
	char ID_num[30];
	flightnode *f = head_of_flight -> next;//退票系统 
	passengernode *p = head_of_passenger -> next, *q = head_of_passenger, *t = head_of_passenger -> next;
	cout << "                  请输入您的姓名：";
	cin >> name;//读入姓名 
	puts("");
	cout << "                  请输入您的证件号：";
	cin >> ID_num;//读入乘客的身份证号码 
	while (p != NULL)
	{
		if (strcmp(p -> name, name) == 0 && strcmp(p -> ID_num, ID_num) == 0)//姓名和身份证号匹配 
		{
			while (f != NULL)//如果没到终点的话 
			{
				if (strcmp(p -> flight_num, f -> flight_num) == 0)//航班号匹配 
				{
					f -> left ++;//余量+1 
					f -> now_seat_num --;//当前座次号减一 
					while (t != NULL)
					{
						if (strcmp(t -> flight_num, p -> flight_num) == 0 && t -> full == 1)
						{
							strcpy(t -> start_place, p -> start_place);//复制起始点 
							strcpy(t -> end_place, p -> end_place);//复制终点 
							strcpy(t -> time, p -> time);//复制时间 
							t -> price = p -> price;
							t -> full = 0;//是否处于预约状态 
							t -> seat_num = f -> now_seat_num + 1;//座次号更新 
							f -> left --;//余票量减一 
							break;
						}
						t = t -> next;
					}
					break;
				}
				f = f -> next;
			}
			if(p == tail_of_passenger)
			{
				tail_of_passenger = q;
				tail_of_passenger -> next = NULL;
			}
			else
			{
				q -> next = p -> next;
			}
			for(passengernode *ptr = q -> next; ptr != NULL; ptr = ptr -> next)
			{
				if(strcmp(ptr -> flight_num, p -> flight_num) == 0 && ptr -> full == 0)
				{
					ptr -> seat_num --;//把对应该航班号的所有处于不是预约状态的座次号更新 
				}
			}
			free(p);//释放该节点的内存 
			cout << "                  退票成功！";
			return;
		}
		q = q -> next;
		p = q -> next;
	}
}
/*******************
* 功能描述：查询订票
* 输入参数：passenger的相关信息
* 输出参数： 所查用户订票的信息
* 返回值： void
* 其它说明：
********************/
void Airline::Check_book()//查询订票
{
	char name[30];
	char ID_num[30];
	passengernode *p = head_of_passenger -> next;//头结点的下一个节点 
	passengernode *q = head_of_passenger -> next;
	cout << "                  请输入您的姓名：";
	cin >> name;
	cout << "                  请输入您的证件号：";
	cin >> ID_num;
	cout << setw(25) << "姓名" << setw(12) << "航班号" << setw(12) << "座次" << setw(12) << "起飞日期" << setw(12) << "出发地" << setw(12) << "目的地" << setw(12) << "价格" << setw(12) << endl;
	int rank = 0;//当前的为此 
	while (p != NULL)
	{
		if (strcmp(p -> name, name) == 0 && strcmp(p -> ID_num, ID_num) == 0)
		{
			if(p -> full)
			{
				for(q; q != NULL; q = q -> next)
				{
					if(q -> full && q -> flight_num == p -> flight_num)
					{
						rank ++;//如果处于预约状态那么rank++ 
					}
				}
				cout << "                  目前该乘客正处于预约状态，排在第" << rank + 1 << "位\n";
			}
			else cout << "                  目前乘客已成功订票，乘客信息如下所示\n"; 
			cout << setw(25) << p -> name << setw(12) << p -> flight_num << setw(12) << p -> seat_num << setw(12) << p->time << setw(12) << p->start_place << setw(12) << p->end_place << setw(12) << p->price << setw(12) << endl;
			cout << "                  ";
			system("pause");
			return;
		}
		else
			p = p -> next;//节点继续往下走啊 
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
void Airline::Save_passenger()//保存用户信息
{
	passengernode *p = head_of_passenger -> next;//头结点往后走 
	ofstream outfile("PassengerList.dat", ios::trunc);//乘客信息 
	if (!outfile)
	{
		cerr << "                  存储失败！";
		return;
	}
	while (p != NULL)//节点不是最后一个节点的话 
	{
		outfile << p -> name << " " << p -> ID_num << " " << p -> flight_num << " " << p -> seat_num << " " << p -> time << " " << p->start_place << " " << p->end_place << " " << p->price << endl;
		p = p -> next;//读出这个节点的下一个节点 
	}
	outfile.close();//关闭文件 
}
void Airline::root_init()
{
	administrator *s = (administrator *)malloc(sizeof(administrator));//初始化管理员 
	head_of_root = tail_of_root = s;//定义一个新的节点后开始更新 
	s -> next = NULL;
}
int Airline::check()
{
	administrator *ptr = (administrator *)malloc(sizeof(administrator));//申请一个新的指针 
	cout << endl << "                  请输入超级管理员（root）用户名：" ;
	cin >> ptr -> name;
	if(strcmp(ptr -> name, root_name) == 1) //看名字是否能够匹配 
	{ 
		cout << endl << "                  用户名错误\n";
		return 0;
	}
	printf("\n"); 
	cout << endl << "                  请输入密码:";
	cin >> ptr -> password;//读入密码即可 
	if(strcmp(ptr -> password, root_password) == 1)//密码能否匹配 
	{
		cout << endl << "                  密码错误\n";
		return 0;
	}
	printf("\n");
	return 1;			
}
/*******************
* 功能描述：管理员信息清零 
* 输入参数： 载入FlightList.dat信息到链表
* 输出参数： 无
* 返回值： void
* 其它说明：无
********************/
void Airline::root_reset()
{
	if(tail_of_root == head_of_root) return;//一次删除所有的管理员信息 
	administrator* ptr = tail_of_root -> pre;
	administrator* s;
	for(ptr; ptr != head_of_root; ptr = ptr -> pre)
	{
		s = ptr -> next;
		free(s);//释放这个节点的内存 
	}
	if(head_of_root -> next != NULL)
	{
		free(head_of_root -> next);//把初始节点的内存释放 
		head_of_root -> next = NULL;
	}
}
/*******************
* 功能描述：管理员添加 
* 输入参数： 无 
* 输出参数： 无
* 返回值： void
* 其它说明：无
********************/
void Airline::root_add()
{
	while(1)
	{
		cout << "                  请输入您要添加的用户名:";//输入要添加的用户名 
		administrator* s = (administrator *)malloc(sizeof(administrator));
		cin >> s -> name;//读入用户名的信息 
		cout << "                  密码为：";
		cin >> s -> password;//读入用户名的密码 
		puts("");
		tail_of_root -> next = s;//更新尾结点 
		s -> pre = tail_of_root;//更新前置节点 
		tail_of_root = s;//更新尾结点 
		cout << "                  添加成功，是否继续添加(是/y；否/n):";
		char p;
		cin >> p;//读入操作 
		if(p == 'n') break;
	}
	tail_of_root -> next = NULL;//更新尾结点的下一个节点为NULL 
}
/*
void Airline::Add_flight()//添加航班
{
	char mark = 'y';
	while (mark == 'y')
	{
		flightnode* s = (flightnode *)malloc(sizeof(flightnode));
		cout << "                  请输入航班号：";
		cin >> s -> flight_num;
		cout << "                  请输入起飞时间：";
		cin >> s -> time;
		cout << "                  请输入出发地:";
		cin >> s -> start_place;
		cout << "                  请输入目的地：";
		cin >> s -> end_place;
		cout << "                  请输入价格：";
		cin >> s -> price;
		cout << "                  请输入余票：";
		cin >> s -> left;
		tail_of_flight -> next = s;
		tail_of_flight = s;
		cout << "                  添加成功！" << endl;
		cout << "                  是否继续添加？（是“y”/否“n”）：";
		cin >> mark;
	}
	tail_of_flight -> next = NULL;
}*/
/*******************
* 功能描述：管理员删除 
* 输入参数： 无 
* 输出参数： 无
* 返回值： void
* 其它说明：无
********************/
void Airline::root_del()//删除管理员
{
	administrator *p = (administrator *)malloc(sizeof(administrator)); //生命一个新的节点命名空间 
	cout << "                  请输入管理员用户名:";
	cin >> p -> name;//读入节点的名字 
	puts("");
	cout << "                  正在删除...........................\n"; //操作 
	for(administrator *ptr = head_of_root -> next; ptr != NULL; ptr = ptr -> next)//遍历管理员链表中的每个管理员 
	{
		if(strcmp(ptr -> name, p -> name) == 0)//如果能够匹配名字 
		{
			if(ptr -> next == NULL)//如果下一个节点为NULL 
			{
				tail_of_root = ptr -> pre;//就第一种更新方式 
				tail_of_root -> next = NULL;//尾结点的下一个节点为NULL 
				free(ptr);//释放这个节点的空间 
				break;
			}
			else
			{
				ptr -> pre -> next = ptr -> next;//更新这个节点前置节点的后继节点 
				ptr -> next -> pre = ptr -> pre;//更新后继节点的前驱节点 
				free(ptr);//释放这个节点 
				break;
			}
		}
	}
	cout << "                  删除成功\n";
} 
void Airline::root_load()//管理员信息载入
{
	administrator *s;//定义这个节点 
	s = (administrator *)malloc(sizeof(administrator));//给这个节点分配命名空间 
	ifstream infile("root.dat", ios::in);//载入管理员的相关信息 
	if (!infile)//如果载入失败的话 
	{
		cerr << "                  信息错误。";
		return;
	}
	while (1)
	{
		infile >> s -> name >> s -> password;//读入用户名和密码 
		if (!infile.eof())//如果读入失败的话 
		{
			tail_of_root -> next = s;//尾结点的下一个节点更新为s 
			s -> pre = tail_of_root;//s的前驱节点更新为尾结点 
			tail_of_root = s;//尾结点更新为s 
			s = (administrator *)malloc(sizeof(administrator));//给s分配内存空间 
		}
		else
			break;//否则就载入结束了 
	}
	tail_of_root -> next = NULL;//尾结点的下一个节点为NULL 
	free(s);			//释放s这个节点 
} 
void Airline::root_save()//管理员信息保存 
{
	administrator *f = head_of_root -> next;//定义f为头结点的下一个节点 
	ofstream outfile("root.dat", ios::trunc);//保存的文件为root.dat 
	if (!outfile)//如果打不开对应的文件 
	{
		cerr << "                  存储失败！";//输出存储失败 
		return;
	}
	while (f != NULL)//如果f不是NULL的话 
	{
		outfile << f -> name << " " << f -> password << endl; //输出对应的所有信息 
		f = f -> next;//移动到下一个指针 
	}
	outfile.close();//输出文件结束 
}
int Airline::root_right()//管理员权限
{
	int flag = 0;
	administrator *p = (administrator *)malloc(sizeof(administrator)); //声明节点p，分配命名空间 
	cout << "                  请输入用户名："; //读入用户名 
	cin >> p -> name;//读入对应的用户名 
	puts("");
	for(administrator *ptr = head_of_root -> next; ptr != NULL; ptr = ptr -> next)//遍历所有的管理员信息 
	{
		if(strcmp(ptr -> name , p -> name) == 0)//如果能够匹配相关的信息的话 
		{
			flag = 1;//让flag=1认为找到节点了 
			cout << "                  请输入密码：";
			cin >> p -> password;//读入密码 
			if(strcmp(ptr -> password, p -> password) == 0)
			{
				flag = 2;//如果用户名和密码都能够匹配的话 
				cout << "                  管理员权限获取成功！\n";
				break;//获得管理员权限 
			}
		}
	} 
	if(flag == 0)//如果用户名错误的话 
	{
		cout << endl;
		cout << "                  用户名错误\n";
		return 0;
	}
	else if(flag == 1)//如果密码错误的话 
	{
		cout << "                  密码错误\n";
		return 0;
	}
	else return 1;//否则认为获得权限 
} 
void Airline::root_mode()//管理员模式 
{
	while(1)
	{
		cout << "                  ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅ " << endl;
		cout << "                            ┇    ≡ 管理员 ≡    ┇ " << endl;
		cout << "                 ┇                                        ┇ " << endl;
		cout << "                            ┇     1.超级管理员模式       ┇ " << endl;
		cout << "                 ┇                                        ┇ " << endl;
		cout << "                            ┇     2.管理员模式           ┇ " << endl;
		cout << "                 ┇                                        ┇ " << endl;
		cout << "                            ┇     3.返回上一步           ┇ " << endl;
		cout << "                 ┇                                        ┇ " << endl;
		cout << "                  ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅ " << endl;
		cout << "                  请输入想要进行的功能：";
		int op;
		cin >> op;
		if(op == 1) 
		{
			if(check())//如果超级管理员权限获得 
			{
				while(1)//进入超级管理员模式 
				{ 
					cout << "                          超级管理员权限获取成功！\n";
					cout << "                  ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅ " << endl;
					cout << "                            ┇    ≡ 超级管理员模式 ≡    ┇ " << endl;
					cout << "                 ┇                                        ┇ " << endl;
					cout << "                            ┇     1.管理员初始化         ┇ " << endl;
					cout << "                 ┇                                        ┇ " << endl;
					cout << "                            ┇     2.添加管理员           ┇ " << endl;
					cout << "                 ┇                                        ┇ " << endl;
					cout << "                            ┇     3.删除管理员           ┇ " << endl;
					cout << "                 ┇                                        ┇ " << endl;
					cout << "                            ┇     4.录入管理员信息       ┇ " << endl;
					cout << "                 ┇                                        ┇ " << endl;
					cout << "                            ┇     5.管理员信息           ┇ " << endl;
					cout << "                 ┇                                        ┇ " << endl;
					cout << "                            ┇     6.返回上一步           ┇ " << endl;
					cout << "                 ┇                                        ┇ " << endl;
					cout << "                  ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅ " << endl;
					cout << "                  请输入想要进行的功能：";
					int op;
					cin >> op;
					if(op == 1)
					{
						root_reset();//管理员初始化 
						root_save();	//保存管理员信息 
					}				
					else if(op == 2)
					{
						root_add();	//管理员添加 
						root_save();//保存管理员信息 
					}	
					else if(op == 3)
					{
						root_del();//管理员删除 
						root_save();//保存管理员信息 
					}
					else if(op == 4)
					{
						root_load();//管理员加载信息 
						cout << "                  管理员信息录入成功\n";
					} 
					else if(op == 5)
					{
						root_display();//展示所有的管理员信息 
					}
					else if(op == 6) break;
					else printf("                             输入有误\n");
				}
			}
		}
		else if(op == 2)
		{
			if(root_right())//如果能够获得管理员权限 
			{
				while(1)//进入管理员模式 
				{
					cout << "                  ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅ " << endl;
					cout << "                            ┇    ≡ 管理员模式 ≡    ┇ " << endl;
					cout << "                 ┇                                        ┇ " << endl;
					cout << "                            ┇     1.查询顾客信息     ┇ " << endl;
					cout << "                 ┇                                        ┇ " << endl;
					cout << "                            ┇     2.返回上一步       ┇ " << endl;
					cout << "                 ┇                                        ┇ " << endl;
					cout << "                  ┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅ " << endl;
					cout << "                  输入想要进行的功能：";		
					int op;
					cin >> op;//读入op操作 
					 
					if(op == 1)
					{
						passenger_display();//顾客信息展示 
					}			
					else if(op == 2)
					{
						break;//退出 
					}
					else
					{
						cout << "                  输入错误\n";
					}
				}
			}
		}
		else
		{
			break;
		}
	}
}
void Airline::root_display()
{
	administrator *ptr = head_of_root -> next;//管理员信息展示 
	cout << setw(25) << "用户名" << setw(12) << "密码" << endl;
	for(ptr; ptr != NULL; ptr = ptr -> next)//节点从前到后遍历 
	{
		cout << setw(25) << ptr -> name << setw(12) << ptr -> password << endl; 
	} 
}
