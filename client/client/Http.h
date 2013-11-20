#pragma once
#include <string>

class Http
{
public:

    enum METHOD {
        GET,
        POST,
    };

    Http(void);
    ~Http(void);

    int extractStatusCode(const char* header);

    int request(std::string* body, METHOD method, const char* host_address, const char* request_page, const char* param, int port = 80);
    int get(std::string* body, const char* host_address, const char* request_page, int port = 80);
    int post(std::string* body, const char* host_address, const char* request_page, const char* param, int port = 80);
};

