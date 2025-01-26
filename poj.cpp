#include <winsock2.h>
#include <iostream>
#include <zlib.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "zlib.lib")  // ��Ӷ� zlib ������

int pojalivetest() {
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in server;
    const char* ipAddress = "168.235.95.213";  // Ŀ�� IP ��ַ
    const int port = 80;  // ��������Ҫ���ӵ� 80 �˿� (����ʵ������޸Ķ˿�)
    char buffer[1024];  // ���ڽ�������

    // ��ʼ�� Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Winsock initialization failed!" << std::endl;
        return 1;
    }

    // �����׽���
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed!" << std::endl;
        WSACleanup();
        return 1;
    }

    // ����Ŀ���������Ϣ
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ipAddress);
    server.sin_port = htons(port);

    // ���ӵ�������
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        std::cerr << "Connection failed!" << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // �����������ݣ������Ҫ�����ض������󣬿����ڴ��޸ģ�
    cconst char* request = "GET /status HTTP/1.1\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7\r\nAccept-Encoding: gzip , deflate\r\nAccept-Language: zh-CN,zh;q=0.9\r\nConnection: keep-alive\r\nCookie: JSESSIONID=FFEB4BB8021B3B45ACC0062FC229895E\r\nHost: poj.org\r\nReferer: http://poj.org/status\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/128.0.0.0 Safari/537.36\r\n\r\n";
    send(sock, request, strlen(request), 0);

    // ������Ӧ����
    int bytesReceived = 0;
    std::string responseData = "";
    while ((bytesReceived = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
        responseData.append(buffer, bytesReceived);
    }

    // ����Ƿ���Ҫ��ѹ�����ݣ���� Content-Encoding ͷ����
    if (responseData.find("Content-Encoding: gzip") != std::string::npos) {
        // ��ѹ�� gzip ����
        uLongf decompressedSize = 1024 * 10;  // �����ѹ������ݴ�С���ᳬ�� 10KB
        char decompressedData[1024 * 10];     // ���ڴ洢��ѹ�������

        int result = uncompress((Bytef*)decompressedData, &decompressedSize, (const Bytef*)responseData.c_str(), responseData.size());
        if (result == Z_OK) {
            decompressedData[decompressedSize] = '\0';  // ȷ���ַ�������
            std::cout << "Decompressed Data: \n" << decompressedData << std::endl;
        } else {
            std::cerr << "Decompression failed with error code: " << result << std::endl;
        }
    } else {
        // �������Ҫ��ѹ����ֱ�����ԭʼ��Ӧ
        std::cout << "Received Data: \n" << responseData << std::endl;
    }

    // �ر��׽���
    closesocket(sock);

    // ���� Winsock
    WSACleanup();

    return 0;
}

