#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>

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
		addr.sin_port = htons(1111);
		addr.sin_family = AF_INET;

		SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
		bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
		listen(sListen, SOMAXCONN);

		SOCKET newConnection;
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

		if (newConnection == 0)
		{
			throw SetErrorMsgText("socket:", WSAGetLastError());
		}
		else
		{
			cout << "Client connected!" << endl;
			char msg[256] = "Message";
			send(newConnection, msg, sizeof(msg), NULL);
		}

		system("pause");







		//ЗАКРЫТИЕ
		if (closesocket(sListen) == SOCKET_ERROR)
			throw SetErrorMsgText("closesocket:", WSAGetLastError());

		if (WSACleanup() == SOCKET_ERROR)
			throw SetErrorMsgText("Cleanup:", WSAGetLastError());

	}
	catch (string errorMsgText)
	{
		cout << endl << "WSAGetLastError: " << errorMsgText;
	}
}