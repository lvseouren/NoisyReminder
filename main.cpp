#include<iostream>
#include<Windows.h>
#include<Winuser.h>
#include<shellapi.h>
#include<time.h>

#include"Itime.h"

using std::cin;
using std::cout;
using std::endl;

Itime GetCurrentITime()//�ŵ�time.h��ȥ
{
	time_t now;
	time(&now);
	struct tm* t = new tm();
	localtime_s(t,&now);
	return Itime(t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
}
void StartShake();

void main(void)
{
	//TODO:���������ʱ���Ϊ���û�����
	cout<<"����������ʱ�䣨��ʽΪ hour��minute��second������ʽ����ҿɲ����𣡣�:"<<endl;
	string remindTimeStr;
	cin>>remindTimeStr;

	//Itime BeginRemindTime(0,0,0,20,35,0);
	Itime BeginRemindTime = StrConvertToItime(remindTimeStr);

	cout<<"���趨�ĵ��ʱ����:"<<BeginRemindTime<<endl;

	Itime timeBeforeSleep;
	Itime timeWakeup;
	int secToSleep=0;
	bool sleeped = false;
	string remindEatStr = "���";
	string remindGoHomeStr = "�ؼ�";
	
	cout<<"�𼱣����ڿ��ű��أ���ʱ�����һ�������"<<remindEatStr<<"��."<<endl;
	while(1)
	{
		timeWakeup = GetCurrentITime();
		if(sleeped&&secToSleep!=0)
		{
			cout<<"��˯���ˣ�����ʱ���ǣ�"<<timeWakeup<<endl;
		}
		Itime currentTime = GetCurrentITime();
		if(currentTime > BeginRemindTime)
		{
			cout<<"������������������������ҡ����ҡҡҡ��"<<endl;
			StartShake();
			cout<<"ע�⵽�����˰ɣ����ȣ����������Ȼһ������㣡"<<endl;
			Sleep(5000);
			cout<<"ʲô����Ȼ��ûע�⵽�ң�����ҡҡҡ��"<<endl;
			StartShake();
			ShellExecute(NULL,L"open",L"http://www.meican.com/corps/idreamsky/",NULL,NULL,SW_SHOWMAXIMIZED);
			break;
		}
		else//�������ʱ�仹���ã��ó�����sleepһ��ʱ�䡣
		{
			secToSleep = (BeginRemindTime -currentTime).ItimeToSecond();
			secToSleep -= 2;//��ǰ��������
			if(secToSleep<0)
			{
				secToSleep = 0;//��ֹʱ��С��0
			}
			timeBeforeSleep = currentTime;
			if(secToSleep!=0)
			{
				cout<<"����ʱ���ǣ�"<<timeBeforeSleep<<endl;
				cout<<"��"<<remindEatStr<<"ʱ�仹�е�Զ������˯"<<secToSleep<<"��"<<endl;
			}
			Sleep(secToSleep*1000);
			sleeped = true;
		}
	}
	cout<<"������ɣ��ǵ�"<<remindEatStr<<"���ҹ��ˡ�"<<endl;
	
	//TODO���ȴ�2s���ر�
	Sleep(2000);
}
void StartShake()
{
    srand((unsigned)time(NULL));
    int sysX,sysY;
    sysX=GetSystemMetrics(SM_CXSCREEN);//�����Ļ���
    sysY=GetSystemMetrics(SM_CYSCREEN);//�����Ļ�߶�
	Itime t1= GetCurrentITime();
    while(1)
    {
        HWND hWnd=GetDesktopWindow();//���������
        for(hWnd=GetWindow(hWnd,GW_CHILD);hWnd;hWnd=GetWindow(hWnd,GW_HWNDNEXT))
        {           
            RECT rect;
             
            long style=GetWindowLong(hWnd,GWL_STYLE);//��ô�������
            if(style&WS_VISIBLE)//���ڿ���
            {           
                GetWindowRect(hWnd,&rect);//��ô��ھ�������
                int posX,posY,cX,cY;
                bool flag=!(rand()%2);
                 
                cX=rect.right-rect.left;
                cY=rect.bottom-rect.top;
 
				int shaker = 10;
                //�����´�������
                if(flag)
                {
                    posX=rect.left+rand()%shaker*5;
                    posY=rect.top+rand()%shaker*5;
                }               
                else
                {
                    posX=rect.left-rand()%shaker*5;
                    posY=rect.top-rand()%shaker*5;
                }
                 
                //�߾��ж�
                if(posX<0)    posX=0;
                if(posY<0)    posY=0;
                if(posX+cX>sysX)
                    posX=sysX-cX;
                if(posY+cY>sysY)
                    posY=sysY-cY;
 
                //���ô���λ��
                SetWindowPos(hWnd,HWND_NOTOPMOST,posX,posY,rect.right-rect.left,
                    rect.bottom-rect.top,SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOACTIVATE );
            }
        }
		Itime t2=GetCurrentITime();
		if((t2-t1).ItimeToSecond()>5)
		{
			break;
		}
    }
}