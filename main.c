#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct carro {
    char tipo[50];
    char modelo[50];
    int ano;
    float preco;
    char chassi[50];
    int renavam;
};

struct listaTelefonica {
    char nome[50];
    char telefone[50];
    char endereco[50];
    char email[50];
};

//bubble sort para organizar em ordem alfabetica os nomes
void ordenarAlfabeticamente(struct listaTelefonica *lista, int n) {
    int i, j;
    struct listaTelefonica aux;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (strcmp(lista[i].nome, lista[j].nome) > 0) {
                aux = lista[i];
                lista[i] = lista[j];
                lista[j] = aux;
            }
        }
    }
}

struct data {
    int dia;
    int mes;
    int ano;
};

struct hora {
    int hora;
    int minuto;
    int segundo;
};

struct data_hora {
    struct data data;
    struct hora hora;
};

int compararDataHora(struct data_hora a, struct data_hora b) {
    if (a.data.ano != b.data.ano) return a.data.ano - b.data.ano;
    if (a.data.mes != b.data.mes) return a.data.mes - b.data.mes;
    if (a.data.dia != b.data.dia) return a.data.dia - b.data.dia;
    if (a.hora.hora != b.hora.hora) return a.hora.hora - b.hora.hora;
    if (a.hora.minuto != b.hora.minuto) return a.hora.minuto - b.hora.minuto;
    return a.hora.segundo - b.hora.segundo;
}

void ordenarDataHora(struct data_hora *data_hora, int n) {
    int i, j;
    struct data_hora temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (compararDataHora(data_hora[j], data_hora[j + 1]) > 0) {
                temp = data_hora[j];
                data_hora[j] = data_hora[j + 1];
                data_hora[j + 1] = temp;
            }
        }
    }
}


