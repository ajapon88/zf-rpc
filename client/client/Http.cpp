#include "Http.h"

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include <sstream>


Http::Http(void)
{
    WSADATA data;
    WSAStartup(MAKEWORD(2,0), &data);
}


Http::~Http(void)
{
    WSACleanup();
}

// ステータスコード抜出し
int Http::extractStatusCode(const char* header)
{
    std::stringstream ss;
    std::string str;
    ss << header;
    while(true) {
        ss >> str;
        if (str.length() <= 0) {
            break;
        }
        if(str.find_first_not_of("0123456789") == std::string::npos) {
            return atoi(str.c_str());
        }
    }

    return 0;
}

// HTTPリクエスト
int Http::request(std::string* body, METHOD method, const char* host_address, const char* request_page, const char* param, int port)
{
    SOCKET sock;
    struct sockaddr_in server;

    *body = "";


    sock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    server.sin_addr.S_un.S_addr = inet_addr(host_address);
    if (server.sin_addr.S_un.S_addr == 0xffffffff) {
        struct hostent *host;

        host = gethostbyname(host_address);
        if (host == NULL) {
            // 名前解決失敗
            printf("gethostbyname: %d\n", WSAGetLastError());
            closesocket(sock);
            return -1;
        }
        server.sin_addr.S_un.S_addr = *(unsigned int *)host->h_addr_list[0];
    }
    connect(sock, (struct sockaddr *)&server, sizeof(server));


    char buf[256];
    std::stringstream send_request;
    if (method == POST) {
        send_request << "POST " << request_page << " HTTP/1.0\r\nContent-Length: " << strlen(param) << "\r\n\r\n" << param;
    } else {
        send_request << "GET " << request_page << " HTTP/1.0\r\n\r\n";
    }

//    printf("%s\n", send_request.str().c_str());

    if (send(sock, send_request.str().c_str(), static_cast<int>(send_request.str().length()), 0) < 0) {
        // 送信失敗
        printf("send: %d\n", WSAGetLastError());
        closesocket(sock);
        return -1;
    }

    // 受信
    int n = 0;
    std::string recv_data;
    do {
        n = recv(sock, buf, sizeof(buf)-1, 0);
        if (n < 0) {
            printf("recv: %d\n", WSAGetLastError());
            closesocket(sock);
            return 1;
        }
        buf[n] = '\0';
        //        printf("%s\n", buf);
        recv_data += buf;
    } while (n > 0);
    closesocket(sock);

    // ヘッダを切り離す
    const char* separate_str = "\r\n\r\n";
    unsigned int separate_pos = static_cast<unsigned int>(recv_data.find(separate_str, 0));
    std::string header;
    if (std::string::npos != separate_pos) {
        header = recv_data.substr(0, separate_pos);
        *body = recv_data.substr(separate_pos+strlen(separate_str));
    } else {
        header = recv_data;
        *body = "";
    }


    return extractStatusCode(header.c_str());
}

int Http::get(std::string* body, const char* host_address, const char* request_page, int port)
{
    return request(body, GET, host_address, request_page, "", port);
}


int Http::post(std::string* body, const char* host_address, const char* request_page, const char* param, int port)
{
    return request(body, POST, host_address, request_page, param, port);
}