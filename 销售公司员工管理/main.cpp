#include "company_staff.h"
#include "staff_manage.h"
int main(void)                                               //������
{
	try                                                          //������쳣������
	{                                                             //���ܻ���ִ���ĺ���
	StaffManage objSM ;                             //����һ��Ա�����ݹ���Ķ���
	objSM.Run();                                        //���ó�Ա����Run()����ʵ�ֲ���
	}
	 catch(char /*error  char*error*/ /*...*/)   // ���Ϊchar ����char���쳣  ���Ϊ...���������쳣         
	{
	cout<<"error!";                                   // �쳣������򣬲�����throw���ʽ�׳����쳣
	}
system("PAUSE");                                  //�⺯��������Ļ���õĹ۲����
return 0;
}