#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct listaTelefonica {
    char nome[50];
    char telefone[30];
    char email[50];
};

struct data{
    int ano;
    int mes;
    int dia;
};

struct hora{
    int hora;
    int minuto;
    int segundo;
};

struct evento{
    struct listaTelefonica *lista;
    struct data data;
    struct hora inicio;
    struct hora final;
    char localizacao[100];
    char descricao[500];
    int numParticipantes;
};

struct hora definirHora(int hora, int minuto, int segundo){
    //calculos para transformar horario 
    do{
        if(segundo > 59){
            segundo -= 60;
            minuto += 1;
        }
        if(minuto > 59) {
            minuto -= 60;
            hora += 1;
        }
        if(hora > 23) {
            hora -= 24;
        }
    } while(hora > 23 || minuto > 59 || segundo > 59);

    //transforma os inteiros em um struct
    struct hora horas;
    horas.hora = hora;
    horas.minuto = minuto;
    horas.segundo = segundo;

    return horas;
}
    
struct data definirData(int dia, int mes, int ano){
    do{
        if(dia > 31){   //considerando que todos os meses tem 31 dias, se fosse aplicar os meses com menores dias ia ficar mais complexo a logica
            dia -=  31;
            mes += 1;
        }
        if(mes > 12){
            mes -= 12;
            ano += 1;
        }
    }while(dia > 31 || mes > 12);

    //transforma os inteiros em um struct
    struct data data;
    data.ano = ano;
    data.mes = mes;
    data.dia = dia;
    return data;

}

struct listaTelefonica definirContato(char* nome, char* telefone, char* email) {
    struct listaTelefonica contato;
    
    strcpy(contato.nome, nome);
    strcpy(contato.telefone, telefone);
    strcpy(contato.email, email);
    return contato;
}

//funcao para comparar os eventos, usada para organizar em ordem cronologica
int comparaEventos(const void *a, const void *b) {
    struct evento *eventoA = (struct evento *)a;
    struct evento *eventoB = (struct evento *)b;

    //compara anos
    if (eventoA->data.ano != eventoB->data.ano) {
        return eventoA->data.ano - eventoB->data.ano;
    }
    //compara meses
    if (eventoA->data.mes != eventoB->data.mes) {
        return eventoA->data.mes - eventoB->data.mes;
    }
    //compara dias
    if (eventoA->data.dia != eventoB->data.dia) {
        return eventoA->data.dia - eventoB->data.dia;
    }
    //compara horas
    if (eventoA->inicio.hora != eventoB->inicio.hora) {
        return eventoA->inicio.hora - eventoB->inicio.hora;
    }
    //compara minutos
    if (eventoA->inicio.minuto != eventoB->inicio.minuto) {
        return eventoA->inicio.minuto - eventoB->inicio.minuto;
    }
    
    return eventoA->inicio.segundo - eventoB->inicio.segundo;
}

//funcao q chama a de cima para organizar em ordem cronologica
struct evento *ordenarEventos(struct evento *evento, int quantidade) {
    qsort(evento, quantidade, sizeof(struct evento), comparaEventos);
    return evento;
}

//funcao para poder mudar a data do evento desejado
struct evento *mudarData(struct evento *eventos, int quantidade, struct data novaData, int indice) {
    if (indice < 0 || indice >= quantidade) {
        printf("Indice fora dos limites!\n");
        return NULL;
    }

    eventos[indice].data = novaData;
    return eventos;
}

//funcao para poder mudar o horario inicial do evento desejado
struct evento *mudarHorarioInicial(struct evento *eventos, int quantidade, struct hora novaHora, int indice){
    if (indice < 0 || indice >= quantidade) {
        printf("Indice fora dos limites!\n");
        return NULL;
    }

    eventos[indice].inicio = novaHora;
    return eventos;
}

//funcao para poder mudar o horario final do evento desejado
struct evento *mudarHorarioFinal(struct evento *eventos, int quantidade, struct hora novaHora, int indice){
    if (indice < 0 || indice >= quantidade) {
        printf("Indice fora dos limites!\n");
        return NULL;
    }

