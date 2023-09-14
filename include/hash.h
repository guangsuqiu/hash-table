#ifndef __HSAH_H__
#define __HSAH_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief hash_table数组大小,根据业务冲定义.
 *
 */
#define SIZE 10

/**
 * @brief key对应的数据类型,根据业务重定义.
 *
 */
typedef int hash_key_t;

/**
 * @brief value对应的数据类型,根据业务重定义.
 *
 */
typedef int hash_value_t;

/**
 * @brief 哈希文件描述符/句柄
 *
 */
struct hash_hdr
{
    int (*hash_function)(hash_key_t); // 哈希处理函数
    struct node *hash_table[SIZE];    // 哈希表
};

/**
 * @brief 哈希节点
 *
 */
struct node
{
    hash_key_t key;
    hash_value_t value;
    struct node *next;
};

/**
 * @brief 初始化hash表,注册哈希函数,返回结构体指针.
 *
 * @param func 注册的哈希函数.
 * @return struct hash_hdr* 结构体指针,里面包含哈希表与哈希处理函数.
 */
struct hash_hdr *hash_init(int (*func)(hash_key_t));

/**
 * @brief 插入一组数据
 *
 * @param hash hash_hdr 结构体指针
 * @param key 键
 * @param value 值
 * @return int 成功返回0,失败返回1.
 */
int insert(struct hash_hdr *hash, hash_key_t key, hash_value_t value);

/**
 * @brief 获取key对应的value
 * 
 * @param hash hash_hdr 结构体指针(input)
 * @param key 键(input)
 * @param value 值(output)
 * @return int 成功返回0,失败返回1.
 */
int get(struct hash_hdr *hash, hash_key_t key, hash_value_t *value);

/**
 * @brief 删除指定节点
 *
 * @param hash hash_hdr 结构体指针
 * @param key 键
 * @param value 值
 * @return int 成功返回0,失败返回1.
 */
int del_node(struct hash_hdr *hash, hash_key_t key, hash_value_t value);

/**
 * @brief 释放hash表
 *
 * @param hash hash_hdr 结构体指针
 */
void hash_free(struct hash_hdr **hash);

#endif // __HSAH_H__