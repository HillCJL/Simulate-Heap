#include<stdio.h>
#pragma warning(disable:4996)

#define Flag 2147483648
int malloc(long long *heap, int size);
int getPoint(long long value);
void free(long long *heap, int point);
void write(long long *heap, int point, int NumberToStore);
void putPoint(long long *Number, int point);
int read(long long *heap, int point);
void PrintValue(long long *heap, const int head);
void PrintAddress(long long *heap, int head);

/*所有输入请保证合法！*/

int main() {
    long long a[1000];
    int testcase, ordernumber, input;
    int head, end, temp, temp2, NumberOfLink = 0;
    int i, counter;
    for ( i = 0; i < 1000; i++ ) {                                  /*初始化数组作为堆*/
        *(a + i) = 0;
    }
    /*读入需要输入多少个数据*/
    printf("How many number would you want to input:");
    scanf("%d", &testcase);
    temp = malloc(a, 1000);
    /*读入数据*/
    for ( i = 0; i < testcase; i++ ) {
        scanf("%d", &input);
        write(a, temp, input);                                      /*将数据写入当前位置*/
        NumberOfLink++;
        if ( i == 0 ) {
            head = temp;
            end = temp;
            putPoint(&a[temp], Flag - 1);
        }
        if ( i != 0 ) {
            putPoint(&a[end], temp);
            end = temp;
            putPoint(&a[temp], Flag - 1);
        }
        temp = malloc(a, 1000);
    }
    free(a, temp);
    printf("\n");
    printf("Now the link has %d values as the following:\n", NumberOfLink);
    PrintValue(a, head);
    printf("\n");

    /*删除节点*/
    printf("How many value would you want to delete?");
    scanf("%d", &testcase);
    printf("\n");
    while ( testcase-- ) {
        printf("Which value would you want to delete?Please enter the position:");
        scanf("%d", &ordernumber);
        printf("\n");
        if ( ordernumber == 1 ) {                                             /*删除头元素*/
            printf("You want to delete the head of the link.\n");
            temp = head;
            head = getPoint(a[head]);
            free(a, temp);
            NumberOfLink--;
        }
        else {
            if ( ordernumber == NumberOfLink ) {
                printf("You want to delete the end of the link.\n");    /*删除尾元素*/
                counter = NumberOfLink - 1;
                temp = head;
                while ( --counter ) {
                    temp = getPoint(a[temp]);
                }
                end = temp;
                temp = getPoint(a[temp]);
                putPoint(&a[end], Flag - 1);
                free(a, temp);
                NumberOfLink--;
            }
            else {
                printf("You want to delete the middle of the link.\n"); /*删除中间节点*/
                temp = head;
                counter = ordernumber - 1;
                while ( --counter ) {
                    temp = getPoint(a[temp]);
                }
                temp2 = getPoint(a[temp]);
                putPoint(&a[temp], getPoint(a[temp2]));
                free(a, temp2);
                NumberOfLink--;
            }
        }
        printf("Now the link has %d values as the following:\n", NumberOfLink);
        PrintValue(a, head);
        printf("\n");
    }
    
    /*增添节点*/
    printf("How many value would you want to add?");
    scanf("%d", &testcase);
    printf("\n");
    while ( testcase-- ) {
        printf("Which value would you want to add?Please enter the position first:");
        scanf("%d", &ordernumber);
        printf("The value you want to add is:");
        scanf("%d", &input);
        printf("\n");
        if ( ordernumber == 1 ) {
            printf("You want to add %d at the head of the link.\n", input);
            temp = malloc(a, 1000);
            write(a, temp, input);
            putPoint(&a[temp], head);
            head = temp;
            NumberOfLink++;
        }
        else {
            if ( ordernumber == NumberOfLink + 1 ) {
                printf("You want to add %d at the end of the link.\n", input);
                temp = malloc(a, 1000);
                write(a, temp, input);
                putPoint(&a[temp], Flag - 1);
                putPoint(&a[end], temp);
                end = temp;
                NumberOfLink++;
            }
            else {
                printf("You want to add %d at the middle of the link.\n", input);
                temp = malloc(a, 1000);
                write(a, temp, input);
                temp2 = head;
                ordernumber--;
                while ( --ordernumber ) {
                    temp2 = getPoint(a[temp2]);
                }
                putPoint(&a[temp], getPoint(a[temp2]));
                putPoint(&a[temp2], temp);
                NumberOfLink++;
            }
        }
        printf("Now the link has %d values as the following:\n", NumberOfLink);
        PrintValue(a, head);
        printf("\n");
        
        
    }
    printf("The address of the link is:\n");
    PrintAddress(a, head);
    printf("\n");
    getchar();
    getchar();
    return 0;
}

/*
该函数用以查找并分配空余空间
和真正的malloc函数不同的是，这里传递过来的不是需要寻址空间的大小，而是c文件中数组的头指针和数组大小
*/
int malloc(long long *heap, int size) {
    int i;
    for ( i = 0; i < size; i++ ) {          /*遍历寻找空闲空间*/
        if ( !(*(heap + i) & Flag) ) {      /*按位与判断第32位是否为1*/
            *(heap + i) |= Flag;            /*按位或将第32位变成1*/
            return i;                       /*返回地址*/
        }
    }
    return Flag - 1;                              /*寻址失败返回2147483647*/
}

/*
该函数作用为将数组值Value转为地址
*/
int getPoint(long long value) {
    return value & (Flag - 1);
}

/*
该函数作用为将point保存到Number中
*/
void putPoint(long long *Number, int point) {
    *Number &= ((long long)(-1)) << 31;
    *Number |= point;
}

/*
该函数作用为将地址为point的数组释放，便于再次使用
*/
void free(long long *heap, int point) {
    *(heap + point) = 0;
}

/*
该函数作用为将数据NumberToStore写入地址为point的数组元素中储存
*/
void write(long long *heap, int point, int NumberToStore) {
    *(heap + point) |= (((long long)NumberToStore) << 32);
}

/*
该函数用来读取储存在point处的数值
*/
int read(long long *heap, int point) {
    return (*(heap + point)) >> 32;
}

/*
该函数用于遍历链表输出元素的值
*/
void PrintValue(long long *heap, int head) {
    while ( head != Flag - 1 ) {
        printf("%d ", read(heap, head));
        head = getPoint(heap[head]);
    }
    printf("\n");
}

/*
该函数用于遍历链表输出元素地址
*/
void PrintAddress(long long *heap, int head) {
    while ( head != Flag - 1 ) {
        printf("%d ", head);
        head = getPoint(heap[head]);
    }
    printf("\n");
}
