#include <iostream>
#include <string>
#include <windows.h> // Для русского языка (если нужно)

// Подключаем обновленные хедеры
#include "Stack_ds.h"
#include "QUEUE.h"

using namespace std;

int main() {
    SetConsoleOutputCP(65001); // UTF-8

    // 1. Создаем основные структуры
    // По заданию: One narrow parking lane (Stack)
    // Давайте сделаем вместимость 5 машин
    ParkingLaneStack parkingLane(5);

    // Temporary Holding Lane (Queue)
    TempQueue tempLane;

    // Предзаполним парковку как в примере PDF:
    // Bottom -> Car 10, Car 20, Car 30, Car 40 -> Top
    parkingLane.push({"Car 10"});
    parkingLane.push({"Car 20"});
    parkingLane.push({"Car 30"});
    parkingLane.push({"Car 40"});

    int choice = 0;
    bool isRunning = true;

    while (isRunning) {
        cout << "\n=========================================" << endl;
        cout << "   PARKING LOT MANAGEMENT SYSTEM         " << endl;
        cout << "=========================================" << endl;
        cout << "Current Lane Status:" << endl;
        parkingLane.displayStack();
        cout << "-----------------------------------------" << endl;
        cout << "1. Park a Car (Push to Stack)" << endl;
        cout << "2. Remove a Specific Car (The Main Logic)" << endl;
        cout << "3. Display All Cars" << endl;
        cout << "0. Exit" << endl;
        cout << "=========================================" << endl;
        cout << "Choice: ";

        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(10000, '\n'); choice = -1;
        }

        switch (choice) {
        case 1: {
            string id;
            cout << "Enter Car ID (e.g. 'Car 50'): ";
            cin.ignore();
            getline(cin, id);

            if (!id.empty()) {
                if (!parkingLane.isFull()) {
                    parkingLane.push({id});
                    cout << ">> Success: " << id << " parked." << endl;
                } else {
                    cout << ">> Error: Parking is FULL!" << endl;
                }
            }
            break;
        }

        case 2: {
            // ЛОГИКА ИЗ PDF (Remove Specific Car)
            if (parkingLane.isEmpty()) {
                cout << ">> Parking is empty. Nothing to remove." << endl;
                break;
            }

            string targetID;
            cout << "Enter Car ID to remove: ";
            cin.ignore();
            getline(cin, targetID);

            cout << "\n--- STARTING REMOVAL PROCESS ---" << endl;
            int moves = 0;
            bool found = false;

            // Шаг 1: Ищем машину, перекладывая верхние в Очередь
            // (Keep popping cars until you find the target)
            while (!parkingLane.isEmpty()) {
                Car topCar = parkingLane.peek();

                if (topCar.id == targetID) {
                    // НАШЛИ!
                    parkingLane.pop(); // Просто удаляем (машина уезжает)
                    moves++; // Удаление тоже считается движением (по PDF)
                    cout << ">> Target found: " << topCar.id << " removed! (Move #" << moves << ")" << endl;
                    found = true;
                    break; // Прерываем цикл поиска
                }
                else {
                    // Не та машина. Перемещаем во временную очередь
                    Car temp = parkingLane.pop();
                    tempLane.enqueue(temp.id);
                    moves++;
                    cout << ">> Moved " << temp.id << " to temp queue. (Move #" << moves << ")" << endl;
                }
            }

            if (!found) {
                cout << ">> Car " << targetID << " not found in the lane!" << endl;
            }

            // Шаг 2: Возвращаем машины из Очереди обратно в Стек
            // (Move cars from the queue back into the stack)
            cout << "--- RESTORING OTHER CARS ---" << endl;
            while (!tempLane.isempty()) {
                string tempID = tempLane.dequeue();
                parkingLane.push({tempID});
                moves++;
                cout << ">> Moved " << tempID << " back to stack. (Move #" << moves << ")" << endl;
            }

            cout << "---------------------------------" << endl;
            if (found) {
                cout << "Total moves required: " << moves << endl;
            } else {
                cout << "Car was not found. System restored." << endl;
            }
            break;
        }

        case 3: {
            cout << "\nParking Lane (Top to Bottom):" << endl;
            parkingLane.displayStack();
            break;
        }

        case 0:
            cout << "Exiting..." << endl;
            isRunning = false;
            break;

        default:
            cout << "Invalid choice." << endl;
        }
    }

    return 0;
}