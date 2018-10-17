#include <stdio.h>
#include <stdlib.h>

void validaCedula();
void validaSaque(int *valores);

int main(){
	validaCedula();
}

void validaCedula(){
	int notas[6] = {2,5,10,20,50,100};
	int resultado[2],temp[2];
	int confere=0,b1,b2,b3, maior,menor,meio;
	
	system("cls");	
	printf("Bandeja 1: ");
	scanf("%d",&b1);
	printf("Bandeja 2: ");
	scanf("%d",&b2);
	printf("Bandeja 3: ");
	scanf("%d",&b3);
	
	if(b1 == 2 || b1 == 5 || b1 == 10 || b1 == 20 || b1 == 50 || b1 == 100){
		if(b2 == 2 || b2 == 5 || b2 == 10 || b2 == 20 || b2 == 50 || b2 == 100){
			if(b3 == 2 || b3 == 5 || b3 == 10 || b3 == 20 || b3 == 50 || b3 == 100){
				printf("Verificacao OK\n");
			} else {
				printf("Valores invalidos!\n");
				system("pause");
				validaCedula();
			}
		} else {
			printf("Valores invalidos!\n");
			system("pause");
			validaCedula();
		}
	} else {
		printf("Valores invalidos!\n");
		system("pause");
		validaCedula();
	}
	
	if(b1 > b2 && b1 > b3){ //Organizar as cedulas da maior para menor
		maior = b1;			//Eu juro que tentei fazer com bubble sort mas nao funcionava de jeito nenhum, desculpa.
		if(b2 > b3){
			meio = b2;
			menor = b3;
		} else {
			meio = b3;
			menor = b2;
		}
	} else if(b2 > b1 && b2 > b3){
		maior = b2;
		if(b1 > b3){
			meio = b1;
			menor = b3;
		} else {
			meio = b3;
			menor = b1;
		}
	} else {
		maior = b3;
		if(b1 > b2){
			meio = b1;
			menor = b2;
		} else {
			meio = b2;
			menor = b1;
		}
	}
	resultado[0] = maior;
	resultado[1] = meio;
	resultado[2] = menor;
		
	validaSaque(resultado);
}

void validaSaque(int *valores){
	int saque, i=0, bandeja1 = 250, bandeja2 = 250, bandeja3 = 250, escolha, saques_realizados=0, total_sacado=0,resta=0, saques_malsucedidos=0;
	int opumx, opumy, opumz,opdoisx, opdoisy, opdoisz,optresx, optresy, optresz;
	int b1=0,b2=0,b3=0;
	int x, y,z,cont;
	
	FILE *arqSaida;
	arqSaida = fopen("saida.txt","w");
	while(1){
		system("cls");
		printf("----------ORGANIZANDO----------\n");
		for(cont=0;cont<3;cont++){
			printf("Bandeja %d: %d\n",cont+1,valores[cont]);
		}
		printf("Saque desejado (0) para sair: ");
		scanf("%d",&saque);
		if(saque <= 0){
			resta = bandeja1 * valores[0] + bandeja2 * valores[1] + bandeja3 * valores[2];
			printf("----------SAINDO----------\n");
			fprintf(arqSaida,"\n\n\nQuantidade de saques bem sucedidos: %d\nQuantidade de saques mal sucedidos: %d\n\n",saques_realizados,saques_malsucedidos);
			fprintf(arqSaida,"Total sacado: R$ %d\n\n",total_sacado);
			fprintf(arqSaida,"Quantidade sacada da bandeja (1): %d\nQuantidade sacada da bandeja (2): %d\nQuantidade sacada da bandeja (3): %d\n\n",b1,b2,b3);
			fprintf(arqSaida,"Quantidade remanescente na bandeja (1): %d\nQuantidade remanescente na bandeja (2): %d\nQuantidade remanescente na bandeja (3): %d\n\n", bandeja1,bandeja2,bandeja3);
			fprintf(arqSaida,"Total restante no caixa: R$ %d\n", resta);
			system("pause");
			exit(0);
		}else if(saque >= 2500){
			printf("Resultado: Erro - valor desejado excede R$ 2.500,00\n");
			fprintf(arqSaida,"SAQUE NUMERO %d - VALOR R$ %d\nResultaldo: Erro - valor desejado excede R$ 2.500,00\n\n",saques_realizados+1,saque);
			saques_realizados++;
			saques_malsucedidos += 1;
			system("pause");
			continue;
		} else{
			fprintf(arqSaida,"SAQUE NUMERO %d - VALOR: R$ %d\nOpcoes mostradas:\n",saques_realizados+1,saque);
			for (x = saque/valores[0]; x >= 0; --x){
		        for (y = saque/valores[1]; y >= 0; --y){
		            for (z = saque/valores[2]; z >= 0; --z){
		                if (saque == (x * valores[0] + y*valores[1] + z*valores[2])){
		                    printf("OPCAO %d) %d nota(s) de R$ %d + %d nota(s) de R$ %d + %d nota(s) de R$ %d\n",i+1, x,valores[0], y,valores[1], z,valores[2]);
		                    i++;
		                    if(i==1){
		                    	opumx = x;
		                    	opumy = y;
		                    	opumz = z;
		                	} else if(i==2){
		                		opdoisx = x;
		                		opdoisy = y;
		                		opdoisz = z;
							} else if(i==3){
								optresx = x;
								optresy = y;
								optresz = z;
								break;
							}
							fprintf(arqSaida,"OPCAO %d) %d nota(s) de R$ %d + %d nota(s) de R$ %d + %d nota(s) de R$ %d\n",i, x,valores[0], y,valores[1], z,valores[2]);
		                }
		            }
		            if(i>=3){
		            	break;
					}
		        }
		        if(i>=3){
		        	break;
				}
		    }
		    if(i == 0){
		    	printf("Nao foi possivel realizar o saque deste valor!\n");
		    	saques_malsucedidos += 1;
		    	fprintf(arqSaida,"Saque mal sucedido!\n\n");
		    	system("pause");
		    	continue;
			}else if(i<3){
		       	printf("Nao existem mais combinacoes possiveis\n");
			}
		}
		
		printf("Escolha uma opcao: ");
		scanf("%d",&escolha);
		if(escolha > i){
			printf("Opcao invalida!\n");
			saques_malsucedidos += 1;
			fprintf(arqSaida,"Saque mal sucedido!\n\n");
			system("pause");
			continue;
		} else if(escolha == 1){
			bandeja1 -= opumx;
			bandeja2 -= opumy;
			bandeja3 -= opumz;
			b1 += opumx;
			b2 += opumy;
			b3 += opumz;
			saques_realizados += 1;
			total_sacado += saque;
			printf("Saque realizado com sucesso!\n");
		} else if(escolha == 2){
			bandeja1 -= opdoisx;
			bandeja2 -= opdoisy;
			bandeja3 -= opdoisz;
			b1 += opdoisx;
			b2 += opdoisy;
			b3 += opdoisz;
			saques_realizados += 1;
			total_sacado += saque;
			printf("Saque realizado com sucesso!\n");
		} else if(escolha == 3){
			bandeja1 -= optresx;
			bandeja2 -= optresy;
			bandeja3 -= optresz;
			b1 += optresx;
			b2 += optresy;
			b3 += optresz;
			saques_realizados += 1;
			total_sacado += saque;
			printf("Saque realizado com sucesso!\n");
		}
		fprintf(arqSaida,"Opcao escolhida: %d\n\n",escolha);
		i=0;
		system("pause");
	}
}
