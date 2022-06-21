/********************
* 版权所有 (C)2022, Yuxing liu。
*
* 文件名称： main.cpp
* 文件标识：无
* 内容摘要：该代码用于完成界面及选择功能
* 其它说明：无
* 当前版本： V1.0
* 作 者：刘宇星 
* 完成日期： 2022-05-10
********************/

#include <iostream>
#include <windows.h> ///改变字体颜色用
#include "head.h"
using namespace std;
int main()
{
	Airline airline;
	airline.Init_passenger();//初始用户信息
	//airline.Load_flight();
	airline.Init_flight();//初始化航班
	//airline.Load_passenger();
	airline.root_init();//管理员初始化 
	airline.root_load();
	while (1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | ///字体颜色
			FOREGROUND_BLUE | FOREGROUND_GREEN);
		cout << "\n";
		cout << "                       ╬╬ 飞 机 订 票 系 统 ╬╬ " << endl << endl;
		cout << "                 ╔┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅╗ " << endl;
		cout << "                 ┇                                        ┇ " << endl;
		cout << "                            ┇    ≡ 主菜单 ≡    ┇ " << endl;
		cout << "                 ┇                                        ┇ " << endl;
		cout << "                            ┇   1.录入航班信息   ┇ " << endl;
		cout << "                 ┇                                        ┇ " << endl;
		cout << "                            ┇   2.录入乘客信息   ┇ " << endl;
		cout << "                 ┇                                        ┇ " << endl;
		cout << "                            ┇     3.查询航班     ┇ " << endl;
		cout << "                 ┇                                        ┇ " << endl;
		cout << "                            ┇   4.订票 5.退票    ┇ " << endl;
		cout << "                 ┇                                        ┇ " << endl;
		cout << "                            ┇     6.查询订单     ┇ " << endl;
		cout << "                 ┇                                        ┇ " << endl;
		cout << "                            ┇   7.修改航班信息   ┇ " << endl;
		cout << "                 ┇                                        ┇ " << endl;
		cout << "                            ┇   8.管理员模式     ┇ " << endl;
		cout << "                 ┇                                        ┇ " << endl;
		cout << "                            ┇    0.退出系统      ┇ " << endl;
		cout << "                 ┇                                        ┇ " << endl;
		cout << "                 ╚┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅╝ " << endl;
		cout << "                  请输入想要进行的功能：";
		int i;
		cin >> i;
		if (i == 1)
		{
			airline.Load_flight();//录入航班信息
			printf("                 恭喜您，航班信息录入成功\n"); 
		}
		else if(i == 2)
		{
			airline.Load_passenger();//录入乘客信息 
			printf("                 恭喜您，乘客信息录入成功\n");
		} 
		else if (i == 3)
		
			airline.Check_flight();//查找航班
		else if (i == 4)
		{
			airline.Book();//定票
			airline.Save_flight();//保存航班信息
			airline.Save_passenger();//保存用户信息
			printf("\n                 航班信息已自动保存\n");
			printf("\n                 用户信息已自动保存\n");
		}
		else if (i == 5)
		{
			airline.Qbook();//退票
			airline.Save_flight();//保存航班信息
			airline.Save_passenger();//保存用户信息
			printf("\n                 航班信息已自动保存\n");
			printf("\n                 用户信息已自动保存\n");
		}
		else if (i == 6)
			airline.Check_book();//查询订单
		else if (i == 7)
		{
			airline.Revise_flight();//修改航班信息
			airline.Save_flight();//保存航班信息
			printf("\n                 航班信息已自动保存\n");
		}
		else if(i == 8)
		{
			airline.root_mode();
		 } 
		else if (i == 0)
			break;
		else
		{
			cout << "                 无效数字，请重新输入！";
			system("pause");
			system("cls");
		}
	}
	return 0;
}
