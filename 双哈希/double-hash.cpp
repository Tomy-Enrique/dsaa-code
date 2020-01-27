/*
Lab Work 09-1. Double Hashing

Note. Programming in C/C++, including <iostream>/<iostream.h> and <cstdlib>/<cstdlib.h>only

Consider a hash table with M = 64 bins. Given a 24-bit unsigned number, take the lowest 8 bits as the primary hash function (bin number), and the highest 8 bits as the secondary hash function (jump size).

Determine the array structures for a hash table
Hash a list of 32 random 24-bit positive numbers
Calculate the average number of probes
(End)
*/

/*
 考虑一个64bins的哈希表，给定一个24位无符号的无符号数，
 取低8位作为主哈希函数（抛出数），高8位作为辅助哈希函数（跳转大小）

 Hash1(key) = Lowest 6 bits
 Hash2(key) = Highet 6 bits
 (hash1(key) + i * hash2(key)) % TABLE_SIZE
*/

#include <iostream>
#include <cstdlib> 
using namespace std;
#define Hash_Size 64

//24位无符号数数据结构
struct int24 {
    unsigned int data : 24;
};

//哈希表数据结构
typedef struct {
    int24* Array;
    int KeyNum;
}HashTable;

HashTable CreateHash(int Size) {
    HashTable* H;
    H = (HashTable*)malloc(sizeof(HashTable));
    (*H).Array = (int24*)malloc(sizeof(int24) * Hash_Size);
    for (int i = 0; i < Hash_Size; i++) {
        H->Array[i].data = 0;
    }
    (*H).KeyNum = 0;
    return *H;
}

bool IsFull(HashTable* H) {
    return (*H).KeyNum == Hash_Size;
}

int Hash1(int24 k) {
    int temp;
    temp = k.data % 64;     //取低6位
    return temp;
}

int Hash2(int24 k) {
    int temp;
    temp = k.data >> 18;    //取高6位
    return temp;
}

void InsertHash(HashTable* H, int24 k, int* Probs) {
    if (IsFull(H)) {
        return;
    }
    //(hash1(key) + i * hash2(key)) % TABLE_SIZE
    int index1 = Hash1(k);
    //int index2 = Hash2(k);
    if ((*H).Array[index1].data != 0) {
        int index2 = Hash2(k);
        int i = 1;
        while (true) {
            int newIndex = (index1 + i * index2) % Hash_Size;

            if ((*H).Array[newIndex].data == 0) {
                (*H).Array[newIndex].data = k.data;
                break;
            }
            i++;
        }
        (*Probs) += i+1;
    }
    else {
        (*H).Array[index1] = k;
        (*Probs)++;
    }
    (*H).KeyNum++;
    //return Probs;
}

void Display(HashTable* H) {
    for (int i = 0; i < Hash_Size; i++) {
        if ((*H).Array[i].data != 0) {
            cout << i << " --> "
                << (*H).Array[i].data << endl;
        }
        else {
            cout << i << endl;
        }
    }
}

int main()
{
    HashTable hashTable = CreateHash(Hash_Size);
    int24 randNum[32];
    int probs = 0;
    for (int i = 0; i < 32; i++) {
        int24 temp;
        temp.data = (rand() << 17) | (rand() << 3) | (rand());
        randNum[i].data = temp.data;
        //cout << temp.data << endl;
    }
    for (int i = 0; i < 32; i++) {
        InsertHash(&hashTable, randNum[i], &probs);
    }
    cout << "Hash Table: " << endl;
    Display(&hashTable);
    cout << "The number of probs: "<< probs << endl;
    cout << "The average number of probes is " << (double)probs/32 << endl;
}
