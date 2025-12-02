#include <iostream>
using namespace std;

class QueueNode {
public:
    string track;
    QueueNode* next;

    QueueNode(const string& t) : track(t), next(nullptr) {}
};

class Queue {
private:
    QueueNode* first;  // указатель на первый элемент
    QueueNode* last;   // указатель на последний элемент
    int size;
    const int MAX = 50;

public:
    Queue() {
        first = nullptr;
        last = nullptr;
        size = 0;
    }

    ~Queue() {
        while (!isempty()) {
            dequeue();
        }
    }

    bool isempty() {
        return size == 0;
    }

    bool isfull() {
        return size == MAX;
    }

    void enqueue(const string& track) {
        if (isfull()) {
            cout << "queue is full" << endl;
            return;
        }

        QueueNode* newNode = new QueueNode(track);

        if (isempty()) {
            first = newNode;
            last = newNode;
        }
        else {
            last->next = newNode;
            last = newNode;
        }

        size++;
    }

    string dequeue() {
        if (isempty()) {
            cout << "queue is empty" << endl;
            return "";
        }

        QueueNode* temp = first;
        string next = temp->track;

        first = first->next;

        if (first == nullptr) {
            last = nullptr;
        }

        delete temp;
        size--;
        return next;
    }

    string front() {
        if (isempty()) {
            cout << "queue is empty" << endl;
            return "";
        }
        return first->track;
    }
};

