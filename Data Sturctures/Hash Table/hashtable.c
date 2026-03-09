#include <stdlib.h>

typedef struct
{
    int key;
    int value;
    int used;
} Entry;

typedef struct
{
    Entry *table;
    int size;
} HashTable;

// 最簡單
int hash(int key, int m) 
{
    return key % m;
}

HashTable *create(int size)
{
    HashTable *ht = malloc(sizeof(HashTable));

    ht->size = size;
    ht->table = malloc(sizeof(Entry) * size);

    for (int i = 0; i < size; i++)
    {
        ht->table[i].used = 0;
    }

    return ht;
}

void add(HashTable *ht, int key, int value)
{
    int index = hash(key, ht->size);

    while (ht->table[index].used)
    {
        if (ht->table[index].key == key)
        {
            ht->table[index].value = value;
            return;
        }

        index = (index + 1) % ht->size;
    }

    ht->table[index].key = key;
    ht->table[index].value = value;
    ht->table[index].used = 1;
}

int exists(HashTable *ht, int key)
{
    int index = hash(key, ht->size);

    while (ht->table[index].used)
    {
        if (ht->table[index].key == key)
        {
            return 1;
        }

        index = (index + 1) % ht->size;
    }

    return 0;
}

int get(HashTable *ht, int key)
{
    int index = hash(key, ht->size);

    while (ht->table[index].used)
    {
        if (ht->table[index].key == key)
        {
            return ht->table[index].value;
        }

        index = (index + 1) % ht->size;
    }

    return -1;
}

void remove_key(HashTable *ht, int key)
{
    int index = hash(key, ht->size);

    while (ht->table[index].used)
    {
        if (ht->table[index].key == key)
        {
            ht->table[index].used = 0;
            return;
        }

        index = (index + 1) % ht->size;
    }
}

int main()
{
    HashTable *ht = create(10);

    add(ht, 1, 100);
    add(ht, 2, 200);
    add(ht, 11, 300); 

    printf("%d\n", exists(ht, 1));
    printf("%d\n", get(ht, 2));

    remove_key(ht, 2);

    printf("%d\n", exists(ht, 2));

    return 0;
}