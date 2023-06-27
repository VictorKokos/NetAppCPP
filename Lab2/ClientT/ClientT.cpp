#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <ctime>

#pragma warning(disable:4996)
using namespace std;



string GetErrorMsgText(int code) // Функция позволяет получить сообщение ошибки
{
	string msgText;
	switch (code)
	{
	case WSAEINTR: msgText = "Работа функции прервана";
		break;
	case WSAEACCES: msgText = "Разрешение отвергнуто";
		break;
	case WSAEFAULT: msgText = "Ошибочный адрес";
		break;
	case WSASYSCALLFAILURE: msgText = "Аварийное завершение системного вызова";
		break;
	default: msgText = "***ERROR***";
		break;
	}

	return msgText;
}
string SetErrorMsgText(string msgText, int code)
{
	return msgText + GetErrorMsgText(code);
};




int main()
{

	try {
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
		{
			throw SetErrorMsgText("startup:", WSAGetLastError());
		}

		SOCKADDR_IN addr;
		int sizeofaddr = sizeof(addr);
		addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		addr.sin_port = htons(2000);
		addr.sin_family = AF_INET;

		SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);

		if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
		{
			throw SetErrorMsgText("connect:", WSAGetLastError());
		}
		
		cout << "Connected!";
		int num;
		cout << "Enter number of messages" << endl;
		cin >> num;
		clock_t start = clock();
		char count[5];
		itoa(num, count, 10);
		send(Connection, count, sizeof(count), NULL);
		for (int i = 0; i <= num; i++) {

		

			char msg[256];
			sprintf(msg, "Hello from Client%d", i);
			send(Connection, msg, sizeof(msg), NULL);
			char received[256];
			recv(Connection, received, sizeof(received), NULL);

		
			int received_i;
			sscanf(received, "Hello from Client%d", &received_i);
			received_i++;

			sprintf(msg, "Hello from Client%d", received_i);
			send(Connection, msg, sizeof(msg), NULL);
		}
		
		clock_t end = clock();
		double elapsed_time = double(end - start) / CLOCKS_PER_SEC;
		cout << "Elapsed time: " << elapsed_time << " seconds" << endl;

		system("pause");

		if (closesocket(Connection) == SOCKET_ERROR)
			throw SetErrorMsgText("closesocket:", WSAGetLastError());

		if (WSACleanup() == SOCKET_ERROR)
			throw SetErrorMsgText("Cleanup:", WSAGetLastError());
	}
	catch (string errorMsgText)
	{
		cout << endl << "WSAGetLastError: " << errorMsgText;
	}
}