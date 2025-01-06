#include <iostream>
using namespace std;

class Node {
public:
    int data;      // 節點的數值
    Node* next;    // 指向下一個節點的指標

    Node(int value) {
        data = value;
        next = nullptr;  // 初始時下一個節點指標為空
    }
};

class SinglyLinkedList {
private:
    Node* head;    // 指向鏈結串列的頭節點

public:
    SinglyLinkedList() {
        head = nullptr;
    }

    // 在尾端新增節點
    void append(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;  // 將新節點連接到最後一個節點
        }
    }

    // 計算鏈結串列的大小（節點數量）
    int size() {
        int count = 0;        
        Node* temp = head;    
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    // 輸出所有節點
    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << "\n";
            temp = temp->next;
        }
    }
};

int main() {
    SinglyLinkedList list;

    list.append(10);
    list.append(20);
    list.append(30);

    list.display();

    cout << "size: " << list.size() << endl;

    return 0;
}
