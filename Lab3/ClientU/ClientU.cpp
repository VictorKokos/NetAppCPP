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


        SOCKET cC = socket(AF_INET, SOCK_DGRAM, NULL);

        SOCKADDR_IN serv;              // параметры  сокета сервера
        int ls = sizeof(serv);
        serv.sin_family = AF_INET;    // используется ip-адресация  
        serv.sin_port = htons(2000);   // порт 2000
        serv.sin_addr.s_addr = inet_addr("192.168.50.110"); // адрес сервера  
        char obuf[50] = "Hello from ClientU";   //буфер вывода
        int  lobuf = 0;                    //количество отправленных  


        int num;
        cout << "Enter number of messages" << endl;
        cin >> num;
        clock_t start = clock();
        char count[5];
        itoa(num, count, 10);

        if ((lobuf = sendto(cC, count, strlen(count) + 1, NULL,
            (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR)
            throw  SetErrorMsgText("send:", WSAGetLastError());

        for (int i = 0; i <= num; i++)
        {
            sprintf(obuf, "Hello from Client%d", i);


            if ((lobuf = sendto(cC, obuf, strlen(obuf) + 1, NULL,
                (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR)
                throw  SetErrorMsgText("send:", WSAGetLastError());

            


            if (lobuf = recvfrom(cC, obuf, sizeof(obuf), NULL, (sockaddr*)&serv, &ls) == SOCKET_ERROR)
                throw SetErrorMsgText("recv:", WSAGetLastError());

            cout << obuf << endl;

           
            int received_i;
            sscanf(obuf, "Hello from Client%d", &received_i);
            received_i++;

            sprintf(obuf, "Hello from Client%d", received_i);

            if ((lobuf = sendto(cC, obuf, strlen(obuf) + 1, NULL,
                (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR)
                throw  SetErrorMsgText("send:", WSAGetLastError());

        }

        clock_t end = clock();
        double elapsed_time = double(end - start) / CLOCKS_PER_SEC;
        cout << "Elapsed time: " << elapsed_time << " seconds" << endl;

     







        system("pause");

        //ЗАКРЫТИЕ
        if (closesocket(cC) == SOCKET_ERROR)
            throw SetErrorMsgText("closesocket:", WSAGetLastError());

        if (WSACleanup() == SOCKET_ERROR)
            throw SetErrorMsgText("Cleanup:", WSAGetLastError());

    }
    catch (string errorMsgText)
    {
        cout << endl << "WSAGetLastError: " << errorMsgText << WSAGetLastError();
    }
}