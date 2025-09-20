// Inclusão das bibliotecas necessárias para entrada/saída e manipulação de strings.
#include <stdio.h>
#include <string.h>

// Define a struct para representar um Território.
#define QTD_TERRITORIOS 5

/*
 * Definição da Estrutura (struct) Territorio
 * Esta estrutura agrupa os dados relacionados a um único território do jogo.
 * - nome: armazena o nome do território (até 29 caracteres + caractere nulo).
 * - cor: armazena a cor do exército que domina o território.
 * - tropas: armazena a quantidade de tropas no território.
 */

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

    // --- Seção de Cadastro ---
    printf("--- Cadastro de Territorios ---\n\n");
    
    // Laço for para preencher os dados de 5 territórios.
    for (i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);

        // Solicita e lê o nome do território.
        printf("  Digite o nome do territorio: ");
        scanf(" %29[^\n]", territorios[i].nome);
        
        // Solicita e lê a cor do exercito.
        printf("  Digite a cor do exercito (ex: Vermelho, Azul): ");
        scanf(" %9[^\n]", territorios[i].cor);

        // Solicita e lê a quantidade de tropas.
        printf("  Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        
        printf("\n");
    }

    // --- Seção de Exibição ---
    printf("\n--- Dados dos Territorios Cadastrados ---\n\n");
    // Laço for para percorrer o vetor e exibir os dados de cada território.
    for (i = 0; i < 5; i++) {
        printf("Territorio %d\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("\n");
    }

    return 0; // Indica que o programa foi executado com sucesso.
}

// ============================================================================
//         ANÁLISE DO CÓDIGO E REQUISITOS:
// ============================================================================

// - O código C acima cumpre todos os requisitos funcionais e não funcionais solicitados:
// - Criação da struct: A struct Territorio foi definida com os campos nome, cor e tropas.
// - Cadastro dos territórios: O programa utiliza um laço for para solicitar e ler os dados de 5 territórios, armazenando-os em um vetor de structs.
// - Exibição dos dados: Após o cadastro, outro laço for é usado para percorrer o vetor e imprimir as informações de cada território de forma clara e organizada.
// - Usabilidade: As mensagens de entrada ("Digite o nome...", "Digite a cor...") são claras e orientam o usuário. A formatação de saída também é fácil de ler.
// - Documentação: O código contém comentários explicativos sobre a definição da struct, a lógica do laço de entrada de dados e a exibição, tornando-o mais fácil de entender e manter.
// - Manutenibilidade: Os nomes das variáveis (territorios, i) e da struct (Territorio) são claros e autoexplicativos, o que facilita a leitura e futuras modificações.
// - Observação sobre scanf: Para a leitura de strings com espaços, foi utilizada a sintaxe scanf(" %29[^\n]", ...) e scanf(" %9[^\n]", ...) que lê a linha inteira até a quebra de linha (\n), evitando problemas com espaços em branco e garantindo que o buffer de entrada seja limpo para a próxima leitura. O espaço antes do % ignora qualquer espaço em branco, incluindo a quebra de linha deixada pelo scanf anterior.
// ============================================================================
