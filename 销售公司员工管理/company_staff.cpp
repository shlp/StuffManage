#include "company_staff.h"
//Ա�����Ա������ʵ��
Staff::Staff(){}                     //���캯����ʵ��
Staff::~Staff(){}                   //����������ʵ��
const char*Staff::GetNum()const     //�õ�Ա�����
{
	return num;                   //����Ա������
}
 const char*Staff::GetName()const //�õ�Ա������
{    
	return name;                 //����Ա������
}
const char* Staff::GetFname()   //�õ�Ա����
{
   return  fname;              //����Ա����
}
 const char* Staff::GetSname()  //�õ�Ա����
{
   return  sname;               //����Ա����
}
 const char* Staff::GetAge()   //�õ�����
{
   return  age;               //��������
}