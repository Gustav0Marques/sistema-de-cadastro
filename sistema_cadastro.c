#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define MAX 100

typedef struct {
    char nome[50];
    int telefone;
    char empresa[50];
    char email[50];
    int dia, mes;
    int cpf;
    char endereco[100];
} Cliente;

Cliente clientes[MAX];
int totalClientes = 0;

/*
* Função: limparBuffer
* Descrição: Remove caracteres restantes do buffer após o uso de scanf.
* Parâmetros: Nenhum.
* Retorna: Nada.
*/
void limparBuffer() { 
 while (getchar() != '\n'); 
}

/*
* Função: clienteExiste
* Descrição: Verifica se já existe um cliente cadastrado com o email informado.
* Parâmetros:
*   email: string contendo o email a ser pesquisado.
* Retorna:
*   1 se o cliente existe, 0 caso contrário.
*/
int clienteExiste(char email[]) { 
int i; 
for (i = 0; i < totalClientes; i++) { 
  if (strcmp(clientes[i].email, email) == 0) { 
   return 1; 
  } 
 } 
	return 0; 
}

/*
* Função: addClientes
* Descrição: Realiza o cadastro de um novo cliente no sistema.
* Parâmetros: Nenhum.
* Retorna: Nada.
*/
void addClientes() {
    Cliente novo;
    
    if (totalClientes >= MAX) {
        printf("Limite maximo de clientes atingido!\n");
        return;
    }

    do {
        printf("Nome: ");
        fgets(novo.nome, 50, stdin);
        novo.nome[strcspn(novo.nome, "\n")] = 0;
    } while (strlen(novo.nome) == 0);

    do {
        printf("Empresa: ");
        fgets(novo.empresa, 50, stdin);
        novo.empresa[strcspn(novo.empresa, "\n")] = 0;
    } while (strlen(novo.empresa) == 0);

    do {
        printf("Email: ");
        fgets(novo.email, 50, stdin);
        novo.email[strcspn(novo.email, "\n")] = 0;
        if (clienteExiste(novo.email)) {
            printf("?? Este email já está cadastrado!\n");
        }
    } while (strlen(novo.email) == 0 || clienteExiste(novo.email));

    do {
        printf("Telefone (apenas numeros): ");
        if (scanf("%d", &novo.telefone) != 1) {
            printf("Entrada invalida! Digite apenas numeros.\n");
            limparBuffer();
        } else break;
    } while (1);
    limparBuffer();

    do {
        printf("CPF (apenas numeros): ");
        if (scanf("%d", &novo.cpf) != 1) {
            printf(" Entrada invalida! Digite apenas numeros.\n");
            limparBuffer();
        } else break;
    } while (1);
    limparBuffer();

    do {
        printf("Endereco: ");
        fgets(novo.endereco, 100, stdin);
        novo.endereco[strcspn(novo.endereco, "\n")] = 0;
    } while (strlen(novo.endereco) == 0);

    do {
        printf("Dia de aniversario: ");
        if (scanf("%d", &novo.dia) != 1 || novo.dia <= 0 || novo.dia > 31) {
            printf("Dia invalido!\n");
            limparBuffer();
        } else break;
    } while (1);

    do {
        printf("Mes: ");
        if (scanf("%d", &novo.mes) != 1 || novo.mes <= 0 || novo.mes > 12) {
            printf("Mes invalido!\n");
            limparBuffer();
        } else break;
    } while (1);
    limparBuffer();

    clientes[totalClientes] = novo;
    totalClientes++;
    printf("Cliente cadastrado com sucesso!\n");
}

