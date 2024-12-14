#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
#include<chrono>
#include<thread>
#include<iostream>
#include<ctime>
#include<cstdlib>
#define cout std::cout
#define cin std::cin
#include<vector>
using namespace std;
// �洢������Ϣ��ӳ��
map<int, int>kaoqin_map;
// �洢�����û���Ϣ��ӳ��
map<int, int>all__map;

// ��Ϣ�ṹ�壬���ڴ洢��Ϣ��Ϣ
struct message
{
	string t_name; // ��Ϣ����������
	string neirong; // ��Ϣ����
	string time; // ��Ϣ����ʱ��
};

// �洢��Ϣ�б�
vector<message>message_list;

string student_account; // ѧ���˺�

// ��ȡ��ǰʱ��ĺ����������ַ�����ʽ��ʱ��
string current_time()
{
	time_t now = time(nullptr);
	tm* local_time = localtime(&now);
	return to_string(local_time->tm_year + 1900) + "��" + to_string(local_time->tm_mon + 1) + "��" + to_string(local_time->tm_mday) + "��" + to_string(local_time->tm_hour) + ":" + to_string(local_time->tm_min);
}

string teacher_name; // ��ʦ����
string student_name; // ѧ������

// ��ʦ�ṹ�壬���ڴ洢��ʦ��Ϣ
struct teacher
{
	string name; // ��ʦ����
	string account; // ��ʦ�˺�
	string password; // ��ʦ����
};

// ѧ���ṹ�壬���ڴ洢ѧ����Ϣ
struct student
{
	string name; // ѧ������
	string account; // ѧ���˺�
	string password; // ѧ������
	int id; // ѧ��ID
	int is_kaoqin; // �Ƿ���뿼��
	int is_message; // �Ƿ�����Ϣ
	int is_finish_kaoqin; // �Ƿ���ɿ���
	int have_look_message; // �Ƿ�鿴����Ϣ
	int have_look_kaoqin; // �Ƿ�鿴������
};

// ����ṹ�壬���ڴ洢ѧ��������Ϣ
struct student_apply
{
	string name_s; // ѧ������
	string type; // ��������
	string time; // ����ʱ��
	string message; // ��������
	bool finish; // �Ƿ��������
	bool pass; // �������
};

// �洢�����б�
vector<student_apply>apply_list;

// �洢��ʦ�û��б�
vector<teacher>user_t;
// �洢ѧ���û��б�
vector<student>user_s;

// ���ڽṹ�壬���ڴ洢������Ϣ
struct kaoqin
{
	string message; // ��������
	string time; // ����ʱ��
	string place; // ���ڵص�
	string teacher_name; // ��ʦ����
	int id; // ����ID
	string student_name; // ѧ������
};

