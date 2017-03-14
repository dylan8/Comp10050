#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>


int key1;
char arr[7][3][20];
int findElement(int key, char slotInformation[7][3][20];);

int main(void) {
    int ini;
    int both =0;;
    int inputCount =0;
    char line[1000];
    char slotInformation[7][3][20];
    char sortedSlots[7][3][20];
    int i =0;
    int j;
    char player[10][2][20];
    char blank[100];
    int numPlay;
    int typePlay;
    const char One[] = "Elf";
    const char Two[] = "Human";
    const char Three[] = "Ogre";
    const char Four[] = "Wizard";

    printf("Please Enter The Number of Players Playing (Max 6)\n");

    scanf("%d", &numPlay);

    printf("Now Please Enter The Names of Players Playing\n");

    for (i=0; i<numPlay; i++){

        scanf("%s", &player[i][1]);

    }
    for (i=0; i<numPlay; i++){

        printf("%s", player[i][1]);

    }
    printf("\n\nFor The Following Please enter\n1 for Type: Elf\n2 for Type: Human\n3 for Type: Ogre\n4 for Type: Wizrd\n");
    for (i=0; i<numPlay; i++){
        printf("Now Please Enter The Type of %s\n", player[i][1]);
        scanf("%d", &typePlay);

        if (typePlay == 1){
            sscanf(One, "%s", player[i][2]);
        }
        if (typePlay == 2){
            sscanf(Two, "%s", player[i][2]);
        }
        if (typePlay == 3){
            sscanf(Three,"%s", player[i][2]);
        }
        if (typePlay == 4){
            sscanf(Four, "%s", player[i][2]);
        }

    }
    printf("The Players Are:");
    for (i=0; i<numPlay; i++){
        printf("%s %s\n", player[i][1],player[i][2]);
    }
    return 0;
}
