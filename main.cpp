#include <iostream>
#include <string>
#include <thread> // Для имитации задержки воспроизведения (sleep)
#include <chrono>
#include <windows.h>

// Подключаем ваши хедеры
// ВАЖНО: Предполагается, что конфликт имен Node уже исправлен внутри этих файлов!
#include "arraym.h"
#include "QUEUE.h"
#include "Stack_ds.h"

using namespace std;

// Вспомогательная функция для паузы (чтобы было похоже на плеер)
void fakePlay(string title, string artist = "Unknown", int duration = 2) {
    cout << " >> [NOW PLAYING]: " << title;
    if (artist != "Unknown") cout << " by " << artist;
    cout << " ... (" << duration << " sec)" << endl;

    // Имитация времени проигрывания
    this_thread::sleep_for(chrono::seconds(duration));
    cout << " -- Track finished.\n" << endl;
}

int main() {
    SetConsoleOutputCP(65001);
    // 1. Создаем структуры данных
    Arraymethod library;       // Хранилище всех песен (Массив)
    Queue standardQueue;       // Обычная очередь (Очередь)
    PlayNextStack priorityStack; // Список "Играть далее" (Стек)

    cout << "=== 1. ЗАПОЛНЕНИЕ БИБЛИОТЕКИ (Arraymethod) ===" << endl;

    library.append("Linkin Park - Numb");
    library.append("Daft Punk - Get Lucky");
    library.append("Queen - Bohemian Rhapsody");
    library.append("Metallica - Enter Sandman");
    library.append("Eminem - Lose Yourself");

    library.display(); // Показываем библиотеку

    cout << "=== 2. СОЗДАНИЕ ОЧЕРЕДИ ВОСПРОИЗВЕДЕНИЯ (Queue) ===" << endl;
    // Добавляем пару треков из библиотеки в очередь
    // (Помним, что проверки границ нет, поэтому используем существующие индексы: 0, 1, 3)

    cout << "Adding '" << library.getbyindex(0) << "' to queue..." << endl;
    standardQueue.enqueue(library.getbyindex(0));

    cout << "Adding '" << library.getbyindex(1) << "' to queue..." << endl;
    standardQueue.enqueue(library.getbyindex(1));

    cout << "Adding '" << library.getbyindex(3) << "' to queue..." << endl;
    standardQueue.enqueue(library.getbyindex(3));

    cout << "\nQueue is ready.\n" << endl;

    cout << "=== 3. ИСПОЛЬЗОВАНИЕ 'ИГРАТЬ СЛЕДУЮЩИМ' (Stack) ===" << endl;
    // Представим, что пользователь резко захотел послушать песню СЕЙЧАС же.
    // Стек принимает структуру Song, поэтому создаем её вручную.

    Song urgentSong1 = {"Shape of You", "Ed Sheeran", 3};
    priorityStack.push(urgentSong1);

    Song urgentSong2 = {"Blinding Lights", "The Weeknd", 2};
    priorityStack.push(urgentSong2);

    priorityStack.displayStack(); // Покажет, что Weeknd будет первым (LIFO)

    cout << "\n=== 4. ЗАПУСК ПЛЕЕРА (Имитация работы) ===" << endl;
    cout << "Логика плеера: Сначала Стек -> Если пуст, то Очередь -> Если пуста, то Стоп.\n" << endl;

    while (true) {
        // Шаг 1: Проверяем приоритетный стек (Play Next)
        if (!priorityStack.isEmpty()) {
            cout << "[INFO] Found track in Priority Stack (Play Next)..." << endl;
            Song s = priorityStack.pop();
            fakePlay(s.title, s.artist, s.duration);
        }
        // Шаг 2: Если стек пуст, проверяем обычную очередь
        else if (!standardQueue.isempty()) {
            cout << "[INFO] Playing from Standard Queue..." << endl;
            string trackName = standardQueue.dequeue();
            // Так как очередь хранит только string, передаем его
            fakePlay(trackName);
        }
        // Шаг 3: Если всё пусто - выходим
        else {
            cout << "=== PLAYLIST FINISHED. SILENCE. ===" << endl;
            break;
        }
    }

    return 0;
}