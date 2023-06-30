#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

using namespace std;

string GetErrorMsgText(int code)
{
    switch (code)
    {
    case WSAEINTR: return "WSAEINTR: Работа функции прервана ";
    default: return "**ERROR**";
    }
}

string SetErrorMsgText(string msgText, int code)
{
    return msgText + GetErrorMsgText(code);
}

int main()
{
    WSADATA wsaData;
    try
    {
        if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
            throw SetErrorMsgText("Startup:", WSAGetLastError());

        SOCKET cC;
        if ((cC = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
            throw SetErrorMsgText("socket:", WSAGetLastError());

        SOCKADDR_IN serv;
        serv.sin_family = AF_INET;
        serv.sin_port = htons(2002);
        serv.sin_addr.s_addr = inet_addr("127.0.0.1");

        char obuf[50] = "Hello";
        int lobuf = strlen(obuf);

        if (sendto(cC, obuf, lobuf + 1, NULL, (sockaddr*)&serv, sizeof(serv)) == SOCKET_ERROR)
            throw SetErrorMsgText("sendto:", WSAGetLastError());

        char ibuf[50];
        int libuf = 0;
        if ((libuf = recvfrom(cC, ibuf, sizeof(ibuf), NULL, NULL, NULL)) == SOCKET_ERROR)
            throw SetErrorMsgText("recvfrom:", WSAGetLastError());
        ibuf[libuf] = 0x00;

        cout << "Answer from server: " << ibuf << endl;

        if (closesocket(cC) == SOCKET_ERROR)
            throw SetErrorMsgText("closesocket:", WSAGetLastError());

        if (WSACleanup() == SOCKET_ERROR)
            throw SetErrorMsgText("Cleanup:", WSAGetLastError());
    }
    catch (string errorMsgText)
    {
        cout << endl << errorMsgText;
    }
}