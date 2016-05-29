// UDPClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>
#include <WINSOCK2.H>
#define BUF_SIZE 1024

int main(int argc, char* argv[])
{
	WSADATA wsd;
	SOCKET sClient;
	int iRetVal;
	char buf[BUF_SIZE];

	if (WSAStartup(MAKEWORD(1,1),&wsd)!=0)
	{
		cout<<"��ʼ���׽��ֶ�̬��ʧ��"<<endl;
		return -1;
	}

	if (LOBYTE(wsd.wVersion)!=1||HIBYTE(wsd.wVersion)!=1)
	{
		WSACleanup();
		return -1;
	}

	sClient=socket(AF_INET,SOCK_DGRAM,0);
	if (INVALID_SOCKET==sClient)
	{
		cout<<"�����׽���ʧ��"<<endl;
		WSACleanup();
		return -1;
	}
	SOCKADDR_IN addrServ;
	addrServ.sin_family=AF_INET;
	addrServ.sin_port=htons(8899);
	addrServ.sin_addr.S_un.S_addr=inet_addr("192.168.1.114");
	//����������������
	char *str = "This is Client";
	iRetVal=sendto(sClient,str,strlen(str),0,(SOCKADDR *)&addrServ,sizeof(SOCKADDR));
	if (SOCKET_ERROR==iRetVal)
	{
		cout<<"��������ʧ��"<<endl;
		closesocket(sClient);
		WSACleanup();
		return -1;
	}
	//���շ�������Ӧ������
	int len = sizeof(SOCKADDR);
	ZeroMemory(buf,BUF_SIZE);
	iRetVal=recvfrom(sClient,buf,BUF_SIZE,0,(SOCKADDR *)&addrServ,&len);
	if (SOCKET_ERROR==iRetVal)
	{
		cout<<"��������ʧ��"<<endl;
		closesocket(sClient);
		WSACleanup();
		return -1;
	}
	cout<<buf<<endl;
	closesocket(sClient);
	WSACleanup();
	return 0;
}
