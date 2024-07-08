#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <ws2tcpip.h> // ����inet_ntop����

#pragma comment(lib, "ws2_32.lib")	//���� ws2_32.lib��

int main()
{
	printf("TCP server\n");

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

	SOCKET sockServ = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == sockServ)
	{
		printf("socker errorno = %d\n", GetLastError());	//10093
		return -1;
	}

	SOCKADDR_IN addrServ;
	addrServ.sin_family = AF_INET;
	addrServ.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrServ.sin_port = htons(9527);

	if (SOCKET_ERROR == bind(sockServ, (SOCKADDR*)&addrServ, sizeof(SOCKADDR)))
	{
		printf("bind errorno = %d\n", GetLastError());
		return -1;
	}

	if (SOCKET_ERROR == listen(sockServ, 4))
	{
		printf("listen errorno = %d\n", GetLastError());
		return -1;
	}

	SOCKADDR_IN addrCli;
	int len = sizeof(SOCKADDR);
	while (1)
	{
		SOCKET sockConn = accept(sockServ, (SOCKADDR*)&addrCli, &len);
		char sendBuf[1024] = { 0 };

		char ipString[INET_ADDRSTRLEN];
		const char* ip = nullptr;
		inet_ntop(AF_INET, &addrCli, ipString, sizeof(ipString));
		sprintf_s(sendBuf, 100, "Welcome %s to China!" , ipString);

		int iLen = send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);

		char recvBuf[1024] = { 0 };
		iLen = recv(sockConn, recvBuf, sizeof(recvBuf), 0);
		
		printf("recv��%s\n", sendBuf);
		closesocket(sockConn);
	}


	closesocket(sockServ);
	WSACleanup();

	system("pause");
	return 0;
}

int MySocketRecv0(int sock, char* buf, int dataSize)
{
	int numsRecvSoFar = 0;
	int numsRecvTarget = dataSize;
	while (1)
	{
		int bytesRead = recv(sock, &buf[numsRecvSoFar], numsRecvTarget, 0);

		if (bytesRead == numsRecvTarget)
		{
			return 0;
		}
		else if (bytesRead > 0)
		{
			numsRecvSoFar += bytesRead;
			numsRecvTarget -= bytesRead;
			continue;
		}
		else if ((bytesRead < 0) && (errno == EAGAIN))
		{
			continue;
		}
		else
		{
			perror("recv");
			return -1;
		}
	}
}