#include <iostream>
#include <cstdlib>
#include <ctime>

#define SIZE 10

using namespace std;

class Node {
public:
    Node() : row(0), col(0) {}
    Node(int r, int c) : row(r), col(c) {}

    int getRow() { return row; }
    int getCol() { return col; }
    void setRow(int r) {
        if (r >= 0 && r < SIZE)
            row = r;
    }
    void setCol(int c) {
        if (c >= 0 && c < SIZE)
            col = c;
    }

private:
    int row, col;
};

class List {
public:
    List() : top(0) {}

    void addElement(int r, int c) {
        if (top < SIZE * SIZE) {
            data[top++] = Node(r, c);
        }
    }

    Node *removeElement() {
        if (top > 0) {
            return &data[--top];
        }
        return NULL;
    }

    void printList() {
        for (int j = 0; j < top; j++) {
            cout << "(" << data[j].getRow() << ", " << data[j].getCol() << ")" << endl;
        }
    }

private:
    Node data[SIZE * SIZE];
    int top;
};

class Maze {
public:
    Maze() {
        initMaze(SIZE);
    }

    void initMaze(int s) {
        srand(time(NULL));
        maze = new int *[s];
        for (int i = 0; i < s; i++) {
            maze[i] = new int[s];
        }

        // 初始化迷宮
        for (int i = 0; i < s; i++) {
            for (int j = 0; j < s; j++) {
                maze[i][j] = (rand() % 100 < 20) ? 1 : 0; // 20% 牆壁
            }
        }

        // 確保起點和終點是空的
        maze[0][0] = 0;
        maze[s - 1][s - 1] = 0;
    }

    List *getPath() {
        List *path = new List();
        if (findPath(0, 0, path)) {
            return path;
        }
        delete path;
        return new List(); // 找不到路徑，回傳空的 List
    }

    void printMaze() {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                if (maze[j][k] == 0)
                    cout << " ";
                else if (maze[j][k] == 1)
                    cout << "*";
            }
            cout << "\n";
        }
    }

private:
    int **maze;

    bool findPath(int r, int c, List *path) {
        // 範圍檢查
        if (r < 0 || c < 0 || r >= SIZE || c >= SIZE || maze[r][c] == 1) {
            return false;
        }

        // 到達終點
        if (r == SIZE - 1 && c == SIZE - 1) {
            path->addElement(r, c);
            return true;
        }

        // 標記為已訪問
        maze[r][c] = 1;

        // 嘗試四個方向
        if (findPath(r + 1, c, path) || findPath(r, c + 1, path) || findPath(r - 1, c, path) || findPath(r, c - 1, path)) {
            path->addElement(r, c);
            return true;
        }

        // 回溯
        maze[r][c] = 0;
        return false;
    }
};

int main() {
    Maze *maze = new Maze();
    maze->printMaze();
    List *path = maze->getPath();
    path->printList();
    delete maze;
    delete path;
}
