#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// the data structure of a polynomial node
typedef struct Node{
    int coef;
    int expo;
    struct Node *next;
}Node;
// helper function to print out the polynomial
// input polynomial linked list head
void print_poly(Node *head){
    printf("\n");
    if(head){
        while(head->next){
            printf("(%d)X^%d + ",head->coef,head->expo);
            head = head->next;
        }
        printf("(%d)X^%d",head->coef,head->expo);
    }
    else
        printf("0");
    printf("\n");
}
// create a new polynomial node and return the pointer point to the node
Node* new_node(int coef, int expo){
    Node *node = malloc(sizeof(Node));
    node->coef = coef;
    node->expo = expo;
    node->next = NULL;
    return node;
}

// construct polynomial and return the pointer point to the head of polynomial
// You can Customize the input of this function 
Node* construct(int arr[], int listsize ){
    if(listsize < 2 && arr == NULL)return NULL;
    Node *head = new_node(arr[0], arr[1]);
    for(int i = 2; i < listsize ; i += 2){
        int coef = arr[i];
        int expo = arr[i+1];
        //創件一個ptp
        Node **curr = &head;
        //找新的node的linklist中的位置 *curr要存在且下一個expo不能比新的大
        while (*curr != NULL && (*curr)->expo > expo){
            //把**curr一到下一個node
            curr = &((*curr)->next); 
        }
        //如果下一個和新的相同次數的加在一起
        if (*curr != NULL && (*curr)->expo == expo){
            (*curr)->coef += coef;
            //如果下一個項相加後係數是零就把它去掉
            if ((*curr)->coef == 0){
                Node *temp = *curr;
                *curr = (*curr)->next;
                free(temp);
            }
        }
        else {
            //在下一個創一個新的node
            Node *temp = new_node(coef, expo);
            temp ->next = *curr;
            *curr = temp; 
        }
        
    }
    return head;
}

// A + B and return the pointer point to the head of result
// input are two polynomial linked list heads
Node* plus(Node *A_head , Node* B_head){
    //創一個reslist來接
    Node *res = NULL, **curr = &res;
    while(A_head && B_head){
        if(A_head->expo == B_head->expo){
            //如果相加係數不等於0創新的node
            if((A_head->coef + B_head->coef) != 0){
                *curr = new_node((A_head->coef + B_head->coef), A_head->expo);
                curr = &(*curr)->next;
            }
            A_head = A_head->next;
            B_head = B_head->next;

        }
        else if(A_head->expo > B_head->expo){
            *curr = new_node(A_head->coef, A_head->expo);
            curr = &(*curr)->next;
            A_head = A_head->next;
        }
        else {
            *curr = new_node(B_head->coef, B_head->expo);
            curr = &(*curr)->next;
            B_head = B_head->next;
        }
    }
    //A_head 或 B_head有一個不存在時 代表一個讀完了 把令一個的厚厚全部複製進去res就好
    while((!A_head) && B_head){
        *curr = new_node(B_head->coef, B_head->expo);
        curr = &(*curr)->next;
        B_head = B_head->next;
    }
    while((!B_head) && A_head){
        *curr = new_node(A_head->coef, A_head->expo);
        curr = &(*curr)->next;
        A_head = A_head->next;
    }
    return res;
}


// A - B and return the pointer point to the head of result
// input are two polynomial linked list heads
Node* minus(Node *A_head , Node* B_head){
    Node *res = NULL, **curr = &res;
    while(A_head && B_head){
        if(A_head->expo == B_head->expo){
            //如果相加係數不等於0創新的node
            if((A_head->coef - B_head->coef) != 0){
                *curr = new_node((A_head->coef - B_head->coef), A_head->expo);
                curr = &(*curr)->next;
            }
            A_head = A_head->next;
            B_head = B_head->next;
        }
        else if(A_head->expo > B_head->expo){
            *curr = new_node(A_head->coef, A_head->expo);
            curr = &(*curr)->next;
            A_head = A_head->next;
        }
        else {
            *curr = new_node(-(B_head->coef), B_head->expo);
            curr = &(*curr)->next;
            B_head = B_head->next;
        }
    }
    //A_head 或 B_head有一個不存在時 代表一個讀完了 把令一個的後面全部複製進去res就好
    while(B_head){
        *curr = new_node(-(B_head->coef), B_head->expo);
        curr = &(*curr)->next;
        B_head = B_head->next;
    }
    while(A_head){
        *curr = new_node(A_head->coef, A_head->expo);
        curr = &(*curr)->next;
        A_head = A_head->next;
    }
    return res;
}
void free_poly(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}
#define MAXREAD 10
void print_add_minus(char *filemname, int arra_len, int arrb_len){
    FILE *in;
    in = fopen(filemname, "r");//只讀就好
    if (!in) {
        perror("Error opening file");
        return;
    }
    int reada[MAXREAD] = {0},readb[MAXREAD] = {0};
    for (int i = 0; i < arra_len; i++) {
        fscanf(in, "%d", &reada[i]);
    }

    // 讀取第二行到 arr2
    for (int i = 0; i < arrb_len; i++) {
        fscanf(in, "%d", &readb[i]);
    }
    fclose(in);
    Node *A = construct(reada, arra_len);
    Node *B = construct(readb, arrb_len);
    printf("%s\n", filemname);
    printf("\n");

    printf("A:");
    print_poly(A);

    printf("B:");
    print_poly(B);
    Node *sum = plus(A, B);
    printf("A+B:");
    print_poly(sum);
    Node *diff = minus(A, B);
    printf("A-B:");
    print_poly(diff);
    printf("\n");

    free_poly(A);
    free_poly(B);
    free_poly(sum);
    free_poly(diff);
}

int main(){
    // Node declare

    // file read and construct two given polynomial
    
    // A+B and A-B

    //For print
    print_add_minus("test1.txt", 6, 8);
    print_add_minus("test2.txt", 8, 8);
    print_add_minus("test3.txt", 8, 8);
    print_add_minus("test4.txt", 8,8);
    print_add_minus("test5.txt", 6,6);

    
    return 0;
}
