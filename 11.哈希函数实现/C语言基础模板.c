#include "hash.h"

int main() {
    HashMap *map = hashmap_create();
    if (map == NULL) {
        return 1;
    }

    // �����ֵ��
    hashmap_put(map, "name", "Alice");
    hashmap_put(map, "age", "25");

    // ��ѯ��ֵ��
    ValueType name = hashmap_get(map, "name");
    ValueType age = hashmap_get(map, "age");
    if (name) {
        printf("Name: %s\n", name);
    }
    if (age) {
        printf("Age: %s\n", age);
    }

    // ɾ����ֵ��
    if (hashmap_remove(map, "age")) {
        printf("Removed 'age' successfully.\n");
    }

    //�ٴβ�ѯ��ɾ���ļ�
    age = hashmap_get(map, "age");
    if (age == NULL) {
       printf("'age' not found after removal.\n");
    }

    // ���ٹ�ϣ��
    hashmap_destroy(map);


    return 0;
}