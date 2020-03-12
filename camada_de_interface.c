#include <stdio.h>
void main(){
	int i, j;
	for (i = 0; i < 8; i++){
		if (i == 0){
			for (j = 0; j < 8; j++){
				if (j == 7){
					printf("2");
				}
				else printf(".");
			}
			printf("\n");
		}
		else if (i == 7){
			for (j = 0; j < 8; j++){
				if (j == 0){
					printf("1");
				}
				else printf(".");
			}
			printf("\n");
		}
		else if (i == 4){
			for (j = 0; j < 8; j++){
				if (j == 4){
					printf("B");
				}
				else printf(".");
			}
			printf("\n");
		}
		else{
			for (j = 0; j < 8; j++){
			printf(".");
			}
			printf("\n");
		}
	}
}