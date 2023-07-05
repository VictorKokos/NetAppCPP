#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <Windows.h>
#pragma warning(disable:4996)
using namespace std;



string GetPipeError(int code) // Функция позволяет получить сообщение ошибки
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
string SetPipeError(string msgText, int code)
{
    return msgText + GetPipeError(code);
};











int main()
{


    try
    {
        HANDLE hPipe;
        DWORD dwWritten;
        char buffer[1024];





        if ((hPipe = CreateFile(
            L"\\\\.\\pipe\\Tube",
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL, OPEN_EXISTING, NULL,
            NULL)) == INVALID_HANDLE_VALUE)
            throw SetPipeError("createfile:", GetLastError());
        
        if (hPipe != INVALID_HANDLE_VALUE)
        {

            int num;
            cout << "Enter number of messages" << endl;
            cin >> num;
            clock_t start = clock();
            char count[5];
            itoa(num, count, 10);


            WriteFile(hPipe, count, 30, &dwWritten, NULL);

            for (int i = 0; i <= num; i++)
            {
                char msg[256];
                sprintf(msg, "Hello from Client%d", i);
                WriteFile(hPipe, msg, 30, &dwWritten, NULL);

                if (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &dwWritten, NULL) != FALSE)
                {
                    buffer[dwWritten] = '\0';
                    int received_i;
                    sscanf(buffer, "Hello from Client%d", &received_i);
                    received_i++;

                    sprintf(msg, "Hello from Client%d", received_i);

                    WriteFile(hPipe, msg, 30, &dwWritten, NULL);
                }


            }
            clock_t end = clock();
            double elapsed_time = double(end - start) / CLOCKS_PER_SEC;
            cout << "Elapsed time: " << elapsed_time << " seconds" << endl;


        
        }




        // Закрыть дескриптор канала
        CloseHandle(hPipe);
    }
    catch (string errorMsgText)
    {
        cout << endl << "WSAGetLastError: " << errorMsgText;
    }
}