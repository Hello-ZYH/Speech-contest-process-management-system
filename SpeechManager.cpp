#include"SpeechManager.h"


//构造函数
SpeechManager::SpeechManager()
{
	//初始化容器和属性
	this->initSpeech();

	//创建12名选手
	this->createrSpeaker();
}


//菜单功能
void SpeechManager::show_Menu()
{
	cout << "************************************************" << endl;
	cout << "**************  欢迎参加演讲比赛  **************" << endl;
	cout << "***************  1.开始演讲比赛  ***************" << endl;
	cout << "***************  2.查看往届记录  ***************" << endl;
	cout << "***************  3.清空比赛记录  ***************" << endl;
	cout << "***************  0.退出比赛程序  ***************" << endl;
	cout << "************************************************" << endl;
	cout << endl;
}


//退出功能
void SpeechManager::exitSystem()
{
	cout << "欢迎您下次使用" << endl;
	system("pause");
	exit(0);
}


//初始化容器和属性
void SpeechManager::initSpeech()
{
	//容器都置空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Sperker.clear();

	//初始化比赛轮数
	this->m_Index = 1;
}


//创建12名选手
void SpeechManager::createrSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];

		//创建具体选手
		Speaker sp;
		sp.m_Name = name;

		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}

		//创建选手编号，并且放入到v1容器中
		this->v1.push_back(i + 10001);

		//将选手编号以及对应选手放入到map容器中
		this->m_Sperker.insert(make_pair(i + 10001, sp));
	}
}


//开始比赛（整个比赛流程控制函数）
void SpeechManager::startSpeech()
{
	//第一轮开始比赛

	//1、抽签
	this->speechDraw();

	//2、比赛
	this->speechContest();

	//3、显示晋级结果
	this->showScore();

	//4、第二轮开始比赛
	this->m_Index++;

	//1、抽签
	this->speechDraw();

	//2、比赛
	this->speechContest();

	//3、显示最终结果
	this->showScore();

	//4、保存分数到文件中
	this->saveRecord();

	cout << "本届比赛完毕！" << endl;

	system("pause");
	system("cls");
}


//抽签
void SpeechManager::speechDraw()
{
	cout << "第 << " << this->m_Index << " >>" << " 轮比赛的选手正在抽签" << endl;
	cout << "-----------------------------------------------------------------------" << endl;
	cout << "抽签后的演讲顺序如下；" << endl;

	if (m_Index == 1)
	{
		//第一轮比赛
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}

		cout << endl;
		cout << "-----------------------------------------------------------------------" << endl;
		system("pause");
		cout << endl;
	}
	else
	{
		//第二轮比赛
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}

		cout << endl;
		cout << "-----------------------------------------------------------------------" << endl;
		system("pause");
		cout << endl;
	}
}


//比赛
void SpeechManager::speechContest()
{
	cout << "-------------第" << this->m_Index << "轮比赛正式开始-------------" << endl;

	//准备临时容器，存放小组成绩
	multimap<double, int, greater<double>>groupScore;

	//记录人员个数，6人一组
	int num = 0;

	//比赛选手容器
	vector<int>v_Src;
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//遍历所有选手进行比赛
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;

		//评委打分
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;      //600~1000

			//测试输出
			//cout << score << " ";
			d.push_back(score);
		}
		//cout << endl;

		//排序
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();   //去除最高分
		d.pop_back();	 //去除最低分

		//总分
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		//平均分
		double avg = sum / (double)d.size();

		//测试打印平均分
		//cout << "编号：" << *it << "   姓名：" << this->m_Sperker[*it].m_Name << "   平均分：" << avg << endl;

		//将平均分放入到map容器中
		this->m_Sperker[*it].m_Score[m_Index - 1] = avg;

		//将打分数据放入到临时容器中
		groupScore.insert(make_pair(avg, *it));   //key是得分，value是具体选手编号

		//每6人取出前三名
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号：" << it->second << "   姓名：" << this->m_Sperker[it->second].m_Name << "   成绩：" << this->m_Sperker[it->second].m_Score[this->m_Index - 1] << endl;
			}

			//取走前三名
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{ 
				if (this->m_Index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}
			}

			//小组容器清空
			groupScore.clear();
			cout << endl;
		}
	}
	cout << "---------------第" << this->m_Index << "轮比赛完毕---------------" << endl;
	system("pause");
}


//显示得分
void SpeechManager::showScore()
{
	cout << "-------------第" << this->m_Index << "轮晋级的选手信息如下：-------------" << endl;

	vector<int>v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号：" << *it << "   姓名：" << this->m_Sperker[*it].m_Name << "   分数：" << this->m_Sperker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
//	this->show_Menu();
}


//保存记录
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);   //用app追加的方式写文件

	//将每个选手的数据写入到文件中
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Sperker[*it].m_Score[1] << ",";
	}
	ofs << endl;

	ofs.close();
	cout << "记录已经保存" << endl;
}


//读取记录
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);   //读文件

	//文件不存在
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	//文件存在但为空
	char ch;
	ifs >> ch;

	if (ifs.eof())
	{
		cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件存在且不为空
	this->fileIsEmpty = false;

	ifs.putback(ch);   //将上面读取的单个字符放回来

	string data;
	int index = 0;

	while (ifs >> data)
	{
		//cout << data << endl;

		vector<string>v;   //存放6个string字符串
		int pos = -1;   //查到“，”位置的变量
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				//没有找到
				break;
			}

			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			v.push_back(temp);
			start = pos + 1;
		}

		this->m_Record.insert(make_pair(index, v));
		index++;
	}

	ifs.close();

	//for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
	//{
	//	cout << it->first << "冠军编号：" << it->second[0] << "   分数：" << it->second[1] << endl;
	//}
}


//显示往届记录
void SpeechManager:: showRecord()
{
	for (int i = 0; i < this->m_Record.size(); i++)
	{
		cout << "第" << i + 1 << "届" << endl
				<< "冠军编号：" << this->m_Record[i][0] << "   得分：" << this->m_Record[0][1] << endl
				<< "亚军编号：" << this->m_Record[i][2] << "   得分：" << this->m_Record[0][3] << endl
				<< "季军编号：" << this->m_Record[i][4] << "   得分：" << this->m_Record[0][5] << endl << endl;
	}

	system("pause");
	system("cls");
}


//清空文件
void SpeechManager::clearRecord()
{
	cout << "是否确定清空文件" << endl;
	cout << "1、是" << endl;
	cout << "2、否" << endl;

	int select = 0;

	cin >> select;

	if (select == 1)
	{
		//确认清空
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//初始化容器和属性
		this->initSpeech();

		//创建12名选手
		this->createrSpeaker();

		//加载往届记录
		this->loadRecord();

		cout << "清空成功！" << endl;
	}

	system("pause");
	system("cls");
}


//析构函数
SpeechManager::~SpeechManager()
{

}