// �洢�����б�
vector<kaoqin>kaoqin_list;
vector<string>student_but_kaoqin; // �洢û�в��뿼�ڵ�ѧ��
void bar(int totalSteps) {
	int barWidth = 50;

	for (int step = 0; step <= totalSteps; ++step) {
		float progress = (float)step / totalSteps;
		int pos = barWidth * progress;
		for (int i = 0; i < barWidth; ++i) {
			if (i < pos) cout << "\033[44m \033[0m";
			else cout << "\033[41m \033[0m";
		}
		cout << "\033[45m->\033[0m ";
		cout << "\033[33m" << int(progress * 100.0) << "%\r\033[0m";
		cout.flush();
		this_thread::sleep_for(chrono::milliseconds(100));
	}
	cout << endl;
}
int add_user()
{
	again:
	cout<<"\033[34m��ѡ����ӵĽ�ɫ��\033[0m\033[36m\n\t1.ѧ��\n\t2.��ʦ\033[0m\033[33m"<<endl;
	int i; cin >> i; 
	cout << "\033[0m";
	string account, password, name;
	if (i == 1)
	{

		
		cout << "\033[34m��������ӵ�������\n\033[0m\033[33m";
		string name; cin >> name;
		cout << "\033[0m\033[34m��������ӵ��˺ţ�\n\033[0m\033[33m";
		string account; cin >> account;
		cout << "\033[0m\033[34m��������ӵ����룺\n\033[0m\033[33m";
		string password; cin >> password;
		cout << "\033[0m\033[34m��������ӵ�ѧ�ţ�\n\033[0m\033[33m";
		int id; cin >> id;
		user_s.push_back({ name,account,password,id ,0,0,0,1,1 });
		cout << "\033[0m\033[32m��ӳɹ���\033[0m" << endl;
		return 1;
	}

	else if (i == 2)
	{
		
		cout << "\033[34m��������ӵ�������\n\033[0m\033[33m";
		cin >> name;
		cout << "\033[0m\033[34m��������ӵ��˺ţ�\n\033[0m\033[33m";
		cin >> account;
		cout << "\033[0m\033[34m��������ӵ����룺\n\033[0m\033[33m";
		cin >> password;
		user_t.push_back({ name,account,password });
		cout << "\033[0m\033[32m��ӳɹ���\033[0m" << endl;
		return 1;
	}
	else
	{
		cout << "\033[41;1m�������\033[0m" << endl;
		goto again;
	}
}
int delete_user()
{
	delete_again_choice:
	cout<<"\033[34m��ѡ��ɾ���Ľ�ɫ��\033[0m\033[31m\n\t1.ѧ��\n\t2.��ʦ\033[0m\033[32m\n\t3.�˳�ɾ��\033[0m"<<endl;
	int i; cin >> i;
	if (i == 1)
	{
		
		cout << "\033[31m������ɾ����������\033[0m\033[33m\n";
		string to_delete_name;
		cin>>to_delete_name;
		cout << "\033[0m";
		for (auto it = user_s.begin(); it != user_s.end(); it++)
		{
			if (it->name == to_delete_name)
			{
				string check;
				cout << "\033[31mȷ��Ҫɾ����\033[34m(\033[0m\033[31my\033[34m\033[0m or \033[32mn\033[0m\033[34m)\033[0m\033[35m\n";
				cout<<it->name<<"     "<<it->account<<"     "<<it->password<<"     "<<it->id<<"\n\033[0m\033[33m";
				cin >> check;
				cout << "\033[0m";
				if (check == "y" || check == "Y"||check=="yes"||check=="YES"||check=="��")
				{
					user_s.erase(it);
					cout << "\033[41;4mɾ����...wait for a while...\033[0m" << endl;
					bar(25);
					cout << "\033[31mɾ���ɹ���\033[0m" << endl;
					return 1;
				}
				else
				{
					cout << "\033[32mȡ��ɾ����\033[0m" << endl;
					goto delete_again_choice;
				}
			}
			
		}
		cout << "\033[31;1mû�и�ѧ����\033[0m" << endl;
		goto delete_again_choice;
	}
	else if (i == 2)
	{
		
		cout << "\033[34m������ɾ����������\033[0m\033[33m\n";
		string to_delete_name;
		cin >> to_delete_name;
		cout << "\033[0m";
		for (auto it = user_t.begin(); it != user_t.end(); it++)
		{
			if (it->name == to_delete_name)
			{
				string check;
				cout << "\033[31mȷ��Ҫɾ����\033[34m(\033[0m\033[31my\033[34m\033[0m or \033[32mn\033[0m\033[34m)\033[0m\n\033[33m";
				cin >> check;
				cout << "\033[0m";
				if (check == "y" || check == "Y" || check == "yes" || check == "YES" || check == "��")
				{
					user_t.erase(it);
					cout << "\033[41;4mɾ����...wait for a while...\033[0m" << endl;
					bar(25);
					cout << "\033[31mɾ���ɹ���\033[0m" << endl;

					goto delete_again_choice;
				}
				else
				{
					cout << "\033[32mȡ��ɾ����\033[0m" << endl;
					goto delete_again_choice;
				}
			}
			
		}
		cout << "\033[31;1mû�иý�ʦ��\033[0m" << endl;
		goto delete_again_choice;
	}
	else if (i == 3)
	{
		return 1;
	}
	else
	{
		cout << "\033[31;1m����������������룡\033[0m" << endl;
		goto delete_again_choice;
	}
}
int modify_user()
{
xiugai_again_choice:
	cout << "\033[34;4m��������Ҫ�޸ĵ��˺����ͣ�\033[0m\033[36m\n\t1.ѧ�� \n\t2.��ʦ\n\t\033[0m\033[31m3.�˳��޸�\033[0m\033[33m" << endl;
	int i; cin >> i;
	cout << "\033[0m";
	
	
	if (i == 1)
	{
		cout << "\033[34m��������Ҫ�޸ĵ��˺ţ�\033[0m\033[33m\n";
		string account_xiugai; cin >> account_xiugai;
		cout << "\033[0m";
		for (auto it = user_s.begin(); it != user_s.end(); it++)
		{
			if (it->account == account_xiugai)
			{
				cout << "\033[34m�������޸ĺ�����룺\033[0m\033[33m\n";
				string new_password; cin >> new_password;
				it->password = new_password;
				cout << "\033[0m\033[34m�������޸ĺ��ѧ�ţ�\033[0m\033[33m\n";
				int new_id; cin >> new_id;
				it->id = new_id;
				cout << "\033[0m\033[32m�޸ĳɹ���\033[0m" << endl;
				return 1;
			}
			else
			{
				cout << "\033[31mû�и�ѧ����\033[0m\n";
				cout << "\033[34;4m�Ƿ��������룡\033[0m\n\033[33m";
				string check; cin >> check;
				cout << "\033[0m";
				if (check == "yes" || check == "YES" || check == "��")
				{
					goto xiugai_again_choice;
				}
				else
				{
					return 1;
				}
			}
		}
	}
	else if (i == 2)
	{
		cout << "\033[34m��������Ҫ�޸ĵ��˺ţ�\033[0m\033[33m\n";
		string account_xiugai; cin >> account_xiugai;
		cout << "\033[0m";
		for (auto it = user_t.begin(); it != user_t.end(); it++)
		{
			if (it->account == account_xiugai)
			{
				cout << "\\033[34m�������޸ĺ�����룺\033[0m\033[33m\n";
				string new_password; cin >> new_password;
				it->password = new_password;
				cout << "\033[0m\033[32m�޸ĳɹ���\033[0m" << endl;
				return 1;
			}
			else
			{
				cout << "\033[31mû�иý�ʦ��\033[0m\n";
				cout<<"\033[34;4m�Ƿ��������룡\033[0m\\033[33m\n";
				string check;cin>>check;
				cout << "\\033[0m";
				if(check=="yes"||check=="YES"||check=="��")
				{
					goto xiugai_again_choice;
				}
				else
				{
					return 1;
				}
			}
			}
		}
	else if (i == 3)
	{
		return 1;
	}
	else
	{
		cout << "\033[41;1m����������������룡\033[0m" << endl;
		goto xiugai_again_choice;
	}
}
int query_user()
{
	cout << "\033[32m���ڲ�ѯ��...wait for a while...\033[0m\n";
	bar(25);
	cout << "\033[34;4m��ѯ������£�\n\033[0m\033[36;4mѧ����\033[0m\n\033[36m";
	cout<<left<<setw(30)<<"����"<< setw(30) << "�˺�"<< setw(30) << "����"<< setw(30) << "ѧ��\033[0m\033[35m"<<endl;
	for (auto it = user_s.begin(); it != user_s.end(); it++)
	{
		cout <<left << setw(30) << it->name << setw(30) << it->account << setw(30) << it->password << setw(30) << it->id << endl;
	}
	cout << "\033[0m\033[36;4m��ʦ��\n\033[0m";
	cout<<left<<setw(30)<<"\033[36m����"<< setw(30) << "     �˺�"<< setw(30) << "     ����\033[0m\033[35m"<<endl;
	
	for (auto it = user_t.begin(); it != user_t.end(); it++)
	{
		cout <<left << setw(30) <<  it->name << setw(30) <<  it->account << setw(30) << it->password << endl;
	}
	cout << "\033[0m" << endl;
	cout << "\033[32;4m��ѯ��ɣ�\033[0m" << endl;
	return 1;
}
int guanliyuan()
{
	guanliyuan_again_choice:
	cout << "\033[34m��������:\033[0m\n\t\033[32m1.����û�\033[0m\n\t\033[31m2.ɾ���û�\033[0m\033[36m\n\t3.�޸��û�\n\t4.��ѯ�û�\033[0m\n\t\033[31m5.������һ��\033[0m\033[33m" << endl;
	int choice; cin >> choice;
	cout << "\033[0m";
	switch (choice)
	{
	case 1:
	{
		int add = add_user();
		if (add == 1)goto guanliyuan_again_choice;

	}
	case 2:
	{
		int del = delete_user();
		if (del == 1)goto guanliyuan_again_choice;
	}
	case 3:
	{
		int xiugai = modify_user();
		if (xiugai == 1)goto guanliyuan_again_choice;
	}
	case 4:
	{
		int chaxun = query_user();
		if (chaxun == 1)goto guanliyuan_again_choice;
	}
	case 5:
	{
		return 1;
	}

	default:
	{
		cout << "\033[41;1m����������������룡\033[0m" << endl;
		goto guanliyuan_again_choice;
	}
	}
}
bool user_login_s(string account, string password)
{
	for (auto it = user_s.begin(); it != user_s.end(); it++)
	{
		if (it->account == account && it->password == password)
		{
			return true;
		}
	}
	return false;
}
bool user_login_t(string account, string password)
{
	for (auto it = user_t.begin(); it != user_t.end(); it++)
	{
		if (it->account == account && it->password == password)
		{
			return true;
		}
	}
	return false;
}
int guanliyuan_check()
{
	cout << "\033[34;4m�������������룺\033[0m\033[33m" << endl;;
	string password;cin>>password;
	cout << "\033[0m";
	if (password == "23456789")
	{
		cout << "\033[32m�����֤�ɹ���wait for a while...\033[0m" << endl;
		bar(25);
		int chect_finish = guanliyuan();
		if (chect_finish == 1)return 1;
		
	}
	else
	{
		cout << "\033[41;1m�����֤ʧ�ܣ���������֤���" << endl;
		cout << "����������ҳ�棡 \033[0m" << endl;
		bar(50);
		return 1;
	}
}
int kaoqin_send()
{
	string message, time, place, finish,name;
	cout << "\033[34m��������Ҫ�����Ŀ�����Ϣ��\033[0m\033[33m" << endl;
	cin>>message;
	cout << "\033[0m\033[34m�����뿼�ڽ�ֹʱ�䣺\033[0m\033[33m" << endl;
	cin>>time;
	cout << "\033[0m\033[34m�����뿼�ڵص㣺\033[0m\033[33m\n";
	cin>>place;
	cout << "\033[0m\033[34m�Ƿ���Ҫȫ��ѧ����ɣ�\033[34m(\033[0m\033[32my\033[34m\033[0m or \033[31mn\033[0m\033[34m)\033[0m\033[33m\n";
	cin>>finish;
	if (finish == "y" || finish == "Y" || finish == "yes" || finish == "YES" || finish == "��")
	{
		string teacher_name_t = teacher_name;
		for (auto it = user_s.begin(); it != user_s.end(); it++)
		{
			it->have_look_kaoqin = 0;
		}
		cout << "\033[32m���ڷ���������Ϣ...wait for a while...\033[0m" << endl;
		int temp = 10000 + rand() % 100000;
		all__map[temp]=user_s.size();
		kaoqin_map[temp] = 0;//����������
		kaoqin_list.push_back({ message,time,place,teacher_name_t,temp,"ȫ��ѧ��" });
		bar(25);
		cout << "\033[32;1m�����ɹ���\033[0m" << endl;
		return 1;
	}
	else
	{
		string teacher_name_t = teacher_name;
		kaoqin_send_again:
		cout<<"\033[34m�����벻��Ҫ��ɵ�ѧ��������\033[0m\033[33m\n";
		cin>>name;
		cout << "\033[0m";
		for (auto it = user_s.begin(); it != user_s.end(); it++)
		{
			if (it->name == name)
			{
				it->is_kaoqin = 1;
				it->have_look_kaoqin = 1;
			}
			it->have_look_kaoqin = 0;
		}
		for (auto it = user_s.begin(); it != user_s.end(); it++)
		{
			if (it->name == name)
			{
				student_but_kaoqin.push_back(name);
				it->is_kaoqin = true;
				int temp = 10000 + rand() % 100000;
				kaoqin_list.push_back({ message,time,place,teacher_name_t,temp,"but "+name});
				cout << "\033[32m���ڷ���������Ϣ...wait for a while...\033[0m" << endl;
				all__map[temp] = user_s.size()-1;
				bar(25);
				cout << "\033[32m�����ɹ���\033[0m" << endl;
				return 1;
			}
		}
		cout << "\033[41;1mû�и�ѧ����\033[0m" << endl;
		cout<<"\033[34m�Ƿ���������ѧ������?\033[0m\033[34m(\033[0m\033[31my\033[34m\033[0m or \033[32mn\033[0m\033[34m)\033[0m\n";
		string check;cin>>check;
		if (check == "y" || check == "Y" || check == "yes" || check == "YES" || check == "��")
		{
			goto kaoqin_send_again;
		}
		else
		{
			return 1;
		}
	}
}
int kaoqin_look()
{
	cout << "\033[32m���ڲ�ѯ������Ϣ...wait for a while...\033[0m" << endl;
	bar(25);
	cout << "\033[34m������Ϣ���£�\n\033[0m";
	int count = 1;
	cout << left << setw(15) <<"\033[36m���"<< setw(15) << "     ������" << setw(15) << "     ��������" << setw(15) << "     ���ڵص�" << setw(15) << "     ���ڽ�ֹʱ��" << setw(15) << "   ��Ҫ����ѧ��"<<setw(15) << "   ����ID"<<setw(15)<<"   ������\033[0m\033[35m" << endl;
	for (auto it = kaoqin_list.begin(); it != kaoqin_list.end(); it++)
	{	
	cout << left <<setw(15)<<count++<<setw(15)<< it->teacher_name  << setw(15)<<it->message<< setw(15) << it->place << setw(15) << it->time << setw(15) << it->student_name << setw(15) << it->id <<kaoqin_map[it->id]<<"/"<<all__map[it->id]<<endl;
	}
	cout << "\033[0m" ;
	cout << "\033[32;4m��ѯ��ɣ�\033[0m" << endl;
	return 1;
}
int kaoqin_del(int num)
{
	if (num < 1 || num > kaoqin_list.size())
	{
		cout << "\033[41;1m�������\033[0m" << endl;	
		return 1;
	}
	else
	{
		kaoqin_list.erase(kaoqin_list.begin() + num - 1);
		cout << "\033[31;4m����ɾ��������Ϣ...wait for a while...\033[0m" << endl;
		bar(25);
		cout << "\033[32;4mɾ���ɹ���\033[0m" << endl;
		return 1;
	
	}
}
int xiugaimima()
{
	xiugai_again_choice:
	cout << "\033[34m��������Ҫ�޸ĵ�ѧ���˺ţ�\033[0m\n\033[33m";
	string account_xiugai; cin >> account_xiugai;
	cout << "\033[0m";
	for (auto it = user_s.begin(); it != user_s.end(); it++)
	{
		if (it->account == account_xiugai)
		{
			cout << "\033[32;4m�������޸ĺ�����룺\033[0m\033[33m\n";
			string new_password; cin >> new_password;
			it->password = new_password;
			cout << "\033[0m\033[32m�޸ĳɹ���\033[0m" << endl;
			return 1;
		}
		else
		{
			cout << "\033[41;1mû�и�ѧ����\033[0m\n";
			cout << "\033[34m�Ƿ���������ѧ���˺ţ�\033[0m\033[34m(\033[0m\033[31my\033[34m\033[0m or \033[32mn\033[0m\033[34m)\033[0m\n\033[33m";
			string check; cin >> check;
			cout<<"\033[0m";
			if (check == "y" || check == "Y" || check == "yes" || check == "YES" || check == "��")
			{
				goto xiugai_again_choice;
			}
			else
			{
				return 1;
			}
		}
	}
}
int apply_handle(int i)
{
	cout<<"\033[34m��������Ϣ���£�\033[0m\n\033[36m";
	cout << left << setw(20)  << "ѧ������" << setw(20) << "��������" << setw(20) << "����ʱ��" << setw(20) << "��������\033[0m\033[35m" << setw(20) << endl;
	cout<<left<<setw(20)<<apply_list[i-1].name_s<<setw(20)<<apply_list[i-1].type<<setw(20)<<apply_list[i-1].message<<setw(20)<<apply_list[i-1].time<<endl;
	cout<<"\033[0m\033[34m�Ƿ�ͬ������룿\033[0m\033[34m(\033[0m\033[32my\033[34m\033[0m or \033[31mn\033[0m\033[34m)\033[0m\n\033[33m";
	string result;cin>>result;
	cout << "\033[0m";
	if (result == "y" || result == "Y" || result == "yes" || result == "YES" || result == "��")
	{
		apply_list[i - 1].finish = true;
		cout << "\033[32;4m�����ɹ���\033[0m" << endl;
		apply_list[i - 1].pass = true;
	}
	else
	{
		apply_list[i - 1].finish = true;
		cout << "\033[31;4m�Ѿ����أ�\033[0m" << endl;
		apply_list[i - 1].pass = false	;
	}
	cout<<"\033[34m�Ƿ���������������룿\033[0m\033[34m(\033[0m\033[32my\033[34m\033[0m or \033[31mn\033[0m\033[34m)\033[0m\n\033[33m";
	string check;cin>>check;
	cout << "\033[0m";
	if (check == "y" || check == "Y" || check == "yes" || check == "YES" || check == "��")
	{
		cout << "\033[34m������Ҫ�����������ţ�\033[0m\n\033[33m";
		int i;cin>>i;
		cout<<"\033[0m";
		apply_handle(i);
	}
	else
	{
		return 1;
	}
}
int apply()
{
	cout << "\033[34mѧ�����������£�\033[0m\n\033[36m";
	int count = 1;
	cout<<left<<setw(10)<<"���"<<setw (20)<< "ѧ������" << setw(20) << "��������" << setw(30) << "��������" << setw(20) << "����ʱ��" << setw(20) << "����״̬\033[0m"  << endl;
	cout << "\033[0m";
	cout << "\033[35m";
	for (auto it = apply_list.begin(); it != apply_list.end(); it++)
	{
		
		cout<<left<<setw(10)<<count++<<setw(20)<< it->name_s << setw(20)<< it->type << setw(30)<< it->message << setw(20)<< it->time << setw(20)<< (it->finish ? "\033[0m\033[32m������\033[0m" : "\033[31mδ����\033[0m\033[35m") << endl;
	}
	cout << "\033[0m";
	apply_again_choice:
	cout<<"\033[0m\033[34;4m�Ƿ�ʼ����\033[34m(\033[0m\033[32my\033[34m\033[0m or \033[31mn\033[0m\033[34m)\033[0m\033[33m" << endl;
	string check; cin >> check;
	cout << "\033[0m";
	if (check == "y" || check == "Y" || check == "yes" || check == "YES" || check == "��")
	{
		cout << "\033[34m������Ҫ�����������ţ�\033[0m\n\033[33m";
		int i; cin >> i;
		cout<<"\033[0m";
		if (i < 1 || i > apply_list.size())
		{
			cout << "\033[41;1m����������������룡\033[0m" << endl;
			goto apply_again_choice;
		}
		int result = apply_handle(i);
		if (result == 1)
		{
			return 1;
		}
	}
	
	else return 1;
}
int kaoqinxitong_t()
{
	kaoqinxitong_t_again_choice:
	cout<<"\033[34;4m��ӭʹ�ý�ʦ����ϵͳ��\033[0m"<<endl;
	cout<<"\033[34m��ѡ����Ҫ���еĲ�����\n\t\033[0m\033[32m1.��������\033[0m\n\t\033[36m2.��ѯ����\n\t\033[0m\033[31m3.ɾ������\n\t4.�޸�����\033[0m\033[36m\n\t5.��ѯѧ����Ϣ\n\t6.ѧ�����봦��\n\t7.��������\n\t\033[0m\033[31m8.�˳�ϵͳ\033[0m\033[33m"<<endl;
	int choice; cin >> choice;
	cout << "\033[0m";
	switch (choice)
	{
	case 1:
	{
		int i = kaoqin_send();
		if (i == 1)goto kaoqinxitong_t_again_choice;
	}
	case 2:
	{
		int i = kaoqin_look();
		if (i == 1)goto kaoqinxitong_t_again_choice;
	}
	case 3:
	{
		cout << "\033[34m��������Ҫɾ���Ŀ�����ţ�\033[0m\n\033[33m";
		int num; cin >> num;
		cout << "\033[0m";
		int i = kaoqin_del(num);
		if (i == 1)goto kaoqinxitong_t_again_choice;
	}
	case 4:
	{
		int i = xiugaimima();
		if (i == 1)goto kaoqinxitong_t_again_choice;
	}
	case 5:
	{
		cout << "\033[32m���ڲ�ѯ��...wait for a while...\033[0m\n";
		bar(25);
		cout << "\033[36;4m��ѯ������£�\nѧ����\033[0m\033[36m\n";
		cout << left << setw(30) << "����" << setw(30) << "�˺�" << setw(30) << "����" << setw(30) << "ѧ��" << endl;
		cout<<"\033[0m\033[35m";
		for (auto it = user_s.begin(); it != user_s.end(); it++)
		{
			cout << left << setw(30) << it->name << setw(30) << it->account << setw(30) << it->password << setw(30) << it->id << endl;
		}
		cout << "\033[0m\033[32;4m��ѯ��ɣ�\033[0m" << endl;
		goto kaoqinxitong_t_again_choice;
	}
	case 6:
	{
		int i = apply();
		if (i == 1)goto kaoqinxitong_t_again_choice;
	}
	case 7:
	{
		string gonggao_message;
		cout<<"\033[34;4m�����빫�����ݣ�\033[0m\033[33m"<<endl;
		cin >> gonggao_message;
		message_list.push_back({ teacher_name ,gonggao_message,current_time()});
		cout << "\033[0m\033[32m���ڷ�������...wait for a while...\033[0m" << endl;
		bar(25);
		for (auto it = user_s.begin(); it != user_s.end(); it++)
		{
			it->have_look_message = 0;
		}
		cout << "\033[32;4m�����ɹ���\033[0m" << endl;
		goto kaoqinxitong_t_again_choice;
	}
	case 8:
	{
		cout << "\033[34m��ӭ�´�ʹ�ã�\033[0m" << endl;
		return 1;
	}
	default:
	{
		cout << "\033[41;1m����������������룡\033[0m" << endl;
		goto kaoqinxitong_t_again_choice;
	}
	}
}
int self_kaoqin_s()
{
	for (auto it = user_s.begin(); it != user_s.end(); it++)
	{
		if (it->name == student_name)it->have_look_kaoqin = 1;
	}
	cout << "\033[32m���ڲ�ѯ������Ϣ...wait for a while...\033[0m" << endl;
	bar(25);
	cout << "\033[34;4m������Ϣ���£�\n\033[0m\033[36m";
	cout << left << setw(20) << "������" << setw(20) << "��������" << setw(20) << "���ڵص�" << setw(20) << "���ڽ�ֹʱ��" <<  setw(20) << "����ID\033[0m" <<endl;
	for (auto it = kaoqin_list.begin(); it != kaoqin_list.end(); it++)
	{
		if (it->student_name == "but " + student_name) {  continue; }
		cout << "\033[35m";
		cout << left << setw(20) << it->teacher_name << setw(20) << it->message << setw(20) << it->place << setw(20) << it->time <<   setw(20) << it->id <<  endl;
		cout << "\033[0m";
		kaoqin_map[it->id] ++;
	}
	cout <<left<< "\033[32;4m��ѯ��ɣ�\033[0m" << endl;
	return 1;
	
}
int self_message()
{
	cout<<"\033[32;4m���ڲ�ѯ������Ϣ...wait for a while...\033[0m\n";
	bar(25);
	cout<<"\033[34m�������£�\033[0m\n\033[36m";
	cout<<left<<setw(20)<<"������"<<setw(20)<<"����ʱ��"<<setw(20)<<"��������\033[0m\033[35m"<<endl;
	for (auto it = message_list.begin(); it != message_list.end(); it++)
	{
		cout<<left<<setw(20)<<it->t_name<<setw(20)<<it->time<<setw(20)<<it->neirong<<endl;
	}
	cout<<"\033[0m\033[32;4m��ѯ��ɣ�\033[0m"<<endl;
	for (auto it = user_s.begin(); it != user_s.end(); it++)
	{
		if (it->name == student_name)it->have_look_message = 1;
	}
	return 1;
}
int xiugaimima_s()
{
	int tries = 3;
	cout << "\033[31;4m�������޸��������룡\n������ԭ���룺\033[0m\033[33m" << endl;
	string old_password;
	string t = student_account;
	while (cin >> old_password)
	{
		cout << "\033[0m\033[41;1m������" << tries << "�λ��ᣡ\033[0m" << endl;
		if (user_login_s(t, old_password))
		{
			cout << "\033[32mԭ������ȷ��\033[0m" << endl;
			cout << "\033[31m�����������룺\033[0m\033[33m" << endl;
			string new_password; cin >> new_password;
			user_s[0].password = new_password;
			cout << "\033[0m\033[32m�����޸ĳɹ���\033[0m" << endl;
			return 2;
		}
		else
		{
			cout << "\033[41;1mԭ�������\033[0m" << endl;
			tries--;
			if (tries == 0)
				break;
		}
	}
	cout << "\033[41;1m�����޸�ʧ�ܣ�����ϵ����Ա��\033[0m" << endl;
	return 2;
}
int xiugainfomation_s()
{
	xueshengxinxi_again_choice:
	cout<<"\033[34m��������Ҫ�޸ĵĸ�����Ϣ��\033[0m\033[36m\n\t1.����\n\t2.�˺�\n\t3.ID\n\t\033[0m\033[31m4.�˳�\033[0m\033[33m"<<endl;
	int choice; cin >> choice;
	cout << "\033[0m";
	switch (choice)
	{
	case 1:
	{
		cout << "\033[34m����������������\033[0m\033[33m" << endl;
		string truename; cin >> truename;
		cout << "\033[0m";
		for (auto it = user_s.begin(); it != user_s.end(); it++)
		{
			if (it->name == student_name)
			{
				it->name = truename;
				cout << "\033[32m�����޸ĳɹ���\033[0m" << endl;
				student_name = truename;
				goto xueshengxinxi_again_choice;
			
			}
		}
	}
	case 2:
	{
		cout << "\033[34m�����������˺ţ�\033[0m\033[33m" << endl;
		string trueaccount; cin >> trueaccount	;
		cout << "\033[0m";
		for (auto it = user_s.begin(); it != user_s.end(); it++)
		{
			if (it->name == student_name)
			{
				it->account = trueaccount;
				student_account = trueaccount;
				cout << "\033[32m�˺��޸ĳɹ���\033[0m" << endl;
				
				goto xueshengxinxi_again_choice;

			}
		}
	}
	case 3:
	{
		cout << "\033[34m����������ѧ�ţ�\033[0m\033[33m" << endl;
		int trueid; cin >> trueid;
		cout << "\033[0m";
		for (auto it = user_s.begin(); it != user_s.end(); it++)
		{
			if (it->name == student_name)
			{
				it->id = trueid;
				cout << "\033[32mѧ���޸ĳɹ���\033[0m" << endl;
				goto xueshengxinxi_again_choice;
			}
		}
	}
	case 4:
	{
		return 1;
	}
	default:
	{
		cout << "\033[41;1m����������������룡\033[0m" << endl;
		goto xueshengxinxi_again_choice;
	}
	}
	}
