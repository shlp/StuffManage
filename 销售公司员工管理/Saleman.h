#pragma once       
#include "company_staff.h"
class Saleman:virtual public Staff      //����Ա��  ��̳�Staff��
{
protected:   
	char prof[10];                      //ְ��
	double saleroom;                   //���۶�
    double deduct;                     //���
public:
	Saleman();                         //���캯��
	virtual~Saleman();                 //����������
	virtual void Input();             //����������Ϣ����������
	virtual void Show()const;          //��ʾ���ݺ�������
	virtual void Read(fstream&f)const; //���ļ��ж���Ϣ 
	virtual void Write(fstream&f)const; //���ļ���д��Ϣ
	virtual double GetSalary();        //�õ����ʺ���
};
