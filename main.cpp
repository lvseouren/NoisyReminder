#include<iostream>
#include<Windows.h>
#include<Winuser.h>
#include<shellapi.h>
#include<time.h>

#include"Itime.h"

using std::cin;
using std::cout;
using std::endl;

//start global
const Itime dayTime(0,0,0,24,0,0);
//end global
Itime GetCurrentITime()//放到time.h中去
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
	//TODO:将点餐提醒时间改为由用户设置
	//cout<<"请输入提醒时间（格式为 hour：minute：second——格式输错我可不负责！）:"<<endl;
	//string remindTimeStr;
	//cin>>remindTimeStr;
	
	//为了程序只要运行一次就不用再管，时间写死
	//TODO:软件运行时发现时间超过16:30:0，则将明天的16:30：0作为点餐提醒时间。

	Itime BeginRemindTime(0,0,0,10,30,0);
	/*Itime BeginRemindTime = StrConvertToItime(remindTimeStr);*/

	cout<<"你设定的点餐时间是:"<<BeginRemindTime<<endl;

	Itime timeBeforeSleep;
	Itime timeWakeup;
	int secToSleep=0;
	bool sleeped = false;
	string remindEatStr = "点餐";
	string remindGoHomeStr = "回家";
	bool today = false;
	
	cout<<"别担心，我在看着表呢！到时间了我会提醒你"<<remindEatStr<<"的."<<endl;
	while(1)
	{
		timeWakeup = GetCurrentITime();
		if(sleeped&&secToSleep!=0)
		{
			cout<<"我睡醒了，现在时间是："<<timeWakeup<<endl;
		}
		Itime currentTime = GetCurrentITime();
		if(currentTime > BeginRemindTime && today)
		{
			cout<<"点餐啦，点餐啦，听不见？我摇，我摇摇摇！"<<endl;
			StartShake();
			cout<<"注意到了我了吧！逗比，点餐啦，不然一会饿死你！"<<endl;
			Sleep(5000);
			cout<<"什么，居然还没注意到我！我再摇摇摇！"<<endl;
			StartShake();
			ShellExecute(NULL,L"open",L"http://www.meican.com/corps/idreamsky/",NULL,NULL,SW_SHOWMAXIMIZED);
			//重新打开软件进行明天的点餐
			//TODO:测试无误之后将打开方式设为SW_HIDE ，即隐藏，后台运行
			ShellExecute( NULL, L"open",/* L"explorer.exe",*/ L"C:\\Users\\asus\\Documents\\visual studio 2012\\Projects\\点餐提醒者\\Debug\\点餐提醒者.exe", NULL,NULL, SW_SHOWMAXIMIZED ); 
			break;
		}
		else//算出离点餐时间还差多久，让程序先sleep一段时间。
		{
			secToSleep = (BeginRemindTime -currentTime).ItimeToSecond();
			Itime sleepTime = BeginRemindTime -currentTime;
			secToSleep -= 2;//提前两秒醒来
			if(secToSleep<0)
			{
				secToSleep = 0;//防止时间小于0
			}
			timeBeforeSleep = currentTime;
			if(secToSleep!=0)
			{
				cout<<"现在时间是 "<<timeBeforeSleep<<endl;
				cout<<"离"<<remindEatStr<<"时间还有点远，我先睡"<<sleepTime.ItimeLenToString()<<"醒了叫你"<<endl;
			}
			Sleep(secToSleep*1000);
			sleeped = true;
			today = true;
		}
	}
	cout<<"任务完成，记得"<<remindEatStr<<"，我滚了。"<<endl;
	
	//TODO：等待2s，关闭
	Sleep(2000);
}
void StartShake()
{
    srand((unsigned)time(NULL));
    int sysX,sysY;
    sysX=GetSystemMetrics(SM_CXSCREEN);//获得屏幕宽度
    sysY=GetSystemMetrics(SM_CYSCREEN);//获得屏幕高度
	Itime t1= GetCurrentITime();
    while(1)
    {
        HWND hWnd=GetDesktopWindow();//获得桌面句柄
        for(hWnd=GetWindow(hWnd,GW_CHILD);hWnd;hWnd=GetWindow(hWnd,GW_HWNDNEXT))
        {           
            RECT rect;
             
            long style=GetWindowLong(hWnd,GWL_STYLE);//获得窗口类型
            if(style&WS_VISIBLE)//窗口可视
            {           
                GetWindowRect(hWnd,&rect);//获得窗口矩形坐标
                int posX,posY,cX,cY;
                bool flag=!(rand()%2);
                 
                cX=rect.right-rect.left;
                cY=rect.bottom-rect.top;
 
				int shaker = 10;
                //生成新窗口坐标
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
                 
                //边境判断
                if(posX<0)    posX=0;
                if(posY<0)    posY=0;
                if(posX+cX>sysX)
                    posX=sysX-cX;
                if(posY+cY>sysY)
                    posY=sysY-cY;
 
                //设置窗口位置
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