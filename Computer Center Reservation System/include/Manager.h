#pragma once
#include "Identity.h"
#include "Student.h"
#include"Teacher.h"
#include<algorithm>
#include <ComputerRoom.h>
class Manager : public Identity
{
public:
    Manager();

    Manager(string name, string pwd);

    //菜单界面
    virtual  void operMenu();

    // 添加账号
    void addPerson();

    // 查看账号
    void showPerson();

    // 查看机房信息
    void showComputer();

    //清空预约记录
    void cleanFile();

    //初始化容器
    void initVector();
  
    //去重检测
    bool checkRepeat(int id,int type);

    //学生容器
    vector<Student> vStu;

    //教师容器
    vector<Teacher> vTea;

    //机房容器
    vector<ComputerRoom> vCom;

    
};