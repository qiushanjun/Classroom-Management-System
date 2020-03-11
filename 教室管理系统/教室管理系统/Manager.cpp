#include "Manager.h"
#include <iostream>
#include <fstream>
#include "globalfile.h"
#include <algorithm>

//用于showAccount回调
void printStudent(Student& s)
{
	cout << "学号：" << s.id << "     姓名：" << s.name << "    密码：" << s.passwd << endl;
}
void printTeacher(Teacher& t)
{
	cout << "工号：" << t.id << "     姓名：" << t.name << "    密码：" <<t.passwd << endl;
}
void printClassroom(Classroom& c)
{
	cout << "名称：" << c.c_name << "     能容纳人数：" << c.num <<  endl;
}


//默认构造
Manager::Manager()
{
}


//有参构造
Manager::Manager(string id, string passwd, string name)
{
	this->id = id;
	this->passwd = passwd;
	this->name = name;

	//初始化容器
	this->initVector();


}

//菜单界面
void Manager::openMenu()
{
	cout << endl << endl << endl;
	cout << "-----------------------------管理员："<<this->name<<"------------------------" << endl;
	cout << endl << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|        1、添加账号              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|        2、查看账号              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|        3、查看预约              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|        4、清空预约              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|        5、审核预约              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|        6、注销登录              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t ---------------------------------\n";
}

//查看所有预约
void Manager::showAllOrder()
{
	Order order;

	//无记录时
	if (order.size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < order.size; i++)
	{
		cout << i + 1 << "、";
		cout << "预约人：" << order.m_orderData[i]["name"];
		cout << "  预约日期：周" << order.m_orderData[i]["date"];
		cout << "  时间段：第" << order.m_orderData[i]["interval"] << "节课";
		cout << "  教室：" << order.m_orderData[i]["room"];
		string status = "状态：";
		//1、审核中 2、已预约	3、预约失败	4、取消预约

		if (order.m_orderData[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (order.m_orderData[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (order.m_orderData[i]["status"] == "3")
		{
			status += "预约失败，审核为通过";
		}
		else
		{
			status += "预约已取消";
		}
		cout << status << endl;



	}
}


//添加账号
void Manager::addAccount()
{
	ofstream ofs;
	ofs.open(ACCOUNT_FILE, ios::out | ios::app);   //写文件+追加
	string id;
	string name;
	string passwd;
	cout << "请输入账号" << endl;
	
	//检测重复账号
	while (true)
	{
		cin >> id;
		if (id == "q")
		{
			return;
		}
		bool repeat=checkRepeat(id);
		if (repeat)
		{
			cout << "账号已存在" << endl;
		}
		else
		{
			break;
		}
		cout << "请重新输入账号，输入q退出" << endl;

	}

	int type = id.length();
	if ( type == 13 || type == 6)
	{
		cout << "请输入姓名" << endl;
		cin >> name;
		cout << "请输入密码" << endl;
		cin >> passwd;

		ofs << id << " " << name << " " << passwd << " " << endl;
		
		ofs.close();
		this->initVector();
		cout << "添加成功" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "账号格式错误" << endl;
		cout << "学生请输入13位学号" << endl;
		cout << "教室请输入6位职工号" << endl;
	}

}

//查看账号
void Manager::showAccount()
{
	cout << "请选择查看内容：" << endl;
	cout << "1、查看所有学生" << endl;
	cout << "2、查看所有老师" << endl;
	cout << "3、查看所有教室" << endl;

	int select = 0;
	cin >> select;
	if (select == 1)
	{
		cout << "所有学生信息如下:" << endl;
		for_each(vstu.begin(), vstu.end(), printStudent);

	}
	else if(select==2)
	{
		cout << "所有老师信息如下：" << endl;
		for_each(vtea.begin(), vtea.end(), printTeacher);
	}
	else
	{
		cout << "所有教室信息如下：" << endl;
		for_each(vcla.begin(), vcla.end(), printClassroom);
	}
	system("pause");
	system("cls");
}

//清空预约记录
void Manager::clearFile()
{
	ofstream ofs(ORDER_FILR, ios::trunc);         //覆盖存在的文件
	ofs.close();

	cout << "清空成功" << endl;
	system("pause");
	system("cls");
}


void Manager::initVector()
{
	ifstream ifs;
	ifs.open(ACCOUNT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}
	vstu.clear();
	vtea.clear();
	
	Student s;
	Teacher t;
	Classroom c;
	
	//读取全部学生信息
	while (ifs >> s.id&& ifs >> s.name&& ifs >> s.passwd)
	{
		if(s.id.length()==13)
		{
			vstu.push_back(s);
		}
	}
	cout << "当前学生数量:" << vstu.size() << endl;
	ifs.close();


	//读取全部教师信息
	ifs.open(ACCOUNT_FILE, ios::in);
	while (ifs >> t.id&& ifs >> t.name&& ifs >> t.passwd)
	{
		if (t.id.length() == 6)
		{
			vtea.push_back(t);
		}
	}
	cout << "当前教师数量:" << vtea.size() << endl;
	ifs.close();

	//读取全部教室信息
	ifs.open(CLASSROOM_FILE, ios::in);
	while (ifs >> c.c_name&& ifs >> c.num)
	{
		vcla.push_back(c);
	}
	cout << "当前教室数量:" << vcla.size() << endl;
	ifs.close();
}

bool Manager::checkRepeat(string id)
{
	int type = id.length();
	if (type == 13)
	{
		//检测学生
		for (vector<Student>::iterator it = vstu.begin(); it != vstu.end(); it++)
		{
			if (id == it->id)
			{
				return true;
			}
		}

	}
	else 
	{
		//检测老师
		for (vector<Teacher>::iterator it = vtea.begin(); it != vtea.end(); it++)
		{
			if (id == it->id)
			{
				return true;
			}
		}
	}
	return false;
}


void Manager::review()
{
	Order order;

	//无记录时
	if (order.size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "待审核的预约记录如下：" << endl;

	vector<int>v;        
	int index = 1;
	for (int i = 0; i < order.size; i++)
	{
		if (order.m_orderData[i]["status"]=="1")
		{
			v.push_back(i);
			cout << index++ << "、";
			cout << "申请人：" << order.m_orderData[i]["name"];
			cout << "  预约日期：周" << order.m_orderData[i]["date"];
			cout << "  时间段：第" << order.m_orderData[i]["interval"] << "节课";
			cout << "  教室：" << order.m_orderData[i]["room"];

			string status = "状态：";
			if (order.m_orderData[i]["status"] == "1")
			{
				status += "审核中";
			}
			cout << status << endl;
		}
	}
	cout << "请输入审核的预约记录，0可以返回：";
	int select = 0;
	int ret = 0;

	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				cout << "请输入审核结果：" << endl;
				cout << "1、通过" << endl;
				cout << "2、不通过" << endl;
				cin >> ret;

				if (ret == 1)
				{
					order.m_orderData[v[select - 1]]["status"] = "2";
				}
				else
				{
					order.m_orderData[v[select - 1]]["status"] = "3";
				}
				order.updateorder();
				cout << "审核完毕" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入" << endl;
	}

	system("pause");
	system("cls");
}