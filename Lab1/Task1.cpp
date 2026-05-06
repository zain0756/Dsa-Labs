#include <iostream>
using namespace std;
class Song {
public:
    int songID;
    string songName;
    float duration;
    Song* next;
    Song* prev;

    Song(int id, string name, float dur) {
        songID = id;
        songName = name;
        duration = dur;
        next = prev = NULL;
    }
};
class Playlist { 
private:
    Song* head;
    Song* tail;
    Song* current; 
public:
    Playlist() {
        head = tail = current = NULL;
    }
    void addSong(int id, string name, float dur) {
        Song* newSong = new Song(id, name, dur);
        if (head == NULL) {
            head = tail = current = newSong;
        }
        else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }
        cout << "Song added: " << name << endl;
    }  
    void deleteSong(string name) {
        Song* temp = head;
        while (temp != NULL) {
            if (temp->songName == name) {           
                if (temp == head) {
                    head = head->next;
                    if (head != NULL)
                        head->prev = NULL;
                }             
                else if (temp == tail) {
                    tail = tail->prev;
                    tail->next = NULL;
                }            
                else {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                }              
                if (current == temp)
                    current = temp->next ? temp->next : temp->prev;
                delete temp;
                cout << "Song deleted: " << name << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Song not found!\n";
    } 
    void playNext() {
        if (current == NULL) {
            cout << "Playlist is empty!\n";
            return;
        }
        if (current->next != NULL) {
            current = current->next;
            cout << "Now playing: " << current->songName << endl;
        }
        else {
            cout << "Already at the last song!\n";
        }
    }   
    void playPrevious() {
        if (current == NULL) {
            cout << "Playlist is empty!\n";
            return;
        }
        if (current->prev != NULL) {
            current = current->prev;
            cout << "Now playing: " << current->songName << endl;
        }
        else {
            cout << "Already at the first song!\n";
        }
    } 
    void reversePlaylist() {
        Song* temp = NULL;
        Song* curr = head;
        while (curr != NULL) {
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;
            curr = curr->prev;
        }      
        if (temp != NULL) {
            head = temp->prev;
        }
        cout << "Playlist reversed!\n";
    }  
    void display() {
        Song* temp = head;
        if (temp == NULL) {
            cout << "Playlist is empty!\n";
            return;
        }
        cout << "\n--- Playlist ---\n";
        while (temp != NULL) {
            cout << "ID: " << temp->songID
                << ", Name: " << temp->songName
                << ", Duration: " << temp->duration << " mins\n";
            temp = temp->next;
        }
    }
};
int main() {
    Playlist p;

    p.addSong(1, "Song A", 3.5);
    p.addSong(2, "Song B", 4.0);
    p.addSong(3, "Song C", 2.8);

    p.display();

    p.playNext();
    p.playNext();
    p.playPrevious();

    p.deleteSong("Song B");
    p.display();

    p.reversePlaylist();
    p.display();

    return 0;
}