int apply_s()
{
	cout << "\033[34;4m��ӭʹ��ѧ������ϵͳ\033[0m" << endl;
	cout << "\033[34m��������Ҫ�������������ͣ�\033[0m\033[33m" << endl;
	string type; cin >> type;
	cout << "\033[0m\033[34m��������Ҫ�������������ɣ�\033[0m\033[33m" << endl;
	string message; cin >> message;
	apply_list.push_back({student_name,type,current_time(),message,false,false});
	cout << "\033[0m\033[32;4m���ڷ�������...wait for a while...\033[0m" << endl;
	bar(25);
	cout << "\033[32m���뷢���ɹ���\033[0m" << endl;
	return 1;
}
int apply_result()
{
	cout << "\033[32m���ڲ�ѯ������Ϣ...wait for a while...\033[0m" << endl;
	bar(25);
	cout << "\033[34m������Ϣ���£�\n\033[0m\033[36m\n";
	cout << left << setw(15) << "������" << setw(10) << "��������" << setw(30) << "��������" << setw(20) << "����ʱ��" << setw(15) << "������" << endl;
	cout << "\033[0m";
	for (auto it : apply_list)
	{
		
		if (it.name_s == student_name)
		{
			cout << "\033[35m";
			cout << left << setw(15) << it.name_s << setw(10) << it.type << setw(30) << it.message << setw(20) << it.time << setw(15) << (it.finish?(it.pass?"\033[0m\033[32mͨ��\033[0m":"\033[0m\033[31mδͨ��\033[0m"):"\033[0m\033[33mδ����\033[0m") << endl;
			cout << "\033[0m";
		}
		
	}
	return 1;
}
bool finding()
{
	for (auto it : kaoqin_list)
	{
		if (it.student_name == "ȫ��ѧ��")
		{
			return true;
		}
		return false;
	}
}
int have_look()
{
	
	for (auto it : user_s)
	{
		if (it.name == student_name && it.have_look_kaoqin == 0&&finding())
		{
			cout << "\033[34m����û�в鿴��������Ϣ��\033[0m" << endl;
			cout << "\033[34m�Ƿ����̲鿴��\033[34m(\033[0m\033[32my\033[34m\033[0m or \033[31mn\033[0m\033[34m)\033[0m\n\033[33m" << endl;
			string choice; cin >> choice;
			cout << "\033[0m";
			if (choice == "yes" || choice == "Yes" || choice == "YES" || choice == "y" || choice == "Y" || choice == "1")
			{
				int i = self_kaoqin_s();
				if (i == 1)goto kaoqinxitong_s_again_choice;
			}
			else
			{
				goto kaoqinxitong_s_again_choice;
			}

		}
	kaoqinxitong_s_again_choice:
		if (it.name == student_name && it.have_look_message == 0)
		{
			cout << "\033[34m����û�в鿴��������Ϣ��\033[0m" << endl;
			cout << "\033[34m�Ƿ����̲鿴\033[34m(\033[0m\033[32my\033[34m\033[0m or \033[31mn\033[0m\033[34m)\033[0m\n\033[33m" << endl;
			string choice; cin >> choice;
			cout << "\033[0m";
			if (choice == "yes" || choice == "Yes" || choice == "YES" || choice == "y" || choice == "Y" || choice == "1")
			{
				int i = self_message();
				if (i == 1)return 1;
			}
			else
			{
				return 1;
			}
		}
	}
}
int kaoqinxitong_s()
{
	cout<<"\033[45;1m��ӭʹ��ѧ������ϵͳ��\033[0m"<<endl;
	have_look();
kaoqinxitong_s_again_choice:
	cout<<"\033[34m��ѡ����Ҫ���еĲ�����\033[0m\n\t\033[32m1.�鿴����\n\t2.�鿴����\033[0m\n\t\033[31m3.�޸�����\n\t4.�޸ĸ�����Ϣ\033[0m\n\t\033[36m5.��������\n\t6.�鿴��������\n\t\033[0m\033[31m7.�˳�ϵͳ\033[0m\033[33m"<<endl;
	int choice; cin >> choice;
	cout << "\033[0m";
	switch (choice)
	{
	case 1:
	{
		int i = self_kaoqin_s();
		if (i == 1)goto kaoqinxitong_s_again_choice;
		
	}
	case 2:
	{
		int i =self_message();
		if (i == 1)goto kaoqinxitong_s_again_choice;
		
	}
	case 3:
	{
		int i = xiugaimima_s();
		if (i == 2)goto kaoqinxitong_s_again_choice;
		
	}
	case 4:
	{
		int i = xiugainfomation_s();
		cout<<"\033[34m���ݼ�����...wait for a while...\033[0m"<<endl;
		bar(25);
		if (i == 1)goto kaoqinxitong_s_again_choice;
		
	}
	case 5:
	{
		int i = apply_s();
		if (i == 1)goto kaoqinxitong_s_again_choice;
	
	}
	case 6:
	{
		int i = apply_result();
		if (i == 1)goto kaoqinxitong_s_again_choice;
	}
	case 7:
	{
		cout << "\033[34;4m��ӭ�´�ʹ�ã�\033[0m" << endl;
		return 1;
	
	}
	default:
	{
		cout << "\033[41;1m����������������룡\033[0m" << endl;
		goto kaoqinxitong_s_again_choice;
		
	}
	}
}	
int identity_check_s()
{
	int tries = 3;
identity_check_s:
	cout << "\033[41;1m����" << tries << "�λ���\033[0m" << endl;
	cout << "\033[34m�����������˺ţ�\033[0m\033[33m\n";
	string account; cin >> account;
	cout << "\033[0m\033[34m�������������룺\033[0m\033[33m\n";
	string password; cin >> password;
	cout << "\033[0m";
	if (user_login_s(account, password))
	{
		cout << "\033[42;1m�����֤�ɹ���wait for a while...\033[0m" << endl;
		bar(25);
		for (auto it = user_s.begin(); it != user_s.end(); it++)
		{
			if (it->account == account)student_name = it->name, student_account = it->account;
		}
		
		int check = kaoqinxitong_s();
		if (check == 1)return 1;
		
	}
	else
	{
		cout << "\033[41;1m�����֤ʧ�ܣ���������֤���\033[0m" << endl;
		tries--;
		if (tries != 0)
		{
			goto identity_check_s;

		}
		else
		{
			cout << "\033[41;1m�����֤ʧ�ܣ�����ϵ����Ա��" << endl;
			cout << "����������ҳ�棡\033[0m" << endl;
			bar(50);
			return 1;
		}

	}
}
int identity_check_t()
{
	int tries = 3;
identity_check_t:
	cout << "\033[41;1m����" << tries << "�λ���\033[0m" << endl;
	cout << "\033[34m�����������˺ţ�\033[0m\033[33m\n";
	string account;cin>>account;
	cout << "\033[0m\033[34m�������������룺\033[0m\033[33m\n";
	string password;cin>>password;
	cout << "\033[0m";
	if (user_login_t(account, password))
	{
		cout << "\033[42;1m�����֤�ɹ���wait for a while...\033[0m" << endl;
		bar(25);
		for (auto it = user_t.begin(); it != user_t.end(); it++)
		{
			if (it->account == account)teacher_name = it->name;
		}
		int chect = kaoqinxitong_t();
		if (chect == 1)return 1;
	}
	else
	{
		cout<<"\033[41;1m�����֤ʧ�ܣ���������֤���\033[0m"<<endl;
		tries--;
		if (tries != 0)
		{
			goto identity_check_t;
		}
		else
		{
			cout << "\033[41;1m�����֤ʧ�ܣ�����ϵ����Ա��" << endl;
			cout << "����������ҳ�棡\033[0m" << endl;
			bar(25);
			return 1;
		}

	}
}



