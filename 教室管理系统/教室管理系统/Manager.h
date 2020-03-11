#pragma once
#include <iostream>
#include <vector>
#include "identity.h"
#include "Student.h"
#include "Teacher.h"
#include "Classroom.h"
using namespace std;


class Manager:public Identity
{
public:
	//默认构造
	Manager();

	//有参构造
	Manager(string id, string passwd, string name);

	//菜单界面
	virtual void openMenu();

	//查看所有预约
	void showAllOrder();


	//添加账号
	void addAccount();

	//查看账号
	void showAccount();

	//清空预约记录
	void clearFile();

	//审核预约
	void review();

	//检测账号重复
	bool checkRepeat(string id);

	//初始化容器
	void initVector();

	//学生容器
	vector<Student>vstu;
	//教师容器
	vector<Teacher>vtea;
	//教室容器
	vector<Classroom>vcla;


};

