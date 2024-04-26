#include <stdio.h>

// int main(void) {
//     // int arr[256] = {0};
//     // FILE* file = open();
//     // for (int i = 0; i < 5; i++) {
//     //     fscanf(file, "%d ", arr+i);
//     // }
//     // for (int i = 0; i < 5; i++) {
//     //     printf("%d ", arr[i]);
//     // }
//     // puts("");
//     // return 0;
    
// }
#include <stdio.h>

int main() {
    FILE *file;
    int arr1[8]; // 假設每行有8個整數
    int arr3[8];
    int arr2[8];
    int i;

    file = fopen("test1.txt", "r"); // 打開文件用於讀取
    if (file == NULL) {
        printf("無法打開文件\n");
        return 1;
    }

    // 讀取第一行到 arr1
    
    // for (i = 0; i < 8; i++) {
    //     if(!fscanf(file, "%d")) break;
    //     fscanf(file, "%d", &arr1[i]);
    // }

    // // 讀取第二行到 arr2
    // for (i = 0; i < 8; i++) {
    //     fscanf(file, "%d", &arr2[i]);
    // }
    // int index_a = 0;
    // while (fscanf(file, "%d", &arr1[index_a]) == 1) {
    //     index_a++;
    //     printf("ascanf\n");
    // }
    // printf("%d\n",index_a);
    // int index_b = 0;
    // while (fscanf(file, "%d", &arr2[index_b]) == 1) {
    //     index_b++;
    //     printf("bscanf\n");
    // }
    int index_a = 0;
    char ch;
    do {
    fscanf(file, "%d%c", &arr1[index_a], &ch);
    printf("ascanf\n");
    index_a++;
    } while(ch != '\n' && ch != EOF);

    // Reset ch
    ch = '\0';

    // Read the second line into arr2
    int index_b = 0;
    while ((ch != '\n' && ch != EOF) && fscanf(file, "%d%c", &arr2[index_b], &ch) == 2) {
    printf("bscanf\n");
    index_b++;
    }
    printf("%d\n",index_a);
    printf("%d\n",index_b);

    fclose(file); // 關閉文件

    // 打印讀取的數據以確認
    printf("第一行數據: ");
    for (i = 0; i < 8; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n第二行數據: ");
    for (i = 0; i < 8; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");

    return 0;
}
