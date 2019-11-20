#include "Staff_Manage.h"
#include "company_staff.h"
#include "IndexType.h"
#include <iostream>
#include <string>
using namespace std;
//Ա���������ʵ��
static int objScount,objMcount,objSmcount; //����ȫ�ֱ�������ʵ�ֶԸ�����Ա��������ͳ��

StaffManage::StaffManage ()                       //���캯�� ��ȫ�������ݶ����ڴ��У������Ժ���ļ��Ĳ���
{
	ifstream indexFile("staff.idx",ios::binary); //�Զ������ļ������ӵ��������ļ�
	if (!indexFile.fail())
	{                                                             //�ɹ����ļ�
		indexFile.seekg(0,ios::end);                    //���ļ�ĩβ��ʼ���ļ�
		count=indexFile.tellg() / sizeof(IndexType);    //���������=���ص�ǰָ��λ��ʵ�����ļ����Ĵ�С/�����Ĵ�С
		maxSize=count+NUM_OF_INCREMENT;    //���������������
		indexTable=new IndexType[maxSize];       //Ϊ����������ڴ�   
		indexFile.seekg(0,ios::beg);                       //��ͷ��ʼ���μ���
		int i=0;
		indexFile.read((char*)&indexTable[i++],sizeof(IndexType));//�������ļ�������������ݶ����ڴ���
		while(!indexFile.eof())
		{ 
			indexFile.read((char*)&indexTable[i++],sizeof(IndexType));    //ֱ������Ϊֹ

		}
		indexFile.close();                                               //�ر��ļ�
	}
	else
	{                                                                      //���ļ�ʧ��
		count=0;                                                     //���������
		maxSize=count+NUM_OF_INCREMENT;      //���������             
		indexTable=new IndexType[maxSize];          //Ϊ����������ڴ� 
	}
	//���캯���д����ļ�
	ifstream iFile("staff.dat");                               //�Զ�ģʽ�����ļ����洢Ա�����ݵ��ļ���
	if(iFile.fail())                                                  //���ܴ򿪱�ʾ�������ļ�
	{
		ofstream oFile("staff.dat");                      //��������ļ�             
		if (oFile.fail())throw("���ļ�ʧ�ܣ�");     //�׳��쳣
		oFile.close();                                          //�ر��ļ�
	}
	else
	{
		iFile.close();                                                   //�ر��ļ�                                        
	}
	file.open("staff.dat",ios::in|ios::out|ios::binary);    //�����ڶ�ȡ ������� ������ģʽ���ļ�                 
	if(file.fail())throw("���ļ�ʧ�ܣ�");                   //�׳��쳣  
}
//����������ʵ��
StaffManage::~StaffManage()
{
	ofstream indexFile("staff.idx",ios::binary);                       //дģʽ��������������ļ�   ���ڽ��ڴ��еĶ����ͷŵ���������
	for (int i=0;i<count;i++)
	{                                                                               
		indexFile.write((char*)&indexTable[i],sizeof(IndexType)); //д������  (��������д���ļ���)
	}
	indexFile.close();                                                    //�ر��������ļ�
	file.close();                                                           //�ر�staff.dat   �ڹ��캯���б�����

}
//�����������������������ʵ��
void StaffManage::AddIndexItem(const IndexType&e) 
{
	if(count>=maxSize)
	{//���������(������������������)
		maxSize=maxSize+NUM_OF_INCREMENT;                 //���������������
		IndexType*tmpIndexTable=new IndexType[maxSize]; //��̬������ʱ����������
		for(int i=0;i<count;i++)                                           //ѭ����ȡ������
			tmpIndexTable[i]=indexTable[i];                            //����������(���ɵ��������еĶ��������Ƶ���ʱ����)
		delete[]indexTable;                                                  //�ͷŻ����ڴ�
		indexTable=tmpIndexTable;                                 //ָ����ʱ���������������������������ֽ���indexTable�����Ժ�ʹ�ò�����������ˣ�
	}
	indexTable[count++]=e;                                               // ��������뵽��������      
}
//AddData()������ʵ��  ���������ָ��ʵ����Ϊ��ͬ����ͨ��for���ʵ�ֶ����������ͬʱ�������ļ�������¼
void StaffManage::AddData()
{
	Staff*pStaff;                       //����ָ������� 
	IndexType item;                 //������
	item.delTag=false;              //ɾ����־
	char UserSaysYes;            
	file.seekg(0,ios::end);         //��λ��ĩβ��ʼ ƫ����Ϊ0
	do
	{
		do
		{cout<<"��Ա���ͣ�s:������Ա��m������b:���۾���:";
		cin>>item.staffType;                                           //������Ա����
		item.staffType=tolower(item.staffType);              //ת��ΪСд��
		}while(item.staffType!='s'&&item.staffType!='m'&&item.staffType!='b');
		if (item.staffType=='s')
		{ 
			pStaff=new Saleman;  //ʵ����Ϊ���� �����ڴ�ռ�
			objScount++;             //����
		}
		else if(item.staffType=='m') 
		{
			pStaff=new Manager;            //ʵ����Ϊ���� �����ڴ�ռ�
			objMcount++;                      //����
		}
		else 
		{
			pStaff=new SaleManager;  //ʵ����Ϊ���� �����ڴ�ռ�
			objSmcount++;                 //����
		}                            
		pStaff->Input();                                        //���ú�������Ա����Ϣ
		strcpy(item.num,pStaff->GetNum());        //���Ʊ��    �����������������������
		strcpy(item.age,pStaff->GetAge());           //��������  �����������������������
		strcpy(item.name,pStaff->GetName());     //��������      ���������������������
		strcpy(item.fname,pStaff->GetFname());  //��������  ���������������������
		strcpy(item.sname,pStaff->GetSname());  //������  �������������������
		item.position=file.tellg();                       //��λ����ǰ�ļ���ָ���λ�ã�
		AddIndexItem(item);                            //��������������������        
		pStaff->Write(file);                              //��Ա�������ļ���д��ͨ�����������Ա����Ϣ
		delete pStaff;                                      //�ͷ��ڴ�
		cout<<"�������ô?";
		cin>>UserSaysYes;   
		cout<<endl;                                   
		UserSaysYes=tolower(UserSaysYes);  //ת��ΪСд
	}
	while(UserSaysYes=='y');                   //�߼��������==       �ж��Ƿ����¼��Ա����Ϣ                                          
}
//�������ݺ�����ʵ�� ͨ����Ų��Һ���ʾ�������������ĺ������д�룬ͬʱ��Բ�ͬ����������ļ�ʵ�ֲ�ͬ�Ĳ���
void StaffManage::UpdateData()
{
	Staff*pStaff;               //��������ָ�������           
	IndexType item;         //������                                                          
	item.delTag=false;     //ɾ����־                                                   
	char num[12];           //��Ա���
	cout<<"��Ա��ţ�";
	cin>>num;               //������                                                     
	int pos;                    //��ʱ����                                                  
	for(pos=0;pos<count;pos++)
	{                               //����������  
		if(strcmp(num,indexTable[pos].num)==0 && !indexTable[pos].delTag)  //�����ͬ δ�����ɾ��
			break;                                                                                              //����ѭ��
	}
	if (pos<count)
	{                                                                                           //��ѯ�ɹ�
		file.seekg(indexTable[pos].position,ios::beg);                      //��ͷ��ʼ��λ
		if(indexTable[pos].staffType=='s') pStaff=new Saleman;    //ʵ������ͬ�Ķ���  Ϊ������ڴ�ռ�
		else if (indexTable[pos].staffType=='m') pStaff=new Manager;
		else pStaff=new SaleManager;
		pStaff->Read(file);                                                            //���ļ��ж�Ա����Ϣ
		pStaff->Show();                                                                //��Ա����Ϣ��ʾ����
		do
		{    //����Ҫ�޸ĵ�Ա�������ͣ��޸ĺ�ģ�
			cout<<"��Ա���ͣ�s:������Ա��m������b:���۾���:";
			cin>>item.staffType;                                                                           //������Ա����
			item.staffType=tolower(item.staffType);                                                //��дת��ΪСд
		}while(item.staffType!='s'&&item.staffType!='m' &&item.staffType!='b');   //ʵ������ͬ�Ķ���  Ϊ������ڴ�ռ�
		if (item.staffType=='s') pStaff=new Saleman;
		else if(item.staffType=='m') pStaff=new Manager;
		else pStaff=new SaleManager;
		pStaff->Input();                                                                         //����Ա����Ϣ
		//��Բ�ͬ�������������в�ͬ�Ĳ���
		if(item.staffType==indexTable[pos].staffType)
		{//��Ա����δ��
			strcpy(indexTable [pos].num,pStaff->GetNum());                  //���Ʊ�ŵ���������
			strcpy(item.age,pStaff->GetAge());           //��������  �����������������������
			strcpy(item.name,pStaff->GetName());     //��������      ���������������������
			strcpy(item.fname,pStaff->GetFname());  //��������  ���������������������
			strcpy(item.sname,pStaff->GetSname());  //������  �������������������
			file.seekg(indexTable[pos].position,ios::beg);                         //��ͷ��ʼ��λ
		}                                                                         
		else
		{
			indexTable[pos].delTag=true;               //���ɵı����ɾ����־  �����Ժ�ɾ��
			strcpy(item.num,pStaff->GetNum());    //���Ʊ�� ���������
			strcpy(item.age,pStaff->GetAge());           //��������  �����������������������
			strcpy(item.name,pStaff->GetName());     //��������      ���������������������
			strcpy(item.fname,pStaff->GetFname());  //��������  ���������������������
			strcpy(item.sname,pStaff->GetSname());  //������  �������������������
			file.seekg(0,ios::end);                       //��λ�����ļ�ĩβ����ʼ��
			item.position=file.tellg();                 //д�������ļ���λ�� ��������������¼�����ص�ǰ�ļ���λָ���λ�ã�
			AddIndexItem(item);                       //����������
		}
		pStaff->Write(file);                            //���ļ���д����Ա��Ϣ
		delete pStaff;                                    //�ͷ��ڴ�
	}
	else
	{
		cout<<"���޴��ˣ�"<<endl;
		file.clear();                              //������б���ı�����ͬ������øñ���������������������
	}
}
//��������SearchData()������ʵ��  ͨ����Ż�����ʵ�ֲ�ѯͨ��������ѯʱ���루������ʱ��ʵ��ģ����ѯ
void StaffManage::SearchData()
{
	Staff*pStaff;             //��������
	char num[20];          //���
	char name[20];        //����
	int select;                //ѡ��
	int pos=0;  
	cout<<"1������Ա������ң�2:����������;"<<endl;
	cout<<"������ѡ��\tѡ��";
	cin>>select;
	switch(select)
	{
	case 1:
		cout<<"������Ҫ���ҵ���Ա���룺";
		cin>>num;
		for(pos=0;pos<count;pos++)
		{    //�����������������������������
			if(strcmp(num,indexTable[pos].num)==0&&  //�����ͬ
				!indexTable[pos].delTag)                           //δ��ɾ��
			{	
				cout<<"���ҳɹ���"<<endl;
				break;
			}
		}
		if(pos<count)
		{//���ҳɹ�
			file.seekg(indexTable[pos].position,ios::beg);                      //��ͷ��ʼ��λ
			if(indexTable[pos].staffType=='s')pStaff=new Saleman;   //�����ڴ�ռ�  ʵ����Ϊ��ͬ����
			else if(indexTable[pos].staffType=='m')pStaff=new Manager;
			else pStaff=new SaleManager;
			pStaff->Read(file);                                                        //��ȡԱ����Ϣ
			pStaff->Show();                                                          //��ʾԱ����Ϣ
			delete pStaff;                                                             //�ͷ��ڴ�
		}
		else
		{
			cout<<"���޴��ˣ�"<<endl;
			file.clear();                                                          //������б���ı�����ͬ������øñ���������������������
		}
		break;
	case 2:
		cout<<"�Ƿ�Ϊ����:(1.���ǣ�2.��)";
		int  flag;     //��������  ���ݱ���ʵ�ָ����뵥���յ�ѡ����ʵ�ֲ�ͬ�ķ���
		cin>>flag;
		switch(flag)
		{
		case 1:
			cout<<"������Ҫ���ҵ���(��):";
			cin>>name;        //��������
			if(strlen(name)==2)
			{         //�������Ϊ2 ���ж������������
				for( int pos=0;pos<count;pos++)
				{//������������ҷ����������  ������ͬ�������
					if(strcmp(name,indexTable[pos].fname)==0/*&&strcmp(sname,indexTable[pos].sname)==0*/&&!indexTable[pos].delTag) 
					{  //����Ϊ(��)����ʱ ����������ͬ��
						if(pos<count)
						{                  //���ҳɹ�
							file.seekg(indexTable[pos].position,ios::beg);                      //��ͷ��ʼ��λ
							if(indexTable[pos].staffType=='s')pStaff=new Saleman;   //�����ڴ�ռ�  ʵ����Ϊ��ͬ����
							else if(indexTable[pos].staffType=='m')pStaff=new Manager;
							else pStaff=new SaleManager;
							pStaff->Read(file);                                                        //��ȡԱ����Ϣ
							pStaff->Show();                                                          //��ʾԱ����Ϣ
							delete pStaff;            //�ͷ��ڴ�
						}
					} 
				}
			}
			else 
			{  //�������ȫ��,ʵ�־�ȷ����
				for(int pos=0;pos<count;pos++)     //���������� 
				{         
					if(strcmp(name,indexTable[pos].name)==0&&!indexTable[pos].delTag)
					{ //������ͬ,δ��ɾ��
						file.seekg(indexTable[pos].position,ios::beg);                    //��ͷ��ʼ��λ
						if(indexTable[pos].staffType=='s')pStaff=new Saleman;   //�����ڴ�ռ�  ʵ����Ϊ��ͬ����
						else if(indexTable[pos].staffType=='m')pStaff=new Manager;
						else pStaff=new SaleManager;
						pStaff->Read(file);                                                        //��ȡԱ����Ϣ
						pStaff->Show();                                                          //��ʾԱ����Ϣ
						delete pStaff;            //�ͷ��ڴ�
					}
				}
			}

			break;	
		case 2:
			cout<<"������Ҫ���ҵ���(��):";
			cin>>name;
			if(strlen(name)==4)//����Ǹ���
			{
				for( int pos=0;pos<count;pos++) //��������ҷ���Ҫ������� 
				{
					if(strcmp(name,indexTable[pos].fname)==0&&!indexTable[pos].delTag) 
					{  //������������ҷ����������  ������ͬ�������
						if(pos<count)
						{  //������ҳɹ�
							file.seekg(indexTable[pos].position,ios::beg);                      //��ͷ��ʼ��λ
							if(indexTable[pos].staffType=='s')pStaff=new Saleman;   //�����ڴ�ռ�  ʵ����Ϊ��ͬ����
							else if(indexTable[pos].staffType=='m')pStaff=new Manager;
							else pStaff=new SaleManager;
							pStaff->Read(file);                                                        //��ȡԱ����Ϣ
							pStaff->Show();                                                          //��ʾԱ����Ϣ
							delete pStaff;            //�ͷ��ڴ�
						}
					} 

				}
			}
			else //�������ȫ��,ʵ�־�ȷ����
			{
				for(int pos=0;pos<count;pos++)  //��������ҷ���Ҫ������� 
				{   
					if(strcmp(name,indexTable[pos].name)==0&&!indexTable[pos].delTag)  //������������ҷ����������  ������ͬ�������
					{break;}
				}
				if (pos<count)
				{
					file.seekg(indexTable[pos].position,ios::beg);                      //��ͷ��ʼ��λ
					if(indexTable[pos].staffType=='s')pStaff=new Saleman;   //�����ڴ�ռ�  ʵ����Ϊ��ͬ����
					else if(indexTable[pos].staffType=='m')pStaff=new Manager;
					else pStaff=new SaleManager;
					pStaff->Read(file);                                                        //��ȡԱ����Ϣ
					pStaff->Show();                                                          //��ʾԱ����Ϣ
					delete pStaff;            //�ͷ��ڴ�
				}
				else{cout<<"���޴���!"<<endl;}
			}
			break;	
		}	
	}
}
//ͳ�ƺ�����ʵ��    ʵ�ֲ�ѯ�������Ͳ�ѯ����Ա�����͵�����
void  StaffManage::Stat()
{
	char UserSays;
	do
	{
		cout<<"��ѡ��1.��ѯ��������2.��ѯ����Ա�������͵ĵ�������"<<endl;
		cout<<"���������ѡ��:";
		int choice;
		cin>>choice;
		switch(choice)                                                  //��switch����ѯ������ ������Ա��������  
		{
		case 1:
			cout<<"�Ƿ��ѯ��������";
			char UserSaysYes;
			cin>>UserSaysYes;
			UserSaysYes=tolower(UserSaysYes);           //ת��ΪСд
			if(UserSaysYes=='y')                                  //�ж��Ƿ����������
				cout<<"������Ϊ��"<<count<<endl;      // ���������
			break;
		case 2:
			char UserSay;
			do
			{
				cout<<"��ѡ����Ҫ��ѯ����Ա���͵�������s:������Ա��m������b:���۾���";
				char objStaff;       //��������
				cin>>objStaff;       
				if(objStaff=='s')          
				{
					cout<<"������Աһ���У�"<<objScount<<"��!"<<endl;                             //���������Ա����
				}
				else if(objStaff=='m')cout<<"����һ���У�"<<objMcount<<"��!"<<endl;       //���������Ա����
				else
					cout<<"���۾���һ���У�"<<objSmcount<<"��!"<<endl;                               //������۾�������
				cout<<"�����������ѯ��(y/n)";
				cin>>UserSay;
			}
			while(UserSay=='y'||UserSay=='Y');          //�ж��Ƿ������ѯ
			break;
		default:
			cout<<"���ִ���!"<<endl;
			break;
		}
		cout<<"�Ƿ������ѯͳ������:";
		cin>>UserSays;
	}while(UserSays=='Y'||UserSays=='y');

	file.clear();                                        //������б���ı�����ͬ������øñ���������������������
}