    eventos[indice].final = novaHora;
    return eventos;
}

//funcao para poder mudar a localizacao do evento desejado
struct evento *mudarLocalizacao(struct evento *eventos, int quantidade, char *novaLocalizacao, int indice) {
    if (indice < 0 || indice >= quantidade) {
        printf("Indice fora dos limites!\n");
        return NULL;
    }

    strcpy(eventos[indice].localizacao, novaLocalizacao);
    return eventos;
}

//funcao para poder mudar a descricao do evento desejado
struct evento *mudarDescricao(struct evento *eventos, int quantidade, char *novaDescricao, int indice) {
    if (indice < 0 || indice >= quantidade) {
        printf("Indice fora dos limites!\n");
        return NULL;
    }

    strcpy(eventos[indice].descricao, novaDescricao);
    return eventos;
}

//funcao para poder mudar os participantes do evento desejado
struct evento *mudarParticipantes(struct evento *eventos, int quantidade, struct listaTelefonica *lista, int indice){
    if(indice < 0 || indice >= quantidade){
        printf("Indice fora dos limites");
        return NULL;
    }

    eventos[indice].lista = lista;
    return eventos;
}

//funcao para poder mudar a quantidade de participantes do evento desejado
struct evento *mudarQuantParticipantes(struct evento *eventos, int quantidade, int n, int indice){
    if(indice < 0 || indice >= quantidade){
        printf("Indice fora dos limites");
        return NULL;
    }
    eventos[indice].numParticipantes = n;
    return eventos;
}


