#include <winsock2.h>
#include <iostream>
#include <zlib.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "zlib.lib")  // 添加对 zlib 的引用

int pojalivetest() {
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in server;
    const char* ipAddress = "168.235.95.213";  // 目标 IP 地址
    const int port = 80;  // 假设我们要连接到 80 端口 (根据实际情况修改端口)
    char buffer[1024];  // 用于接收数据

    // 初始化 Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Winsock initialization failed!" << std::endl;
        return 1;
    }

    // 创建套接字
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed!" << std::endl;
        WSACleanup();
        return 1;
    }

    // 设置目标服务器信息
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ipAddress);
    server.sin_port = htons(port);

    // 连接到服务器
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        std::cerr << "Connection failed!" << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // 发送请求数据（如果需要发送特定的请求，可以在此修改）
    cconst char* request = "GET /status HTTP/1.1\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7\r\nAccept-Encoding: gzip , deflate\r\nAccept-Language: zh-CN,zh;q=0.9\r\nConnection: keep-alive\r\nCookie: JSESSIONID=FFEB4BB8021B3B45ACC0062FC229895E\r\nHost: poj.org\r\nReferer: http://poj.org/status\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/128.0.0.0 Safari/537.36\r\n\r\n";
    send(sock, request, strlen(request), 0);

    // 接收响应数据
    int bytesReceived = 0;
    std::string responseData = "";
    while ((bytesReceived = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
        responseData.append(buffer, bytesReceived);
    }

    // 检查是否需要解压缩数据（检测 Content-Encoding 头部）
    if (responseData.find("Content-Encoding: gzip") != std::string::npos) {
        // 解压缩 gzip 数据
        uLongf decompressedSize = 1024 * 10;  // 假设解压后的数据大小不会超过 10KB
        char decompressedData[1024 * 10];     // 用于存储解压后的数据

        int result = uncompress((Bytef*)decompressedData, &decompressedSize, (const Bytef*)responseData.c_str(), responseData.size());
        if (result == Z_OK) {
            decompressedData[decompressedSize] = '\0';  // 确保字符串结束
            std::cout << "Decompressed Data: \n" << decompressedData << std::endl;
        } else {
            std::cerr << "Decompression failed with error code: " << result << std::endl;
        }
    } else {
        // 如果不需要解压缩，直接输出原始响应
        std::cout << "Received Data: \n" << responseData << std::endl;
    }

    // 关闭套接字
    closesocket(sock);

    // 清理 Winsock
    WSACleanup();

    return 0;
}

