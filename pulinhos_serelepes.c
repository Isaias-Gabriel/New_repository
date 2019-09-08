#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

//variaveis globais
int *historico[100], k = 0, *peca_posicao_num[2], turno = 0;
int positions_x[20] = {1, 1, 2, 1, 3, 1, 4, 1, 1, 2,
2, 2, 3, 2, 1, 3, 2, 3, 1, 4},
positions_y[20] = {8, 8, 7, 8, 6, 8, 5, 8, 8, 7,
7, 7, 6, 7, 8, 6, 7, 6, 8, 5};
int copy_x[20]= {1, 1, 2, 1, 3, 1, 4, 1, 1, 2,
2, 2, 3, 2, 1, 3, 2, 3, 1, 4},
copy_y[20]= {8, 8, 7, 8, 6, 8, 5, 8, 8, 7,
7, 7, 6, 7, 8, 6, 7, 6, 8, 5};
FILE *flp, *flp_carregar;

char exibeTabuleiro(int *positions_x, int *positions_y);
char posicaoMatriz(char *str, int n);
int trocaTurno(int num);
int validaPeca(int *positions_x, int *positions_y, int *peca_posicao_num, int turno);
int validaMovimento(int *positions_x,int *positions_y, int *peca_posicao_num, int direcao);
int vitoria(int *positions_x, int *copy_x, int *copy_y, int n);
int escolhaPosicao(int opcao);