int main()
{
	cout << "\033[46m";
	cout << "                            \033[35;5m*                                  *    *                                    " << endl;
	cout << "                            *                                  *    *                                    " << endl;
	cout << "                       *************                        ***********                *                 " << endl;
	cout << "                            *      *                           *    *                 *                  " << endl;
	cout << "                            *  *                               ******                 *                  " << endl;
	cout << "                ************************                   *************     *************               " << endl;
	cout << "                           *                               *      *    *             *   *               " << endl;
	cout << "                          *  *********                     *************           *     *               " << endl;
	cout << "                        *    *                                    *                *     *               " << endl;
	cout << "                      *      * *******                     *************         *       *               " << endl;
	cout << "                                      *                           *            *         *               " << endl;
	cout << "                                      *                    *************     *      *    *               " << endl;
	cout << "                                     *                           *                   *  *                " << endl;
	cout << "                                 * **                     *************                 *                " << endl;
	cout << "\033[0m";
	cout << "                                             \033[35;4m�������������\033[0m                                              " << endl;

	srand(static_cast<unsigned int>(time(nullptr)));
identity1:
	cout << "\033[34;4m�ҵ�����ǣ�\033[0m\033[33m";
	string identity; cin >> identity;
	cout << "\033[0m";
	if (identity == "��ʦ" || identity == "teacher" || identity == "Teacher" || identity == "��ʦ"||identity=="����")
	{
		int t3 =identity_check_t();
		if (t3 == 1)
		{
			goto identity1;
		}
	}
	else if (identity == "ѧ��" || identity == "student" || identity == "Student")
	{
		int  t1 =identity_check_s();
		if (t1 == 1)
		{
			goto identity1;
		}
	}
	else if (identity == "laochenzhenshuai")
	{
		int t2 = guanliyuan_check();
		if (t2 == 1)
		{
			goto identity1;
		}
	}
	else
	{
		cout << "\033[41;1m�������������������룡\033[0m" << endl;
		goto identity1;
	}
}

