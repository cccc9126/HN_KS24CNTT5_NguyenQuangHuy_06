
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 200

typedef struct Node {
    char content[MAX_LEN];
    int isAction;
    struct Node *yesChild;
    struct Node *noChild;
} Node;

Node* create(const char* data) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Không đủ bộ nhớ\n");
        return NULL;
    }
    strncpy(newNode->content, data, MAX_LEN - 1);
    newNode->content[MAX_LEN - 1] = '\0';
    newNode->isAction = 0;
    newNode->yesChild = NULL;
    newNode->noChild = NULL;
    return newNode;
}

Node* addTree(Node *root, const char* data) {
    if (root == NULL) {
        return create(data);
    }

    printf("Nhánh:  %s\n", root->content);
    printf(" 1: Có | 2: Không : ");
    int choice;
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        if (root->yesChild == NULL) {
            root->yesChild = create(data);
        } else {
            root->yesChild = addTree(root->yesChild, data);
        }
    } else if (choice == 2) {
        if (root->noChild == NULL) {
            root->noChild = create(data);
        } else {
            root->noChild = addTree(root->noChild, data);
        }
    }

    return root;
}

void display(Node *root) {
    if (root == NULL) return;
    printf("%s\n",root->content);
    display(root->yesChild);
    display(root->noChild);
}

void playGame(Node *root) {
    if (root == NULL) return;

    printf("\n%s (yes/no): ", root->content);
    char answer[10];
    fgets(answer, sizeof(answer), stdin);
    answer[strcspn(answer, "\n")] = 0;

    if (strcmp(answer, "yes") == 0) {
        if (root->yesChild!=NULL) {
            playGame(root->yesChild);
        } else {
            printf("Kết thúc!\n");
        }
    } else if (strcmp(answer, "no") == 0) {
        if (root->noChild!=NULL) {
            playGame(root->noChild);
        } else {
            printf("Kết thúc!\n");
        }
    } else {
        printf("Nhập 'yes' hoặc 'no'\n");
        playGame(root);
    }
}

void freeTree(Node *root) {
    if (root == NULL) return;
    freeTree(root->yesChild);
    freeTree(root->noChild);
    free(root);
}
Node* deleteNode(Node *root, const char* data) {
    if (root == NULL) return NULL;
    printf("%s", root->content);
    printf("Xóa nút này (yes/no) :");
    char answer[10];
    fgets(answer, sizeof(answer), stdin);
    answer[strcspn(answer, "\n")] = 0;
    if (strcmp(answer, "yes") == 0) {
        if (root->yesChild == NULL && root->noChild == NULL) {
            free(root);
            return NULL;
        } else if (root->yesChild == NULL) {
            Node *temp = root->noChild;
            free(root);
        }
    }
}
int main() {
    int choice;
    Node *root = NULL;
    char input[MAX_LEN];

    do {
        printf("\n=======GAME DECISION SIMULATOR=======\n");
        printf("1. Bắt đầu\n");
        printf("2. Hiện thị cây quyết định\n");
        printf("3. Thêm hành động hoặc câu hỏi\n");
        printf("4. Xóa 1 nút bất kì\n");
        printf("5. Thoát\n");
        printf("=====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                if (root == NULL) {
                    printf("Hãy thêm câu hỏi!\n");
                } else {
                    playGame(root);
                }
                break;
            case 2:
                if (root == NULL) {
                    printf("Không có câu hỏi nào!\n");
                } else {
                    display(root);
                }
                break;
            case 3:
                printf("Nhập câu hỏi hoặc hành động: ");
                fgets(input, MAX_LEN, stdin);
                input[strcspn(input, "\n")] = 0;
                root = addTree(root, input);
                printf("Thêm thành công!\n");
                break;
            case 4:

                deleteNode(root, input);
                break;

            case 5:
                freeTree(root);
                printf("Đang thoát chương tình!\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ.\n");
                break;
        }
    } while (choice != 4);

    return 0;
}