int main(void){
int i, j, m, d = 0, opcao;
char tabuleiro[9][9], partida[30], copy_partida[30], str1[]="_nova_partida.txt", str2[]="_carregar_partida.txt";

for(i=0;i<9;i++){
	for(j=0;j<9;j++){
        tabuleiro[i][j]=' ';
	}
}
for(i=0;i<9;i++){
    historico[i]=0;
}

printf("---------PULINHOS SERELEPES---------\n\n\n\n\n");

printf("1: Iniciar nova partida.\n");
printf("2: Carregar partida.\n");
printf("3: Ver replay.\n");
printf("4: Sair.\n\n");
scanf("%d",&opcao);
system("cls");

//codigo principal para o uso de arquivos
if(opcao == 1 ){
    printf("Digite um nome para a partida(sem espacos)\n");
    scanf("%s",partida), strcpy(copy_partida,partida), strcat(partida,str1), strcat(copy_partida,str2);
    flp = fopen(partida,"w+"),fclose(flp);
    while((flp = fopen(partida,"w+")) == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        printf("Digite um nome para a partida(sem espaços)\n");
        scanf("%s",partida);
        flp = fopen(partida,"w+"), fclose(flp);
    }
}
//carregar partida
if(opcao == 2){
    printf("Digite o nome da partida\n"),scanf("%s",partida),
    strcpy(copy_partida,partida), strcat(partida,str1), strcat(copy_partida,str2);
    flp_carregar = fopen(copy_partida,"r+");
    for(i=0;i<20;i+=2){
        fscanf(flp_carregar,"%d %d ",&j,&m);
        positions_x[i] = j, positions_x[i+1] = m;
    }
    for(i=0;i<20;i+=2){
        fscanf(flp_carregar,"%d %d ",&j,&m);
        positions_y[i] = j, positions_y[i+1] = m;
    }

    fscanf(flp_carregar,"%d",&j), turno = j;
    fclose(flp);
}

if(opcao == 3){
    printf("Digite o nome da partida\n"), scanf("%s",partida), strcat(partida,str1);
    flp = fopen(partida,"r+");
}

if(opcao == 4){
    system("cls");
    printf("JOGO ENCERRADO.");
    return 0;
}

system("cls");
//loop principal do jogo
while(opcao == 1 || opcao == 2 || opcao ==3){
    int a, b, c = 0, replay, replay1, replay2;
    int direcao;
    char direcaoc;
    turno = trocaTurno(turno);

    printf("---------PULINHOS SERELEPES---------\n\n");
    printf("TURNO %d\n",turno);
    if(turno % 2 == 1){
        printf("        TURNO DO JOGADOR X\n\n");
    }
    else{
        printf("        TURNO DO JOGADOR O\n\n");
    }

    exibeTabuleiro(positions_x, positions_y);

    if(d != 2)
        escolhaPosicao(opcao);

    while(d == 0 || d == 2){
        if(d == 2){
            int escolha;
            if(!(opcao == 3)){
            printf("Digite 5 caso nao queira realizar novos pulos, digite 0 caso queira\n");
            scanf("%d",&escolha);
            if(escolha == 5){
                d = 0;
                break;}
                escolhaPosicao(opcao);
            }
            else{
                fscanf(flp,"%d %d ",&replay1, &replay2);
                for(i=0;i<19;i+=2){
                if(turno%2==1){
                if(positions_x[i] == replay1 && positions_x[i+1] == replay2){
                    peca_posicao_num[0] = replay1, peca_posicao_num[1] = replay2;
                    break;
                    }
                    }
                else{
                if(positions_y[i] == replay1 && positions_y[i+1] == replay2){
                    peca_posicao_num[0] = replay1, peca_posicao_num[1] = replay2;
                    break;
                    }
                    }
                }
                d = 0;
                break;
                }
                }


        if(!(opcao == 3)){
            printf("\nEscolha a direcao\n");
            scanf(" %c",&direcaoc);
            direcao = direcaoc - '0';
        }
        else{
            fscanf(flp,"%d ",&replay);
            direcao = replay;
        }
        if(turno%2==1){
            d = validaMovimento(positions_x, positions_y, peca_posicao_num, direcao);
            if(d != 0){
                if(d == 2)
                    turno -= 1;
                else
                    d = 0;
                historico[k] = direcao, k += 1;
                break;
            }
        }
        else{
            d = validaMovimento(positions_y, positions_x, peca_posicao_num, direcao);
            if(d != 0){
                if(d == 2)
                    turno -= 1;
                else
                    d = 0;
                historico[k] = direcao; k += 1;
                break;
            }
        }
    }

    if(turno%2==1){
        if(vitoria(positions_x, copy_x, copy_y, 0)==10){
                system("cls");
                printf("\n\n\n\n\n        O JOGADOR 'X' VENCEU!!!       ");
                break;
        }
    }
    else{
        if(turno == 50 ){
            if(vitoria(positions_x, copy_x, copy_y, 1)==1){
                system("cls");
                printf("\n\n\n\n\n        O JOGADOR 'O' VENCEU!!!       ");
                break;
        }
            else if(vitoria(positions_y, copy_y, copy_x, 1)==1){
                system("cls");
                printf("\n\n\n\n\n        O JOGADOR 'X' VENCEU!!!       ");
                break;
        }
        if(vitoria(positions_y, copy_y, copy_x, 0)==10){
                system("cls");
                printf("\n\n\n\n\n        O JOGADOR 'O' VENCEU!!!       ");
                break;
        }
    }
    }
    //for(i=0;i<9;i++){
    //printf("%d \n",historico[i]);}
    if(opcao == 1 || opcao == 2){
        flp = fopen(partida,"a+"),
        fprintf(flp,"%d %d %d ",historico[k-3],historico[k-2],historico[k-1]);
        fclose(flp);
        //carregar um jogo
        flp_carregar = fopen(copy_partida,"w+");
        for(i=0;i<40;i++){
            if(i<20)
                fprintf(flp_carregar,"%d ",positions_x[i]);
            else
                fprintf(flp_carregar,"%d ",positions_y[i-20]);
            }
        fprintf(flp_carregar,"%d",turno);
        fclose(flp_carregar);
        }

    if(opcao == 3){
        int ii, jj, kk;
        for(k=0;kk<2000;kk++){
            exibeTabuleiro(positions_x, positions_y);
            char falso_tabuleiro[100][100];
            for(ii=0;ii<100;ii++){
                for(jj=0;jj<100;jj++){
                    falso_tabuleiro[ii][jj]=' ';
                }
            }
            for(ii=0;ii<100;ii++){
                for(jj=0;jj<100;jj++){
                    printf("%c",falso_tabuleiro[ii][jj]=' ');
                }
            }
            system("cls");
            }
    }

    system("cls");
}
return 0;
}

