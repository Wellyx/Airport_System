/********************
* ��Ȩ���� (C)2022, Yuxing liu��
*
* �ļ����ƣ� main.cpp
* �ļ���ʶ����
* ����ժҪ���ô���������ɽ��漰ѡ����
* ����˵������
* ��ǰ�汾�� V1.0
* �� �ߣ������� 
* ������ڣ� 2022-05-10
********************/

#include <iostream>
#include <windows.h> ///�ı�������ɫ��
#include "head.h"
using namespace std;
int main()
{
	Airline airline;
	airline.Init_passenger();//��ʼ�û���Ϣ
	//airline.Load_flight();
	airline.Init_flight();//��ʼ������
	//airline.Load_passenger();
	airline.root_init();//����Ա��ʼ�� 
	airline.root_load();
	while (1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | ///������ɫ
			FOREGROUND_BLUE | FOREGROUND_GREEN);
		cout << "\n";
		cout << "                       �p�p �� �� �� Ʊ ϵ ͳ �p�p " << endl << endl;
		cout << "                 �X���������������������������������������������������������������������������������[ " << endl;
		cout << "                 ��                                        �� " << endl;
		cout << "                            ��    �� ���˵� ��    �� " << endl;
		cout << "                 ��                                        �� " << endl;
		cout << "                            ��   1.¼�뺽����Ϣ   �� " << endl;
		cout << "                 ��                                        �� " << endl;
		cout << "                            ��   2.¼��˿���Ϣ   �� " << endl;
		cout << "                 ��                                        �� " << endl;
		cout << "                            ��     3.��ѯ����     �� " << endl;
		cout << "                 ��                                        �� " << endl;
		cout << "                            ��   4.��Ʊ 5.��Ʊ    �� " << endl;
		cout << "                 ��                                        �� " << endl;
		cout << "                            ��     6.��ѯ����     �� " << endl;
		cout << "                 ��                                        �� " << endl;
		cout << "                            ��   7.�޸ĺ�����Ϣ   �� " << endl;
		cout << "                 ��                                        �� " << endl;
		cout << "                            ��   8.����Աģʽ     �� " << endl;
		cout << "                 ��                                        �� " << endl;
		cout << "                            ��    0.�˳�ϵͳ      �� " << endl;
		cout << "                 ��                                        �� " << endl;
		cout << "                 �^���������������������������������������������������������������������������������a " << endl;
		cout << "                  ��������Ҫ���еĹ��ܣ�";
		int i;
		cin >> i;
		if (i == 1)
		{
			airline.Load_flight();//¼�뺽����Ϣ
			printf("                 ��ϲ����������Ϣ¼��ɹ�\n"); 
		}
		else if(i == 2)
		{
			airline.Load_passenger();//¼��˿���Ϣ 
			printf("                 ��ϲ�����˿���Ϣ¼��ɹ�\n");
		} 
		else if (i == 3)
		
			airline.Check_flight();//���Һ���
		else if (i == 4)
		{
			airline.Book();//��Ʊ
			airline.Save_flight();//���溽����Ϣ
			airline.Save_passenger();//�����û���Ϣ
			printf("\n                 ������Ϣ���Զ�����\n");
			printf("\n                 �û���Ϣ���Զ�����\n");
		}
		else if (i == 5)
		{
			airline.Qbook();//��Ʊ
			airline.Save_flight();//���溽����Ϣ
			airline.Save_passenger();//�����û���Ϣ
			printf("\n                 ������Ϣ���Զ�����\n");
			printf("\n                 �û���Ϣ���Զ�����\n");
		}
		else if (i == 6)
			airline.Check_book();//��ѯ����
		else if (i == 7)
		{
			airline.Revise_flight();//�޸ĺ�����Ϣ
			airline.Save_flight();//���溽����Ϣ
			printf("\n                 ������Ϣ���Զ�����\n");
		}
		else if(i == 8)
		{
			airline.root_mode();
		 } 
		else if (i == 0)
			break;
		else
		{
			cout << "                 ��Ч���֣����������룡";
			system("pause");
			system("cls");
		}
	}
	return 0;
}
