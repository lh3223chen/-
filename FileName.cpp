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
// 存储考勤信息的映射
map<int, int>kaoqin_map;
// 存储所有用户信息的映射
map<int, int>all__map;

// 消息结构体，用于存储消息信息
struct message
{
	string t_name; // 消息发布者姓名
	string neirong; // 消息内容
	string time; // 消息发布时间
};

// 存储消息列表
vector<message>message_list;

string student_account; // 学生账号

// 获取当前时间的函数，返回字符串格式的时间
string current_time()
{
	time_t now = time(nullptr);
	tm* local_time = localtime(&now);
	return to_string(local_time->tm_year + 1900) + "年" + to_string(local_time->tm_mon + 1) + "月" + to_string(local_time->tm_mday) + "日" + to_string(local_time->tm_hour) + ":" + to_string(local_time->tm_min);
}

string teacher_name; // 教师姓名
string student_name; // 学生姓名

// 教师结构体，用于存储教师信息
struct teacher
{
	string name; // 教师姓名
	string account; // 教师账号
	string password; // 教师密码
};

// 学生结构体，用于存储学生信息
struct student
{
	string name; // 学生姓名
	string account; // 学生账号
	string password; // 学生密码
	int id; // 学生ID
	int is_kaoqin; // 是否参与考勤
	int is_message; // 是否有消息
	int is_finish_kaoqin; // 是否完成考勤
	int have_look_message; // 是否查看过消息
	int have_look_kaoqin; // 是否查看过考勤
};

// 申请结构体，用于存储学生申请信息
struct student_apply
{
	string name_s; // 学生姓名
	string type; // 申请类型
	string time; // 申请时间
	string message; // 申请内容
	bool finish; // 是否完成审批
	bool pass; // 审批结果
};

// 存储申请列表
vector<student_apply>apply_list;

// 存储教师用户列表
vector<teacher>user_t;
// 存储学生用户列表
vector<student>user_s;

// 考勤结构体，用于存储考勤信息
struct kaoqin
{
	string message; // 考勤内容
	string time; // 考勤时间
	string place; // 考勤地点
	string teacher_name; // 教师姓名
	int id; // 考勤ID
	string student_name; // 学生姓名
};

