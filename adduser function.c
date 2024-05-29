#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cadastro {
    char nome[100];
    int idade;
    int id;
    float saldo;
};

int menu() {
    int opc;
    do {
        printf("\nMenu:\n");
        printf("1. Adicionar um usuario\n");
        printf("2. Adicionar varios usuarios\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opc) != 1) {
            while (getchar() != '\n'); // Clear invalid input
            opc = -1; // Invalid option
        }
        getchar(); // Clear newline character
    } while (opc < 0 || opc > 2);
    return opc;
}

int adduser(int qtdusuarios, struct cadastro **cadastro) {
    *cadastro = realloc(*cadastro, (qtdusuarios + 1) * sizeof(struct cadastro));
    if (*cadastro == NULL) {
        printf("Erro de alocacao de memoria.\n");
        exit(1);
    }

    while (1) {
        printf("\nDefina o nome do usuario (max 100 caracteres): ");
        fgets((*cadastro)[qtdusuarios].nome, sizeof((*cadastro)[qtdusuarios].nome), stdin);


        if ((*cadastro)[qtdusuarios].nome[strlen((*cadastro)[qtdusuarios].nome) - 1] != '\n') {
            printf("Erro: o nome excede 100 caracteres. Tente novamente.\n");
            while (getchar() != '\n');
        } else {
            (*cadastro)[qtdusuarios].nome[strcspn((*cadastro)[qtdusuarios].nome, "\n")] = '\0';
            break;
        }
    }

    printf("Insira a idade do usuario: ");
    while (scanf("%d", &(*cadastro)[qtdusuarios].idade) != 1 || (*cadastro)[qtdusuarios].idade < 0) {
        while (getchar() != '\n');
        printf("Idade invalida. Tente novamente: ");
    }

    printf("Insira o saldo do usuario: ");
    while (scanf("%f", &(*cadastro)[qtdusuarios].saldo) != 1 || (*cadastro)[qtdusuarios].saldo < 0) {
        while (getchar() != '\n');
        printf("Saldo invalido. Tente novamente: ");
    }
    getchar();

    (*cadastro)[qtdusuarios].id = qtdusuarios + 1;

    FILE *cadFile = fopen("Cadastro.txt", "a");
    if (cadFile == NULL) {
        printf("Arquivo nao pode ser aberto!\n");
        getchar();
        exit(0);
    }

    fprintf(cadFile, "Nome: %s ID: %d Idade: %d Saldo: %.2f\n",
            (*cadastro)[qtdusuarios].nome,
            (*cadastro)[qtdusuarios].id,
            (*cadastro)[qtdusuarios].idade,
            (*cadastro)[qtdusuarios].saldo);
    fclose(cadFile);

    printf("Dados do usuario:\n -Nome: %s\n -ID: %d\n -Idade: %d\n -Saldo: %.2f\n",
           (*cadastro)[qtdusuarios].nome,
           (*cadastro)[qtdusuarios].id,
           (*cadastro)[qtdusuarios].idade,
           (*cadastro)[qtdusuarios].saldo);

    return qtdusuarios + 1;
}

int addvuser(int qtdusuarios, struct cadastro **cadastro) {
    int qtd;
    printf("\nDefina quantos usuarios deseja adicionar: ");
    while (scanf("%d", &qtd) != 1 || qtd <= 0) {
        while (getchar() != '\n');
        printf("Quantidade invalida. Tente novamente: ");
    }
    getchar();
    for (int i = 0; i < qtd; i++) {
        qtdusuarios = adduser(qtdusuarios, cadastro);
    }

    return qtdusuarios;
}

int main() {
    int qtdusuarios = 0;
    struct cadastro *usuarios = NULL;
    int opc;
    int continuar = 1;

    do {
        opc = menu();
        switch (opc) {
            case 1:
                qtdusuarios = adduser(qtdusuarios, &usuarios);
                break;
            case 2:
                qtdusuarios = addvuser(qtdusuarios, &usuarios);
                break;
            case 0:
                continuar = 0;
                break;
        }
    } while (continuar == 1);

    free(usuarios);
    return 0;
}
