#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
struct nguoichoi
{
    char ten[24];
    int solandoan;
};
void inrakyluc(struct nguoichoi* player,int dem)
{
    for (int i=0;i<dem;i++)
    {
        printf("kỷ lục %d *****\n tên người choi:%s \n số lần đoán %d",i,player[i].ten,player[i].solandoan);
    }
}
void swap(struct nguoichoi *a, struct nguoichoi *b) {
    struct nguoichoi temp = *a;
    *a = *b;
    *b = temp;
}
int taosongaunhien()
{
     srand(time(NULL));
    int randomNumber = rand() % 9000 + 1000; 
    return randomNumber;
}
void sosanhketqua(int number[], int *arr, int *arrrd) {
    for (int i = 0; i < 4; i++) 
    { 
        if (number[i] == arrrd[i]) 
        {
            arr[i] = arrrd[i];
        }
    }
}
void hamsapxep(struct nguoichoi* playerds, int dem) {
    for(int i = 0; i < dem - 1; i++) {
        for(int j = 0; j < dem - 1; j++) {
            if(playerds[j].solandoan > playerds[j + 1].solandoan) {
                swap(&playerds[j], &playerds[j + 1]);
            }
        }
    }
}
void tachSo(int numberrandom, int *arr) 
{
    arr[0] = numberrandom / 1000;        
    arr[1] = (numberrandom / 100) % 10;  
    arr[2] = (numberrandom / 10) % 10;   
    arr[3] = numberrandom % 10;          
}
void luuvaofile(struct nguoichoi player)
{
    struct nguoichoi playerds[5];
    FILE *file = fopen("danhsach.txt", "r+");
    if (file == NULL) {
        printf("Không thể mở tệp tin.\n");
        exit(1);
    }
    int demmoi=0;
    int dem=0;
    while (fread(playerds, sizeof(struct nguoichoi), 1, file) == 1) 
    {
      dem++;
    }
    if(dem<5)
    {
        fseek(file, 0, SEEK_END);
        fwrite(&player,sizeof(struct nguoichoi),1,file);
         fseek(file, 0, SEEK_SET);
         hamsapxep(playerds,dem);
    }
    else if(dem=5)
    {
        while (fread(playerds, sizeof(struct nguoichoi), 1, file) == 1) 
            {
            }
                  hamsapxep(playerds,5);

    for(int i=0;i<5;i++)
    {
        if(player.solandoan>playerds[i].solandoan && player.solandoan<playerds[i+1].solandoan)
        {
            playerds[i+1]=player;
            i++;
            for (int k = 3; k >= i; k--) 
            {
                    playerds[k + 1] = playerds[k];
            }
        }
        else if(player.solandoan=playerds[i].solandoan )
        {
            playerds[i+1]=player;
            i++;
            for (int k = i; k <5; k++)
{
                    playerds[k + 1] = playerds[k];
            }
        }
    }
    
    }
inrakyluc(playerds,dem);
 fclose(file);
}
void inraketqua(int* arr,int* arrrd,int* dem)
{
     while (arr[0] == -1 || arr[1] == -1 || arr[2] == -1 || arr[3] == -1) 
     { 
       nhap:
        printf("Nhập 4 số bạn chọn để đoán (0-9): ");
        int number[4];
        for (int i=0;i<4;i++)
        {
            scanf("%d", &number[i]);
            if(number[i]>9 || number[i]<0)
            {
             printf("giá trị nhập không hợp lệ\n");
                goto nhap;
            }
            (*dem)++;
        }
        sosanhketqua(&number, arr, arrrd);
        for (int i = 0; i < 4; i++) 
        {
            if (arr[i] != -1) 
            {
                printf("%d", arr[i]);
            } 
            else
            {
                printf("_");
            }
        }
        printf("\n");
        printf("số lần bạn đã đoán:%d\n",*dem);
        if(number!=arrrd[0] && number!=arrrd[1] && number!=arrrd[2] && number!=arrrd[3]  )
        printf("nhập sai vui lòng nhập lại\n");
    }
}
int main() {
    char name[24];
    int dem=0;
    int* demptr=&dem;
    int randomNumber=taosongaunhien();
  
    int arrrd[4];
    tachSo(randomNumber, arrrd);
     printf("Số ngẫu nhiên là: %d\n", randomNumber);
     float sacxuat=sacxuatcuabaitoan(arrrd);
    printf("sác xuất bài toán  là: %f %\n", sacxuat*100);
    int arr[4] = {-1, -1, -1, -1}; 
    printf("Vui lòng nhập tên của bạn:");
    fgets(name, sizeof(name), stdin);
    inraketqua(arr,arrrd,demptr);
    struct nguoichoi nguoichoi1;
    strcpy(nguoichoi1.ten,name);
    nguoichoi1.solandoan=dem;
    luuvaofile(nguoichoi1);
    return 0;
}