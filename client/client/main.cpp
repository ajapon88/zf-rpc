#include <stdio.h>
#include <string>
#include "Http.h"


int main(int argc, char *argv[])
{
    Http http;
    const char* hostname = "localhost";
    const char* xmlrpc_page = "/xmlrpc";
    int port = 80;
    int status_code = 0;
    std::string data;

    const char* xml_base = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><methodCall><methodName>%s</methodName><params><param><value><int>%d</int></value></param><param><value><int>%d</int></value></param></params></methodCall>";
    char xml[256];

    // ‘«‚µŽZ
    _snprintf_s(xml, sizeof(xml), xml_base, "Calculator.add", 42, 18);
    status_code = http.post(&data, hostname, xmlrpc_page, xml, port);
    printf("add(%d):\n%s\n", status_code, data.c_str());
    // ˆø‚«ŽZ
    _snprintf_s(xml, sizeof(xml), xml_base, "Calculator.subtract", 42, 18);
    status_code = http.post(&data, hostname, xmlrpc_page, xml, port);
    printf("subtract(%d):\n%s\n", status_code, data.c_str());
    // Š|‚¯ŽZ
    _snprintf_s(xml, sizeof(xml), xml_base, "Calculator.multiply", 42, 18);
    status_code = http.post(&data, hostname, xmlrpc_page, xml, port);
    printf("multiply(%d):\n%s\n", status_code, data.c_str());
    // Š„‚èŽZ
    _snprintf_s(xml, sizeof(xml), xml_base, "Calculator.divide", 42, 18);
    status_code = http.post(&data, hostname, xmlrpc_page, xml, port);
    printf("divide(%d):\n%s\n", status_code, data.c_str());

    getchar();

    return 0;
}
