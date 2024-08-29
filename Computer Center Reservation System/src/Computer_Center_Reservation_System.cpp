#pragma once
#include "Identity.h"
#include<fstream>
#include <GlobalFile.h>
#include <Student.h>
#include <Teacher.h>
#include <Manager.h>

//进入教师子菜单界面
void teacherMenu(Identity * &teacher)
{
    while(true)
    {
        //调用子菜单
        teacher->operMenu();

        Teacher *tea = (Teacher*)teacher;
        //接受用户选择
        int select = 0 ;
        cin>>select;
        if(select == 1)//查看所有预约
        {
            tea->showAllOrder();
        }
        else if(select==2)//处理预约
        {
            tea->validOrder();
        }
        else 
        {
            delete teacher;
            cout<<"注销成功"<<endl;
            system("pause");
            system("cls");
            break;
        }

    }

}

//进入学生子菜单界面
void studentMenu(Identity * &student)
{
    while(true)
    {
        //调用子菜单
        student->operMenu();

        Student *stu = (Student*)student;
        //接受用户选择
        int select = 0 ;
        cin>>select;
        if(select == 1)//申请预约
        {
            stu->applyOrder();
        }
        else if(select==2)//查看我的预约
        {
            stu->showMyOrder();
        }
        else if(select==3)//查看所有人预约
        {
            stu->showAllOrder();
        }
        else if(select==4)//取消预约
        {
            stu->cancelOrder();
        }
        else//注销登录
        {
            delete student; //销毁掉堆区对象
            cout<<"注销成功"<<endl;
            system("pause");
            system("cls");
            return;
        }

    }
}


//进入管理员子菜单界面
void managerMenu(Identity * &manager)
{
    while(true)
    {
        //调用管理员子菜单
        manager->operMenu();

        //将父类指针 转为子类指针，调用子类里的其他接口
        Manager *man = (Manager*)manager;

        int select = 0 ;
        //接受用户选项
        cin>>select;

        if(select==1)//添加账号
        {
            cout<<"添加账号"<<endl;
            man->addPerson();
        }
        else if(select==2)//查看账号
        {
            cout<<"查看账号"<<endl;
            man->showPerson();
        }
        else if(select==3)//查看机房
        {
            cout<<"查看机房"<<endl;
            man->showComputer();
        }
        else if(select==4)//清空预约
        {
            cout<<"清空预约"<<endl;
            man->cleanFile();
        }
        else                //注销登录
        {
            delete manager; //销毁掉堆区对象
            cout<<"注销成功"<<endl;
            system("pause");
            system("cls");
            return;
        }
    }
}


//登录功能  参数1 操作文件名  参数2操作身份类型
void LoginIn(string fileName ,int type)
{
    //父类指针，用于指向子类对象
    Identity *person=NULL;

    //读文件
    ifstream ifs;
    ifs.open(fileName,ios::in);

    //判断文件是否存在
    if(!ifs.is_open())
    {
        cout<<"文件不存在"<<endl;
        ifs.close();
        return;
    }

    //准备接受用户的信息
    int id = 0;
    string name;
    string pwd;

    //判断身份
    if(type==1) //学生身份
    {
        cout <<"请输入你的学号："<<endl;
        cin>>id;
    }
    else if(type==2) //老师身份
    {
        cout <<"请输入你的职工号："<<endl;
        cin>>id;
    }

    cout<<"请输入用户名："<<endl;
    cin>>name;
    cout<<"请输入密码："<<endl;
    cin>>pwd;

//验证身份进行下一个子菜单
    int fId;    //从文件中读取的id号
    string fName ;//从文件中获取的姓名  
    string fPwd;//从文件中获取密码
    if(type==1)
    {
    //学生身份验证

        while (ifs>>fId && ifs>>fName && ifs>>fPwd)
        { 
            //与用户输入的信息对比
            if(id==fId && name==fName && pwd==fPwd)
            {
                cout<<"学生身份验证成功！"<<endl;
                system("pause");
                system("cls");
                //创建学生对象
                person = new Student(id,name,pwd);
                //进入学生身份的子菜单
                studentMenu(person);
                return;//return直接返回主函数
            }

        }
    }
    else if(type==2) 
    {while (ifs>>fId && ifs>>fName && ifs>>fPwd)
    {
        if(fId == id && name==fName && fPwd==pwd)
        {
            //老师身份验证
            cout<<"老师身份验证成功！"<<endl;
            system("pause");
            system("cls");
            //创建老师对象
            person = new Teacher(id,name,pwd);
            //进入老师身份的子菜单
            teacherMenu(person);
            return;
        }
    }
    
    }
    else if(type==3) 
    {
    //管理员身份验证
    while (ifs>>fName && ifs>>fPwd)
    {
        if(fName==name && fPwd==pwd)
        {
            //管理员身份验证
            cout<<"管理员身份验证成功！"<<endl;
            system("pause");
            system("cls");
            //创建管理员对象
            person = new Manager(name,pwd);
            //进入管理员身份的子菜单
            managerMenu(person);
            return;
        }
    }
    }

    cout<<"验证登录失败！"<<endl;
    system("pause");
    system("cls");
    return;
}



int main()
{
    int select = 0 ; //用于接收用户的选择
    while(true)
    {
    cout<<"============ 欢迎来到____机房预约系统 ============\n";
    cout<<endl<<"请输入您的身份"<<endl;
    cout<<"\t\t -----------------------------\n";
    cout<<"\t\t|                             |\n";
    cout<<"\t\t|          1.学生代表         |\n";
    cout<<"\t\t|                             |\n";
    cout<<"\t\t|          2.老师             |\n";
    cout<<"\t\t|                             |\n";
    cout<<"\t\t|          3.管理员           |\n";
    cout<<"\t\t|                             |\n";
    cout<<"\t\t|          0.退出             |\n";
    cout<<"\t\t|                             |\n";
    cout<<"\t\t -----------------------------\n";
    cout<<"请输入您的选择：";

    cin>>select;
    switch(select)
    {
    case 1:
        LoginIn(STUDENT_FILE,1);
        break;
    case 2:
        LoginIn(TEACHER_FILE,2);
        break;
    case 3:
        LoginIn(ADMIN_FILE,3);
        break;
    case 0:
        cout<<"欢迎下次使用"<<endl;
        system("pause");
        return 0;
    default:
        cout<<"输入有误，请重新输入"<<endl;
        system("pause");
        system("cls");
        break;
    }

    }

    system("pause");
    return 0;
}