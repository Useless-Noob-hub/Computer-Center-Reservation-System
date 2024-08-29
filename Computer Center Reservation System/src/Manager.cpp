#include "Manager.h"
Manager::Manager()
{
    
}
Manager::Manager(string name, string pwd)
{
    //初始化管理员信息
    this->m_Name=name;
    this->m_Pwd=pwd;

    //初始化容器（学生、老师、机房）
    this->initVector();

}

    //菜单界面
void Manager:: operMenu()
{
        cout<<"欢迎来到管理员："<<this->m_Name<<"登录！\n";
	    cout<<"\t\t -----------------------------\n";
	    cout<<"\t\t|                             |\n";
	    cout<<"\t\t|          1.添加账号         |\n";
	    cout<<"\t\t|                             |\n";
	    cout<<"\t\t|          2.查看账号         |\n";
	    cout<<"\t\t|                             |\n";
	    cout<<"\t\t|          3.查看机房         |\n";
	    cout<<"\t\t|                             |\n";
	    cout<<"\t\t|          4.清空预约         |\n";
	    cout<<"\t\t|                             |\n";
	    cout<<"\t\t|          0.注销登录         |\n";
	    cout<<"\t\t|                             |\n";
	    cout<<"\t\t -----------------------------\n";
    cout<<"请输入您的操作：";
}

    // 添加账号
void Manager::addPerson()
{
    cout<<"请输入添加账号类型"<<endl;
    cout<<"1.添加学生"<<endl;
    cout<<"2.添加老师"<<endl;
    cout<<"3.返回上一级菜单"<<endl;
    string fileName;//操作的文件名
    string tip;//提示id号
     
    ofstream ofs;   //文件操作对象
    int select=0;
    cin>>select;
    string errortip;
    if(select==1)
    {
        // 添加的是学生
        fileName=STUDENT_FILE;
        tip="请输入学号：";
        errortip="学号已存在！请重新输入：";

    }
    else if(select==2)
    {
        // 添加的是老师
        fileName=TEACHER_FILE;
        tip="请输入工号：";
        errortip="工号已存在！请重新输入：";
    }
    else 
    {
        return;
    }

    //写文件
    //利用追加的方式 写文件
    ofs.open(fileName,ios::out|ios::app);

    int id;
    string name;
    string pwd;
    
    cout<<tip<<endl;
    cin>>id;
    //检查id是否重复
    while(true)
    {
        if(checkRepeat(id,select))
        {
            cout<<errortip<<endl;
            cin>>id;
        }
        else
        {
            break;
        }
    }

    cout<<"请输入姓名："<<endl;
    cin>>name;

    cout<<"请输入密码："<<endl;
    cin>>pwd;
    
    //像文件中添加数据
    ofs<<id<<"\t"<<name<<"\t"<<pwd<<endl;
    cout<<"添加成功！"<<endl;

    //重新初始化容器
    this->initVector();

    system("pause");
    system("cls");
    ofs.close();

}

    // 查看账号
void Manager::showPerson()
{
    cout<<"请选择查看内容:"<<endl;
    cout<<"1.查看学生信息"<<endl;
    cout<<"2.查看老师信息"<<endl;

    int select;
    cin>>select;
    if(select==1)
    {
        //查看学生
        cout<<"所有学生信息如下："<<endl;
        for_each(vStu.begin(),vStu.end(),[](Student &s){
            cout<<"学号："<<s.m_Id<<"姓名:"<<s.m_Name<<"密码:"<<s.m_Pwd<<endl;
        });

    }
    else if(select==2)
    {
        //查看老师
        cout<<"所有老师信息如下："<<endl;
        for_each(vTea.begin(),vTea.end(),[](Teacher &t){
            cout<<"职工号："<<t.m_EmpId<<"姓名:"<<t.m_Name<<"密码:"<<t.m_Pwd<<endl;
        });
    }
    system("pause");
    system("cls");
    
}

    // 查看机房信息
void Manager::showComputer()
{
    //读取机房信息
    cout<<"所有机房信息如下："<<endl;
    for_each(vCom.begin(),vCom.end(),[](ComputerRoom &com){
        cout<<"机房编号："<<com.m_ComId<<"机房最大容量："<<com.m_MaxNum<<endl;
    });
    system("pause");
    system("cls");

    
}

    //清空预约记录
void Manager::cleanFile()
{
    // 清空确认
    int select;
    cout<<"确认清空？"<<endl;
    cout<<"1.确认清空"<<endl;
    cout<<"2.取消清空"<<endl;
    cin>>select;
    if(select==2)
    {
        return;
    }
    ofstream ofs(ORDER_FILE,ios::trunc);
    ofs.close();
    cout<<"清空成功！"<<endl;
    system("pause");
    system("cls");
    
}

//初始化容器
void Manager::initVector()
{
    //确保容器清空
    vStu.clear();
    vTea.clear();

    //读取学生信息
    ifstream ifs;
    ifs.open(STUDENT_FILE,ios::in);
    if(!ifs.is_open())
    {
        cout<<"文件打开失败！"<<endl;
        return;
    }
    Student s;
    while(ifs>>s.m_Id && ifs>>s.m_Name && ifs>>s.m_Pwd)
    {
        vStu.push_back(s);
    }
    // cout<<"当前学生数量为："<<vStu.size()<<endl;
    ifs.close();

    // 读取老师信息
    ifs.open(TEACHER_FILE,ios::in);
    if(!ifs.is_open())
    {
        cout<<"文件打开失败！"<<endl;
        return;
    }
    Teacher t;
    while(ifs>>t.m_EmpId && ifs>>t.m_Name && ifs>>t.m_Pwd)
    {
        vTea.push_back(t);
    }
    // cout<<"当前老师数量为："<<vTea.size()<<endl;
    ifs.close();

    //机房信息初始化
    ifs.open(COMPUTER_FILE,ios::in);
    if(!ifs.is_open())
    {
        cout<<"文件打开失败！"<<endl;
        return;
    }
    ComputerRoom com;
    while(ifs>>com.m_ComId && ifs>>com.m_MaxNum)
    {
        vCom.push_back(com);
    }
    ifs.close();

}

//检测ID是否重复
bool Manager::checkRepeat(int id, int type)
{
    if(type==1) 
    {
        //检测学生
        for(vector<Student>::iterator it=vStu.begin();it!=vStu.end();it++)
        {
            if(it->m_Id==id)
            {
                return true;
            }
        }
    }
    if(type==2) 
    {
        //检测学生
        for(vector<Teacher>::iterator it=vTea.begin();it!=vTea.end();it++)
        {
            if(it->m_EmpId==id)
            {
                return true;
            }
        }
    }
    return false;
}
