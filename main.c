//
// created by Daniel de Vargas 13/07/2020
//

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

#define TAM_BUFFER_READ_FILE 255
#define TAM_ALFABETO 52

int cifragem_monoalfabetica();

int decifragem_monoalfabetica();

bool read_dicionario(FILE *file_dictionary, char alfabeto[], char dicionario[]);

int get_position(char vetor[], char c);

int main() {
    setlocale(LC_ALL, "");
    short int opcao_menu_inicial;
    short int sub_opcao_menu;
    short int resultado;

    printf(" ***** O Escaravelho do Diabo *****\n\n");

    do {
        printf("1-Cifragem e decifragem monoalfabetica  2-Verificação de plaintext\n"
               "3-Tabela de frequência\t\t0-Sair"
               "\nSelecione: ");
        scanf("%d", &opcao_menu_inicial);

        switch (opcao_menu_inicial) {
            case 1: //cifragem e decifragem
                do {
                    printf("1-Cifrar mensagem 2-Decifrar mensagem 0-Voltar\n");
                    scanf("%d", &sub_opcao_menu);
                    resultado = 0;
                    switch (sub_opcao_menu) {
                        case 1:
                            resultado = cifragem_monoalfabetica();
                            if (resultado < 0) {
                                if (resultado == -1) {
                                    printf("Erro ao abrir arquivo. (Certifique-se de digitar apenas "
                                           "o nome e que seja um arquivo .txt)\n");
                                }
                                if (resultado == -2){
                                    printf("Erro ao ler dicionario\n");
                                }
                            } else{
                                printf("Cifragem ok\n");
                            }
                            break;
                        case 2:
                            resultado = decifragem_monoalfabetica();
                            if (resultado < 0) {
                                if (resultado == -1) {
                                    printf("Erro ao abrir arquivo. (Certifique-se de digitar apenas "
                                           "o nome e que seja um arquivo .txt)\n");
                                }
                                if (resultado == -2){
                                    printf("Erro ao ler dicionario\n");
                                }
                            } else{
                                printf("Decifragem ok\n");
                            }
                            break;
                        case 0:
                            printf("Voltando\n");
                            break;
                        default:
                            printf("Opção indisponível\n");
                    }
                } while (sub_opcao_menu != 0);
                break;
            case 2: //verificação de plaintext

                break;
            case 3: //tabela de frequencia
                break;
            case 0: //sair
                printf("Bay");
                break;
            default:
                printf("Opção incorreta\n");
        }
    } while (opcao_menu_inicial != 0);
}

/**
 * Fluxo de execução para uma encriptação monoalfabetica,
 * solicitando aberturas de arquivos necessarios e fazendo a encriptação
 * @return Se foi possível ou não realizar a encriptação
 */
int cifragem_monoalfabetica() {
    FILE *fdicionario;
    FILE *fcipher;
    FILE *fplaintext;
    char alfabeto[TAM_ALFABETO];
    char dicionario[TAM_ALFABETO];
    char buffer[TAM_BUFFER_READ_FILE];

    printf("Nome arquivo dicionario: ");
    scanf("%s", &buffer);
    fdicionario = fopen(strcat(buffer, ".txt"), "r");
    if (fdicionario == NULL) {
        return -1;
    }

    printf("Nome arquivo mensagem: ");
    scanf("%s", &buffer);
    fplaintext = fopen(strcat(buffer, ".txt"), "r");
    if (fplaintext == NULL) {
        return -1;
    }

    printf("Defina o nome do arquivo de saída: ");
    scanf("%s", &buffer);
    fcipher = fopen(strcat(buffer, ".txt"), "w");
    if (fcipher == NULL) {
        return -1;
    }


    if (!read_dicionario(fdicionario, alfabeto, dicionario)){
        return -1;
    }

    while (!feof(fplaintext)) {
        fgets(buffer, TAM_BUFFER_READ_FILE, fplaintext);
        int position;
        for (int i = 0; i < TAM_BUFFER_READ_FILE || !feof(fplaintext); i++) {
            if (buffer[i] != EOF && buffer[i] != '\0' && buffer[i] != '\n') {
                if (buffer[i] != ' ') {
                    position = get_position(alfabeto, buffer[i]);
                    if (position >= 0) {
                        putc(dicionario[position], fcipher);
                    }
                }
            } else {
                break;
            }
        }
    }
    fclose(fcipher);
    fclose(fdicionario);
    fclose(fplaintext);
    return 0;
}

