#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[1024];

    // Cria um soquete do cliente.
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    // Configura o endereço do servidor.
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080); // Define a porta do servidor
    serverAddr.sin_addr.s_addr = inet_addr("3.85.17.170"); // Substitua pelo IP do servidor AWS

    // Estabelece uma conexão com o servidor.
    connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    while (1) {
        // Limpa o buffer para uso.
        memset(buffer, 0, sizeof(buffer));

        printf("[Cliente] Digite uma mensagem: "); // Mensagem para indicar que é a vez do cliente escrever a mensagem.
        
        // Obtém uma mensagem do usuário (cliente).
        fgets(buffer, 1024, stdin);

        // Envia a mensagem para o servidor.
        send(clientSocket, buffer, strlen(buffer), 0);

        // Recebe a resposta do servidor.
        recv(clientSocket, buffer, 1024, 0);

        printf("[Servidor]: %s", buffer); // Imprime a mensagem recebida do servidor.
    }

    // Fecha o soquete do cliente quando não é mais necessário.
    close(clientSocket);

    return 0;
}
