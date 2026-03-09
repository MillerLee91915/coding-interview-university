#include <stdlib.h>
#include <stdio.h>

struct node
{
    int data;
    struct node *next;
};
typedef struct node Node;

// size
int size(Node *linklist);

// empty
int empty(Node *linklist);

// value_at(index)
int value_at(Node *linklist, int index);

// push_front(value)
void push_front(Node **addr_of_linklist, int value);

// pop_front()
int pop_front(Node **addr_of_linklist);

// push_back(value)
void push_back(Node **addr_of_linklist, int value);

// pop_back()
int pop_back(Node **addr_of_linklist);

// front()
int front(Node **addr_of_linklist);

// back()
int back(Node **addr_of_linklist);

// insert(index, value)
void insert(Node **head, int index, int value);

// erase(index)
void erase(Node **head, int index);

// value_n_from_end(n)
int value_n_from_end(Node *head, int n);

// reverse()
void reverse(Node **head);

// remove_value(value)
void remove_value(Node **head, int value);

void print_linklist(Node *linklist);

int main()
{
    Node *list = NULL;

    printf("=== init ===\n");
    print_linklist(list);
    printf("size = %d\n\n", size(list));

    printf("=== push_back 10,20,30 ===\n");
    push_back(&list, 10);
    push_back(&list, 20);
    push_back(&list, 30);
    print_linklist(list);            // 預期: 10 20 30
    printf("size = %d\n\n", size(list)); // 預期: 3

    printf("=== push_front 5 ===\n");
    push_front(&list, 5);
    print_linklist(list);            // 預期: 5 10 20 30
    printf("size = %d\n\n", size(list)); // 預期: 4

    printf("=== insert(index=2, value=15) ===\n");
    insert(&list, 2, 15);
    print_linklist(list);            // 預期: 5 10 15 20 30
    printf("size = %d\n\n", size(list)); // 預期: 5

    printf("=== erase(index=3) ===\n");
    erase(&list, 3);
    print_linklist(list);            // 預期: 5 10 15 30
    printf("size = %d\n\n", size(list)); // 預期: 4

    printf("=== remove_value(10) ===\n");
    remove_value(&list, 10);
    print_linklist(list);            // 預期: 5 15 30
    printf("size = %d\n\n", size(list)); // 預期: 3

    printf("=== reverse ===\n");
    reverse(&list);
    print_linklist(list);            // 預期: 30 15 5
    printf("size = %d\n\n", size(list)); // 預期: 3

    printf("=== value_n_from_end (1-based: n=1 is last) ===\n");
    printf("n=1 -> %d (預期 5)\n",  value_n_from_end(list, 1));
    printf("n=2 -> %d (預期 15)\n", value_n_from_end(list, 2));
    printf("n=3 -> %d (預期 30)\n\n", value_n_from_end(list, 3));

    printf("=== pop_front ===\n");
    printf("pop_front = %d (預期 30)\n", pop_front(&list));
    print_linklist(list);            // 預期: 15 5
    printf("size = %d (預期 2)\n\n", size(list));

    printf("=== pop_back ===\n");
    printf("pop_back = %d (預期 5)\n", pop_back(&list));
    print_linklist(list);            // 預期: 15
    printf("size = %d (預期 1)\n\n", size(list));

    printf("=== pop_back on single-node ===\n");
    printf("pop_back = %d (預期 15)\n", pop_back(&list));
    print_linklist(list);            // 預期: (空)
    printf("size = %d (預期 0)\n\n", size(list));

    printf("=== pop_front on empty (看你的實作如何處理) ===\n");
    // 如果你 pop_front 沒處理空串列，這行會 crash；建議你要加保護
    // printf("pop_front = %d\n", pop_front(&list));

    printf("=== cleanup: ensure empty ===\n");
    print_linklist(list);
    printf("size = %d\n", size(list));

    return 0;
}

