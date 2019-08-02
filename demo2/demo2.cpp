#include "demo2.pb.h"
#include<iostream>
#include<fstream>
#include<cstring> // strcpy
using namespace std;
int main()
{
    //初始化方式
    person::Person msg;//还可以写成msg{}
    person::Person* msg_ptr = &msg;//对应的指针
    //普通类型赋值
    msg.set_id("10234457");
    msg_ptr->set_sex(person::Sex::male);//男
    //自定义类型赋值，第一种方式 set_allocate_XXX, 需要自己delete

    //自定义类型赋值，第2种方式 mutable_XXX, 
    person::Info* info_ptr = msg.mutable_info();//这里是自定义类型的指针
    info_ptr->set_name("Tom");
    info_ptr->set_age(18);
    info_ptr->set_email("Tom@121.com");
    info_ptr->set_phone("17552759310");

    //可重复的基本类型赋值
    for(int i=0;i<5;++i)
    {
        msg.add_other_info("other"); 
    }
    //可重复的自定义类型赋值
    for(int i=0;i<5;i++)
    {
        auto friends_ptr = msg.add_friends();//返回指针
        friends_ptr->set_name("Anddy");
        friends_ptr->set_age(18+i);
        friends_ptr->set_sex(person::Sex::male);
    }

    //序列化消息
    string buff;
    msg.SerializeToString(&buff);//注意加&

    cout<<"写入文件"<<endl;
    ofstream outfile;
    string outfile_name= "data.txt";
    outfile.open(outfile_name.c_str(), ios::app | ios::binary);//追加写入,二进制

    outfile << buff ;//写入文件
    outfile << '|';//方便后续读取
    outfile.close();//关闭文件

    cout<<"直接由流解析消息"<<endl;
    person::Person p;
    p.ParseFromString(buff);
    cout<<p.id()<<" ";
    cout<<p.sex()<<endl;

    cout<<"从文件解析消息"<<endl;
    string s;
    ifstream infile;
    infile.open(outfile_name.c_str(), ios::in | ios::binary);
    while(getline(infile, s, '|'))  //以‘|’作为分隔符读取
    {
        person::Person p;
        p.ParseFromString(buff);
        cout<<p.id()<<" ";
        cout<<p.sex()<<endl;
        //自定义类型数据解析
        person::Info info = p.info();//auto == person::Info
        cout<<info.name()<<"| "<<info.age()<<"| "<<info.email()<<"| "<<info.phone()<<"| "<<endl;
        cout<<"other_info()"<<endl;
        for (int i =0 ;i<p.other_info_size();++i)
        {
            cout<<p.other_info(i)<<" ";
        }
        cout<<endl<<"friends"<<endl;
        for (int i =0 ;i<p.friends_size();++i)
        {
            auto friends = p.friends(i);
            cout<<friends.name()<<" "<<friends.age()<<" "<<friends.sex()<<endl;
        }
        //cout<<"二进制："<<s<<endl;
    }
}
