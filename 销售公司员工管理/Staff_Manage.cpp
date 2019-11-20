#include "Staff_Manage.h"
#include "company_staff.h"
#include "IndexType.h"
#include <iostream>
#include <string>
using namespace std;
//员工管理类的实现
static int objScount,objMcount,objSmcount; //声明全局变量用于实现对各类型员工的人数统计

StaffManage::StaffManage ()                       //构造函数 将全部的数据读到内存中，便于以后对文件的操作
{
	ifstream indexFile("staff.idx",ios::binary); //以二进制文件打开连接到索引表文件
	if (!indexFile.fail())
	{                                                             //成功打开文件
		indexFile.seekg(0,ios::end);                    //从文件末尾开始读文件
		count=indexFile.tellg() / sizeof(IndexType);    //索引项个数=返回当前指针位置实际是文件流的大小/索引的大小
		maxSize=count+NUM_OF_INCREMENT;    //索引表最大索引项
		indexTable=new IndexType[maxSize];       //为索引表分配内存   
		indexFile.seekg(0,ios::beg);                       //从头开始依次检索
		int i=0;
		indexFile.read((char*)&indexTable[i++],sizeof(IndexType));//将索引文件中索引表的内容读到内存中
		while(!indexFile.eof())
		{ 
			indexFile.read((char*)&indexTable[i++],sizeof(IndexType));    //直到读完为止

		}
		indexFile.close();                                               //关闭文件
	}
	else
	{                                                                      //打开文件失败
		count=0;                                                     //索引项个数
		maxSize=count+NUM_OF_INCREMENT;      //最大索引项             
		indexTable=new IndexType[maxSize];          //为索引表分配内存 
	}
	//构造函数中创建文件
	ifstream iFile("staff.dat");                               //以读模式创建文件（存储员工数据的文件）
	if(iFile.fail())                                                  //不能打开表示不存在文件
	{
		ofstream oFile("staff.dat");                      //创建输出文件             
		if (oFile.fail())throw("打开文件失败！");     //抛出异常
		oFile.close();                                          //关闭文件
	}
	else
	{
		iFile.close();                                                   //关闭文件                                        
	}
	file.open("staff.dat",ios::in|ios::out|ios::binary);    //以用于读取 用于输出 二进制模式打开文件                 
	if(file.fail())throw("打开文件失败！");                   //抛出异常  
}
//析构函数的实现
StaffManage::~StaffManage()
{
	ofstream indexFile("staff.idx",ios::binary);                       //写模式建立输出索引表文件   用于将内存中的东西释放到索引表中
	for (int i=0;i<count;i++)
	{                                                                               
		indexFile.write((char*)&indexTable[i],sizeof(IndexType)); //写索引表  (将索引表写到文件中)
	}
	indexFile.close();                                                    //关闭索引表文件
	file.close();                                                           //关闭staff.dat   在构造函数中被打开了

}
//在索引表中增加索引项函数的实现
void StaffManage::AddIndexItem(const IndexType&e) 
{
	if(count>=maxSize)
	{//索引表溢出(索引项大于最大索引项)
		maxSize=maxSize+NUM_OF_INCREMENT;                 //增加索引项的容量
		IndexType*tmpIndexTable=new IndexType[maxSize]; //动态创建临时索引表用于
		for(int i=0;i<count;i++)                                           //循环读取索引表
			tmpIndexTable[i]=indexTable[i];                            //复制索引表(将旧的索引表中的东西都复制到临时表中)
		delete[]indexTable;                                                  //释放回收内存
		indexTable=tmpIndexTable;                                 //指向临时索引表（即扩大了容量的索引表又叫做indexTable便于以后使用不过容量变大了）
	}
	indexTable[count++]=e;                                               // 索引项加入到索引表中      
}
//AddData()函数的实现  创建基类的指针实例化为不同对象通过for语句实现多次输入数据同时在索引文件中做记录
void StaffManage::AddData()
{
	Staff*pStaff;                       //对象指针的声明 
	IndexType item;                 //索引项
	item.delTag=false;              //删除标志
	char UserSaysYes;            
	file.seekg(0,ios::end);         //定位从末尾开始 偏移量为0
	do
	{
		do
		{cout<<"人员类型（s:销售人员，m：经理，b:销售经理）:";
		cin>>item.staffType;                                           //输入人员类型
		item.staffType=tolower(item.staffType);              //转化为小写的
		}while(item.staffType!='s'&&item.staffType!='m'&&item.staffType!='b');
		if (item.staffType=='s')
		{ 
			pStaff=new Saleman;  //实例化为对象 分配内存空间
			objScount++;             //计数
		}
		else if(item.staffType=='m') 
		{
			pStaff=new Manager;            //实例化为对象 分配内存空间
			objMcount++;                      //计数
		}
		else 
		{
			pStaff=new SaleManager;  //实例化为对象 分配内存空间
			objSmcount++;                 //计数
		}                            
		pStaff->Input();                                        //调用函数输入员工信息
		strcpy(item.num,pStaff->GetNum());        //复制编号    用于向索引表中添加索引项
		strcpy(item.age,pStaff->GetAge());           //复制年龄  用于向索引表中添加索引项
		strcpy(item.name,pStaff->GetName());     //复制姓名      用于向索引表中添加姓名
		strcpy(item.fname,pStaff->GetFname());  //复制姓氏  用于向索引表中添加姓氏
		strcpy(item.sname,pStaff->GetSname());  //复制名  用于向索引表中添加名
		item.position=file.tellg();                       //定位（当前文件读指针的位置）
		AddIndexItem(item);                            //在索引表中增加索引项        
		pStaff->Write(file);                              //向员工数据文件中写入通过键盘输入的员工信息
		delete pStaff;                                      //释放内存
		cout<<"继续添加么?";
		cin>>UserSaysYes;   
		cout<<endl;                                   
		UserSaysYes=tolower(UserSaysYes);  //转化为小写
	}
	while(UserSaysYes=='y');                   //逻辑运算符是==       判断是否继续录入员工信息                                          
}
//更新数据函数的实现 通过编号查找后显示出来，并将更改后的数据写入，同时针对不同情况对索引文件实现不同的操作
void StaffManage::UpdateData()
{
	Staff*pStaff;               //基类对象的指针的声明           
	IndexType item;         //索引项                                                          
	item.delTag=false;     //删除标志                                                   
	char num[12];           //人员编号
	cout<<"人员编号：";
	cin>>num;               //输入编号                                                     
	int pos;                    //临时变量                                                  
	for(pos=0;pos<count;pos++)
	{                               //遍历索引表  
		if(strcmp(num,indexTable[pos].num)==0 && !indexTable[pos].delTag)  //编号相同 未被标记删除
			break;                                                                                              //跳出循环
	}
	if (pos<count)
	{                                                                                           //查询成功
		file.seekg(indexTable[pos].position,ios::beg);                      //从头开始定位
		if(indexTable[pos].staffType=='s') pStaff=new Saleman;    //实例化不同的对象  为其分配内存空间
		else if (indexTable[pos].staffType=='m') pStaff=new Manager;
		else pStaff=new SaleManager;
		pStaff->Read(file);                                                            //从文件中读员工信息
		pStaff->Show();                                                                //将员工信息显示出来
		do
		{    //输入要修改的员工的类型（修改后的）
			cout<<"人员类型（s:销售人员，m：经理，b:销售经理）:";
			cin>>item.staffType;                                                                           //输入人员类型
			item.staffType=tolower(item.staffType);                                                //大写转化为小写
		}while(item.staffType!='s'&&item.staffType!='m' &&item.staffType!='b');   //实例化不同的对象  为其分配内存空间
		if (item.staffType=='s') pStaff=new Saleman;
		else if(item.staffType=='m') pStaff=new Manager;
		else pStaff=new SaleManager;
		pStaff->Input();                                                                         //输入员工信息
		//针对不同情况对索引表进行不同的操作
		if(item.staffType==indexTable[pos].staffType)
		{//人员类型未变
			strcpy(indexTable [pos].num,pStaff->GetNum());                  //复制编号到索引表中
			strcpy(item.age,pStaff->GetAge());           //复制年龄  用于向索引表中添加索引项
			strcpy(item.name,pStaff->GetName());     //复制姓名      用于向索引表中添加姓名
			strcpy(item.fname,pStaff->GetFname());  //复制姓氏  用于向索引表中添加姓氏
			strcpy(item.sname,pStaff->GetSname());  //复制名  用于向索引表中添加名
			file.seekg(indexTable[pos].position,ios::beg);                         //从头开始定位
		}                                                                         
		else
		{
			indexTable[pos].delTag=true;               //将旧的标记上删除标志  用于以后删除
			strcpy(item.num,pStaff->GetNum());    //复制编号 添加索引项
			strcpy(item.age,pStaff->GetAge());           //复制年龄  用于向索引表中添加索引项
			strcpy(item.name,pStaff->GetName());     //复制姓名      用于向索引表中添加姓名
			strcpy(item.fname,pStaff->GetFname());  //复制姓氏  用于向索引表中添加姓氏
			strcpy(item.sname,pStaff->GetSname());  //复制名  用于向索引表中添加名
			file.seekg(0,ios::end);                       //定位（从文件末尾处开始）
			item.position=file.tellg();                 //写入数据文件的位置 在索引表中做记录（返回当前文件定位指针的位置）
			AddIndexItem(item);                       //增加索引项
		}
		pStaff->Write(file);                            //向文件中写入人员信息
		delete pStaff;                                    //释放内存
	}
	else
	{
		cout<<"查无此人！"<<endl;
		file.clear();                              //清空所有保存的变量，同样会调用该变量的析构函数进行清理
	}
}
//查找数据SearchData()函数的实现  通过编号或姓名实现查询通过姓名查询时输入（复）姓时能实现模糊查询
void StaffManage::SearchData()
{
	Staff*pStaff;             //创建对象
	char num[20];          //编号
	char name[20];        //姓名
	int select;                //选择
	int pos=0;  
	cout<<"1：按人员编码查找；2:按姓名查找;"<<endl;
	cout<<"请输入选择！\t选择：";
	cin>>select;
	switch(select)
	{
	case 1:
		cout<<"请输入要查找的人员编码：";
		cin>>num;
		for(pos=0;pos<count;pos++)
		{    //遍历索引表查找满足条件的索引项
			if(strcmp(num,indexTable[pos].num)==0&&  //编号相同
				!indexTable[pos].delTag)                           //未被删除
			{	
				cout<<"查找成功！"<<endl;
				break;
			}
		}
		if(pos<count)
		{//查找成功
			file.seekg(indexTable[pos].position,ios::beg);                      //从头开始定位
			if(indexTable[pos].staffType=='s')pStaff=new Saleman;   //分配内存空间  实例化为不同对象
			else if(indexTable[pos].staffType=='m')pStaff=new Manager;
			else pStaff=new SaleManager;
			pStaff->Read(file);                                                        //读取员工信息
			pStaff->Show();                                                          //显示员工信息
			delete pStaff;                                                             //释放内存
		}
		else
		{
			cout<<"查无此人！"<<endl;
			file.clear();                                                          //清空所有保存的变量，同样会调用该变量的析构函数进行清理
		}
		break;
	case 2:
		cout<<"是否为复姓:(1.不是，2.是)";
		int  flag;     //声明变量  根据变量实现复姓与单个姓的选择来实现不同的方法
		cin>>flag;
		switch(flag)
		{
		case 1:
			cout<<"请输入要查找的姓(名):";
			cin>>name;        //输入姓名
			if(strlen(name)==2)
			{         //如果长度为2 即判断输入的是姓氏
				for( int pos=0;pos<count;pos++)
				{//遍历索引表查找符求的索引项  姓氏相同的输出来
					if(strcmp(name,indexTable[pos].fname)==0/*&&strcmp(sname,indexTable[pos].sname)==0*/&&!indexTable[pos].delTag) 
					{  //输入为(单)姓氏时 查找姓氏相同的
						if(pos<count)
						{                  //查找成功
							file.seekg(indexTable[pos].position,ios::beg);                      //从头开始定位
							if(indexTable[pos].staffType=='s')pStaff=new Saleman;   //分配内存空间  实例化为不同对象
							else if(indexTable[pos].staffType=='m')pStaff=new Manager;
							else pStaff=new SaleManager;
							pStaff->Read(file);                                                        //读取员工信息
							pStaff->Show();                                                          //显示员工信息
							delete pStaff;            //释放内存
						}
					} 
				}
			}
			else 
			{  //如果输入全名,实现精确查找
				for(int pos=0;pos<count;pos++)     //遍历索引项 
				{         
					if(strcmp(name,indexTable[pos].name)==0&&!indexTable[pos].delTag)
					{ //姓名相同,未被删除
						file.seekg(indexTable[pos].position,ios::beg);                    //从头开始定位
						if(indexTable[pos].staffType=='s')pStaff=new Saleman;   //分配内存空间  实例化为不同对象
						else if(indexTable[pos].staffType=='m')pStaff=new Manager;
						else pStaff=new SaleManager;
						pStaff->Read(file);                                                        //读取员工信息
						pStaff->Show();                                                          //显示员工信息
						delete pStaff;            //释放内存
					}
				}
			}

			break;	
		case 2:
			cout<<"请输入要查找的姓(名):";
			cin>>name;
			if(strlen(name)==4)//如果是复姓
			{
				for( int pos=0;pos<count;pos++) //遍引表查找符合要求的索引 
				{
					if(strcmp(name,indexTable[pos].fname)==0&&!indexTable[pos].delTag) 
					{  //遍历索引表查找符求的索引项  姓氏相同的输出来
						if(pos<count)
						{  //如果查找成功
							file.seekg(indexTable[pos].position,ios::beg);                      //从头开始定位
							if(indexTable[pos].staffType=='s')pStaff=new Saleman;   //分配内存空间  实例化为不同对象
							else if(indexTable[pos].staffType=='m')pStaff=new Manager;
							else pStaff=new SaleManager;
							pStaff->Read(file);                                                        //读取员工信息
							pStaff->Show();                                                          //显示员工信息
							delete pStaff;            //释放内存
						}
					} 

				}
			}
			else //如果输入全名,实现精确查找
			{
				for(int pos=0;pos<count;pos++)  //遍引表查找符合要求的索引 
				{   
					if(strcmp(name,indexTable[pos].name)==0&&!indexTable[pos].delTag)  //遍历索引表查找符求的索引项  姓氏相同的输出来
					{break;}
				}
				if (pos<count)
				{
					file.seekg(indexTable[pos].position,ios::beg);                      //从头开始定位
					if(indexTable[pos].staffType=='s')pStaff=new Saleman;   //分配内存空间  实例化为不同对象
					else if(indexTable[pos].staffType=='m')pStaff=new Manager;
					else pStaff=new SaleManager;
					pStaff->Read(file);                                                        //读取员工信息
					pStaff->Show();                                                          //显示员工信息
					delete pStaff;            //释放内存
				}
				else{cout<<"查无此人!"<<endl;}
			}
			break;	
		}	
	}
}
//统计函数的实现    实现查询总人数和查询各类员工类型的人数
void  StaffManage::Stat()
{
	char UserSays;
	do
	{
		cout<<"请选择1.查询总人数；2.查询各类员工类型型的的人数；"<<endl;
		cout<<"请输入你的选择:";
		int choice;
		cin>>choice;
		switch(choice)                                                  //用switch语句查询总人数 各类型员工的人数  
		{
		case 1:
			cout<<"是否查询总人数：";
			char UserSaysYes;
			cin>>UserSaysYes;
			UserSaysYes=tolower(UserSaysYes);           //转化为小写
			if(UserSaysYes=='y')                                  //判断是否输出总人数
				cout<<"总人数为："<<count<<endl;      // 输出总人数
			break;
		case 2:
			char UserSay;
			do
			{
				cout<<"请选择所要查询的人员类型的总数（s:销售人员，m：经理，b:销售经理）";
				char objStaff;       //声明变量
				cin>>objStaff;       
				if(objStaff=='s')          
				{
					cout<<"销售人员一共有："<<objScount<<"名!"<<endl;                             //输出销售人员人数
				}
				else if(objStaff=='m')cout<<"经理一共有："<<objMcount<<"名!"<<endl;       //输出经理人员人数
				else
					cout<<"销售经理一共有："<<objSmcount<<"名!"<<endl;                               //输出销售经理人数
				cout<<"请输入继续查询吗？(y/n)";
				cin>>UserSay;
			}
			while(UserSay=='y'||UserSay=='Y');          //判断是否继续查询
			break;
		default:
			cout<<"出现错误!"<<endl;
			break;
		}
		cout<<"是否继续查询统计人数:";
		cin>>UserSays;
	}while(UserSays=='Y'||UserSays=='y');

	file.clear();                                        //清空所有保存的变量，同样会调用该变量的析构函数进行清理
}

