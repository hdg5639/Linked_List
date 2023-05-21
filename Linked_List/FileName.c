#include <stdio.h>
#include <stdlib.h>

typedef int element;
int counter = 0;
typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

ListNode* insert_first(ListNode* head, int value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    head = p;
    return head;
}

ListNode* insert(ListNode* head, ListNode* pre, element value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;

    if (pre == NULL) {
        p->link = head;
        head = p;
    }
    else {
        p->link = pre->link;
        pre->link = p;
    }

    return head;
}

ListNode* delete_first(ListNode* head) {
    ListNode* removed;
    if (head == NULL) return NULL;
    removed = head;
    head = removed->link;
    free(removed);
    return head;
}

ListNode* delete(ListNode* head, ListNode* pre) {
    ListNode* removed;
    if (pre == NULL || pre->link == NULL) {
        return head;
    }
    removed = pre->link;
    pre->link = removed->link;
    free(removed);
    return head;
}

void print_list(ListNode* head) {
    for (ListNode* p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("\n");
}

int main() {
    ListNode* head = NULL;
    int select, n, p;

    for (;;) {
        printf("Menu\n(1) Insert\n(2) Delete\n(3) Print\n(0) Exit\nEnter the menu: ");
        scanf_s("%d", &select);

        switch (select) {
        case 1:
            printf("Enter the number and position: ");
            scanf_s("%d %d", &n, &p);
            if (p < 0 || (p > counter && head == NULL)) {
                printf("List is empty. Insert at position 0..\n\n");
                p = 0;
            }
            if (p < 0) {
                printf("Invalid position. Insert at position 0..\n\n");
                p = 0;
            }
            else if (p > counter) {
                printf("The last index is %d. Insert at the end of the list..\n\n", counter);
                p = counter;
            }

            int moves = 0;

            if (p == 0) {
                head = insert_first(head, n);
                moves = 0;
            }
            else {
                ListNode* current = head;
                int i;
                for (i = 0; i < p - 1; i++) {
                    if (current == NULL) {
                        printf("Invalid position. Position exceeds the list length.\n\n");
                        break;
                    }
                    current = current->link;
                    moves++;
                }
                if (i == p - 1 && current != NULL) {
                    head = insert(head, current, n);
                    moves++;
                }
            }

            printf("\nMove along the link: %d\n\n", moves);
            counter++;
            break;

        case 2:
            if (head == NULL)
                printf("List is empty.\n\n");
            else {
                printf("Enter the position to delete: ");
                scanf_s("%d", &p);
                if (p < 0) {
                    printf("Invalid position. Position should be non-negative.\n");
                }
                else if (p == 0) {
                    head = delete_first(head);
                    printf("\nMove along the link: 0\n\n");
                }
                else {
                    ListNode* current = head;
                    int i;
                    int moves = 0;
                    for (i = 0; i < p - 1; i++) {
                        if (current == NULL || current->link == NULL) {
                            printf("Invalid position. Position exceeds the list length.\n\n");
                            break;
                        }
                        current = current->link;
                        moves++;
                    }
                    if (i == p - 1 && current != NULL) {
                        head = delete(head, current);
                        moves++;
                    }

                    printf("\nMove along the link: %d\n\n", moves);
                }
            }
            break;
        case 3:
            printf("List: ");
            print_list(head);
            printf("\n");
            break;

        case 0:
            printf("Exit the program.\n");
            printf("\n-------------------------------\n");
            exit(1);

        default:
            printf("Invalid Menu. Please select again..\n");
        }
    }
}