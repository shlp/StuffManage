#include "SaleManager.h"
//���۾���Salemanager���ʵ��
SaleManager:: SaleManager(){}                 //���캯����ʵ��
SaleManager::~SaleManager(){}                 //����������ʵ��
void SaleManager::Input()                     //������Ϣ�ĺ���
{ //¼��Ա����Ϣ(��һ���ж�������ж�������Ϣ�Ƿ���ȷ)
	char flag;                                  //��������
	do{
		cout<<"���:";cin>>num;                 //������
		cout<<"��:";cin>>fname;                 //��������
		cout<<"��:";cin>>sname;                 //������
		cout<<"����:";cin>>name;                //��������
		cout<<"����:";cin>>age;                 //��������
		cout<<"���۶�:";cin>>saleroom;          //�������۶�
		cout<<"��н:";cin>>basicSalary;         //�����н
		cout<<"���������۶�:";cin>>affSale;     //�������������۶�
		cout<<"ְ��:";cin>>prof;                //����ְ��
		cout<<"ȷ����Ϣ��ȷ���?";             //�ж���Ϣ�Ƿ���ȷ
		cin>>flag;                              //�����ж�
		flag=tolower(flag);                    //ת��ΪСд
	}while(flag!='y');
}
void SaleManager::Show()const                  //��ʾ������ʵ��
{                                              //��������ĸ�ʽ
	cout<<setw(8)<<"���"<<setw(12)<<"����"<<setw(8)<<"����"<<setw(12)<<"ְ��"
		<<setw(12)<<"���۶�"<<endl;
	cout<<setw(8)<<num<<setw(9)<<fname<<sname<<setw(10)<<age<<setw(12)<<prof
		<<setw(12)<<saleroom<<endl;
}
void SaleManager::Read(fstream&f)const         //��ȡ�ļ�������ʵ��
{
	f.read((char*)this,sizeof(SaleManager));  //���ļ��ж�ȡ��Ϣ�����ڴ���ת��Ϊchar�Ͷ�ȡ����ΪSaleManager
}
void SaleManager::Write(fstream&f)const     //д�����ݺ�����ʵ��
{
	f.write((char*)this,sizeof(SaleManager));//�����뵽�ڴ��е�����д���ļ���ת��Ϊchar�� д�볤��ΪSaleManager
}
double SaleManager::GetSalary ()             //���㹤�ʺ�����ʵ��
{
	return (basicSalary+affSale*0.005);      //���ؼ�����
}