//删除数据的实现（只是对将要删除的员工信息做标记  并未被真实删除  在重组文件中实现物理上的删除）
void StaffManage::DeleteData()
{
	Staff*pStaff;                            //声明基类对象的指针
	IndexType item;                    //索引项
	item.delTag=false;              //删除标志
	char num[20];                    //编号
	cout<<"人员编码：";
	cin>>num;
	int pos;
	for (pos=0;pos<count;pos++)
	{                                                                        //  遍历索引表 查找满足条件的索引项
		if(strcmp(num,indexTable[pos].num)==0&&  //编号形同
			!indexTable[pos].delTag)                            //未被删除
			break;
	}
	if(pos<count)
	{ //查询成功
		file.seekg(indexTable[pos].position,ios::beg);            //定位
		if(indexTable[pos].staffType=='s')
		{
			pStaff=new Saleman;         //分配内存空间 实例化为不同对象
			objScount--;                     //计数  删除后自减
		}

		else if(indexTable[pos].staffType=='m') 
		{
			pStaff=new Manager;        //分配内存空间 实例化为不同对象
			objMcount--;                    //计数  删除后自减
		}
		else 
		{
			pStaff=new SaleManager;   //分配内存空间 实例化为不同对象
			objMcount--;                     //计数  删除后自减
		}
		pStaff->Read(file);                                                       //调用函数读取员工信息（即将要删除的）
		cout<<"被删除记录为："<<endl;
		pStaff->Show();                                                          //显示到屏幕上
		indexTable[pos].delTag=true;                                     //做上删除标志
		delete  pStaff;                                                           //释放内存空间
		cout<<"删除成功！"<<endl;
	}
	else{
		cout<<"删除失败！"<<endl;
		file.clear();                                                                //清空所有保存的变量，同样会调用该变量的析构函数进行清理
	}
}
//重组文件函数的实现(实际上的删除文件  创建一个新的文件用于将未
//做删除标记的员工信息写入 做了标记的被留在原来的文件中 
//最后将旧文件删除 并将新文件更名为就文件名   同时定义临时变量实现对索引项的处理 实现文件的删除)
void StaffManage::Pack()
{
	ofstream oFile("tem.dat");                                //以写模式临时创建文件用于向文件中写入未做标记的员工信息
	oFile.close();                                                     //关闭文件
	fstream outFile("tem.dat",ios::app|ios::binary); // 建立文件对象 追加到文件末尾 并以二进制形式打开
	Staff*pStaff;                                                  //基类指针对象的生命
	int cur_cout=0;                                          //临时变量 新索引项的个数
	for(int pos=0;pos<count;pos++)
	{//处理索引表中的每一项     将未做删除标记的员工信息写到新创建的文件中
		if(!indexTable[pos].delTag)
		{//未被删除
			file.seekg(indexTable[pos].position,ios::beg);                       //从头开始定位
			indexTable[pos].position=outFile.tellg();                          //新文件的写入位置(定位到当前文件读指针的位置)
			if(indexTable[pos].staffType=='s')pStaff=new Saleman;   //分配内存空间   实例化为不同对象
			else if(indexTable[pos].staffType=='m')pStaff=new Manager;
			else pStaff=new SaleManager;
			pStaff->Read(file);                                                //从旧文件中读取员工信息
			pStaff->Write(outFile);                                          //将读取的员工信息写到新文件中
			delete pStaff;                                                     //释放内存
			indexTable[cur_cout++]=indexTable[pos];           //索引项复制到新位置(重新计数索引项的个数写到索引表中)
		}
	}
	count=cur_cout;                                                       //新索引项的个数
	file.close();                                                              //关闭文件
	outFile.close();
	remove("staff.dat");                                               //删除旧文件
	rename("tem.dat","staff.dat");                               //将新文件重新命名为就我文件的名字
	file.open("staff.dat",ios::in|ios::out|ios::binary);       //重新打开文件(用于输入输出以二进制模式打开)
}
//计算工资函数的实现  通过输入人员姓名来实现并输出工资
void StaffManage::CacS()
{
	Staff*pStaff;                                       //创建基类的指针
	char name[20];                                  //姓名
	char num[20];                                    //编号
	char usersay;                                     //声明变量
	int pos;
	char type;
	do
	{
		cout<<"请输入选择(1.通过姓名，2.通过编号,3.输出各类员工工资，4.按年龄段输出工资):";
		int select;          //声明变量
		cin>>select;      //输入选择
		switch(select)
		{
		case 1:
			cout<<"请输入要计算的人的姓名:";	
			cin>>name;
			for( int pos=0;pos<count;pos++) 
			{//遍历索引表查找符合要求的索引项           
				if(strcmp(name,indexTable[pos].name)==0&&!indexTable[pos].delTag)//姓名相同未被删除
				{                                                   
					file.seekg(indexTable[pos].position,ios::beg);                                //定位
					if(indexTable[pos].staffType=='s')pStaff=new Saleman;                 //分配内存空间 实例化为不同对象
					else if(indexTable[pos].staffType=='m')pStaff=new Manager;
					else pStaff=new SaleManager;
					pStaff->Read(file);                                                                       //调用函数将文件中的东西读到内存中
					cout<<pStaff->GetNum()<<"\t工资:"<<pStaff->GetSalary()<<endl;                              //调用函数计算工资并输出来
					delete pStaff;                                                                               //释放内存
				}
				else continue;
			}
			break;
		case 2:
			cout<<"请输入要计算的人员编码：";
			cin>>num;
			for(int pos=0;pos<count;pos++)                                                       //遍历索引表查找满足条件的索引项
				if(strcmp(num,indexTable[pos].num)==0&&!indexTable[pos].delTag)    //编号相同未被删除
				{     
					if(pos<count)                                                                       //查找成功
					{
						file.seekg(indexTable[pos].position,ios::beg);                                 //定位
						if(indexTable[pos].staffType=='s')pStaff=new Saleman;                //分配内存空间 实例化为不同对象
						else if(indexTable[pos].staffType=='m')pStaff=new Manager;
						else pStaff=new SaleManager;
						pStaff->Read(file);                                                                        //调用函数将文件中的东西读到内存中
						cout<<pStaff->GetName()<<"\t工资:"<<pStaff->GetSalary()<<endl;                               //调用函数计算工资并输出来
						delete pStaff;  //释放内存
						break;
					}	
					else  cout<<"此人不存在！请检查是否输入正确！";

				}
				break;
		case 3:
			cout<<"请输入要计算的员工类型(s:销售人员，}m：经理，b:销售经理):";
			cin>>type;
			if(type=='s')         //输出Saleman类的员工的工资
			{
				for(int pos=0;pos<count;pos++)
				{
					file.seekg(indexTable[pos].position,ios::beg);                               //定位
					if(indexTable[pos].staffType=='s')  pStaff=new Saleman;          //分配内存空间 实例化为不同对
					else continue;                                                                        //如果没有此类对象 跳出此循环
					pStaff->Read(file);                                                                 //调用函数将文件中的东西读到内存中
					cout<<pStaff->GetName()<<setw(5)<<"\t工资:"<<pStaff->GetSalary()<<endl;        //将工资显示出来
					delete pStaff;
				}
			}
			else if(type=='m')     //输出Manager类的员工的工资
			{
				for(int pos=0;pos<count;pos++)
				{
					file.seekg(indexTable[pos].position,ios::beg);                            //定位
					if(indexTable[pos].staffType=='m')  pStaff=new Manager;      //分配内存空间 实例化为不同对象
					else continue;                                                                       //如果没有此类对象 跳出此循环
					pStaff->Read(file);                                                               //调用函数将文件中的东西读到内存中
					cout<<pStaff->GetName()<<setw(5)<<"\t工资:"<<pStaff->GetSalary()<<endl;        //将工资显示出来
					delete pStaff;                                                                 // 释放内存
				}
			}
			else 
			{
				for(int pos=0;pos<count;pos++)  //遍历索引表 
				{
					file.seekg(indexTable[pos].position,ios::beg);                            //定位
					if(indexTable[pos].staffType=='b')  pStaff=new SaleManager;  //分配内存空间 实例化为不同对象
					else continue;         //如果没有此类对象 跳出此循环
					pStaff->Read(file);                                                                 //调用函数将文件中的东西读到内存中
					cout<<pStaff->GetName()<<setw(5)<<"\t工资:"<<pStaff->GetSalary()<<endl;        //将工资显示出来
					delete pStaff;
				}
			}
			break;
		case 4:
			cout<<"输出你要计算的年龄段:";
			char firAge[20];char lasAge[20];         //声明变量
			cin>>firAge>>lasAge;                     //输入变量的值
			for(int pos=0;pos<count;pos++)          //遍历索引表 查找符合的项
			{ 
				if(atoi(firAge)<atoi(indexTable[pos].age)&&atoi(indexTable[pos].age)<=atoi(lasAge)&&!indexTable[pos].delTag)
				{        //用atoi()函数将char*转化为数字进行比较
					if(pos<count)                                                                  //如果查找成功
					{
						file.seekg(indexTable[pos].position,ios::beg);                      //从头开始定位
						if(indexTable[pos].staffType=='s')pStaff=new Saleman;   //分配内存空间  实例化为不同对象
						else if(indexTable[pos].staffType=='m')pStaff=new Manager;
						else pStaff=new SaleManager;
						pStaff->Read(file);                                                        //读取员工信息
						pStaff->Show();                                                          //显示员工信息
						delete pStaff;            //释放内存
					}
				}
			}
			break;
		}
		cout<<"是否继续计算工资：";
		cin>>usersay;
	}while(usersay=='y'||usersay=='Y');
}

