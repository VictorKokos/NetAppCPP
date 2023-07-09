#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <Windows.h>
#pragma warning(disable:4996)
using namespace std;



string GetMSError(int code) // Функция позволяет получить сообщение ошибки
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
    case 2: return "Ошибка при создании файла";
    default: return "**ERROR**";
    }


}
string SetMSError(string msgText, int code)
{
    return msgText + GetMSError(code);
};











int main()
{
    setlocale(LC_ALL, "");

    try
    {
       
        HANDLE hM1, hM2, hM3; // дескриптор почтового ящика 

  
        DWORD wb; // длина записанного сообщения
        char wbuf[] = "Hello from Maislot-client"; // буфер вывода 
        
            if ((hM1 = CreateFile(L"\\\\DESKTOP-DJ6A5P8\\mailslot\\Box",
                GENERIC_WRITE, // будем писать в ящик
                FILE_SHARE_READ, // разрешаем одновременно читать 
                NULL,
                OPEN_EXISTING, // ящик уже есть
                NULL, NULL)) == INVALID_HANDLE_VALUE)
                throw SetMSError("CreateFile1", GetLastError());
            clock_t start = clock();
            for (int i = 0; i <= 1000; i++)
            {

                char msg[100];
                sprintf(msg, "Hello from Maislot-client%d", i);
                if (!WriteFile(hM1,
                    msg, // буфер
                    sizeof(msg), // размер буфера
                    &wb, // записано
                    NULL))
                    throw SetMSError("WriteFile1", GetLastError());



                


            }
            clock_t end = clock();
            double elapsed_time = double(end - start) / CLOCKS_PER_SEC;
            cout << "Elapsed time: " << elapsed_time << " seconds" << endl;
            CloseHandle(hM1);
          
            //if ((hM2 = CreateFile(L"\\\\.\\mailslot\\Box",
            //    GENERIC_WRITE, // будем писать в ящик
            //    FILE_SHARE_READ, // разрешаем одновременно читать 
            //    NULL,
            //    OPEN_EXISTING, // ящик уже есть
            //    NULL, NULL)) == INVALID_HANDLE_VALUE)
            //    throw SetMSError("CreateFile2", GetLastError());
            //if (!WriteFile(hM2,
            //    wbuf, // буфер
            //    sizeof(wbuf), // размер буфера
            //    &wb, // записано
            //    NULL))
            //    throw SetMSError("WriteFile2", GetLastError());

            //if ((hM3 = CreateFile(L"\\\\.\\mailslot\\Box",
            //    GENERIC_WRITE, // будем писать в ящик
            //    FILE_SHARE_READ, // разрешаем одновременно читать 
            //    NULL,
            //    OPEN_EXISTING, // ящик уже есть
            //    NULL, NULL)) == INVALID_HANDLE_VALUE)
            //    throw SetMSError("CreateFile3", GetLastError());
            //if (!WriteFile(hM3,
            //    wbuf, // буфер
            //    sizeof(wbuf), // размер буфера
            //    &wb, // записано
            //    NULL))
            //    throw SetMSError("WriteFile3", GetLastError());
        

    }
    catch (string errorMsgText)
    {
        cout << endl << "WSAGetLastError: " << errorMsgText << GetLastError();
    }
}