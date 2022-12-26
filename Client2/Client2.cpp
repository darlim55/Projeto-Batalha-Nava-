#include "stdafx.h"
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <iostream>
#include <tchar.h>
#include <mutex>
#define BUFFER_SIZE 128


using namespace std;
mutex mtx;

void verifica_linha_coluna(int* linha, int* coluna) {

	int linhaaux, colunaaux;

	if ((*linha < 1 || *linha > 10) || (*coluna < 1 || *coluna > 10)) {

		while (1) {

			cout << "Digite uma linha e coluna validos (NUMEROS ENTRE 1-10)";
			cout << "Linha: " << endl;
			cin >> linhaaux;
			cout << "Coluna: " << endl;
			cin >> colunaaux;
			if ((linhaaux >= 1 && linhaaux <= 10) && (colunaaux >= 1 && colunaaux <= 10)) {
				*linha = linhaaux;
				*coluna = colunaaux;
				break;
			}
		}

	}

}

bool verifica_quadrados(char tabuleiro_jogador[10][10], int dado, int linha, int coluna) {

	if (dado >= 0 && dado < 3) {

		if (tabuleiro_jogador[linha][coluna] == '-' && tabuleiro_jogador[linha][coluna + 1] == '-' && coluna <= 8) {
			tabuleiro_jogador[linha][coluna] = 'S';
			tabuleiro_jogador[linha][coluna + 1] = 'S';
			return true;


		}
		else
			return false;


	}
	else if (dado >= 3 && dado <= 4) {


		if (tabuleiro_jogador[linha][coluna] == '-' && tabuleiro_jogador[linha][coluna + 1] == '-' && tabuleiro_jogador[linha][coluna + 2] == '-' && coluna <= 7) {
			tabuleiro_jogador[linha][coluna] = 'P';
			tabuleiro_jogador[linha][coluna + 1] = 'P';
			tabuleiro_jogador[linha][coluna + 2] = 'P';
			return true;


		}
		else
			return false;


	}
	else if (dado == 5) {


		if (tabuleiro_jogador[linha][coluna] == '-' && tabuleiro_jogador[linha][coluna + 1] == '-' &&
			tabuleiro_jogador[linha][coluna + 2] == '-' && tabuleiro_jogador[linha][coluna + 3] == '-' && coluna <= 6) {
			tabuleiro_jogador[linha][coluna] = 'N';
			tabuleiro_jogador[linha][coluna + 1] = 'N';
			tabuleiro_jogador[linha][coluna + 2] = 'N';
			tabuleiro_jogador[linha][coluna + 3] = 'N';
			return true;


		}
		else
			return false;


	}
	else {
		if (tabuleiro_jogador[linha][coluna] == '-' && tabuleiro_jogador[linha][coluna + 1] == '-' &&
			tabuleiro_jogador[linha][coluna + 2] == '-' && tabuleiro_jogador[linha][coluna + 3] == '-' && tabuleiro_jogador[linha][coluna + 4] && coluna <= 5) {
			tabuleiro_jogador[linha][coluna] = 'P';
			tabuleiro_jogador[linha][coluna + 1] = 'P';
			tabuleiro_jogador[linha][coluna + 2] = 'P';
			tabuleiro_jogador[linha][coluna + 3] = 'P';
			tabuleiro_jogador[linha][coluna + 4] = 'P';
			return true;


		}
		else
			return false;




	}
}

void posicina_elementos(char tabuleiro_jogador[10][10], int dado) {
	int linha, coluna;
	char p;
	cout << "Digite Linha" << endl;
	cin >> linha;
	cout << "Digite Coluna " << endl;
	cin >> coluna;
	cout << endl;
	while (1) {

		if (linha >= 1 && linha <= 10 && coluna >= 1 && coluna <= 10) {
			if (tabuleiro_jogador[linha][coluna] == '-') {
				if (verifica_quadrados(tabuleiro_jogador, dado, linha - 1, coluna - 1))
					break;


			}

		}
		cout << "Digte uma linha ou coluna validos (POSICAO OCUPADA OU FORA DO TAMANHO DO TABULEIRO" << endl;
		cout << "Digite Linha" << endl;
		cin >> linha;
		cout << "Digite Coluna " << endl;
		cin >> coluna;
		cout << endl;
	}

}

void introducao(char tabuleiro_jogador[10][10])
{
	cout << "Bem-vindo ao Batalha Naval " << endl;
	cout << "Voce e um almirante que tem a missao de derrubar as embarcacoes inimigas " << endl;
	cout << "Posicone os elementos na seguinte ordem: " << endl;
	cout << "3x Submarino = S" << endl;
	cout << "2x Contratorpederos = C" << endl;
	cout << "1x Navio-Tanque = N" << endl;
	cout << "1x Porta - Avião = P" << endl;
	int dados = 0;
	for (int i = 0; i < 7; i++) {
		posicina_elementos(tabuleiro_jogador, i);

	}

}

void imprimi(char tabuleiro_jogador[10][10]) {

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << tabuleiro_jogador[i][j] << " ";

		}
		cout << endl;
	}


}



