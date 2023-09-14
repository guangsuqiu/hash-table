#include "include/hash.h"

// 哈希处理函数
int hash_function(hash_key_t key)
{
    return key % SIZE; // 取余作为哈希函数
}

/**
 * @brief 打印所有节点,以整形为例
 *
 * @param hash hash_hdr结构体指针
 */
void all_printf(struct hash_hdr *hash)
{
    printf("%s:\n", __func__);
    for (int i = 0; i < SIZE; i++)
    {
        if (hash->hash_table[i] == NULL)
            // 当结构体变量为NULL的时候，不能在访问该结构体中的成员变量，会报段错误
            // if(hash_table[i]->key==(int *)NULL)
            continue;
        printf("\tindex:%d\tkey:%d\tvalue:%d\n", i, hash->hash_table[i]->key, hash->hash_table[i]->value);
        if (hash->hash_table[i]->next != NULL)
        {
            struct node *cur = hash->hash_table[i]->next;
            while (cur != NULL)
            {
                printf("\t\tkey:%d\tvalue:%d\n", cur->key, cur->value);
                cur = cur->next;
            }
        }
    }
    return;
}

int main()
{
    struct hash_hdr *hash = hash_init(hash_function);
    if(NULL==hash)
    {
        perror("hash_init error\n");
        return -1;
    }

    insert(hash, 11, 100);
    insert(hash, 1, 500);
    insert(hash, 1, 600);
    insert(hash, 21, 700);
    insert(hash, 2, 200);
    insert(hash, 3, 300);

    hash_value_t value = 0;
    if (!get(hash, 1, &value))
        del_node(hash, 31, value + 1);
    if (!get(hash, 1, &value))
        del_node(hash, 1, value);

    if (!get(hash, 1, &value))
        printf("%d\n", value); // 输出100
    if (!get(hash, 2, &value))
        printf("%d\n", value); // 输出200
    if (!get(hash, 3, &value))
        printf("%d\n", value);
    if (!get(hash, 4, &value))
        printf("%d\n", value); // 输出-1
    if (!get(hash, 11, &value))
        printf("%d\n", value);
    if (!get(hash, 21, &value))
        printf("%d\n", value);

    all_printf(hash);

    hash_free(&hash);

    return 0;
}