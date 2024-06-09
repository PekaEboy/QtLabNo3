#ifndef LIST_H
#define LIST_H

#include <QWidget>
#include <QMainWindow>
struct Student {
    QString name;
    int score[3];
};

struct Node {
    Student val;
    Node* next;
    int number;
    Node(Student _val) : val(_val), next(nullptr), number(0) {};
};

class List
{
public:
    Node* first;
    Node* last;
    List();
    bool is_empty();
    Node* find(int num);
    void push_back(Student dude);
    void remove(int num);
};

#endif // LIST_H
