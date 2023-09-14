#include "include/hash.h"

#define NONE "\e[0m"      // 清除颜色，即之后的打印为正常输出，之前的不受影响
#define INFO "\e[0;35m"   // 深粉，暗粉，偏暗紫
#define WARING "\e[1;36m" // 鲜亮青色
#define ERROR "\e[1;40m " // 红色

struct hash_hdr *hash_init(int (*func)(hash_key_t))
{
    struct hash_hdr *hash = (struct hash_hdr *)malloc(sizeof(struct hash_hdr));
    if (NULL != hash)
    {
        memset((void *)hash, 0, sizeof(struct hash_hdr));
        hash->hash_function = func;
    }
    return hash;
}

int insert(struct hash_hdr *hash, hash_key_t key, hash_value_t value)
{
    // 先创建hash点，保存key与value
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->key = key;
    new_node->value = value;
    // 使用hash函数，获取序号
    int index = hash->hash_function(key);
    // 如果该序号存在值，则存放在该序号链表中
    if (hash->hash_table[index] == NULL)
    {
        hash->hash_table[index] = new_node;
    }
    else
    {
        struct node *cur = hash->hash_table[index];
        while (cur->next != NULL)
        {
            // 当后面由节点时，确保当前不存在key
            if (cur->key == key)
            {
                printf(WARING "WARING:fun:%s The hash table for the key is exist.\n" NONE, __func__);
                free(new_node);
                return 1;
            }
            cur = cur->next;
        }
        // 当后面没节点时，确保当前不存在key
        if (cur->key == key)
        {
            printf(WARING "WARING:fun:%s The hash table for the key is exist.\n" NONE, __func__);
            free(new_node);
            return 1;
        }
        cur->next = new_node;
    }
    return 0;
}

int get(struct hash_hdr *hash, hash_key_t key, hash_value_t *value)
{
    // 通过key取出序号，通过序号访问数组
    int index = hash->hash_function(key);
    // 通过判断数组指定位置是否为空，不为空则判断key是否与询问的key相同
    // 相同返回value 不相同查链表直至没有数据为止
    if (hash->hash_table[index] == NULL)
    {
        return 1; // 表示没有找到对应的值
    }
    else
    {
        struct node *cur = hash->hash_table[index];
        while (cur != NULL && cur->key != key)
        {
            // 查找是否存在该键
            cur = cur->next;
        }
        if (cur == NULL)
        {
            return 1; // 表示没有找到对应的值
        }
        else
        {
            *value = cur->value; // 返回对应的值
        }
    }
    return 0;
}

int del_node(struct hash_hdr *hash, hash_key_t key, hash_value_t value)
{
    int index = hash->hash_function(key); // 通过key值获取数组序号
    if (hash->hash_table[index] == NULL)
    {
        printf(WARING "WARING:fun:%s The hash table for the key is not exist.\n" NONE, __func__);
        return 1;
    }
    struct node *prev = NULL;
    struct node *new = hash->hash_table[index];
    while (new->key != key)
    {
        prev = new;
        if (new->next != NULL)
            new = new->next;
        else
        {
            printf(WARING "WARING:fun:%s The hash table for the key is not exist.\n" NONE, __func__);
            return 1;
        }
    }
    if (new->value == value)
    {
        prev->next = new->next;
        free(new);
    }
    else
    {
        printf(WARING "WARING:fun:%s The value is not exist.\n" NONE, __func__);
        return 1;
    }
    return 0;
}

void hash_free(struct hash_hdr **hash)
{
    for (int i = 0; i < SIZE; i++)
    {
        // 要先判断结构体是否为NULL，否则直接使用成员变量会段错误
        if ((*hash)->hash_table[i] != NULL)
        {
            while ((*hash)->hash_table[i]->next != NULL)
            {
                struct node *temp = (*hash)->hash_table[i];
                (*hash)->hash_table[i] = (*hash)->hash_table[i]->next;
                free(temp);
            }
            free((*hash)->hash_table[i]);
            (*hash)->hash_table[i] = NULL;
        }
    }
    free(*hash);
}