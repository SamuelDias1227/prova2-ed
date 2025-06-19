#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAM_NOME_SENSOR 50
#define TAM_NOME_TIPO_DADO 8 //CONJ_Z, CONJ_Q, TEXTO, BINARIO

time_t gerar_timestamp_aleatorio(int dia, int mes, int ano, int hora, int min, int seg, int dia_final, int mes_final, int ano_final, int hora_final, int min_final, int seg_final);
void gerarArquivo(int argc, char *argv[]);
int obterValorInteiroAleatorio();
float obterValorRealAleatorio();
char* obterValorLiteralAleatorio();
char* obterValorLogicoAleatorio();

int main(int argc, char *argv[])
{

    if (argc < 15) {

        printf(
            "Ao aplicar o comando de execução deste programa, você deve juntamente informar os seguintes parâmetros:\n\n"
            "  - Data e Hora Inicial\n"
            "  - Data e Hora Final\n"
            "  - Nome do Sensor\n"
            "  - Tipo do Dado da Medição do Sensor\n\n"
            "OBSERVAÇÕES:\n"
            "  - O formato da Data e Hora deve ser: (dd mm aaaa hh mm ss)\n"
            "  - Tipos válidos de dados para o sensor:\n"
            "      - CONJ_Z   : Dados do tipo inteiro\n"
            "      - CONJ_Q   : Dados do tipo float\n"
            "      - TEXTO    : Dados do tipo string\n"
            "      - BINARIO  : Dados do tipo booleano\n"
            "IMPORTANTE!!\n"
            "  - Note que ao todo serão exigidos **ao menos 14 parâmetros**.\n"
            "  - Você pode incluir mais sensores adicionando outros 14 parâmetros para cada novo sensor.\n"
        );

        return 0;

    }

    gerarArquivo(argc, argv);

    return 0;
}

time_t gerar_timestamp_aleatorio(int dia, int mes, int ano, int hora, int min, int seg, int dia_final, int mes_final, int ano_final, int hora_final, int min_final, int seg_final) {
    struct tm t1, t2;
    time_t timestamp_inicial, timestamp_final;

    t1.tm_year = ano - 1900;
    t1.tm_mon = mes - 1;
    t1.tm_mday = dia;
    t1.tm_hour = hora;
    t1.tm_min = min;
    t1.tm_sec = seg;
    t1.tm_isdst = -1;

    
    timestamp_inicial = mktime(&t1);
    if (timestamp_inicial == -1) {
        printf("Data inválida.\n");
        return -1;
    }

    t2.tm_year = ano_final - 1900;
    t2.tm_mon = mes_final - 1;
    t2.tm_mday = dia_final;
    t2.tm_hour = hora_final;
    t2.tm_min = min_final;
    t2.tm_sec = seg_final;
    t2.tm_isdst = -1;
    
    timestamp_final = mktime(&t2);
    if (timestamp_final == -1) {
        printf("Data inválida.\n");
        return -1;
    }

    time_t timestamp_aleatorio = timestamp_inicial + rand() % (timestamp_final - timestamp_inicial + 1);
    
    return timestamp_aleatorio;
}

