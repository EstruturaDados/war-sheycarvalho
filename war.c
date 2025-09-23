// Inclusão das bibliotecas necessárias para entrada/saída e manipulação de strings.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define a struct para representar um Território.
// Define um tamanho para a string da missão.
#define QTD_TERRITORIO 5
#define QTD_MISSAO 100

// A struct armazena o nome do território, a cor do exército e a quantidade de tropas.
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    // Declaração do vetor de 5 structs do tipo Territorio para armazenar os dados.
    struct Territorio territorios[5];
    int i;

    // Função para simular a rolagem de um dado de 6 lados.
int rolar_dado() {
    return rand() % 6 + 1; // Gera um número aleatório entre 1 e 6.
}

   // --- PROTÓTIPOS DAS FUNÇÕES ---

// Funções de Utilitário
void limparBufferEntrada();
void liberarMemoria(struct Territorio* territorios, char* missao);

// Funções de Exibição
void exibirMenu();
void exibirMapa(const struct Territorio* paises, int totalpaises);
void exibirMissao(const char* missao);

// Funções de Lógica do Jogo
void atacar(struct Territorio* atacante, struct Territorio* defensor);
void atribuirMissao(char* destino, const char* missoes[], int totalMissoes);
int verificarMissao(const char* missao, struct Territorio* mapa, int totalTerritorios);

// --- FUNÇÃO PRINCIPAL ---

int main() {
    struct Territorio *paises = NULL; // Ponteiro para o vetor de territórios
    char* missaoJogador = NULL;      // Ponteiro para a string da missão do jogador
    int totalpaises = 0;
    int opcao;

    // Vetor de missões pré-definidas
    const char* missoes[] = {
        "Conquistar todos os territorios do mapa.",
        "Eliminar todos os territorios da cor 'Vermelha'.",
        "Conquistar a America do Sul, o Leste Europeu e a Asia.", // Lógica não implementada
        "Ter 10 tropas em pelo menos dois territorios.",        // Lógica não implementada
        "Dominar completamente dois continentes de sua escolha."  // Lógica não implementada
    };
    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    // Inicializa a semente do gerador de números aleatórios
    srand(time(NULL));

    // Aloca memória para os territórios e para a missão do jogador
    paises = (struct Territorio*) calloc(QTD_TERRITORIO, sizeof(struct Territorio));
    missaoJogador = (char*) malloc(QTD_MISSAO * sizeof(char));

    // Verifica se a alocação de memória falhou
    if (paises == NULL || missaoJogador == NULL) {
        printf("Erro ao alocar memoria! O programa sera encerrado.\n");
        liberarMemoria(paises, missaoJogador); // Libera o que foi alocado
        return 1;
    }

    // Atribui e exibe a missão do jogador no início do jogo
    atribuirMissao(missaoJogador, missoes, totalMissoes);
    exibirMissao(missaoJogador);

    // Loop principal do jogo
    do {
        exibirMenu();
        scanf("%d", &opcao);
        limparBufferEntrada();
        printf("\n");

        switch (opcao) {
            case 1: // Cadastrar Território
                printf("--- CADASTRO DE NOVO TERRITORIO --- \n\n");
                if (totalpaises < QTD_TERRITORIO) {
                    printf("DIGITE O NOME DO TERRITORIO: ");
                    fgets(paises[totalpaises].nome, 30, stdin);

                    printf("DIGITE A COR: ");
                    fgets(paises[totalpaises].cor, 10, stdin);

                    printf("DIGITE O NUMERO DE TROPAS: ");
                    scanf("%d", &paises[totalpaises].tropas);
                    limparBufferEntrada();

                    // CORREÇÃO: Remove o '\n' do final da string e adiciona o terminador '\0'
                    paises[totalpaises].nome[strcspn(paises[totalpaises].nome, "\n")] = '\0';
                    paises[totalpaises].cor[strcspn(paises[totalpaises].cor, "\n")] = '\0';

                    totalpaises++;
                    printf("\nTERRITORIO CADASTRADO COM SUCESSO!\n");
                } else {
                    printf("ATINGIU O LIMITE DE TERRITORIOS\n");
                }
                break;

            case 2: // Listar Territórios
                exibirMapa(paises, totalpaises);
                break;

            case 3: // Fase de Ataque
                printf("--- FASE DE ATAQUE --- \n\n");
                if (totalpaises < 2) {
                    printf("E necessario ter pelo menos 2 territorios cadastrados para atacar.\n");
                    break;
                }

                exibirMapa(paises, totalpaises);

                int indiceAtacante, indiceDefensor;
                printf("\nEscolha o territorio ATACANTE (pelo numero): ");
                scanf("%d", &indiceAtacante);
                printf("Escolha o territorio DEFENSOR (pelo numero): ");
                scanf("%d", &indiceDefensor);
                limparBufferEntrada();
                
                indiceAtacante--; 
                indiceDefensor--;

                if (indiceAtacante < 0 || indiceAtacante >= totalpaises ||
                    indiceDefensor < 0 || indiceDefensor >= totalpaises) {
                    printf("\nERRO: Escolha invalida. Pelo menos um dos territorios nao existe.\n");
                    break;
                }
                if (indiceAtacante == indiceDefensor) {
                    printf("\nERRO: O territorio nao pode atacar a si mesmo.\n");
                    break;
                }
                if (paises[indiceAtacante].tropas <= 1) {
                    printf("\nERRO: O territorio atacante precisa de mais de 1 tropa para atacar.\n");
                    break;
                }
                if (strcmp(paises[indiceAtacante].cor, paises[indiceDefensor].cor) == 0) {
                    printf("\nERRO: Nao e possivel atacar um territorio que ja e seu.\n");
                    break;
                }

                atacar(&paises[indiceAtacante], &paises[indiceDefensor]);

                printf("\n--- ESTADO ATUALIZADO DO MAPA ---\n");
                exibirMapa(paises, totalpaises);

                // Verifica se a missão foi cumprida após o ataque
                if (verificarMissao(missaoJogador, paises, totalpaises)) {
                    printf("\n***************************************************\n");
                    printf(" VITORIA! Voce cumpriu sua missao!\n");
                    printf(" Missao: %s\n", missaoJogador);
                    printf("***************************************************\n");
                    opcao = 0; // Encerra o jogo
                }
                break;

            case 0:
                printf("\nSAINDO DO SISTEMA...\n");
                break;

            default:
                printf("\nOPCAO INVALIDA! TENTE NOVAMENTE...\n");
                break;
        }

        if (opcao != 0) {
            printf("\nPRESSIONE ENTER PARA CONTINUAR...");
            getchar();
        }

    } while (opcao != 0);
    
    // Libera toda a memória alocada antes de sair
    liberarMemoria(paises, missaoJogador);
    return 0;
}


// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

/**
 * @brief Limpa o buffer de entrada do teclado (stdin).
 */
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Libera toda a memória alocada dinamicamente.
 * @param territorios Ponteiro para o vetor de territórios.
 * @param missao Ponteiro para a string da missão.
 */
void liberarMemoria(struct Territorio* territorios, char* missao) {
    printf("Liberando memoria alocada...\n");
    if (territorios != NULL) {
        free(territorios);
    }
    if (missao != NULL) {
        free(missao);
    }
}

/**
 * @brief Exibe o menu principal de opções do jogo.
 */
void exibirMenu() {
    printf("\n===========================================\n");
    printf("      WAR - Jogo de Estrategia\n");
    printf("===========================================\n");
    printf("1 - CADASTRAR NOVO TERRITORIO\n");
    printf("2 - LISTAR TODOS OS TERRITORIOS (MAPA)\n");
    printf("3 - FASE DE ATAQUE\n");
    printf("0 - SAIR\n");
    printf("===========================================\n");
    printf("ESCOLHA UMA OPCAO: ");
}

/**
 * @brief Exibe o estado atual de todos os territórios cadastrados.
 * @param paises Ponteiro para o vetor de territórios (passagem por referência).
 * @param totalpaises Total de territórios cadastrados (passagem por valor).
 */
