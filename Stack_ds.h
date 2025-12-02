#ifndef STACK_DS_H
#define STACK_DS_H

#include <iostream>
#include <string>

using namespace std;

struct Song {
    string title;
    string artist;
    int duration;
};

struct StackNode {
    Song data;
    StackNode* next;
};

class PlayNextStack {
private:
    StackNode* topNode;

public:
    PlayNextStack() {
        topNode = nullptr;
    }

    ~PlayNextStack() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() {
        return topNode == nullptr;
    }

    void push(Song newSong) {
        StackNode* newNode = new StackNode();
        newNode->data = newSong;
        newNode->next = topNode;
        topNode = newNode;
        
        cout << "[Stack] Added to Play Next: " << newSong.title << endl;
    }

    Song pop() {
        if (isEmpty()) {
            cout << "[Stack] No songs in Play Next list." << endl;
            return {"", "", 0}; // Return empty song if stack is empty
        }

        StackNode* temp = topNode;
        Song poppedSong = topNode->data;
        topNode = topNode->next;
        
        delete temp;
        return poppedSong;
    }

    Song peek() {
        if (isEmpty()) {
            return {"", "", 0};
        }
        return topNode->data;
    }

    void displayStack() {
        if (isEmpty()) {
            cout << "\n--- Play Next List is Empty ---\n";
            return;
        }

        cout << "\n--- Up Next (Priority) ---\n";
        StackNode* current = topNode;
        int count = 1;
        while (current != nullptr) {
            cout << count << ". " << current->data.title 
                 << " - " << current->data.artist << endl;
            current = current->next;
            count++;
        }
        cout << "--------------------------\n";
    }
};

#endif