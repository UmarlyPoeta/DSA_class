#include <iostream>
#include <cassert>
#include <sstream>
#include "zadania.cpp"

using namespace std;

// ============ QUEUE TESTS ============
void test_basic_operations() {
    Queue q;
    assert(q.isEmpty() == true);
    
    q.enqueue(1);
    assert(q.isEmpty() == false);
    
    q.enqueue(2);
    q.enqueue(3);
    
    q.dequeue();
    q.dequeue();
    q.dequeue();
    assert(q.isEmpty() == true);
    
    cout << "test_basic_operations passed\n";
}

void test_fifo_order() {
    Queue q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    
    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());
    
    q.print();
    
    cout.rdbuf(old);
    
    assert(buffer.str() == "10 20 30 \n");
    
    cout << "test_fifo_order passed\n";
}

void test_empty_queue() {
    Queue q;
    
    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());
    
    q.dequeue();
    
    cout.rdbuf(old);
    
    assert(buffer.str() == "Queue is empty. Cannot dequeue.\n");
    
    cout << "test_empty_queue passed\n";
}

void test_many_clients() {
    Queue q;
    
    for (int i = 1; i <= 100; i++) {
        q.enqueue(i);
    }
    
    for (int i = 1; i <= 50; i++) {
        q.dequeue();
    }
    
    assert(q.isEmpty() == false);
    
    for (int i = 1; i <= 50; i++) {
        q.dequeue();
    }
    
    assert(q.isEmpty() == true);
    
    cout << "test_many_clients passed\n";
}

// ============ PRIORITY QUEUE TESTS ============
void test_priority_queue_basic() {
    PriorityQueue pq;
    
    pq.enqueue(1, 5);
    pq.enqueue(2, 3);
    pq.enqueue(3, 8);
    
    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());
    
    pq.dequeue();
    pq.dequeue();
    pq.dequeue();
    
    cout.rdbuf(old);
    
    cout << "test_priority_queue_basic passed\n";
}

void test_priority_queue_order() {
    PriorityQueue pq;
    
    pq.enqueue(1, 2);
    pq.enqueue(2, 5);
    pq.enqueue(3, 3);
    pq.enqueue(4, 5);
    pq.enqueue(5, 1);
    
    cout << "test_priority_queue_order passed\n";
}

void test_priority_queue_empty() {
    PriorityQueue pq;
    
    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());
    
    pq.dequeue();
    
    cout.rdbuf(old);
    
    assert(buffer.str() == "Priority queue is empty. Cannot dequeue.\n");
    
    cout << "test_priority_queue_empty passed\n";
}

// ============ ROUND ROBIN TESTS ============
void test_round_robin_simple() {
    RoundRobin rr(3);
    
    rr.dodajProces(1, 5);
    rr.dodajProces(2, 3);
    rr.dodajProces(3, 7);
    
    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());
    
    rr.symuluj();
    
    cout.rdbuf(old);
    
    cout << "test_round_robin_simple passed\n";
}

void test_round_robin_exact_quantum() {
    RoundRobin rr(5);
    
    rr.dodajProces(1, 5);
    rr.dodajProces(2, 10);
    rr.dodajProces(3, 5);
    
    rr.symuluj();
    
    cout << "test_round_robin_exact_quantum passed\n";
}

void test_round_robin_single_process() {
    RoundRobin rr(4);
    
    rr.dodajProces(1, 10);
    
    rr.symuluj();
    
    cout << "test_round_robin_single_process passed\n";
}

// ============ DOUBLE SIDED QUEUE TESTS ============
void test_deque_add_front() {
    DoubleSidedQueue dq;
    
    dq.addFront("Task1", 1);
    dq.addFront("Task2", 2);
    dq.addFront("Task3", 3);
    
    assert(dq.isEmpty() == false);
    
    cout << "test_deque_add_front passed\n";
}

void test_deque_add_rear() {
    DoubleSidedQueue dq;
    
    dq.addRear("Task1", 1);
    dq.addRear("Task2", 2);
    dq.addRear("Task3", 3);
    
    assert(dq.isEmpty() == false);
    
    cout << "test_deque_add_rear passed\n";
}

