#include <iostream>
using namespace std;

class Player {
public:
    int playerID;
    int score;
    Player* next;

    Player(int id, int sc) {
        playerID = id;
        score = sc;
        next = NULL;
    }
};

class Game {
private:
    Player* current;

public:
    Game() {
        current = NULL;
    }

    void addPlayer(int id, int score) {
        Player* newPlayer = new Player(id, score);

        if (current == NULL) {
            current = newPlayer;
            newPlayer->next = newPlayer;
        }
        else {
            Player* temp = current;
            while (temp->next != current) {
                temp = temp->next;
            }

            temp->next = newPlayer;
            newPlayer->next = current;
        }

        cout << "Player added: " << id << endl;
    }

    void removePlayer(int id) {
        if (current == NULL) {
            cout << "No players in the game!\n";
            return;
        }

        Player* temp = current;
        Player* prev = NULL;

        if (current->next == current && current->playerID == id) {
            delete current;
            current = NULL;
            cout << "Player removed. No players left!\n";
            return;
        }

        do {
            if (temp->playerID == id) {

                if (temp == current) {
                    Player* last = current;
                    while (last->next != current)
                        last = last->next;

                    current = current->next;
                    last->next = current;
                }
                else {
                    prev->next = temp->next;
                }

                delete temp;
                cout << "Player removed: " << id << endl;
                return;
            }

            prev = temp;
            temp = temp->next;

        } while (temp != current);

        cout << "Player not found!\n";
    }

    void nextTurn() {
        if (current == NULL) {
            cout << "No players available!\n";
            return;
        }

        current = current->next;
        cout << "Current turn: Player " << current->playerID << endl;
    }

    void skipPlayer() {
        if (current == NULL) {
            cout << "No players available!\n";
            return;
        }

        cout << "Skipping Player " << current->next->playerID << endl;
        current = current->next->next;
        cout << "Now it's Player " << current->playerID << "'s turn\n";
    }

    void checkWinner() {
        if (current == NULL) {
            cout << "No players in game.\n";
            return;
        }

        if (current->next == current) {
            cout << "Game Over! Winner is Player " << current->playerID << endl;
        }
        else {
            cout << "Game still in progress...\n";
        }
    }

    void display() {
        if (current == NULL) {
            cout << "No players in game!\n";
            return;
        }

        Player* temp = current;

        cout << "\nPlayers in game:\n";
        do {
            cout << "PlayerID: " << temp->playerID
                << ", Score: " << temp->score << endl;
            temp = temp->next;
        } while (temp != current);
    }
};

int main() {
    Game g;

    g.addPlayer(1, 10);
    g.addPlayer(2, 20);
    g.addPlayer(3, 15);

    g.display();

    g.nextTurn();
    g.skipPlayer();

    g.removePlayer(2);
    g.display();

    g.checkWinner();

    g.removePlayer(1);
    g.removePlayer(3);

    g.checkWinner();

    return 0;
}