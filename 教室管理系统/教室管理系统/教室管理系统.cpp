/*
1、教室预约系统：
	提供给海洋学院学生老师教室信息，方便同学们开会或者自习

2、身份简介:
	学生班长    学号、姓名、密码
	教师		学号、姓名、密码
	管理员		学号、密码

3、教室简介
	旧教教室--容量55人
	新平教室--容量110人
	电教室  --容量300人

4、申请简介
	
	学生或老师可以预约未来一周机房使用，预约日期为周一至周五，预约需要选择时间段（上午1，上午2，下午1，下午2，晚1，晚2）
	管理员来审核预约，通过或不通过

5、系统需求
	首先是登录界面
	用户名、密码

	学生具体功能
		申请预约
		查看自身的预约
		查看所有预约
		取消预约
	教师具体功能
		申请预约
		查看自身的预约
		查看所有预约
		取消预约
	管理员具体功能
		添加账号
		查看账号
		查看教师
		清空预约

6、管理员账号：
	admin 
	root

*/

#include <algorithm>
#include <iostream>
#include <string>
#include <ctype.h>
#include <fstream>
#include <cstdlib>
#include "Student.h"
#include "Teacher.h"
#include"Manager.h"
#include "identity.h"
#include "globalfile.h"
using namespace std;

//进入教师子菜单
void teacherMenu(Identity*& student)
{
	while (true)
	{
		//调用教师子菜单
		student->openMenu();
		cout << "请选择您的操作" << endl;

		//person只能调用公共内容，转成子类
		Student* stu = (Student*)student;



		int select = 0;

		cin >> select;
		if (select == 1)
		{
			//申请预约
			cout << "申请预约" << endl;
			stu->applyOrder();
		}
		else if (select == 2)
		{
			//查看自己的预约
			cout << "查看自己的预约" << endl;
			stu->showSelf();
		}
		else if (select == 3)
		{
			//查看所有预约
			cout << "查看所有预约" << endl;
			stu->showAllOrder();
		}
		else if (select == 4)
		{
			//取消预约
			//cout << "取消预约" << endl;
			stu->canceOrder();
		}
		else
		{
			//注销
			delete student;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}


	}
}

//进入学生子菜单
void studentMenu(Identity*& student)
{
	while (true)
	{
		//调用学生子菜单
		student->openMenu();
		cout << "请选择您的操作" << endl;

		//person只能调用公共内容，转成子类
		Student* stu = (Student*)student;



		int select = 0;

		cin >> select;
		if (select == 1)
		{
			//申请预约
			cout << "申请预约" << endl;
			stu->applyOrder();
		}
		else if (select == 2)
		{
			//查看自己的预约
			cout << "查看自己的预约" << endl;
			stu->showSelf();
		}
		else if (select == 3)
		{
			//查看所有预约
			cout << "查看所有预约" << endl;
			stu->showAllOrder();
		}
		else if (select == 4)
		{
			//取消预约
			//cout << "取消预约" << endl;
			stu->canceOrder();
		}
		else
		{
			//注销
			delete student;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}


	}
}




//进入管理员子菜单
void managerMenu(Identity*& manager)
{
	while (true)
	{
		//调用openMenu
		manager->openMenu();
		cout << "请选择您的操作" << endl;

		//person只能调用公共内容，转成子类
		Manager* man = (Manager*)manager;
		

		int select=0;

		cin >> select;
		if (select == 1)
		{
			//添加账号
			cout << "添加账号" << endl;
			man->addAccount();
		}
		else if (select == 2)
		{
			//查看账号
			cout << "查看账号" << endl;
			man->showAccount();
		}
		else if (select == 3)
		{
			//查看预约
			cout << "查看预约" << endl;
			man->showAllOrder();
		}
		else if(select == 4)
		{	
			//清空预约
			//cout << "清空预约" << endl;
			man->clearFile();
		}
		else if (select == 5)
		{
			man->review();
		}
		else 
		{
			//注销
			delete manager;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
		
		

	}
}



//登录功能
void Login(string filename, string id,int type)
{
	//多态指针
	Identity* person = NULL;

	//读文件
	ifstream ifs;
	ifs.open(filename, ios::in);

	//判断文件是否存在
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		return;
	}

	//准备接受用户输入的密码
	string  passwd;

	//判断身份
	cout << "请输入密码：";
	cin >> passwd;

	string fId;                    //从文件中读取的id号
	string fName;				//从文件中获取的姓名
	string fPwd;				//从文件中获取的密码
	
	while (ifs>>fId && ifs>>fName && ifs>>fPwd)
	{
		
		//对比账号密码
		if (fId == id && fPwd == passwd)
		{
			cout << "登录成功" << endl;
			system("pause");
			system("cls");
			if (type == 5)                  //登录的是管理员
			{
				person = new Manager(id,passwd,fName);
				//进入管理员身份的子菜单
				managerMenu(person);
			}
			else if (type==6)               //登录的是老师
			{
				person = new Teacher(id, passwd, fName);
				//进入老师身份的子菜单
				teacherMenu(person);
			}
			else                            //登录的是学生
			{
				person = new Student(id,passwd,fName);
				//进入学生身份的子菜单
				studentMenu(person);
			}
			
			return;
			
		}
	}
	ifs.close();
	system("pause");
}

void PrintIndex()
{
	cout << endl << endl << endl;
	cout << "---------------------欢迎来到海洋学院教室预约系统-------------------------" << endl;
	cout << endl << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|   在账号处输入quit退出系统      |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t ---------------------------------\n";
}

int main()
{
	bool quit=true;
	while (quit)
	{
		system("cls");
		PrintIndex();

		//账号和密码
		string id, passwd;
		cout << "请输入您的账号:";
		cin >> id;
		if (id == "quit")
		{
			quit = false;
		}
		else
		{
			int type = id.length();
			if (type == 5 || type == 13 || type == 6)
			{
				Login(ACCOUNT_FILE, id,type);
			}
			else
			{
				cout << "账号输入错误，请重新输入!";
				system("pause");
				
			}


		}
	}



	system("pause");
	return 0;
}