#pragma once
#include "company_staff.h"
#include "Manager.h"
#include "Saleman.h"
#include "SaleManager.h"
#include "IndexType.h"
#define NUM_OF_INCREMENT 100  //�궨��,����,����
class StaffManage            //Ա�������������,�������ļ����й�����ɾ�Ĳ�(ÿ�����ж���Ҫ���½���ͳһ����)��ͬʱ���������в���
{
private:                               //˽�����ݳ�Ա
	fstream file;                      //������Ա���ݵĶ������ļ�
	IndexType*indexTable;              //����һ��������Ķ���ָ��������������ڴ�Ŷ����ַ��ָ���ڶ��д���������
	int maxSize;                       //���������,��������
	int count;                         //���������
	void AddIndexItem(const IndexType&e);    //����������
	void AddData();                          //��������
	void DeleteData();                      //ɾ������
	void UpdateData();                      //��������
	void SearchData();                       //��������
	void Pack();                             //�����ǵ�����
	void CacS();                             //���㹤��
	void Stat();                            //ͳ�ƺ���
public:
	StaffManage();                    //���캯��
	~StaffManage();                 //��������������Ҫ����������û�д��麯�����߲��û����ָ��ɾ��������Ķ���
	void Run();                              //����ɾ�Ĳ�ͳһ�жϽ������,������ͬ��switch����

};


