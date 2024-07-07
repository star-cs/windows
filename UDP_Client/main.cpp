#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

int main()
{
	std::cout << "Client start" << std::endl;
	//Winsock�ĳ�ʼ��
	// ���������Winsock�汾��������Winsock 2.2
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2); // ��������İ汾��Ϊ2.2

	// ����WSAStartup������ʼ��Winsock����
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		// ���WSAStartup���ش��󣬴�ӡ������Ϣ����������-1����ֹ����ִ��
		printf("WSAStartup errorNum = %d\n", GetLastError());
		return -1;
	}

	// ���ʵ�ʼ��ص�Winsock�汾�Ƿ�������İ汾ƥ��
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		// ����汾��ƥ�䣬��ӡ������Ϣ������Winsock��Դ������-1
		printf("LOBYTE errorNum = %d\n", GetLastError());
		WSACleanup(); // ����Winsock��Դ
		return -1;
	}

	int sockCli = socket(AF_INET, SOCK_DGRAM, 0);
	if (INVALID_SOCKET == sockCli)
	{
		printf("socket errorNo = %d\n", GetLastError());
		return -1;
	}
	
	SOCKADDR_IN addrServ;
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(9527);
	addrServ.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	int iLen = sizeof(SOCKADDR);

	char sendBuf[1024] = "hello,I am Client";
	char recvBuf[1024] = { 0 };

	sendto(sockCli, sendBuf, strlen(sendBuf) + 1, 0, (SOCKADDR*)&addrServ, iLen);
	
	recvfrom(sockCli, recvBuf, sizeof(recvBuf), 0, (SOCKADDR*)&addrServ, &iLen);

	std::cout << recvBuf << std::endl;
	closesocket(sockCli);
	WSACleanup();
	system("pause");
	return 0;


	system("pause");
	return 0;
}