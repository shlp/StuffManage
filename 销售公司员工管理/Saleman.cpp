#include "company_staff.h"
#include "Saleman.h"
//����ԱSaleman���ʵ��
Saleman::Saleman(){}  //���캯��                
Saleman::~Saleman(){} //��������
void Saleman:: Input()  //������Ϣ������ʵ��
{ //¼��Ա����Ϣ(��һ���ж�������ж�������Ϣ�Ƿ���ȷ)
	char flag;             //��������
	do{
		cout<<"���:";cin>>num;    //������
     	cout<<"��:";cin>>fname;    //��������
		cout<<"��:";cin>>sname;    //������
		cout<<"����:";cin>>name;   //��������
		cout<<"����:";cin>>age;    //��������
		cout<<"ְ��:";cin>>prof;   //����ְ��
		cout<<"���۶�:";cin>>saleroom;//�������۶�
		cout<<"���:";cin>>deduct;    //�������
		cout<<"ȷ����Ϣ��ȷ���?";    //��ʾ�û��ж���Ϣ��ȷ���
		cin>>flag;                 //�����ж�
		flag=tolower(flag);         //ת��ΪСд
	}while(flag!='y');
}
void Saleman::Show()const              //��ʾ������ʵ��
{                                       //��������ĸ�ʽ
	cout<<setw(8)<<"���"<<setw(12)<<"����"<<setw(10)<<"����"<<setw(12)<<"ְ��"<<setw(12)<<"���۶�"<<endl;
	cout<<setw(8)<<num<<setw(9)<<fname<<sname<<setw(9)<<age<<setw(12)<<prof<<setw(12)<<saleroom<<endl;
}
void Saleman::Read(fstream&f)const     //��ȡ�ļ�������ʵ��
{
	f.read((char*)this,sizeof(Saleman)); //���ļ��ж�ȡ��Ϣ�����ڴ���ת��Ϊchar�Ͷ�ȡ����ΪSaleman
}
void Saleman::Write(fstream&f)const    //д�����ݺ�����ʵ��
{
	f.write((char*)this,sizeof(Saleman));//�����뵽�ڴ��е�����д���ļ���ת��Ϊchar�� д�볤��ΪSaleman
}
double Saleman::GetSalary ()           //���㹤�ʺ�����ʵ��
{
return (saleroom*0.04*deduct);         //���ؼ����Ĺ���
}


