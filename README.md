# 哈希实现

#### 介绍

哈希存储的简单实现。

#### 编译教程

1. 生成debug/release版本
    ```bash
    cmake . -DCMAKE_BUILD_TYPE=debug
    cmake . -DCMAKE_BUILD_TYPE=release
    ```
2. 编译
    在LINUX下输入：
    ```bash
    make
    ```
3. 可执行文件存放在tmp下
    ```bash
    ./tmp/hash_test
    ```

#### 使用教程
1. 定义key与value数据类型,并修改hash_table的大小
    ```c
    #define SIZE 10
    typedef int hash_key_t;
    typedef int hash_value_t;
    ```

2. 编写哈希处理函数,如何通过key值获取一个相对不重复的序号
    ```c
    int hash_function(hash_key_t key)
    {
        return key % SIZE; // 取余作为哈希函数
    }
    ```
3. 初始化,并注册hash处理函数
    ```c
    struct hash_hdr *hash = hash_init(hash_function);
    ```

4. 进行增删查操作
    ```c
    int insert(struct hash_hdr *hash, hash_key_t key, hash_value_t value);
    int del_node(struct hash_hdr *hash, hash_key_t key, hash_value_t value);
    int get(struct hash_hdr *hash, hash_key_t key, hash_value_t *value);
    ```

5. 释放内存
    ```c
    void hash_free(struct hash_hdr **hash);
    ```

#### 本人才疏学浅，欢迎交流讨论。