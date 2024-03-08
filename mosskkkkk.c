#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct nguoichoi
{
    char ten[24];
    int solandoan;
};
struct nguoichoi playerarray[100]; //initializize struct nguoichoi have 100 element
int count = 0;
struct nguoichoi player;

int taosongaunhien() //initializize random number

{  
    srand(time(NULL));
    int randomNumber = rand() % 9000 + 1000;
    return randomNumber;
}
void swap(struct nguoichoi *a, struct nguoichoi *b) {  // swap address struct
    struct nguoichoi temp = *a;
    *a = *b;
    *b = temp;
}

void sosanhketqua(int number[], int *arr, int *arrrd) 
{
    for (int i = 0; i < 4; i++) 
    {
        if (number[i] == arrrd[i]) 
        {
            arr[i] = arrrd[i];
        }
    }
}

void tachSo(int numberrandom, int *arr) 
{  // seperate number into array
    arr[0] = numberrandom / 1000;
    arr[1] = (numberrandom / 100) % 10;
    arr[2] = (numberrandom / 10) % 10;
    arr[3] = numberrandom % 10;
}

void loaddata() {
    FILE *file = fopen("danhsach.txt", "r");
    if (file == NULL) {
        printf("can't open file.\n");
        exit(1);
    }
    count=0;
    while (fscanf(file, "%s %d", playerarray[count].ten, &playerarray[count].solandoan) == 2) 
    {
        count++;                            // Go through each element in the file and count element
    }
    fclose(file);
}

void luuvaofilevathem() {
    FILE *file = fopen("danhsach.txt", "w"); // open file "danhsach.txt" "with writing mode
    if (file == NULL) {
        printf("can't open file.\n");
        exit(1);
    }
    if(count<100)
    {
    playerarray[count] = player;
    count++;

    for (int i = 0; i < count; i++) {            // arrange element base on total guesses
        for (int j = 0; j < count - i - 1; j++) {
            if (playerarray[j].solandoan > playerarray[j + 1].solandoan) {
                swap(&playerarray[j], &playerarray[j + 1]);
            }
        }
    }
    // write player's data to file
    if (count == 0) {
        fprintf(file, "%s %d\n", playerarray[0].ten, playerarray[0].solandoan);                     
    }
    else {
            for (int i = 0; i < count; i++)                                                             
                {
                    fprintf(file, "%s %d\n", playerarray[i].ten, playerarray[i].solandoan);
                }
        }

    }
    fclose(file);
}

void inrakyluc() 
{   // print top five data after arrange from file
    printf("TOP 5 record:\n");
    if(count >5)
    {
        for (int i = 0; i < 5; i++) 
        {
             float ti_le_doan = (float) 1 / playerarray[i].solandoan * 100;
            printf("record %d *****user name: %s \n total number of guesses: %d\n lucky ratio: %.2f%%\n", i + 1, playerarray[i].ten, playerarray[i].solandoan, ti_le_doan);
        }
    }
    else if(count<=5)
    {
        for (int i = 0; i < count; i++) 
        {
             float ti_le_doan = (float) 1 / playerarray[i].solandoan * 100;
printf("Record %d *****\n user name: %s\n total number of guesses: %d\n lucky ratio: %.2f%%\n", i + 1, playerarray[i].ten, playerarray[i].solandoan, ti_le_doan);
        }
    }
}

void inraketqua(int *arr, int *arrrd) 
{
    // compare randomNumber and number which user enters 
    int array[4]={-1, -1, -1, -1};
    {
        for (int i = 0; i < 4; i++) 
        {
            if (arr[i] == arrrd[i]) 
                {
                    array[i] = arrrd[i];
                }
        }
    }
     for (int i = 0; i < 4; i++) 
     {
            if (array[i] != -1) {
                printf("%d", array[i]);
            }
            else {
printf("_");
            }
    }
        printf("\n");
        
    
}

int main() {
    int dem = 0;
    int arrrd[4];
    int arr[4];
    char key;
    printf("START GAME !!!!!!!\n");
    do {
        // request user enter input to play a game 
        char name[24];
        printf("enter your name: ");
        fgets(name, sizeof(name), stdin);
        int randomNumber = taosongaunhien();
        printf("random number is: %d\n", randomNumber);
        int number;
        nhap:
        while(number != randomNumber) {
            printf("enter your number(4 digit): ");
            scanf("%d", &number);
            if (number < 1000 || number > 9999 ) {
                printf("Invalid value, please enter a 4-digit number.\n");
                continue;
            }
            dem++;
            tachSo(randomNumber, arrrd);
            tachSo(number, arr);
            inraketqua(arr, arrrd);
            printf("Total guesses: %d\n", dem);
            
        }
        // assign value to struct and print record
        strcpy(player.ten, name);
        player.solandoan = dem;
        loaddata();
        luuvaofilevathem();
        printf("Do you wanna see the record (y/n)");
        char k;
        scanf(" %c",&k);
        if(k=='y') 
           {
               inrakyluc();
           }
        else;
        // Ask the user if he wants to continue playing
        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &key);
        getchar();
        dem = 0;
    } while (key == 'y');
    printf("END GAME !!!");

    return 0;
}