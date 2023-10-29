#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void distribuir_carta(char *mao, char *deck, char cor[51][10], int *cartas_totais, bool *carta_distribuida) {

    int num_total;

    do {
        num_total = rand() % (*cartas_totais);
        
    } while (carta_distribuida[num_total]);


    sprintf(mao, "%c %s", deck[num_total], cor[num_total]);
    carta_distribuida[num_total] = true;
    (*cartas_totais)--;
}


int atribui_valor(char carta[20]) {

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



int main() {

    time_t seed;
    srand((unsigned) time(&seed));
    
    char deck[51] = { '1', '1', '2', '2', '3', '3', '4', '5', '6', '7', 'J', 'Q', 'K', 'A', 
                    '1', '1', '3', '3', '4', '4', '5', '5', '7', 'C', 'J', 'Q', 'K', 'A', 
                    '1', '1', '2', '2', '3', '4', '5', 'J', 'Q', 'K', 'A', 
                    '2', '2', '2', '4', '4', '5', '5', '5', 'J', 'Q', 'K', 'A'};

    char maop1[7][20], maop2[7][20], cor[51][10], p1[99], p2[99], em_jogop1[20], em_jogop2[20];
    int i, case1, num_total, rodadas = 1, cartas_totais = 51, pontuacao_p1 = 0, pontuacao_p2 = 0, escolhap1, escolhap2, roxa = 0, preta = 0, vermelha = 0, amarela = 0;

    bool carta_distribuida[51];
    for (i = 0; i < 51; i++) {
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


    do {
        printf("> Card Game - dumb play\n");
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
        printf("\n%s ", maop1[i]);
    }

    printf("\n");
    printf("\nDistribuindo as cartas (7) para %s\n", p2);

    for(i = 0; i < 7; i++) {
        distribuir_carta(maop2[i], deck, cor, &cartas_totais, carta_distribuida);
        printf("\n%s ", maop2[i]);
    }

    printf("\n");
    
    printf("\nRodada: %d", rodadas);

    int numcartasp1 = 7; 
    int numcartasp2 = 7;
    int compra_vermelha_p1 = 0;
    int compra_vermelha_p2 = 0;

    do{

        printf("\nVez de %s", p1);
        printf("\nCartas de %s:\n", p1);
        for(i = 0; i < numcartasp1; i++){
            printf("\n%d- %s ", i + 1, maop1[i]);
        }

        printf("\n\nQual carta deseja jogar? Digite o numero: ");
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

        if(em_jogop1[2] == 'V'){
            vermelha++;
        }
        else if(em_jogop1[2] == 'P'){
            preta++;
        }
        else if(em_jogop1[2] == 'V'){
            roxa++;
        }
        else if(em_jogop1[2] == 'A'){
            amarela++;
        }

        int valorp1 = atribui_valor(em_jogop1);

        printf("\n\nCarta(s) em jogo de %s: %s\n", p1, em_jogop1);

        for (i = escolhap1 - 1; i < numcartasp1 - 1; i++) {
            strcpy(maop1[i], maop1[i + 1]);
        }

        numcartasp1--; 

        int continuar = 0;

        printf("\nPressione 1 para continuar: ");
        scanf("%d", &continuar);  
            
        printf("\nVez de %s", p2);
        printf("\nCartas de %s\n", p2);

        for(i = 0; i < numcartasp2; i++){
            printf("\n%d- %s ", i + 1, maop2[i]);
        }

        printf("\n\nQual carta deseja jogar? Digite o numero: ");
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

        if(em_jogop2[2] == 'V'){
            vermelha++;
        }
        else if(em_jogop2[2] == 'P'){
            preta++;
        }
        else if(em_jogop2[2] == 'V'){
            roxa++;
        }
        else if(em_jogop2[2] == 'A'){
            amarela++;
        }


        int valorp2 = atribui_valor(em_jogop2);

        for (i = escolhap2 - 1; i < numcartasp2 - 1; i++) {
            strcpy(maop2[i], maop2[i + 1]);
        }

        numcartasp2--; 
            
        printf("\nCarta(s) em jogo de %s: %s\n", p2, em_jogop2);

        if(valorp1 > valorp2){
            pontuacao_p1 = pontuacao_p1 + valorp1;
        }
        else if(valorp2 > valorp1){
            pontuacao_p2 = pontuacao_p2 + valorp2;
        }
        else {
            printf("\nEmpate na rodada!\n");
        }
        

        if (vermelha > 0) {
            int compra = (vermelha < 7 - numcartasp1) ? vermelha : (7 - numcartasp1);
            for (i = 0; i < compra; i++) {
                do {
                    num_total = rand() % 51;
                } while (carta_distribuida[num_total]);
                distribuir_carta(maop1[numcartasp1 + i], deck, cor, &cartas_totais, carta_distribuida);
                compra_vermelha_p1++;
            }
            numcartasp1 += compra;
        }
        

        if (vermelha > 0) {
            int compra = (vermelha < 7 - numcartasp2) ? vermelha : (7 - numcartasp2);
            for (i = 0; i < compra; i++) {
                do {
                    num_total = rand() % 51;
                } while (carta_distribuida[num_total]);
                distribuir_carta(maop2[numcartasp2 + i], deck, cor, &cartas_totais, carta_distribuida);
                compra_vermelha_p2++;
            }
            numcartasp2 += compra;
        }

        printf("\nFim da rodada %d\n", rodadas);
        printf("\nPontuacao %s: %d \n", p1, pontuacao_p1);
        printf("\nPontuacao %s: %d \n", p2, pontuacao_p2);
        printf("\nCartas restantes no baralho principal: %d\n", cartas_totais);
        printf("\nPressione 1 para continuar: ");
        scanf("%d", &continuar);
        rodadas++;

    } while (cartas_totais != 0);

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