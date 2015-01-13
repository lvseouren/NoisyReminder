#include"Itime.h"

Itime::Itime(int y,int m,int d,int hour,int min,int sec):year(y),month(m),day(d),hour(hour),minute(min),second(sec)
{
}
Itime::Itime()
{}
Itime Itime::operator-(const Itime& rhs)
{
	int year_differ = year-rhs.year;
	int mon_differ = month-rhs.month;
	int day_differ = (day-rhs.day);
	int hour_differ = (hour-rhs.hour);
	int min_differ = (minute-rhs.minute);
	int sec_differ = second-rhs.second;
	return Itime(year_differ,mon_differ,day_differ,hour_differ,min_differ,sec_differ);
}
bool Itime::operator>(const Itime&rhs)
{
	Itime differ = *this-rhs;
	if(differ.hour>0)
	{
		return true;
	}
	else if(differ.hour == 0)
	{
		if(differ.minute > 0)
		{
			return true;
		}
		else if(differ.minute == 0)
		{
			return differ.second>0?true:false;
		}
		else//hour = 0,minute<0
		{
			return false;
		}
	}
	//hour<0
	return false;


		

}
int Itime::ItimeToSecond()
{
	bool yun_year = false;
	if(year%400==0)
		yun_year = true;
	else if(year%4==0 && year%100!=0)
		yun_year = true;
	//todo:����µ�����ת���÷�������ۣ��ݲ�����
	//int year_sec = yun_year?31622400*year:31536000*year;
	//int mon_sec = 
	//int day_sec = day*86400;
	int hour_sec = hour*3600;
	int min_sec = minute*60;
	int result = hour_sec+min_sec+second;
	return result;
}
string Itime::ItimeToString()
{
	string result;

	char TimeSecStr[128];
	char TimeMinStr[128];
	char TimeHourStr[128];
	sprintf_s(TimeSecStr,"%d",second);
	sprintf_s(TimeMinStr,"%d",minute);
	sprintf_s(TimeHourStr,"%d",hour);

	result = TimeHourStr+string(":")+TimeMinStr+string(":")+TimeSecStr;
	return result;
}

string Itime::ItimeLenToString()
{
	//����ʱ��
	if(hour<0)
	{
		hour+=24;
	}
	if(minute<0)
	{
		--hour;
		minute+=60;
	}
	if(second<0)
	{
		--minute;
		second+=60;
	}

	string result;

	char TimeSecStr[128];
	char TimeMinStr[128];
	char TimeHourStr[128];
	sprintf_s(TimeSecStr,"%d",second);
	sprintf_s(TimeMinStr,"%d",minute);
	sprintf_s(TimeHourStr,"%d",hour);

	result =string("����") + TimeHourStr+string("h")+TimeMinStr+string("m")+TimeSecStr+string("s");
	return result;
}

string Itime::ItimeToFileString()
{
	string result;

	char TimeYearStr[128];
	char TimeMonthStr[128];
	char TimeDayStr[128];
	sprintf_s(TimeYearStr,"%d",year);
	sprintf_s(TimeMonthStr,"%d",month);
	sprintf_s(TimeDayStr,"%d",day);

	result = TimeYearStr+string("��")+TimeMonthStr+string("��")+TimeDayStr+string("��.txt");
	return result;
}


ostream& operator<<(ostream& os,Itime time)
{
	os<<time.hour<<":"<<time.minute<<":"<<time.second;
	return os;
}

Itime StrConvertToItime(const string&timeStr)
{
	int startHour;
	int endHour;
	int startMin;
	int endMin;
	int startSec;
	int endSec;

	//�����㷨��ǰ����,':'ֻռ��һ���ַ��ĳ���
	string test = ":";
	int lengh = test.length();

	startHour = 0;
	endHour = timeStr.find(':');

	startMin = endHour+1;
	endMin = timeStr.rfind(':')-1;

	startSec = endMin+2;
	endSec = timeStr.length()-1;

	string hourStr = timeStr.substr(startHour,endHour);
	string minStr = timeStr.substr(startMin,endMin);
	string secStr = timeStr.substr(startSec,endSec);

	int hour = atoi(hourStr.c_str());
	int min = atoi(minStr.c_str());
	int sec = atoi(secStr.c_str());

	return Itime(0,0,0,hour,min,sec);
}