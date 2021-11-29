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


//����ݽ�����������
class SpeechManager
{
public:
	//���캯��
	SpeechManager();

	//�˵�����
	void show_Menu();

	//�˳�����
	void exitSystem();

	//��������
	~SpeechManager();

	//��ʼ������������
	void initSpeech();

	//����12��ѡ��
	void createrSpeaker();

	//��ʼ�����������������̿��ƺ�����
	void startSpeech();

	//��ǩ
	void speechDraw();

	//����
	void speechContest();

	//��ʾ�÷�
	void showScore();

	//�����¼
	void saveRecord();

	//��ȡ��¼
	void loadRecord();

	//��ʾ�����¼
	void showRecord();

	//����ļ�
	void clearRecord();

	//�ж��ļ��Ƿ�Ϊ��
	bool fileIsEmpty;

	//��������¼������
	map<int, vector<string>>m_Record;

	//��Ա����
	//�����һ�ֱ���ѡ�ֱ�ŵ�����
	vector<int>v1;

	//��һ�ֽ���ѡ�ֱ�ŵ�����
	vector<int>v2;

	//ʤ����ǰ����ѡ�ֱ�ŵ�����
	vector<int>vVictory;

	//��ű���Լ���Ӧ����ѡ�ֵ�����
	map<int, Speaker>m_Sperker;

	//��ű���������
	int m_Index;
};
