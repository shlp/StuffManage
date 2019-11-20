#pragma once                               //��ֹͷ�ļ��ظ�����
#include <iostream>                      //Ԥ�������� ��������� 
#include <fstream>                        //�ļ���������� Ԥ��������
#include <iomanip>                        //����ʽ����Ԥ��������
#include<string>
using namespace std;                       //ʹ�ñ�׼�����ռ�
class Staff  	                           //Ա����
{
protected:                                    //���������ݳ�Ա
	char num[20];                               //���	
	char name[20];                              //����
	char fname[20];                             //����
	char sname[20];                             // ��
	char  age[20];                              //����
public:                                          //���г�Ա����
	Staff();                                    //���캯��
	virtual~Staff();                             //���������� 
	const char*GetNum()const;                  //���ر��
	virtual void Input()=0;                   //����Ա����Ϣ����
	virtual void Show()const=0;               //��ʾԱ����Ϣ����
	virtual void Read(fstream&f)const=0;     //���ļ��ж�ȡ��Ϣ�ĺ���
	virtual void Write(fstream&f)const=0;     //д���ݵ��ļ���,����Ϊ���麯����Ϊ������������ʵ�ֲ�ͬ����Ҫ
	virtual double GetSalary()=0;            //����нˮ����
	const char* GetName()const;              //��������
	const char*  GetFname();                 //�õ����Ϻ���
	const  char*  GetSname() ;               //�õ�������
	const  char*  GetAge() ;                 //�õ����亯��
};


