#pragma  once     //防止头文件重复包含
class IndexType   //索引类
{
public:
	bool delTag;  // 删除标志
	char num[20]; // 编号
	int position; // 在数据文件中的相对位置 不同对象数据在二进制文件中的相对存储位置
	char staffType;//文件操作时要确定写入的大小 用人员类型便于分配空间，s:销售员,m:经理,b:销售经理
	char name[20];// 姓名,便于在索引文件中做记录 用于实现查找
	char fname[20];// 姓,便于在索引文件中做记录 用于实现查找
	char sname[10];//名,便于在索引文件中做记录 用于实现查找
	char age[20]; //年龄,便于在索引文件中做记录 用于实现查找
};