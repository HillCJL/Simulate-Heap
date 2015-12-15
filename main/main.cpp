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

/*���������뱣֤�Ϸ���*/

int main() {
    long long a[1000];
    int testcase, ordernumber, input;
    int head, end, temp, temp2, NumberOfLink = 0;
    int i, counter;
    for ( i = 0; i < 1000; i++ ) {                                  /*��ʼ��������Ϊ��*/
        *(a + i) = 0;
    }
    /*������Ҫ������ٸ�����*/
    printf("How many number would you want to input:");
    scanf("%d", &testcase);
    temp = malloc(a, 1000);
    /*��������*/
    for ( i = 0; i < testcase; i++ ) {
        scanf("%d", &input);
        write(a, temp, input);                                      /*������д�뵱ǰλ��*/
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

    /*ɾ���ڵ�*/
    printf("How many value would you want to delete?");
    scanf("%d", &testcase);
    printf("\n");
    while ( testcase-- ) {
        printf("Which value would you want to delete?Please enter the position:");
        scanf("%d", &ordernumber);
        printf("\n");
        if ( ordernumber == 1 ) {                                             /*ɾ��ͷԪ��*/
            printf("You want to delete the head of the link.\n");
            temp = head;
            head = getPoint(a[head]);
            free(a, temp);
            NumberOfLink--;
        }
        else {
            if ( ordernumber == NumberOfLink ) {
                printf("You want to delete the end of the link.\n");    /*ɾ��βԪ��*/
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
                printf("You want to delete the middle of the link.\n"); /*ɾ���м�ڵ�*/
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
    
    /*����ڵ�*/
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
�ú������Բ��Ҳ��������ռ�
��������malloc������ͬ���ǣ����ﴫ�ݹ����Ĳ�����ҪѰַ�ռ�Ĵ�С������c�ļ��������ͷָ��������С
*/
int malloc(long long *heap, int size) {
    int i;
    for ( i = 0; i < size; i++ ) {          /*����Ѱ�ҿ��пռ�*/
        if ( !(*(heap + i) & Flag) ) {      /*��λ���жϵ�32λ�Ƿ�Ϊ1*/
            *(heap + i) |= Flag;            /*��λ�򽫵�32λ���1*/
            return i;                       /*���ص�ַ*/
        }
    }
    return Flag - 1;                              /*Ѱַʧ�ܷ���2147483647*/
}

/*
�ú�������Ϊ������ֵValueתΪ��ַ
*/
int getPoint(long long value) {
    return value & (Flag - 1);
}

/*
�ú�������Ϊ��point���浽Number��
*/
void putPoint(long long *Number, int point) {
    *Number &= ((long long)(-1)) << 31;
    *Number |= point;
}

/*
�ú�������Ϊ����ַΪpoint�������ͷţ������ٴ�ʹ��
*/
void free(long long *heap, int point) {
    *(heap + point) = 0;
}

/*
�ú�������Ϊ������NumberToStoreд���ַΪpoint������Ԫ���д���
*/
void write(long long *heap, int point, int NumberToStore) {
    *(heap + point) |= (((long long)NumberToStore) << 32);
}

/*
�ú���������ȡ������point������ֵ
*/
int read(long long *heap, int point) {
    return (*(heap + point)) >> 32;
}

/*
�ú������ڱ����������Ԫ�ص�ֵ
*/
void PrintValue(long long *heap, int head) {
    while ( head != Flag - 1 ) {
        printf("%d ", read(heap, head));
        head = getPoint(heap[head]);
    }
    printf("\n");
}

/*
�ú������ڱ����������Ԫ�ص�ַ
*/
void PrintAddress(long long *heap, int head) {
    while ( head != Flag - 1 ) {
        printf("%d ", head);
        head = getPoint(heap[head]);
    }
    printf("\n");
}
