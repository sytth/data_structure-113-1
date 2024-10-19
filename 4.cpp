#include <iostream>
#include <cstring>

#define SIZE 100

using namespace std;

class Queue
{
public:
    Queue()
    { 
        top = 0;    //起始端
        bot = -1;   //尾端
        count = 0;  //計算幾個數字
    }

    //先加bot再存入data，這樣最後才會保存最終尾端位置
    int enqueue(int data){
        if(count >= SIZE){
            return -1; 
        }
            

        /*  當bot達到陣列的最後一個位置（SIZE - 1）時，再加 1 就會變成 SIZE。
            (bot + 1) % SIZE 的結果會變成 0，這樣 bot 就可以回到陣列的開頭。
            其他時候bot不會變   */
        bot = (bot + 1) % SIZE;

        this->data[bot] = data;
        count++;
        return 1;
    }


    int *dequeue(){
        if(count <= 0){
            return NULL;
        }
        int *temp = &data[top];
        top = (top + 1) % SIZE;
        count--;
        return temp;
    }
private:
    int data[SIZE];
    int top, bot,count;
};

int main()
{
    int data, *temp;
    char command[50];
    Queue *queue = new Queue();
    while(1)
    {
        cin>>command;
        if(strcmp(command, "exit") == 0)
        {
            break;
        }
        else if(strcmp(command, "enqueue") == 0)
        {
            cout<<"Please input a integer data:";
            cin>>data;
            if(queue->enqueue(data) == 1)
            {
                cout<<"Successfully enqueue data "<<data<<" into queue."<<endl;
            }
            else
            {
                cout<<"Failed to enqueue data into queue."<<endl;
            }
        }
        else if(strcmp(command, "dequeue") == 0) 
        {
            temp = queue->dequeue();
            if(temp == NULL)
            {
                cout<<"Failed to dequeue a data from queue.\n";
            }
            else
            {
                cout<<"Dequeue data "<<*temp<<" from queue."<<endl;
            }
        }
    }
}
