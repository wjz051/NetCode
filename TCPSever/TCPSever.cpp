#include<winsock2.h>						//����ͷ�ļ�
#include<stdio.h>
#include<windows.h>
#pragma comment(lib,"WS2_32.lib")			//��ʽ�����׽��ֿ�

int main()									//��������ʼ
{
	/*1.��ʼ���׽��ֿ�*/
	WSADATA data;							//����WSADATA�ṹ�����
	WORD w = MAKEWORD(2, 0);					//����汾����
	::WSAStartup(w, &data);					//��ʼ���׽��ֿ�

	/*2.�����׽��־��*/
	SOCKET s, s1;							//���������׽��ֺ������շ��׽��־��
	s = ::socket(AF_INET, SOCK_STREAM, 0);		//����TCP�׽���

	/*3.���õ�ַ��Ϣ*/
	sockaddr_in addr, addr1;					//�����׽��ֵ�ַ�ṹ
	int n = sizeof(addr);					//��ȡ�׽��ֵ�ַ�ṹ��С
	addr.sin_family = AF_INET;				//��ʼ����ַ�ṹ
	addr.sin_port = htons(75);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	/*4.��*/
	::bind(s, (sockaddr*)&addr, sizeof(addr));	//���׽���

	/*5.����*/
	::listen(s, 5);								//�����׽���
	printf("�������Ѿ�����\r\n");				//�����ʾ��Ϣ

	char sztext[] = "��ӭ��\r\n";				//���岢��ʼ�����͵��ͻ��˵��ַ�����
	while (true)
	{
		/*6.��������*/
		s1 = ::accept(s, (sockaddr*)&addr1, &n);	//������������--����ֱ���пͻ�������
		if (s1 != NULL)
		{
			printf("%s�Ѿ�������\r\n", inet_ntoa(addr1.sin_addr));
			/*7.���ݷ���*/
			::send(s1, sztext, sizeof(sztext), 0);	//��ͻ��˷����ַ�����--����ֱ�����ݷ������
		}
		/*8.�ر��׽���*/
		::closesocket(s);						//�ر��׽��־��
		::closesocket(s1);
		::WSACleanup();							//�ͷ��׽��ֿ�
		if (getchar())							//��������룬��رճ���
		{
			return 0;							//������������
		}
		else
		{
			::Sleep(100);						//Ӧ��˯��0.1��
		}
	}
}
