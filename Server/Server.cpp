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

void preenche_jogador(char tabuleiro_jogador1[10][10], char buffer[42]) {

	int l = 0;
	for (int i = 0; i < 21; i++) {

		tabuleiro_jogador1[(int)buffer[l]][(int)buffer[l + 1]] = 'O';
		l = l + 2;

	}

}

void recebedadosjogador(char tabuleiro_jogador1[10][10], char tabuleiro_jogador2[10][10], const vector<int> &a) {

	char buffer[42];
	recv(a[0], (char*)buffer, sizeof(buffer), 0);
	preenche_jogador(tabuleiro_jogador1, buffer);
	memset(&buffer, 0, 42);
	recv(a[1], (char*)buffer, sizeof(buffer), 0);
	preenche_jogador(tabuleiro_jogador2, buffer);
}

void envia_jogada_jogador(const vector<int>& a, char tabuleiro_jogador1[10][10], char tabuleiro_jogador2[10][10]) {

	char buffer[5];
	char aux1[5];
	char aux2[5];
	mtx.lock();

	//Recebe dados do jogador 1
	recv(a[0], (char*)buffer, sizeof(buffer), 0);
	for (int i = 0; i <= 4; i++) {
		aux1[i] = buffer[i];

	}
	memset(&buffer, 0, 5);

	//Recebe dados do jogador 2
	recv(a[1], (char*)buffer, sizeof(buffer), 0);
	for (int i = 0; i <= 4; i++) {
		aux2[i] = buffer[i];

	}


	//Verifica Jogada

	if (tabuleiro_jogador2[(int)aux1[1]][(int)aux1[2]] == 'O' ) {
		int aux_vida = (int)aux2[0] - 1;
		tabuleiro_jogador2[(int)aux1[1]][(int)aux1[2]] = 'X';
		aux1[3] = 'A';
		aux1[4] = aux_vida;
		aux2[0] = aux_vida;
	}
	else {
		aux1[3] = 'E';
		aux1[4] = (int)aux2[0];
		aux2[0] = (int)aux2[0];
	}


	if (tabuleiro_jogador1[(int)aux2[1]][(int)aux2[2]] == 'O') {
		int aux_vida = (int)aux1[0] - 1;
		tabuleiro_jogador1[(int)aux1[1]][(int)aux1[2]] = 'X';
		aux2[3] = 'A';
		aux2[4] = aux_vida;
		aux1[0] = aux_vida;
	}
	else {
		aux2[3] = 'E';
		aux2[4] = (int)aux1[0];
		aux1[0] = (int)aux1[0];

	}

	send(a[0], (char*)aux1, sizeof(aux1), 0);
	send(a[1], (char*)aux2, sizeof(aux2), 0);

	memset(&buffer, 0, 5);
	memset(&aux1, 0, 5);
	memset(&aux2, 0, 5);
	mtx.unlock();


}

int main()
{
	char jogada1[4];
	int jogada = 1;
	int jogada2 = 1;
	vector<int> conet;
	char tabuleiro_jogador1[10][10] = {
		{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
		{'-', '-', '-','-', '-' , '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-','-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'}

	};
	char tabuleiro_jogador2[10][10] = {
		{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
		{'-', '-', '-','-', '-' , '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-','-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'}

	};

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

	 recebedadosjogador(tabuleiro_jogador1, tabuleiro_jogador2, conet);

	 do {
		 thread th1(envia_jogada_jogador, conet, tabuleiro_jogador1, tabuleiro_jogador2);
	
		 th1.join();
	

	 } while (1);

	 WSACleanup();
	 return 0;

}

