#pragma once
#include "company_staff.h"
#include "Manager.h"
#include "Saleman.h"
#include "SaleManager.h"
#include "IndexType.h"
#define NUM_OF_INCREMENT 100  //宏定义,常量,增量
class StaffManage            //员工管理类的声明,对数据文件进行管理增删改查(每个类中都需要有新建类统一管理)，同时对索引进行操作
{
private:                               //私有数据成员
	fstream file;                      //保存人员数据的二进制文件
	IndexType*indexTable;              //声明一个索引类的对象指针变量索引表，用于存放对象地址（指向在堆中创建的区域）
	int maxSize;                       //最大索引项,可以扩大
	int count;                         //索引项个数
	void AddIndexItem(const IndexType&e);    //增加索引项
	void AddData();                          //增加数据
	void DeleteData();                      //删除数据
	void UpdateData();                      //更新数据
	void SearchData();                       //查找数据
	void Pack();                             //清除标记的数据
	void CacS();                             //计算工资
	void Stat();                            //统计函数
public:
	StaffManage();                    //构造函数
	~StaffManage();                 //析构函数，不需要用虚析构（没有纯虚函数或者不用基类的指针删除派生类的对象）
	void Run();                              //将增删改查统一判断将代码简化,条件相同用switch语句简化

};


