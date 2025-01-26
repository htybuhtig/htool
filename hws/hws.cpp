#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include<bits/stdc++.h>
#include<cstring>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
string readf(string fn1){
	string fn = fn1;
	if(fn=="/") fn = "/index.html";
	string t = "host"+fn;
	ifstream file(t.c_str());
    if (file.is_open()) {
        file.seekg(0, std::ios::end);
        std::streampos length = file.tellg();
        file.seekg(0, std::ios::beg);
        char* buffer = new char[length];
        file.read(buffer, length);
        //std::cout << buffer << std::endl;
        string ans = buffer;
        ans = "HTTP/1.1 200 OK\r\nServer: nginx/1.14.0 (Ubuntu)\r\nDate: Sun, 26 Jan 2025 00:58:24 GMT\r\nContent-Type: text/html;charset=utf-8\r\nTransfer-Encoding: chunked\r\nConnection: keep-alive\r\nContent-Encoding: deflate\r\nVary: Accept-Encoding\r\n\r\n"+ans;
        return ans;
        delete[] buffer;
        file.close();
    } else {
        std::cout << "无法打开文件"<<t << std::endl;
    }
    return "HTTP 404 ERROR\r\n\r\n";
}
int main1() {
    WSADATA wsaData;
    int startupResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (startupResult != 0) {
        cerr << "WSAStartup failed: " << WSAGetLastError() << endl;
        return 1;
    }
    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket == INVALID_SOCKET) {
        cerr << "Socket creation failed: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // Listen on all IPs of the machine
    serverAddr.sin_port = htons(8080); // Port number to listen on, e.g., 8080 for HTTP
    if (bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "Bind failed: " << WSAGetLastError() << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) { // SOMAXCONN is a good default value for backlog parameter.
        cerr << "Listen failed: " << WSAGetLastError() << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    SOCKET clientSocket = accept(listenSocket, NULL, NULL); // Accept a client connection.
    if (clientSocket == INVALID_SOCKET) {
        cerr << "Accept failed: " << WSAGetLastError() << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    } else {
        char buffer[1024]; // Buffer for the received data.
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0); // Receive data from the client.
        if (bytesReceived > 0) { // Process the request (in this case, just echo it back).
            buffer[bytesReceived] = '\0'; // Null-terminate the string for easier printing.
            cout << "Received: \n" << buffer << endl; // Echo back the received data to the client.
            string res = buffer;
            int p = res.find("GET ")+4;
            string t1 = res.substr(p);
            int p1 = t1.find("HTTP/");
            string t2 = t1.substr(0,p1-1);
            cout<<"t2:"<<t2<<endl;
            const char* response = readf(t2).c_str();
            cout<<"Send msg:\n"<<response<<endl;
            send(clientSocket, response, strlen(response), 0); // Send the response back to the client.
        } else { // Handle errors or close connection if no data received.
            cerr << "No data received." << endl; // Or handle error appropriately.
        }
    }
    closesocket(clientSocket);
    WSACleanup();
}
int main(){
	while(1){
		main1();
	}
	return 0;
}
