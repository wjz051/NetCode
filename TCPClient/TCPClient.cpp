#include<winsock2.h>				//����ͷ�ļ�
#include<stdio.h>
#include<windows.h>
#pragma comment(lib,"WS2_32.lib")		//��ʽ�����׽��ֿ�

int main()							//��������ʼ
{
	/*1.��ʼ���׽��ֿ�*/
	WSADATA data;						//����WSADATA�ṹ�����
	WORD w = MAKEWORD(2, 0);					//����汾����
	::WSAStartup(w, &data);					//��ʼ���׽��ֿ�

	/*2.�����׽��־��*/
	SOCKET s;						//���������׽��־��
	char sztext[10] = { 0 };
	s = ::socket(AF_INET, SOCK_STREAM, 0);			//����TCP�׽���

	/*3.���õ�ַ��Ϣ*/
	sockaddr_in addr;					//�����׽��ֵ�ַ�ṹ
	addr.sin_family = AF_INET;				//��ʼ����ַ�ṹ
	addr.sin_port = htons(75);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	printf("�ͻ����Ѿ�����\r\n");				//�����ʾ��Ϣ

	/*4.����*/
	::connect(s, (sockaddr*)&addr, sizeof(addr));

	/*5.���ݽ���*/
	::recv(s, sztext, sizeof(sztext), 0);//����ֱ�������ݿɶ�
	printf("%s\r\n", sztext);

	/*6.�ر��׽���*/
	::closesocket(s);					//�ر��׽��־��
	::WSACleanup();						//�ͷ��׽��ֿ�
	if (getchar())						//��������룬��رճ���
	{
		return 0;					//������������
	}
	else
	{
		::Sleep(100);					//����˯��
	}
}
