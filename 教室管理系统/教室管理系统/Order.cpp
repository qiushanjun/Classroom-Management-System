#include "Order.h"


//默认构造
Order::Order()
{
	ifstream ifs;
	ifs.open(ORDER_FILR,ios::in);

	//日期、时间段、预约人、教室、状态
	string date, interval, name, room, status;

	this->size = 0;

	//获取每条记录
	while (ifs >> name && ifs >> date && ifs >> interval && ifs >> room && ifs >> status)
	{
		//截取name
		string key, value;
		map<string, string>m;
		int pos = name.find(":");
		if (pos != -1) {
			key = name.substr(0, pos);
			value = name.substr(pos + 1, -1);

			m.insert(make_pair(key, value));
		}

		//截取date
	    pos = date.find(":");
		if (pos != -1) {
			key = date.substr(0, pos);
			value = date.substr(pos + 1, -1);

			m.insert(make_pair(key, value));
		}


		//截取interval
		pos = interval.find(":");
		if (pos != -1) {
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, -1);

			m.insert(make_pair(key, value));
		}

		//截取room
		pos = room.find(":");
		if (pos != -1) {
			key = room.substr(0, pos);
			value = room.substr(pos + 1, -1);

			m.insert(make_pair(key, value));
		}

		//截取status
		pos = status.find(":");
		if (pos != -1) {
			key = status.substr(0, pos);
			value = status.substr(pos + 1, -1);

			m.insert(make_pair(key, value));
		}

		//将小map放入大map
		this->m_orderData.insert(make_pair(this->size, m));
		this->size++;
		

	}
	ifs.close();
	
	

}

//更新预约记录
void Order::updateorder()
{
	//无记录
	if (this->size == 0)
	{
		return;
	}

	ofstream ofs(ORDER_FILR, ios::out | ios::trunc);
	for (int i = 0; i < this->size; i++)
	{
		ofs << "name:" << this->m_orderData[i]["name"] << " ";
		ofs << "date:" << this->m_orderData[i]["date"] << " ";
		ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
		ofs << "room:" << this->m_orderData[i]["room"] << " ";
		ofs << "status:" << this->m_orderData[i]["status"] << endl;
	}
	ofs.close();

}

