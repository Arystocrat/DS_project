#include <iostream>
#include <string>
#include <thread> // For sleep
#include <chrono>

// Include your headers
#include "arraym.h"
#include "QUEUE.h"
#include "Stack_ds.h"

using namespace std;

// Helper function to simulate playing a track
void playTrackDisplay(string title, string artist = "", int duration = 2) {
    cout << "\n------------------------------------------------" << endl;
    cout << " >> [NOW PLAYING] " << title;
    if (!artist.empty()) cout << " " << artist; // Artist is now optional/part of title
    cout << endl;
    cout << "------------------------------------------------" << endl;

    // Progress bar simulation
    cout << "Playing: [";
    for(int i=0; i<10; i++) {
        cout << "/";
        this_thread::sleep_for(chrono::milliseconds(duration * 100));
    }
    cout << "] Done.\n" << endl;
}

int main() {
    // 1. Initialize Data Structures
    Arraymethod library;
    Queue standardQueue;
    PlayNextStack priorityStack;

    // 2. Pre-fill the Library
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
        cout << "         CONSOLE MUSIC PLAYER v2.2       " << endl;
        cout << "=========================================" << endl;
        cout << "1. Show Library (All Tracks)" << endl;
        cout << "2. Add to Queue (Standard Playlist)" << endl;
        cout << "3. Play Next (Priority Stack) [From Lib]" << endl; // <--- CHANGED
        cout << "4. View Player Status (Queue & Stack)" << endl;
        cout << "5. >> PLAY NEXT TRACK >>" << endl;
        cout << "6. [+] Add New Track to Library" << endl;
        cout << "0. Exit" << endl;
        cout << "=========================================" << endl;
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = -1;
        }

        switch (choice) {
        case 1: {
            cout << "\n--- MUSIC LIBRARY ---" << endl;
            library.display();
            break;
        }

        case 2: {
            // Add to Standard Queue (Last in, Last out)
            int idx;
            cout << "Enter track index for Queue: ";
            cin >> idx;

            if (idx >= 0) {
                string track = library.getbyindex(idx);
                standardQueue.enqueue(track);
                cout << "[Success] Added to Queue: " << track << endl;
            } else {
                cout << "[Error] Invalid index." << endl;
            }
            break;
        }

        case 3: {
            // Add to Priority Stack (Last in, First out) - FROM LIBRARY
            int idx;
            cout << "Enter track index for 'Play Next' (Priority): ";
            cin >> idx;

            if (idx >= 0) {
                string trackName = library.getbyindex(idx);

                // We need to convert the library string into a Song struct
                // because the Stack works with 'Song' objects.
                Song s;
                s.title = trackName;  // Put the whole string (e.g. "Artist - Name") here
                s.artist = "";        // Leave artist empty (it's already in title)
                s.duration = 3;       // Default duration for quick adding

                priorityStack.push(s);
                cout << "[Success] Jumped the queue! Up Next: " << trackName << endl;
            } else {
                cout << "[Error] Invalid index." << endl;
            }
            break;
        }

        case 4: {
            priorityStack.displayStack();
            cout << "\n--- Standard Queue ---" << endl;
            standardQueue.displayQueue();
            cout << "----------------------" << endl;
            break;
        }

        case 5: {
            // Playback logic
            if (!priorityStack.isEmpty()) {
                Song s = priorityStack.pop();
                cout << "\n[INFO] Playing from 'Play Next' List (Priority)" << endl;
                playTrackDisplay(s.title, s.artist, s.duration);
            }
            else if (!standardQueue.isempty()) {
                string trackName = standardQueue.dequeue();
                cout << "\n[INFO] Playing from Standard Queue" << endl;
                playTrackDisplay(trackName);
            }
            else {
                cout << "\n[!] Silence... The queue is empty." << endl;
            }
            break;
        }

        case 6: {
            string newTrackName;
            cout << "Enter track name: ";
            cin.ignore();
            getline(cin, newTrackName);

            if (!newTrackName.empty()) {
                library.append(newTrackName);
                cout << "[Success] Track added to library!" << endl;
            }
            break;
        }

        case 0:
            cout << "Exiting..." << endl;
            isRunning = false;
            break;

        default:
            cout << "Invalid command." << endl;
        }

        cout << "\n";
    }

    return 0;
}