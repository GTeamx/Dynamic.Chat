#include <iostream>
#include <winsock2.h>
#include <lmcons.h>
#include <vector>
#include <thread>
#include <string>

void runServer();
char * translateEncryptionKey(std::string encryptionKey);
std::string XOR(std::string data, const char key[]);
std::vector<std::string> keysArray;
std::string encryptionKey;
std::string username;
std::string broadcastAddress = "192.168.1.255";

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Get username
    TCHAR name [ UNLEN + 1 ];
    DWORD size = UNLEN + 1;

    if (GetUserName( (TCHAR*)name, &size )) {
        username = name;
    }

    time_t now = time(0);
    tm* ltm = localtime(&now);

    encryptionKey = username + std::to_string(ltm->tm_sec);

    std::cout << "           ██████╗ ██╗   ██╗███╗   ██╗ █████╗ ███╗   ███╗██╗ ██████╗\n"
                 "           ██╔══██╗╚██╗ ██╔╝████╗  ██║██╔══██╗████╗ ████║██║██╔════╝\n"
                 "           ██║  ██║ ╚████╔╝ ██╔██╗ ██║███████║██╔████╔██║██║██║     \n"
                 "           ██║  ██║  ╚██╔╝  ██║╚██╗██║██╔══██║██║╚██╔╝██║██║██║     \n"
                 "           ██████╔╝   ██║   ██║ ╚████║██║  ██║██║ ╚═╝ ██║██║╚██████╗\n"
                 "           ╚═════╝    ╚═╝   ╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝     ╚═╝╚═╝ ╚═════╝\n"
                 "                                                                    \n"
                 "                        ██████╗██╗  ██╗ █████╗ ████████╗            \n"
                 "                       ██╔════╝██║  ██║██╔══██╗╚══██╔══╝            \n"
                 "                       ██║     ███████║███████║   ██║               \n"
                 "                       ██║     ██╔══██║██╔══██║   ██║               \n"
                 "                       ╚██████╗██║  ██║██║  ██║   ██║               \n"
                 "                        ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝               v1\n\n\n" << std::endl;

    std::cout << "* Your key is '" + encryptionKey + "'\n"
        << "* The other users have to run 'addmdp " + encryptionKey + "' to be able to chat with you.\n"
        << "* To receive other users messages do 'addmdp theirkey'\n"
        << "* You can change your key using 'mdp yournewkey'\n" << std::endl;

    std::thread serverThread(runServer);

    while (true) {

        // Initialize WinSock
        WSAData wsaData{};

        // Start WSA
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cout << "An error occurred when starting WSA." << std::endl;
            return 1;
        }

        // Create ClientSocket
        auto clientSocket = INVALID_SOCKET;

        clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
        if (clientSocket == INVALID_SOCKET) {
            std::cout << "An error occurred when creating client socket." << std::endl;
            WSACleanup();
            return 1;
        }

        // Allow for broadcast sending
        char broadcast = '1';
        if (setsockopt(clientSocket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0) {
            std::cout << "An error occurred when changing broadcast settings." << std::endl;
            closesocket(clientSocket);
            WSACleanup();
        }

        // Configure for broadcast send on port 888
        struct sockaddr_in clientSocketConfig{};

        clientSocketConfig.sin_family = AF_INET;
        clientSocketConfig.sin_port = htons(888);
        clientSocketConfig.sin_addr.s_addr = inet_addr(broadcastAddress.c_str());

        std::string userMessage;
        std::getline(std::cin, userMessage);

        if (userMessage.find("mdp ") == 0) {

            encryptionKey = userMessage.substr(4, userMessage.length());
            std::cout << "*\n"
                      << "* Your new key is '"
                      << encryptionKey
                      << "'\n"
                      << "*\n" << std::endl;

        } else if (userMessage.find("addmdp ") == 0) {

            std::string addKey = userMessage.substr(7, userMessage.length());

            keysArray.push_back(addKey);
            std::cout << "*\n"
                      << "* The key '"
                      << addKey
                      << "' has been added\n"
                      << "*\n"
                      << std::endl;
        } else if (userMessage.find("broadcastIp ") == 0) {

            broadcastAddress = userMessage.substr(12, userMessage.length());

            std::cout << "*\n"
                      << "* Broadcast address set to '"
                      << broadcastAddress + "'"
                      << "*\n"
                      << std::endl;

        } else {

            std::string message = XOR("IDENT=" + encryptionKey + "USER=" + username + "," + userMessage, translateEncryptionKey(encryptionKey));

            std::cout << message;

            // Send UDP packet to broadcast
            sendto(clientSocket, message.c_str(), strlen(message.c_str()) + 1, 0, (sockaddr *) &clientSocketConfig,
                   sizeof(clientSocketConfig));

            // Cleanup
            closesocket(clientSocket);
            WSACleanup();
        }
    }
}

