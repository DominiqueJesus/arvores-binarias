#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// ================= FUNÇÃO INPUT =================
int input(const char prompt[], char vetor[], int tam) {

    fputs(prompt, stdout);

    setbuf(stdin, NULL);

    if (fgets(vetor, tam, stdin)) {

        int i = 0;

        for(i = 0; vetor[i] != '\n' && vetor[i]; ++i);

        vetor[i] = '\0';

        return i;
    }

    return -1;
}

// ================= ESTRUTURA DA ÁRVORE =================
typedef struct T_no T_no;

struct T_no {

    long long int CPF;
    char Nome[50];

    T_no *esq;
    T_no *dir;
};

T_no *arvoreCPF = NULL;

// ================= FUNÇÃO PARA INSERIR FUNCIONÁRIO =================
T_no *inserirFunc(char nome[], long long int cpf, T_no *arvoreCPF) {

    T_no *funcionario;

    if(cpf > 99999999999LL) {
        printf("\nPor favor, insira um CPF válido.\n");
        return arvoreCPF;
    }

    // Árvore vazia
    if(arvoreCPF == NULL) {
    
        // Alocando memória para novo nó/funcionario da árvore
        funcionario = (T_no *) malloc(sizeof(T_no));
        if(funcionario == NULL) {
            printf("\nERRO AO ALOCAR MEMÓRIA!\n");
            exit(1);
        }

        funcionario->CPF = cpf;
        strcpy(funcionario->Nome, nome);
        funcionario->esq = NULL;
        funcionario->dir = NULL;

        printf("\nInseriu %s\n", nome);

        return funcionario;
    }

    // CPF duplicado
    if(arvoreCPF->CPF == cpf) {

        printf("\nERRO: CPF já cadastrado.\n");

        return arvoreCPF;
    }

    // Inserir em sub-árvore esquerda
    if(cpf < arvoreCPF->CPF) {
        arvoreCPF->esq = inserirFunc(nome, cpf, arvoreCPF->esq);
    }

    // Inserir em sub-árvore direita
    else {
        arvoreCPF->dir = inserirFunc(nome, cpf, arvoreCPF->dir);
    }

    return arvoreCPF;
}

// ================= FUNÇÃO PARA BUSCAR FUNCIONÁRIO =================
T_no *buscarFunc(long long int cpf, T_no *arvoreCPF) {

    if(arvoreCPF == NULL) {
        printf("\nCPF %lld não localizado\n", cpf);
        return NULL;
    }

    if(arvoreCPF->CPF == cpf) {
        printf("\nEncontrou: %s %lld\n",
               arvoreCPF->Nome,
               arvoreCPF->CPF);

        return arvoreCPF;
    }

    if(cpf < arvoreCPF->CPF) {

        return buscarFunc(cpf, arvoreCPF->esq);
    }

    else {

        return buscarFunc(cpf, arvoreCPF->dir);
    }
}

// ========== FUNÇÃO PARA ENCONTRAR O MENOR VALOR DA ÁRVORE ==========
T_no *menorValor(T_no *no) {
    T_no *atual = no;

    while(atual && atual->esq != NULL) {
        atual = atual->esq;
    }

    return atual;
}

// ================= FUNÇÃO PARA REMOVER FUNCIONÁRIO =================
T_no *removerFunc(long long int cpf, T_no *arvoreCPF) {

    if(arvoreCPF == NULL) {
        printf("\nCPF %lld não localizado\n", cpf);

        return NULL;
    }

    // Procura na esquerda
    if(cpf < arvoreCPF->CPF) {
        arvoreCPF->esq = removerFunc(cpf, arvoreCPF->esq);
    }

    // Procura na direita
    else if(cpf > arvoreCPF->CPF) {
        arvoreCPF->dir = removerFunc(cpf, arvoreCPF->dir);
    }

    // Encontrou o nó
    else {
        printf("\nRemoveu %s %lld\n",
               arvoreCPF->Nome,
               arvoreCPF->CPF);

        // Sem filhos
        if(arvoreCPF->esq == NULL &&
           arvoreCPF->dir == NULL) {

            free(arvoreCPF);

            return NULL;
        }

        // Apenas filho à direita
        else if(arvoreCPF->esq == NULL) {

            T_no *temp = arvoreCPF->dir;

            free(arvoreCPF);

            return temp;
        }

        // Apenas filho à esquerda
        else if(arvoreCPF->dir == NULL) {

            T_no *temp = arvoreCPF->esq;

            free(arvoreCPF);

            return temp;
        }

        // Dois filhos
        T_no *temp = menorValor(arvoreCPF->dir);

        arvoreCPF->CPF = temp->CPF;
        strcpy(arvoreCPF->Nome, temp->Nome);

        arvoreCPF->dir = removerFunc(temp->CPF, arvoreCPF->dir);
    }

    return arvoreCPF;
}

