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

/**
 * Fluxo de execução para uma encriptação monoalfabetica,
 * solicitando aberturas de arquivos necessarios e fazendo a encriptação
 * @return Se foi possível ou não realizar a encriptação
 */
int cifragem_monoalfabetica();

/**
 * IMplementa a decifragem monoalfabetica de uma cifra
 * @param fdicionario Dicionário onde se encontram as regras de decifragem
 * @param fcipher Arquivo com a cifra a ser decifrada
 * @param fplaintext Arquivo onde será gravado a mensagem decifrada
 * @return 1 Se foi possível realizar a decifragem
 */
int decifragem_monoalfabetica(FILE *fdicionario, FILE *fcipher, FILE *fplaintext);

/**
 * Verifica se uma palavra existe dentro de uma matriz de palavras alocado dinamicamente.
 * @param palavras_encontradas Matriz
 * @param pal Palavra a ser encontrada
 * @return True caso seja encontrada, senão retorna false.
 */
bool existe_banco(char **palavras_encontradas, int tamanho, char *pal);

/**
 * Faz a leitura de um arquivo de dicionario para encriptação ou decriptação
 * @param file_dictionary arquivo a ser lido
 * @param alfabeto onde serão lidos os caracteres da lingua para o plaintext
 * @param dicionario onde serão lidos os caracteres usados para a encriptação
 * @return se a leitura foi completada ou não
 */
bool read_dicionario(FILE *file_dictionary, char alfabeto[], char dicionario[]);

/**
 * Verifica a primira ocorrencia de um caractere dentro de um vetor
 * @param vetor a ser analisado
 * @param c caractere a ser encontrado
 * @return a posição do caractere dentro de vetor, se não for encontrado retorna -1
 */
int get_position(char vetor[], char c);

/**
 * Implementa o fluxo necessário para fazer uma verificação de frequência.
 */
void fluxo_verificacao_frequencia();

/**
 * Implementa o fluxo de abertura de arquivos e tratamentos de erros para a decifragem de uma
 * cifra
 * @return 1 se o fluxo ocorreu bem
 */
int fluxo_opcao_decifragem();

/**
 * Calcula a frequencia de ocorrencia de cada caractere, todas as posições se baseiam em vet_caract e são
 * salvas de acordo.
 * @param vet_caract Vetor de caracteres lidos.
 * @param vet_ocor Vetor com o número de ocorrencia de cada caractere.
 * @param vet_freq Vetor onde serão salvas as frequencias.
 */
void calculo_frequencia(char *vet_caract, int *vet_ocor, float *vet_freq);

/**
 * Implementa o fluxo de verificação de plaintext.
 */
void fluxo_verificacao_plaitext();

int main() {
    setlocale(LC_ALL, "");
    short int opcao_menu_inicial;
    short int sub_opcao_menu;
    short int resultado;

    printf("\n ***** O Escaravelho de Ouro *****\n");

    do {
        printf("\n[1]-Cifragem e decifragem monoalfabetica\n[2]-Verificação de plaintext\n"
               "[3]-Tabela de frequência\n[0]-Sair\nSelecione: ");
        scanf("%hi", &opcao_menu_inicial);

        switch (opcao_menu_inicial) {
            case 1: //cifragem e decifragem
                do {
                    printf("\nCifragem e decifragem\n[1]-Cifrar mensagem\n[2]-Decifrar mensagem\n[0]-Voltar\nSelecione: ");
                    scanf("%hi", &sub_opcao_menu);
                    resultado;
                    switch (sub_opcao_menu) {
                        case 1:
                            resultado = (short int) cifragem_monoalfabetica();
                            if (resultado < 0) {
                                if (resultado == -1) {
                                    printf("Erro ao abrir arquivo. (Certifique-se de digitar apenas "
                                           "o nome e que seja um arquivo .txt)\n");
                                }
                                if (resultado == -2) {
                                    printf("Erro ao ler dicionario\n");
                                }
                            } else {
                                printf("Cifragem ok\n");
                            }
                            break;
                        case 2:
                            fluxo_opcao_decifragem();
                            break;
                        case 0:
                            printf("Voltando\n\n");
                            break;
                        default:
                            printf("Opção indisponível\n");
                    }
                } while (sub_opcao_menu != 0);
                break;
            case 2: //verificação de plaintext
                printf("\nVerificação de plaintext\n");
                fluxo_verificacao_plaitext();
                break;
            case 3: //tabela de frequencia
                printf("\nTabela de frequência\n");
                fluxo_verificacao_frequencia();
                break;
            case 0: //sair
                printf("Saindo\n");
                break;
            default:
                printf("Opção indisponível\n");
        }
    } while (opcao_menu_inicial != 0);
}

