#include<winsock2.h>					//����ͷ�ļ�
#include<stdio.h>
#include<windows.h>
#pragma comment(lib,"WS2_32.lib")			//�����׽��ֿ�--����

int main()
{
	/*1.��ʼ���׽��ֿ�*/
	WSADATA data;					//����ṹ�����
	WORD w = MAKEWORD(2, 0);				//��ʼ���׽��ְ汾��
	::WSAStartup(w, &data);				//��ʼ���׽��ֿ�

	/*2.�����׽��־��*/
	SOCKET s;					//�����׽���
	s = ::socket(AF_INET, SOCK_DGRAM, 0);		//����UDP�׽���

	/*3.����λ������*/
	sockaddr_in addr, addr1;				//�����׽��ֵ�ַ
	addr.sin_family = AF_INET;
	addr.sin_port = htons(75);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	printf("UDP�ͻ����Ѿ�����\r\n");

	char sztext[] = "���\r\n";
	int n = sizeof(addr1);
	char buff[10] = { 0 };
	/*4.�������ݸ�������*/
	if (::sendto(s, sztext, sizeof(sztext), 0, (sockaddr*)&addr, n) != 0)	//������Ϣ
	{
		/*5.���շ���������*/
		::recvfrom(s, buff, 10, 0, (sockaddr*)&addr1, &n);		//������Ϣ
		printf("������˵��%s\r\n", buff);

		/*6.�ر��׽���*/
		::closesocket(s);					//�ر��׽���
		::WSACleanup();						//�ͷ��׽��ֿ�
	}
	if (getchar())							//��������룬��رճ���
	{
		return 0;						//������������
	}
	else
	{
		::Sleep(100);						//Ӧ�ó���˯��
	}
}
