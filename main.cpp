#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <windows.h> // Для русского языка

// Подключаем ваши хедеры
#include "arraym.h"
#include "QUEUE.h"
#include "Stack_ds.h"

using namespace std;

// Функция имитации проигрывания
void playTrackDisplay(string title, string artist = "", int duration = 2) {
    cout << "\n------------------------------------------------" << endl;
    cout << " >> [PLAYING NOW] ♫ " << title;
    if (!artist.empty()) cout << " - " << artist;
    cout << " ♫" << endl;
    cout << "------------------------------------------------" << endl;

    // Имитация прогресс-бара
    cout << "Loading: [";
    for(int i=0; i<10; i++) {
        cout << "#";
        this_thread::sleep_for(chrono::milliseconds(duration * 100));
    }
    cout << "] Done.\n" << endl;
}

int main() {
    SetConsoleOutputCP(65001); // Русский язык в консоли

    // Инициализация структур
    Arraymethod library;       // Библиотека
    Queue standardQueue;       // Очередь
    PlayNextStack priorityStack; // Стек (срочное)

    // 1. Предварительно заполним библиотеку (чтобы было из чего выбирать)
    library.append("Linkin Park - Numb");
    library.append("Daft Punk - Get Lucky");
    library.append("Queen - Bohemian Rhapsody");
    library.append("Metallica - Enter Sandman");
    library.append("Eminem - Lose Yourself");
    library.append("Hans Zimmer - Time");

    int choice = 0;
    bool isRunning = true;

    while (isRunning) {
        cout << "=========================================" << endl;
        cout << "         МУЗЫКАЛЬНЫЙ ПЛЕЕР v2.0          " << endl;
        cout << "=========================================" << endl;
        cout << "1. Показать библиотеку (все треки)" << endl;
        cout << "2. Добавить трек в Очередь (по индексу)" << endl;
        cout << "3. 'Играть следующим' (Play Next - Стек)" << endl;
        cout << "4. Показать, что будет играть (Status)" << endl;
        cout << "5. >> ИГРАТЬ ТРЕК (Next Track) >>" << endl;
        cout << "0. Выход" << endl;
        cout << "=========================================" << endl;
        cout << "Ваш выбор: ";

        if (!(cin >> choice)) { // Защита от ввода букв
            cin.clear();
            cin.ignore(10000, '\n');
            choice = -1;
        }

        switch (choice) {
        case 1: {
            cout << "\n--- БИБЛИОТЕКА ---" << endl;
            library.display();
            break;
        }

        case 2: {
            int idx;
            cout << "Введите индекс трека из библиотеки: ";
            cin >> idx;
            // Простейшая проверка (так как в классе нет getLength, рискуем, но надеемся на пользователя)
            // Лучше добавить метод getLength() в Arraymethod, но пока просто пробуем:
            string track = library.getbyindex(idx);
            // Если индекс плохой, программа может упасть (нужна доработка Arraymethod),
            // но если ввели верно:
            standardQueue.enqueue(track);
            cout << "[OK] Добавлено в хвост очереди: " << track << endl;
            break;
        }

        case 3: {
            // Стек требует структуру Song, вводим данные вручную
            string t, a;
            int d;
            cout << "Введите название песни: ";
            cin.ignore(); // Очистка буфера после cin >> choice
            getline(cin, t);
            cout << "Введите исполнителя: ";
            getline(cin, a);
            cout << "Длительность (сек): ";
            cin >> d;

            Song s = {t, a, d};
            priorityStack.push(s);
            break;
        }

        case 4: {
            // Показываем состояние
            priorityStack.displayStack();

            cout << "\n--- Обычная очередь ---" << endl;
            if (standardQueue.isempty()) {
                cout << "(Пусто)" << endl;
            } else {
                cout << "Следующий в очереди: " << standardQueue.front() << endl;
                cout << "(...остальные скрыты, т.к. в Queue нет метода displayAll)" << endl;
            }
            break;
        }

        case 5: {
            // ЛОГИКА ВОСПРОИЗВЕДЕНИЯ
            // 1. Приоритет у Стека
            if (!priorityStack.isEmpty()) {
                Song s = priorityStack.pop();
                cout << "\n[INFO] Играем из списка 'Play Next' (Приоритет)" << endl;
                playTrackDisplay(s.title, s.artist, s.duration);
            }
            // 2. Если стек пуст, берем Очередь
            else if (!standardQueue.isempty()) {
                string trackName = standardQueue.dequeue();
                cout << "\n[INFO] Играем из обычной очереди" << endl;
                playTrackDisplay(trackName);
            }
            // 3. Если всё пусто
            else {
                cout << "\n[!] Очередь пуста. Добавьте музыку!" << endl;
            }
            break;
        }

        case 0:
            cout << "Выход..." << endl;
            isRunning = false;
            break;

        default:
            cout << "Неверная команда." << endl;
        }

        cout << "\n"; // Отступ
    }

    return 0;
}