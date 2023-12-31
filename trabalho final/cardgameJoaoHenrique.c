#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void distribuir_carta(char *mao, char *deck, char cor[54][10], int *cartas_totais, bool *carta_distribuida) { // seleciona uma carta aleatoria do baralho
    
    int num_total;

    do {
        num_total = rand() % (*cartas_totais);
    } while (carta_distribuida[num_total]);

    sprintf(mao, "%c %s", deck[num_total], cor[num_total]);

    for (int i = num_total; i < *cartas_totais - 1; i++) {
        deck[i] = deck[i + 1];
        strcpy(cor[i], cor[i + 1]);
        carta_distribuida[i] = carta_distribuida[i + 1];
    }

    (*cartas_totais)--;
}

int atribui_valor(char carta[20]) { // atribui valor para as strings para decidir quem ganhou

    int valor = 0;

    if (carta[0] == '1') {
        valor = 1;
    } else if (carta[0] == '2') {
        valor = 2;
    } else if (carta[0] == '3') {
        valor = 3;
    } else if (carta[0] == '4') {
        valor = 4;
    } else if (carta[0] == '5') {
        valor = 5;
    } else if (carta[0] == '6') {
        valor = 6;
    } else if (carta[0] == '7') {
        valor = 7;
    } else if (carta[0] == 'J') {
        valor = 8;
    } else if (carta[0] == 'Q') {
        valor = 9;
    } else if (carta[0] == 'K') {
        valor = 10;
    } else if (carta[0] == 'A') {
        valor = 11;
    } else if (carta[0] == 'C') {
        valor = 12;
    }
    
    return valor;
}