/*
* Função: atualizarCliente
* Descrição: Permite localizar e editar os dados de um cliente cadastrado.
* Parâmetros: Nenhum.
* Retorna: Nada.
*/
void atualizarCliente() {
    char nomeBusca[50];
    int indices[MAX];
    int totalEncontrados = 0;
    int escolhaCliente, escolhaCampo;
    int i;

    printf("Digite o nome (ou parte) do cliente: ");
    fgets(nomeBusca, 50, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    for (i = 0; i < totalClientes; i++) {
        if (strstr(clientes[i].nome, nomeBusca)) {
            indices[totalEncontrados++] = i;
        }
    }

    if (totalEncontrados == 0) {
        printf("Nenhum cliente encontrado!\n");
        return;
    }

    if (totalEncontrados == 1) {
        escolhaCliente = indices[0];
    } else {
        printf("\nForam encontrados %d clientes:\n", totalEncontrados);
        for (i = 0; i < totalEncontrados; i++) {
            int pos = indices[i];
            printf("[%d] %s | %d | %s\n", i + 1, clientes[pos].nome, clientes[pos].telefone, clientes[pos].empresa);
        }

        do {
            printf("Escolha: ");
            scanf("%d", &escolhaCliente);
            limparBuffer();
            if (escolhaCliente < 1 || escolhaCliente > totalEncontrados)
                printf("Opcao invalida! Tente novamente.\n");
        } while (escolhaCliente < 1 || escolhaCliente > totalEncontrados);

        escolhaCliente = indices[escolhaCliente - 1];
    }

    printf("\n--- O que deseja alterar? ---\n");
    printf("1 - Nome\n2 - Telefone\n3 - Empresa\n4 - Email\n5 - Aniversario\n6 - CPF\n7 - Endereco\n");
    printf("Escolha: ");
    scanf("%d", &escolhaCampo);
    limparBuffer();

    switch (escolhaCampo) {
        case 1:
            do {
                printf("Novo nome: ");
                fgets(clientes[escolhaCliente].nome, 50, stdin);
                clientes[escolhaCliente].nome[strcspn(clientes[escolhaCliente].nome, "\n")] = 0;
            } while (strlen(clientes[escolhaCliente].nome) == 0);
            break;

        case 2:
            do {
                printf("Novo telefone (apenas numeros): ");
                if (scanf("%d", &clientes[escolhaCliente].telefone) != 1) {
                    printf(" Entrada invalida! Digite apenas numeros.\n");
                    limparBuffer();
                } else break;
            } while (1);
            limparBuffer();
            break;

        case 3:
            do {
                printf("Nova empresa: ");
                fgets(clientes[escolhaCliente].empresa, 50, stdin);
                clientes[escolhaCliente].empresa[strcspn(clientes[escolhaCliente].empresa, "\n")] = 0;
            } while (strlen(clientes[escolhaCliente].empresa) == 0);
            break;

        case 4:
            do {
                printf("Novo email: ");
                fgets(clientes[escolhaCliente].email, 50, stdin);
                clientes[escolhaCliente].email[strcspn(clientes[escolhaCliente].email, "\n")] = 0;
            } while (strlen(clientes[escolhaCliente].email) == 0);
            break;

        case 5:
            do {
                printf("Novo dia de aniversario: ");
                if (scanf("%d", &clientes[escolhaCliente].dia) != 1 || clientes[escolhaCliente].dia < 1 || clientes[escolhaCliente].dia > 31) {
                    printf(" Dia invalido!\n");
                    limparBuffer();
                } else break;
            } while (1);

            do {
                printf("Novo mes: ");
                if (scanf("%d", &clientes[escolhaCliente].mes) != 1 || clientes[escolhaCliente].mes < 1 || clientes[escolhaCliente].mes > 12) {
                    printf("Mes invalido!\n");
                    limparBuffer();
                } else break;
            } while (1);
            limparBuffer();
            break;

        case 6:
            do {
                printf("Novo CPF (apenas numeros): ");
                if (scanf("%d", &clientes[escolhaCliente].cpf) != 1) {
                    printf("Entrada invalida! Digite apenas numeros.\n");
                    limparBuffer();
                } else break;
            } while (1);
            limparBuffer();
            break;

        case 7:
            do {
                printf("Novo endereco: ");
                fgets(clientes[escolhaCliente].endereco, 100, stdin);
                clientes[escolhaCliente].endereco[strcspn(clientes[escolhaCliente].endereco, "\n")] = 0;
            } while (strlen(clientes[escolhaCliente].endereco) == 0);
            break;

        default:
            printf("Opcao invalida!\n");
            return;
    }

    printf("\nCliente atualizado com sucesso!\n");
}

/*
* Função: excluirCliente
* Descrição: Remove um cliente com base em seu email.
* Parâmetros: Nenhum.
* Retorna: Nada.
*/
void excluirCliente() {
    char email[50];
    int i, j;

    printf("Informe o email do cliente a ser excluido: ");
    fgets(email, 50, stdin);
    email[strcspn(email, "\n")] = 0;

    for (i = 0; i < totalClientes; i++) {
        if (strcmp(clientes[i].email, email) == 0) {
            for (j = i; j < totalClientes - 1; j++) {
                clientes[j] = clientes[j + 1];
            }
            totalClientes--;
            printf("Cliente excluido com sucesso!\n");
            return;
        }
    }
    printf("Cliente nao encontrado!\n");
}

/*
* Função: listarClientes
* Descrição: Exibe todos os clientes cadastrados na lista.
* Parâmetros: Nenhum.
* Retorna: Nada.
*/
void listarClientes() {
    int i;
    if (totalClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }
    for (i = 0; i < totalClientes; i++) {
        printf("%d - %s | %s | %s\n", i + 1, clientes[i].nome, clientes[i].email, clientes[i].empresa);
    }
}

/*
* Função: pesquisarPorEmpresa
* Descrição: Mostra clientes que trabalham em uma empresa específica.
* Parâmetros: Nenhum.
* Retorna: Nada.
*/
void pesquisarPorEmpresa() {
    char empresa[50];
    int i;
    int encontrado = 0;

    printf("Digite o nome da empresa: ");
    fgets(empresa, 50, stdin);
    empresa[strcspn(empresa, "\n")] = 0;

    for (i = 0; i < totalClientes; i++) {
        if (strcmp(clientes[i].empresa, empresa) == 0) {
            printf("%s - %s\n", clientes[i].nome, clientes[i].email);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Nenhum cliente encontrado para essa empresa.\n");
    }
}

/*
* Função: pesquisarPorNome
* Descrição: Busca clientes pelo nome ou parte dele.
* Parâmetros: Nenhum.
* Retorna: Nada.
*/
void pesquisarPorNome() {
    char nome[50];
    int i;

    printf("Digite o nome (ou parte dele): ");
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = 0;

    for (i = 0; i < totalClientes; i++) {
        if (strstr(clientes[i].nome, nome)) {
            printf("%s (%s)\n", clientes[i].nome, clientes[i].email);
        }
    }
}

/*
* Função: aniversariantesDoMes
* Descrição: Exibe todos os clientes que fazem aniversário no mês informado.
* Parâmetros: Nenhum.
* Retorna: Nada.
*/
void aniversariantesDoMes() {
    int mes, i;
    printf("Informe o mes: ");
    scanf("%d", &mes);
    limparBuffer();

    for (i = 0; i < totalClientes; i++) {
        if (clientes[i].mes == mes) {
            printf("%s faz aniversario dia %d/%d\n", clientes[i].nome, clientes[i].dia, clientes[i].mes);
        }
    }
}

/*
* Função: relatoriosEstatisticos
* Descrição: Mostra dados gerais da base de clientes.
* Número total de clientes;
* Número de clientes por empresa;
* Distribuição de aniversariantes por mes.
*/
void relatoriosEstatisticos() {
    printf("============ RELATORIOS ============\n");
    printf("Total de clientes cadastrados: %d\n", totalClientes);

    if (totalClientes == 0) return;

    // Relatório: Número de clientes por empresa
    printf("\n--- Clientes por Empresa ---\n");
    int i, j, contagemEmpresa;
    int empresaContada[MAX] = {0}; 

    for (i = 0; i < totalClientes; i++) {
        if (empresaContada[i]) continue;
        contagemEmpresa = 1;

        for (j = i + 1; j < totalClientes; j++) {
            if (strcmp(clientes[i].empresa, clientes[j].empresa) == 0) {
                contagemEmpresa++;
                empresaContada[j] = 1;
            }
        }
        printf("%s: %d cliente(s)\n", clientes[i].empresa, contagemEmpresa);
    }

    // Relatório: Distribuição de aniversariantes por mes
    printf("\n--- Distribuicao de Aniversariantes por Mes ---\n");
    int meses[13] = {0}; // índice 1 a 12

    for (i = 0; i < totalClientes; i++) {
        if (clientes[i].mes >= 1 && clientes[i].mes <= 12) {
            meses[clientes[i].mes]++;
        }
    }

    for (i = 1; i <= 12; i++) {
        printf("Mes %02d: %d cliente(s)\n", i, meses[i]);
    }

    printf("====================================\n");
}

/*
* Função: main
* Descrição: Exibe o menu principal e gerencia a execução do programa.
* Parâmetros: Nenhum.
* Retorna: 0 ao finalizar.
*/
int main() {
    int op;

    setlocale(LC_ALL, "");

    do {
        printf("\n===== SISTEMA DE CLIENTES =====\n");
        printf("1. Adicionar Cliente\n");
        printf("2. Atualizar Cliente\n");
        printf("3. Excluir Cliente\n");
        printf("4. Listar Clientes\n");
        printf("5. Pesquisar por Empresa\n");
        printf("6. Pesquisar por Nome\n");
        printf("7. Aniversariantes do Mes\n");
        printf("8. Relatorios Estatisticos\n");
        printf("0. Sair\n");
        printf("Escolha: ");

        if (scanf("%d", &op) != 1) {
            printf("Entrada invalida! Digite um numero.\n");
            limparBuffer();
            continue;
        }
        limparBuffer();

        switch (op) {
            case 1: addClientes(); break;
            case 2: atualizarCliente(); break;
            case 3: excluirCliente(); break;
            case 4: listarClientes(); break;
            case 5: pesquisarPorEmpresa(); break;
            case 6: pesquisarPorNome(); break;
            case 7: aniversariantesDoMes(); break;
            case 8: relatoriosEstatisticos(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (op != 0);

    return 0;
}