#include<winsock2.h>							//包含头文件
#include<stdio.h>
#include<windows.h>
#pragma comment(lib,"WS2_32.lib")				//连接套接字库

int main()
{
	/*1.初始化套接字库*/
	WSADATA data;									//定义结构体变量
	WORD w = MAKEWORD(2, 0);							//定义套接字版本
	::WSAStartup(w, &data);							//初始化套接字库

	/*创建套接字句柄*/
	SOCKET s;										//定义套接字句柄
	s = ::socket(AF_INET, SOCK_DGRAM, 0);				//创建UDP套接字

	/*3.设置位置信息*/
	sockaddr_in addr, addr1;							//套接字地址结构变量
	addr.sin_family = AF_INET;
	addr.sin_port = htons(75);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	/*4.绑定*/
	::bind(s, (sockaddr*)&addr, sizeof(addr));		//绑定套接字
	printf("UDP服务器已经启动\r\n");				//显示提示信息

	char sztext[] = "欢迎你\r\n";						//定义欢迎信息
	int n = sizeof(addr1);							//地址结构变量大小
	char buff[10] = { 0 };								//接收数据缓冲区
	while (1)
	{
		/*5.接收客户端数据*/
		if (::recvfrom(s, buff, 10, 0, (sockaddr*)&addr1, &n) != 0)		//接收客户端信息，循环等待信号
		{
			printf("%s已经连接上\r\n", inet_ntoa(addr1.sin_addr));
			printf("%s\r\n", buff);
			/*6.发送数据*/
			::sendto(s, sztext, sizeof(sztext), 0, (sockaddr*)&addr1, n);//发送数据到客户端
			break;
		}
	}
	/*7.关闭套接字*/
	::closesocket(s);							//关闭套接字对象
	::WSACleanup();								//释放套接字库
	if (getchar())							//如果有输入，则关闭程序
	{
		return 0;									//正常结束程序
	}
	else
	{
		::Sleep(100);									//应用程序睡眠
	}
}
