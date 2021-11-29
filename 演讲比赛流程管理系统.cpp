#include"SpeechManager.h"
#include<iostream>
#include<ctime>
using namespace std;


int main()
{
	//随机数种子
	srand((unsigned int)time(NULL));

	//测试12名选手的创建
	//for (map<int, Speaker>::iterator it = sm.m_Sperker.begin(); it != sm.m_Sperker.end(); it++)
	//{
	//	cout << "选手编号：" << it->first << "   姓名：" << it->second.m_Name << "   分数：" << it->second.m_Score[0] << endl;
	//}

	int choice = 0;   //用于存储用户的输入

	while (true)
	{
		//创建管理类对象
		SpeechManager sm;

		sm.show_Menu();

		cout << "请输入您的选择：" << endl;
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case 1:   //开始比赛
			sm.startSpeech();
			break;

		case 2:   //查看往届比赛记录
			//加载往届记录
			sm.loadRecord();

			sm.showRecord();
			break;

		case 3:   //清空比赛记录
			sm.clearRecord();
			break;

		case 0:   //退出系统
			sm.exitSystem();
			break;

		default:
			system("cls");   //清屏
			break;
		}
	} 

	system("pause");

	return 0;
}