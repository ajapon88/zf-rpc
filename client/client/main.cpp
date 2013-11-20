#include <stdio.h>
#include <string>

#include "Http.h"


int main(int argc, char *argv[])
{
    Http http;
    const char* hostname = "localhost";
    const char* xmlrpc_page = "/xmlrpc";
    const char* jsonrpc_page = "/jsonrpc";
    int port = 80;
    int status_code = 0;

    const char* xml_base = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><methodCall><methodName>%s</methodName><params><param><value><int>%d</int></value></param><param><value><int>%d</int></value></param></params></methodCall>";
    char xml[256];

    printf("XMLRPC\n");
    // ‘«‚µŽZ
    _snprintf_s(xml, sizeof(xml), xml_base, "Calculator.add", 42, 18);
    status_code = http.post(hostname, xmlrpc_page, xml, port);
    printf("add(%d):\n%s\n", status_code, http.getBody().c_str());
    // ˆø‚«ŽZ
    _snprintf_s(xml, sizeof(xml), xml_base, "Calculator.subtract", 42, 18);
    status_code = http.post(hostname, xmlrpc_page, xml, port);
    printf("subtract(%d):\n%s\n", status_code, http.getBody().c_str());
    // Š|‚¯ŽZ
    _snprintf_s(xml, sizeof(xml), xml_base, "Calculator.multiply", 42, 18);
    status_code = http.post(hostname, xmlrpc_page, xml, port);
    printf("multiply(%d):\n%s\n", status_code, http.getBody().c_str());
    // Š„‚èŽZ
    _snprintf_s(xml, sizeof(xml), xml_base, "Calculator.divide", 42, 18);
    status_code = http.post(hostname, xmlrpc_page, xml, port);
    printf("divide(%d):\n%s\n", status_code, http.getBody().c_str());

    printf("\n");

    printf("JSONRPC\n");
    const char* json_base = "{\"jsonrpc\": \"2.0\", \"method\": \"%s\", \"params\": [%d, %d], \"id\": 1}";
    char json[256];
    // ‘«‚µŽZ
    _snprintf_s(json, sizeof(json), json_base, "Calculator.add", 42, 18);
    status_code = http.post(hostname, jsonrpc_page, json, port);
    printf("add(%d):\n%s\n", status_code, http.getBody().c_str());
    // ˆø‚«ŽZ
    _snprintf_s(json, sizeof(json), json_base, "Calculator.subtract", 42, 18);
    status_code = http.post(hostname, jsonrpc_page, json, port);
    printf("subtract(%d):\n%s\n", status_code, http.getBody().c_str());
    // Š|‚¯ŽZ
    _snprintf_s(json, sizeof(json), json_base, "Calculator.multiply", 42, 18);
    status_code = http.post(hostname, jsonrpc_page, json, port);
    printf("multiply(%d):\n%s\n", status_code, http.getBody().c_str());
    // Š„‚èŽZ
    _snprintf_s(json, sizeof(json), json_base, "Calculator.divide", 42, 18);
    status_code = http.post(hostname, jsonrpc_page, json, port);
    printf("divide(%d):\n%s\n", status_code, http.getBody().c_str());


    getchar();

    return 0;
}
