#pragma once                               //防止头文件重复包含
#include <iostream>                      //预处理命令 输入输出流 
#include <fstream>                        //文件输入输出流 预处理命令
#include <iomanip>                        //流格式控制预处理命令
#include<string>
using namespace std;                       //使用标准命名空间
class Staff  	                           //员工类
{
protected:                                    //保护型数据成员
	char num[20];                               //编号	
	char name[20];                              //姓名
	char fname[20];                             //姓氏
	char sname[20];                             // 名
	char  age[20];                              //年龄
public:                                          //公有成员函数
	Staff();                                    //构造函数
	virtual~Staff();                             //虚析构函数 
	const char*GetNum()const;                  //返回编号
	virtual void Input()=0;                   //输入员工信息函数
	virtual void Show()const=0;               //显示员工信息函数
	virtual void Read(fstream&f)const=0;     //从文件中读取信息的函数
	virtual void Write(fstream&f)const=0;     //写数据到文件中,定义为纯虚函数是为了在派生类中实现不同的需要
	virtual double GetSalary()=0;            //计算薪水函数
	const char* GetName()const;              //返回姓名
	const char*  GetFname();                 //得到姓氏函数
	const  char*  GetSname() ;               //得到名函数
	const  char*  GetAge() ;                 //得到年龄函数
};


