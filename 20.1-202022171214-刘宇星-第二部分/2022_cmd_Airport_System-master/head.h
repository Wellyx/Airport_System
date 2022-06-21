/********************
* ��Ȩ���� (C)2022, Yuxing Liu��
*
* �ļ����ƣ� head.cpp
* �ļ���ʶ����
* ����ժҪ�����庽����û�����Ϣ����ɸ�������������
* ����˵������
* ��ǰ�汾�� V1.0
* �� �ߣ������� 
* ������ڣ� 2022-05-10
********************/
#include <bits/stdc++.h>
using namespace std;
typedef struct flightnode
{
	char flight_num[10];//�����
	char plane_num[10];//�ɻ��� 
	char time[20];//���ʱ��
	char date[20];//���� 
	char start_place[20];//������
	char end_place[20];//Ŀ�ĵ�
	int left;//��Ʊ
	int now_seat_num = 0;//��ǰ�����κ� 
	float price;//�۸�
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
	char name[30];//����
	char ID_num[30];//֤����
	char flight_num[10];//����� 
	char time[20];//���ʱ��
	char start_place[20];//������
	char end_place[20];//Ŀ�ĵ�
	float price;//�۸�
	int full = 0;//�Ƿ��ں�״̬ 
	int seat_num;//���κ� 
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
		void Init_flight();//��ʼ������
		void Load_flight();//���뺽��
		void Add_flight();//��Ӻ���
		void Check_flight();//���Һ���
		void Check_flightnum();//����Ų���
		void Check_seplace();//��ʼ�ز���
		void Check_all();//���ȫ������
		void Check_ed();
		void Revise_flight();//�޸ĺ�����Ϣ
		void Delete_flight();//ɾ������
		void Revise_time();//�޸���ɵִ�ʱ��
		void Revise_price();//�޸ļ۸�
		void Save_flight();//���溽����Ϣ
		///�û���Ϣ
		void passenger_display();//�û���Ϣչʾ 
		void Init_passenger();//��ʼ���û�
		void Load_passenger();//�����û���Ϣ
		void Book();//��Ʊ
		void Qbook();//��Ʊ
		void Check_book();//��ѯ����
		void Save_passenger();//�����û���Ϣ	
		//����Աģʽ
		int check();//�ܷ��ó�������ԱȨ�� 
		void root_display();//����Աչʾ 
		void root_save();//����Ա��Ϣ���� 
		void root_load();//����Ա��Ϣ����
		void root_init();//����Ա��ʼ�� 
		void root_reset();//����Ա��� 
		void root_add();//��ӹ���Ա
		void root_del();//ɾ������Ա
		int root_right();//����ԱȨ��
		void root_mode();//����Ա 
};
/*
////��������Ϣ
void Init_flight(flightnode *&);//��ʼ������
void Load_flight(flightnode *&);//���뺽��
void Add_flight(flightnode *&);//��Ӻ���
void Check_flight(flightnode *&);//���Һ���
void Check_flightnum(flightnode *&);//����Ų���
void Check_seplace(flightnode *&);//��ʼ�ز���
void Check_all(flightnode *&);//���ȫ������
void Revise_flight(flightnode *&);//�޸ĺ�����Ϣ
void Delete_flight(flightnode *&);//ɾ������
void Revise_time(flightnode*&);//�޸���ɵִ�ʱ��
void Revise_price(flightnode *&);//�޸ļ۸�
void Save_flight(flightnode *&);//���溽����Ϣ
///�û���Ϣ
void Init_passenger(passengernode *&);//��ʼ���û�
void Load_passenger(passengernode *&);//�����û���Ϣ
void Book(flightnode *&, passengernode *&);//��Ʊ
void Qbook(flightnode *&, passengernode *&);//��Ʊ
void Check_book(passengernode *&);//��ѯ����
void Save_passenger(passengernode *&);//�����û���Ϣ
*/
/*******************
* ������������ʼ������
* ��������� ��
* ��������� ��
* ����ֵ�� void
* ����˵������
********************/
void Airline::Init_flight()//��ʼ������
{
	flightnode* h = (flightnode *)malloc(sizeof(flightnode));
	head_of_flight = tail_of_flight = h;
	h -> next = NULL;
}
/*******************
* �������������뺽����Ϣ
* ��������� ����FlightList.dat��Ϣ������
* ��������� ��
* ����ֵ�� void
* ����˵������
********************/
void Airline::Load_flight()//���뺽��
{
	flightnode *s;
	s = (flightnode *)malloc(sizeof(flightnode));
	ifstream infile("FlightList.dat", ios::in);//���ļ����� 
	if (!infile)
	{
		cerr << "                  ��Ϣ����";//����ļ�������Ļ�����д��Ϣ���� 
		return;
	}
	while (1)//������ص���Ϣ 
	{
		infile >> s -> flight_num >> s -> plane_num >> s -> date >> s -> time >> s -> start_place >> s -> end_place >> s -> price >> s -> left >> s -> now_seat_num;
		if (!infile.eof())
		{
			tail_of_flight -> next = s;//���ϸ���β�����м�ڵ� 
			tail_of_flight = s;//���ϸ���β�����м�ڵ� 
			s = (flightnode *)malloc(sizeof(flightnode));//����һ���µ�ָ��ռ� 
		}
		else
			break;
	}
	tail_of_flight -> next = NULL;//������βָ��ָ��NULL 
	free(s);//��sָ��Ŀռ��ͷ� 
}
/*******************
* ������������Ӻ���
* ��������� ����������Ϣ
* ��������� ��ӳɹ�����ѡ��������
* ����ֵ�� void
* ����˵������
********************/
void Airline::Add_flight()//��Ӻ���
{
	char mark = 'y';
	while (mark == 'y')
	{
		flightnode* s = (flightnode *)malloc(sizeof(flightnode));//�µĺ��������ڵ�ռ� 
		cout << "                  �����뺽��ţ�";
		cin >> s -> flight_num;
		cout << "                  ������ɻ��ţ�";
		cin >> s -> plane_num;
		cout << "                  ���������ڣ�";
		cin >> s -> date;  
		cout << "                  ���������ʱ�䣺";
		cin >> s -> time;
		cout << "                  �����������:";
		cin >> s -> start_place;
		cout << "                  ������Ŀ�ĵأ�";
		cin >> s -> end_place;
		cout << "                  ������۸�";
		cin >> s -> price;
		cout << "                  ��������Ʊ��";
		cin >> s -> left;
		s -> now_seat_num = 0;//��ǰ�����κ� 
		tail_of_flight -> next = s;//�����м�ڵ� 
		tail_of_flight = s;//����β��� 
		cout << "                  ��ӳɹ���" << endl;
		cout << "                  �Ƿ������ӣ����ǡ�y��/��n��)��";
		cin >> mark;//�ж��Ƿ���Ҫ������� 
		cout << endl;
	}
	tail_of_flight -> next = NULL;//�����β�ڵ�ָ��NULL�������ж���ֹ���� 
}
/*******************
* �������������Һ���
* ��������� ѡ����ҷ�ʽ
* ��������� ������غ������в��ҹ���
* ����ֵ�� void
* ����˵������
********************/
void Airline::Check_flight()//���Һ���
{
	system("cls");
	int i;
	cout << "                  �������������������������������������������������������������������������������� " << endl;
	cout << "                            ��    �� ���ҷ�ʽ ��    �� " << endl;
	cout << "                 ��                                        �� " << endl;
	cout << "                            ��    1.����Ų���      �� " << endl;
	cout << "                 ��                                        �� " << endl;
	cout << "                            ��    2.��ʼ�ز���      �� " << endl;
	cout << "                 ��                                        �� " << endl;
	cout << "                            ��     3.�յ����       �� " << endl;
	cout << "                 ��                                        �� " << endl;
	cout << "                            ��   4.���ȫ������     �� " << endl;
	cout << "                 ��                                        �� " << endl;
	cout << "                  �������������������������������������������������������������������������������� " << endl;
	cout << "                  ��������ҷ�ʽ��";
	cin >> i;
	if (i == 1)
		Check_flightnum();//ͨ������Ų��� 
	else if (i == 2)
		Check_seplace();//ͨ����ʼ�ز��� 
	else if(i == 3)
		Check_ed();//�յ���� 
	else if (i == 4)
		Check_all();//���ȫ������ 
}
/*******************
* ��������������Ų���
* ��������� �����
* ��������� ����������Ϣ
* ����ֵ�� void
* ����˵������
********************/
void Airline::Check_flightnum()//����Ų���
{
 
	char flightnum[10];
	flightnode *p = head_of_flight -> next;//����pΪͷ�ڵ����һ���ڵ㣬�����Ļ����ǵ�һ������ 
	cout << setw(32) << "�����뺽��ţ�";
	cin >> flightnum;//��ȡ����� 
	cout << setw(25) << "�����" << setw(12) << "�ɻ���" << setw(12) << "����" << setw(12) << "���ʱ��" << setw(12) << "������" << setw(12) << "Ŀ�ĵ�" << setw(12) << "�۸�" << setw(12) << "��Ʊ" << endl;
	while (p != NULL)//���pû�е����յ� 
	{
		if (strcmp(p->flight_num, flightnum) == 0)//���ܷ�ƥ�亽��� 
		{
			cout << setw(25) << p -> flight_num << setw(12) << p -> plane_num << setw(12) << p -> date << setw(12) << p -> time << setw(12) << p -> start_place << setw(12) << p -> end_place << setw(12) << p->price << setw(12) << p->left << endl;
			cout << "                  ";//�������� 
			system("pause");
			return;
		}
		else
			p = p -> next;//����ͼ��������� 
	}
	cout << setw(32) << "δ�鵽�κ���Ϣ��";//�������� 
	system("pause");
}
/*******************
* ������������ʼ�ز���
* ��������� ��ʼ��
* ��������� ����������Ϣ
* ����ֵ�� void
* ����˵������
********************/
void Airline::Check_seplace()//��ʼ�ز���
{
	char start_place[20], end_place[20];//��ʼ�ص��ַ��� 
	cout << "                  ����������أ�";
	cin >> start_place;//������� 
	cout << "                  ������Ŀ�ĵأ�";
	cin >> end_place;//�����յ� 
	flightnode *p = head_of_flight -> next;//pΪͷָ�����һ��ָ�룬����һ��������ݵ�ָ�� 
	cout << setw(25) << "�����" << setw(12) << "�ɻ���" << setw(12) << "����" << setw(12) <<  "�������" << setw(12) << "������" << setw(12) << "Ŀ�ĵ�" << setw(12) << "�۸�" << setw(12) << "��Ʊ" << endl;
	int flag = 0;
	while (p != NULL)//���û�н����еĺ�������� 
	{
		if (strcmp(p -> start_place, start_place) == 0 && strcmp(p -> end_place, end_place) == 0)//�������յ��ܷ�ֱ�ƥ�� 
		{
			flag = 1;//���Ϊ1 
			cout << setw(25) << p -> flight_num << setw(12) << p -> plane_num << setw(12) << p -> date << setw(12) << p -> time << setw(12) << p->start_place << setw(12) << p->end_place << setw(12) << p->price << setw(12) << p->left << endl;
		}
		p = p -> next;
	}
	if(!flag)
	cout << setw(32) << "δ�鵽�κ���Ϣ" << endl;//���û�б���ǵĻ�������� 
	cout << setw(32);//���� 
	system("pause");
}
/*******************
* ��������������Ŀ�ĵز�ѯ����
* ��������� �� 
* ��������� �������������Ϣ 
* ����ֵ�� void 
* ����˵������
********************/
void Airline::Check_ed()
{
	char end_place[20];//�յ�վ���ַ������� 
	cout << "                  ������Ŀ�ĵأ�";
	cin >> end_place;//�����յ�վ 
	cout << setw(25) << "�����" << setw(12) << "�ɻ���" << setw(12) << "����" << setw(12) << "�������" << setw(12) << "������" << setw(12) << "Ŀ�ĵ�" << setw(12) << "�۸�" << setw(12) << "��Ʊ" << endl;
	flightnode *p = head_of_flight -> next;//����ͷ������һ���ڵ� 
	int flag = 0;//�ж��Ƿ��ܲ��ҵ������Ϣ 
	while (p != NULL)
	{
		if (strcmp(p -> end_place, end_place) == 0)//����ܹ�ƥ��Ļ� 
		{
			cout << setw(25) << p -> flight_num << setw(12) << p -> plane_num << setw(12) << p -> date << setw(12) << p -> time << setw(12) << p->start_place << setw(12) << p->end_place << setw(12) << p->price << setw(12) << p->left << endl;
			flag = 1;//��Ϊ���ҵ���Ӧ�ĺ��� 
		}
		p = p -> next;//���������� 
	}
	if(!flag) 	cout << setw(32) << "δ�鵽�κ���Ϣ" << endl;//������Ҳ����κ���Ϣ�Ļ� 
	cout << setw(32);//�������� 
	system("pause");
}
/*******************
* �������������ȫ������
* ��������� �� 
* ��������� ����������Ϣ
* ����ֵ�� void
* ����˵������
********************/
void Airline::Check_all()//���ȫ������
{
 
	flightnode *p = head_of_flight -> next;//p�ڵ����һ���ڵ� 
	cout << setw(25) << "�����" << setw(12) << "�ɻ���" << setw(12) << "����" << setw(12) <<  "�������" << setw(12) << "������" << setw(12) << "Ŀ�ĵ�" << setw(12) << "�۸�" << setw(12) << "��Ʊ" << endl;
	while (p != NULL)//�����û��β��� 
	{
		cout << setw(25) << p -> flight_num << setw(12) << p -> plane_num << setw(12) << p -> date << setw(12) << p -> time << setw(12) << p -> start_place << setw(12) << p->end_place << setw(12) << p->price << setw(12) << p->left << endl;
		p = p -> next;//���������� 
	}
}
/*******************
* �����������޸ĺ�����Ϣ
* ����������� 
* ��������� ������غ�������ʵ��
* ����ֵ�� void
* ����˵������
********************/
void Airline::Revise_flight()//�޸ĺ�����Ϣ
{
	flightnode *f = head_of_flight -> next;//�׽ڵ����һ���ڵ㣬��һ���������ݵ�ָ��ڵ� 
	int i;
	cout << "                  �������������������������������������������������������������������������������� " << endl;
	cout << "                            ��    �� �޸ķ�ʽ ��    �� " << endl;
	cout << "                 ��                                        �� " << endl;
	cout << "                            ��    1.ɾ������       �� " << endl;
	cout << "                 ��                                        �� " << endl;
	cout << "                            ��    2.��Ӻ���        �� " << endl;
	cout << "                 ��                                        �� " << endl;
	cout << "                            ��    3.�޸����ʱ��    �� " << endl;
	cout << "                 ��                                        �� " << endl;
	cout << "                            ��    4.�޸ĺ���۸�    �� " << endl;
	cout << "                 ��                                        �� " << endl;
	cout << "                            ��       5.����         �� " << endl;
	cout << "                 ��                                        �� " << endl;
	cout << "                  �������������������������������������������������������������������������������� " << endl;
	cout << "                  ��������ҷ�ʽ��";
	cin >> i;
	if (i == 1)
		Delete_flight();//ɾ������ 
	else if (i == 2)
		Add_flight();//��Ӻ��� 
	else if(i == 3) 
		Revise_time();//�޸����ʱ�� 
	else if (i == 4)
		Revise_price();//�޸ĺ���۸� 
	else if (i == 5)//���򷵻� 
		return;
}
/*******************
* ����������ɾ������
* ��������������
* ��������� ɾ���ɹ�
* ����ֵ�� void
* ����˵������
********************/
void Airline::Delete_flight()//ɾ������
{
	flightnode *p = head_of_flight -> next, *q = head_of_flight;//q��������ǰ�ڵ��ǰһ���ڵ� 
	char flightnum[10];//����� 
	cout << "                  ����������Ҫ�޸ĵĺ���ţ�";//������Ҫ�޸ĵĺ���� 
	cin >> flightnum;
	while (p != NULL)//��ǰ�����ҵ���� 
	{
		if (strcmp(p -> flight_num, flightnum) == 0)//ƥ�亽��� 
		{
			if(p -> next == NULL)//���β��������һ���ڵ� 
			{
				tail_of_flight = q;//��ô�ͽ�β�����ǰ��һ�� 
				q -> next = NULL;//β������һ���ڵ�ΪNULL 
			}
			else
			{
				q -> next = p -> next;//���µ�ǰ�ڵ��ǰһ���ڵ� 
			}
			vector<passengernode *> v;
			passengernode *ptr1 = head_of_passenger -> next;
			passengernode *ptr2 = head_of_passenger;
			for(; ptr1 != NULL;)//ɾ����������Ӧ�����г˿���Ϣ 
			{
				if(strcmp(ptr1 -> flight_num, flightnum) == 0)//���������ܹ�ƥ�� 
				{
					if(ptr1 -> next == NULL)//����ڵ��β��� 
					{
						tail_of_passenger = ptr2;//���³˿ͽڵ��β��� 
						ptr2 -> next = NULL;//�ڵ����һ���ڵ�ΪNULL 
					}
					else
					{
						ptr2 -> next = ptr1 -> next;//����ǰһ���ڵ����һ���ڵ�Ϊ��ǰ�ڵ����һ���ڵ� 
					}
					v.push_back(ptr1);//���붯̬���鵱�� 
					ptr1 = ptr2 -> next;//���������� 
				}
				else
				{
					ptr1 = ptr1 -> next;//���������ڵ㶼������ 
					ptr2 = ptr2 -> next;//���������ڵ� 
				}
			}
			for(auto ptr : v)//ö�����е�ָ��ڵ� 
			{
				free(ptr);//�ͷ��ڴ�ռ� 
			}
			free(p);//�ͷŵ�ǰ�ڵ�Ŀռ� 
			cout << "                  ɾ���ɹ���"; 
			return;
		}
		q = q -> next;//ͬʱ������ 
		p = q -> next;//ͬʱ������ 
	}
}
/*******************
* �����������޸���ɵִ�ʱ��
* �������������ţ��µĺ����
* ��������� �޸ĳɹ�
* ����ֵ�� void
* ����˵������
********************/
void Airline::Revise_time()//�޸���ɵִ�ʱ��
{
	char flightnum[10];
	flightnode *p = head_of_flight -> next;//����ͷ�ڵ����һ���ڵ� 
	cout << "                  ����������Ҫ�޸ĵĺ���ţ�";
	cin >> flightnum;//����� 
	while (p != NULL)//���p�ڵ㲻��β��� 
	{
		if (strcmp(p -> flight_num, flightnum) == 0)//����ܹ�ƥ�亽��� 
		{
			cout << "                  �������µ����ʱ�䣺";
			cin >> p -> time;
			cout << "                  �޸ĳɹ���";
			return;
		}
		p = p -> next;//�������ڵ� 
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
void Airline::Revise_price()//�޸ļ۸�
{
	char flightnum[10];
	flightnode *p = head_of_flight -> next;//p�ڵ���ͷ������һ���ڵ� 
	cout << "                  ����������Ҫ�޸ĵĺ���ţ�";
	cin >> flightnum;//���뺽��� 
	while (p != NULL)//���pָ�벻��βָ��Ļ� 
	{
		if (strcmp(p -> flight_num, flightnum) == 0)//flight_num��flightnum�ܹ���Ӧ���� 
		{
			cout << "                  �����µļ۸�";
			cin >> p -> price;
			cout << "                  �޸ĳɹ���	";
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
void Airline::Save_flight()//���溽����Ϣ
{
	flightnode *f = head_of_flight -> next;//fΪͷ������һ���ڵ� 
	ofstream outfile("FlightList.dat", ios::trunc);//����ڵ�������Ϣ 
	if (!outfile)//�����ʧ�ܵĻ� 
	{
		cerr << "                  �洢ʧ�ܣ�";//����洢ʧ�� 
		return;
	}
	while (f != NULL)//���f�ڵ㲻��β���Ļ� 
	{
		outfile << f -> flight_num << " " << f -> plane_num << " " << f -> date << " " << f -> time << " " << f -> start_place << " " << f -> end_place << " " << f -> price << " " << f -> left << " " << f -> now_seat_num << endl;
		f = f -> next;//����f�ڵ����һ���ڵ� 
	}
	outfile.close();//�ر�����ļ� 
}
/*******************
* ������������ʼ���û�
* ��������� ��
* ��������� ��
* ����ֵ�� void
* ����˵������
********************/
void Airline::Init_passenger()//��ʼ���û�
{
	passengernode* c = (passengernode *)malloc(sizeof(passengernode));//�µĽڵ����� 
	head_of_passenger = tail_of_passenger = c;//ͷ������β������c 
	c -> next = NULL;//���½ڵ����һ���ڵ�ΪNULL 
}
/********************
* �����������û���Ϣչʾ
* �����������
* �����������
* ����˵������ 
********************/ 
void Airline::passenger_display()//�û���Ϣչʾ 
{
	passengernode *p = head_of_passenger -> next;//p�ڵ�Ϊͷ������һ���ڵ� 
	cout << setw(25) << "ԤԼ״̬��" << setw(12) << "�˿�����" << setw(12) << "�˿�ID" << setw(12) << "���������" << setw(12) << "����" << setw(12) << "����ʱ��" << setw(12) << "ʼ����" << setw(12) << "�յ�" << setw(12) << "Ʊ��" << endl; 
	for(p; p != NULL; p = p -> next)//���������еĽڵ� 
	{
		cout << setw(25) << p -> full << setw(12) << p -> name << setw(12) << p -> ID_num << setw(12) << p -> flight_num << setw(12) << p -> seat_num << setw(12) << p -> time << setw(12) << p -> start_place << setw(12) << p -> end_place << setw(12) << p -> price << endl;				
	}
	return;//����󷵻ؼ��� 
} 
/*******************
* ���������������û���Ϣ
* ��������� ����PassengerList.dat��Ϣ������
* ��������� ��
* ����ֵ�� void
* ����˵������
********************/
void Airline::Load_passenger()//�����û���Ϣ
{
	passengernode *s;//��������˿ͽڵ�s 
	s = (passengernode *)malloc(sizeof(passengernode));//Ϊ�µĽڵ����������ռ� 
	ifstream infile("PassengerList.dat", ios::in);//���������Ϣ 
	if (!infile)//�����ȡ��������ļ��Ļ� 
	{
		cerr << "                  ��Ϣ����";//��Ϊ��Ϣ���� 
		return;
	}
	while (1)
	{
		infile >> s -> name >> s -> ID_num >> s -> flight_num >> s -> seat_num >> s -> time >> s -> start_place >> s -> end_place >> s -> price;
		if (!infile.eof())//������ص����� 
		{
			tail_of_passenger -> next = s;//�˿ͽڵ����һ���ڵ�Ϊs 
			tail_of_passenger = s;//����β��� 
			s = (passengernode *)malloc(sizeof(passengernode));//����һ���µĽڵ� 
		}
		else
			break;
	}
	tail_of_passenger -> next = NULL;//�ڵ�ĺ�һ���ڵ�ΪNULL
	free(s);//�ͷ�����ڵ� 
}
/*******************
* ����������������Ϣ
* ���������passenger�������Ϣ
			flight�������Ϣ
* ��������� ��Ʊ�ɹ� or ʧ��
* ����ֵ�� void
* ����˵���������Ʊ���㻹����Ԥ��������ж����Ʊ����˲�乺��
********************/
void Airline::Book()//��Ʊ
{
	char start_place[20], end_place[20], flightnum[10];//������Ϣ
	flightnode *p = head_of_flight -> next, *q = head_of_flight -> next;//�����ڵ� 
	passengernode *s;//�ͻ��ڵ� 
	char mark, check = '1';//�����Ƿ��ظ�չʾ 
	s = (passengernode *)malloc(sizeof(passengernode));//�µĳ˿ͽڵ� 
	cout << "                  ����������������"; 
	cin >> s -> name;
	cout << "                  ����������֤���ţ�"; 
	cin >> s -> ID_num;
	cout << "                  �����������:";
	cin >> start_place;
	cout << "                  ������Ŀ�ĵ�:";
	cin >> end_place;
	cout << setw(25) << "�����" << setw(12) << "�������" << setw(12) << "������" << setw(12) << "Ŀ�ĵ�" << setw(12) << "�۸�" << setw(12) << "��Ʊ" << endl;
	while (p != NULL)//��������յ� 
	{
		if (strcmp(p -> start_place, start_place) == 0 && strcmp(p -> end_place, end_place) == 0)
		{
			cout << setw(25) << p -> flight_num << setw(12) << p -> time << setw(12) << p -> start_place << setw(12) << p->end_place << setw(12) << p->price << setw(12) << p->left << endl;
			check = '0';//˵���ҵ��� 
		}
		p = p -> next;
	}
	if (check == '1')//����˵��û���ҵ�qaq 
	{
		cout << "                  û����صĺ��࣬";
		system("pause");
		cout << "                  �����Ƿ���Ҫ�鿴�����ܹ�����ͬһĿ�ĵصĺ���(�� y / �� n)";
		cin >> mark;//���������ӵĻ� 
		if(mark == 'y')
		{
			p = head_of_flight -> next;//ͷ������һ���ڵ� 
			cout << setw(25) << "�����" << setw(12) << "�������" << setw(12) << "������" << setw(12) << "Ŀ�ĵ�" << setw(12) << "�۸�" << setw(12) << "��Ʊ" << endl;
			while(p != NULL)//ָ�벻����NULL 
			{
				if(strcmp(p -> end_place, end_place) == 0)//ƥ��һ���յ�վ 
				{
					cout << setw(25) << p -> flight_num << setw(12) << p -> time << setw(12) << p -> start_place << setw(12) << p -> end_place << setw(12) << p -> price << setw(12) << p -> left << endl;
				}
				p = p -> next;//�������ڵ� 
			}
			cout << "                  ";//������� 
			system("pause");
			return;
		}
		else
		return;//���ؽڵ� 
	}
	cout << "                  ����������Ҫ����ĺ���ţ�";
	cin >> flightnum;//����� 
	puts("");
	while (q != NULL)//q����NULL�ڵ� 
	{
		if (strcmp(q -> flight_num, flightnum) == 0 && strcmp(q -> start_place, start_place) == 0 && strcmp(q->end_place, end_place) == 0)//ƥ����ʼ���Ƿ���ͬ 
		{
			if (q -> left == 0)//�����ƱΪ0�� 
			{
				cout << "                  ��Ʊ���㣬��ѡ���Ƿ�ԤԼ���� y / �� n��";//�����Ʊ���� 
				cin >> mark;//����ָ�� 
				if (mark == 'y')//���ָ��Ϊy�Ļ� 
				{
					s -> price = q -> price;//�۸���� 
					s -> seat_num = 0;//���κŸ��� 
					s -> full = 1;//��ʾ��ԤԼ״̬ 
					strcpy(s -> start_place, start_place);//������� 
					strcpy(s -> end_place, end_place);//�����յ� 
					strcpy(s -> time, q -> time);//����ʱ�� 
					strcpy(s -> flight_num, flightnum);//���ƺ���� 
					cout << "                  ԤԼ�ɹ���" << endl; 
					tail_of_passenger -> next = s;//�˿͵���һ���ڵ�Ϊs 
					tail_of_passenger = s;//�˿ͽڵ����Ϊs 
					tail_of_passenger -> next = NULL;//�˿ͽڵ��β���Ϊ 
					cout << "                  ";
					system("pause");//ϵͳֹͣһ�� 
					return;
				}
				else
					return;
			}
			/*
				char name[30];//����
				char ID_num[30];//֤����
				char flight_num[10];//����� 
				char time[20];//���ʱ��
				char start_place[20];//������
				char end_place[20];//Ŀ�ĵ�
				float price;//�۸�
				int full = 0;//�Ƿ��ں�״̬ 
				int seat_num;//���κ�
			*/
			strcpy(s -> flight_num, flightnum);//���ƺ���� 
			strcpy(s -> start_place, start_place);//������ʼ�ص� 
			strcpy(s -> end_place, end_place);//������ֹ�ص� 
			strcpy(s -> time, q->time);//����ʱ�� 
			s -> full = 0; //���ڶ�Ʊ״̬ 
			s -> price = q -> price;//�۸���� 
			s -> seat_num = q -> now_seat_num + 1;//���κŸ��� 
			tail_of_passenger -> next = s;//����β�ڵ� 
			tail_of_passenger = s; //�˿͵�β��� 
			tail_of_passenger -> next = NULL;//���һ���ڵ��nextΪNULL 
			//��Ʊ�ɹ�
			cout << "                  ��Ʊ�ɹ���" << endl; 
			q -> left --;//��Ʊ��һ 
			q -> now_seat_num ++;//��ǰ�����κ�+1 
			cout << "                  ";
			system("pause");
			return;
		}
		else
			q = q -> next;
	}
	cout << "                  ������������\n";
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
void Airline::Qbook()//��Ʊ
{
	char name[30];
	char ID_num[30];
	flightnode *f = head_of_flight -> next;//��Ʊϵͳ 
	passengernode *p = head_of_passenger -> next, *q = head_of_passenger, *t = head_of_passenger -> next;
	cout << "                  ����������������";
	cin >> name;//�������� 
	puts("");
	cout << "                  ����������֤���ţ�";
	cin >> ID_num;//����˿͵����֤���� 
	while (p != NULL)
	{
		if (strcmp(p -> name, name) == 0 && strcmp(p -> ID_num, ID_num) == 0)//���������֤��ƥ�� 
		{
			while (f != NULL)//���û���յ�Ļ� 
			{
				if (strcmp(p -> flight_num, f -> flight_num) == 0)//�����ƥ�� 
				{
					f -> left ++;//����+1 
					f -> now_seat_num --;//��ǰ���κż�һ 
					while (t != NULL)
					{
						if (strcmp(t -> flight_num, p -> flight_num) == 0 && t -> full == 1)
						{
							strcpy(t -> start_place, p -> start_place);//������ʼ�� 
							strcpy(t -> end_place, p -> end_place);//�����յ� 
							strcpy(t -> time, p -> time);//����ʱ�� 
							t -> price = p -> price;
							t -> full = 0;//�Ƿ���ԤԼ״̬ 
							t -> seat_num = f -> now_seat_num + 1;//���κŸ��� 
							f -> left --;//��Ʊ����һ 
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
					ptr -> seat_num --;//�Ѷ�Ӧ�ú���ŵ����д��ڲ���ԤԼ״̬�����κŸ��� 
				}
			}
			free(p);//�ͷŸýڵ���ڴ� 
			cout << "                  ��Ʊ�ɹ���";
			return;
		}
		q = q -> next;
		p = q -> next;
	}
}
/*******************
* ������������ѯ��Ʊ
* ���������passenger�������Ϣ
* ��������� �����û���Ʊ����Ϣ
* ����ֵ�� void
* ����˵����
********************/
void Airline::Check_book()//��ѯ��Ʊ
{
	char name[30];
	char ID_num[30];
	passengernode *p = head_of_passenger -> next;//ͷ������һ���ڵ� 
	passengernode *q = head_of_passenger -> next;
	cout << "                  ����������������";
	cin >> name;
	cout << "                  ����������֤���ţ�";
	cin >> ID_num;
	cout << setw(25) << "����" << setw(12) << "�����" << setw(12) << "����" << setw(12) << "�������" << setw(12) << "������" << setw(12) << "Ŀ�ĵ�" << setw(12) << "�۸�" << setw(12) << endl;
	int rank = 0;//��ǰ��Ϊ�� 
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
						rank ++;//�������ԤԼ״̬��ôrank++ 
					}
				}
				cout << "                  Ŀǰ�ó˿�������ԤԼ״̬�����ڵ�" << rank + 1 << "λ\n";
			}
			else cout << "                  Ŀǰ�˿��ѳɹ���Ʊ���˿���Ϣ������ʾ\n"; 
			cout << setw(25) << p -> name << setw(12) << p -> flight_num << setw(12) << p -> seat_num << setw(12) << p->time << setw(12) << p->start_place << setw(12) << p->end_place << setw(12) << p->price << setw(12) << endl;
			cout << "                  ";
			system("pause");
			return;
		}
		else
			p = p -> next;//�ڵ���������߰� 
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
void Airline::Save_passenger()//�����û���Ϣ
{
	passengernode *p = head_of_passenger -> next;//ͷ��������� 
	ofstream outfile("PassengerList.dat", ios::trunc);//�˿���Ϣ 
	if (!outfile)
	{
		cerr << "                  �洢ʧ�ܣ�";
		return;
	}
	while (p != NULL)//�ڵ㲻�����һ���ڵ�Ļ� 
	{
		outfile << p -> name << " " << p -> ID_num << " " << p -> flight_num << " " << p -> seat_num << " " << p -> time << " " << p->start_place << " " << p->end_place << " " << p->price << endl;
		p = p -> next;//��������ڵ����һ���ڵ� 
	}
	outfile.close();//�ر��ļ� 
}
void Airline::root_init()
{
	administrator *s = (administrator *)malloc(sizeof(administrator));//��ʼ������Ա 
	head_of_root = tail_of_root = s;//����һ���µĽڵ��ʼ���� 
	s -> next = NULL;
}
int Airline::check()
{
	administrator *ptr = (administrator *)malloc(sizeof(administrator));//����һ���µ�ָ�� 
	cout << endl << "                  �����볬������Ա��root���û�����" ;
	cin >> ptr -> name;
	if(strcmp(ptr -> name, root_name) == 1) //�������Ƿ��ܹ�ƥ�� 
	{ 
		cout << endl << "                  �û�������\n";
		return 0;
	}
	printf("\n"); 
	cout << endl << "                  ����������:";
	cin >> ptr -> password;//�������뼴�� 
	if(strcmp(ptr -> password, root_password) == 1)//�����ܷ�ƥ�� 
	{
		cout << endl << "                  �������\n";
		return 0;
	}
	printf("\n");
	return 1;			
}
/*******************
* ��������������Ա��Ϣ���� 
* ��������� ����FlightList.dat��Ϣ������
* ��������� ��
* ����ֵ�� void
* ����˵������
********************/
void Airline::root_reset()
{
	if(tail_of_root == head_of_root) return;//һ��ɾ�����еĹ���Ա��Ϣ 
	administrator* ptr = tail_of_root -> pre;
	administrator* s;
	for(ptr; ptr != head_of_root; ptr = ptr -> pre)
	{
		s = ptr -> next;
		free(s);//�ͷ�����ڵ���ڴ� 
	}
	if(head_of_root -> next != NULL)
	{
		free(head_of_root -> next);//�ѳ�ʼ�ڵ���ڴ��ͷ� 
		head_of_root -> next = NULL;
	}
}
/*******************
* ��������������Ա��� 
* ��������� �� 
* ��������� ��
* ����ֵ�� void
* ����˵������
********************/
void Airline::root_add()
{
	while(1)
	{
		cout << "                  ��������Ҫ��ӵ��û���:";//����Ҫ��ӵ��û��� 
		administrator* s = (administrator *)malloc(sizeof(administrator));
		cin >> s -> name;//�����û�������Ϣ 
		cout << "                  ����Ϊ��";
		cin >> s -> password;//�����û��������� 
		puts("");
		tail_of_root -> next = s;//����β��� 
		s -> pre = tail_of_root;//����ǰ�ýڵ� 
		tail_of_root = s;//����β��� 
		cout << "                  ��ӳɹ����Ƿ�������(��/y����/n):";
		char p;
		cin >> p;//������� 
		if(p == 'n') break;
	}
	tail_of_root -> next = NULL;//����β������һ���ڵ�ΪNULL 
}
/*
void Airline::Add_flight()//��Ӻ���
{
	char mark = 'y';
	while (mark == 'y')
	{
		flightnode* s = (flightnode *)malloc(sizeof(flightnode));
		cout << "                  �����뺽��ţ�";
		cin >> s -> flight_num;
		cout << "                  ���������ʱ�䣺";
		cin >> s -> time;
		cout << "                  �����������:";
		cin >> s -> start_place;
		cout << "                  ������Ŀ�ĵأ�";
		cin >> s -> end_place;
		cout << "                  ������۸�";
		cin >> s -> price;
		cout << "                  ��������Ʊ��";
		cin >> s -> left;
		tail_of_flight -> next = s;
		tail_of_flight = s;
		cout << "                  ��ӳɹ���" << endl;
		cout << "                  �Ƿ������ӣ����ǡ�y��/��n������";
		cin >> mark;
	}
	tail_of_flight -> next = NULL;
}*/
/*******************
* ��������������Աɾ�� 
* ��������� �� 
* ��������� ��
* ����ֵ�� void
* ����˵������
********************/
void Airline::root_del()//ɾ������Ա
{
	administrator *p = (administrator *)malloc(sizeof(administrator)); //����һ���µĽڵ������ռ� 
	cout << "                  ���������Ա�û���:";
	cin >> p -> name;//����ڵ������ 
	puts("");
	cout << "                  ����ɾ��...........................\n"; //���� 
	for(administrator *ptr = head_of_root -> next; ptr != NULL; ptr = ptr -> next)//��������Ա�����е�ÿ������Ա 
	{
		if(strcmp(ptr -> name, p -> name) == 0)//����ܹ�ƥ������ 
		{
			if(ptr -> next == NULL)//�����һ���ڵ�ΪNULL 
			{
				tail_of_root = ptr -> pre;//�͵�һ�ָ��·�ʽ 
				tail_of_root -> next = NULL;//β������һ���ڵ�ΪNULL 
				free(ptr);//�ͷ�����ڵ�Ŀռ� 
				break;
			}
			else
			{
				ptr -> pre -> next = ptr -> next;//��������ڵ�ǰ�ýڵ�ĺ�̽ڵ� 
				ptr -> next -> pre = ptr -> pre;//���º�̽ڵ��ǰ���ڵ� 
				free(ptr);//�ͷ�����ڵ� 
				break;
			}
		}
	}
	cout << "                  ɾ���ɹ�\n";
} 
void Airline::root_load()//����Ա��Ϣ����
{
	administrator *s;//��������ڵ� 
	s = (administrator *)malloc(sizeof(administrator));//������ڵ���������ռ� 
	ifstream infile("root.dat", ios::in);//�������Ա�������Ϣ 
	if (!infile)//�������ʧ�ܵĻ� 
	{
		cerr << "                  ��Ϣ����";
		return;
	}
	while (1)
	{
		infile >> s -> name >> s -> password;//�����û��������� 
		if (!infile.eof())//�������ʧ�ܵĻ� 
		{
			tail_of_root -> next = s;//β������һ���ڵ����Ϊs 
			s -> pre = tail_of_root;//s��ǰ���ڵ����Ϊβ��� 
			tail_of_root = s;//β������Ϊs 
			s = (administrator *)malloc(sizeof(administrator));//��s�����ڴ�ռ� 
		}
		else
			break;//�������������� 
	}
	tail_of_root -> next = NULL;//β������һ���ڵ�ΪNULL 
	free(s);			//�ͷ�s����ڵ� 
} 
void Airline::root_save()//����Ա��Ϣ���� 
{
	administrator *f = head_of_root -> next;//����fΪͷ������һ���ڵ� 
	ofstream outfile("root.dat", ios::trunc);//������ļ�Ϊroot.dat 
	if (!outfile)//����򲻿���Ӧ���ļ� 
	{
		cerr << "                  �洢ʧ�ܣ�";//����洢ʧ�� 
		return;
	}
	while (f != NULL)//���f����NULL�Ļ� 
	{
		outfile << f -> name << " " << f -> password << endl; //�����Ӧ��������Ϣ 
		f = f -> next;//�ƶ�����һ��ָ�� 
	}
	outfile.close();//����ļ����� 
}
int Airline::root_right()//����ԱȨ��
{
	int flag = 0;
	administrator *p = (administrator *)malloc(sizeof(administrator)); //�����ڵ�p�����������ռ� 
	cout << "                  �������û�����"; //�����û��� 
	cin >> p -> name;//�����Ӧ���û��� 
	puts("");
	for(administrator *ptr = head_of_root -> next; ptr != NULL; ptr = ptr -> next)//�������еĹ���Ա��Ϣ 
	{
		if(strcmp(ptr -> name , p -> name) == 0)//����ܹ�ƥ����ص���Ϣ�Ļ� 
		{
			flag = 1;//��flag=1��Ϊ�ҵ��ڵ��� 
			cout << "                  ���������룺";
			cin >> p -> password;//�������� 
			if(strcmp(ptr -> password, p -> password) == 0)
			{
				flag = 2;//����û��������붼�ܹ�ƥ��Ļ� 
				cout << "                  ����ԱȨ�޻�ȡ�ɹ���\n";
				break;//��ù���ԱȨ�� 
			}
		}
	} 
	if(flag == 0)//����û�������Ļ� 
	{
		cout << endl;
		cout << "                  �û�������\n";
		return 0;
	}
	else if(flag == 1)//����������Ļ� 
	{
		cout << "                  �������\n";
		return 0;
	}
	else return 1;//������Ϊ���Ȩ�� 
} 
void Airline::root_mode()//����Աģʽ 
{
	while(1)
	{
		cout << "                  �������������������������������������������������������������������������������� " << endl;
		cout << "                            ��    �� ����Ա ��    �� " << endl;
		cout << "                 ��                                        �� " << endl;
		cout << "                            ��     1.��������Աģʽ       �� " << endl;
		cout << "                 ��                                        �� " << endl;
		cout << "                            ��     2.����Աģʽ           �� " << endl;
		cout << "                 ��                                        �� " << endl;
		cout << "                            ��     3.������һ��           �� " << endl;
		cout << "                 ��                                        �� " << endl;
		cout << "                  �������������������������������������������������������������������������������� " << endl;
		cout << "                  ��������Ҫ���еĹ��ܣ�";
		int op;
		cin >> op;
		if(op == 1) 
		{
			if(check())//�����������ԱȨ�޻�� 
			{
				while(1)//���볬������Աģʽ 
				{ 
					cout << "                          ��������ԱȨ�޻�ȡ�ɹ���\n";
					cout << "                  �������������������������������������������������������������������������������� " << endl;
					cout << "                            ��    �� ��������Աģʽ ��    �� " << endl;
					cout << "                 ��                                        �� " << endl;
					cout << "                            ��     1.����Ա��ʼ��         �� " << endl;
					cout << "                 ��                                        �� " << endl;
					cout << "                            ��     2.��ӹ���Ա           �� " << endl;
					cout << "                 ��                                        �� " << endl;
					cout << "                            ��     3.ɾ������Ա           �� " << endl;
					cout << "                 ��                                        �� " << endl;
					cout << "                            ��     4.¼�����Ա��Ϣ       �� " << endl;
					cout << "                 ��                                        �� " << endl;
					cout << "                            ��     5.����Ա��Ϣ           �� " << endl;
					cout << "                 ��                                        �� " << endl;
					cout << "                            ��     6.������һ��           �� " << endl;
					cout << "                 ��                                        �� " << endl;
					cout << "                  �������������������������������������������������������������������������������� " << endl;
					cout << "                  ��������Ҫ���еĹ��ܣ�";
					int op;
					cin >> op;
					if(op == 1)
					{
						root_reset();//����Ա��ʼ�� 
						root_save();	//�������Ա��Ϣ 
					}				
					else if(op == 2)
					{
						root_add();	//����Ա��� 
						root_save();//�������Ա��Ϣ 
					}	
					else if(op == 3)
					{
						root_del();//����Աɾ�� 
						root_save();//�������Ա��Ϣ 
					}
					else if(op == 4)
					{
						root_load();//����Ա������Ϣ 
						cout << "                  ����Ա��Ϣ¼��ɹ�\n";
					} 
					else if(op == 5)
					{
						root_display();//չʾ���еĹ���Ա��Ϣ 
					}
					else if(op == 6) break;
					else printf("                             ��������\n");
				}
			}
		}
		else if(op == 2)
		{
			if(root_right())//����ܹ���ù���ԱȨ�� 
			{
				while(1)//�������Աģʽ 
				{
					cout << "                  �������������������������������������������������������������������������������� " << endl;
					cout << "                            ��    �� ����Աģʽ ��    �� " << endl;
					cout << "                 ��                                        �� " << endl;
					cout << "                            ��     1.��ѯ�˿���Ϣ     �� " << endl;
					cout << "                 ��                                        �� " << endl;
					cout << "                            ��     2.������һ��       �� " << endl;
					cout << "                 ��                                        �� " << endl;
					cout << "                  �������������������������������������������������������������������������������� " << endl;
					cout << "                  ������Ҫ���еĹ��ܣ�";		
					int op;
					cin >> op;//����op���� 
					 
					if(op == 1)
					{
						passenger_display();//�˿���Ϣչʾ 
					}			
					else if(op == 2)
					{
						break;//�˳� 
					}
					else
					{
						cout << "                  �������\n";
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
	administrator *ptr = head_of_root -> next;//����Ա��Ϣչʾ 
	cout << setw(25) << "�û���" << setw(12) << "����" << endl;
	for(ptr; ptr != NULL; ptr = ptr -> next)//�ڵ��ǰ������� 
	{
		cout << setw(25) << ptr -> name << setw(12) << ptr -> password << endl; 
	} 
}