/**
 * Verifica a primira ocorrencia de um caractere dentro de um vetor
 * @param vetor a ser analisado
 * @param c caractere a ser encontrado
 * @return a posição do caractere dentro de vetor, se não for encontrado retorna -1
 */
int get_position(char vetor[], char c) {
    for (int i = 0; i < TAM_ALFABETO; ++i) {
        if (c == vetor[i]) return i;
    }
    return -1;
}

/**
 * Faz a leitura de um arquivo de dicionario para encriptação ou decriptação
 * @param file_dictionary arquivo a ser lido
 * @param alfabeto onde serão lidos os caracteres da lingua para o plaintext
 * @param dicionario onde serão lidos os caracteres usados para a encriptação
 * @return se a leitura foi completada ou não
 */
bool read_dicionario(FILE *file_dictionary, char alfabeto[], char dicionario[]) {
    if (file_dictionary != NULL) {
        char buffer[TAM_BUFFER_READ_FILE];

        if (!feof(file_dictionary)) {
            //leitura dos caracteres que compõem a linguagem natural
            fgets(buffer, TAM_BUFFER_READ_FILE, file_dictionary);
            if (buffer != NULL) {
                for (int i = 0, j = 0; j < TAM_ALFABETO; i = i + 2, j++) {
                    alfabeto[j] = buffer[i];
                }
            }
            //leitura dos caracteres que correspondem a cifra
            fgets(buffer, TAM_BUFFER_READ_FILE, file_dictionary);
            if (buffer != NULL) {
                for (int i = 0, j = 0; j < TAM_ALFABETO; i = i + 2, j++) {
                    dicionario[j] = buffer[i];
                }
            }
        }
        return true;
    }
    return false;
}

/**
 * luxo de execução para uma encriptação monoalfabetica,
 * solicitando aberturas de arquivos necessarios e fazendo a encriptação
 * @return Se foi possível ou não realizar a decriptação
 */
int decifragem_monoalfabetica() {
    FILE *fdicionario;
    FILE *fcipher;
    FILE *fplaintext;
    char alfabeto[TAM_ALFABETO];
    char dicionario[TAM_ALFABETO];
    char buffer[TAM_BUFFER_READ_FILE];

    printf("Nome arquivo dicionario: ");
    scanf("%s", &buffer);
    fdicionario = fopen(strcat(buffer, ".txt"), "r");
    if (fdicionario == NULL) {
        return -1;
    }

    printf("Nome arquivo cifra: ");
    scanf("%s", &buffer);
    fcipher = fopen(strcat(buffer, ".txt"), "r");
    if (fcipher == NULL) {
        return -1;
    }

    printf("Defina nome arquivo saida: ");
    scanf("%s", &buffer);
    fplaintext = fopen(strcat(buffer, ".txt"), "w");
    if (fplaintext == NULL) {
        return -1;
    }

    read_dicionario(fdicionario, alfabeto, dicionario);

    while (!feof(fcipher)) {
        fgets(buffer, TAM_BUFFER_READ_FILE, fcipher);
        int position;
        for (int i = 0; i < TAM_BUFFER_READ_FILE || !feof(fplaintext); i++) {
            if (buffer[i] != EOF && buffer[i] != '\0' && buffer[i] != '\n') {
                position = get_position(dicionario, buffer[i]);
                if (position >= 0) {
                    putc(alfabeto[position], fplaintext);
                }
            } else {
                break;
            }
        }
    }
    fclose(fcipher);
    fclose(fplaintext);
    fclose(fdicionario);
    return 0;
}

void verificacao_plaitext() {
    //TODO: implementar o algoritmo do verificacao de plaintext
}

void verificacao_frequencia() {
    //TODO: implementar o algoritmo de vericação de frequencia
}