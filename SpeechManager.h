#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<deque>
#include<algorithm>
#include<functional>
#include<numeric>
#include<fstream>
#include"Speaker.h"
using namespace std;


//设计演讲比赛管理类
class SpeechManager
{
public:
	//构造函数
	SpeechManager();

	//菜单功能
	void show_Menu();

	//退出功能
	void exitSystem();

	//析构函数
	~SpeechManager();

	//初始化容器和属性
	void initSpeech();

	//创建12名选手
	void createrSpeaker();

	//开始比赛（整个比赛流程控制函数）
	void startSpeech();

	//抽签
	void speechDraw();

	//比赛
	void speechContest();

	//显示得分
	void showScore();

	//保存记录
	void saveRecord();

	//读取记录
	void loadRecord();

	//显示往届记录
	void showRecord();

	//清空文件
	void clearRecord();

	//判断文件是否为空
	bool fileIsEmpty;

	//存放往届记录的容器
	map<int, vector<string>>m_Record;

	//成员属性
	//保存第一轮比赛选手编号的容器
	vector<int>v1;

	//第一轮晋级选手编号的容器
	vector<int>v2;

	//胜出的前三名选手编号的容器
	vector<int>vVictory;

	//存放编号以及对应具体选手的容器
	map<int, Speaker>m_Sperker;

	//存放比赛的轮数
	int m_Index;
};
