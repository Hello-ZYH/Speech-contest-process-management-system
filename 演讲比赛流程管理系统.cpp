#include"SpeechManager.h"
#include<iostream>
#include<ctime>
using namespace std;


int main()
{
	//���������
	srand((unsigned int)time(NULL));

	//����12��ѡ�ֵĴ���
	//for (map<int, Speaker>::iterator it = sm.m_Sperker.begin(); it != sm.m_Sperker.end(); it++)
	//{
	//	cout << "ѡ�ֱ�ţ�" << it->first << "   ������" << it->second.m_Name << "   ������" << it->second.m_Score[0] << endl;
	//}

	int choice = 0;   //���ڴ洢�û�������

	while (true)
	{
		//�������������
		SpeechManager sm;

		sm.show_Menu();

		cout << "����������ѡ��" << endl;
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case 1:   //��ʼ����
			sm.startSpeech();
			break;

		case 2:   //�鿴���������¼
			//���������¼
			sm.loadRecord();

			sm.showRecord();
			break;

		case 3:   //��ձ�����¼
			sm.clearRecord();
			break;

		case 0:   //�˳�ϵͳ
			sm.exitSystem();
			break;

		default:
			system("cls");   //����
			break;
		}
	} 

	system("pause");

	return 0;
}