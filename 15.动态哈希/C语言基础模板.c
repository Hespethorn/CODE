#include <stdio.h>
#include "hash.h"

int main() {
    // 创建哈希表
    DynamicHashMap *map = hashmap_create();
    if (!map) {
        fprintf(stderr, "Failed to create hashmap.\n");
        return 1;
    }

    // 测试插入操作
    printf("Testing hashmap_put...\n");
    const char *key1 = "name";
    const char *val1 = "Alice";
    ValueType result1 = hashmap_put(map, (KeyType)key1, (ValueType)val1);
    if (result1) {
        printf("Inserted key: %s, value: %s\n", key1, result1);
    }
    else {
        printf("Failed to insert key: %s\n", key1);
    }

    const char *key2 = "age";
    const char *val2 = "25";
    ValueType result2 = hashmap_put(map, (KeyType)key2, (ValueType)val2);
    if (result2) {
        printf("Inserted key: %s, value: %s\n", key2, result2);
    }
    else {
        printf("Failed to insert key: %s\n", key2);
    }

    // 测试更新操作
    printf("\nTesting update...\n");
    const char *new_val1 = "Bob";
    ValueType update_result = hashmap_put(map, (KeyType)key1, (ValueType)new_val1);
    if (update_result) {
        printf("Updated key: %s, new value: %s\n", key1, update_result);
    }
    else {
        printf("Failed to update key: %s\n", key1);
    }

    // 测试查询操作
    printf("\nTesting hashmap_get...\n");
    ValueType get_result1 = hashmap_get(map, (KeyType)key1);
    if (get_result1) {
        printf("Got key: %s, value: %s\n", key1, get_result1);
    }
    else {
        printf("Key %s not found.\n", key1);
    }

    ValueType get_result2 = hashmap_get(map, (KeyType)key2);
    if (get_result2) {
        printf("Got key: %s, value: %s\n", key2, get_result2);
    }
    else {
        printf("Key %s not found.\n", key2);
    }

    // 测试删除操作
    printf("\nTesting hashmap_remove...\n");
    bool remove_result = hashmap_remove(map, (KeyType)key2);
    if (remove_result) {
        printf("Removed key: %s successfully.\n", key2);
    }
    else {
        printf("Failed to remove key: %s\n", key2);
    }

    // 再次查询已删除的键
    ValueType get_after_remove = hashmap_get(map, (KeyType)key2);
    if (get_after_remove) {
        printf("Got key: %s, value: %s\n", key2, get_after_remove);
    }
    else {
        printf("Key %s not found after removal (expected).\n", key2);
    }

    // 销毁哈希表
    printf("\nDestroying hashmap...\n");
    hashmap_destroy(map);
    printf("Hashmap destroyed.\n");

    return 0;
}