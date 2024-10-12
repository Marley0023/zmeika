
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;
const int width = 20;
const int height = 10;

struct Node {
    int x;
    int y;
    Node* next;
    Node(int x, int y, Node* next = nullptr) : x(x), y(y), next(next) {}
};

class Snake {
public:
    Node* head;
    Node* tail;

public:
    Snake(int x, int y) {
        head = new Node(x, y);
        tail = head;
    }

    void addHead(int x, int y) {
        Node* ptr = new Node(x, y, head);
        head = ptr;
    }

    void removeTail() {
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        }
        else {
            Node* ptr = head;
            while (ptr->next != tail) {
                ptr = ptr->next;
            }
            delete tail;
            tail = ptr;
            tail->next = nullptr;
        }
    }

    bool checkCollision(int x, int y) {
        Node* tekush = head;
        while (tekush != nullptr) {
            if (tekush->x == x && tekush->y == y) {
                return true;
            }
            tekush = tekush->next;
        }
        return false;
    }

    Node* getHead() {
        return head;
    }
};

Snake snake(width / 2, height / 2);
int fruitX, fruitY;
int score;

void Setup() {
    srand(time(0));
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw() {
    system("cls");
    for (int i = 0; i < width + 2; i++)
        cout << "_";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "|";

            bool print = false;
            Node* tekush = snake.head;
            while (tekush != nullptr) {
                if (tekush->x == j && tekush->y == i) {
                    cout << "O";
                    print = true;
                }
                tekush = tekush->next;
            }

            if (!print)
                cout << (fruitX == j && fruitY == i ? "F" : " ");

            if (j == width - 1)
                cout << "|";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    cout << "Очки: " << score << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            exit(0);
        }
    }
}

int Logic() {
    int newX = snake.getHead()->x;
    int newY = snake.getHead()->y;

    switch (dir) {
    case LEFT:
        newX--;
        break;
    case RIGHT:
        newX++;
        break;
    case UP:
        newY--;
        break;
    case DOWN:
        newY++;
        break;
    default:
        break;
    }

    if (newX >= width || newX < 0 || newY >= height || newY < 0 || snake.checkCollision(newX, newY)) {
        cout << "Игра окончена! Ваш счет: " << score << endl;
        return 0;


    }

    snake.addHead(newX, newY);

    if (newX == fruitX && newY == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
    else {
        snake.removeTail();
    }
}
int main() {
    setlocale(0, "rus");
    Setup();
    while (true) {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }
    return 0;
}

