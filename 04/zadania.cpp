#include <iostream>

struct Pacjent {
    int id;
    int priorytet;
    Pacjent* next;
};


struct Klient {
    int id;
    Klient* next;
};

class Queue {
private:
    Klient* front;
    Klient* rear;
public:
    Queue() : front(nullptr), rear(nullptr) {}
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() const {
        return front == nullptr;
    }
        
    void enqueue(int value) {
        Klient* newKlient = new Klient{value, nullptr};
        if (isEmpty()) {
            front = rear = newKlient;
        } else {
            rear->next = newKlient;
            rear = newKlient;
        }
    }

    void dequeue() {
        if (isEmpty()) {
            std::cout << "Queue is empty. Cannot dequeue." << std::endl;
            return;
        }
        Klient* temp = front;
        front = front->next;
        delete temp;
        if (front == nullptr) {
            rear = nullptr;
        }
    }

    void print() const {
        Klient* current = front;
        while (current) {
            std::cout << current->id << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

class PriorityQueue {

private:
    Pacjent* front;
public:
    PriorityQueue() : front(nullptr) {}
    ~PriorityQueue() {
        while (front) {
            Pacjent* temp = front;
            front = front->next;
            delete temp;
        }
    }

    void enqueue(int id, int priorytet) {
        Pacjent* newPacjent = new Pacjent{id, priorytet, nullptr};
        if (!front || front->priorytet < priorytet) {
            newPacjent->next = front;
            front = newPacjent;
        } else {
            Pacjent* current = front;
            while (current->next && current->next->priorytet >= priorytet) {
                current = current->next;
            }
            newPacjent->next = current->next;
            current->next = newPacjent;
        }
    }

    void dequeue() {
        if (!front) {
            std::cout << "Priority queue is empty. Cannot dequeue." << std::endl;
            return;
        }
        Pacjent* temp = front;
        front = front->next;
        delete temp;
    }

};

struct Proces {
    int id;
    int czasWykonania;
    Proces* next;
};

class RoundRobin {
private:
    Proces* front;
    Proces* rear;
    int kwantCzasu;

public:
    RoundRobin(int kwant) : front(nullptr), rear(nullptr), kwantCzasu(kwant) {}
    
    ~RoundRobin() {
        while (front) {
            Proces* temp = front;
            front = front->next;
            delete temp;
        }
    }

    void dodajProces(int id, int czas) {
        Proces* newProces = new Proces{id, czas, nullptr};
        if (!front) {
            front = rear = newProces;
        } else {
            rear->next = newProces;
            rear = newProces;
        }
    }

    void symuluj() {
        std::cout << "Rozpoczynam symulacje Round Robin (kwant czasu: " << kwantCzasu << ")" << std::endl;
        int czas = 0;
        
        while (front) {
            Proces* current = front;
            front = front->next;
            
            std::cout << "Czas " << czas << ": Proces " << current->id 
                      << " (pozostaly czas: " << current->czasWykonania << ")";
            
            if (current->czasWykonania <= kwantCzasu) {
                czas += current->czasWykonania;
                std::cout << " - ZAKONCZONY" << std::endl;
                delete current;
            } else {
                current->czasWykonania -= kwantCzasu;
                czas += kwantCzasu;
                std::cout << " - kontynuuje" << std::endl;
                
                if (!front) {
                    front = rear = current;
                    current->next = nullptr;
                } else {
                    rear->next = current;
                    rear = current;
                    current->next = nullptr;
                }
            }
        }
        
        std::cout << "Symulacja zakonczona. Calkowity czas: " << czas << std::endl;
        rear = nullptr;
    }
};

struct Task {
    std::string nazwa;
    int priorytet;
    Task* next;
};


class DoubleSidedQueue {
private:
    Task* front;
    Task* rear;

public:
    DoubleSidedQueue() : front(nullptr), rear(nullptr) {}
    
    ~DoubleSidedQueue() {
        while (front) {
            Task* temp = front;
            front = front->next;
            delete temp;
        }
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    void addFront(std::string nazwa, int priorytet) {
        Task* newTask = new Task{nazwa, priorytet, nullptr};
        if (isEmpty()) {
            front = rear = newTask;
        } else {
            newTask->next = front;
            front = newTask;
        }
        std::cout << "Zadanie '" << nazwa << "' (priorytet: " << priorytet << ") dodane na poczatek" << std::endl;
    }

    void addRear(std::string nazwa, int priorytet) {
        Task* newTask = new Task{nazwa, priorytet, nullptr};
        if (isEmpty()) {
            front = rear = newTask;
        } else {
            rear->next = newTask;
            rear = newTask;
        }
        std::cout << "Zadanie '" << nazwa << "' (priorytet: " << priorytet << ") dodane na koniec" << std::endl;
    }

    void removeFront() {
        if (isEmpty()) {
            std::cout << "Kolejka jest pusta" << std::endl;
            return;
        }
        Task* temp = front;
        std::cout << "Obsluzono zadanie z poczatku: '" << temp->nazwa << "' (priorytet: " << temp->priorytet << ")" << std::endl;
        front = front->next;
        delete temp;
        if (!front) {
            rear = nullptr;
        }
    }

    void removeRear() {
        if (isEmpty()) {
            std::cout << "Kolejka jest pusta" << std::endl;
            return;
        }
        if (front == rear) {
            std::cout << "Obsluzono zadanie z konca: '" << front->nazwa << "' (priorytet: " << front->priorytet << ")" << std::endl;
            delete front;
            front = rear = nullptr;
            return;
        }
        Task* current = front;
        while (current->next != rear) {
            current = current->next;
        }
        std::cout << "Obsluzono zadanie z konca: '" << rear->nazwa << "' (priorytet: " << rear->priorytet << ")" << std::endl;
        delete rear;
        rear = current;
        rear->next = nullptr;
    }

    void print() const {
        if (isEmpty()) {
            std::cout << "Kolejka jest pusta" << std::endl;
            return;
        }
        std::cout << "Zadania w kolejce: ";
        Task* current = front;
        while (current) {
            std::cout << "[" << current->nazwa << ", P:" << current->priorytet << "] ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

struct ElevatorRequest {
    int floor;
    ElevatorRequest* next;
};

class ElevatorQueue {
private:
    ElevatorRequest* front;
    ElevatorRequest* rear;

public:
    ElevatorQueue() : front(nullptr), rear(nullptr) {}
    
    ~ElevatorQueue() {
        while (front) {
            ElevatorRequest* temp = front;
            front = front->next;
            delete temp;
        }
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    void addRequest(int floor) {
        ElevatorRequest* newRequest = new ElevatorRequest{floor, nullptr};
        if (isEmpty()) {
            front = rear = newRequest;
        } else {
            rear->next = newRequest;
            rear = newRequest;
        }
    }

    int getNextFloor() {
        if (isEmpty()) {
            return -1;
        }
        int floor = front->floor;
        ElevatorRequest* temp = front;
        front = front->next;
        delete temp;
        if (!front) {
            rear = nullptr;
        }
        return floor;
    }

    int peekNextFloor() const {
        if (isEmpty()) {
            return -1;
        }
        return front->floor;
    }
};

class ElevatorSystem {
private:
    ElevatorQueue upQueue;
    ElevatorQueue downQueue;
    int currentFloor;
    enum Direction { UP, DOWN, IDLE };
    Direction currentDirection;
    int minFloor;
    int maxFloor;

public:
    ElevatorSystem(int minF, int maxF) 
        : currentFloor(0), currentDirection(IDLE), minFloor(minF), maxFloor(maxF) {}

    void requestFloor(int targetFloor) {
        if (targetFloor < minFloor || targetFloor > maxFloor) {
            std::cout << "Nieprawidlowe pietro: " << targetFloor << std::endl;
            return;
        }

        if (targetFloor > currentFloor) {
            upQueue.addRequest(targetFloor);
            std::cout << "Dodano zadanie w gore do pietra " << targetFloor << std::endl;
        } else if (targetFloor < currentFloor) {
            downQueue.addRequest(targetFloor);
            std::cout << "Dodano zadanie w dol do pietra " << targetFloor << std::endl;
        } else {
            std::cout << "Winda jest juz na pietrze " << targetFloor << std::endl;
        }
    }

    void simulate() {
        std::cout << "\nRozpoczynanie symulacji windy..." << std::endl;
        std::cout << "Winda startuje z pietra " << currentFloor << std::endl;

        while (!upQueue.isEmpty() || !downQueue.isEmpty()) {
            if (currentDirection == IDLE || currentDirection == UP) {
                if (!upQueue.isEmpty()) {
                    currentDirection = UP;
                    int nextFloor = upQueue.getNextFloor();
                    std::cout << "Winda jedzie w gore: " << currentFloor << " -> " << nextFloor << std::endl;
                    currentFloor = nextFloor;
                    
                    if (currentFloor == maxFloor || upQueue.isEmpty()) {
                        std::cout << "Winda osiagnela najwyzsze pietro lub brak dalszych zadan w gore" << std::endl;
                        currentDirection = DOWN;
                    }
                } else if (!downQueue.isEmpty()) {
                    currentDirection = DOWN;
                }
            }
            
            if (currentDirection == DOWN && !downQueue.isEmpty()) {
                int nextFloor = downQueue.getNextFloor();
                std::cout << "Winda jedzie w dol: " << currentFloor << " -> " << nextFloor << std::endl;
                currentFloor = nextFloor;
                
                if (currentFloor == minFloor || downQueue.isEmpty()) {
                    std::cout << "Winda osiagnela najnizsze pietro lub brak dalszych zadan w dol" << std::endl;
                    currentDirection = UP;
                }
            }
        }

        std::cout << "Symulacja zakonczona. Winda zatrzymala sie na pietrze " << currentFloor << std::endl;
        currentDirection = IDLE;
    }

    void printStatus() const {
        std::cout << "\nStatus windy:" << std::endl;
        std::cout << "Aktualne pietro: " << currentFloor << std::endl;
        std::cout << "Kierunek: ";
        if (currentDirection == UP) std::cout << "W gore" << std::endl;
        else if (currentDirection == DOWN) std::cout << "W dol" << std::endl;
        else std::cout << "Bezczynna" << std::endl;
        std::cout << "Zadania w gore: " << (upQueue.isEmpty() ? "brak" : "obecne") << std::endl;
        std::cout << "Zadania w dol: " << (downQueue.isEmpty() ? "brak" : "obecne") << std::endl;
    }
};
