#include "OrderFile.h"

//截取字符串,放入map<string,string>中
void CutString(string &str,map<string,string>&m)
{
    string key;
    string value;
    int pos=str.find(":");
        if(pos!=-1)
        {
            key=str.substr(0,pos);
            value = str.substr(pos+1,str.size()-pos-1);
            m.insert(make_pair(key,value));
        }
}
//构造函数
OrderFile::OrderFile()
{
    ifstream ifs;
    ifs.open(ORDER_FILE,ios::in);

    string weekday; //日期
    string interval;    //时间段
    string room;        //机房编号
    string studentId;//学生编号
    string studentName;//学生姓名
    string status;  //预约状态

    this->m_Size=0; //记录条数

    while(ifs>>weekday&&ifs>>interval&&ifs>>room
    &&ifs>>studentId&&ifs>>studentName&&ifs>>status)
    {
        map<string,string>m;
        CutString(weekday,m);
        CutString(interval,m);
        CutString(room,m);
        CutString(studentId,m);
        CutString(studentName,m);
        CutString(status,m);

        //将小map插入到大map中
        this->m_OrderData.insert(make_pair(this->m_Size,m));   
        this->m_Size++;  

    }
    ifs.close();


    
}

//更新预约记录
void OrderFile::updateOrder()
{
    //没有数据
    if(this->m_Size==0)
    {
        return;
    }
    ofstream ofs;
    ofs.open(ORDER_FILE,ios::out|ios::trunc);//out表示写入，trunc表示清空文件
    for(int i=0; i<this->m_Size; i++)
    {
        ofs<<"weekday:"<<this->m_OrderData[i]["weekday"]<<"\t"; 
        ofs<<"interval:"<<this->m_OrderData[i]["interval"]<<"\t";
        ofs<<"room:"<<this->m_OrderData[i]["room"]<<"\t";
        ofs<<"studentId:"<<this->m_OrderData[i]["studentId"]<<"\t";
        ofs<<"studentName:"<<this->m_OrderData[i]["studentName"]<<"\t";
        ofs<<"status:"<<this->m_OrderData[i]["status"]<<endl;        
    }
    ofs.close();
}