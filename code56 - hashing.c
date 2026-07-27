#include <stdio.h>
#define TABLE_SIZE 10
#define PRIME 7 // For double hashing

// Hash Table Structure
int hashTable[TABLE_SIZE];

// Direct Addressing Hash Function
int directAddressing(int key) {
    return key % TABLE_SIZE;
}

// Linear Probing Hash Function
int linearProbing(int key, int i) {
    return (directAddressing(key) + i) % TABLE_SIZE;
}

// Quadratic Probing Hash Function
int quadraticProbing(int key, int i) {
    return (directAddressing(key) + i * i) % TABLE_SIZE;
}

// Double Hashing Function
int doubleHashing(int key, int i) {
    int hash1 = directAddressing(key);
    int hash2 = PRIME - (key % PRIME);
    return (hash1 + i * hash2) % TABLE_SIZE;
}

// Insert a key using linear probing
void insertLinear(int key) {
    int i = 0, index;
    while (i < TABLE_SIZE) {
        index = linearProbing(key, i);
        if (hashTable[index] == -1) {
            hashTable[index] = key;
            return;
        }
        i++;
    }
    printf("Table is full, cannot insert key %d\n", key);
}

// Insert a key using quadratic probing
void insertQuadratic(int key) {
    int i = 0, index;
    while (i < TABLE_SIZE) {
        index = quadraticProbing(key, i);
        if (hashTable[index] == -1) {
            hashTable[index] = key;
            return;
        }
        i++;
    }
    printf("Table is full, cannot insert key %d\n", key);
}

// Insert a key using double hashing
void insertDoubleHash(int key) {
    int i = 0, index;
    while (i < TABLE_SIZE) {
        index = doubleHashing(key, i);
        if (hashTable[index] == -1) {
            hashTable[index] = key;
            return;
        }
        i++;
    }
    printf("Table is full, cannot insert key %d\n", key);
}

// Display the hash table
void display() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] != -1)
            printf("Index %d: %d\n", i, hashTable[i]);
        else
            printf("Index %d: ~\n", i);
    }
}

int main() {
    // Initialize hash table with -1 (indicating empty slots)
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = -1;
    }
    
    // Insert keys using different probing methods
    insertLinear(10);
    insertLinear(20);
    insertLinear(30);
    insertQuadratic(25);
    insertQuadratic(35);
    insertDoubleHash(45);
    insertDoubleHash(50);
    
    printf("Hash Table:\n");
    display();
    
    return 0;
}
