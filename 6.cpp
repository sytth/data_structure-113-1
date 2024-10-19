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
    Node *next, *pre;
};

class List
{
public:
    List() { list = NULL; }
    List(int n) { generate(n); }

    // 在list中產生n個隨機數字
    void generate(int n)
    {
        list = NULL;
        for (int j = 0; j < n; j++)
            generate();
    }

    // 產生一個隨機數字存到list中
    void generate()
    {
        Node *buf = new Node(rand() % 100);  // 隨機生成 0-99 的數據
        buf->setNext(list);
        if (list != NULL)
            list->setPre(buf);
        list = buf;
    }

    // 輔助函數：交換兩個pointer
    void swapNodes(Node *a, Node *b)
    {
        if (a == b)
            return;

        Node *aPre = a->getPre();
        Node *aNext = a->getNext();
        Node *bPre = b->getPre();
        Node *bNext = b->getNext();

        // 如果 a 和 b 是相鄰節點
        if (aNext == b)
        {
            if (aPre != NULL)
                aPre->setNext(b);
            if (bNext != NULL)
                bNext->setPre(a);

            b->setPre(aPre);
            a->setNext(bNext);

            b->setNext(a);
            a->setPre(b);
        }
        else if (bNext == a) // 如果 b 和 a 是相鄰節點
        {
            if (bPre != NULL)
                bPre->setNext(a);
            if (aNext != NULL)
                aNext->setPre(b);

            a->setPre(bPre);
            b->setNext(aNext);

            a->setNext(b);
            b->setPre(a);
        }
        else // 如果 a 和 b 不相鄰
        {
            if (aPre != NULL)
                aPre->setNext(b);
            if (aNext != NULL)
                aNext->setPre(b);
            if (bPre != NULL)
                bPre->setNext(a);
            if (bNext != NULL)
                bNext->setPre(a);

            // 交換前後指標
            a->setPre(bPre);
            a->setNext(bNext);
            b->setPre(aPre);
            b->setNext(aNext);
        }

        // 如果 a 或 b 是頭節點，則需要更新頭指標
        if (list == a)
            list = b;
        else if (list == b)
            list = a;
    }

    // 泡沫排序法
    void bubbleSort()
    {
        if (list == NULL || list->getNext() == NULL)
            return;

        bool swapped;
        Node *last = NULL;

        do {
            swapped = false;
            Node *cur = list;

            while (cur->getNext() != last)
            {
                Node *nextNode = cur->getNext();
                if (cur->getData() > nextNode->getData())
                {
                    swapNodes(cur, nextNode);
                    swapped = true;

                    // 因為節點位置改變，cur 應該保持不變以檢查新的 cur->getNext()
                    continue;
                }
                cur = cur->getNext();
            }
            last = cur;  // 每次把最右邊的節點設為已排序
        } while (swapped);
    }

    // 選擇排序法
    void selectionSort()
    {
        Node *cur = list;

        while (cur != NULL)
        {
            Node *minNode = cur;
            Node *next = cur->getNext();

            // 找到最小值
            while (next != NULL)
            {
                if (next->getData() < minNode->getData())
                    minNode = next;
                next = next->getNext();
            }

            // 如果最小值節點不是當前節點才交換
            if (cur != minNode)
            {
                swapNodes(cur, minNode);

                // 確保 cur 保持在原來的位置
                cur = minNode;
            }

            cur = cur->getNext();
        }
    }

    // 插入排序法
    void insertionSort()
    {
        if (list == NULL)
            return;

        Node *sorted = NULL;  // 已排序部分
        Node *cur = list;

        while (cur != NULL)
        {
            Node *next = cur->getNext();  // 儲存下一個未排序節點

            if (sorted == NULL || sorted->getData() >= cur->getData()){
                cur->setNext(sorted);
                sorted = cur;
                sorted->setPre(NULL);
            }
            else
            {
                Node *temp = sorted;

                // 找到正確的插入位置
                while (temp->getNext() != NULL && temp->getNext()->getData() < cur->getData())
                    temp = temp->getNext();

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
        while (cur != NULL)
        {
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

    return 0;
}