// ================= FUNÇÃO PARA LISTAR FUNCIONÁRIOS =================
void listarFunc(T_no *arvoreCPF) {
    if(arvoreCPF != NULL) {

        listarFunc(arvoreCPF->esq);

        printf("Nome: %s - CPF: %lld\n",
               arvoreCPF->Nome,
               arvoreCPF->CPF);

        listarFunc(arvoreCPF->dir);
    }
}

// =============== FUNÇÃO PARA LIBERAR MEMÓRIA (SAIR) ===============
void liberarMemoria(T_no *arvoreCPF) {

    if(arvoreCPF != NULL) {
        liberarMemoria(arvoreCPF->esq);

        liberarMemoria(arvoreCPF->dir);

        free(arvoreCPF);
    }
}

#define TAM 5

// ================= MENU PRINCIPAL DO SISTEMA DE RH =================
int main() {

    setlocale(LC_ALL, ".UTF8");

    char opcao[TAM];

    long long int cpf;

    char nome[50];

    do {

        system("cls");

        printf("\n--- SISTEMA DE GERENCIAMENTO DE RH ---\n");

        printf("\nSelecione uma opção:\n");

        printf("\ni - Inserir funcionário");
        printf("\nr - Remover funcionário");
        printf("\nb - Buscar funcionário");
        printf("\nl - Listar funcionários");
        printf("\ns - Sair");

        input("\n\nOpção selecionada: ", opcao, TAM);

        // ================== INSERIR ==================
        if(opcao[0] == 'i') {

            system("cls");

            printf("INSERIR FUNCIONÁRIO\n");

            input("\nNome: ", nome, 50);

            printf("CPF: ");
            scanf("%lld", &cpf);

            arvoreCPF = inserirFunc(nome, cpf, arvoreCPF);

            while(getchar() != '\n');

            printf("\nPressione ENTER para continuar...");
            getchar();
        }

        // ================== REMOVER ==================
        else if(opcao[0] == 'r') {

            system("cls");

            printf("REMOVER FUNCIONÁRIO\n");

            printf("\nCPF: ");
            scanf("%lld", &cpf);

            arvoreCPF = removerFunc(cpf, arvoreCPF);

            while(getchar() != '\n');

            printf("\nPressione ENTER para continuar...");
            getchar();
        }

        // =============== BUSCAR =================
        else if(opcao[0] == 'b') {

            system("cls");

            printf("BUSCAR FUNCIONÁRIO\n");

            printf("\nCPF: ");
            scanf("%lld", &cpf);

            buscarFunc(cpf, arvoreCPF);

            while(getchar() != '\n');

            printf("\nPressione ENTER para continuar...");
            getchar();
        }

        // ================= LISTAR =================
        else if(opcao[0] == 'l') {

            system("cls");

            printf("LISTA DE FUNCIONÁRIOS\n\n");

            listarFunc(arvoreCPF);

            printf("\nPressione ENTER para continuar...");
            getchar();
        }

        // ================= SAIR =================
        else if(opcao[0] == 's') {

            liberarMemoria(arvoreCPF);

            printf("\nPrograma encerrado.\n");

            break;
        }

        // ================= OPÇÃO INVÁLIDA =================
        else {

            printf("\nOpção inválida!\n");

            while(getchar() != '\n');

            printf("\nPressione ENTER para continuar...");
            getchar();
        }

    } while(1);

    return 0;
}
