#include<winsock2.h>				//包含头文件
#include<stdio.h>
#include<windows.h>
#pragma comment(lib,"WS2_32.lib")		//显式连接套接字库

int main()							//主函数开始
{
	/*1.初始化套接字库*/
	WSADATA data;						//定义WSADATA结构体对象
	WORD w = MAKEWORD(2, 0);					//定义版本号码
	::WSAStartup(w, &data);					//初始化套接字库

	/*2.创建套接字句柄*/
	SOCKET s;						//定义连接套接字句柄
	char sztext[10] = { 0 };
	s = ::socket(AF_INET, SOCK_STREAM, 0);			//创建TCP套接字

	/*3.设置地址信息*/
	sockaddr_in addr;					//定义套接字地址结构
	addr.sin_family = AF_INET;				//初始化地址结构
	addr.sin_port = htons(75);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	printf("客户端已经启动\r\n");				//输出提示信息

	/*4.连接*/
	::connect(s, (sockaddr*)&addr, sizeof(addr));

	/*5.数据接收*/
	::recv(s, sztext, sizeof(sztext), 0);//阻塞直到有数据可读
	printf("%s\r\n", sztext);

	/*6.关闭套接字*/
	::closesocket(s);					//关闭套接字句柄
	::WSACleanup();						//释放套接字库
	if (getchar())						//如果有输入，则关闭程序
	{
		return 0;					//正常结束程序
	}
	else
	{
		::Sleep(100);					//程序睡眠
	}
}