int cifragem_monoalfabetica() {
    FILE *fdicionario;
    FILE *fcipher;
    FILE *fplaintext;
    char alfabeto[TAM_ALFABETO];
    char dicionario[TAM_ALFABETO];
    char buffer[TAM_BUFFER_READ_FILE];

    printf("Nome tabela substuição: ");
    scanf("%s", buffer);
    fdicionario = fopen(strcat(buffer, ".txt"), "r");
    if (fdicionario == NULL) {
        return -1;
    }

    printf("Nome arquivo mensagem: ");
    scanf("%s", buffer);
    fplaintext = fopen(strcat(buffer, ".txt"), "r");
    if (fplaintext == NULL) {
        return -1;
    }

    printf("Defina o nome do arquivo de saída: ");
    scanf("%s", buffer);
    fcipher = fopen(strcat(buffer, ".txt"), "w");
    if (fcipher == NULL) {
        return -1;
    }


    if (!read_dicionario(fdicionario, alfabeto, dicionario)) {
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

int get_position(char vetor[], char c) {
    if (vetor == NULL || c == NULL){
        return -1;
    }
    for (int i = 0; i < strlen(vetor); i++) {
        if (c == vetor[i]) return i;
    }
    return -1;
}

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

int fluxo_opcao_decifragem() {
    int resultado;
    FILE *fdicionario, *fcipher, *fplaintext;
    char buffer[TAM_BUFFER_READ_FILE];

    //abrir os files
    printf("Nome da tabela de substituição: ");
    scanf("%s", buffer);
    fdicionario = fopen(strcat(buffer, ".txt"), "r");
    if (fdicionario == NULL) {
        return -1;
    }

    printf("Nome arquivo cifra: ");
    scanf("%s", buffer);
    fcipher = fopen(strcat(buffer, ".txt"), "r");
    if (fcipher == NULL) {
        return -1;
    }

    printf("Defina nome arquivo saida (plaintext): ");
    scanf("%s", buffer);
    fplaintext = fopen(strcat(buffer, ".txt"), "w");
    if (fplaintext == NULL) {
        return -1;
    }

    resultado = decifragem_monoalfabetica(fdicionario, fcipher, fplaintext);
    if (resultado < 0) {
        if (resultado == -1) {
            printf("Erro ao abrir arquivo. (Certifique-se de digitar apenas "
                   "o nome e que seja um arquivo .txt)\n");
        }
        if (resultado == -2) {
            printf("Erro ao ler dicionario\n");
        }
    } else {
        printf("Decifragem ok\n");
    }

    //fechar os files
    fclose(fcipher);
    fclose(fplaintext);
    fclose(fdicionario);
    return 1;
}

int decifragem_monoalfabetica(FILE *fdicionario, FILE *fcipher, FILE *fplaintext) {
    char alfabeto[TAM_ALFABETO];
    char dicionario[TAM_ALFABETO];
    char buffer[TAM_BUFFER_READ_FILE];

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

    return 1;
}

void fluxo_verificacao_plaitext() {
    FILE *fdicionario;
    FILE *ftabela;
    FILE *fcipher;
    FILE *fplaintext;
    int num_word_encontradas = 0;
    char nome_arq_table[100];
    char **palavras_encontradas = NULL;
    char nome_arq_plaintext[100];
    char nome_arq_dcio[100];
    char bufferd[TAM_BUFFER_READ_FILE];
    char bufferc[TAM_BUFFER_READ_FILE];
    short int op_repeticao;


    //abrir arquivo de tabela de substituição
    printf("Nome arquivo da tabela substituição: ");
    scanf("%s", nome_arq_table);
    ftabela = fopen(strcat(nome_arq_table, ".txt"), "r");
    if (ftabela == NULL) {
        printf("ERRO - Abrir arquivo de tabela de substituição\n");
        return;
    }
    //abrir arquivo de cifra
    printf("Nome arquivo cifrado: ");
    scanf("%s", nome_arq_plaintext);
    fcipher = fopen(strcat(nome_arq_plaintext, ".txt"), "r");
    if (fcipher == NULL) {
        printf("ERRO - Abertura do arquivo de cifra\n");
        return;
    }

    //salvar em um arquivo de plaintext
    printf("Nome do arquivo para salvar o plaintext: ");
    scanf("%s", nome_arq_plaintext);
    fplaintext = fopen(strcat(nome_arq_plaintext, ".txt"), "w+");
    if (fplaintext == NULL) {
        printf("ERRO - Abertura de arquivo para salvar o plaintext");
        return;
    }


    //fazer as substituições
    if (decifragem_monoalfabetica(ftabela, fcipher, fplaintext)) {
        printf("Decifragem ok\n");
    } else {
        printf("ERRO - Houve um problema na decifragem da mensagem\n");
    }

    //retorna o ponteiro para o início do arquivo para fazer a leitura
    rewind(fplaintext);

    do {
        //abrir um arquivo de dicionário de palavras
        printf("Nome do arquivo de dicionário: ");
        scanf("%s", nome_arq_dcio);
        fdicionario = fopen(strcat(nome_arq_dcio, ".txt"), "r");
        if (fdicionario != NULL) {
            while (fgets(bufferd, TAM_BUFFER_READ_FILE, fdicionario)) {
                bufferd[strlen(bufferd) - 1] = '\0'; //como o fgets está lendo o \n seto a ultima posição com o \0
                //para cada palavra no dicionario, buscar ela no texto decifrado (que pode ou não ser correto)
                while (fgets(bufferc, TAM_BUFFER_READ_FILE, fplaintext)) {
                    if (strstr(bufferc, bufferd)) {
                        if (!existe_banco(palavras_encontradas, num_word_encontradas, bufferd)) {
                            palavras_encontradas = (char **) realloc(palavras_encontradas,
                                                                     sizeof(char *) * ++num_word_encontradas);
                            palavras_encontradas[num_word_encontradas - 1] = (char *) malloc(
                                    sizeof(char) * (strlen(bufferd) + 1));
                            strcpy(palavras_encontradas[num_word_encontradas - 1], bufferd);
                        }
                    }
                }
                rewind(fplaintext);
            }
            if (num_word_encontradas != 0) {
                //printar o resultado
                printf("Palavras do arquivo %s encontradas no plaintext decifrado:\n", nome_arq_dcio);
                for (int i = 0; i < num_word_encontradas; ++i) {
                    printf("%s - ", palavras_encontradas[i]);
                }
            } else {
                printf("Nenhuma palavras do arquivo %s encontrada no plaintext decifrado\n", nome_arq_dcio);
            }
        } else {
            printf("Não foi possível encontrar o arquivo\n");
        }

        //desalocar vetor de palavras se houver
        if (palavras_encontradas != NULL) {
            for (int i = 0; i < num_word_encontradas; ++i) {
                free(palavras_encontradas[i]);
            }
            free(palavras_encontradas);
            num_word_encontradas = 0;
        }

        printf("\nDeseja verificar com mais um arquivo? 1-Sim 0-Não\nSelecione: ");
        scanf("%hi", &op_repeticao);
        //TODO: pq dá erro de segmentação ao abrir outro arquivo para verificação?
    } while (op_repeticao);

    fclose(fplaintext);
    fclose(fcipher);
    fclose(fdicionario);
    fclose(ftabela);
    //desalocar memória, se houver
}

bool existe_banco(char **palavras_encontradas, int tamanho, char *pal) {
    if (pal == NULL || palavras_encontradas == NULL) {
        return false;
    }

    for (int i = 0; i < tamanho; i++) {
        if (strstr(palavras_encontradas[i], pal)) {
            return true;
        }
    }
    return false;
}

void fluxo_verificacao_frequencia() {
    char buffer_read_file[TAM_BUFFER_READ_FILE];
    char file_name[TAM_BUFFER_READ_FILE];
    char *aux;
    int op_menu, tamanho_tables = 0, position;
    char *table_chars_freq = NULL;
    int *table_num_ocorrencias_char = NULL;
    float *table_frequ = NULL;
    FILE *ftabela_frequencia;
    FILE *ftabela_cifra;

    printf("Nome do arquivo da tabela de frequência existente ou que deseja criar:\n");
    scanf("%s", file_name);

    ftabela_frequencia = fopen(strcat(file_name, ".txt"), "a+");

    if (ftabela_frequencia == NULL) {
        printf("Erro ao abrir arquivo indicado.\n");
        return;
    }

//    rewind(ftabela_frequencia);

    //leitura da tabela de frequencia
    while (fgets(buffer_read_file, TAM_BUFFER_READ_FILE, ftabela_frequencia)) {
        if (buffer_read_file[0] != '\n') {
            table_chars_freq = realloc(table_chars_freq, sizeof(char *) * ++tamanho_tables);
            table_num_ocorrencias_char = realloc(table_num_ocorrencias_char, sizeof(int *) * tamanho_tables);
            table_frequ = realloc(table_frequ, sizeof(float *) * tamanho_tables);
            aux = strtok(buffer_read_file, "|");
            table_chars_freq[tamanho_tables - 1] = *aux;
            table_num_ocorrencias_char[tamanho_tables - 1] = atoi(strtok(NULL, "|"));
            table_frequ[tamanho_tables - 1] = (float) strtof(strtok(NULL, "|"), NULL);
        }
    }
    //fecha e reabre ele após a leitura para apagar tudo e escrever novamente ao fim da execução
    // ver se não dá problema
    // uma solução mais inteligente seria criar um arq temporário e oculto
    fclose(ftabela_frequencia);
    ftabela_frequencia = fopen(file_name, "w");
    do {
        printf("Selecione um arquivo de cifra para ser analisado: ");
        scanf("%s", buffer_read_file);

        ftabela_cifra = fopen(strcat(buffer_read_file, ".txt"), "r");

        if (ftabela_cifra == NULL) {
            printf("Erro ao abrir arquivo indicado\n");
            return;
        }

        while (!feof(ftabela_cifra)) {
            fgets(buffer_read_file, TAM_BUFFER_READ_FILE, ftabela_cifra);
            for (int i = 0; i < strlen(buffer_read_file); ++i) {
                if (buffer_read_file[i] != EOF && buffer_read_file[i] != '\n' && buffer_read_file[i] != '\0') {
                    position = get_position(table_chars_freq, buffer_read_file[i]);
                    if (position > -1) {
                        table_num_ocorrencias_char[position]++;
                    } else {
                        //TODO: caso a tabela exista, não ta pegando os valores existentes e somando
                        table_chars_freq = (char *) realloc(table_chars_freq, sizeof(char) * ++tamanho_tables);
                        table_num_ocorrencias_char = (int *) realloc(table_num_ocorrencias_char,
                                                                     sizeof(int) * tamanho_tables);
                        table_frequ = (float *) realloc(table_frequ, sizeof(float) * tamanho_tables);
                        table_chars_freq[tamanho_tables - 1] = buffer_read_file[i];
                        table_num_ocorrencias_char[tamanho_tables - 1] = 1;
                        table_frequ[tamanho_tables - 1] = 0.0;
                    }
                } else {
                    break;
                }
            }
        }
        fclose(ftabela_cifra);
        printf("Deseja analisar outra cifra com a mesma tabela? (1-Sim 0-Não) ");
        scanf("%d", &op_menu);
    } while (op_menu);
    //calcular a frequencia
    calculo_frequencia(table_chars_freq, table_num_ocorrencias_char, table_frequ);

    //salvar frequencias e num ocorrencias no arquivo ftabela_frequencia
    for (int j = 0; j < tamanho_tables; j++) {
        fprintf(ftabela_frequencia, "%c|%d|%f\n",
                table_chars_freq[j], table_num_ocorrencias_char[j], table_frequ[j]);
    }

    printf("Tabela de frequência ok\nVerifique o arquivo para ver o resultado.\n");

    //fechar arquivos
    fclose(ftabela_frequencia);
    //desalocar memorias
    free(table_frequ);
    free(table_num_ocorrencias_char);
    free(table_chars_freq);
}

void calculo_frequencia(char *vet_caract, int *vet_ocor, float *vet_freq) {
    if (vet_caract != NULL && vet_ocor != NULL && vet_freq != NULL) {
        int ocorrencia_total = 0;
        for (int i = 0; i < strlen(vet_caract); i++) {
            ocorrencia_total += vet_ocor[i];
        }
        for (int j = 0; j < strlen(vet_caract); j++) {
            vet_freq[j] = (float) vet_ocor[j] / ocorrencia_total;
        }
    }
}