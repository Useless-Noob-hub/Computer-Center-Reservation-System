#pragma once
#include "Identity.h"

class Teacher : public Identity
{
public:
    Teacher();

    Teacher(int EmpId, string name, string pwd);

    // 菜单
    virtual void operMenu();



    // 查看所有预约
    void showAllOrder();

    // 审核预约
    void validOrder();


    int m_EmpId;

};