//Run()函数的实现（将增删改查等函数进行统一处理  使用户使用的界面更整洁）
void  StaffManage::Run()
{
	int i;
	cout<<setw(60)<<"**********欢迎登录销售公司员工管理系统**********"<<endl;
	char depass[9]="yg123456";
	char password[20];
	for( i=0;i<3;i++)
	{
		cout<<"请输入登录密码:";
		cin>>password;
		if(strcmp(depass,password)==0)   //如果密码正确
		{  
			cout<<setw(60)<<"**********欢迎进入销售公司员工管理系统**********"<<endl;
			int select;
			i=4;
			do
			{
				cout<<setw(40)<<"请选择:"<<endl;
				cout<<setw(43)<<"1.增加数据"<<endl;
				cout<<setw(43)<<"2.更新数据"<<endl;
				cout<<setw(43)<<"3.查询数据"<<endl;	
				cout<<setw(43)<<"4.删除数据"<<endl;
				cout<<setw(43)<<"5.重组数据"<<endl;
				cout<<setw(43)<<"6.计算工资"<<endl;
				cout<<setw(43)<<"7.统计人数"<<endl;
				cout<<setw(39)<<"8.退出"<<endl;
				cout<<"请输入你的选择:";
				cin>>select;
				while(cin.get()!='\n');
				switch(select)
				{
				case 1:
					AddData();        //增加数据
					break;
				case 2:
					UpdateData();   //更新数据
					break;
				case 3:
					SearchData();    //查找数据
					break;
				case 4:
					DeleteData();    //删除数据
					break;
				case 5:
					Pack();             //重组文件
					break;
				case 6:
					CacS();            //计算工资
					break;
				case 7:
					Stat();            //统计人数
					break;
				}
			}while(select!=8);
		}
		else        //密码错误
		{
			cout<<"密码错误，请再次输入"<<endl;
		}
	}

	if(i==3)   
	{  //输入次数用完了
		cout<<"登陆失败!"<<endl;
	}
	else
	{
		cout<<"谢谢使用!"<<endl;
	}
}