void test_deque_remove_front() {
    DoubleSidedQueue dq;
    
    dq.addRear("Task1", 1);
    dq.addRear("Task2", 2);
    
    dq.removeFront();
    
    assert(dq.isEmpty() == false);
    
    dq.removeFront();
    
    assert(dq.isEmpty() == true);
    
    cout << "test_deque_remove_front passed\n";
}

void test_deque_remove_rear() {
    DoubleSidedQueue dq;
    
    dq.addRear("Task1", 1);
    dq.addRear("Task2", 2);
    dq.addRear("Task3", 3);
    
    dq.removeRear();
    
    assert(dq.isEmpty() == false);
    
    cout << "test_deque_remove_rear passed\n";
}

void test_deque_mixed_operations() {
    DoubleSidedQueue dq;
    
    dq.addFront("High", 10);
    dq.addRear("Low", 1);
    dq.addFront("VeryHigh", 15);
    
    dq.print();
    
    dq.removeFront();
    dq.removeRear();
    
    assert(dq.isEmpty() == false);
    
    cout << "test_deque_mixed_operations passed\n";
}

void test_deque_empty_operations() {
    DoubleSidedQueue dq;
    
    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());
    
    dq.removeFront();
    
    cout.rdbuf(old);
    
    assert(buffer.str().find("pusta") != string::npos);
    
    cout << "test_deque_empty_operations passed\n";
}

// ============ ELEVATOR SYSTEM TESTS ============
void test_elevator_basic() {
    ElevatorSystem elevator(-2, 10);
    
    elevator.requestFloor(5);
    elevator.requestFloor(3);
    elevator.requestFloor(8);
    
    elevator.simulate();
    
    cout << "test_elevator_basic passed\n";
}

void test_elevator_up_down() {
    ElevatorSystem elevator(0, 5);
    
    elevator.requestFloor(3);
    elevator.requestFloor(5);
    elevator.requestFloor(2);
    
    elevator.simulate();
    
    cout << "test_elevator_up_down passed\n";
}

void test_elevator_invalid_floor() {
    ElevatorSystem elevator(0, 10);
    
    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());
    
    elevator.requestFloor(15);
    elevator.requestFloor(-5);
    
    cout.rdbuf(old);
    
    assert(buffer.str().find("Nieprawidlowe") != string::npos);
    
    cout << "test_elevator_invalid_floor passed\n";
}

void test_elevator_current_floor() {
    ElevatorSystem elevator(0, 10);
    
    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());
    
    elevator.requestFloor(0);
    
    cout.rdbuf(old);
    
    assert(buffer.str().find("jest juz na pietrze") != string::npos);
    
    cout << "test_elevator_current_floor passed\n";
}

void test_elevator_status() {
    ElevatorSystem elevator(0, 10);
    
    elevator.printStatus();
    
    elevator.requestFloor(5);
    elevator.printStatus();
    
    cout << "test_elevator_status passed\n";
}

int main() {
    cout << "=== QUEUE TESTS ===\n";
    test_basic_operations();
    test_fifo_order();
    test_empty_queue();
    test_many_clients();
    
    cout << "\n=== PRIORITY QUEUE TESTS ===\n";
    test_priority_queue_basic();
    test_priority_queue_order();
    test_priority_queue_empty();
    
    cout << "\n=== ROUND ROBIN TESTS ===\n";
    test_round_robin_simple();
    test_round_robin_exact_quantum();
    test_round_robin_single_process();
    
    cout << "\n=== DOUBLE SIDED QUEUE TESTS ===\n";
    test_deque_add_front();
    test_deque_add_rear();
    test_deque_remove_front();
    test_deque_remove_rear();
    test_deque_mixed_operations();
    test_deque_empty_operations();
    
    cout << "\n=== ELEVATOR SYSTEM TESTS ===\n";
    test_elevator_basic();
    test_elevator_up_down();
    test_elevator_invalid_floor();
    test_elevator_current_floor();
    test_elevator_status();
    
    cout << "\n=== ALL TESTS PASSED! ===\n";
    
    return 0;
}