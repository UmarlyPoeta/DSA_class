#include <iostream>


typedef struct Node {
    int data;
    Node* next;

    Node() : data(0), next(nullptr) {};
    Node(int d) : data(d), next(nullptr) {};
    Node(int d, Node* n) : data(d), next(n) {}; 
} Node; 

class List {
public:
    List() {};
    ~List() {
        while (head) {
            Node* tmp = head;
            head = head -> next;
            delete tmp;
        }
    };

    void append(int data) {
        Node* new_node = new Node(data);

        if (!head) {
            head = new_node;
            return;
        }

        Node* tmp = head;
        while (tmp -> next) {
            tmp = tmp->next;
        }

        tmp->next = new_node; 
    }

    void prepend(int data) {
        Node* new_node = new Node(data);

        if (!head) {
            head = new_node;
            return;
        }

        new_node->next = head;
        head = new_node;
    }

    bool remove(int data) {
        if (!head) {return true;}

        if (head->data == data) {head  = head->next;}

        Node* tmp = head->next;
        Node* prev = head;
        Node* next_holder;


        while (tmp->next) {
            if (tmp->data == data) {
                next_holder = tmp->next;
                delete tmp;
                prev -> next = next_holder;
                return true;
            }

            prev = tmp;
            tmp = tmp ->next;
        }

        if (tmp -> data == data) {
            delete tmp;
            prev -> next = nullptr;
            return true;
        }

        return false;
    }

    bool contains(int data) {
        if (!head) {return true;}

        if (head->data == data) {return true;}

        Node* tmp = head->next;
        Node* prev = head;
        Node* next_holder;


        while (tmp->next) {
            if (tmp->data == data) {
                return true;
            }

            prev = tmp;
            tmp = tmp ->next;
        }

        if (tmp -> data == data) {
            return true;
        }

        return false;
    }

    




private:
    Node* head;
};