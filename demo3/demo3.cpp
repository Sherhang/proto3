#include "qq_filter.pb.h"
#include<iostream>
#include<fstream>
#include<cstring> // strcpy
using namespace std;
int main()
{
    //初始化方式
    itc::yuds::book_for_filter::BookForFilter bookforfilter;
    //可重复的基本类型赋值
    for(int i=0;i<5;++i)
    {
        bookforfilter.add_book_id(10000+i); 
    }

    //序列化消息
    string buff;
    bookforfilter.SerializeToString(&buff);//注意加&

    cout<<"写入文件"<<endl;
    ofstream outfile;
    string outfile_name= "data.txt";
    outfile.open(outfile_name.c_str(), ios::app | ios::binary);//追加写入,二进制

    outfile << buff ;//写入文件
    outfile << '|';//方便后续读取
    outfile.close();//关闭文件

    cout<<"从文件解析消息"<<endl;
    string s;
    ifstream infile;
    infile.open(outfile_name.c_str(), ios::in | ios::binary);
    while(getline(infile, s, '|'))  //以‘|’作为分隔符读取
    {
        itc::yuds::book_for_filter::BookForFilter p;

        p.ParseFromString(buff);
        for (int i =0 ;i<p.book_id_size();++i)
        {
            auto book_id = p.book_id(i);
            cout<<book_id<<endl;
        }
        //cout<<"二进制："<<s<<endl;
    }
}
