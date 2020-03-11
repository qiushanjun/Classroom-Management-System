#include "Teacher.h"
#include "Order.h"
#include "Classroom.h"


//默认构造
Teacher::Teacher()
{
}

//有参构造
Teacher::Teacher(string id, string passwd, string name)
{
	//初始化
	this->id = id;
	this->name = name;
	this->passwd = passwd;


	//获取教室信息
	ifstream ifs;
	ifs.open(CLASSROOM_FILE, ios::in);

	Classroom c;
	while (ifs >> c.c_name&& ifs >> c.num)
	{
		vcla.push_back(c);
	}
	ifs.close();

}

//菜单界面
void Teacher::openMenu()
{
	cout << endl << endl << endl;
	cout << "-----------------------------" << this->name << "老师------------------------" << endl;
	cout << endl << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|        1、申请预约              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|        2、查看我的预约          |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|        3、查看所有预约          |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|        4、取消预约              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|        5、注销登录              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t ---------------------------------\n";
}

//申请预约
void Teacher::applyOrder()
{
	cout << "预约开放时间为每周周六日" << endl;
	cout << "预约时间为下周周一到周五" << endl;
	cout << "请输入申请预约的时间：" << endl;
	cout << "1、周一" << endl;
	cout << "2、周二" << endl;
	cout << "3、周三" << endl;
	cout << "4、周四" << endl;
	cout << "5、周五" << endl;

	int date = 0;            //日期
	int interval = 0;        //时间段
	string room = "";            //教室

	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "日期输入有误，请重新输入" << endl;
	}

	cout << "请输入申请预约的时间段：" << endl;
	cout << "1、上午第一节课" << endl;
	cout << "2、上午第二节课" << endl;
	cout << "3、下午第一节课" << endl;
	cout << "4、下午第二节课" << endl;
	cout << "5、晚上第一节课" << endl;
	cout << "6、晚上第二节课" << endl;

	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 6)
		{
			break;
		}
		cout << "时间段输入有误，请重新输入" << endl;
	}


	for (int i = 0; i < vcla.size(); i++)
	{
		cout << vcla[i].c_name << "教室可预约，可容纳" << vcla[i].num << "人" << endl;
	}

	cout << "请选择教室";
	while (true) {
		cin >> room;
		if (room == "旧教105" || room == "旧教106" || room == "旧教107" || room == "旧教108" || room == "旧教205" || room == "旧教206" || room == "旧教207" || room == "旧教208" || room == "旧教309" || room == "旧教310" || room == "旧教311" || room == "旧教312" || room == "新平一" || room == "新平二" || room == "新平三" || room == "新平四" || room == "电一" || room == "电二" || room == "电六")
		{
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}


	cout << "预约成功,审核中" << endl;

	ofstream ofs;
	ofs.open(ORDER_FILR, ios::app);

	ofs << "name:" << this->name << " ";
	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "room:" << room << " ";
	ofs << "status:" << 1 << endl;

	ofs.close();
	system("pause");
	system("cls");


}

//查看自身预约
void Teacher::showSelf()
{
	Order order;
	if (order.size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < order.size; i++)
	{
		if (this->name == order.m_orderData[i]["name"])
		{
			cout << "预约日期：周" << order.m_orderData[i]["date"];
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

	system("pause");
	system("cls");
}

//查看所有预约
void Teacher::showAllOrder()
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

//取消预约
void Teacher::canceOrder()
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

	cout << "审核中或预约成功的记录可以取消，请输入取消的记录" << endl;

	vector<int>v;         //存放在最大容器中的下标编号
	int index = 1;
	for (int i = 0; i < order.size; i++)
	{
		if (this->name == order.m_orderData[i]["name"])
		{
			if (order.m_orderData[i]["status"] == "1" || order.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "、";
				cout << "  预约日期：周" << order.m_orderData[i]["date"];
				cout << "  时间段：第" << order.m_orderData[i]["interval"] << "节课";
				cout << "  教室：" << order.m_orderData[i]["room"];

				string status = "状态：";
				if (order.m_orderData[i]["status"] == "1")
				{
					status += "审核中";
				}
				else if (order.m_orderData[i]["status"] == "2")
				{
					status += "预约成功";
				}
				cout << status << endl;
			}
		}
	}
	cout << "请输入取消的记录，0可以返回：";
	int select = 0;
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
				//v[select-1]：第几个存进去的数据，正好和v的下标-1对应
				order.m_orderData[v[select - 1]]["status"] = 4;
				order.updateorder();

				cout << "已取消预约" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入" << endl;

	}
	system("pause");
	system("cls");

}