//ɾ�����ݵ�ʵ�֣�ֻ�ǶԽ�Ҫɾ����Ա����Ϣ�����  ��δ����ʵɾ��  �������ļ���ʵ�������ϵ�ɾ����
void StaffManage::DeleteData()
{
	Staff*pStaff;                            //������������ָ��
	IndexType item;                    //������
	item.delTag=false;              //ɾ����־
	char num[20];                    //���
	cout<<"��Ա���룺";
	cin>>num;
	int pos;
	for (pos=0;pos<count;pos++)
	{                                                                        //  ���������� ��������������������
		if(strcmp(num,indexTable[pos].num)==0&&  //�����ͬ
			!indexTable[pos].delTag)                            //δ��ɾ��
			break;
	}
	if(pos<count)
	{ //��ѯ�ɹ�
		file.seekg(indexTable[pos].position,ios::beg);            //��λ
		if(indexTable[pos].staffType=='s')
		{
			pStaff=new Saleman;         //�����ڴ�ռ� ʵ����Ϊ��ͬ����
			objScount--;                     //����  ɾ�����Լ�
		}

		else if(indexTable[pos].staffType=='m') 
		{
			pStaff=new Manager;        //�����ڴ�ռ� ʵ����Ϊ��ͬ����
			objMcount--;                    //����  ɾ�����Լ�
		}
		else 
		{
			pStaff=new SaleManager;   //�����ڴ�ռ� ʵ����Ϊ��ͬ����
			objMcount--;                     //����  ɾ�����Լ�
		}
		pStaff->Read(file);                                                       //���ú�����ȡԱ����Ϣ������Ҫɾ���ģ�
		cout<<"��ɾ����¼Ϊ��"<<endl;
		pStaff->Show();                                                          //��ʾ����Ļ��
		indexTable[pos].delTag=true;                                     //����ɾ����־
		delete  pStaff;                                                           //�ͷ��ڴ�ռ�
		cout<<"ɾ���ɹ���"<<endl;
	}
	else{
		cout<<"ɾ��ʧ�ܣ�"<<endl;
		file.clear();                                                                //������б���ı�����ͬ������øñ���������������������
	}
}
//�����ļ�������ʵ��(ʵ���ϵ�ɾ���ļ�  ����һ���µ��ļ����ڽ�δ
//��ɾ����ǵ�Ա����Ϣд�� ���˱�ǵı�����ԭ�����ļ��� 
//��󽫾��ļ�ɾ�� �������ļ�����Ϊ���ļ���   ͬʱ������ʱ����ʵ�ֶ�������Ĵ��� ʵ���ļ���ɾ��)
void StaffManage::Pack()
{
	ofstream oFile("tem.dat");                                //��дģʽ��ʱ�����ļ��������ļ���д��δ����ǵ�Ա����Ϣ
	oFile.close();                                                     //�ر��ļ�
	fstream outFile("tem.dat",ios::app|ios::binary); // �����ļ����� ׷�ӵ��ļ�ĩβ ���Զ�������ʽ��
	Staff*pStaff;                                                  //����ָ����������
	int cur_cout=0;                                          //��ʱ���� ��������ĸ���
	for(int pos=0;pos<count;pos++)
	{//�����������е�ÿһ��     ��δ��ɾ����ǵ�Ա����Ϣд���´������ļ���
		if(!indexTable[pos].delTag)
		{//δ��ɾ��
			file.seekg(indexTable[pos].position,ios::beg);                       //��ͷ��ʼ��λ
			indexTable[pos].position=outFile.tellg();                          //���ļ���д��λ��(��λ����ǰ�ļ���ָ���λ��)
			if(indexTable[pos].staffType=='s')pStaff=new Saleman;   //�����ڴ�ռ�   ʵ����Ϊ��ͬ����
			else if(indexTable[pos].staffType=='m')pStaff=new Manager;
			else pStaff=new SaleManager;
			pStaff->Read(file);                                                //�Ӿ��ļ��ж�ȡԱ����Ϣ
			pStaff->Write(outFile);                                          //����ȡ��Ա����Ϣд�����ļ���
			delete pStaff;                                                     //�ͷ��ڴ�
			indexTable[cur_cout++]=indexTable[pos];           //������Ƶ���λ��(���¼���������ĸ���д����������)
		}
	}
	count=cur_cout;                                                       //��������ĸ���
	file.close();                                                              //�ر��ļ�
	outFile.close();
	remove("staff.dat");                                               //ɾ�����ļ�
	rename("tem.dat","staff.dat");                               //�����ļ���������Ϊ�����ļ�������
	file.open("staff.dat",ios::in|ios::out|ios::binary);       //���´��ļ�(������������Զ�����ģʽ��)
}
//���㹤�ʺ�����ʵ��  ͨ��������Ա������ʵ�ֲ��������
void StaffManage::CacS()
{
	Staff*pStaff;                                       //���������ָ��
	char name[20];                                  //����
	char num[20];                                    //���
	char usersay;                                     //��������
	int pos;
	char type;
	do
	{
		cout<<"������ѡ��(1.ͨ��������2.ͨ�����,3.�������Ա�����ʣ�4.��������������):";
		int select;          //��������
		cin>>select;      //����ѡ��
		switch(select)
		{
		case 1:
			cout<<"������Ҫ������˵�����:";	
			cin>>name;
			for( int pos=0;pos<count;pos++) 
			{//������������ҷ���Ҫ���������           
				if(strcmp(name,indexTable[pos].name)==0&&!indexTable[pos].delTag)//������ͬδ��ɾ��
				{                                                   
					file.seekg(indexTable[pos].position,ios::beg);                                //��λ
					if(indexTable[pos].staffType=='s')pStaff=new Saleman;                 //�����ڴ�ռ� ʵ����Ϊ��ͬ����
					else if(indexTable[pos].staffType=='m')pStaff=new Manager;
					else pStaff=new SaleManager;
					pStaff->Read(file);                                                                       //���ú������ļ��еĶ��������ڴ���
					cout<<pStaff->GetNum()<<"\t����:"<<pStaff->GetSalary()<<endl;                              //���ú������㹤�ʲ������
					delete pStaff;                                                                               //�ͷ��ڴ�
				}
				else continue;
			}
			break;
		case 2:
			cout<<"������Ҫ�������Ա���룺";
			cin>>num;
			for(int pos=0;pos<count;pos++)                                                       //�����������������������������
				if(strcmp(num,indexTable[pos].num)==0&&!indexTable[pos].delTag)    //�����ͬδ��ɾ��
				{     
					if(pos<count)                                                                       //���ҳɹ�
					{
						file.seekg(indexTable[pos].position,ios::beg);                                 //��λ
						if(indexTable[pos].staffType=='s')pStaff=new Saleman;                //�����ڴ�ռ� ʵ����Ϊ��ͬ����
						else if(indexTable[pos].staffType=='m')pStaff=new Manager;
						else pStaff=new SaleManager;
						pStaff->Read(file);                                                                        //���ú������ļ��еĶ��������ڴ���
						cout<<pStaff->GetName()<<"\t����:"<<pStaff->GetSalary()<<endl;                               //���ú������㹤�ʲ������
						delete pStaff;  //�ͷ��ڴ�
						break;
					}	
					else  cout<<"���˲����ڣ������Ƿ�������ȷ��";

				}
				break;
		case 3:
			cout<<"������Ҫ�����Ա������(s:������Ա��}m������b:���۾���):";
			cin>>type;
			if(type=='s')         //���Saleman���Ա���Ĺ���
			{
				for(int pos=0;pos<count;pos++)
				{
					file.seekg(indexTable[pos].position,ios::beg);                               //��λ
					if(indexTable[pos].staffType=='s')  pStaff=new Saleman;          //�����ڴ�ռ� ʵ����Ϊ��ͬ��
					else continue;                                                                        //���û�д������ ������ѭ��
					pStaff->Read(file);                                                                 //���ú������ļ��еĶ��������ڴ���
					cout<<pStaff->GetName()<<setw(5)<<"\t����:"<<pStaff->GetSalary()<<endl;        //��������ʾ����
					delete pStaff;
				}
			}
			else if(type=='m')     //���Manager���Ա���Ĺ���
			{
				for(int pos=0;pos<count;pos++)
				{
					file.seekg(indexTable[pos].position,ios::beg);                            //��λ
					if(indexTable[pos].staffType=='m')  pStaff=new Manager;      //�����ڴ�ռ� ʵ����Ϊ��ͬ����
					else continue;                                                                       //���û�д������ ������ѭ��
					pStaff->Read(file);                                                               //���ú������ļ��еĶ��������ڴ���
					cout<<pStaff->GetName()<<setw(5)<<"\t����:"<<pStaff->GetSalary()<<endl;        //��������ʾ����
					delete pStaff;                                                                 // �ͷ��ڴ�
				}
			}
			else 
			{
				for(int pos=0;pos<count;pos++)  //���������� 
				{
					file.seekg(indexTable[pos].position,ios::beg);                            //��λ
					if(indexTable[pos].staffType=='b')  pStaff=new SaleManager;  //�����ڴ�ռ� ʵ����Ϊ��ͬ����
					else continue;         //���û�д������ ������ѭ��
					pStaff->Read(file);                                                                 //���ú������ļ��еĶ��������ڴ���
					cout<<pStaff->GetName()<<setw(5)<<"\t����:"<<pStaff->GetSalary()<<endl;        //��������ʾ����
					delete pStaff;
				}
			}
			break;
		case 4:
			cout<<"�����Ҫ����������:";
			char firAge[20];char lasAge[20];         //��������
			cin>>firAge>>lasAge;                     //���������ֵ
			for(int pos=0;pos<count;pos++)          //���������� ���ҷ��ϵ���
			{ 
				if(atoi(firAge)<atoi(indexTable[pos].age)&&atoi(indexTable[pos].age)<=atoi(lasAge)&&!indexTable[pos].delTag)
				{        //��atoi()������char*ת��Ϊ���ֽ��бȽ�
					if(pos<count)                                                                  //������ҳɹ�
					{
						file.seekg(indexTable[pos].position,ios::beg);                      //��ͷ��ʼ��λ
						if(indexTable[pos].staffType=='s')pStaff=new Saleman;   //�����ڴ�ռ�  ʵ����Ϊ��ͬ����
						else if(indexTable[pos].staffType=='m')pStaff=new Manager;
						else pStaff=new SaleManager;
						pStaff->Read(file);                                                        //��ȡԱ����Ϣ
						pStaff->Show();                                                          //��ʾԱ����Ϣ
						delete pStaff;            //�ͷ��ڴ�
					}
				}
			}
			break;
		}
		cout<<"�Ƿ�������㹤�ʣ�";
		cin>>usersay;
	}while(usersay=='y'||usersay=='Y');
}

