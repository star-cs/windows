#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

int main()
{
	std::cout << "Client start" << std::endl;
	//Winsock的初始化
	// 定义请求的Winsock版本，这里是Winsock 2.2
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2); // 设置请求的版本号为2.2

	// 调用WSAStartup函数初始化Winsock环境
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		// 如果WSAStartup返回错误，打印错误信息并立即返回-1，终止程序执行
		printf("WSAStartup errorNum = %d\n", GetLastError());
		return -1;
	}

	// 检查实际加载的Winsock版本是否与请求的版本匹配
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		// 如果版本不匹配，打印错误信息，清理Winsock资源并返回-1
		printf("LOBYTE errorNum = %d\n", GetLastError());
		WSACleanup(); // 清理Winsock资源
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