int main() { // deveria ter sido + modularizado o codigo, achei que seria + simples acabei fazendo tudo na main e nao consegui separar depois 

    time_t seed;
    srand((unsigned) time(&seed));
    
    char deck[54] = { '1', '1', '2', '2', '3', '3', '4', '5', '6', '7', 'J', 'Q', 'K', 'A', 
                    '1', '1', '3', '3', '4', '4', '5', '5', '7', 'C', 'J', 'Q', 'K', 'A', 
                    '1', '1', '2', '2', '3', '4', '5', 'J', 'Q', 'K', 'A', 
                    '2', '2', '2', '4', '4', '5', '5', '5', 'J', 'Q', 'K', 'A', 'J', 'J', 'J'};

    char maop1[7][20], maop2[7][20], cor[54][10], p1[99], p2[99], em_jogop1[20], em_jogop2[20];
    int i, case1, num_total, rodadas = 1, cartas_totais = 54, pontuacao_p1 = 0, pontuacao_p2 = 0, escolhap1, escolhap2, vermelha = 0, vermelhap1 = 0, vermelhap2 = 0;
    int chamar_combate, combate_cont = 0, combatew_p1 = 0, combatew_p2 = 0, combate_totais = 0, opcombate = 0;

    bool carta_distribuida[54];
    for (i = 0; i < 54; i++) {
        carta_distribuida[i] = false;
    }

    for (i = 0; i < 14; i++) {
        strcpy(cor[i], "Roxa");
    }
    for (i = 14; i < 28; i++) {
        strcpy(cor[i], "Preta");
    }
    for (i = 28; i < 39; i++) {
        strcpy(cor[i], "Vermelha");
    }
    for (i = 39; i < 51; i++) {
        strcpy(cor[i], "Amarela");
    }

    strcpy(cor[51], "Roxa");
    strcpy(cor[52], "Vermelha");
    strcpy(cor[53], "Amarela");
    


    do {

        printf("> Card Game - dumb play\n");
        printf("(Leia atentamente as orientacoes do jogo)\n");
        printf("Bem vindo! Digite 1 para comecar: ");
        scanf("%d", &case1);

    } while(case1 != 1);

    printf("\nEscolha um apelido para o player 1: ");
    scanf("%s", p1);
    printf("\nEscolha um apelido para o player 2: ");
    scanf("%s", p2);
    printf("\n");
    printf("\nOk, vamos comecar. Distribuindo as cartas (7) para %s:\n", p1);

    for (i = 0; i < 7; i++) {
        distribuir_carta(maop1[i], deck, cor, &cartas_totais, carta_distribuida);
    }

    printf("\n");
    printf("\nDistribuindo as cartas (7) para %s\n", p2);

    for(i = 0; i < 7; i++) {
        distribuir_carta(maop2[i], deck, cor, &cartas_totais, carta_distribuida);
    }

    printf("\n");
    printf("\nRodada: %d", rodadas);

    int numcartasp1 = 7; 
    int numcartasp2 = 7;
    int compra_vermelha_p1 = 0;
    int compra_vermelha_p2 = 0;

    while (cartas_totais > 0 || numcartasp1 > 0 || numcartasp2 > 0){ // loop do jogo

        int continuar = 0;
        combate_cont = 0;
        printf("\nVez de %s", p1);
        printf("\nCartas de %s:\n", p1);
        for(i = 0; i < numcartasp1; i++){
            if (maop1[i][2] == 'R' && maop1[i][0] != 'J' && maop1[i][0] != 'K' && maop1[i][0] != 'A' && maop1[i][0] != 'Q'){
                printf("\n%d- R%s ", i + 1, maop1[i]);

            }
            else {
                printf("\n%d- %s ", i + 1, maop1[i]);
            }
                
        }

        for(i = 0; i < numcartasp1; i++){
            if(maop1[i][2] == 'P'){
                combate_cont++;
                opcombate++;
            }
        }

        if(combate_cont > 0){
            printf("\nVoce tem %d opcoes de combate nas cartas de posicao ", combate_cont);
            for(i = 0; i < numcartasp1; i++){
                if(maop1[i][2] == 'P'){
                    printf("(%d) ", i + 1);
                }   
            }

            printf("\nDeseja chamar um combate? Digite 1 se sim, <> 1 se nao: ");
            scanf("%d", &chamar_combate);

            if(chamar_combate == 1){

                printf("\nInforme qual carta sera utilizada para chamar o combate (preta): ");
                scanf("%d", &escolhap1);

                switch (escolhap1) {
                        case 1:
                            strcpy(em_jogop1, maop1[0]);
                            break;
                        case 2:
                            strcpy(em_jogop1, maop1[1]);
                            break;
                        case 3:
                            strcpy(em_jogop1, maop1[2]);                        
                            break;
                        case 4:
                            strcpy(em_jogop1, maop1[3]);
                            break;
                        case 5:                                
                            strcpy(em_jogop1, maop1[4]);
                            break;
                        case 6:
                            strcpy(em_jogop1, maop1[5]);
                            break;
                        case 7: 
                            strcpy(em_jogop1, maop1[6]);
                            break;
                }

                while (em_jogop1[2] != 'P') {

                    printf("\nCarta invalida, digite novamente: ");
                    scanf("%d", &escolhap1);

                    switch (escolhap1) {
                        case 1:
                            strcpy(em_jogop1, maop1[0]);
                            break;
                        case 2:
                            strcpy(em_jogop1, maop1[1]);
                            break;
                        case 3:
                            strcpy(em_jogop1, maop1[2]);                        
                            break;
                        case 4:
                            strcpy(em_jogop1, maop1[3]);
                            break;
                        case 5:                                
                            strcpy(em_jogop1, maop1[4]);
                            break;
                        case 6:
                            strcpy(em_jogop1, maop1[5]);
                            break;
                        case 7: 
                            strcpy(em_jogop1, maop1[6]);
                            break;
                    }

                }

                int valorp1 = atribui_valor(em_jogop1);

                for (i = escolhap1 - 1; i < numcartasp1 - 1; i++) {
                    strcpy(maop1[i], maop1[i + 1]);
                }

                numcartasp1--;

                printf("\n> Combate");
                printf("\nCartas de %s\n", p2);

                for(i = 0; i < numcartasp2; i++){
                    printf("\n%d- %s ", i + 1, maop2[i]);
                }

                if(numcartasp2 > 0){

                    printf("\n\nInforme uma carta para responder o combate: ");
                    scanf("%d", &escolhap2);

                    switch (escolhap2) {
                        case 1:
                            strcpy(em_jogop2, maop2[0]);
                            break;
                        case 2:                    
                            strcpy(em_jogop2, maop2[1]);
                            break;
                        case 3:
                            strcpy(em_jogop2, maop2[2]);                        
                            break;
                        case 4:
                            strcpy(em_jogop2, maop2[3]);
                            break;
                        case 5:
                            strcpy(em_jogop2, maop2[4]);
                            break;
                        case 6:
                            strcpy(em_jogop2, maop2[5]);
                            break;
                        case 7: 
                            strcpy(em_jogop2, maop2[6]);
                            break;
                    }

                    while(escolhap2 > numcartasp2 || escolhap2 < 1){

                        printf("\n\nPosicao invalida, digite novamente: ");
                        scanf("%d", &escolhap2);

                        switch (escolhap2) {
                            case 1:
                                strcpy(em_jogop2, maop2[0]);
                                break;
                            case 2:                    
                                strcpy(em_jogop2, maop2[1]);
                                break;
                            case 3:
                                strcpy(em_jogop2, maop2[2]);                        
                                break;
                            case 4:
                                strcpy(em_jogop2, maop2[3]);
                                break;
                            case 5:
                                strcpy(em_jogop2, maop2[4]);
                                break;
                            case 6:
                                strcpy(em_jogop2, maop2[5]);
                                break;
                            case 7: 
                                strcpy(em_jogop2, maop2[6]);
                                break;
                        }
                    }

                    int valorp2 = atribui_valor(em_jogop2);

                    for (i = escolhap2 - 1; i < numcartasp2 - 1; i++) {
                        strcpy(maop2[i], maop2[i + 1]);
                    }

                    numcartasp2--; 

                    if (em_jogop2[2] == em_jogop1[2] && valorp2 > valorp1){
                        printf("\n%s ganhou o combate!", p2);
                        combatew_p2 += 1;
                        combate_totais++;
                    }
                    else if (em_jogop2[2] == em_jogop1[2] && valorp2 == valorp1){
                        printf("\nEmpate no combate!");
                        combate_totais++;
                    }
                    else {
                        printf("\n%s ganhou o combate!", p1);
                        combate_totais++;
                        combatew_p1 += 1;
                    }
                }
            } else {
                printf("Pressione 1 para continuar: ");
                scanf("%d", &continuar);
            }
        }

        printf("\n> Fim do combate/combate negado/sem opcao de combate\n");
        printf("\nCartas de %s:\n", p1);

        for(i = 0; i < numcartasp1; i++){
            if (maop1[i][2] == 'R' && maop1[i][0] != 'J' && maop1[i][0] != 'K' && maop1[i][0] != 'A' && maop1[i][0] != 'Q'){
                printf("\n%d- R%s ", i + 1, maop1[i]);
            }
            else {
                printf("\n%d- %s ", i + 1, maop1[i]);
            }
        }

        if(numcartasp1 > 0){

            printf("\nQual carta deseja jogar? Digite a posicao (1 - 7): ");
            scanf("%d", &escolhap1);
           
            switch (escolhap1) {
                case 1:
                    strcpy(em_jogop1, maop1[0]);
                    break;
                case 2:
                    strcpy(em_jogop1, maop1[1]);
                    break;
                case 3:
                    strcpy(em_jogop1, maop1[2]);                        
                    break;
                case 4:
                    strcpy(em_jogop1, maop1[3]);
                    break;
                case 5:
                    strcpy(em_jogop1, maop1[4]);
                    break;
                case 6:
                    strcpy(em_jogop1, maop1[5]);
                    break;
                case 7: 
                    strcpy(em_jogop1, maop1[6]);
                    break;
            }

            while (escolhap1 > numcartasp1 || escolhap1 < 1){

                printf("\nPosicao invalida. Digite novamente: ");
                scanf("%d", &escolhap1);
           
                switch (escolhap1) {
                    case 1:
                        strcpy(em_jogop1, maop1[0]);
                        break;
                    case 2:
                        strcpy(em_jogop1, maop1[1]);
                        break;
                    case 3:
                        strcpy(em_jogop1, maop1[2]);                        
                        break;
                    case 4:
                        strcpy(em_jogop1, maop1[3]);
                        break;
                    case 5:
                        strcpy(em_jogop1, maop1[4]);
                        break;
                    case 6:
                        strcpy(em_jogop1, maop1[5]);
                        break;
                    case 7: 
                        strcpy(em_jogop1, maop1[6]);
                        break;
                }
            } 
        }

        if(em_jogop1[2] == 'V'){
            vermelhap1++;
            vermelha++;
        }

        int valorp1 = atribui_valor(em_jogop1);

        printf("\n\nCarta(s) em jogo de %s: %s\n", p1, em_jogop1);

        for (i = escolhap1 - 1; i < numcartasp1 - 1; i++) {
            strcpy(maop1[i], maop1[i + 1]);
        }
        numcartasp1--;

        printf("\nPressione 1 para continuar: ");
        scanf("%d", &continuar);  
        printf("\nVez de %s", p2);
        printf("\nCartas de %s\n", p2);

        combate_cont = 0;

        for(i = 0; i < numcartasp2; i++){
            printf("\n%d- %s ", i + 1, maop2[i]);
        }

        for(i = 0; i < numcartasp1; i++){
            if(maop2[i][2] == 'P'){
                combate_cont++;
                opcombate++;
            }
        }

        if(combate_cont > 0){
            printf("\nVoce tem %d opcoes de combate nas cartas de posicao ", combate_cont);
            for(i = 0; i < numcartasp2; i++){
                if(maop2[i][2] == 'P'){
                    printf("(%d) ", i + 1);
                }   
            }

            chamar_combate = 0;

            printf("\nDeseja chamar um combate? Digite 1 se sim, <> 1 se nao: ");
            scanf("%d", &chamar_combate);

            if(chamar_combate == 1){

                printf("\nInforme qual carta sera utilizada para chamar o combate (preta): ");
                scanf("%d", &escolhap2);

                switch (escolhap2) {
                        case 1:
                            strcpy(em_jogop2, maop2[0]);
                            break;
                        case 2:
                            strcpy(em_jogop2, maop2[1]);
                            break;
                        case 3:
                            strcpy(em_jogop2, maop2[2]);                        
                            break;
                        case 4:
                            strcpy(em_jogop2, maop2[3]);
                            break;
                        case 5:                                
                            strcpy(em_jogop2, maop2[4]);
                            break;
                        case 6:
                            strcpy(em_jogop2, maop2[5]);
                            break;
                        case 7: 
                            strcpy(em_jogop2, maop2[6]);
                            break;
                }

                while (em_jogop2[2] != 'P') {

                    printf("\nCarta invalida, digite novamente: ");
                    scanf("%d", &escolhap2);

                    switch (escolhap2) {
                        case 1:
                            strcpy(em_jogop2, maop2[0]);
                            break;
                        case 2:
                            strcpy(em_jogop2, maop2[1]);
                            break;
                        case 3:
                            strcpy(em_jogop2, maop2[2]);                        
                            break;
                        case 4:
                            strcpy(em_jogop2, maop2[3]);
                            break;
                        case 5:                                
                            strcpy(em_jogop2, maop2[4]);
                            break;
                        case 6:
                            strcpy(em_jogop2, maop2[5]);
                            break;
                        case 7: 
                            strcpy(em_jogop2, maop2[6]);
                            break;
                        }
                }

                int valorp2 = atribui_valor(em_jogop2);

                for (i = escolhap2 - 1; i < numcartasp2 - 1; i++) {
                    strcpy(maop2[i], maop2[i + 1]);
                }

                numcartasp2--;

                printf("\n> Combate");
                printf("\nCartas de %s\n", p1);

                for(i = 0; i < numcartasp1; i++){
                    printf("\n%d- %s ", i + 1, maop1[i]);
                }

                if(numcartasp1 > 0){

                    printf("\n\nInforme uma carta para responder o combate: ");
                    scanf("%d", &escolhap1);

                    switch (escolhap1) {
                        case 1:
                            strcpy(em_jogop1, maop1[0]);
                            break;
                        case 2:                    
                            strcpy(em_jogop1, maop1[1]);
                            break;
                        case 3:
                            strcpy(em_jogop1, maop1[2]);                        
                            break;
                        case 4:
                            strcpy(em_jogop1, maop1[3]);
                            break;
                        case 5:
                            strcpy(em_jogop1, maop1[4]);
                            break;
                        case 6:
                            strcpy(em_jogop1, maop1[5]);
                            break;
                        case 7: 
                            strcpy(em_jogop1, maop1[6]);
                            break;
                    }

                    while (escolhap1 > numcartasp1 || escolhap1 < 1){

                        printf("\nPosicao invalida. Digite novamente: ");
                        scanf("%d", &escolhap1);

                        switch (escolhap1) {
                        case 1:
                            strcpy(em_jogop1, maop1[0]);
                            break;
                        case 2:                    
                            strcpy(em_jogop1, maop1[1]);
                            break;
                        case 3:
                            strcpy(em_jogop1, maop1[2]);                        
                            break;
                        case 4:
                            strcpy(em_jogop1, maop1[3]);
                            break;
                        case 5:
                            strcpy(em_jogop1, maop1[4]);
                            break;
                        case 6:
                            strcpy(em_jogop1, maop1[5]);
                            break;
                        case 7: 
                            strcpy(em_jogop1, maop1[6]);
                            break;
                        }
                    }

                    int valorp1 = atribui_valor(em_jogop1);

                    for (i = escolhap1 - 1; i < numcartasp1 - 1; i++) {
                        strcpy(maop1[i], maop1[i + 1]);
                    }

                    numcartasp1--; // nao consegui implementar a mecanica de jogar mais de uma carta no combate sem quebrar outras partes do jogo

                    if (valorp1 == 10 && valorp2 == 12){ // castelo que é a carta de maior valor perde apenas para o rei (independente do naipe)
                        combatew_p1 += 1;
                        combate_totais++;
                    }

                    else if (valorp2 == 10 && valorp1 == 12){
                        combatew_p2 += 1;
                        combate_totais++;
                    } 

                    else if (em_jogop1[2] == em_jogop2[2] && valorp1 > valorp2){
                        printf("\n%s ganhou o combate!", p1);
                        combatew_p1 += 1;
                        combate_totais++;
                    }

                    else if (em_jogop1[2] == em_jogop2[2] && valorp2 == valorp1){
                        printf("\nEmpate no combate!");
                        combate_totais++;
                    }
                    
                    else {
                        printf("\n%s ganhou o combate!", p2);
                        combate_totais++;
                        combatew_p2 += 1;
                    }
                }
            } else {
                printf("Pressione 1 para continuar: ");
                scanf("%d", &continuar);
            }
        }

        printf("\n> Fim do combate/combate negado/sem opcao de combate\n");
        printf("\nCartas de %s:\n", p2);

        for(i = 0; i < numcartasp2; i++){
            if (maop2[i][2] == 'R' && maop2[i][0] != 'J' && maop2[i][0] != 'K' && maop2[i][0] != 'A' && maop2[i][0] != 'Q'){
                printf("\n%d- R%s ", i + 1, maop2[i]);
            }
            else {
                printf("\n%d- %s ", i + 1, maop2[i]);
            }
        }

        if(numcartasp2 > 0){

            printf("\n\nQual carta deseja jogar? Digite a posicao (1 - 7): ");
            scanf("%d", &escolhap2);

            switch (escolhap2) {
                case 1:
                    strcpy(em_jogop2, maop2[0]);
                    break;
                case 2:                    
                    strcpy(em_jogop2, maop2[1]);
                    break;
                case 3:
                    strcpy(em_jogop2, maop2[2]);                        
                    break;
                case 4:
                    strcpy(em_jogop2, maop2[3]);
                    break;
                case 5:
                    strcpy(em_jogop2, maop2[4]);
                    break;
                case 6:
                    strcpy(em_jogop2, maop2[5]);
                    break;
                case 7: 
                    strcpy(em_jogop2, maop2[6]);
                    break;
            }

            while (escolhap2 > numcartasp2 || escolhap2 < 1){

                printf("\nPosicao invalida. Digite novamente: ");
                scanf("%d", &escolhap2);
           
                switch (escolhap2) {
                case 1:
                    strcpy(em_jogop2, maop2[0]);
                    break;
                case 2:                    
                    strcpy(em_jogop2, maop2[1]);
                    break;
                case 3:
                    strcpy(em_jogop2, maop2[2]);                        
                    break;
                case 4:
                    strcpy(em_jogop2, maop2[3]);
                    break;
                case 5:
                    strcpy(em_jogop2, maop2[4]);
                    break;
                case 6:
                    strcpy(em_jogop2, maop2[5]);
                    break;
                case 7: 
                    strcpy(em_jogop2, maop2[6]);
                    break;

                }
            }
        }

        if(em_jogop2[2] == 'V'){
            vermelhap2++;
            vermelha++;
        }

        int valorp2 = atribui_valor(em_jogop2);

        for (i = escolhap2 - 1; i < numcartasp2 - 1; i++) {
            strcpy(maop2[i], maop2[i + 1]);
        }

        numcartasp2--; 
            
        printf("\nCarta(s) em jogo de %s: %s\n", p2, em_jogop2);

        pontuacao_p1 += valorp1;
        pontuacao_p2 += valorp2;

        if (vermelhap1 > 0 && cartas_totais > 0) {
            int falta_cartas_p1 = 7 - numcartasp1;

            if (falta_cartas_p1 > 0) {
                int compra = (vermelhap1 < falta_cartas_p1) ? vermelhap1 : falta_cartas_p1;
                for (i = 0; i < compra; i++) {
                    do {
                        num_total = rand() % 54;
                    } while (carta_distribuida[num_total]);
                    distribuir_carta(maop1[numcartasp1 + i], deck, cor, &cartas_totais, carta_distribuida);
                    compra_vermelha_p1++;
                }

                numcartasp1 += compra;
            }
        }
 
        else if(vermelhap1 == 0 && numcartasp1 < 7){ // nao e o ideal mas funciona

                int compra = 1;
                for (i = 0; i < compra; i++) {
                    do {
                        num_total = rand() % 54;
                    } while (carta_distribuida[num_total]);
                    distribuir_carta(maop1[numcartasp1 + i], deck, cor, &cartas_totais, carta_distribuida);
                    compra_vermelha_p1++;
                }

                numcartasp1 += compra;
            
            
        }


        if (vermelhap2 > 0 && cartas_totais > 0) {

            int falta_cartas_p2 = 7 - numcartasp2;

            if (falta_cartas_p2 > 0) {
                int compra = (vermelhap2 < falta_cartas_p2) ? vermelhap2 : falta_cartas_p2;
                for (i = 0; i < compra; i++) {
                    do {
                        num_total = rand() % 54;
                    } while (carta_distribuida[num_total]);
                        distribuir_carta(maop2[numcartasp2 + i], deck, cor, &cartas_totais, carta_distribuida);
                        compra_vermelha_p2++;
                    }

                numcartasp2 += compra;

            }
        }

        else if(vermelhap2 == 0 && numcartasp2 < 7){

            int compra = 1;
                for (i = 0; i < compra; i++) {
                    do {
                        num_total = rand() % 54;
                    } while (carta_distribuida[num_total]);
                        distribuir_carta(maop2[numcartasp2 + i], deck, cor, &cartas_totais, carta_distribuida);
                        compra_vermelha_p2++;
                    }

                numcartasp2 += compra;

        }
    
        printf("\nFim da rodada %d\n", rodadas);
        printf("Combates vencidos por %s: %d\n", p1, combatew_p1);
        printf("Combates vencidos por %s: %d", p2, combatew_p2);
        printf("\nCartas disponiveis para compra: %d", cartas_totais);
        printf("\nPressione 1 para continuar: ");
        scanf("%d", &continuar);
        rodadas++;

    }

    pontuacao_p1 += (combatew_p1 * 3);
    pontuacao_p2 += (combatew_p2 * 3);

    printf("\n> FIM DE JOGO\n");
    printf("\nTotal de rodadas: %d", rodadas);
    printf("\nCombates vencidos por %s: %d", p1, combatew_p1);
    printf("\nCombates vencidos por %s: %d", p2, combatew_p2);
    printf("\nPontuacao %s: %d", p1, pontuacao_p1);
    printf("\nPontuacao %s: %d", p2, pontuacao_p2);

    if(pontuacao_p1 > pontuacao_p2){
        printf("\nResultado final: %s ganhou! Parabens!", p1);
    }

    else if(pontuacao_p2 > pontuacao_p1){
        printf("\nResultado final: %s ganhou! Parabens!", p2);
    }

    else {
        printf("\nResultado final: empate!");
    }

    return 0;
    
}