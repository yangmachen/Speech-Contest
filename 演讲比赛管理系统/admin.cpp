#include "admin.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <functional>
#include <fstream>

#define FILENAME "winner.csv"

using namespace std;

Admin::Admin()
{
    this->initSysytem();
    this->createPlayers();
}

Admin::~Admin()
{

}

void Admin::showMenu()
{
    cout << "------------------------------------" << endl;
    cout << "------欢迎使用演讲比赛管理系统------" << endl;
    cout << "-----------1 开始演讲比赛-----------" << endl;
    cout << "-----------2 查看往届记录-----------" << endl;
    cout << "-----------3 清空比赛记录-----------" << endl;
    cout << "-----------0 退出演讲比赛-----------" << endl;
    cout << "------------------------------------" << endl;
    cout << endl;
    
}

void Admin::exitSystem()
{
    cout << "欢迎下次使用！" << endl;
    system("read -s -n1 -p 'Press any key to continue...\n' key");
    exit(0);
}

void Admin::initSysytem()
{
    this->v1.clear();
    this->v2.clear();
    this->vVictor.clear();
    this->m_players.clear();

    this->m_index = 1;
    
}

void Admin::createPlayers()
{
    // 创建十二名
    string nameSeed = "ABCDEFGHIJKL";
    for(int i = 0; i < nameSeed.size(); i++)
    {
        string name = "选手";
        name += nameSeed[i];
        // 创建选手
        Player ply;
        ply.m_Name = name;
        // 两个成绩初始化为零
        for(int j = 0; j < 2; j++)
        {
            ply.score[j] = 0;
        }
        int id = 10001 + i;
        this->v1.push_back(id);
        this->m_players.insert(make_pair(id, ply));
    }
}

void Admin::playerDraw()
{
    vector<int> v_Src;
    if(this->m_index == 1)
    {
        v_Src = v1;
    }
    else
    {
        v_Src = v2;
    }

    // 开始抽签
    random_shuffle(v_Src.begin(), v_Src.end());
    // 显示抽签结果
    cout << "第 << " << this->m_index << " >> 轮的抽签结果如下:" << endl;
    for(vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
    {
        cout << (*it) << " ";
    }
    cout << endl;
    system("read -s -n1 -p 'Press any key to continue...\n' key");
}

void Admin::giveScore()
{
    // 存储小组得分
    multimap<double, int, greater<double>> groudScore;
    cout << "选手得分情况如下：" << endl;
    vector<int> v_Src;
    if(this->m_index == 1)
    {
        v_Src = this->v1;
    }
    else
    {
        v_Src = this->v2;
    }
    // 遍历每一位选手
    int num = 1;
    for(vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++, num++)
    {
        deque<double> myScore;
        // 评委打分
        for(int i = 0; i < 10; i++)
        {
            double score = (rand() % 401 + 600) / 10.f;
            // cout << score << " ";
            myScore.push_back(score);
        }
        // cout << endl;
        // 去最高最低分
        sort(myScore.begin(), myScore.end(), greater<double>());
        myScore.pop_back();
        myScore.pop_front();
        // 求平均分
        double sum = accumulate(myScore.begin(), myScore.end(), 0.0f);
        double avg = sum / (double)myScore.size();
        // 写入选手记录
        this->m_players[(*it)].score[this->m_index - 1] = avg;
        // 加入到小组中
        groudScore.insert(make_pair(avg, (*it)));
        if(num % 6 == 0)
        {
            cout << "----------------第 " << num / 6 << " 组选手的得分为：------------" << endl;
            for(auto it = groudScore.begin(); it != groudScore.end(); it++)
            {
                cout << "选手编号：" << (*it).second << "\t选手姓名：" << this->m_players[(*it).second].m_Name
                    << "\t选手得分：" << (*it).first << endl;
            }
            // 选出前三名
            int count = 0;
            for(auto it = groudScore.begin(); it != groudScore.end() && count < 3; it++, count++)
            {
                if(this->m_index == 1)
                {
                    this->v2.push_back((*it).second);
                }   
                else
                {
                    this->vVictor.push_back((*it).second);
                }             
            }
            // 清空小组
            groudScore.clear();
            myScore.clear();
        }
    }
    system("read -s -n1 -p 'Press any key to continue...\n' key");
}

void Admin::showWiner()
{
    cout << "第 " << this->m_index << " 轮晋级选手如下：" << endl;
    vector<int> v_Src;
    if(this->m_index == 1)
    {
        v_Src = this->v2;
    }
    else
    {
        v_Src = this->vVictor;
    }
    for(auto it = v_Src.begin(); it != v_Src.end(); it++)
    {
        cout << "选手编号：" << (*it) << "\t选手姓名：" << this->m_players[(*it)].m_Name
                    << "\t选手得分：" << this->m_players[(*it)].score[this->m_index - 1] << endl;
    }
    cout << endl;
    system("read -s -n1 -p 'Press any key to continue...\n' key");

}

void Admin::save()
{
    // 打开文件
    ofstream ofs;
    ofs.open(FILENAME, ios::out | ios::app);
    // 写入
    for(auto it = this->vVictor.begin(); it != this->vVictor.end(); it++)
    {
        ofs << (*it) << "," << this->m_players[(*it)].score[1] << ",";
    }
    ofs << endl;
    ofs.close();
}


void Admin::startSpeechContest()
{
    // 第一轮抽签
    this->playerDraw();
    // 开始比赛
    this->giveScore();
    // 显示晋级
    this->showWiner();
    this->m_index++;

    // 第二轮抽签
    this->playerDraw();
    // 开始比赛
    this->giveScore();
    // 显示获胜者
    this->showWiner();
    // 保存胜者
    this->save();

    // 初始化
    this->initSysytem();
    this->createPlayers();
}
