#include <iostream>
#include <cstdlib>
#include <ctime>

#define SIZE 100

using namespace std;

class Node
{
public:
    Node()
    {
        next = NULL;
        pre = NULL;
    }
    Node(int n)
    {
        data = n;
        next = NULL;
        pre = NULL;
    }
    int getData() { return data; }
    Node *getNext() { return next; }
    Node *getPre() { return pre; }
    void setData(int d) { data = d; }
    void setNext(Node *n) { next = n; }
    void setPre(Node *p) { pre = p; }

private:
    int data; 
    Node *next, *pre;  // 下一個節點與前一個節點的指標
};

class List
{
public:
    List() { list = NULL; }
    List(int n) { generate(n); }

    // 在list中產生n個隨機數字
    void generate(int n)
    {
        int j;
        list = NULL;
        for (j = 0; j < n; j++)
            generate();
    }

    // 產生一個隨機數字存到list中
    void generate()
    {
        Node *buf = new Node(rand() % 100);  // 隨機產生0到99的數值
        buf->setNext(list);
        if (list != NULL)
            list->setPre(buf);
        list = buf;
    }

    // 泡沫排序法
    void bubbleSort()
    {
        bool swapped;  // 用來判斷是否交換過
        Node *cur;
        Node *last = NULL;  // 記錄最後一個已經比大小的節點

        do{
            swapped = false;
            cur = list;

            // 前後節點比較，交換data
            while (cur->getNext() != last)
            {
                if (cur->getData() > cur->getNext()->getData())
                {
                    // 交換節點中的data
                    int temp = cur->getData();
                    cur->setData(cur->getNext()->getData());
                    cur->getNext()->setData(temp);
                    swapped = true;  // 記錄這次有進行交換
                }
                cur = cur->getNext();  // 移動到下一個節點
            }
            last = cur;  // 更新最後一個已經比大小的節點

        } while (swapped);  // 直到沒有交換
    }

    // 選擇排序法
    void selectionSort()
    {
        Node *cur = list;

        while (cur != NULL){
            Node *minNode = cur;  // 假設現在為最小值
            Node *next = cur->getNext();

            // 在未排序部分找到最小值
            while (next != NULL){
                if (next->getData() < minNode->getData())
                    minNode = next;
                next = next->getNext();
            }

            // 將最小值與當前節點的數據交換
            int temp = cur->getData();
            cur->setData(minNode->getData());
            minNode->setData(temp);

            cur = cur->getNext();  // 移動到下一個節點
        }
    }

    // 插入排序法
    void insertionSort()
    {
        if (list == NULL)
            return;

        Node *sorted = NULL;  // 已排序部分
        Node *cur = list;

        while (cur != NULL){
            Node *next = cur->getNext();  // 保存下一個節點

            // 還沒有排序 或 已排序部分比較大
            if (sorted == NULL || sorted->getData() >= cur->getData()){
                // 插入到已排序的最前面
                cur->setNext(sorted);
                if (sorted != NULL)
                    sorted->setPre(cur);
                sorted = cur;
                sorted->setPre(NULL);
            }
            else{
                Node *temp = sorted;

                // 找到插入點，讓插入後保持排序
                while (temp->getNext() != NULL && temp->getNext()->getData() < cur->getData())
                {
                    temp = temp->getNext();
                }

                // 插入到已排序部分
                cur->setNext(temp->getNext());
                if (temp->getNext() != NULL)
                    temp->getNext()->setPre(cur);
                temp->setNext(cur);
                cur->setPre(temp);
            }

            cur = next;  // 繼續處理下一個未排序節點
        }
        list = sorted;
    }

    void print()
    {
        Node *cur = list;
        while (cur != NULL){
            cout << cur->getData() << " ";
            cur = cur->getNext();
        }
        cout << endl;
    }

private:
    Node *list; 
};

int main()
{
    srand(time(NULL));

    List *l = new List(10);
    l->print();
    l->bubbleSort();
    l->print();

    l = new List(10);
    l->print();
    l->insertionSort();
    l->print();

    l = new List(10);
    l->print();
    l->selectionSort();
    l->print();
}
