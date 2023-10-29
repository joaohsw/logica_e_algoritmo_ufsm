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

    for (int i = num_total; i < *cartas_totais - 1; i++) {
        deck[i] = deck[i + 1];
        strcpy(cor[i], cor[i + 1]);
        carta_distribuida[i] = carta_distribuida[i + 1];
    }

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
    int chamar_combate, combate_cont = 0, combatew_p1 = 0, combatew_p2 = 0, combate_totais = 0;

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

    while (cartas_totais > 0 || numcartasp1 > 0 || numcartasp2 > 0){

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
            }
        }

        if(combate_cont > 0){
            printf("\nVoce tem %d opcoes de combate nas cartas ", combate_cont);
            for(i = 0; i < numcartasp1; i++){
                if(maop1[i][2] == 'P'){
                    printf("%d ", i + 1);
                }   
            }

            printf("\nDeseja chamar um combate? Digite 1 se sim, diferente de 1 se nao: ");
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

                printf("\nResposta ao combate %s", p2);
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

                    int valorp2 = atribui_valor(em_jogop2);

                    for (i = escolhap2 - 1; i < numcartasp2 - 1; i++) {
                        strcpy(maop2[i], maop2[i + 1]);
                    }

                    numcartasp2--; 

                    if (em_jogop2[2] == em_jogop1[2] && valorp2 > valorp1){
                        printf("\nJogador %s ganhou o combate!", p2);
                        pontuacao_p2 += 3;
                        combatew_p2++;
                        combate_totais++;
                    }
                    else if (em_jogop2[2] == em_jogop1[2] && valorp2 == valorp1){
                        printf("\nEmpate no combate!");
                        combate_totais++;
                    }
                    else {
                        printf("\nJogador %s ganhou o combate!", p1);
                        combate_totais++;
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

            printf("\nQual carta deseja jogar? Digite o numero: ");
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
            }
        }

        if(combate_cont > 0){
            printf("\nVoce tem %d opcoes de combate nas cartas ", combate_cont);
            for(i = 0; i < numcartasp2; i++){
                if(maop2[i][2] == 'P'){
                    printf("%d ", i + 1);
                }   
            }

            chamar_combate = 0;

            printf("\nDeseja chamar um combate? Digite 1 se sim, diferente de 1 se nao: ");
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

                printf("\nResposta ao combate %s", p1);
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

                    int valorp1 = atribui_valor(em_jogop1);

                    for (i = escolhap1 - 1; i < numcartasp1 - 1; i++) {
                        strcpy(maop1[i], maop1[i + 1]);
                    }

                    numcartasp1--; 

                    if (em_jogop1[2] == em_jogop2[2] && valorp1 > valorp2){
                        printf("\nJogador %s ganhou o combate!", p1);
                        pontuacao_p1 += 3;
                        combatew_p1++;
                        combate_totais++;
                    }

                    else if (em_jogop1[2] == em_jogop2[2] && valorp2 == valorp1){
                        printf("\nEmpate no combate!");
                        combate_totais++;
                    }
                    
                    else {
                        printf("\nJogador %s ganhou o combate!", p2);
                        combate_totais++;
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
            pontuacao_p1 += 1;
        }
        else if(valorp2 > valorp1){
            pontuacao_p2 += 1;
        }
        else {
            printf("\nEmpate na rodada!\n");
        }
        

        if (vermelha > 0 && cartas_totais > 0) {
            int falta_cartas_p1 = 7 - numcartasp1;
            int falta_cartas_p2 = 7 - numcartasp2;

            if (falta_cartas_p1 > 0) {
                int compra = (vermelha < falta_cartas_p1) ? vermelha : falta_cartas_p1;
                for (i = 0; i < compra; i++) {
                    do {
                        num_total = rand() % 51;
                    } while (carta_distribuida[num_total]);
                    distribuir_carta(maop1[numcartasp1 + i], deck, cor, &cartas_totais, carta_distribuida);
                    compra_vermelha_p1++;
                }

                numcartasp1 += compra;
            }

            if (vermelha > 0 && cartas_totais > 1) {
                int falta_cartas_p1 = 7 - numcartasp1;
                int falta_cartas_p2 = 7 - numcartasp2;

                if (falta_cartas_p2 > 0) {
                    int compra = (vermelha < falta_cartas_p2) ? vermelha : falta_cartas_p2;
                    for (i = 0; i < compra; i++) {
                        do {
                            num_total = rand() % 51;
                        } while (carta_distribuida[num_total]);
                        distribuir_carta(maop2[numcartasp2 + i], deck, cor, &cartas_totais, carta_distribuida);
                        compra_vermelha_p2++;
                    }

                numcartasp2 += compra;

                }
            }
        }


        printf("\nFim da rodada %d\n", rodadas);
        printf("\nPressione 1 para continuar: ");
        scanf("%d", &continuar);
        rodadas++;

    
    }

    printf("\n> FIM DE JOGO\n");
    printf("Total de rodadas: %d", rodadas);
    printf("\nPontuacao %s: %d \n", p1, pontuacao_p1);
    printf("\nPontuacao %s: %d \n", p2, pontuacao_p2);


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