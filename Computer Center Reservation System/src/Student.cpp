#include "Student.h"

Student::Student()
{

}

Student::Student(int id, string name, string pwd)
{
    this->m_Id=id;
    this->m_Name=name;
    this->m_Pwd=pwd;

    //初始化机房信息
    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in); 


    if(!ifs.is_open()) {
        cout<<"文件打开失败！"<<endl;
    } else {
        //文件打开成功
        ComputerRoom com;
    while(ifs>>com.m_ComId && ifs>>com.m_MaxNum)
    {
        vCom.push_back(com);
    }
    ifs.close();
    }
}

void Student::operMenu()
{
    cout<<"欢迎学生代表："<<this->m_Name<<"登录！\n";
    cout<<"\t\t -----------------------------\n";
    cout<<"\t\t|                             |\n";
    cout<<"\t\t|          1.申请预约         |\n";
    cout<<"\t\t|                             |\n";
    cout<<"\t\t|          2.查看我的预约     |\n";
    cout<<"\t\t|                             |\n";
    cout<<"\t\t|          3.查看所有预约     |\n";
    cout<<"\t\t|                             |\n";
    cout<<"\t\t|          4.取消预约         |\n";
    cout<<"\t\t|                             |\n";
    cout<<"\t\t|          0.注销登录         |\n";
    cout<<"\t\t|                             |\n";
    cout<<"\t\t -----------------------------\n";
    cout<<"请输入您的操作：";
}

//申请预约
void Student::applyOrder()
{
    
    int weekday=0;//日期
    int interval=0;//时间段
    int room=0;//机房编号

    cout<<"机房开放时间：周一至周五 09:00~18:00"<<endl;
    cout<<"请输入申请预约的时间："<<endl;
    cout<<"1、周一"<<endl;
    cout<<"2、周二"<<endl;
    cout<<"3、周三"<<endl;
    cout<<"4、周四"<<endl;
    cout<<"5、周五"<<endl;

    while(true)
    {
        cin>>weekday;
        if(weekday>=1 && weekday<=5)
        {
            break;
        }
        cout<<"输入有误，请重新输入："<<endl;

    }
    cout<< "请输入申请预约的时间段："<<endl;
    cout<<"1、上午"<<endl;
    cout<<"2、下午"<<endl;
    while(true)
    {
        cin>>interval;
        if(interval>=1 && interval<=2)
        {
            break;
        }
        cout<<"输入有误，请重新输入："<<endl;

    }

    cout<< "请输入申请预约的机房编号："<<endl;
    for_each(vCom.begin(), vCom.end(), [&](ComputerRoom &c)
    {
        cout<<c.m_ComId<<"号机房容量为："<<c.m_MaxNum<<endl;
    }
    );
    while(true)
    {
        cin>>room;
        if(room>=1 && room<=vCom.size())
        {
            break;
        }
        cout<<"输入有误，请重新输入："<<endl;
    }

    cout<< "预约成功！审核中"<<endl;

    // 写入预约文件
    ofstream ofs;
    ofs.open(ORDER_FILE,ios::app);

    ofs<<"weekday:"<<weekday<<"\t";
    ofs<<"interval:"<<interval<<"\t";
    ofs<<"room:"<<room<<"\t";
    ofs<<"studentId:"<<this->m_Id<<"\t";
    ofs<<"studentName:"<<this->m_Name<<"\t";
    ofs<<"status:"<<1<<endl;

    ofs.close();

    system("pause");
    system("cls");
}

//显示预约
void Student::showMyOrder()
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
        if(this->m_Id==atoi(of.m_OrderData[i]["studentId"].c_str()))
        // atoi()将字符串转换为整型,c_str()将string转换为char*
        //找到自身预约
        {
            cout<<"预约日期：周"<<of.m_OrderData[i]["weekday"]<<"\t";
            cout<<"时间段："<<(of.m_OrderData[i]["interval"]=="1"?"上午":"下午")<<"\t";
            cout<<"机房编号："<<of.m_OrderData[i]["room"]<<"\t";
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
    }
    system("pause");
    system("cls");
}

void Student::showAllOrder()
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

//取消预约
void Student::cancelOrder()
{
    OrderFile of;
    if(of.m_Size==0)
    {
        cout<<"无预约记录！"<<endl;
        system("pause");
        system("cls");
        return;
    }
    cout<<"审核总或预约成功的记录可以取消，请输入取消的记录"<<endl;
    vector<int>v;//存放在最大容器中的下表编号
    int index =1;
    for(int i = 0 ; i<of.m_Size; i++)
    {
        // 找到自身预约
        if(this->m_Id==atoi(of.m_OrderData[i]["studentId"].c_str()))
        {
            // 审核通过或预约成功的记录可以取消
            if(of.m_OrderData[i]["status"]=="2" || of.m_OrderData[i]["status"]=="1")
            {
            v.push_back(i);//记录在最大容器中的下标 v[index]=i
            cout<<index++<<"\t"; 
            cout<<"预约日期：周"<<of.m_OrderData[i]["weekday"]<<"\t";
            cout<<"时间段："<<(of.m_OrderData[i]["interval"]=="1"?"上午":"下午")<<"\t";
            cout<<"机房编号："<<of.m_OrderData[i]["room"]<<"\t";
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
            cout<<status<<endl;
            }
        }
    }
    cout<<"请输入取消的记录，0代表返回"<<endl;
    int select=0;
    while(true)
    {
        cin>>select;
        if(select==0)
        {
            break;
        }
        else if(select>=1 && select<=index)
        {
            //v[select-1]表示最大容器中的下标 
            of.m_OrderData[v[select-1]]["status"]="0";//取消预约
            of.updateOrder();//更新预约文件
            cout<<"取消成功！"<<endl;
            break;
        }else{
        cout<<"输入有误，请重新输入："<<endl;
        }
    }
    system("pause");
    system("cls");
}
 