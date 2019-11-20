#pragma once
#include "company_staff.h"
class Manager:virtual public Staff      //经理类虚继承Staff类
{ 
public:
	Manager();                        //构造函数
	virtual~Manager();                //虚析构函数 有虚函数成员 或当用一个基类的指针删除派生类的对象时，派生类的析构函数会被调用
	virtual void Input();             //输入数据信息函数的声明
	virtual void Show()const;         //显示数据函数声明
	virtual void Read(fstream&f)const;//从文件中读信息 
	virtual void Write(fstream&f)const; //向文件中写信息
	virtual double GetSalary();        //计算薪水
};