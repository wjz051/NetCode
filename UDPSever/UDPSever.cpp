#include<winsock2.h>							//����ͷ�ļ�
#include<stdio.h>
#include<windows.h>
#pragma comment(lib,"WS2_32.lib")				//�����׽��ֿ�

int main()
{
	/*1.��ʼ���׽��ֿ�*/
	WSADATA data;									//����ṹ�����
	WORD w = MAKEWORD(2, 0);							//�����׽��ְ汾
	::WSAStartup(w, &data);							//��ʼ���׽��ֿ�

	/*�����׽��־��*/
	SOCKET s;										//�����׽��־��
	s = ::socket(AF_INET, SOCK_DGRAM, 0);				//����UDP�׽���

	/*3.����λ����Ϣ*/
	sockaddr_in addr, addr1;							//�׽��ֵ�ַ�ṹ����
	addr.sin_family = AF_INET;
	addr.sin_port = htons(75);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	/*4.��*/
	::bind(s, (sockaddr*)&addr, sizeof(addr));		//���׽���
	printf("UDP�������Ѿ�����\r\n");				//��ʾ��ʾ��Ϣ

	char sztext[] = "��ӭ��\r\n";						//���延ӭ��Ϣ
	int n = sizeof(addr1);							//��ַ�ṹ������С
	char buff[10] = { 0 };								//�������ݻ�����
	while (1)
	{
		/*5.���տͻ�������*/
		if (::recvfrom(s, buff, 10, 0, (sockaddr*)&addr1, &n) != 0)		//���տͻ�����Ϣ��ѭ���ȴ��ź�
		{
			printf("%s�Ѿ�������\r\n", inet_ntoa(addr1.sin_addr));
			printf("%s\r\n", buff);
			/*6.��������*/
			::sendto(s, sztext, sizeof(sztext), 0, (sockaddr*)&addr1, n);//�������ݵ��ͻ���
			break;
		}
	}
	/*7.�ر��׽���*/
	::closesocket(s);							//�ر��׽��ֶ���
	::WSACleanup();								//�ͷ��׽��ֿ�
	if (getchar())							//��������룬��رճ���
	{
		return 0;									//������������
	}
	else
	{
		::Sleep(100);									//Ӧ�ó���˯��
	}
}
