#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct LRUNode {
    int value;
    int lastUsed;
    struct LRUNode *next;
    struct LRUNode *last;
} LRUNode;

typedef struct ClockNode {
    int value;
    
} ClockNode;


LRUNode* createLRUNode(int value) {
    LRUNode* node = (LRUNode*)malloc(sizeof(LRUNode));
    node->value = value;
    node->lastUsed = 0;
    node->next = NULL;
    node->last = NULL;
    return node;
}

void LRUReplacement(FILE* file) {
    LRUNode* head = createLRUNode(100);
    LRUNode* tail = createLRUNode(100);
    int buf;
    fscanf(file, "%d, ", &buf);
    LRUNode* node = createLRUNode(buf);
    node->last = head;
    head->next = node;
    node->lastUsed = 2;
    fscanf(file, "%d, ", &buf);
    LRUNode* node2 = createLRUNode(buf);
    node2->last = node;
    node2->lastUsed = 1;
    node->next = node2;
    fscanf(file, "%d, ", &buf);
    LRUNode* node3 = createLRUNode(buf);
     node3->last = node2;
     node3->next = tail;
    node2->next = node3;
    node3->lastUsed = 0;
    tail->last = node3;

    printf("\n\nInitial Frames: %d, %d, %d\n", node->value, node2->value, node3->value);
    printf("Initial Least Recently Used Values: %d, %d, %d\n\n", node->lastUsed, node2->lastUsed, node3->lastUsed);
    
    char c = fgetc(file);
    ungetc(c, file);
    while (c != '\r') {
        fscanf(file, "%d, ", &buf);
        LRUNode* addedNode = createLRUNode(buf);
        LRUNode* ptrNode = head->next;
        if (ptrNode->value == buf || ptrNode->next->value == buf || ptrNode->next->next->value == buf) {
            if (ptrNode->value == buf) {
                ptrNode->lastUsed = 0;
                if (ptrNode->next->lastUsed < ptrNode->next->next->lastUsed) {
                    ptrNode->next->lastUsed = 1;
                    ptrNode->next->next->lastUsed = 2;
                }
                else {
                    ptrNode->next->lastUsed = 2;
                    ptrNode->next->next->lastUsed = 1;
                }
            }
            else if (ptrNode->next->value == buf) {
                ptrNode->next->lastUsed = 0;
                if (ptrNode->lastUsed < ptrNode->next->next->lastUsed) {
                    ptrNode->lastUsed = 1;
                    ptrNode->next->next->lastUsed = 2;
                }
                else {
                    ptrNode->lastUsed = 2;
                    ptrNode->next->next->lastUsed = 1;
                }
            }
            else {
                ptrNode->next->next->lastUsed = 0;
                if (ptrNode->lastUsed < ptrNode->next->lastUsed) {
                    ptrNode->lastUsed = 1;
                    ptrNode->next->lastUsed = 2;
                }
                else {
                    ptrNode->lastUsed = 2;
                    ptrNode->next->lastUsed = 1;
                }
            }
        }
        else {
            for (int i = 0; i < 3; i++) {
            if (ptrNode->lastUsed == 2) {
                addedNode->last = ptrNode->last;
                addedNode->next = ptrNode->next;
                addedNode->last->next = addedNode;
                addedNode->next->last = addedNode;
                free(ptrNode);
                if (i == 0) {
                    if (addedNode->next->lastUsed < addedNode->next->next->lastUsed) {
                        addedNode->next->lastUsed = 1;
                        addedNode->next->next->lastUsed = 2;
                        break;
                    }
                    else {
                        addedNode->next->lastUsed = 2;
                        addedNode->next->next->lastUsed = 1;
                        break;
                    }
                }
                if (i == 1) {
                    if (addedNode->last->lastUsed < addedNode->next->lastUsed) {
                        addedNode->last->lastUsed = 1;
                        addedNode->next->lastUsed = 2;
                        break;
                    }
                    else {
                        addedNode->last->lastUsed = 2;
                        addedNode->next->lastUsed = 1;
                        break;
                    }
                }
                else {
                    if (addedNode->last->last->lastUsed < addedNode->last->lastUsed) {
                        addedNode->last->last->lastUsed = 1;
                        addedNode->last->lastUsed = 2;
                        break;
                    }
                    else {
                        addedNode->last->last->lastUsed = 2;
                        addedNode->last->lastUsed = 1;
                        break;
                    }
                }
            }
            ptrNode = ptrNode->next;
            }
        }

       printf("Current Frames: %d, %d, %d\n", head->next->value, head->next->next->value, head->next->next->next->value);
       printf("Current Least Recently Used Values: %d, %d, %d\n\n", head->next->lastUsed, head->next->next->lastUsed, head->next->next->next->lastUsed);
    c = fgetc(file);
    ungetc(c, file);
}

free(head);
free(tail);
free(node);
free(node2);

}
int main() {
    FILE* file = fopen("Pages.txt", "r");
    LRUReplacement(file);
    LRUReplacement(file);
    LRUReplacement(file);
    LRUReplacement(file);
    

}