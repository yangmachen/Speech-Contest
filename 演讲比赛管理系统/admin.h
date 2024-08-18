#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include "player.h"

using namespace std;


class Admin
{
public:
    Admin();

    ~Admin();

    // 显示菜单
    void showMenu();
    // 退出系统
    void exitSystem();
    // 初始化
    void initSysytem();
    // 创建选手
    void createPlayers();
    // 开始比赛
    void startSpeechContest();
    // 抽签
    void playerDraw();
    // 打分
    void giveScore();
    // 显示胜者
    void showWiner();
    // 保存胜者
    void save();




    // 第一轮选手
    vector<int> v1;
    // 第二轮选手
    vector<int> v2;
    // 最后的胜利者 冠亚季
    vector<int> vVictor;

    // 存储选手信息
    map<int, Player> m_players;

    // 轮数
    int m_index;

};