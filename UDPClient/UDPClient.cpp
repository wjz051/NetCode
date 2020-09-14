#include<winsock2.h>					//包含头文件
#include<stdio.h>
#include<windows.h>
#pragma comment(lib,"WS2_32.lib")			//连接套接字库--测热额

int main()
{
	/*1.初始化套接字库*/
	WSADATA data;					//定义结构体变量
	WORD w = MAKEWORD(2, 0);				//初始化套接字版本号
	::WSAStartup(w, &data);				//初始化套接字库

	/*2.创建套接字句柄*/
	SOCKET s;					//定义套接字
	s = ::socket(AF_INET, SOCK_DGRAM, 0);		//创建UDP套接字

	/*3.设置位置数据*/
	sockaddr_in addr, addr1;				//定义套接字地址
	addr.sin_family = AF_INET;
	addr.sin_port = htons(75);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	printf("UDP客户端已经启动\r\n");

	char sztext[] = "你好\r\n";
	int n = sizeof(addr1);
	char buff[10] = { 0 };
	/*4.发送数据给服务器*/
	if (::sendto(s, sztext, sizeof(sztext), 0, (sockaddr*)&addr, n) != 0)	//发送信息
	{
		/*5.接收服务器数据*/
		::recvfrom(s, buff, 10, 0, (sockaddr*)&addr1, &n);		//接收信息
		printf("服务器说：%s\r\n", buff);

		/*6.关闭套接字*/
		::closesocket(s);					//关闭套接字
		::WSACleanup();						//释放套接字库
	}
	if (getchar())							//如果有输入，则关闭程序
	{
		return 0;						//正常结束程序
	}
	else
	{
		::Sleep(100);						//应用程序睡眠
	}
}
