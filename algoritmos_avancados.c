#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- 1. Estrutura e Funções de Construção ---

// Definição da estrutura do nó da árvore (Sala)
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda; // Caminho para a esquerda
    struct Sala *direita;  // Caminho para a direita
} Sala;

// Função auxiliar para criar e inicializar uma nova sala/nó
Sala* criarSala(const char *nome) {
    Sala *nova_sala = (Sala*)malloc(sizeof(Sala));
    if (nova_sala == NULL) {
        perror("Erro ao alocar memoria para a sala");
        exit(EXIT_FAILURE);
    }
    // Copia o nome, garantindo o terminador de string
    strncpy(nova_sala->nome, nome, sizeof(nova_sala->nome) - 1);
    nova_sala->nome[sizeof(nova_sala->nome) - 1] = '\0';
    nova_sala->esquerda = NULL;
    nova_sala->direita = NULL;
    return nova_sala;
}

// Função para liberar a memória da árvore
void liberarArvore(Sala *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

// --- 2. Construção Estática da Árvore (Mapa da Mansão) ---

Sala* construirMapa() {
    // Nível 0 (Raiz)
    Sala *hallEntrada = criarSala("Hall de Entrada");

    // Nível 1
    hallEntrada->esquerda = criarSala("Sala de Jantar");
    hallEntrada->direita = criarSala("Biblioteca");

    // Nível 2
    hallEntrada->esquerda->esquerda = criarSala("Cozinha");
    hallEntrada->esquerda->direita = criarSala("Despensa");

    hallEntrada->direita->esquerda = criarSala("Escritorio");
    hallEntrada->direita->direita = criarSala("Jardim de Inverno"); // Folha

    // Nível 3
    hallEntrada->esquerda->esquerda->esquerda = criarSala("Patio Tras."); // Folha
    hallEntrada->esquerda->esquerda->direita = criarSala("Adega"); // Folha
    
    hallEntrada->direita->esquerda->esquerda = criarSala("Quarto Principal");

    // Nível 4
    hallEntrada->direita->esquerda->esquerda->esquerda = criarSala("Banheiro"); // Folha
    hallEntrada->direita->esquerda->esquerda->direita = criarSala("Closet"); // Folha

    return hallEntrada;
}

// --- 3. Função de Exploração Interativa ---

void explorarSalas(Sala *salaAtual) {
    char opcao;
    
    // Loop principal de navegação
    while (1) {
        // Exibir o nome da sala atual
        printf("\nVoce esta em: **%s**\n", salaAtual->nome);

        // Verifica se e um no-folha (fim do caminho)
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("\n--- FIM DO CAMINHO ---\n");
            printf("Voce alcancou um no-folha. Voltando ao menu principal.\n");
            return; // Encerra a exploracao
        }

        // Exibe opcoes de navegacao
        printf("Escolha o caminho (o: Esquerda | d: Direita | s: Sair):\n");
        
        printf("> ");
        if (scanf(" %c", &opcao) != 1) {
            // Limpa o buffer em caso de erro de leitura
            while(getchar() != '\n'); 
            continue;
        }

        switch (opcao) {
            case 'o': // Esquerda
            case 'O':
                if (salaAtual->esquerda != NULL) {
                    salaAtual = salaAtual->esquerda;
                } else {
                    printf("Nao ha caminho para a esquerda a partir desta sala.\n");
                }
                break;

            case 'd': // Direita
            case 'D':
                if (salaAtual->direita != NULL) {
                    salaAtual = salaAtual->direita;
                } else {
                    printf("Nao ha caminho para a direita a partir desta sala.\n");
                }
                break;

            case 's': // Sair
            case 'S':
                printf("Saindo da exploracao atual.\n");
                return;

            default:
                printf("Opcao invalida. Por favor, digite 'o', 'd' ou 's'.\n");
                break;
        }
        
        // Limpar o buffer de entrada apos a leitura (boa pratica)
        while(getchar() != '\n');
    }
}

// --- 4. Função Principal (main) ---

int main() {
    Sala *mapa = construirMapa();
    
    printf("--- Bem-vindo(a) a Mansao dos Codigos ---\n");
    printf("Voce inicia no Hall de Entrada. Tente encontrar os nos-folha!\n");
    
    // Inicia a exploracao
    explorarSalas(mapa);

    // Limpeza de memoria
    liberarArvore(mapa);
    printf("\nMemoria da mansao liberada. Programa encerrado.\n");

    return 0;
}