//Run()������ʵ�֣�����ɾ�Ĳ�Ⱥ�������ͳһ����  ʹ�û�ʹ�õĽ�������ࣩ
void  StaffManage::Run()
{
	int i;
	cout<<setw(60)<<"**********��ӭ��¼���۹�˾Ա������ϵͳ**********"<<endl;
	char depass[9]="yg123456";
	char password[20];
	for( i=0;i<3;i++)
	{
		cout<<"�������¼����:";
		cin>>password;
		if(strcmp(depass,password)==0)   //���������ȷ
		{  
			cout<<setw(60)<<"**********��ӭ�������۹�˾Ա������ϵͳ**********"<<endl;
			int select;
			i=4;
			do
			{
				cout<<setw(40)<<"��ѡ��:"<<endl;
				cout<<setw(43)<<"1.��������"<<endl;
				cout<<setw(43)<<"2.��������"<<endl;
				cout<<setw(43)<<"3.��ѯ����"<<endl;	
				cout<<setw(43)<<"4.ɾ������"<<endl;
				cout<<setw(43)<<"5.��������"<<endl;
				cout<<setw(43)<<"6.���㹤��"<<endl;
				cout<<setw(43)<<"7.ͳ������"<<endl;
				cout<<setw(39)<<"8.�˳�"<<endl;
				cout<<"���������ѡ��:";
				cin>>select;
				while(cin.get()!='\n');
				switch(select)
				{
				case 1:
					AddData();        //��������
					break;
				case 2:
					UpdateData();   //��������
					break;
				case 3:
					SearchData();    //��������
					break;
				case 4:
					DeleteData();    //ɾ������
					break;
				case 5:
					Pack();             //�����ļ�
					break;
				case 6:
					CacS();            //���㹤��
					break;
				case 7:
					Stat();            //ͳ������
					break;
				}
			}while(select!=8);
		}
		else        //�������
		{
			cout<<"����������ٴ�����"<<endl;
		}
	}

	if(i==3)   
	{  //�������������
		cout<<"��½ʧ��!"<<endl;
	}
	else
	{
		cout<<"ллʹ��!"<<endl;
	}
}