// 存储考勤列表
vector<kaoqin>kaoqin_list;
vector<string>student_but_kaoqin; // 存储没有参与考勤的学生
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
	cout<<"\033[34m请选择添加的角色：\033[0m\033[36m\n\t1.学生\n\t2.教师\033[0m\033[33m"<<endl;
	int i; cin >> i; 
	cout << "\033[0m";
	string account, password, name;
	if (i == 1)
	{

		
		cout << "\033[34m请输入添加的姓名：\n\033[0m\033[33m";
		string name; cin >> name;
		cout << "\033[0m\033[34m请输入添加的账号：\n\033[0m\033[33m";
		string account; cin >> account;
		cout << "\033[0m\033[34m请输入添加的密码：\n\033[0m\033[33m";
		string password; cin >> password;
		cout << "\033[0m\033[34m请输入添加的学号：\n\033[0m\033[33m";
		int id; cin >> id;
		user_s.push_back({ name,account,password,id ,0,0,0,1,1 });
		cout << "\033[0m\033[32m添加成功！\033[0m" << endl;
		return 1;
	}

	else if (i == 2)
	{
		
		cout << "\033[34m请输入添加的姓名：\n\033[0m\033[33m";
		cin >> name;
		cout << "\033[0m\033[34m请输入添加的账号：\n\033[0m\033[33m";
		cin >> account;
		cout << "\033[0m\033[34m请输入添加的密码：\n\033[0m\033[33m";
		cin >> password;
		user_t.push_back({ name,account,password });
		cout << "\033[0m\033[32m添加成功！\033[0m" << endl;
		return 1;
	}
	else
	{
		cout << "\033[41;1m输入错误！\033[0m" << endl;
		goto again;
	}
}
int delete_user()
{
	delete_again_choice:
	cout<<"\033[34m请选择删除的角色：\033[0m\033[31m\n\t1.学生\n\t2.教师\033[0m\033[32m\n\t3.退出删除\033[0m"<<endl;
	int i; cin >> i;
	if (i == 1)
	{
		
		cout << "\033[31m请输入删除的姓名：\033[0m\033[33m\n";
		string to_delete_name;
		cin>>to_delete_name;
		cout << "\033[0m";
		for (auto it = user_s.begin(); it != user_s.end(); it++)
		{
			if (it->name == to_delete_name)
			{
				string check;
				cout << "\033[31m确定要删除吗？\033[34m(\033[0m\033[31my\033[34m\033[0m or \033[32mn\033[0m\033[34m)\033[0m\033[35m\n";
				cout<<it->name<<"     "<<it->account<<"     "<<it->password<<"     "<<it->id<<"\n\033[0m\033[33m";
				cin >> check;
				cout << "\033[0m";
				if (check == "y" || check == "Y"||check=="yes"||check=="YES"||check=="是")
				{
					user_s.erase(it);
					cout << "\033[41;4m删除中...wait for a while...\033[0m" << endl;
					bar(25);
					cout << "\033[31m删除成功！\033[0m" << endl;
					return 1;
				}
				else
				{
					cout << "\033[32m取消删除！\033[0m" << endl;
					goto delete_again_choice;
				}
			}
			
		}
		cout << "\033[31;1m没有该学生！\033[0m" << endl;
		goto delete_again_choice;
	}
	else if (i == 2)
	{
		
		cout << "\033[34m请输入删除的姓名：\033[0m\033[33m\n";
		string to_delete_name;
		cin >> to_delete_name;
		cout << "\033[0m";
		for (auto it = user_t.begin(); it != user_t.end(); it++)
		{
			if (it->name == to_delete_name)
			{
				string check;
				cout << "\033[31m确定要删除吗？\033[34m(\033[0m\033[31my\033[34m\033[0m or \033[32mn\033[0m\033[34m)\033[0m\n\033[33m";
				cin >> check;
				cout << "\033[0m";
				if (check == "y" || check == "Y" || check == "yes" || check == "YES" || check == "是")
				{
					user_t.erase(it);
					cout << "\033[41;4m删除中...wait for a while...\033[0m" << endl;
					bar(25);
					cout << "\033[31m删除成功！\033[0m" << endl;

					goto delete_again_choice;
				}
				else
				{
					cout << "\033[32m取消删除！\033[0m" << endl;
					goto delete_again_choice;
				}
			}
			
		}
		cout << "\033[31;1m没有该教师！\033[0m" << endl;
		goto delete_again_choice;
	}
	else if (i == 3)
	{
		return 1;
	}
	else
	{
		cout << "\033[31;1m输入错误！请重新输入！\033[0m" << endl;
		goto delete_again_choice;
	}
}
int modify_user()
{
xiugai_again_choice:
	cout << "\033[34;4m请输入需要修改的账号类型：\033[0m\033[36m\n\t1.学生 \n\t2.教师\n\t\033[0m\033[31m3.退出修改\033[0m\033[33m" << endl;
	int i; cin >> i;
	cout << "\033[0m";
	
	
	if (i == 1)
	{
		cout << "\033[34m请输入需要修改的账号：\033[0m\033[33m\n";
		string account_xiugai; cin >> account_xiugai;
		cout << "\033[0m";
		for (auto it = user_s.begin(); it != user_s.end(); it++)
		{
			if (it->account == account_xiugai)
			{
				cout << "\033[34m请输入修改后的密码：\033[0m\033[33m\n";
				string new_password; cin >> new_password;
				it->password = new_password;
				cout << "\033[0m\033[34m请输入修改后的学号：\033[0m\033[33m\n";
				int new_id; cin >> new_id;
				it->id = new_id;
				cout << "\033[0m\033[32m修改成功！\033[0m" << endl;
				return 1;
			}
			else
			{
				cout << "\033[31m没有该学生！\033[0m\n";
				cout << "\033[34;4m是否重新输入！\033[0m\n\033[33m";
				string check; cin >> check;
				cout << "\033[0m";
				if (check == "yes" || check == "YES" || check == "是")
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
		cout << "\033[34m请输入需要修改的账号：\033[0m\033[33m\n";
		string account_xiugai; cin >> account_xiugai;
		cout << "\033[0m";
		for (auto it = user_t.begin(); it != user_t.end(); it++)
		{
			if (it->account == account_xiugai)
			{
				cout << "\\033[34m请输入修改后的密码：\033[0m\033[33m\n";
				string new_password; cin >> new_password;
				it->password = new_password;
				cout << "\033[0m\033[32m修改成功！\033[0m" << endl;
				return 1;
			}
			else
			{
				cout << "\033[31m没有该教师！\033[0m\n";
				cout<<"\033[34;4m是否重新输入！\033[0m\\033[33m\n";
				string check;cin>>check;
				cout << "\\033[0m";
				if(check=="yes"||check=="YES"||check=="是")
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
		cout << "\033[41;1m输入错误！请重新输入！\033[0m" << endl;
		goto xiugai_again_choice;
	}
}
int query_user()
{
	cout << "\033[32m正在查询中...wait for a while...\033[0m\n";
	bar(25);
	cout << "\033[34;4m查询结果如下：\n\033[0m\033[36;4m学生：\033[0m\n\033[36m";
	cout<<left<<setw(30)<<"姓名"<< setw(30) << "账号"<< setw(30) << "密码"<< setw(30) << "学号\033[0m\033[35m"<<endl;
	for (auto it = user_s.begin(); it != user_s.end(); it++)
	{
		cout <<left << setw(30) << it->name << setw(30) << it->account << setw(30) << it->password << setw(30) << it->id << endl;
	}
	cout << "\033[0m\033[36;4m教师：\n\033[0m";
	cout<<left<<setw(30)<<"\033[36m姓名"<< setw(30) << "     账号"<< setw(30) << "     密码\033[0m\033[35m"<<endl;
	
	for (auto it = user_t.begin(); it != user_t.end(); it++)
	{
		cout <<left << setw(30) <<  it->name << setw(30) <<  it->account << setw(30) << it->password << endl;
	}
	cout << "\033[0m" << endl;
	cout << "\033[32;4m查询完成！\033[0m" << endl;
	return 1;
}
int guanliyuan()
{
	guanliyuan_again_choice:
	cout << "\033[34m请输入编号:\033[0m\n\t\033[32m1.添加用户\033[0m\n\t\033[31m2.删除用户\033[0m\033[36m\n\t3.修改用户\n\t4.查询用户\033[0m\n\t\033[31m5.返回上一级\033[0m\033[33m" << endl;
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
		cout << "\033[41;1m输入错误！请重新输入！\033[0m" << endl;
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
	cout << "\033[34;4m请输入您的密码：\033[0m\033[33m" << endl;;
	string password;cin>>password;
	cout << "\033[0m";
	if (password == "23456789")
	{
		cout << "\033[32m身份验证成功！wait for a while...\033[0m" << endl;
		bar(25);
		int chect_finish = guanliyuan();
		if (chect_finish == 1)return 1;
		
	}
	else
	{
		cout << "\033[41;1m身份验证失败！请重新验证身份" << endl;
		cout << "即将返回主页面！ \033[0m" << endl;
		bar(50);
		return 1;
	}
}
int kaoqin_send()
{
	string message, time, place, finish,name;
	cout << "\033[34m请输入您要发布的考勤信息：\033[0m\033[33m" << endl;
	cin>>message;
	cout << "\033[0m\033[34m请输入考勤截止时间：\033[0m\033[33m" << endl;
	cin>>time;
	cout << "\033[0m\033[34m请输入考勤地点：\033[0m\033[33m\n";
	cin>>place;
	cout << "\033[0m\033[34m是否需要全部学生完成：\033[34m(\033[0m\033[32my\033[34m\033[0m or \033[31mn\033[0m\033[34m)\033[0m\033[33m\n";
	cin>>finish;
	if (finish == "y" || finish == "Y" || finish == "yes" || finish == "YES" || finish == "是")
	{
		string teacher_name_t = teacher_name;
		for (auto it = user_s.begin(); it != user_s.end(); it++)
		{
			it->have_look_kaoqin = 0;
		}
		cout << "\033[32m正在发布考勤信息...wait for a while...\033[0m" << endl;
		int temp = 10000 + rand() % 100000;
		all__map[temp]=user_s.size();
		kaoqin_map[temp] = 0;//计算完成情况
		kaoqin_list.push_back({ message,time,place,teacher_name_t,temp,"全部学生" });
		bar(25);
		cout << "\033[32;1m发布成功！\033[0m" << endl;
		return 1;
	}
	else
	{
		string teacher_name_t = teacher_name;
		kaoqin_send_again:
		cout<<"\033[34m请输入不需要完成的学生姓名：\033[0m\033[33m\n";
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
				cout << "\033[32m正在发布考勤信息...wait for a while...\033[0m" << endl;
				all__map[temp] = user_s.size()-1;
				bar(25);
				cout << "\033[32m发布成功！\033[0m" << endl;
				return 1;
			}
		}
		cout << "\033[41;1m没有该学生！\033[0m" << endl;
		cout<<"\033[34m是否重新输入学生姓名?\033[0m\033[34m(\033[0m\033[31my\033[34m\033[0m or \033[32mn\033[0m\033[34m)\033[0m\n";
		string check;cin>>check;
		if (check == "y" || check == "Y" || check == "yes" || check == "YES" || check == "是")
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
	cout << "\033[32m正在查询考勤信息...wait for a while...\033[0m" << endl;
	bar(25);
	cout << "\033[34m考勤信息如下：\n\033[0m";
	int count = 1;
	cout << left << setw(15) <<"\033[36m序号"<< setw(15) << "     发布人" << setw(15) << "     考勤内容" << setw(15) << "     考勤地点" << setw(15) << "     考勤截止时间" << setw(15) << "   需要参与学生"<<setw(15) << "   考勤ID"<<setw(15)<<"   完成情况\033[0m\033[35m" << endl;
	for (auto it = kaoqin_list.begin(); it != kaoqin_list.end(); it++)
	{	
	cout << left <<setw(15)<<count++<<setw(15)<< it->teacher_name  << setw(15)<<it->message<< setw(15) << it->place << setw(15) << it->time << setw(15) << it->student_name << setw(15) << it->id <<kaoqin_map[it->id]<<"/"<<all__map[it->id]<<endl;
	}
	cout << "\033[0m" ;
	cout << "\033[32;4m查询完成！\033[0m" << endl;
	return 1;
}
int kaoqin_del(int num)
{
	if (num < 1 || num > kaoqin_list.size())
	{
		cout << "\033[41;1m输入错误！\033[0m" << endl;	
		return 1;
	}
	else
	{
		kaoqin_list.erase(kaoqin_list.begin() + num - 1);
		cout << "\033[31;4m正在删除考勤信息...wait for a while...\033[0m" << endl;
		bar(25);
		cout << "\033[32;4m删除成功！\033[0m" << endl;
		return 1;
	
	}
}
int xiugaimima()
{
	xiugai_again_choice:
	cout << "\033[34m请输入需要修改的学生账号：\033[0m\n\033[33m";
	string account_xiugai; cin >> account_xiugai;
	cout << "\033[0m";
	for (auto it = user_s.begin(); it != user_s.end(); it++)
	{
		if (it->account == account_xiugai)
		{
			cout << "\033[32;4m请输入修改后的密码：\033[0m\033[33m\n";
			string new_password; cin >> new_password;
			it->password = new_password;
			cout << "\033[0m\033[32m修改成功！\033[0m" << endl;
			return 1;
		}
		else
		{
			cout << "\033[41;1m没有该学生！\033[0m\n";
			cout << "\033[34m是否重新输入学生账号？\033[0m\033[34m(\033[0m\033[31my\033[34m\033[0m or \033[32mn\033[0m\033[34m)\033[0m\n\033[33m";
			string check; cin >> check;
			cout<<"\033[0m";
			if (check == "y" || check == "Y" || check == "yes" || check == "YES" || check == "是")
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
	cout<<"\033[34m该申请信息如下：\033[0m\n\033[36m";
	cout << left << setw(20)  << "学生姓名" << setw(20) << "申请类型" << setw(20) << "申请时间" << setw(20) << "申请理由\033[0m\033[35m" << setw(20) << endl;
	cout<<left<<setw(20)<<apply_list[i-1].name_s<<setw(20)<<apply_list[i-1].type<<setw(20)<<apply_list[i-1].message<<setw(20)<<apply_list[i-1].time<<endl;
	cout<<"\033[0m\033[34m是否同意该申请？\033[0m\033[34m(\033[0m\033[32my\033[34m\033[0m or \033[31mn\033[0m\033[34m)\033[0m\n\033[33m";
	string result;cin>>result;
	cout << "\033[0m";
	if (result == "y" || result == "Y" || result == "yes" || result == "YES" || result == "是")
	{
		apply_list[i - 1].finish = true;
		cout << "\033[32;4m审批成功！\033[0m" << endl;
		apply_list[i - 1].pass = true;
	}
	else
	{
		apply_list[i - 1].finish = true;
		cout << "\033[31;4m已经驳回！\033[0m" << endl;
		apply_list[i - 1].pass = false	;
	}
	cout<<"\033[34m是否继续处理其他申请？\033[0m\033[34m(\033[0m\033[32my\033[34m\033[0m or \033[31mn\033[0m\033[34m)\033[0m\n\033[33m";
	string check;cin>>check;
	cout << "\033[0m";
	if (check == "y" || check == "Y" || check == "yes" || check == "YES" || check == "是")
	{
		cout << "\033[34m请输入要处理的申请序号：\033[0m\n\033[33m";
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
	cout << "\033[34m学生的申请如下：\033[0m\n\033[36m";
	int count = 1;
	cout<<left<<setw(10)<<"序号"<<setw (20)<< "学生姓名" << setw(20) << "申请类型" << setw(30) << "申请理由" << setw(20) << "申请时间" << setw(20) << "审批状态\033[0m"  << endl;
	cout << "\033[0m";
	cout << "\033[35m";
	for (auto it = apply_list.begin(); it != apply_list.end(); it++)
	{
		
		cout<<left<<setw(10)<<count++<<setw(20)<< it->name_s << setw(20)<< it->type << setw(30)<< it->message << setw(20)<< it->time << setw(20)<< (it->finish ? "\033[0m\033[32m已审批\033[0m" : "\033[31m未审批\033[0m\033[35m") << endl;
	}
	cout << "\033[0m";
	apply_again_choice:
	cout<<"\033[0m\033[34;4m是否开始处理\033[34m(\033[0m\033[32my\033[34m\033[0m or \033[31mn\033[0m\033[34m)\033[0m\033[33m" << endl;
	string check; cin >> check;
	cout << "\033[0m";
	if (check == "y" || check == "Y" || check == "yes" || check == "YES" || check == "是")
	{
		cout << "\033[34m请输入要处理的申请序号：\033[0m\n\033[33m";
		int i; cin >> i;
		cout<<"\033[0m";
		if (i < 1 || i > apply_list.size())
		{
			cout << "\033[41;1m输入错误！请重新输入！\033[0m" << endl;
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
	cout<<"\033[34;4m欢迎使用教师考勤系统！\033[0m"<<endl;
	cout<<"\033[34m请选择您要进行的操作：\n\t\033[0m\033[32m1.发布考勤\033[0m\n\t\033[36m2.查询考勤\n\t\033[0m\033[31m3.删除考勤\n\t4.修改密码\033[0m\033[36m\n\t5.查询学生信息\n\t6.学生申请处理\n\t7.发布公告\n\t\033[0m\033[31m8.退出系统\033[0m\033[33m"<<endl;
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
		cout << "\033[34m请输入需要删除的考勤序号：\033[0m\n\033[33m";
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
		cout << "\033[32m正在查询中...wait for a while...\033[0m\n";
		bar(25);
		cout << "\033[36;4m查询结果如下：\n学生：\033[0m\033[36m\n";
		cout << left << setw(30) << "姓名" << setw(30) << "账号" << setw(30) << "密码" << setw(30) << "学号" << endl;
		cout<<"\033[0m\033[35m";
		for (auto it = user_s.begin(); it != user_s.end(); it++)
		{
			cout << left << setw(30) << it->name << setw(30) << it->account << setw(30) << it->password << setw(30) << it->id << endl;
		}
		cout << "\033[0m\033[32;4m查询完成！\033[0m" << endl;
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
		cout<<"\033[34;4m请输入公告内容：\033[0m\033[33m"<<endl;
		cin >> gonggao_message;
		message_list.push_back({ teacher_name ,gonggao_message,current_time()});
		cout << "\033[0m\033[32m正在发布公告...wait for a while...\033[0m" << endl;
		bar(25);
		for (auto it = user_s.begin(); it != user_s.end(); it++)
		{
			it->have_look_message = 0;
		}
		cout << "\033[32;4m发布成功！\033[0m" << endl;
		goto kaoqinxitong_t_again_choice;
	}
	case 8:
	{
		cout << "\033[34m欢迎下次使用！\033[0m" << endl;
		return 1;
	}
	default:
	{
		cout << "\033[41;1m输入错误！请重新输入！\033[0m" << endl;
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
	cout << "\033[32m正在查询考勤信息...wait for a while...\033[0m" << endl;
	bar(25);
	cout << "\033[34;4m考勤信息如下：\n\033[0m\033[36m";
	cout << left << setw(20) << "发布人" << setw(20) << "考勤内容" << setw(20) << "考勤地点" << setw(20) << "考勤截止时间" <<  setw(20) << "考勤ID\033[0m" <<endl;
	for (auto it = kaoqin_list.begin(); it != kaoqin_list.end(); it++)
	{
		if (it->student_name == "but " + student_name) {  continue; }
		cout << "\033[35m";
		cout << left << setw(20) << it->teacher_name << setw(20) << it->message << setw(20) << it->place << setw(20) << it->time <<   setw(20) << it->id <<  endl;
		cout << "\033[0m";
		kaoqin_map[it->id] ++;
	}
	cout <<left<< "\033[32;4m查询完成！\033[0m" << endl;
	return 1;
	
}
int self_message()
{
	cout<<"\033[32;4m正在查询公告信息...wait for a while...\033[0m\n";
	bar(25);
	cout<<"\033[34m公告如下：\033[0m\n\033[36m";
	cout<<left<<setw(20)<<"发布人"<<setw(20)<<"发布时间"<<setw(20)<<"公告内容\033[0m\033[35m"<<endl;
	for (auto it = message_list.begin(); it != message_list.end(); it++)
	{
		cout<<left<<setw(20)<<it->t_name<<setw(20)<<it->time<<setw(20)<<it->neirong<<endl;
	}
	cout<<"\033[0m\033[32;4m查询完成！\033[0m"<<endl;
	for (auto it = user_s.begin(); it != user_s.end(); it++)
	{
		if (it->name == student_name)it->have_look_message = 1;
	}
	return 1;
}
int xiugaimima_s()
{
	int tries = 3;
	cout << "\033[31;4m您正在修改您的密码！\n请输入原密码：\033[0m\033[33m" << endl;
	string old_password;
	string t = student_account;
	while (cin >> old_password)
	{
		cout << "\033[0m\033[41;1m您还有" << tries << "次机会！\033[0m" << endl;
		if (user_login_s(t, old_password))
		{
			cout << "\033[32m原密码正确！\033[0m" << endl;
			cout << "\033[31m请输入新密码：\033[0m\033[33m" << endl;
			string new_password; cin >> new_password;
			user_s[0].password = new_password;
			cout << "\033[0m\033[32m密码修改成功！\033[0m" << endl;
			return 2;
		}
		else
		{
			cout << "\033[41;1m原密码错误！\033[0m" << endl;
			tries--;
			if (tries == 0)
				break;
		}
	}
	cout << "\033[41;1m密码修改失败！请联系管理员！\033[0m" << endl;
	return 2;
}
int xiugainfomation_s()
{
	xueshengxinxi_again_choice:
	cout<<"\033[34m请输入您要修改的个人信息：\033[0m\033[36m\n\t1.姓名\n\t2.账号\n\t3.ID\n\t\033[0m\033[31m4.退出\033[0m\033[33m"<<endl;
	int choice; cin >> choice;
	cout << "\033[0m";
	switch (choice)
	{
	case 1:
	{
		cout << "\033[34m请输入您的姓名：\033[0m\033[33m" << endl;
		string truename; cin >> truename;
		cout << "\033[0m";
		for (auto it = user_s.begin(); it != user_s.end(); it++)
		{
			if (it->name == student_name)
			{
				it->name = truename;
				cout << "\033[32m姓名修改成功！\033[0m" << endl;
				student_name = truename;
				goto xueshengxinxi_again_choice;
			
			}
		}
	}
	case 2:
	{
		cout << "\033[34m请输入您的账号：\033[0m\033[33m" << endl;
		string trueaccount; cin >> trueaccount	;
		cout << "\033[0m";
		for (auto it = user_s.begin(); it != user_s.end(); it++)
		{
			if (it->name == student_name)
			{
				it->account = trueaccount;
				student_account = trueaccount;
				cout << "\033[32m账号修改成功！\033[0m" << endl;
				
				goto xueshengxinxi_again_choice;

			}
		}
	}
	case 3:
	{
		cout << "\033[34m请输入您的学号：\033[0m\033[33m" << endl;
		int trueid; cin >> trueid;
		cout << "\033[0m";
		for (auto it = user_s.begin(); it != user_s.end(); it++)
		{
			if (it->name == student_name)
			{
				it->id = trueid;
				cout << "\033[32m学号修改成功！\033[0m" << endl;
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
		cout << "\033[41;1m输入错误！请重新输入！\033[0m" << endl;
		goto xueshengxinxi_again_choice;
	}
	}
	}
int apply_s()
{
	cout << "\033[34;4m欢迎使用学生申请系统\033[0m" << endl;
	cout << "\033[34m请输入您要发布的申请类型：\033[0m\033[33m" << endl;
	string type; cin >> type;
	cout << "\033[0m\033[34m请输入您要发布的申请理由：\033[0m\033[33m" << endl;
	string message; cin >> message;
	apply_list.push_back({student_name,type,current_time(),message,false,false});
	cout << "\033[0m\033[32;4m正在发布申请...wait for a while...\033[0m" << endl;
	bar(25);
	cout << "\033[32m申请发布成功！\033[0m" << endl;
	return 1;
}
int apply_result()
{
	cout << "\033[32m正在查询申请信息...wait for a while...\033[0m" << endl;
	bar(25);
	cout << "\033[34m申请信息如下：\n\033[0m\033[36m\n";
	cout << left << setw(15) << "申请人" << setw(10) << "申请类型" << setw(30) << "申请理由" << setw(20) << "申请时间" << setw(15) << "处理结果" << endl;
	cout << "\033[0m";
	for (auto it : apply_list)
	{
		
		if (it.name_s == student_name)
		{
			cout << "\033[35m";
			cout << left << setw(15) << it.name_s << setw(10) << it.type << setw(30) << it.message << setw(20) << it.time << setw(15) << (it.finish?(it.pass?"\033[0m\033[32m通过\033[0m":"\033[0m\033[31m未通过\033[0m"):"\033[0m\033[33m未处理\033[0m") << endl;
			cout << "\033[0m";
		}
		
	}
	return 1;
}
bool finding()
{
	for (auto it : kaoqin_list)
	{
		if (it.student_name == "全部学生")
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
			cout << "\033[34m您还没有查看过考勤信息！\033[0m" << endl;
			cout << "\033[34m是否立刻查看？\033[34m(\033[0m\033[32my\033[34m\033[0m or \033[31mn\033[0m\033[34m)\033[0m\n\033[33m" << endl;
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
			cout << "\033[34m您还没有查看过公告信息！\033[0m" << endl;
			cout << "\033[34m是否立刻查看\033[34m(\033[0m\033[32my\033[34m\033[0m or \033[31mn\033[0m\033[34m)\033[0m\n\033[33m" << endl;
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
	cout<<"\033[45;1m欢迎使用学生考勤系统！\033[0m"<<endl;
	have_look();
kaoqinxitong_s_again_choice:
	cout<<"\033[34m请选择您要进行的操作：\033[0m\n\t\033[32m1.查看考勤\n\t2.查看公告\033[0m\n\t\033[31m3.修改密码\n\t4.修改个人信息\033[0m\n\t\033[36m5.发布申请\n\t6.查看个人申请\n\t\033[0m\033[31m7.退出系统\033[0m\033[33m"<<endl;
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
		cout<<"\033[34m数据加载中...wait for a while...\033[0m"<<endl;
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
		cout << "\033[34;4m欢迎下次使用！\033[0m" << endl;
		return 1;
	
	}
	default:
	{
		cout << "\033[41;1m输入错误！请重新输入！\033[0m" << endl;
		goto kaoqinxitong_s_again_choice;
		
	}
	}
}	
int identity_check_s()
{
	int tries = 3;
identity_check_s:
	cout << "\033[41;1m还有" << tries << "次机会\033[0m" << endl;
	cout << "\033[34m请输入您的账号：\033[0m\033[33m\n";
	string account; cin >> account;
	cout << "\033[0m\033[34m请输入您的密码：\033[0m\033[33m\n";
	string password; cin >> password;
	cout << "\033[0m";
	if (user_login_s(account, password))
	{
		cout << "\033[42;1m身份验证成功！wait for a while...\033[0m" << endl;
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
		cout << "\033[41;1m身份验证失败！请重新验证身份\033[0m" << endl;
		tries--;
		if (tries != 0)
		{
			goto identity_check_s;

		}
		else
		{
			cout << "\033[41;1m身份验证失败！请联系管理员！" << endl;
			cout << "即将返回主页面！\033[0m" << endl;
			bar(50);
			return 1;
		}

	}
}
int identity_check_t()
{
	int tries = 3;
identity_check_t:
	cout << "\033[41;1m还有" << tries << "次机会\033[0m" << endl;
	cout << "\033[34m请输入您的账号：\033[0m\033[33m\n";
	string account;cin>>account;
	cout << "\033[0m\033[34m请输入您的密码：\033[0m\033[33m\n";
	string password;cin>>password;
	cout << "\033[0m";
	if (user_login_t(account, password))
	{
		cout << "\033[42;1m身份验证成功！wait for a while...\033[0m" << endl;
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
		cout<<"\033[41;1m身份验证失败！请重新验证身份\033[0m"<<endl;
		tries--;
		if (tries != 0)
		{
			goto identity_check_t;
		}
		else
		{
			cout << "\033[41;1m身份验证失败！请联系管理员！" << endl;
			cout << "即将返回主页面！\033[0m" << endl;
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
	cout << "                                             \033[35;4m告诉我您的身份\033[0m                                              " << endl;

	srand(static_cast<unsigned int>(time(nullptr)));
identity1:
	cout << "\033[34;4m我的身份是：\033[0m\033[33m";
	string identity; cin >> identity;
	cout << "\033[0m";
	if (identity == "老师" || identity == "teacher" || identity == "Teacher" || identity == "教师"||identity=="先生")
	{
		int t3 =identity_check_t();
		if (t3 == 1)
		{
			goto identity1;
		}
	}
	else if (identity == "学生" || identity == "student" || identity == "Student")
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
		cout << "\033[41;1m身份输入错误，请重新输入！\033[0m" << endl;
		goto identity1;
	}
}

