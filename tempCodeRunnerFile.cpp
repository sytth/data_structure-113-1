#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <queue>
#include <vector>
#include <map>
#include <set>

using namespace std;

template <class T>
class Node
{
public:
	Node()
	{
		data = new T;
	}
	Node(T d)
	{
		data = new T;
		(*data) = d;
	}
	Node &operator=(T d)
	{
		(*data) = d;
		return *this;
	}
	friend std::ostream &operator<<(std::ostream &out, Node n)
	{
		out<<*(n.data);
		return out;
	}
	friend std::ostream &operator<<(std::ostream &out, Node *n)
	{
		out<<*(n->data);
		return out;
	}
	void setData(T d)
	{
		*data = d;
	}
	T &getData() const
	{
		return *data;
	}
protected:
	T *data;
};

template<class T>
class ListNode : public Node<T>
{
public:
	ListNode() : Node<T>()
	{
		prev = NULL;
		next = NULL;
	}
	ListNode(T d) : Node<T>(d)
	{
		prev = NULL;
		next = NULL;
	}
	ListNode(ListNode *p, ListNode *n) : Node<T>()
	{
		prev = p;
		next = n;
	}
	ListNode(T d, ListNode *p, ListNode *n) : Node<T>(d)
	{
		prev = p;
		next = n;
	}
	ListNode *getNext() const
	{
		return next;
	}
	ListNode *getPrev() const
	{
		return prev;
	}
	void setNext(ListNode *n)
	{
		next = n;
	}
	void setPrev(ListNode *p)
	{
		prev = p;
	}
	ListNode &operator=(T d)
	{
		this->setData(d);
		return *this;
	}
private:
	ListNode *prev, *next;
};

template<class T>
class LinkList
{
public:
	LinkList()
	{
		head = NULL;
		tail = NULL;
	}
	void addFromHead(T d)
	{
		ListNode<T> *node = new ListNode<T>(d);
		if(head != NULL)
		{
			head->setPrev(node);
		}
		node->setNext(head);
		head = node;
		if(tail == NULL)
			tail = node;
	}
	void addFromTail(T d)
	{
		ListNode<T> *node = new ListNode<T>(d);
		if(tail != NULL)
		{
			tail->setNext(node);
		}
		node->setPrev(tail);
		tail = node;
		if(head == NULL)
			head = node;
	}
	void addAfter(ListNode<T> *at, T d)
	{
		if(!exist(at))
			return;
		ListNode<T> *node = new ListNode<T>(d);
		if(at->getNext() != NULL)
			at->getNext()->setPrev(node);
		node->setNext(at->getNext());
		at->setNext(node);
		node->setPrev(at);
		if(node->getNext() == NULL)
			tail = node;
	}
	ListNode<T> *removeFromHead()
	{
		ListNode<T> *n = head;
		if(head != NULL)
		{
			head = head->getNext();
			if(head != NULL)
				head->setPrev(NULL);
			else
				tail = NULL;
			n->setNext(NULL);
		}
		return n;
	}
	ListNode<T> *removeFromTail()
	{
		ListNode<T> *n = tail;
		if(tail != NULL)
		{
			tail = tail->getPrev();
			if(tail != NULL)
				tail->setNext(NULL);
			else
				head = NULL;
			n->setPrev(NULL);
		}
		return n;
	}
	ListNode<T> *remove(ListNode<T> *n)
	{
		if(!exist(n))
			return NULL;
		if(n == head)
			return removeFromHead();
		if(n == tail)
			return removeFromTail();
		n->getPrev()->setNext(n->getNext());
		n->getNext()->setPrev(n->getPrev());
		n->setNext(NULL);
		n->setPrev(NULL);
		return n;
	}
	ListNode<T> *exist(T d)
	{
		ListNode<T> *j = head;
		while(j != NULL)
		{
			if(j->getData() == d)
				return j;
			j = j->getNext();
		}
		return NULL;
	}
	bool exist(ListNode<T> *n)
	{
		ListNode<T> *j = head;
		while(j != NULL)
		{
			if(j == n)
				return true;
			j = j->getNext();
		}
		return false;
	}
	ListNode<T> &operator[](int i)
	{
		ListNode<T> *j = head;
		int k;
		for(k = 0;k < i && j != NULL;k ++)
			j = j->getNext();
		if(j == NULL)
			throw std::invalid_argument("index does not exist.");
		return *j;
	}
	void print() const
	{
		ListNode<T> *j;
		j = head;
		while(j != NULL)
		{
			std::cout<<(*j)<<" ";
			j = j->getNext();
		}
		std::cout<<std::endl;
	}
protected:
	ListNode<T> *head, *tail;
};

template<class V, class E>
class WeightedGraphEdge;

template<class V, class E>
class WeightedGraphVertex : public Node<V>
{
public:
	WeightedGraphVertex() :Node<V>()
	{
		list = new LinkList<E>();
	}
	WeightedGraphVertex(V d) :Node<V>(d)
	{
		list = new LinkList<WeightedGraphEdge<V, E> *>();
	}
	void addEdge(WeightedGraphEdge<V, E> *edge)
	{
		list->addFromTail(edge);
	}
	void remove(WeightedGraphEdge<V, E> *node)
	{
	}
	ListNode<WeightedGraphEdge<V, E> *> *operator[](int n)
	{
		try
		{
			return (&(*list)[n]);
		}
		catch(std::invalid_argument e)
		{
			return NULL;
		}
	}
private:
	LinkList<WeightedGraphEdge<V, E> *> *list;
};

