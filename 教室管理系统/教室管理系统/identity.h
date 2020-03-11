#pragma once
#include <iostream>
using namespace std;


//底层身份抽象类
class Identity
{
public:
	
	//操作菜单
	virtual void openMenu() = 0;

	//账号
	string id;
	//密码
	string passwd;
	//姓名
	string name;
};