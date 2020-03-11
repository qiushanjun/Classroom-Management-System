#pragma once
#include <iostream>
#include <vector>
#include "identity.h"
#include "Order.h"
#include "Classroom.h"
using namespace std;

class Student:public Identity
{
public:
	//默认构造
	Student();
	
	//有参构造
	Student(string id, string passwd, string name);

	//菜单界面
	virtual void openMenu();

	//申请预约
	void applyOrder();

	//查看自身预约
	void showSelf();

	//查看所有预约
	void showAllOrder();

	//取消预约
	void canceOrder();

	//学生姓名
	string name;

	//教室容器
	vector<Classroom>vcla;

	//预约容器
	vector<Order>vorder;
};