void gerarArquivo(int argc, char *argv[]){

    int dia_inicio, mes_inicio, ano_inicio, hora_inicio, min_inicio, seg_inicio;
    int dia_final, mes_final, ano_final, hora_final, min_final, seg_final;
    char id_sensor[TAM_NOME_SENSOR];
    char tipo_dado_medicao[TAM_NOME_TIPO_DADO];
    char *finalConversao;
    
    FILE *file = fopen("dados_gerados.txt", "w");

    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    fprintf(file, "<TIMESTAMP><ID_SENSOR><VALOR>\n");

    for (int i = 1; i+13 < argc; i = i + 14)
    {
        dia_inicio = strtol(argv[i], &finalConversao, 10);
        if (*finalConversao != '\0') {
            // parou antes de terminar de converter a string para inteiro, ou seja, nao tinha apenas numeros
            printf("Erro: Dia inicial inválido.\n");
            break;
        } else {
            mes_inicio = strtol(argv[i+1], &finalConversao, 10);
            if (*finalConversao != '\0') {
                // parou antes de terminar de converter a string para inteiro, ou seja, nao tinha apenas numeros
                printf("Erro: Mês inicial inválido.\n");
                break;
            } else {
                ano_inicio = strtol(argv[i+2], &finalConversao, 10);
                if (*finalConversao != '\0') {
                    // parou antes de terminar de converter a string para inteiro, ou seja, nao tinha apenas numeros
                    printf("Erro: Ano inicial inválido.\n");
                    break;
                } else {
                    hora_inicio = strtol(argv[i+3], &finalConversao, 10);
                    if (*finalConversao != '\0') {
                        // parou antes de terminar de converter a string para inteiro, ou seja, nao tinha apenas numeros
                        printf("Erro: Hora inicial inválida.\n");
                        break;
                    } else {
                        min_inicio = strtol(argv[i+4], &finalConversao, 10);
                        if (*finalConversao != '\0') {
                            // parou antes de terminar de converter a string para inteiro, ou seja, nao tinha apenas numeros
                            printf("Erro: Minuto inicial inválido.\n");
                            break;
                        } else {
                            seg_inicio = strtol(argv[i+5], &finalConversao, 10);
                            if (*finalConversao != '\0') {
                                // parou antes de terminar de converter a string para inteiro, ou seja, nao tinha apenas numeros
                                printf("Erro: Segundo inicial inválido.\n");
                                break;
                            } else {
                                dia_final = strtol(argv[i+6], &finalConversao, 10);
                                if (*finalConversao != '\0') {
                                    // parou antes de terminar de converter a string para inteiro, ou seja, nao tinha apenas numeros
                                    printf("Erro: Dia final inválido.\n");
                                    break;
                                } else {
                                    mes_final = strtol(argv[i+7], &finalConversao, 10);
                                    if (*finalConversao != '\0') {
                                        // parou antes de terminar de converter a string para inteiro, ou seja, nao tinha apenas numeros
                                        printf("Erro: Mês final inválido.\n");
                                        break;
                                    } else {
                                        ano_final = strtol(argv[i+8], &finalConversao, 10);
                                        if (*finalConversao != '\0') {
                                            // parou antes de terminar de converter a string para inteiro, ou seja, nao tinha apenas numeros
                                            printf("Erro: Ano final inválido.\n");
                                            break;
                                        } else {
                                            hora_final = strtol(argv[i+9], &finalConversao, 10);
                                            if (*finalConversao != '\0') {
                                                // parou antes de terminar de converter a string para inteiro, ou seja, nao tinha apenas numeros
                                                printf("Erro: Hora final inválida.\n");
                                                break;
                                            } else {
                                                min_final = strtol(argv[i+10], &finalConversao, 10);
                                                if (*finalConversao != '\0') {
                                                    // parou antes de terminar de converter a string para inteiro, ou seja, nao tinha apenas numeros
                                                    printf("Erro: Minuto final inválido.\n");
                                                    break;
                                                } else {
                                                    seg_final = strtol(argv[i+11], &finalConversao, 10);
                                                    if (*finalConversao != '\0') {
                                                        // parou antes de terminar de converter a string para inteiro, ou seja, nao tinha apenas numeros
                                                        printf("Erro: Segundo final inválido.\n");
                                                        break;
                                                    } else {
                                                        snprintf(id_sensor, TAM_NOME_SENSOR, "%s", argv[i+12]);
                                                        snprintf(tipo_dado_medicao, TAM_NOME_TIPO_DADO, "%s", argv[i+13]);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        for (int p = 0; p < 200; p++)
        {
            //time_t timestamp_inicial = converter_para_timestap(dia_inicio, mes_inicio, ano_inicio, hora_inicio, min_inicio, seg_inicio);
            //time_t timestamp_final = converter_para_timestap(dia_final, mes_final, ano_final, hora_final, min_final, seg_final);
    
            if (strcmp(tipo_dado_medicao, "CONJ_Z") == 0)
            {
                fprintf(file, "%ld,%s,%d\n", gerar_timestamp_aleatorio(dia_inicio, mes_inicio, ano_inicio, hora_inicio, min_inicio, seg_inicio, dia_final, mes_final, ano_final, hora_final, min_final, seg_final), id_sensor, obterValorInteiroAleatorio());
            } else if (strcmp(tipo_dado_medicao, "CONJ_Q") == 0)
            {
                fprintf(file, "%ld,%s,%.2f\n", gerar_timestamp_aleatorio(dia_inicio, mes_inicio, ano_inicio, hora_inicio, min_inicio, seg_inicio, dia_final, mes_final, ano_final, hora_final, min_final, seg_final), id_sensor, obterValorRealAleatorio());
            } else if (strcmp(tipo_dado_medicao, "TEXTO") == 0)
            {
                fprintf(file, "%ld,%s,%s\n", gerar_timestamp_aleatorio(dia_inicio, mes_inicio, ano_inicio, hora_inicio, min_inicio, seg_inicio, dia_final, mes_final, ano_final, hora_final, min_final, seg_final), id_sensor, obterValorLiteralAleatorio());
            } else if (strcmp(tipo_dado_medicao, "BINARIO") == 0)
            {
                fprintf(file, "%ld,%s,%s\n", gerar_timestamp_aleatorio(dia_inicio, mes_inicio, ano_inicio, hora_inicio, min_inicio, seg_inicio, dia_final, mes_final, ano_final, hora_final, min_final, seg_final), id_sensor, obterValorLogicoAleatorio());
            } else
            {
                printf("Erro: Tipo de dados informado para o sensor é inválido\n");
                break;
            }
        }
    }
}

int obterValorInteiroAleatorio() {
    return rand() % 1000; // Inteiro entre 0 e 999
}

float obterValorRealAleatorio() {
    return ((float) rand() / (float)(RAND_MAX)) * 1000.0f; // Float entre 0.0 e 1000.0
}

char* obterValorLiteralAleatorio() {
    static char opcoes[5][7] = {"ALTA", "FIRME", "MEDIA", "FRACA", "BAIXA"};
    int indice = rand() % 5;
    return opcoes[indice];
}

char* obterValorLogicoAleatorio() {
    static char opcoes[2][7] = {"false", "true"};
    int indice = rand() % 2;
    return opcoes[indice];
}