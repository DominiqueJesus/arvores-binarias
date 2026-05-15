# arvores-binarias

Função de busca beta:

T_no *buscarFunc(int cpf, T_no *arvoreCPF) {
    T_no *funcEncontrado;
    funcEncontrado = 0;
    T_no *esquerda, *direita;
    esquerda = 0;
    direita = 0;

    if(!arvoreCPF) {
        printf("CPF %d não foi localizado");
        return arvoreCPF;
    }

    if(arvoreCPF->CPF == cpf) {
        printf("Encontrou: %.50s %d", arvoreCPF->Nome. arvoreCPF->CPF);
        return arvoreCPF;
    }

    esquerda = buscarFunc(cpf, arvoreCPF->esq);
    direita = buscarFunc(cpf, arvoreCPF->dir);

    if(esquerda) {
        return esquerda;
    } else {
        return direita;
    }

}
