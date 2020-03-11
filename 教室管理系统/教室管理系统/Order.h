#pragma once
#include <string>
#include <iostream>
#include "globalfile.h"
#include <fstream>
#include <map>
#include <string>

using namespace std;


class Order
{
public:
	//默认构造
	Order();
	
	//更新预约记录
	void updateorder();


	//预约条数
	int size=0;

	//记录所有预约的容器  int为第几条，map为键值对信息
	map<int, map<string, string>>m_orderData;


};