void runServer() {

    while (true) {

        // Initialize WinSock
        WSAData wsaData{};

        // Start WSA
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cout << "An error occurred when starting WSA." << std::endl;
        }

        // Create ServerSocket
        auto serverSocket = INVALID_SOCKET;

        serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
        if (serverSocket == INVALID_SOCKET) {
            std::cout << "An error occurred when creating server socket." << std::endl;
            WSACleanup();
        }

        // Allow for broadcast receiving
        char broadcast = '1';
        if (setsockopt(serverSocket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0) {
            std::cout << "An error occurred when changing broadcast settings." << std::endl;
            closesocket(serverSocket);
            WSACleanup();
        }

        // Configure for broadcast receive on port 888
        struct sockaddr_in serverSocketConfig{};
        struct sockaddr_in clientSocketConfig{};

        int len = sizeof(struct sockaddr_in);
        char recvbuff[65535];
        int recvbufflen = 65535;

        serverSocketConfig.sin_family = AF_INET;
        serverSocketConfig.sin_port = htons(888);
        serverSocketConfig.sin_addr.s_addr = INADDR_ANY;

        // Bind client socket to listen for broadcasts
        if (bind(serverSocket, (sockaddr *) &serverSocketConfig, sizeof(serverSocketConfig)) < 0) {
            std::cout << "An error occurred when binding server socket." << std::endl;
            closesocket(serverSocket);
            WSACleanup();
        }

        // Receive incoming data from ClientSocket
        recvfrom(serverSocket, recvbuff, recvbufflen, 0, (sockaddr *) &clientSocketConfig, &len);

        std::string decryptedString;
        for (const auto & i : keysArray) {
            decryptedString = XOR(recvbuff, translateEncryptionKey(i));

            if (decryptedString.substr(0, i.length() + 6) == "IDENT=" + i) {

                // Get current time
                time_t now = time(0);
                tm* ltm = localtime(&now);
                std::string time = std::to_string(ltm->tm_hour) + ":" + std::to_string(ltm->tm_min) + ":" + std::to_string(ltm->tm_sec);

                // Get sender's username & message cleanly
                std::string cleanMessage = decryptedString.substr(decryptedString.find(',') + 1, decryptedString.length());
                std::string displayUsername = decryptedString.substr(i.length() + 11, (decryptedString.length() - 11 - i.length()) - (cleanMessage.length() + 1));

                std::cout << time + " | " + displayUsername + ": " + cleanMessage << std::endl;
            }
        }

        // Cleanup
        closesocket(serverSocket);
        WSACleanup();
    }
}

char * translateEncryptionKey(std::string encryptionKey) { const int length = encryptionKey.length(); char* char_array = new char[length + 1]; strcpy(char_array, encryptionKey.c_str()); return char_array; }

std::string XOR(std::string data, const char key[]) { std::string xorstring = data; for (int i = 0; i < xorstring.size(); i++) { xorstring[i] = data[i] ^ key[i % (sizeof(key) / sizeof(char))]; } return xorstring; }
