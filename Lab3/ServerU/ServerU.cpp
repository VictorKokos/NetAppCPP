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
        addr.sin_port = htons(2000);
        addr.sin_family = AF_INET;

        SOCKET sS = socket(AF_INET, SOCK_DGRAM, NULL);
        bind(sS, (SOCKADDR*)&addr, sizeof(addr));









        SOCKADDR_IN clnt; // параметры сокета клиента
        memset(&clnt, 0, sizeof(clnt)); // обнулить память
        int lc = sizeof(clnt);
        char ibuf[50]; //буфер ввода 
        int lb = 0; //количество принятых байт
        if (lb = recvfrom(sS, ibuf, sizeof(ibuf), NULL, (sockaddr*)&clnt, &lc) == SOCKET_ERROR)
            throw SetErrorMsgText("recv:", WSAGetLastError());





     

        //ЗАКРЫТИЕ
        if (closesocket(sS) == SOCKET_ERROR)
            throw SetErrorMsgText("closesocket:", WSAGetLastError());

        if (WSACleanup() == SOCKET_ERROR)
            throw SetErrorMsgText("Cleanup:", WSAGetLastError());

    }
    catch (string errorMsgText)
    {
        cout << endl << "WSAGetLastError: " << errorMsgText;
    }
}