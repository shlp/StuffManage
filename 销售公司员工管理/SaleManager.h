#pragma once
#include "company_staff.h"
#include "Manager.h"
#include "Saleman.h"
class SaleManager:public Saleman,public Manager        //���۾�����̳�Saleman����Manager��
{
protected:
	double basicSalary;                        //��н
	double affSale;                            //��������Ա�����ܶ�
public:
	SaleManager();                            //���캯��
	virtual~SaleManager();                    //����������
	const char*GetNum()const;                 //�õ����
	virtual void Input();                     //������Ϣ����
	virtual void Show()const;                //��ʾ���ݺ�������
	virtual void Read(fstream&f)const;       //���ļ��ж�����
	virtual void Write(fstream&f)const;      //д���ݵ��ļ���
    virtual double GetSalary();              //�õ����ʺ���
};

