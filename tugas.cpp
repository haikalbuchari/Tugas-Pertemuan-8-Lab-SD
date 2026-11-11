#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int TABLE_SIZE = 10;


const int EMPTY_SLOT = 0;
const int OCCUPIED   = 1;
const int DELETED    = 2;

class HashTable {
private:
    vector<pair<int, string>> table;
    vector<int> status;

    
    int hash1(int key) {
        return key % TABLE_SIZE;
    }

   
    int hash2(int key) {
        return 7 - (key % 7);
    }

public:
    HashTable() {
        table.resize(TABLE_SIZE);
        status.resize(TABLE_SIZE, EMPTY_SLOT);
    }

    void insert(int key, string value) {
        int index = hash1(key);
        int step = hash2(key);
        int initialIndex = index;

        int deletedIndex = -1;

        while (true) {
            // Key sudah ada -> update value
            if (status[index] == OCCUPIED && table[index].first == key) {
                table[index].second = value;
                cout << "Key " << key << " diperbarui" << endl;
                return;
            }

            
            if (status[index] == DELETED && deletedIndex == -1) {
                deletedIndex = index;
            }

            
            if (status[index] == EMPTY_SLOT) {
                if (deletedIndex != -1) {
                    index = deletedIndex;
                }

                table[index] = make_pair(key, value);
                status[index] = OCCUPIED;
                cout << "Key " << key << " disimpan di index " << index << endl;
                return;
            }

            index = (index + step) % TABLE_SIZE;

            if (index == initialIndex) {
                break;
            }
        }

       
        if (deletedIndex != -1) {
            table[deletedIndex] = make_pair(key, value);
            status[deletedIndex] = OCCUPIED;
            cout << "Key " << key << " disimpan di index " << deletedIndex << endl;
        } else {
            cout << "Table penuh" << endl;
        }
    }

    void search(int key) {
        int index = hash1(key);
        int step = hash2(key);
        int initialIndex = index;

        while (status[index] != EMPTY_SLOT) {
            if (status[index] == OCCUPIED && table[index].first == key) {
                cout << "Data ditemukan : " << table[index].second << endl;
                return;
            }

            index = (index + step) % TABLE_SIZE;

            if (index == initialIndex) {
                break;
            }
        }

        cout << "Data tidak ditemukan" << endl;
    }

    void remove(int key) {
        int index = hash1(key);
        int step = hash2(key);
        int initialIndex = index;

        while (status[index] != EMPTY_SLOT) {
            if (status[index] == OCCUPIED && table[index].first == key) {
                status[index] = DELETED;
                cout << "Data berhasil dihapus" << endl;
                return;
            }

            index = (index + step) % TABLE_SIZE;

            if (index == initialIndex) {
                break;
            }
        }

        cout << "Data tidak ditemukan" << endl;
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << " : ";

            if (status[i] == OCCUPIED) {
                cout << table[i].first << " - " << table[i].second;
            } else if (status[i] == DELETED) {   
                cout << "DELETED";
            } else {
                cout << "EMPTY";
            }

            cout << endl;
        }
    }
};

int main() {
    HashTable ht;

    ht.insert(23, "Andi");
    ht.insert(43, "Budi");
    ht.insert(13, "Citra");
    ht.insert(35, "Dewi");

    cout << "\nIsi Hash Table : " << endl;
    ht.display();

    cout << "\nMencari key 43 : " << endl;
    ht.search(43);

    cout << "\nMenghapus key 43 : " << endl;
    ht.remove(43);

    cout << "\nMencari key 43 setelah dihapus : " << endl;
    ht.search(43);

    cout << "\nHash Table setelah penghapusan : " << endl;
    ht.display();

    return 0;
}