#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>
using namespace std;

// Renamed to QueueNode to avoid conflict with Stack's Node
class QueueNode {
public:
    string track;
    QueueNode* next;

    QueueNode(const string& t) : track(t), next(nullptr) {}
};

class Queue {
private:
    QueueNode* first;
    QueueNode* last;
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
            cout << "[Queue] Full!" << endl;
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
            cout << "[Queue] Empty!" << endl;
            return "";
        }

        QueueNode* temp = first;
        string nextTrack = temp->track;

        first = first->next;

        if (first == nullptr) {
            last = nullptr;
        }

        delete temp;
        size--;
        return nextTrack;
    }

    string front() {
        if (isempty()) {
            return "Empty";
        }
        return first->track;
    }

    // --- NEW METHOD ---
    void displayQueue() {
        if (isempty()) {
            cout << "   (Queue is empty)" << endl;
            return;
        }

        QueueNode* current = first;
        int count = 1;
        while (current != nullptr) {
            cout << "   " << count << ". " << current->track << endl;
            current = current->next;
            count++;
        }
    }
};

#endif