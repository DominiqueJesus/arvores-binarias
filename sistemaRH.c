#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// Criação da função input() para recebimento de dados do usuário
int input(char prompt[], char vetor[], int tam) {
    fputs(prompt, stdout); // prompt não pode ter %. 
    setbuf(stdin, NULL); // Livra-se de teclas antigas
    if (fgets(vetor, tam, stdin)) { 
        int i=0;
        for( i=0; vetor[i] != '\n' && vetor[i]; ++i)
            ;
        vetor[i] = '\0'; // Sobrescreve o \n
        return i;
    } else
        return -1;
}

// Criação da estrutura referente à ABB
typedef struct T_no T_no;

struct T_no {
    int CPF;
    char Nome[50];
    T_no *esq, *dir;
};

T_no *arvoreCPF;

// Função que imprime um texto guia adequado de acordo com a opção escolhida e ps dados fornecidos pelo usuário
int validaCPF(int cpf, char opcao[]) {
     if (opcao[0] == 'i') {
        printf("\nPor favor, informe o nome completo e o CPF do funcionário (separe com ; ): \n");
    } else {
        printf("\nPor favor, informe o CPF do funcionário");
    }

    return 0;
}



T_no *inserirFunc(char nome[], int cpf) {
    T_no *funcionario;
    funcionario = 0;

    if(funcionario) {
        printf("ERRO: alocação de memória em ponteiro não nulo!");
    } else {
        funcionario = (T_no *)malloc(sizeof(T_no));
        if(!funcionario) {
            printf("ERRO: Malloc falhou!");
            exit(1);
        }
    }

    funcionario->CPF = cpf;
    strcpy(funcionario->Nome, nome);
    funcionario->esq = funcionario->dir = NULL;

}

int removerFunc() {
    
}

int buscarFunc() {
    
}

int listarFunc() {
    
}

int sair() {
    
}

#define TAM 5

int main () {
    setlocale(LC_ALL,".UTF8");
    char opcao[TAM];
    int cpf;
    char nome[50];

    do{

    system("cls");

    printf("\n--- SISTEMA DE GERENCIAMENTO DE RECURSOS HUMANOS ---\n");

    printf("\nSelecione a ação desejada no menu abaixo: \n");

    printf("\ni - Inserir funcionários\n");
    printf("r - Remover funcionários\n");
    printf("b - Buscar funcionários\n");
    printf("l - Listar funcionários\n");
    printf("s - Sair\n");

    input("\n", opcao, TAM);

        if (opcao[0] == 'i') {
            input("Por favor, informe o nome do funcionário: ", nome, 50);
            printf("Por favor, informe o CPF do funcionário (somente os números): ");
            scanf("%d", &cpf);
            inserirFunc(nome, cpf);
            printf("Funcionário registrado com sucesso!");
        } 
        else if (opcao[0] == 'r') {
            printf("Removendo funcionário...");
        }
        else if (opcao[0] == 'b') {
            printf("Buscando funcionário...");
        }
        else if (opcao[0] == 'l') {
            printf("Listando funcionários...");
        }
        else if (opcao[0] == 's') {
            printf("Saindo...");
        }
        else {
            printf("Opção inválida! Por favor, tente novamente.");
        }

    } while(1);

}

// LEMBRETE: Liberar todos os endereços de memória alocados