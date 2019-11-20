#include "company_staff.h"
#include "staff_manage.h"
int main(void)                                               //主函数
{
	try                                                          //错误的异常处理函数
	{                                                             //可能会出现错误的函数
	StaffManage objSM ;                             //声明一个员工数据管理的对象
	objSM.Run();                                        //调用成员函数Run()函数实现操作
	}
	 catch(char /*error  char*error*/ /*...*/)   // 如果为char 处理char型异常  如果为...处理所有异常         
	{
	cout<<"error!";                                   // 异常处理程序，捕获由throw表达式抛出的异常
	}
system("PAUSE");                                  //库函数冻结屏幕更好的观察输出
return 0;
}