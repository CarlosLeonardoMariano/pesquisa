#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100
#define MAX_NOTA 10

// Função para adicionar aluno ao arquivo "alunos.txt"
void adicionar_aluno(FILE *arquivo, const char *nome, const char *nota) {
    fprintf(arquivo, "%s,%s\n", nome, nota);
    printf("Aluno %s com nota %s adicionado.\n", nome, nota);
}

// Função para listar alunos presentes no arquivo "alunos.txt"
void listar_alunos(FILE *arquivo) {
    char linha[MAX_NOME + MAX_NOTA + 2]; // buffer para leitura das linhas do arquivo

    rewind(arquivo); // Garante que o ponteiro do arquivo seja movido para o início
    printf("Lista de Alunos e suas Notas:\n");

    while (fgets(linha, sizeof(linha), arquivo)) {
        char *nome = strtok(linha, ",");
        char *nota = strtok(NULL, "\n");
        printf("Nome: %s, Nota: %s\n", nome, nota);
    }
}

int main() {
    FILE *arquivo;
    int opcao;
    char nome[MAX_NOME], nota[MAX_NOTA];

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar Aluno\n");
        printf("2. Listar Alunos\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado

        // Abertura do arquivo em modo de leitura e escrita. Cria o arquivo caso não exista.
        arquivo = fopen("alunos.txt", "a+");
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo!\n");
            return 1;
        }

        switch (opcao) {
            case 1:
                // Adicionar aluno
                printf("Digite o nome do aluno: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = 0; // Remover o '\n' do final da string

                printf("Digite a nota do aluno: ");
                fgets(nota, MAX_NOTA, stdin);
                nota[strcspn(nota, "\n")] = 0; // Remover o '\n' do final da string

                adicionar_aluno(arquivo, nome, nota);
                break;

            case 2:
                // Listar alunos
                fclose(arquivo);  // Fechar o arquivo após adicionar um aluno e abrir em modo leitura
                arquivo = fopen("alunos.txt", "r");
                if (arquivo == NULL) {
                    printf("Erro ao abrir o arquivo para leitura!\n");
                    return 1;
                }
                listar_alunos(arquivo);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }

        fclose(arquivo); // Fechar o arquivo após a operação
    } while (opcao != 0);

    return 0;
}