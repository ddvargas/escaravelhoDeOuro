//
// created by Daniel de Vargas 13/07/2020
//

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

#define TAM_BUFFER_READ_FILE 255
#define TAM_ALFABETO 52

void cifragem_monoalfabetica();
void decifragem_monoalfabetica();
bool read_dicionario(FILE *file_dictionary, char alfabeto[], char dicionario[]);

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
                            cifragem_monoalfabetica();
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

void cifragem_monoalfabetica(){
    //TODO: implementar o algoritmo de cifragem
    FILE *fdicionario = fopen("dicionario.txt","r");
    char alfabeto[52];
    char dicionario[52];

    read_dicionario(fdicionario, alfabeto, dicionario);
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