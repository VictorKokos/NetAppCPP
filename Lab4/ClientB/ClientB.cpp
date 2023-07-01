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
    case WSAEACCES: return "WSAEACCES: Разрешение отвергнуто";
    case WSAEFAULT:	return "WSAEFAULT: Ошибочный адрес";
    case WSAEINVAL:	return "WSAEINVAL: Ошибка в аргументе";
    case WSAEMFILE: return "WSAEMFILE: Слишком много файлов открыто";
    case WSAEWOULDBLOCK: return "WSAEWOULDBLOCK: Ресурс временно недоступен";
    case WSAEINPROGRESS: return "WSAEINPROGRESS: Операция в процессе развития";
    case WSAEALREADY: return "WSAEALREADY: Операция уже выполняется";
    case WSAENOTSOCK: return "WSAENOTSOCK: Сокет задан неправильно";
    case WSAEDESTADDRREQ: return "WSAEDESTADDRREQ: Требуется адрес расположения";
    case WSAEMSGSIZE: return "WSAEMSGSIZE: Сообщение слишком длинное";
    case WSAEPROTOTYPE: return "WSAEPROTOTYPE: Неправильный тип протокола для сокета";
    case WSAENOPROTOOPT: return "WSAENOPROTOOPT: Ошибка в опции протокола";
    case WSAEPROTONOSUPPORT: return "WSAEPROTONOSUPPORT: Протокол не поддерживается";
    case WSAESOCKTNOSUPPORT: return "WSAESOCKTNOSUPPORT: Тип сокета не поддерживается";
    case WSAEOPNOTSUPP:	return "WSAEOPNOTSUPP: Операция не поддерживается";
    case WSAEPFNOSUPPORT: return "WSAEPFNOSUPPORT: Тип протоколов не поддерживается";
    case WSAEAFNOSUPPORT: return "WSAEAFNOSUPPORT: Тип адресов не поддерживается протоколом";
    case WSAEADDRINUSE:	return "WSAEADDRINUSE: Адрес уже используется";
    case WSAEADDRNOTAVAIL: return "WSAEADDRNOTAVAIL: Запрошенный адрес не может быть использован";
    case WSAENETDOWN: return "WSAENETDOWN: Сеть отключена";
    case WSAENETUNREACH: return "WSAENETUNREACH: Сеть не достижима";
    case WSAENETRESET: return "WSAENETRESET: Сеть разорвала соединение";
    case WSAECONNABORTED: return "WSAECONNABORTED: Программный отказ связи";
    case WSAECONNRESET:	return "WSAECONNRESET: Связь восстановлена";
    case WSAENOBUFS: return "WSAENOBUFS: Не хватает памяти для буферов";
    case WSAEISCONN: return "WSAEISCONN: Сокет уже подключен";
    case WSAENOTCONN: return "WSAENOTCONN: Сокет не подключен";
    case WSAESHUTDOWN: return "WSAESHUTDOWN: Нельзя выполнить send : сокет завершил работу";
    case WSAETIMEDOUT: return "WSAETIMEDOUT: Закончился отведенный интервал  времени";
    case WSAECONNREFUSED: return "WSAECONNREFUSED: Соединение отклонено";
    case WSAEHOSTDOWN: return "WSAEHOSTDOWN: Хост в неработоспособном состоянии";
    case WSAEHOSTUNREACH: return "WSAEHOSTUNREACH: Нет маршрута для хоста";
    case WSAEPROCLIM: return "WSAEPROCLIM: Слишком много процессов";
    case WSASYSNOTREADY: return "WSASYSNOTREADY: Сеть не доступна";
    case WSAVERNOTSUPPORTED: return "WSAVERNOTSUPPORTED: Данная версия недоступна";
    case WSANOTINITIALISED:	return "WSANOTINITIALISED: Не выполнена инициализация WS2_32.DLL";
    case WSAEDISCON: return "WSAEDISCON: Выполняется отключение";
    case WSATYPE_NOT_FOUND: return "WSATYPE_NOT_FOUND: Класс не найден";
    case WSAHOST_NOT_FOUND:	return "WSAHOST_NOT_FOUND: Хост не найден";
    case WSATRY_AGAIN: return "WSATRY_AGAIN: Неавторизированный хост не найден";
    case WSANO_RECOVERY: return "WSANO_RECOVERY: Неопределенная ошибка";
    case WSANO_DATA: return "WSANO_DATA: Нет записи запрошенного типа";
    case WSA_INVALID_HANDLE: return "WSA_INVALID_HANDLE: Указанный дескриптор события с ошибкой";
    case WSA_INVALID_PARAMETER: return "WSA_INVALID_PARAMETER: Один или более параметров с ошибкой";
    case WSA_IO_INCOMPLETE:	return "WSA_IO_INCOMPLETE: Объект ввода - вывода не в сигнальном состоянии";
    case WSA_IO_PENDING: return "WSA_IO_PENDING: Операция завершится позже";
    case WSA_NOT_ENOUGH_MEMORY: return "WSA_NOT_ENOUGH_MEMORY: Не достаточно памяти";
    case WSA_OPERATION_ABORTED: return "WSA_OPERATION_ABORTED: Операция отвергнута";
    case WSASYSCALLFAILURE: return "WSASYSCALLFAILURE: Аварийное завершение системного вызова";
    default: return "**ERROR**";
    }
}

string SetErrorMsgText(string msgText, int code)
{
    return msgText + GetErrorMsgText(code);
}



bool GetServer(char* call, short port, struct sockaddr* from, int* flen)
{
    SOCKET sS;
    SOCKADDR_IN serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    serv.sin_addr.s_addr = INADDR_BROADCAST;

    if ((sS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
        throw SetErrorMsgText("socket:", WSAGetLastError());

    int optval = 1;
    int lbuflen = sizeof(int);
    if (setsockopt(sS, SOL_SOCKET, SO_BROADCAST, (char*)&optval, lbuflen) == SOCKET_ERROR)
        throw SetErrorMsgText("setsockopt:", WSAGetLastError());

    if (sendto(sS, call, strlen(call) + 1, NULL, (sockaddr*)&serv, sizeof(serv)) == SOCKET_ERROR)
        throw SetErrorMsgText("sendto:", WSAGetLastError());

    char ibuf[50];
    int libuf = 0;

    int timeout = 5000; // 5 seconds
    if (setsockopt(sS, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) == SOCKET_ERROR)
        throw SetErrorMsgText("setsockopt:", WSAGetLastError());


    if ((libuf = recvfrom(sS, ibuf, sizeof(ibuf), NULL, from, flen)) == SOCKET_ERROR)
    {
        if (WSAGetLastError() == WSAETIMEDOUT)
            return false;
        else
            throw SetErrorMsgText("recvfrom:", WSAGetLastError());
    }
    ibuf[libuf] = 0x00;
    if (strcmp(ibuf, call) != 0)
        return false;

    if (closesocket(sS) == SOCKET_ERROR)
        throw SetErrorMsgText("closesocket:", WSAGetLastError());
    return true;
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
        serv.sin_port = htons(3000);
        serv.sin_addr.s_addr = inet_addr("127.0.0.1");

        char obuf[50] = "Hello";
        int lobuf = strlen(obuf);

        
        
        SOCKADDR_IN from;
        int flen = sizeof(from);

    
        if (GetServer(obuf, 3000, (struct sockaddr*)&from, &flen))
        {
            cout << "Answer from server: " << obuf << endl;


            cout << "Server address: " << inet_ntoa(from.sin_addr) << ":" << ntohs(from.sin_port) << endl;
        }
        else
        {
            cout << "No answer from server" << endl;
        }

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