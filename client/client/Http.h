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
    std::string extractField(const char* field, const char* header);

    int request(METHOD method, const char* host_address, const char* request_page, const char* param, int port = 80);
    int get(const char* host_address, const char* request_page, int port = 80);
    int post(const char* host_address, const char* request_page, const char* param, int port = 80);

    inline int getLastErrorCode() { return last_error_code; }
    inline std::string getHeader() { return header; }
    inline std::string getBody() { return body; }
    inline std::string getHeaderField(const char* field) { return extractField(field, header.c_str()); }

private:
    std::string string_trim(const std::string& str, const char* delim = " \t\n");

private:
    int last_error_code;
    std::string header;
    std::string body;
};

