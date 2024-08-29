#include "Teacher.h"
#include "OrderFile.h"

Teacher::Teacher()
{
}

Teacher::Teacher(int EmpId, string name, string pwd)
{
    //初始化属性
    this->m_EmpId=EmpId;
    this->m_Name=name;
    this->m_Pwd=pwd;

}

void Teacher::operMenu()
{
    cout<<"欢迎教师："<<this->m_Name<<"登录！\n";
    cout<<"\t\t -----------------------------\n";
    cout<<"\t\t|                             |\n";
    cout<<"\t\t|          1.查看所有预约     |\n";
    cout<<"\t\t|                             |\n";
    cout<<"\t\t|          2.审核预约         |\n";
    cout<<"\t\t|                             |\n";
    cout<<"\t\t|          0.注销登录         |\n";
    cout<<"\t\t|                             |\n";
    cout<<"\t\t -----------------------------\n";
    cout<<"请输入您的操作：";
}

void Teacher::showAllOrder()
{
    OrderFile of;
    if(of.m_Size==0)
    {
        cout<<"无预约记录！"<<endl;
        system("pause");
        system("cls");
        return;
    }
    for(int i = 0; i<of.m_Size; i++)
    {
        cout<<"第"<<i+1<<"条\t";
        cout<<"预约日期：周"<<of.m_OrderData[i]["weekday"]<<"\t";
        cout<<"时间段："<<(of.m_OrderData[i]["interval"]=="1"?"上午":"下午")<<"\t";
        cout<<"机房编号："<<of.m_OrderData[i]["room"]<<"\t";
        cout<<"学号："<<of.m_OrderData[i]["studentId"]<<"\t";
        cout<<"姓名："<<of.m_OrderData[i]["studentName"]<<"\t";

        string status ="预约状态：";
        //1 审核中，2 已预约 -1预约失败 0取消预约
        if(of.m_OrderData[i]["status"]=="1")
        {
            status+="审核中";
        }
        else if(of.m_OrderData[i]["status"]=="2")
        {
            status+="已预约";
        }
        else if(of.m_OrderData[i]["status"]=="-1")
        {
            status+="预约失败";
        }
        else if(of.m_OrderData[i]["status"]=="0")
        {
            status+="取消预约";
        }
        cout<<status<<endl;
    }
    system("pause");
    system("cls");
}

void Teacher::validOrder()
{
    OrderFile of;
    if(of.m_Size==0)
    {
        cout<<"无预约记录！"<<endl;
        system("pause");
        system("cls");
        return;
    }
    cout<<"待审核的预约如下："<<endl;

    int index=0;
    vector<int>v;
    for(int i = 0; i<of.m_Size; i++)
    {
        if(of.m_OrderData[i]["status"]=="1")
        {
            v.push_back(i);
            cout<<"第"<<++index<<"条\t";
            cout<<"预约日期：周"<<of.m_OrderData[i]["weekday"]<<"\t";
            cout<<"时间段："<<(of.m_OrderData[i]["interval"]=="1"?"上午":"下午")<<"\t";
            cout<<"机房编号："<<of.m_OrderData[i]["room"]<<"\t";
            cout<<"学号："<<of.m_OrderData[i]["studentId"]<<"\t";
            cout<<"姓名："<<of.m_OrderData[i]["studentName"]<<"\t";
            cout<<"预约状态：审核中"<<endl;
        }
    }
    cout<<"请输入要审核的预约编号,0代表返回"<<endl;
    int select=0;//接受老师选择的预约记录
    int ret = 0; //接受预约结果记录
    while(true)
    {
        cin>>select;
        if(select>=0&&select<=v.size())
        {
            if(select==0)
            {
                break;
            }
            else{
                cout<<"请输入审核结果"<<endl;
                cout<<"1、通过"<<endl;
                cout<<"2、不通过"<<endl;
                cin>>ret;
                if(ret==1)
                {
                    //通过清空
                    of.m_OrderData[v[select-1]]["status"]="2";
                }
                else if(ret==2)
                {
                    //不通过
                    of.m_OrderData[v[select-1]]["status"]="-1";
                }
                of.updateOrder();
                cout<<"审核成功！"<<endl;
                break;
            }
        }
    }
    system("pause");
    system("cls");

}
