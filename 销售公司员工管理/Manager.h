#pragma once
#include "company_staff.h"
class Manager:virtual public Staff      //��������̳�Staff��
{ 
public:
	Manager();                        //���캯��
	virtual~Manager();                //���������� ���麯����Ա ����һ�������ָ��ɾ��������Ķ���ʱ������������������ᱻ����
	virtual void Input();             //����������Ϣ����������
	virtual void Show()const;         //��ʾ���ݺ�������
	virtual void Read(fstream&f)const;//���ļ��ж���Ϣ 
	virtual void Write(fstream&f)const; //���ļ���д��Ϣ
	virtual double GetSalary();        //����нˮ
};