char exibeTabuleiro(int *positions_x, int *positions_y){
/*
	 A	 B	 C 	 D 	 E	 F	 G	 H
    ---.---.---.---.---.---.---.---.
  1  X | X | X | X |   |   |   |   |
	---.---.---.---.---.---.---.---.
  2  X | X | X |   |   |   |   |   |
    ---.---.---.---.---.---.---.---.
  3  X | X |   |   |   |   |   |   |
    ---.---.---.---.---.---.---.---.
  4  X |   |   |   |   |   |   |   |
    ---.---.---.---.---.---.---.---.
  5    |   |   |   |   |   |   | O |
    ---.---.---.---.---.---.---.---.
  6    |   |   |   |   |   | O | O |
    ---.---.---.---.---.---.---.---.
  7    |   |   |   |   | O | O | O |
    ---.---.---.---.---.---.---.---.
  8    |   |   |   | O | O | O | O |
	---.---.---.---.---.---.---.---.
*/

int i, j, k;
char tabuleiro[9][9];
int veri = 0;

for(i=0;i<9;i++){
	for(j=0;j<9;j++){
	tabuleiro[i][j]=' ';
	}
}
tabuleiro[0][1]='a', tabuleiro[0][2]='b', tabuleiro[0][3]='c', tabuleiro[0][4]='d', tabuleiro[0][5]='e', tabuleiro[0][6]='f',
tabuleiro[0][7]='g', tabuleiro[0][8]='h', tabuleiro[1][0]='1', tabuleiro[2][0]='2', tabuleiro[3][0]='3',
tabuleiro[4][0]='4', tabuleiro[5][0]='5', tabuleiro[6][0]='6', tabuleiro[7][0]='7', tabuleiro[8][0]='8';

for(i=0;i<9;i++){
	for(j=0;j<9;j++){
        veri = 0;
		if(i!=0){
            for(k=0;k<19;k+=2){
                if(positions_x[k]==j && positions_x[k+1]==i){
                    tabuleiro[i][j] = 'x';
                    printf(" X |");
                    veri = 1;
                    break;
                }
            }
            for(k=0;k<19;k+=2){
                if(positions_y[k]==j && positions_y[k+1]==i){
                    tabuleiro[i][j] = 'o';
                    printf(" O |");
                    veri = 1;
                    break;
                }
            }
            if(veri == 0){
            printf(" %c |",tabuleiro[i][j]);
            }
		}
		else
			printf(" %c  ",tabuleiro[i][j]);
	}
	printf("\n");
	for(j=0;j<9;j++){
		if(j!=0)
			printf("---.");
		else
			printf("    ");
	}
	printf("\n");
}
return **tabuleiro;
}

char posicaoMatriz(char *str, int n){
int posicao_let, posicao_num;

strlwr(str);

if(n == 0){
    posicao_let = str[0] - 'a' + 1;
    return posicao_let;
}
else{
    posicao_num = str[1] - '0';
    return posicao_num;
}
}

int trocaTurno(int num){
num += 1;
return num;
}

