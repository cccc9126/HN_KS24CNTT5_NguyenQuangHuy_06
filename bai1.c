
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 100

typedef struct Node {
    char bookTitle[MAX_LEN];
    struct Node *next;
} Node;

typedef struct Stack {
    Node *top;
} Stack;

typedef struct Queue {
    Node *front;
    Node *rear;
} Queue;

void initStack(Stack *s) {
    s->top = NULL;
}

int isEmpty(Stack *s) {
    return s->top == NULL;
}

void push(Stack *s, char *bookTitle) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    strcpy(newNode->bookTitle, bookTitle);
    newNode->next = s->top;
    s->top = newNode;
}
char* pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return NULL;
    }
    Node *temp = s->top;
    char* bookTitle = strdup(temp->bookTitle);
    s->top = s->top->next;
    free(temp);
    return bookTitle;
}

void printStack(Stack *s) {
    Node *temp = s->top;
    while (temp != NULL) {
        printf("%s\n", temp->bookTitle);
        temp = temp->next;
    }
}

void initQueue(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
}

int isEmptyQueue(Queue *q) {
    return q->front == NULL;
}

void enqueue(Queue *q, char *bookTitle) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    strcpy(newNode->bookTitle, bookTitle);
    newNode->next = NULL;
    if (isEmptyQueue(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

char* dequeue(Queue *q) {
    if (isEmptyQueue(q)) {
        printf("Queue is empty\n");
        return NULL;
    }
    Node *temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    char* bookTitle = strdup(temp->bookTitle);
    free(temp);
    return bookTitle;
}

void printQueue(Queue *q) {
    Node *temp = q->front;
    while (temp != NULL) {
        printf("%s\n", temp->bookTitle);
        temp = temp->next;
    }
    printf("\n");
}


void freeQueue(Queue *q) {
    while (!isEmptyQueue(q)) {
        dequeue(q);
    }
}


void freeStack(Stack *s) {
    while (!isEmpty(s)) {
        pop(s);
    }
}


int main() {
    Stack *bookStack = (Stack *) malloc(sizeof(Stack));
    Queue *closedBook = (Queue *) malloc(sizeof(Queue));
    initStack(bookStack);
    initQueue(closedBook);
    int choice;
    char current[MAX_LEN];

    do {
        printf("==========E-BOOK READER MANAGER==========\n");
        printf("1. Mở sách mới\n");
        printf("2. Đóng sách hiên tại\n");
        printf("3. Xem sách đang đọc gần nhất\n");
        printf("4. Lịch sử đóng sách\n");
        printf("5. Khôi phục sách\n");
        printf("6. Hiển thị các sách đang mở\n");
        printf("7. Thoát\n");
        printf("========================================\n");
        printf("Mời nhập lựa chọn của bạn: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                char newBook[MAX_LEN];
                printf("Nhập tên sách mới: ");
                fgets(newBook, MAX_LEN, stdin);
                newBook[strcspn(newBook, "\n")] = '\0';
                push(bookStack, newBook);


                break;

            case 2:
                if (!isEmpty(bookStack)) {
                    char* current = pop(bookStack);
                    if (current != NULL) {
                        enqueue(closedBook, current);
                        free(current);
                        printf("Sách đã được đóng và chuyển vào lịch sử\n");

                    }
                } else {
                    printf("Không có sách nào đang mở\n");
                }
                break;

            case 3:
                if (!isEmpty(bookStack)) {
                    printf("Sách đang đọc gần nhất: %s\n", bookStack->top->bookTitle);
                } else {
                    printf("Không có sách nào đang mở\n");
                }
                break;

            case 4:
                if (!isEmptyQueue(closedBook)) {
                    printf("Lịch sử sách đã đóng:\n");
                    printQueue(closedBook);
                } else {
                    printf("Chưa có sách nào trong lịch sử\n");
                }
                break;
case 5:
                if (!isEmptyQueue(closedBook)) {
                    char*temp = dequeue(closedBook);
                    printf("%s", temp);
                    push(bookStack, temp);
                    free(temp);




                }else {
                    printf("Không có sách nào đang đóng.\n");
                }
                break;
            case 6:
                if (!isEmpty(bookStack)) {
                    printf("Các sách đang mở:\n");
                    printStack(bookStack);
                } else {
                    printf("Không có sách nào đang mở\n");
                }
                break;
            case 7:

                freeStack(bookStack);
                freeQueue(closedBook);
                break;
            default:
                printf("Lựa chọn không hợp lệ .");
                break;
        }
    } while (choice != 7);
printf("Thoát chương trình....\n");
    return 0;
}