int main() {
    int n, i;
       
    printf("Quantos carros deseja criar? ");
    scanf("%d", &n);
    struct carro *carros = malloc(sizeof(struct carro) * n); //alocacao de memoria para o array de carros

    for (i = 0; i < n; i++) {
        printf("Digite o tipo do carro %d: ", i + 1);
        scanf("%s", carros[i].tipo);
        printf("Digite o modelo do carro %d: ", i + 1);
        scanf("%s", carros[i].modelo);
        printf("Digite o ano do carro %d: ", i + 1);
        scanf("%d", &carros[i].ano);
        printf("Digite o preco do carro %d: ", i + 1);
        scanf("%f", &carros[i].preco);
        printf("Digite o chassi do carro %d: ", i + 1);
        scanf("%s", carros[i].chassi);
        printf("Digite o renavam do carro %d: ", i + 1);
        scanf("%d", &carros[i].renavam);
    }

    
    for (i = 0; i < n; i++) {
        printf("Tipo: %s\n", carros[i].tipo);
        printf("Modelo: %s\n", carros[i].modelo);
        printf("Ano: %d\n", carros[i].ano);
        printf("Preco: %.2f\n", carros[i].preco);
        printf("Chassi: %s\n", carros[i].chassi);
        printf("Renavam: %d\n", carros[i].renavam);
        printf("\n");
    }
    free(carros); //liberação da memoria 

    
    printf("Quantos contatos deseja criar? ");
    scanf("%d", &n);

    struct listaTelefonica *lista = malloc(sizeof(struct listaTelefonica) * n);
    for (i = 0; i < n; i++) {
        printf("Digite o nome do contato %d: ", i + 1);
        scanf("%s", lista[i].nome);
        printf("Digite o telefone do contato %d: ", i + 1);
        scanf("%s", lista[i].telefone);
        printf("Digite o endereco do contato %d: ", i + 1);
        scanf("%s", lista[i].endereco);
        printf("Digite o email do contato %d: ", i + 1);
        scanf("%s", lista[i].email);
    }

    //chamada da funcao para ordenar os nomes em ordem alfabetica
    ordenarAlfabeticamente(lista, n);

    for (i = 0; i < n; i++) {
        printf("Nome: %s\n", lista[i].nome);
        printf("Telefone: %s\n", lista[i].telefone);
        printf("Endereco: %s\n", lista[i].endereco);
        printf("Email: %s\n", lista[i].email);
        printf("\n");
    }
    free(lista);   

    struct data data1;
    printf("Insira a data desejada para calcular a diferenca de tempo ate o dia de hoje: ");
    scanf("%d %d %d", &data1.dia, &data1.mes, &data1.ano);
    printf("Otimo, agora insira o horario desejado para calcular a diferenca de tempo ate o dia de hoje: ");
    struct hora hora1;
    scanf("%d %d %d", &hora1.hora, &hora1.minuto, &hora1.segundo);

    //pega o horario atual da minha maquina
    time_t horario_atual = time(NULL);
    struct tm *tm_horario = localtime(&horario_atual); //converte em um struct q contem data e hora

    //converte a data e hora inserida pelo usuario em um struct tm
    struct tm horario_data1 = {0};
    horario_data1.tm_year = data1.ano - 1900; //struct tm armazena contando os anos a partir de 1900, por isso tem que diminuir 1900
    horario_data1.tm_mon = data1.mes - 1; //struct tm conta meses de 0 a 11
    horario_data1.tm_mday = data1.dia;
    horario_data1.tm_hour = hora1.hora;
    horario_data1.tm_min = hora1.minuto;
    horario_data1.tm_sec = hora1.segundo;

    //converte o struct tm em um time_t
    time_t horario_usuario = mktime(&horario_data1);

    //funcao difftime para calcular a diferenca de tempo entre o horario atual e o horario inserido pelo usuario
    double diferenca = difftime(horario_atual, horario_usuario);

    //calculos para obter a diferenca de tempo em dias, horas, minutos e segundos
    int dias = diferenca / (60 * 60 * 24);
    int horas = ((int)diferenca % (60 * 60 * 24)) / (60 * 60);
    int minutos = ((int)diferenca % (60 * 60)) / 60;
    int segundos = (int)diferenca % 60;

    printf("Diferenca de tempo: %d dias, %d horas, %d minutos, %d segundos\n", dias, horas, minutos, segundos);


    printf("Insira uma quantidade de datas que voce deseja adicionar (max 10): \n");
    scanf("%d", &n);

    if(n > 10){
        printf("Numero de datas excede o limite de 10\n");
        return 0;
    }

    struct data_hora data_hora[n];
    for(i = 0; i < n; i++){
        printf("Insira a data desejada: ");
        scanf("%d %d %d", &data_hora[i].data.ano, &data_hora[i].data.mes, &data_hora[i].data.dia);
        
        printf("Otimo, agora insira o horario desejado: ");
        scanf("%d %d %d", &data_hora[i].hora.hora, &data_hora[i].hora.minuto, &data_hora[i].hora.segundo);
    }

    //ordenacao dos horarios
    ordenarDataHora(data_hora, n);

    //print dos horarios ordenados
    printf("Datas e horarios ordenados:\n");
    for (i = 0; i < n; i++) {
        printf("%02d/%02d/%04d %02d:%02d:%02d\n", data_hora[i].data.dia, data_hora[i].data.mes, data_hora[i].data.ano, data_hora[i].hora.hora, data_hora[i].hora.minuto, data_hora[i].hora.segundo);
    }

    //com alocacao dinamica

    printf("Insira uma quantidade de datas que voce deseja adicionar (max 10): \n");
    scanf("%d", &n);

    if(n > 10){
        printf("Numero de datas excede o limite de 10\n");
        return 0;
    }
    
  
    struct data_hora *data_hora = malloc(sizeof(struct data_hora) * n);
    
    for(i = 0; i < n; i++){
        printf("Insira a data desejada: ");
        scanf("%d %d %d", &data_hora[i].data.ano, &data_hora[i].data.mes, &data_hora[i].data.dia);
        
        printf("Otimo, agora insira o horario desejado: ");
        scanf("%d %d %d", &data_hora[i].hora.hora, &data_hora[i].hora.minuto, &data_hora[i].hora.segundo);
    }

   
    ordenarDataHora(data_hora, n);

    
    printf("Datas e horarios ordenados:\n");
    for (i = 0; i < n; i++) {
        printf("%02d/%02d/%04d %02d:%02d:%02d\n", data_hora[i].data.dia, data_hora[i].data.mes, data_hora[i].data.ano, data_hora[i].hora.hora, data_hora[i].hora.minuto, data_hora[i].hora.segundo);
    }



    return 0;
}