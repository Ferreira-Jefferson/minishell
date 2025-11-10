#include <stdio.h>
#include <unistd.h> // Header obrigatório para chdir e getcwd
#include <stdlib.h> // Para NULL e malloc (embora getcwd possa usar buffer)
#include <errno.h> // Para NULL e malloc (embora getcwd possa usar buffer)

void ft_handler_error(char *message)
{
	printf("Error: %d\n", errno);
	perror(message);
}

int main() {
    char buffer_antes[1024];
    char buffer_depois[1024];

    // 1. Pega o diretório atual ANTES da mudança
    if (getcwd(buffer_antes, sizeof(buffer_antes)) != NULL) {
        printf("Diretório atual (antes): %s\n", buffer_antes);
		printf("Error 1: %d\n", errno);
    } else {
		printf("Error 1d: %d\n", errno);
        perror("Erro ao pegar diretório inicial");
        return 1;
    }

    // 2. Tenta mudar para o diretório raiz "/"
    // Você pode mudar "/" para qualquer caminho que exista, ex: "/tmp"
    const char *novo_caminho = "/src"; 
    int resultado = chdir(novo_caminho);

    // 3. Verifica se a mudança funcionou
    if (resultado == 0) {
        printf("MUDANÇA BEM-SUCEDIDA para: %s\n", novo_caminho);
		printf("Error 2: %d\n", errno);
    } else {
        // Se falhou (retornou -1), perror imprime o erro
		printf("Error 2d: %d\n", errno);
        ft_handler_error("cd");
        return 1;
    }

    // 4. Pega o diretório atual DEPOIS da mudança para confirmar
    if (getcwd(buffer_depois, sizeof(buffer_depois)) != NULL) {
        printf("Diretório atual (depois): %s\n", buffer_depois);
		printf("Error 3: %d\n", errno);
    } else {
		printf("Error 3d: %d\n", errno);
         ft_handler_error("cd");
    }

    return 0;
}