int validaPeca(int *positions_x, int *positions_y, int *peca_posicao_num, int turno){
int k;
//verifica se o jogador X pode mover determinada peça
if(turno % 2 == 1){
    for(k=0;k<19;k+=2){
        if(positions_x[k] == peca_posicao_num[0] && positions_x[k+1] == peca_posicao_num[1]){
            return 1;
            }
        }
    printf("\nEssa casa nao possui uma peca que voce pode mover ou a casa e invalida.\n");
    return 0;
    }
//verifica se o jogador O pode mover determinada peça
else{
    for(k=0;k<19;k+=2){
        if(positions_y[k] == peca_posicao_num[0] && positions_y[k+1] == peca_posicao_num[1]){
            return 1;
            }
        }
    printf("\nEssa casa nao possui uma peca que voce pode mover ou a casa e invalida.\n");
    return 0;
    }
}

int validaMovimento(int *positions_x, int *positions_y, int *peca_posicao_num, int direcao){
int a, b, c, d, i, j, k;

if(direcao == 8){
    a = 0, b = -1, c = 1;
}
else if(direcao == 6){
    a = 1, b = 0, c = 0;
}
else if(direcao == 2){
    a = 0, b = 1, c = 1;
}
else if(direcao == 4){
    a = -1, b = 0, c = 0;
}
else if(direcao == 7){
    a = -1, b = -1;
}
else if(direcao == 9){
    a = 1, b = -1;
}
else if(direcao == 3){
    a = 1, b = 1;
}
else if(direcao == 1){
    a = -1, b = 1;
}
else if(direcao > 9 || direcao <1){
    printf("Direcao invalida\n");
    return 0;
}

if(direcao == 8 || direcao == 4){
    for(k=0;k<19;k+=2){
        if(positions_x[k] == peca_posicao_num[0] && positions_x[k+1] == peca_posicao_num[1]){
            if(positions_x[k+c]>1){
                for(i=0;i<19;i+=2){
                    if((positions_x[i] == (peca_posicao_num[0]+a) && positions_x[i+1] == (peca_posicao_num[1]+b))||
                       (positions_y[i] == (peca_posicao_num[0]+a) && positions_y[i+1] == (peca_posicao_num[1]+b))){
                        if(positions_x[k+c]>2){
                            for(j=0;j<19;j+=2){
                                if((positions_x[j] == (peca_posicao_num[0]+a+a) && positions_x[j+1] == (peca_posicao_num[1]+b+b))||
                                   (positions_y[j] == (peca_posicao_num[0]+a+a) && positions_y[j+1] == (peca_posicao_num[1]+b+b))){
                                        printf("Nao e possivel mover a peca nessa direcao");
                                        return 0;
                                   }
                            }
                            positions_x[k+c] += a + a + b + b;
                            return 2;
                        }
                        else{
                            printf("Nao e possivel mover a peca nessa direcao");
                            return 0;
                        }
                        }
                }
                positions_x[k+c] += a + b;
                return 1;
            }
            else{
                printf("Nao e possivel mover a peca nessa direcao");
                return 0;
            }
        }
    }
}

else if(direcao == 2 || direcao == 6){
    for(k=0;k<19;k+=2){
        if(positions_x[k] == peca_posicao_num[0] && positions_x[k+1] == peca_posicao_num[1]){
            if(positions_x[k+c]<8){
                for(i=0;i<19;i+=2){
                    if((positions_x[i] == (peca_posicao_num[0]+a) && positions_x[i+1] == (peca_posicao_num[1]+b))||
                       (positions_y[i] == (peca_posicao_num[0]+a) && positions_y[i+1] == (peca_posicao_num[1]+b))){
                        if(positions_x[k+c]<7){
                            for(j=0;j<19;j+=2){
                                if((positions_x[j] == (peca_posicao_num[0]+a+a) && positions_x[j+1] == (peca_posicao_num[1]+b+b))||
                                   (positions_y[j] == (peca_posicao_num[0]+a+a) && positions_y[j+1] == (peca_posicao_num[1]+b+b))){
                                        printf("Nao e possivel mover a peca nessa direcao");
                                        return 0;
                                   }
                            }
                            positions_x[k+c] += a + a + b + b;
                            return 2;
                        }
                        else{
                            printf("Nao e possivel mover a peca nessa direcao");
                            return 0;
                        }
                        }
                }
                positions_x[k+c] += a + b;
                return 1;
            }
            else{
                printf("Nao e possivel mover a peca nessa direcao");
                return 0;
            }
        }
    }
}

else if(direcao == 7){
    for(k=0;k<19;k+=2){
        if(positions_x[k] == peca_posicao_num[0] && positions_x[k+1] == peca_posicao_num[1]){
            if(positions_x[k]>1 && positions_x[k+1]>1){
                for(i=0;i<19;i+=2){
                    if((positions_x[i] == (peca_posicao_num[0]+a) && positions_x[i+1] == (peca_posicao_num[1]+b))||
                       (positions_y[i] == (peca_posicao_num[0]+a) && positions_y[i+1] == (peca_posicao_num[1]+b))){
                        if(positions_x[k]>2 && positions_x[k+1]>2){
                            for(j=0;j<19;j+=2){
                                if((positions_x[j] == (peca_posicao_num[0]+a+a) && positions_x[j+1] == (peca_posicao_num[1]+b+b))||
                                   (positions_y[j] == (peca_posicao_num[0]+a+a) && positions_y[j+1] == (peca_posicao_num[1]+b+b))){
                                        printf("Nao e possivel mover a peca nessa direcao");
                                        return 0;
                                   }
                            }
                            positions_x[k] += a + a, positions_x[k+1] += b + b;
                            return 2;
                        }
                        else{
                            printf("Nao e possivel mover a peca nessa direcao");
                            return 0;
                        }
                        }
                }
                positions_x[k] += a, positions_x[k+1] += b;
                return 1;
            }
            else{
                printf("Nao e possivel mover a peca nessa direcao");
                return 0;
            }
        }
    }
}

else if(direcao == 9){
    for(k=0;k<19;k+=2){
        if(positions_x[k] == peca_posicao_num[0] && positions_x[k+1] == peca_posicao_num[1]){
            if(positions_x[k]<8 && positions_x[k+1]>1){
                for(i=0;i<19;i+=2){
                    if((positions_x[i] == (peca_posicao_num[0]+a) && positions_x[i+1] == (peca_posicao_num[1]+b))||
                       (positions_y[i] == (peca_posicao_num[0]+a) && positions_y[i+1] == (peca_posicao_num[1]+b))){
                        if(positions_x[k]<7 && positions_x[k+1]>2){
                            for(j=0;j<19;j+=2){
                                if((positions_x[j] == (peca_posicao_num[0]+a+a) && positions_x[j+1] == (peca_posicao_num[1]+b+b))||
                                   (positions_y[j] == (peca_posicao_num[0]+a+a) && positions_y[j+1] == (peca_posicao_num[1]+b+b))){
                                        printf("Nao e possivel mover a peca nessa direcao");
                                        return 0;
                                   }
                            }
                            positions_x[k] += a + a, positions_x[k+1] += b + b;
                            return 2;
                        }
                        else{
                            printf("Nao e possivel mover a peca nessa direcao");
                            return 0;
                        }
                        }
                }
                positions_x[k] += a, positions_x[k+1] += b;
                return 1;
            }
            else{
                printf("Nao e possivel mover a peca nessa direcao");
                return 0;
            }
        }
    }
}

else if(direcao == 3){
    for(k=0;k<19;k+=2){
        if(positions_x[k] == peca_posicao_num[0] && positions_x[k+1] == peca_posicao_num[1]){
            if(positions_x[k]<8 && positions_x[k+1]<8){
                for(i=0;i<19;i+=2){
                    if((positions_x[i] == (peca_posicao_num[0]+a) && positions_x[i+1] == (peca_posicao_num[1]+b))||
                       (positions_y[i] == (peca_posicao_num[0]+a) && positions_y[i+1] == (peca_posicao_num[1]+b))){
                        if(positions_x[k]<7 && positions_x[k+1]<7){
                            for(j=0;j<19;j+=2){
                                if((positions_x[j] == (peca_posicao_num[0]+a+a) && positions_x[j+1] == (peca_posicao_num[1]+b+b))||
                                   (positions_y[j] == (peca_posicao_num[0]+a+a) && positions_y[j+1] == (peca_posicao_num[1]+b+b))){
                                        printf("Nao e possivel mover a peca nessa direcao");
                                        return 0;
                                   }
                            }
                            positions_x[k] += a + a, positions_x[k+1] += b + b;
                            return 2;
                        }
                        else{
                            printf("Nao e possivel mover a peca nessa direcao");
                            return 0;
                        }
                        }
                }
                positions_x[k] += a, positions_x[k+1] += b;
                return 1;
            }
            else{
                printf("Nao e possivel mover a peca nessa direcao");
                return 0;
            }
        }
    }
}

else if(direcao == 1){
    for(k=0;k<19;k+=2){
        if(positions_x[k] == peca_posicao_num[0] && positions_x[k+1] == peca_posicao_num[1]){
            if(positions_x[k]>1 && positions_x[k+1]<8){
                for(i=0;i<19;i+=2){
                    if((positions_x[i] == (peca_posicao_num[0]+a) && positions_x[i+1] == (peca_posicao_num[1]+b))||
                       (positions_y[i] == (peca_posicao_num[0]+a) && positions_y[i+1] == (peca_posicao_num[1]+b))){
                        if(positions_x[k]>2 && positions_x[k+1]<7){
                            for(j=0;j<19;j+=2){
                                if((positions_x[j] == (peca_posicao_num[0]+a+a) && positions_x[j+1] == (peca_posicao_num[1]+b+b))||
                                   (positions_y[j] == (peca_posicao_num[0]+a+a) && positions_y[j+1] == (peca_posicao_num[1]+b+b))){
                                        printf("Nao e possivel mover a peca nessa direcao");
                                        return 0;
                                   }
                            }
                            positions_x[k] += a + a, positions_x[k+1] += b + b;
                            return 2;
                        }
                        else{
                            printf("Nao e possivel mover a peca nessa direcao");
                            return 0;
                        }
                        }
                }
                positions_x[k] += a, positions_x[k+1] += b;
                return 1;
            }
            else{
                printf("Nao e possivel mover a peca nessa direcao");
                return 0;
            }
        }
    }
}

}