void exibirMapa(const struct Territorio* paises, int totalpaises) {
    printf("--- MAPA ATUAL --- \n\n");
    if (totalpaises == 0) {
        printf("NENHUM TERRITORIO CADASTRADO\n");
    } else {
        for (int i = 0; i < totalpaises; i++) {
            printf("--------------------------------------\n");
            printf("%d - %s\n", i + 1, paises[i].nome);
            printf("    Cor: %s\n", paises[i].cor); // CORREÇÃO: Adicionado '\n'
            printf("    Tropas: %d\n", paises[i].tropas);
        }
        printf("--------------------------------------\n");
    }
}

/**
 * @brief Exibe a missão do jogador.
 * @param missao String contendo a missão (passagem por valor).
 */
void exibirMissao(const char* missao) {
    printf("\n===========================================\n");
    printf("SUA MISSAO ESTRATEGICA SECRETA:\n");
    printf(">> %s <<\n", missao);
    printf("===========================================\n");
    printf("Pressione ENTER para iniciar o jogo...");
    getchar();
}

/**
 * @brief Simula um ataque com dados entre dois territórios.
 * @param atacante Ponteiro para o território atacante.
 * @param defensor Ponteiro para o território defensor.
 */
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n--- BATALHA: %s vs %s ---\n", atacante->nome, defensor->nome);
    printf("DADOS: Atacante rolou %d | Defensor rolou %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\n>>> VITORIA DO ATACANTE! <<<\n");
        printf("O territorio %s foi conquistado por %s!\n", defensor->nome, atacante->nome);
        
        // REQUISITO: Transfere a cor e metade das tropas do atacante
        strcpy(defensor->cor, atacante->cor);
        int tropasMovidas = atacante->tropas / 2;
        if (tropasMovidas < 1) tropasMovidas = 1; // Garante que pelo menos 1 tropa se mova

        defensor->tropas = tropasMovidas;
        atacante->tropas -= tropasMovidas;

        // Garante que o atacante sempre fique com pelo menos 1 tropa
        if (atacante->tropas < 1) {
            atacante->tropas = 1;
        }

    } else {
        printf("\n>>> VITORIA DO DEFENSOR! <<<\n");
        printf("O ataque foi repelido!\n");

        // REQUISITO: O atacante perde uma tropa
        atacante->tropas--;
        printf("O atacante recuou e perdeu uma tropa.\n");
    }
}

/**
 * @brief Sorteia uma missão do vetor de missões e a copia para o destino.
 * @param destino Ponteiro para onde a missão sorteada será copiada.
 * @param missoes Vetor de strings com as missões disponíveis.
 * @param totalMissoes Número total de missões no vetor.
 */
void atribuirMissao(char* destino, const char* missoes[], int totalMissoes) {
    int indiceSorteado = rand() % totalMissoes;
    strcpy(destino, missoes[indiceSorteado]);
}

/**
 * @brief Verifica se a condição de vitória de uma missão foi atingida.
 * (Implementação simplificada para duas missões específicas).
 * @param missao A missão a ser verificada.
 * @param mapa O vetor de territórios.
 * @param totalTerritorios O número total de territórios.
 * @return 1 se a missão foi cumprida, 0 caso contrário.
 */
int verificarMissao(const char* missao, struct Territorio* mapa, int totalTerritorios) {
    // Lógica para a missão: "Conquistar todos os territorios do mapa."
    if (strcmp(missao, "Conquistar todos os territorios do mapa.") == 0) {
        if (totalTerritorios < 2) return 0; // Não pode vencer com menos de 2 territórios no mapa
        
        const char* primeiraCor = mapa[0].cor;
        for (int i = 1; i < totalTerritorios; i++) {
            if (strcmp(mapa[i].cor, primeiraCor) != 0) {
                return 0; // Encontrou uma cor diferente, missão não cumprida
            }
        }
        return 1; // Todas as cores são iguais, missão cumprida
    }
    
    
    // Lógica para a missão: "Eliminar todos os territorios da cor 'Vermelha'."
    if (strcmp(missao, "Eliminar todos os territorios da cor 'Vermelha'.") == 0) {
        for (int i = 0; i < totalTerritorios; i++) {
            if (strcmp(mapa[i].cor, "Vermelha") == 0) {
                return 0; // Encontrou um território vermelho, missão não cumprida
            }
        }
    }
}
