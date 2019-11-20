#include "company_staff.h"
#include "Saleman.h"
//销售员Saleman类的实现
Saleman::Saleman(){}  //构造函数                
Saleman::~Saleman(){} //析构函数
void Saleman:: Input()  //输入信息函数的实现
{ //录入员工信息(用一个判断语句来判断输入信息是否正确)
	char flag;             //声明变量
	do{
		cout<<"编号:";cin>>num;    //输入编号
     	cout<<"姓:";cin>>fname;    //输入姓氏
		cout<<"名:";cin>>sname;    //输入名
		cout<<"姓名:";cin>>name;   //输入姓名
		cout<<"年龄:";cin>>age;    //输入年龄
		cout<<"职称:";cin>>prof;   //输入职称
		cout<<"销售额:";cin>>saleroom;//输入销售额
		cout<<"提成:";cin>>deduct;    //输入提成
		cout<<"确认信息正确与否?";    //提示用户判断信息正确与否
		cin>>flag;                 //输入判断
		flag=tolower(flag);         //转换为小写
	}while(flag!='y');
}
void Saleman::Show()const              //显示函数的实现
{                                       //设置输出的格式
	cout<<setw(8)<<"编号"<<setw(12)<<"姓名"<<setw(10)<<"年龄"<<setw(12)<<"职称"<<setw(12)<<"销售额"<<endl;
	cout<<setw(8)<<num<<setw(9)<<fname<<sname<<setw(9)<<age<<setw(12)<<prof<<setw(12)<<saleroom<<endl;
}
void Saleman::Read(fstream&f)const     //读取文件函数的实现
{
	f.read((char*)this,sizeof(Saleman)); //从文件中读取信息读到内存中转化为char型读取长度为Saleman
}
void Saleman::Write(fstream&f)const    //写入数据函数的实现
{
	f.write((char*)this,sizeof(Saleman));//将输入到内存中的数据写到文件中转化为char型 写入长度为Saleman
}
double Saleman::GetSalary ()           //计算工资函数的实现
{
return (saleroom*0.04*deduct);         //返回计算后的工资
}


