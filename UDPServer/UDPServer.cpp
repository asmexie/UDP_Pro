// UDPServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>
#include <stdio.h>
#include <WINSOCK2.H>
#define BUF_SIZE 1024

int main(int argc, char* argv[])
{
	WSADATA wsd;		//WSADATA�����������׽��ֿ�ð汾��Ϣ
	SOCKET sServer;		//�������׽���
	int iRetVal;
	char buf[BUF_SIZE];
	if (WSAStartup(MAKEWORD(1,1),&wsd)!=0)
	{
		cout<<"��ʼ���׽��ֶ�̬��ʧ��"<<endl;
		return -1;
	}
	//�жϰ汾�Ƕ�������ȷ���������1.1�汾�򷵻�
	if (LOBYTE(wsd.wVersion)!=1||HIBYTE(wsd.wVersion)!=1)
	{
		WSACleanup();
		return -1;
	}
	sServer=socket(AF_INET,SOCK_DGRAM,0);
	if (INVALID_SOCKET==sServer)
	{
		cout<<"�����׽���ʧ��"<<endl;
		WSACleanup();
		return -1;
	}
	//�������׽��ֵ�ַ
	SOCKADDR_IN addServ;
	addServ.sin_family=AF_INET;
	addServ.sin_port=htons(8899);
	addServ.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	//���׽���
	iRetVal=bind(sServer,(SOCKADDR *)&addServ,sizeof(SOCKADDR));
	if (SOCKET_ERROR==iRetVal)
	{
		cout<<"��ʧ��"<<endl;
		closesocket(sServer);
		WSACleanup();
		return -1;
	}
	cout<<"�������Ѿ�������׼������"<<endl;
	SOCKADDR_IN addrClient;
	int len = sizeof(addrClient);
	while (1)
	{
		ZeroMemory(buf,BUF_SIZE);		//��ս������ݻ�����
		//�������ݣ�ע���õ���recvFrom()������
		iRetVal=recvfrom(sServer,buf,BUF_SIZE,0,(SOCKADDR *)&addrClient,&len);
			if (SOCKET_ERROR==iRetVal)
			{
				cout<<"��������ʧ��"<<endl;
				closesocket(sServer);
				WSACleanup();
				return -1;
			}
			cout<<buf<<endl;
			char sendBuf[1024];
			sprintf(sendBuf,"Welcome %s to Server",inet_ntoa(addrClient.sin_addr));
			//�������ݣ�ע���õ���sendto()����
			sendto(sServer,sendBuf,1024,0,(SOCKADDR *)&addrClient,len);
	}
	closesocket(sServer);
	WSACleanup();
	return 0;
}