template<class V, class E>
class WeightedGraphEdge : public Node<E>
{
public:
	WeightedGraphEdge() : Node<E>()
	{
		end[0] = NULL;
		end[1] = NULL;
	}
	WeightedGraphEdge(E d) : Node<E>(d)
	{
		end[0] = NULL;
		end[1] = NULL;
	}
	WeightedGraphEdge(E d, WeightedGraphVertex<V, E> *v1, WeightedGraphVertex<V, E> *v2) : Node<E>(d)
	{
		end[0] = v1;
		end[1] = v2;
	}
	WeightedGraphVertex<V, E> *&getAnotherEnd(WeightedGraphVertex<V, E> *v)
	{
		if(v != end[0])
			return end[0];
		return end[1];
	}
private:
	WeightedGraphVertex<V, E> *end[2];
};


// 定義比較函數，讓 queue 可以根據邊的權重排序
template <class V, class E>
struct CompareEdges {
    bool operator()(WeightedGraphEdge<V, E> *a, WeightedGraphEdge<V, E> *b) {
        return a->getData() > b->getData(); // 小的權重優先
    }
};

template<class V, class E>
class WeightedGraph
{
public:
	WeightedGraph()
	{
		vertex = new LinkList<WeightedGraphVertex<V, E> *>();
		edge = new LinkList<WeightedGraphEdge<V, E> *>();
	}
	WeightedGraphVertex<V, E> *operator[](int n)
	{
		try
		{
			return (*vertex)[n].getData();
		}
		catch(std::invalid_argument e)
		{
			return NULL;
		}
	}
	void addLink(WeightedGraphVertex<V, E> *v1, WeightedGraphVertex<V, E> *v2, E w)
	{
		WeightedGraphEdge<V, E> *edge = new WeightedGraphEdge<V, E>(w, v1, v2);
		v1->addEdge(edge);
		if(v1 != v2)
			v2->addEdge(edge);
	}
	WeightedGraphVertex<V, E> *addVertex(V d)
	{
		WeightedGraphVertex<V, E> *v = new WeightedGraphVertex<V, E>(d);
		vertex->addFromTail(v);
		vertexCount ++;
		return v;
	}
	void adjList()
	{
		ListNode<WeightedGraphVertex<V, E> *> *cur = &(*vertex)[0];
		while(cur != NULL)
		{
			WeightedGraphVertex<V, E> *temp = cur->getData();
			std::cout<<temp<<": ";
			ListNode<WeightedGraphEdge<V, E> *> *e = (*temp)[0];
			while(e != NULL)
			{
				std::cout<<e->getData()->getAnotherEnd(temp)<<"("<<e->getData()<<") ";
				e = e->getNext();
			}
			std::cout<<std::endl;
			cur = cur->getNext();
		}
	}


	WeightedGraph *minimumSpanningTree(WeightedGraphVertex<V, E> *v){
        if (!vertex->exist(v)) {
            return nullptr; // 如果起始節點不存在，return nullptr
        }

        // 儲存最小生成樹的結構
        // 記錄已訪問的節點
        // queue 根據邊的權重排序
        auto *mst = new WeightedGraph<V, E>();
        set<WeightedGraphVertex<V, E> *> visited;
        priority_queue<WeightedGraphEdge<V, E> *, vector<WeightedGraphEdge<V, E> *>, CompareEdges<V, E>> edgeQueue;

        // 起始點加到 mst
        auto *startVertex = mst->addVertex(v->getData());
        visited.insert(v);

        // 將與起始點相鄰的邊加入 queue
        ListNode<WeightedGraphEdge<V, E> *> *curEdge = (*v)[0];
        while (curEdge != nullptr) {
            // 檢查是否已訪問過另一端節點，未被訪問過才將該邊加入 queue
            if (!visited.count(curEdge->getData()->getAnotherEnd(v))) {
                edgeQueue.push(curEdge->getData());
            }
            curEdge = curEdge->getNext();
        }

        // 開始構建 mst
        while (!edgeQueue.empty()) {
            auto *edge = edgeQueue.top();   // 取出權重最小的邊
            edgeQueue.pop();                // 移除

            WeightedGraphVertex<V, E> *v1 = edge->getAnotherEnd(v); // 一端
            WeightedGraphVertex<V, E> *v2 = edge->getAnotherEnd(v1); // 另一端

            // if 兩端點都已訪問，此邊會形成環，跳過。
            if (visited.count(v1) && visited.count(v2)) {
                continue;
            }

            // 找到未訪問的節點，加入 MST
            WeightedGraphVertex<V, E> *newVertex = nullptr;
            if (!visited.count(v1)) {
                newVertex = mst->addVertex(v1->getData());
                visited.insert(v1);
            } else {
                newVertex = mst->addVertex(v2->getData());
                visited.insert(v2);
            }

            mst->addLink(startVertex, newVertex, edge->getData());

            // 將新的節點的相鄰邊加入優先佇列
            curEdge = (*newVertex)[0];
            while (curEdge != nullptr) {
                if (!visited.count(curEdge->getData()->getAnotherEnd(newVertex))) {
                    edgeQueue.push(curEdge->getData());
                }
                curEdge = curEdge->getNext();
            }
        }

        return mst;

	}
private:
	LinkList<WeightedGraphVertex<V, E> *> *vertex;
	LinkList<WeightedGraphEdge<V, E> *> *edge;
	int vertexCount, edgeCount;
};

int main()
{
	WeightedGraph<char, int> *g = new WeightedGraph<char, int>();
	WeightedGraph<char, int> *tree;
	int j, k, i, l;
	srand(time(NULL));
	for(j = 0;j < 5;j++)
	{
		g->addVertex(j + 'a');
	}
	for(j = 0;j < 5;j ++)
    {
        k = rand() % 5;
        i = rand() % 5;
        l = rand() % 100;
        g->addLink((*g)[k], (*g)[i], l);
    }
	g->adjList();
	tree = g->minimumSpanningTree((*g)[0]);
	tree->adjList();
	return 0;
}
