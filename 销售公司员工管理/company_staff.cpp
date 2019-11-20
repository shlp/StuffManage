#include "company_staff.h"
//员工类成员函数的实现
Staff::Staff(){}                     //构造函数的实现
Staff::~Staff(){}                   //析构函数的实现
const char*Staff::GetNum()const     //得到员工编号
{
	return num;                   //返回员工编码
}
 const char*Staff::GetName()const //得到员工姓名
{    
	return name;                 //返回员工姓名
}
const char* Staff::GetFname()   //得到员工姓
{
   return  fname;              //返回员工姓
}
 const char* Staff::GetSname()  //得到员工名
{
   return  sname;               //返回员工名
}
 const char* Staff::GetAge()   //得到年龄
{
   return  age;               //返回年龄
}