#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 16

typedef struct
{
    int *data;
    size_t size;
    size_t capacity;
} Vector;

/* prototypes */
void create(Vector *v, size_t size);
void destroy(Vector *v);
size_t vec_size(Vector *v);
size_t vec_capacity(Vector *v);
int is_empty(Vector *v);
int at(Vector *v, int index);
void push(Vector *v, int item);
void insert(Vector *v, int index, int item);
void prepend(Vector *v, int item);
int pop(Vector *v);
void delete_at(Vector *v, int index);
void remove_item(Vector *v, int item);
int find(Vector *v, int item);
void resize(Vector *v, size_t new_capacity);

// 應該還要手動釋放記憶體空間
void create(Vector *v, size_t size)
{
    size_t init_capacity = CAPACITY;
    while (init_capacity < size) {
        init_capacity *= 2;
    }

    v->data = (int *)malloc(init_capacity * sizeof(int));
    if (v->data == NULL)
    {
        printf("malloc failed\n");
        exit(1);
    }

    // 初始化前 size 個元素為 0（因為你 main 的需求是 size=n 並初始化為零）
    for (size_t i = 0; i < size; i++)
    {
        *(v->data + i) = 0;
    }

    v->size = size;
    v->capacity = init_capacity;
}

void destroy(Vector *v)
{
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

size_t vec_size(Vector *v)
{
    return v->size;
}

size_t vec_capacity(Vector *v)
{
    return v->capacity;
}

int is_empty(Vector *v)
{
    return v->size == 0;
}

int at(Vector *v, int index)
{
    if (index < 0 || (size_t)index >= v->size)
    {
        printf("out of boundary\n");
        exit(1);
    }

    return *(v->data + index);
}

void push(Vector *v, int item)
{
    insert(v, (int)v->size, item);
}

void insert(Vector *v, int index, int item)
{
    if (index < 0 || (size_t)index > v->size)
    {
        printf("insert index out of boundary\n");
        exit(1);
    }

    // 容量不夠先擴容
    if (v->size == v->capacity)
    {
        resize(v, v->capacity * 2);
    }

    // 從尾巴往後搬移，騰出 index
    for (int i = (int)v->size; i > index; i--)
    {
        *(v->data + i) = *(v->data + i - 1);
    }

    *(v->data + index) = item;
    v->size++;
}

void prepend(Vector *v, int item)
{
    insert(v, 0, item);
}

int pop(Vector *v)
{
    if (v->size == 0)
    {
        printf("pop from empty vector\n");
        exit(1);
    }

    int end = *(v->data + v->size - 1);
    v->size--;

    // optional shrink
    if (v->capacity > CAPACITY && v->size <= v->capacity / 4)
    {
        resize(v, v->capacity / 2);
    }

    return end;
}

void delete_at(Vector *v, int index)
{
    if (index < 0 || (size_t)index >= v->size)
    {
        printf("delete index out of boundary\n");
        exit(1);
    }

    for (int i = index; (size_t)i < v->size - 1; i++)
    {
        *(v->data + i) = *(v->data + i + 1);
    }

    v->size--;

    // optional shrink
    if (v->capacity > CAPACITY && v->size <= v->capacity / 4)
    {
        resize(v, v->capacity / 2);
    }
}

void remove_item(Vector *v, int item)
{
    for (int i = 0; (size_t)i < v->size; i++)
    {
        if (*(v->data + i) == item)
        {
            delete_at(v, i);
            i--; // 避免跳過搬移後的新元素
        }
    }
}

int find(Vector *v, int item)
{
    for (int i = 0; (size_t)i < v->size; i++)
    {
        if (*(v->data + i) == item)
        {
            return i; // 回傳 index
        }
    }

    return -1;
}

void resize(Vector *v, size_t new_capacity)
{
    if (new_capacity < CAPACITY)
    {
        new_capacity = CAPACITY;
    }

    if (new_capacity < v->size)
    {
        // 不允許縮到比 size 還小
        new_capacity = v->size;
    }

    int *new_data = (int *)malloc(new_capacity * sizeof(int));
    if (new_data == NULL)
    {
        printf("resize malloc failed\n");
        exit(1);
    }

    for (size_t i = 0; i < v->size; i++)
    {
        *(new_data + i) = *(v->data + i);
    }

    free(v->data);
    v->data = new_data;
    v->capacity = new_capacity;
}

/* debug print */
void print_vector(Vector *v)
{
    printf("size=%zu, capacity=%zu, data=[", v->size, v->capacity);
    for (size_t i = 0; i < v->size; i++)
    {
        printf("%d", *(v->data + i));
        if (i + 1 < v->size) printf(", ");
    }
    printf("]\n");
}

int main()
{
    Vector my_vec;

    // 建立一個 Vector (size 為 n) 並初始化為零
    create(&my_vec, 10);
    print_vector(&my_vec); // should be 10 zeros

    push(&my_vec, 100);
    prepend(&my_vec, 50);
    insert(&my_vec, 3, 777);
    print_vector(&my_vec);

    printf("at(3) = %d\n", at(&my_vec, 3));
    printf("find(777) = %d\n", find(&my_vec, 777));

    delete_at(&my_vec, 3);
    print_vector(&my_vec);

    push(&my_vec, 100);
    push(&my_vec, 100);
    print_vector(&my_vec);

    remove_item(&my_vec, 100);
    print_vector(&my_vec);

    printf("pop = %d\n", pop(&my_vec));
    print_vector(&my_vec);

    destroy(&my_vec);
    return 0;
}