#include "company_staff.h"
#include "Manager.h"
//经理类的实现
Manager::Manager(){}                     //构造函数
Manager::~Manager(){}                    //析构函数
void Manager::Input()                    //显示信息
{ //录入员工信息(用一个判断语句来判断输入信息是否正确)
	char flag;                           //声明变量
	do{
		cout<<"编号:";cin>>num;          //输入编号
		cout<<"姓:";cin>>fname;          //输入姓氏
		cout<<"名:";cin>>sname;          //输入名
		cout<<"姓名:";cin>>name;         //输入姓名
		cout<<"年龄:";cin>>age;          //输入年龄
		cout<<"确认信息正确与否?";       //提示用户判断
		cin>>flag;                      //输入判断
		flag=tolower(flag);
	}while(flag!='y');
}
void Manager::Show()const                   //显示函数的实现
{                                           //设置输出的格式
  cout<<setw(8)<<"编号"<<setw(12)<<"姓名"<<setw(10)<<"年龄"<<setw(12)<<endl;
  cout<<setw(8)<<num<<setw(9)<<fname<<sname<<setw(9)<<age<<setw(12)<<endl;
}
void Manager::Read(fstream&f)const    //读取文件函数的实现
{
   f.read((char*)this,sizeof(Manager));    //从文件中读取信息读到内存中转化为char型读取长度为Manager
}
void Manager::Write(fstream&f)const   //写入数据函数的实现
{
    f.write((char*)this,sizeof(Manager));//将输入到内存中的数据写到文件中转化为char型 写入长度为Manager
}
double Manager::GetSalary ()             //计算工资函数的实现
{
 const int salary=8000;                  //薪水设为常量
 return salary;                          //返回薪水
}
