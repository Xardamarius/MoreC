#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include <winsock2.h>

void chat(SOCKET s)
{
    char mes[200];
    WSAEventSelect(s, 0, FD_READ);
    do
    {
        if ( (GetKeyState(VK_F2) < 0) && (GetForegroundWindow() == GetConsoleWindow()) )
        {
            printf("message: ");
            while (getch() != 0);
            scanf("\n%200[0-9a-zA-Z.,! ]",  mes);
            send(s, mes, sizeof(mes), 0 );
        }

        if (recv(s, mes, sizeof(mes), 0 ) > 0)
            printf("%s\n", mes);
    }
    while (GetKeyState(VK_ESCAPE) >= 0);
}

int main()
{
    WSADATA ws;
    WSAStartup( MAKEWORD(2,2), &ws );

    SOCKET s;
    s = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN sa;
        memset(&sa, 0, sizeof(sa) );
        sa.sin_family = AF_INET;
        sa.sin_port  = htons(1234);

    char c;
    printf("s - server\nk - client\n");
    scanf("%c", &c);

    if (c == 'k')
    {
        char ip[100];
        printf("set ip address: ");
        scanf("\n%100[0-9.]", ip);

        sa.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

        connect(s, &sa, sizeof(sa) );

        chat(s);
    }

    if (c == 's')
    {
        bind(s, &sa, sizeof(sa) );

        listen(s, 100);

        char buf[200];
        memset(buf, 0, sizeof(buf) );
            SOCKET client_socket;
            SOCKADDR_IN client_addr;
            int client_addr_size = sizeof(client_addr);

        while (client_socket = accept(s, &client_addr, &client_addr_size) )
        {
            printf("connect OK\n");

            chat(client_socket);

        }
    }

    closesocket(s);

    return 0;
}
