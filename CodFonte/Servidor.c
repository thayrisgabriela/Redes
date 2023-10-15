#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrSize = sizeof(struct sockaddr_in);
    char buffer[1024];

    // Cria um soquete do servidor.
    serverSocket = socket(PF_INET, SOCK_STREAM, 0);

    // Configura o endereço do servidor.
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080); // Define a porta do servidor.
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Aceita conexões de qualquer interface.

    // Vincula o soquete do servidor ao endereço e à porta especificados.
    bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    // Coloca o soquete do servidor no modo de escuta e permite até 5 conexões pendentes.
    listen(serverSocket, 5);

    // Imprime uma mensagem indicando que o servidor está aguardando conexões.
    printf("[Servidor] Aguardando conexão...\n");

    // Aceita uma conexão de cliente.
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrSize);

    while (1) {
        // Recebe dados do cliente e armazena no buffer.
        recv(clientSocket, buffer, 1024, 0);

        // Imprime a mensagem recebida do cliente.
        printf("Mensagem enviada pelo Cliente: %s", buffer);

        // Aqui você pode processar a mensagem recebida e gerar uma resposta.
        // A lógica de processamento de mensagens deve ser adicionada aqui.

        // Limpa o buffer para uso posterior.
        memset(buffer, 0, sizeof(buffer));

        printf("Resposta do Servidor: "); // Indica que o servidor está enviando uma resposta.

        // Obtém uma nova mensagem do servidor.
        fgets(buffer, 1024, stdin);

        // Envia a mensagem do servidor de volta ao cliente.
        send(clientSocket, buffer, strlen(buffer), 0);
    }

    // Fecha os soquetes do cliente e do servidor quando o loop é encerrado.
    close(clientSocket);
    close(serverSocket);

    return 0;
}