void print_linklist(Node *linklist)
{
    printf("linklist: ");
    if (linklist == NULL)
    {
        printf("linklist is null\n");
        return;
    }

    Node *current = linklist;
    while (current->next != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("%d ", current->data);
    printf("\n");
}

int size(Node *linklist)
{
    int num = 0;
    Node *current = linklist;
    if (current == NULL)
    {
        return 0;
    }

    while (current->next != NULL)
    {
        num++;
        current = current->next;
    }
    num++;

    return num;
}

int empty(Node *linklist)
{
    if (size(linklist) == 0)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

int value_at(Node *linklist, int index)
{
    Node *current;
    current = linklist;

    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    return current->data;
}

void push_front(Node **addr_of_linklist, int value)
{
    Node *newnode = (Node *)malloc(sizeof(Node));
    if (newnode == NULL)
    {
        printf("malloc failed\n");
        return;
    }

    newnode->data = value;
    newnode->next = *addr_of_linklist; // 接到原本的 head

    *addr_of_linklist = newnode; // 更新 head
}

int pop_front(Node **addr_of_linklist)
{
    // 空串列會爆炸

    Node *old = *addr_of_linklist; // 舊 head
    int pop_data = old->data;

    *addr_of_linklist = old->next; // head 往後移
    free(old);                     // 釋放舊 head

    return pop_data;
}

void push_back(Node **linklist, int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("malloc failed\n");
        return;
    }

    newNode->data = value;
    newNode->next = NULL;

    // 如果是空串列，新的節點就是 head
    if (*linklist == NULL)
    {
        *linklist = newNode;
        return;
    }

    // 走到最後一個節點
    Node *current = *linklist;
    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = newNode;
}

int pop_back(Node **addr_of_linklist)
{
    if (addr_of_linklist == NULL || *addr_of_linklist == NULL)
    {
        // 串列是空的：你可以自己決定要怎麼處理
        // 例如印錯誤、return 某個特殊值
        printf("list is empty\n");
        return 0;
    }

    Node *current = *addr_of_linklist;
    Node *previous = NULL;

    // 只有一個節點
    if (current->next == NULL)
    {
        int pop_data = current->data;
        free(current);
        *addr_of_linklist = NULL; // head 變空
        return pop_data;
    }

    // 走到最後一個
    while (current->next != NULL)
    {
        previous = current;
        current = current->next;
    }

    int pop_data = current->data;
    previous->next = NULL; // 先斷鏈再 free（比較安全）
    free(current);

    return pop_data;
}

int front(Node **addr_of_linklist)
{

    // 空串列檢查

    Node *current;
    current = *addr_of_linklist;

    return current->data;
}

// back()
int back(Node **addr_of_linklist)
{

    if (addr_of_linklist == NULL || *addr_of_linklist == NULL)
    {
        // 串列是空的：你可以自己決定要怎麼處理
        // 例如印錯誤、return 某個特殊值
        printf("list is empty\n");
        return 0;
    }

    Node *current = *addr_of_linklist;
    Node *previous = NULL;

    // 只有一個節點
    if (current->next == NULL)
    {
        int pop_data = current->data;
        free(current);
        *addr_of_linklist = NULL; // head 變空
        return pop_data;
    }

    // 走到最後一個
    while (current->next != NULL)
    {
        previous = current;
        current = current->next;
    }

    return current->data;
}

void insert(Node **head, int index, int value)
{
    if (head == NULL || index < 0) return;

    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) { printf("malloc failed\n"); return; }
    newNode->data = value;
    newNode->next = NULL;

    // insert at front
    if (index == 0)
    {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    // find (index-1)th node
    Node *prev = *head;
    for (int i = 0; i < index - 1; i++)
    {
        if (prev == NULL) { free(newNode); printf("index out of range\n"); return; }
        prev = prev->next;
    }

    if (prev == NULL) { free(newNode); printf("index out of range\n"); return; }

    newNode->next = prev->next;
    prev->next = newNode;
}

void erase(Node **head, int index)
{
    if (head == NULL || *head == NULL || index < 0) return;

    // erase front
    if (index == 0)
    {
        Node *old = *head;
        *head = old->next;
        free(old);
        return;
    }

    Node *prev = *head;
    for (int i = 0; i < index - 1; i++)
    {
        if (prev == NULL || prev->next == NULL) { printf("index out of range\n"); return; }
        prev = prev->next;
    }

    Node *target = prev->next;
    if (target == NULL) { printf("index out of range\n"); return; }

    prev->next = target->next;
    free(target);
}

int value_n_from_end(Node *head, int n)
{
    if (head == NULL || n <= 0) return INT_MIN;

    Node *fast = head;
    for (int i = 1; i < n; i++)
    {
        if (fast->next == NULL) return INT_MIN;
        fast = fast->next;
    }

    Node *slow = head;
    while (fast->next != NULL)
    {
        fast = fast->next;
        slow = slow->next;
    }
    return slow->data;
}

void reverse(Node **head)
{
    if (head == NULL) return;

    Node *prev = NULL;
    Node *cur = *head;

    while (cur != NULL)
    {
        Node *next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    *head = prev;
}

// remove_value(value)
void remove_value(Node **head, int value)
{
    if (head == NULL || *head == NULL) return;

    // head matches
    if ((*head)->data == value)
    {
        Node *old = *head;
        *head = old->next;
        free(old);
        return;
    }

    Node *prev = *head;
    Node *cur = prev->next;

    while (cur != NULL && cur->data != value)
    {
        prev = cur;
        cur = cur->next;
    }

    if (cur == NULL) return; // not found

    prev->next = cur->next;
    free(cur);
}