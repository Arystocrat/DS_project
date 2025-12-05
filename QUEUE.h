#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>
using namespace std;

// Узел очереди
class QueueNode {
public:
    string carID; // Храним просто ID машины
    QueueNode* next;

    QueueNode(const string& id) : carID(id), next(nullptr) {}
};

class TempQueue { // Переименовали в TempQueue
private:
    QueueNode* first;
    QueueNode* last;
    int size;

public:
    TempQueue() {
        first = nullptr;
        last = nullptr;
        size = 0;
    }

    ~TempQueue() {
        while (!isempty()) {
            dequeue();
        }
    }

    bool isempty() {
        return size == 0;
    }

    void enqueue(const string& carID) {
        QueueNode* newNode = new QueueNode(carID);

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
            return "";
        }

        QueueNode* temp = first;
        string val = temp->carID;

        first = first->next;

        if (first == nullptr) {
            last = nullptr;
        }

        delete temp;
        size--;
        return val;
    }

    // Метод для отображения (отладки)
    void displayQueue() {
        if (isempty()) {
            cout << "(Empty)";
            return;
        }
        QueueNode* curr = first;
        while(curr) {
            cout << "[" << curr->carID << "] ";
            curr = curr->next;
        }
    }
};

#endif