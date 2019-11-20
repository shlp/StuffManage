#pragma once
#include "company_staff.h"
#include "Manager.h"
#include "Saleman.h"
class SaleManager:public Saleman,public Manager        //销售经理类继承Saleman类与Manager类
{
protected:
	double basicSalary;                        //底薪
	double affSale;                            //下属销售员销售总额
public:
	SaleManager();                            //构造函数
	virtual~SaleManager();                    //虚析构函数
	const char*GetNum()const;                 //得到编号
	virtual void Input();                     //输入信息函数
	virtual void Show()const;                //显示数据函数声明
	virtual void Read(fstream&f)const;       //从文件中读数据
	virtual void Write(fstream&f)const;      //写数据到文件中
    virtual double GetSalary();              //得到工资函数
};

