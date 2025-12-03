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
    if (!artist.empty()) cout << " - " << artist;
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
    Arraymethod library;         // Storage for all songs
    Queue standardQueue;         // Standard playlist
    PlayNextStack priorityStack; // "Play Next" feature

    // 2. Pre-fill the Library with some classics
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
        cout << "         CONSOLE MUSIC PLAYER v2.1       " << endl;
        cout << "=========================================" << endl;
        cout << "1. Show Library (All Tracks)" << endl;
        cout << "2. Add to Queue (by Index)" << endl;
        cout << "3. Play Next (Priority Stack)" << endl;
        cout << "4. View Player Status (Queue & Stack)" << endl;
        cout << "5. >> PLAY NEXT TRACK >>" << endl;
        cout << "6. [+] Add New Track to Library" << endl; // <--- NEW OPTION
        cout << "0. Exit" << endl;
        cout << "=========================================" << endl;
        cout << "Enter choice: ";

        // Input validation
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
            int idx;
            cout << "Enter track index from Library: ";
            cin >> idx;

            // Note: Since Arraymethod doesn't have a getSize() check,
            // we rely on the user entering a valid index.
            if (idx >= 0) {
                // Warning: If idx is out of bounds, program might crash
                // because Arraymethod implementation lacks bounds checking.
                string track = library.getbyindex(idx);
                standardQueue.enqueue(track);
                cout << "[Success] Added to Queue: " << track << endl;
            } else {
                cout << "[Error] Invalid index." << endl;
            }
            break;
        }

        case 3: {
            // Stack requires a Song struct
            string t, a;
            int d;
            cout << "Enter Song Title: ";
            cin.ignore(); // Clear buffer
            getline(cin, t);
            cout << "Enter Artist: ";
            getline(cin, a);
            cout << "Duration (sec): ";
            cin >> d;

            Song s = {t, a, d};
            priorityStack.push(s);
            break;
        }

        case 4: {
            // Display Stack (Priority)
            priorityStack.displayStack();

            // Display Queue (Standard)
            cout << "\n--- Standard Queue ---" << endl;
            standardQueue.displayQueue();
            cout << "----------------------" << endl;
            break;
        }

        case 5: {
            // PLAYBACK LOGIC (Interactive Mode)

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
                cout << "\n[!] Silence... The queue is empty. Add more songs!" << endl;
            }
            break;
        }

        case 6: { // <--- NEW CASE: ADD TO LIBRARY
            string newTrackName;
            cout << "Enter the full track name (e.g. 'Artist - Song'): ";
            cin.ignore(); // Clear buffer from the previous cin >> choice
            getline(cin, newTrackName);

            if (!newTrackName.empty()) {
                library.append(newTrackName);
                cout << "[Success] Track added to library!" << endl;
            } else {
                cout << "[Error] Track name cannot be empty." << endl;
            }
            break;
        }

        case 0:
            cout << "Exiting Player..." << endl;
            isRunning = false;
            break;

        default:
            cout << "Invalid command. Please try again." << endl;
        }

        cout << "\n";
    }

    return 0;
}