int vitoria(int *positions_x, int *copy_x, int *copy_y, int n){
//condicao 1
int i,j,num = 0;

if(n==0){
    for(i = 0;i<19;i+=2){
        for(j = 0;j<19;j+=2){
            if(positions_x[i] == copy_y[j] && positions_x[i+1] == copy_y[j+1]){
                num += 1;
                break;
            }
        }
    }
    return num;
}
//condicao 2
if(n==1){
    for(i = 0;i<19;i+=2){
        for(j = 0;j<19;j+=2){
            if(positions_x[i] == copy_x[j] && positions_x[i+1] == copy_x[j+1]){
                return 1;
            }
        }
    }
    return 0;
}
}

int escolhaPosicao(int opcao){
    int c = 0, replay1, replay2;
    char *peca_posicao[2];
    while(c == 0){
            if(!(opcao == 3)){
                printf("\nEscolha a peca\n");
                scanf("%s",peca_posicao);
                peca_posicao_num[0] = posicaoMatriz(peca_posicao, 0), peca_posicao_num[1] = posicaoMatriz(peca_posicao, 1);
                c = validaPeca(positions_x, positions_y, peca_posicao_num, turno);
                if(c==1){
                    historico[k] = peca_posicao_num[0], historico[k+1] = peca_posicao_num[1], k += 2;
                    break;
                }
            }
            else{
                fscanf(flp,"%d %d ",&replay1, &replay2);
                peca_posicao_num[0] = replay1, peca_posicao_num[1] = replay2;
                c = 1;
            }
        }
}
















