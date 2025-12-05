#ifndef STACK_DS_H
#define STACK_DS_H

#include <iostream>
#include <string>

using namespace std;

// Структура теперь Машина, а не Песня
struct Car {
    string id;      // Номер машины (Car ID)
    int moves;      // (Опционально) сколько раз ее двигали, но пока хватит ID
};

struct StackNode {
    Car data;
    StackNode* next;
};

class ParkingLaneStack { // Переименовали из PlayNextStack
private:
    StackNode* topNode;
    int count;          // Текущее количество машин
    int capacity;       // Вместимость парковки (по заданию)

public:
    ParkingLaneStack(int cap = 5) { // По умолчанию 5 мест
        topNode = nullptr;
        count = 0;
        capacity = cap;
    }

    ~ParkingLaneStack() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() {
        return topNode == nullptr;
    }

    bool isFull() {
        return count == capacity;
    }

    void push(Car newCar) {
        if (isFull()) {
            cout << ">> Parking Full! Cannot park Car " << newCar.id << endl;
            return;
        }
        StackNode* newNode = new StackNode();
        newNode->data = newCar;
        newNode->next = topNode;
        topNode = newNode;
        count++;

        // cout << "[Stack] Car Parked: " << newCar.id << endl;
    }

    Car pop() {
        if (isEmpty()) {
            return {"", 0};
        }

        StackNode* temp = topNode;
        Car poppedCar = topNode->data;
        topNode = topNode->next;

        delete temp;
        count--;
        return poppedCar;
    }

    Car peek() {
        if (isEmpty()) {
            return {"", 0};
        }
        return topNode->data;
    }

    void displayStack() {
        if (isEmpty()) {
            cout << "   (Lane is Empty)\n";
            return;
        }

        StackNode* current = topNode;
        cout << "(EXIT) -> ";
        while (current != nullptr) {
            cout << "[" << current->data.id << "] ";
            current = current->next;
        }
        cout << " -> (WALL)" << endl;
    }
};

#endif