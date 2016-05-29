// UDPServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>
#include <stdio.h>
#include <WINSOCK2.H>
#define BUF_SIZE 1024

int main(int argc, char* argv[])
{
	WSADATA wsd;		//WSADATA变量，存有套接字库得版本信息
	SOCKET sServer;		//服务器套接字
	int iRetVal;
	char buf[BUF_SIZE];
	if (WSAStartup(MAKEWORD(1,1),&wsd)!=0)
	{
		cout<<"初始化套接字动态库失败"<<endl;
		return -1;
	}
	//判断版本是都加载正确，如果不是1.1版本则返回
	if (LOBYTE(wsd.wVersion)!=1||HIBYTE(wsd.wVersion)!=1)
	{
		WSACleanup();
		return -1;
	}
	sServer=socket(AF_INET,SOCK_DGRAM,0);
	if (INVALID_SOCKET==sServer)
	{
		cout<<"创建套接字失败"<<endl;
		WSACleanup();
		return -1;
	}
	//服务器套接字地址
	SOCKADDR_IN addServ;
	addServ.sin_family=AF_INET;
	addServ.sin_port=htons(8899);
	addServ.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	//绑定套接字
	iRetVal=bind(sServer,(SOCKADDR *)&addServ,sizeof(SOCKADDR));
	if (SOCKET_ERROR==iRetVal)
	{
		cout<<"绑定失败"<<endl;
		closesocket(sServer);
		WSACleanup();
		return -1;
	}
	cout<<"服务器已经启动，准备接收"<<endl;
	SOCKADDR_IN addrClient;
	int len = sizeof(addrClient);
	while (1)
	{
		ZeroMemory(buf,BUF_SIZE);		//清空接收数据缓冲区
		//接收数据，注意用的是recvFrom()函数！
		iRetVal=recvfrom(sServer,buf,BUF_SIZE,0,(SOCKADDR *)&addrClient,&len);
			if (SOCKET_ERROR==iRetVal)
			{
				cout<<"接收数据失败"<<endl;
				closesocket(sServer);
				WSACleanup();
				return -1;
			}
			cout<<buf<<endl;
			char sendBuf[1024];
			sprintf(sendBuf,"Welcome %s to Server",inet_ntoa(addrClient.sin_addr));
			//发送数据，注意用的是sendto()函数
			sendto(sServer,sendBuf,1024,0,(SOCKADDR *)&addrClient,len);
	}
	closesocket(sServer);
	WSACleanup();
	return 0;
}
