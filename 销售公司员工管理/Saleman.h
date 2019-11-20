#pragma once       
#include "company_staff.h"
class Saleman:virtual public Staff      //销售员类  虚继承Staff类
{
protected:   
	char prof[10];                      //职称
	double saleroom;                   //销售额
    double deduct;                     //提成
public:
	Saleman();                         //构造函数
	virtual~Saleman();                 //虚析构函数
	virtual void Input();             //输入数据信息函数的声明
	virtual void Show()const;          //显示数据函数声明
	virtual void Read(fstream&f)const; //从文件中读信息 
	virtual void Write(fstream&f)const; //向文件中写信息
	virtual double GetSalary();        //得到工资函数
};
