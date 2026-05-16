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

T_no *inserirFunc(char nome[], int cpf, T_no *arvoreCPF) {
    T_no *funcionario;
    funcionario = 0;

    if(!arvoreCPF) {
        // Alocação de memória para nó da arvore (malloc)
        funcionario = (T_no *)malloc(sizeof(T_no));
        if(!funcionario) {
            printf("\nERRO: Malloc falhou!\n");
            exit(1);
        }

        funcionario->CPF = cpf;
        strcpy(funcionario->Nome, nome);
        funcionario->esq = funcionario->dir = NULL;

        return funcionario;
    }

    if(arvoreCPF->CPF == cpf) {
        printf("\nERRO: O CPF informado já está cadastrado.\n");
        return arvoreCPF;
    }

    if(arvoreCPF->CPF > cpf) {
        arvoreCPF->esq = inserirFunc(nome, cpf, arvoreCPF->esq);
    } else {
        arvoreCPF->dir = inserirFunc(nome, cpf, arvoreCPF->dir);
    }

    return arvoreCPF;
}

T_no *buscarFunc(int cpf, T_no *arvoreCPF) {

    if(!arvoreCPF) {
        printf("\nCPF %d não foi localizado\n", cpf);
        return arvoreCPF;
    }
    
    if(arvoreCPF->CPF == cpf) {
        printf("\nEncontrou: %.50s %d\n", arvoreCPF->Nome, arvoreCPF->CPF);
        return arvoreCPF;
    }

    if(arvoreCPF->CPF > cpf) {
        return buscarFunc(cpf, arvoreCPF->esq);
    } 
    else {
        return buscarFunc(cpf, arvoreCPF->dir);
    }

}

int removerFunc(int cpf, T_no *arvoreCPF) {
    
}

int listarFunc() {
    
}

int sair() {
    // Lembrar de colocar free() para liberar memória de todos os ponteiros
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
            system("cls");
            printf("INSERIR FUNCIONÁRIO:\n");
            input("\nInsira o nome do funcionário: ", nome, 50);
            printf("\nInsira o CPF do funcionário (somente números): ");
            scanf("%d", &cpf);
            inserirFunc(nome, cpf, arvoreCPF);
            printf("\nFuncionário inserido com sucesso!\n");

            while (getchar() != '\n');
            printf("\nPressione ENTER para voltar...\n");
            getchar();
        } 
        else if (opcao[0] == 'r') {
            system("cls");
            printf("REMOVER FUNCIONÁRIO:\n");
            printf("\nInsira o CPF do funcionário (somente números): ");
            scanf("%d", &cpf);
            removerFunc(cpf, arvoreCPF);
            printf("\nFuncionário removido com sucesso!\n");
            
            while (getchar() != '\n');
            printf("\nPressione ENTER para voltar...\n");
            getchar();
        }
        else if (opcao[0] == 'b') {
            system("cls");
            printf("BUSCAR FUNCIONÁRIO:\n");
            printf("\nInsira o CPF do funcionário (somente números): ");
            scanf("%d", &cpf);
            buscarFunc(cpf, arvoreCPF);

            while (getchar() != '\n');
            printf("\nPressione ENTER para voltar...\n");
            getchar();
        }
        else if (opcao[0] == 'l') {
            printf("- LISTA DE FUNCIONÁRIOS -\n");
            listarFunc();

            while (getchar() != '\n');
            printf("\nPressione ENTER para voltar...\n");
            getchar();
        }
        else if (opcao[0] == 's') {
            printf("Saindo...");
            sair();
        }
        else {
            printf("Opção inválida! Por favor, tente novamente.");
        }

    } while(1);

}

// LEMBRETE: Liberar todos os endereços de memória alocados