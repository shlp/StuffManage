#include "company_staff.h"
#include "Manager.h"
//�������ʵ��
Manager::Manager(){}                     //���캯��
Manager::~Manager(){}                    //��������
void Manager::Input()                    //��ʾ��Ϣ
{ //¼��Ա����Ϣ(��һ���ж�������ж�������Ϣ�Ƿ���ȷ)
	char flag;                           //��������
	do{
		cout<<"���:";cin>>num;          //������
		cout<<"��:";cin>>fname;          //��������
		cout<<"��:";cin>>sname;          //������
		cout<<"����:";cin>>name;         //��������
		cout<<"����:";cin>>age;          //��������
		cout<<"ȷ����Ϣ��ȷ���?";       //��ʾ�û��ж�
		cin>>flag;                      //�����ж�
		flag=tolower(flag);
	}while(flag!='y');
}
void Manager::Show()const                   //��ʾ������ʵ��
{                                           //��������ĸ�ʽ
  cout<<setw(8)<<"���"<<setw(12)<<"����"<<setw(10)<<"����"<<setw(12)<<endl;
  cout<<setw(8)<<num<<setw(9)<<fname<<sname<<setw(9)<<age<<setw(12)<<endl;
}
void Manager::Read(fstream&f)const    //��ȡ�ļ�������ʵ��
{
   f.read((char*)this,sizeof(Manager));    //���ļ��ж�ȡ��Ϣ�����ڴ���ת��Ϊchar�Ͷ�ȡ����ΪManager
}
void Manager::Write(fstream&f)const   //д�����ݺ�����ʵ��
{
    f.write((char*)this,sizeof(Manager));//�����뵽�ڴ��е�����д���ļ���ת��Ϊchar�� д�볤��ΪManager
}
double Manager::GetSalary ()             //���㹤�ʺ�����ʵ��
{
 const int salary=8000;                  //нˮ��Ϊ����
 return salary;                          //����нˮ
}
