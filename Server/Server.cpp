#include "stdafx.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <tchar.h>
#include <thread>
#include <vector> 
#include <mutex> 
#define BUFFER_SIZE 128

using namespace std;
mutex mtx;

void envia_jogada_jogador1(const vector<int> &a, int * jogada) {


	char buffer[5];
	char aux[5];
	mtx.lock();

	//Recebe dados do jogador 1
	recv(a[0], (char*)buffer, sizeof(buffer), 0);
	for (int i = 0; i < 4; i++) {
		aux[i] = buffer[i];

	}

	//Envida dados do jogadpr 1 -> 2
	send(a[1], (char*)aux, sizeof(aux), 0);


	//Envida o acerto ou erro para o jogador 1.
	memset(&aux, 0, 5);
	memset(&buffer, 0, 5);
	
	recv(a[1], (char*)buffer, sizeof(buffer), 0);
	for (int i = 0; i < 4; i++) {
		aux[i] = buffer[i];

	}
	send(a[0], (char*)aux, sizeof(aux), 0);
	mtx.unlock();
}

void envia_jogada_jogador2(const vector<int>&a, int * jogada2) {

	char buffer[5];
	char aux[5];
	mtx.lock();


	//Recebe a jogada do jogador 2
	recv(a[1], (char*)buffer, sizeof(buffer), 0);


	for (int i = 0; i < 5; i++) {
		aux[i] = buffer[i];

	}
	//envia jogada para o jogador 1
	send(a[0], (char*)aux, sizeof(aux), 0);

	
	//Envida o acerto ou erro para o jogador 2.
	memset(&aux, 0, 5);
	memset(&buffer, 0, 5);

	recv(a[0], (char*)buffer, sizeof(buffer), 0);
	for (int i = 0; i < 5; i++) {
		aux[i] = buffer[i];

	}
	send(a[1], (char*)aux, sizeof(aux), 0);



	mtx.unlock();


}

int main()
{
	char jogada1[4];
	int jogada = 1;
	int jogada2 = 1;
	vector<int> conet;

	int byteCount;
	cout << "====== W11 Sockets ======\n";
	cout << "======== SERVER =========\n";
	cout << "\n=== Step 1 - Set up DLL ===\n";
	SOCKET serverSocket, acceptSocket;
	int port = 55555;
	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0)
	{
		cout << "The winsock dll not found!\n";
		exit(1);
	}
	cout << "\n=== Step 2 - Set up Server Socket ===\n";

	serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET)
	{
		cout << "Error at socket():" << WSAGetLastError() << '\n';
		WSACleanup();
		return 0;
	}
	else
	{
		cout << "Socket() is OK!\n";
	}

	cout << "\n=== Step 3 - Bind Socket ===\n";

	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(port);
	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
	{
		cout << "bind()failed: " << WSAGetLastError() << '\n';
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}
	else
	{
		cout << "bind() is OK!\n";
	}

	cout << "\n=== Step 4 - Initiate Listen ===\n";


	if (listen(serverSocket, 2) == SOCKET_ERROR)
	{
		cout << "listen(): Error listening on socket" << WSAGetLastError() << '\n';
	}
	else
	{
		cout << "listen() is OK, i'm waiting for connections...\n";
	}

	cout << "\n=== Step 5 - Accept Connection from Client ===\n";
	int i = 0;
	 while (conet.size() != 2) {
		acceptSocket = accept(serverSocket, NULL, NULL);
		if (acceptSocket == INVALID_SOCKET)
		{
			cout << "accept failed:" << WSAGetLastError() << '\n';
			WSACleanup();
			return -1;
		}
		conet.push_back(acceptSocket);
		cout << acceptSocket << endl;
		cout << "Accept connection\n";
	}


	 do {

		 thread th1(envia_jogada_jogador1, conet, &jogada);
		 thread th2(envia_jogada_jogador2, conet, &jogada2);


		 th1.join();
		 th2.join();


	


	 } while (1);

	 WSACleanup();
	 return 0;

}