int main()
{
	char message[BUFFER_SIZE];

	int linha; 
	int coluna;
	int vida = 21;
	char tabuleiro_inimigo[10][10] = {
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
	;

	char tabuleiro_jogador[10][10] = {
		{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
		{'H', 'H', 'H', '-', '-', '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
		{'-', '-', '-','-', '-' , '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-','-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'}

	};


	//introducao(tabuleiro_jogador);

	cout << "====== W11 Sockets ======\n";
	cout << "======== CLIENT =========\n";
	cout << "\n=== Step 1 - Set up DLL ===\n";
	SOCKET clientSocket;
	int port = 55555;
	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0)
	{
		cout << "The winsock dll not found!\n";
		return 0;
	}
	else
	{
		cout << "The winsock dll found!\n";
		cout << "The status: " << wsaData.szSystemStatus << '\n';

	}

	cout << "\n=== Step 2 - Set up Client Socket ===\n";

	clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET)
	{
		cout << "Error at socket():" << WSAGetLastError() << '\n';
		WSACleanup();
		return 0;
	}
	else
	{
		cout << "Socket() is OK!\n";
	}

	cout << "\n=== Step 3 - Connect with Server ===\n";

	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);
	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR)
	{
		cout << "Client: connect() - Failed to connect." << '\n';
		WSACleanup();
		return 0;
	}
	else
	{
		cout << "Client: connect() is OK!\n";
		cout << "Client: Can start sending and receiving data...\n";
	}


	introducao(tabuleiro_jogador);
	cout << "\n=== Step 4 - Chat to the Server ===\n";
	char buffer_reposta[5];
	char aux_resposta[5];
	char buffer_jogada[5];
	char aux_jogada[5];
	do{ 
		memset(&buffer_jogada, 0, 5);

		//Recebe jogada do jogador 1
		cout << "Aguardando Jogador 1:" << endl;;
		int byteCount = recv(clientSocket, (char*)buffer_jogada, sizeof(buffer_jogada), 0);

		if (byteCount == 0)
		{
			WSACleanup();
		}
		if ((tabuleiro_jogador[(int)buffer_jogada[1]][(int)buffer_jogada[2]]!= '-') && (tabuleiro_jogador[(int)buffer_jogada[1]][(int)buffer_jogada[2]] != 'X') && (tabuleiro_jogador[(int)buffer_jogada[1]][(int)buffer_jogada[2]] != 'O')) {
			tabuleiro_jogador[(int)buffer_jogada[1]][(int)buffer_jogada[2]] = 'O';
			vida = vida - 1;
			aux_jogada[0] = static_cast<char>(vida);
			aux_jogada[1] = (int)buffer_jogada[1];
			aux_jogada[2] = (int)buffer_jogada[2];
			aux_jogada[3] = 'A';
			aux_jogada[4] = '\0';

			byteCount = send(clientSocket, (char*)aux_jogada, sizeof(aux_jogada), 0);

			if (vida == 0) {
				cout << "Voce Perdeu" << endl;
				break;

			}
		}
		else {
			tabuleiro_jogador[(int)buffer_jogada[1]][(int)buffer_jogada[2]] = 'X';
			aux_jogada[0] = static_cast<char>(vida);
			aux_jogada[1] = (int)buffer_jogada[1];
			aux_jogada[2] = (int)buffer_jogada[2];
			aux_jogada[3] = 'E';
			aux_jogada[4] = '\0';

			byteCount = send(clientSocket, (char*)aux_jogada, sizeof(aux_jogada), 0);

		}

		//Limpa as variaveis
		memset(&aux_jogada, 0, 5);
		memset(&buffer_jogada, 0, 5);


		//Envia a jogador 2 para o 1
		cout << "TABULEIRO INIMIGO: " << endl;
		imprimi(tabuleiro_inimigo);
		cout << "------------------------------------ " << endl;
		cout << endl;
		cout << "SEU TABULEIRO: " << endl;
		imprimi(tabuleiro_jogador);

		//Envia solicitacao para o jogador 2
		cout << "Digite Linha" << endl;
		cin >> linha;
		cout << "Digite Coluna " << endl;
		cin >> coluna;
		verifica_linha_coluna(&linha, &coluna);


		buffer_reposta[0] = static_cast<char>(vida);
		buffer_reposta[1] = static_cast<char>(linha-1);
		buffer_reposta[2] = static_cast<char>(coluna-1);
		buffer_reposta[3] = ' ';
		buffer_reposta[4] = '\0';

		byteCount = send(clientSocket, (char*)buffer_reposta, sizeof(buffer_reposta), 0);

		if (byteCount == 0)
		{
			WSACleanup();
		}


		memset(&buffer_jogada, 0, 5);
		//Recebe do jogador o status da jogada
		byteCount = recv(clientSocket, (char*)buffer_jogada, sizeof(buffer_jogada), 0);

		if (byteCount == 0)
		{
			WSACleanup();
		}

		cout << buffer_jogada[3] << endl;

		if ((int)buffer_jogada[0] > 0) {
			if (buffer_jogada[3] == 'A') {
				cout << "ACERTOU" << endl;
				tabuleiro_inimigo[(int)buffer_jogada[1]][(int)buffer_jogada[2]] = 'O';
			}
			else {
				cout << "VOCE ERROU" << endl;
				tabuleiro_inimigo[(int)buffer_jogada[1]][(int)buffer_jogada[2]] = 'X';
			}


		}
		else {
			cout << "VOCE GANHOU" << endl;
			break;
		}
	
	} while (1);


	WSACleanup();
	return 0;
}