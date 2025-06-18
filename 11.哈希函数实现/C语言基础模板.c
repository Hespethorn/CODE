#include "hash.h"

int main() {
    HashMap *map = hashmap_create();
    if (map == NULL) {
        return 1;
    }

    // 插入键值对
    hashmap_put(map, "name", "Alice");
    hashmap_put(map, "age", "25");

    // 查询键值对
    ValueType name = hashmap_get(map, "name");
    ValueType age = hashmap_get(map, "age");
    if (name) {
        printf("Name: %s\n", name);
    }
    if (age) {
        printf("Age: %s\n", age);
    }

    // 删除键值对
    if (hashmap_remove(map, "age")) {
        printf("Removed 'age' successfully.\n");
    }

    //再次查询已删除的键
    age = hashmap_get(map, "age");
    if (age == NULL) {
       printf("'age' not found after removal.\n");
    }

    // 销毁哈希表
    hashmap_destroy(map);


    return 0;
}