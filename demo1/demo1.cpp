#include "demo1.pb.h"
#include<iostream>
#include<fstream>
#include<cstring> // strcpy
using namespace std;
int main()
{
    person::Person msg;
    msg.set_name("Sherhang");
    msg.set_age(19);
    //序列化消息
    char buff[1024] = {0};
    msg.SerializeToArray(buff, 1024);

    cout<<"写入文件"<<endl;
    ofstream outf;
    string outf_name= "data.txt";
    outf.open(outf_name.c_str(), ios::app | ios::binary);//追加写入,二进制

    outf << buff ;//写入文件
    outf << '|';//方便后续读取
    outf.close();//关闭文件

    cout<<"直接由流解析消息"<<endl;
    person::Person p;
    p.ParseFromArray(buff, 1024);
    cout<<p.name()<<" ";
    cout<<p.age()<<endl;

    cout<<"从文件解析消息"<<endl;
    string s;
    ifstream infile;
    infile.open(outf_name.c_str(), ios::in | ios::binary);
    while(getline(infile, s, '|'))  //以‘|’作为分隔符读取
    {
        char buff[1024] ;
        strcpy(buff, s.c_str());//把string转为char*,用strcpy
        person::Person p;
        p.ParseFromArray(buff, 1024);
        cout<<p.name()<<" ";
        cout<<p.age()<<endl;
        cout<<"二进制："<<s<<endl;
    }
}
