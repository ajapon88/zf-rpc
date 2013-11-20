#include "Http.h"

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include <sstream>


Http::Http(void):
last_error_code(0)
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

    // 1行目取出し
    ss << header;
    std::getline(ss, str);
    ss.clear();
    ss.str(str);

    while(true) {
        ss >> str;
        if (str.length() <= 0) {
            break;
        }
        // 数字だけの項目をステータスコードとみなす
        if(str.find_first_not_of("0123456789") == std::string::npos) {
            return atoi(str.c_str());
        }
    }

    return 0;
}

// フィールド抜出し
std::string Http::extractField(const char* field, const char* header)
{
    std::stringstream ss;
    std::string line;
    std::string search_field(field);
    // フィールドには’：’がつく
    search_field += ':';

    ss << header;
    while(std::getline(ss, line)) {
        line = string_trim(line);

        if (line.find(search_field.c_str()) == 0) {
            return string_trim(line.substr(search_field.length()));
        }
    }

    return "";
}

// HTTPリクエスト
int Http::request(METHOD method, const char* host_address, const char* request_page, const char* param, int port)
{
    SOCKET sock;
    struct sockaddr_in server;

    header = "";
    body = "";


    sock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    server.sin_addr.S_un.S_addr = inet_addr(host_address);
    if (server.sin_addr.S_un.S_addr == 0xffffffff) {
        struct hostent *host;

        host = gethostbyname(host_address);
        if (host == NULL) {
            // 名前解決失敗
            last_error_code = WSAGetLastError();
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
        last_error_code = WSAGetLastError();
        closesocket(sock);
        return -1;
    }

    // 受信
    int n = 0;
    std::string recv_data;
    do {
        n = recv(sock, buf, sizeof(buf)-1, 0);
        if (n < 0) {
            last_error_code = WSAGetLastError();
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
        body = recv_data.substr(separate_pos+strlen(separate_str));
    } else {
        header = recv_data;
        body = "";
    }

    last_error_code = WSAGetLastError();

    return extractStatusCode(header.c_str());
}

int Http::get(const char* host_address, const char* request_page, int port)
{
    return request(GET, host_address, request_page, "", port);
}


int Http::post(const char* host_address, const char* request_page, const char* param, int port)
{
    return request(POST, host_address, request_page, param, port);
}

std::string getHeader();
std::string getBody();


std::string Http::string_trim(const std::string& str, const char* delim)
{
    const int p1 = static_cast<int>(str.find_first_not_of(delim));
    if(p1 == std::string::npos){
        return std::string();
    }
    const int p2 = static_cast<int>(str.find_last_not_of(delim));
    return str.substr(p1, p2 - p1 + 1);
}