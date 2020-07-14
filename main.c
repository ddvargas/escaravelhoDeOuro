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
void decifragem_monoalfabetica();
bool read_dicionario(FILE *file_dictionary, char alfabeto[], char dicionario[]);
int get_position(char vetor[], char c);

int main(){
    setlocale(LC_ALL, "");
    int opcao_menu_inicial;
    int sub_opcao_menu;

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

                    switch (sub_opcao_menu) {
                        case 1:
                            if(cifragem_monoalfabetica() < 0) {
                                printf("Erro ao abrir arquivo. (Certifique-se de digitar apenas "
                                       "o nome e que seja um arquivo .txt)\n");
                            }
                            break;
                        case 2:
                            break;
                            decifragem_monoalfabetica();
                        case 0:
                            printf("Voltando\n");
                            break;
                        default:
                            printf("Opção indisponível\n");
                    }
                }while (sub_opcao_menu != 0);
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
 */
int cifragem_monoalfabetica(){
    //TODO: implementar o algoritmo de cifragem
    FILE *fdicionario;
    FILE *fcipher;
    FILE *fplaintext;
    char alfabeto[TAM_ALFABETO];
    char dicionario[TAM_ALFABETO];
    char buffer[TAM_BUFFER_READ_FILE];

    printf("Nome arquivo dicionario: ");
    scanf("%s", &buffer);
    fdicionario = fopen(strcat(buffer, ".txt"), "r");
    if (fdicionario == NULL){
        return -1;
    }

    printf("Nome arquivo plaintext: ");
    scanf("%s", &buffer);
    fplaintext = fopen(strcat(buffer, ".txt"), "r");
    if (fplaintext == NULL){
        return -1;
    }

    printf("Defina nome arquivo saida: ");
    scanf("%s", &buffer);
    fcipher = fopen(strcat(buffer, ".txt"), "w");
    if (fcipher == NULL){
        return -1;
    }

    read_dicionario(fdicionario, alfabeto, dicionario);

    while (!feof(fplaintext)){
        fgets(buffer, TAM_BUFFER_READ_FILE, fplaintext);
        int position;
        for (int i = 0; i < TAM_BUFFER_READ_FILE || !feof(fplaintext); i++) {
            if (buffer[i] != EOF && buffer[i] != '\0' && buffer[i] != '\n'){
                if (buffer[i] != ' '){
                    position = get_position(alfabeto, buffer[i]);
                    if (position >= 0){
                        putc(dicionario[position], fcipher);
                    }
                }
            } else{
                break;
            }
        }
    }
}

/**
 * Verifica a primira ocorrencia de um caractere dentro de um vetor
 * @param vetor a ser analisado
 * @param c caractere a ser encontrado
 * @return a posição do caractere dentro de vetor, se não for encontrado retorna -1
 */
int get_position(char vetor[], char c){
    for (int i = 0; i < TAM_ALFABETO; ++i) {
        if (c == vetor[i]) return i;
    }
    return -1;
}



bool read_dicionario(FILE *file_dictionary, char alfabeto[], char dicionario[]){
    if (file_dictionary != NULL){
        char buffer[TAM_BUFFER_READ_FILE];

        if (!feof(file_dictionary)){
            //leitura dos caracteres que compõem a linguagem natural
            fgets(buffer, TAM_BUFFER_READ_FILE, file_dictionary);
            if (buffer != NULL){
                for (int i=0, j=0; j < TAM_ALFABETO; i=i+2, j++){
                    alfabeto[j] = buffer[i];
                }
            }
            //leitura dos caracteres que correspondem a cifra
            fgets(buffer, TAM_BUFFER_READ_FILE, file_dictionary);
            if (buffer != NULL){
                for (int i=0, j=0; j < TAM_ALFABETO; i=i+2, j++){
                    dicionario[j] = buffer[i];
                }
            }
        }

    }
}

void decifragem_monoalfabetica(){
    //TODO: implementar algoritmo de decifragem monoalfabetica
}

void verificacao_plaitext(){
    //TODO: implementar o algoritmo do verificacao de plaintext
}

void verificacao_frequencia(){
    //TODO: implementar o algoritmo de vericação de frequencia
}