int main(){
    int quantidade;
    printf("Quantos eventos deseja criar? ");
    scanf(" %d", &quantidade);
    
    struct evento *eventos = malloc(sizeof(struct evento) * quantidade); //alocacao de memoria necessaria
    if (eventos == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }



    //looping para coletar os dados necessarios para n eventos      
    for(int N = 0; N<quantidade; N++){
    int ano, dia, mes, hora, minuto, segundo, n, i;
    char nome[50], telefone[30], email[50], localizacao[100], descricao[500];
    
    
    printf("Defina uma data para o seu evento (%d) (dd/mm/yyyy): ", N+1);
    scanf(" %d %d %d", &dia, &mes, &ano);
    struct data dataEvento = definirData(dia, mes, ano);


    printf("Agora defina o horario do inicial do evento (hora/minuto/segundo): ");
    scanf(" %d %d %d", &hora, &minuto, &segundo);
    struct hora horaI = definirHora(hora, minuto, segundo);
    

    printf("Agora defina o horario do final do evento (hora/minuto/segundo): ");
    scanf(" %d %d %d", &hora, &minuto, &segundo);
    struct hora horaF = definirHora(hora, minuto, segundo);
    
    printf("Quantas pessoas deseja adicionar nesse evento? ");
    scanf(" %d", &n);

    struct listaTelefonica *contato = malloc(n * sizeof(struct listaTelefonica));
    if (contato == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }
    getchar(); //consome o caractere de nova linha deixado pelo scanf anterior
    for(i = 0; i < n; i++){
        
        printf("O nome da pessoa %d: ", i+1);
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = '\0'; 
        
        printf("Telefone da pessoa %d: ", i+1);
        fgets(telefone, sizeof(telefone), stdin);
        telefone[strcspn(telefone, "\n")] = '\0'; 
        
        printf("Email da pessoa %d: ", i+1);
        fgets(email, sizeof(email), stdin);
        email[strcspn(email, "\n")] = '\0'; 
    
        contato[i] = definirContato(nome, telefone, email);
    }

    
    printf("Qual sera a localização do seu evento (online/endereco): ");
    fgets(localizacao, sizeof(localizacao), stdin);
    localizacao[strcspn(localizacao, "\n")] = '\0';  

    printf("Digite uma breve descricao do evento: ");
    fgets(descricao, sizeof(descricao), stdin);
    descricao[strcspn(descricao, "\n")] = '\0'; 

    
    eventos[N].data = dataEvento;
    strcpy(eventos[N].descricao , descricao);
    eventos[N].final = horaF;
    eventos[N].inicio = horaI;
    eventos[N].lista = contato;
    eventos[N].numParticipantes = n; // Armazena o número de participantes
    strcpy(eventos[N].localizacao , localizacao);
    }
    
    //chamada da funcao de organizacao
    ordenarEventos(eventos, quantidade);

    printf("\n");
   for (int N = 0; N < quantidade; N++) {
        printf("Evento %d\n", N + 1);
        printf("Data: %02d/%02d/%04d\n", eventos[N].data.dia, eventos[N].data.mes, eventos[N].data.ano);
        printf("Horario de inicio: %02d:%02d:%02d\n", eventos[N].inicio.hora, eventos[N].inicio.minuto, eventos[N].inicio.segundo);
        printf("Horario de final: %02d:%02d:%02d\n", eventos[N].final.hora, eventos[N].final.minuto, eventos[N].final.segundo);
        printf("Localizacao: %s\n", eventos[N].localizacao);
        printf("Descricao: %s\n", eventos[N].descricao);
        printf("Participantes:\n");
        for (int i = 0; i < eventos[N].numParticipantes; i++) { 
            printf("Nome: %s\n", eventos[N].lista[i].nome);
        }
        printf("\n");
    }

    //funcionalidade a mais do google agendas, que é poder alterar algum dos dados do evento
    char escolha;
    printf("Deseja editar algum evento? (s/n) ");
    scanf(" %c", &escolha);
    if(tolower(escolha) == 's'){ 
        int x, evento;
        printf("Em qual evento?");
        scanf(" %d", &evento);

        printf("Menu:\n");
        printf("1. Data\n");
        printf("2. Horario Inicial\n");
        printf("3. Horario Final\n");
        printf("4. Localizacao\n");
        printf("5. Descricao\n");
        printf("6. Participantes\n");
        scanf("%d ", &x);

  switch (x) {
            case 1: {
                int dia, mes, ano;
                printf("Defina uma nova data para o seu evento (dd/mm/yyyy): ");
                scanf("%d %d %d", &dia, &mes, &ano);

                struct data novaData = definirData(dia, mes, ano);
                struct evento *eventoAtual = mudarData(eventos, quantidade, novaData, evento - 1);
                if (eventoAtual != NULL) {
                    printf("Data do evento %d alterada para %02d/%02d/%04d\n", evento, novaData.dia, novaData.mes, novaData.ano);
                }
                ordenarEventos(eventos, quantidade);
                break;
            }
            case 2: {
                int hora, minuto, segundo;
                printf("Defina um novo horario inicial do evento (hora/minuto/segundo): ");
                scanf("%d %d %d", &hora, &minuto, &segundo);

                struct hora horaNova = definirHora(hora, minuto, segundo);

                if (evento - 1 < 0 || evento - 1 >= quantidade) {
                    printf("Indice do evento fora dos limites!\n");
                } else {
                    struct evento *eventoAtual = mudarHorarioInicial(eventos, quantidade, horaNova, evento - 1);
                    if (eventoAtual != NULL) {
                        printf("Horario inicial do evento %d alterado para %02d:%02d:%02d\n", evento, horaNova.hora, horaNova.minuto, horaNova.segundo);
                    }
                }
                ordenarEventos(eventos, quantidade); // Ordenar eventos após a modificação
                break;
            }
            case 3: {
                int hora, minuto, segundo;
                printf("Defina um novo horario final do evento (hora/minuto/segundo): ");
                scanf("%d %d %d", &hora, &minuto, &segundo);

                struct hora horaNova = definirHora(hora, minuto, segundo);

                if (evento - 1 < 0 || evento - 1 >= quantidade) {
                    printf("Indice do evento fora dos limites!\n");
                } else {
                    struct evento *eventoAtual = mudarHorarioFinal(eventos, quantidade, horaNova, evento - 1);
                    if (eventoAtual != NULL) {
                        printf("Horario final do evento %d alterado para %02d:%02d:%02d\n", evento, horaNova.hora, horaNova.minuto, horaNova.segundo);
                    }
                }
                ordenarEventos(eventos, quantidade); // Ordenar eventos após a modificação
                break;
            }
            case 4: {
                char localizacaoNova[100];
                getchar(); // Limpa o buffer do teclado
                printf("Informe a nova localização desejada: ");
                fgets(localizacaoNova, sizeof(localizacaoNova), stdin);
                localizacaoNova[strcspn(localizacaoNova, "\n")] = '\0';

                struct evento *eventoAtual = mudarLocalizacao(eventos, quantidade, localizacaoNova, evento - 1);
                if (eventoAtual != NULL) {
                    printf("Localizacao do evento %d alterada para: %s\n", evento, localizacaoNova);
                }
                ordenarEventos(eventos, quantidade); // Ordenar eventos após a modificação
                break;
            }
            case 5: {
                char descricaoNova[500];
                getchar(); // Limpa o buffer do teclado
                printf("Informe a nova descricao desejada: ");
                fgets(descricaoNova, sizeof(descricaoNova), stdin);
                descricaoNova[strcspn(descricaoNova, "\n")] = '\0';

                struct evento *eventoAtual = mudarDescricao(eventos, quantidade, descricaoNova, evento - 1);
                if (eventoAtual != NULL) {
                    printf("Descricao do evento %d alterada para: %s\n", evento, descricaoNova);
                }
                ordenarEventos(eventos, quantidade); // Ordenar eventos após a modificação
                break;
            }
            case 6: {
                int n;
                printf("Quantos participantes deseja adicionar na nova lista: ");
                scanf("%d", &n);
                getchar();

                struct listaTelefonica *contato = malloc(sizeof(struct listaTelefonica) * n);
                if (contato == NULL) {
                    printf("Erro ao alocar memoria!\n");
                    break;
                }

                for (int i = 0; i < n; i++) {
                    char nome[50], telefone[15], email[50];
                    printf("O nome da pessoa %d: ", i + 1);
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = '\0';

                    printf("Telefone da pessoa %d: ", i + 1);
                    fgets(telefone, sizeof(telefone), stdin);
                    telefone[strcspn(telefone, "\n")] = '\0';

                    printf("Email da pessoa %d: ", i + 1);
                    fgets(email, sizeof(email), stdin);
                    email[strcspn(email, "\n")] = '\0';

                    contato[i] = definirContato(nome, telefone, email);
                }

                struct evento *eventoAtual = mudarParticipantes(eventos, quantidade, contato, evento - 1);
                if (eventoAtual != NULL) {
                    printf("Participantes do evento %d alterados com sucesso!\n", evento);
                }

                free(contato);
                ordenarEventos(eventos, quantidade); // Ordenar eventos após a modificação
                break;
            }
            default:
                printf("Opcao invalida! Escolha uma opcao valida.\n");
                break;
        }
    }

   //print da nova ordenação 
   printf("\n");
   for (int N = 0; N < quantidade; N++) {
        printf("Evento %d\n", N + 1);
        printf("Data: %02d/%02d/%04d\n", eventos[N].data.dia, eventos[N].data.mes, eventos[N].data.ano);
        printf("Horario de inicio: %02d:%02d:%02d\n", eventos[N].inicio.hora, eventos[N].inicio.minuto, eventos[N].inicio.segundo);
        printf("Horario de final: %02d:%02d:%02d\n", eventos[N].final.hora, eventos[N].final.minuto, eventos[N].final.segundo);
        printf("Localizacao: %s\n", eventos[N].localizacao);
        printf("Descricao: %s\n", eventos[N].descricao);
        printf("Participantes:\n");
        for (int i = 0; i < eventos[N].numParticipantes; i++) { 
            printf("Nome: %s\n", eventos[N].lista[i].nome);
        }
        printf("\n");
    }
    
    // Liberar a memória alocada
    for (int N = 0; N < quantidade; N++) {
        free(eventos[N].lista);
    }
    free(eventos);

    return 0;
}