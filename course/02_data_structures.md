# 02. Data Structures

## Learning Outcomes

After completing this module, you will be able to:

- Implement and use fundamental data structures (stacks, queues, linked lists)
- Understand hash tables and collision resolution techniques
- Work with tree structures (BST, AVL, Red-Black trees)
- Analyze time complexity of operations on different data structures
- Choose the appropriate data structure for specific problems
- Implement self-balancing trees

## Theory

### What are Data Structures?

A **data structure** is a way of organizing and storing data to enable efficient access and modification. The choice of data structure significantly impacts algorithm performance.

### Classification of Data Structures

```
Data Structures
├── Linear
│   ├── Arrays
│   ├── Linked Lists
│   ├── Stacks
│   └── Queues
└── Non-Linear
    ├── Trees
    │   ├── Binary Search Trees (BST)
    │   ├── AVL Trees
    │   └── Red-Black Trees
    ├── Graphs
    └── Hash Tables
```

## 1. Stacks (LIFO - Last In, First Out)

### Definition
A stack is a linear data structure where elements are added and removed from the same end (top).

### Operations
- **Push(x)** - Add element x to top: O(1)
- **Pop()** - Remove and return top element: O(1)
- **Peek/Top()** - Return top element without removing: O(1)
- **IsEmpty()** - Check if stack is empty: O(1)

### Pseudocode

```
Stack Implementation (Array-based):
    
    Initialize:
        items = new array[MAX_SIZE]
        top = -1
    
    Push(x):
        if top == MAX_SIZE - 1:
            error "Stack Overflow"
        top = top + 1
        items[top] = x
    
    Pop():
        if top == -1:
            error "Stack Underflow"
        x = items[top]
        top = top - 1
        return x
    
    Peek():
        if top == -1:
            error "Stack Empty"
        return items[top]
    
    IsEmpty():
        return top == -1
```

### Applications
- Function call management (call stack)
- Expression evaluation and syntax parsing
- Undo mechanism in editors
- Backtracking algorithms

## 2. Queues (FIFO - First In, First Out)

### Definition
A queue is a linear data structure where elements are added at the rear and removed from the front.

### Operations
- **Enqueue(x)** - Add element x to rear: O(1)
- **Dequeue()** - Remove and return front element: O(1)
- **Front()** - Return front element: O(1)
- **IsEmpty()** - Check if queue is empty: O(1)

### Pseudocode

```
Queue Implementation (Circular Array):
    
    Initialize:
        items = new array[MAX_SIZE]
        front = 0
        rear = -1
        size = 0
    
    Enqueue(x):
        if size == MAX_SIZE:
            error "Queue Full"
        rear = (rear + 1) % MAX_SIZE
        items[rear] = x
        size = size + 1
    
    Dequeue():
        if size == 0:
            error "Queue Empty"
        x = items[front]
        front = (front + 1) % MAX_SIZE
        size = size - 1
        return x
    
    Front():
        if size == 0:
            error "Queue Empty"
        return items[front]
```

### Applications
- Job scheduling
- BFS in graphs
- Request handling in servers
- Print queue management

## 3. Linked Lists

### Definition
A linked list is a linear collection of nodes where each node contains data and a reference (pointer) to the next node.

### Types
1. **Singly Linked List** - Each node points to next
2. **Doubly Linked List** - Each node points to both next and previous
3. **Circular Linked List** - Last node points to first

### Operations (Singly Linked List)
- **Insert at beginning**: O(1)
- **Insert at end**: O(n) without tail pointer, O(1) with tail
- **Delete from beginning**: O(1)
- **Search**: O(n)
- **Access by index**: O(n)

### Pseudocode

```
Node Structure:
    data: element value
    next: pointer to next node

LinkedList Operations:

    InsertAtBeginning(head, x):
        newNode = new Node
        newNode.data = x
        newNode.next = head
        head = newNode
        return head
    
    InsertAtEnd(head, x):
        newNode = new Node
        newNode.data = x
        newNode.next = null
        
        if head == null:
            return newNode
        
        current = head
        while current.next != null:
            current = current.next
        current.next = newNode
        return head
    
    Delete(head, x):
        if head == null:
            return null
        
        if head.data == x:
            return head.next
        
        current = head
        while current.next != null and current.next.data != x:
            current = current.next
        
        if current.next != null:
            current.next = current.next.next
        
        return head
    
    Search(head, x):
        current = head
        while current != null:
            if current.data == x:
                return true
            current = current.next
        return false
```

## 4. Hash Tables

### Definition
A hash table is a data structure that maps keys to values using a hash function for efficient lookup.

### Hash Function
A good hash function should:
- Be deterministic (same input → same output)
- Distribute keys uniformly
- Be fast to compute

### Collision Resolution

#### 1. Chaining
Store colliding elements in a linked list at each hash table index.

```
Insert(table, key, value):
    index = hash(key) % table_size
    // Insert (key, value) at table[index] linked list
    
Search(table, key):
    index = hash(key) % table_size
    // Search for key in table[index] linked list
```

**Time Complexity:**
- Average: O(1 + α) where α = n/m (load factor)
- Worst: O(n) if all keys hash to same index

#### 2. Open Addressing
Find another open slot when collision occurs.

**Linear Probing:**
```
h(k, i) = (h'(k) + i) mod m
```

**Quadratic Probing:**
```
h(k, i) = (h'(k) + c₁·i + c₂·i²) mod m
```

**Double Hashing:**
```
h(k, i) = (h₁(k) + i·h₂(k)) mod m
```

## 5. Binary Search Trees (BST)

### Definition
A binary search tree is a binary tree where for each node:
- Left subtree contains only nodes with keys less than node's key
- Right subtree contains only nodes with keys greater than node's key
- Both subtrees are also BSTs

### Operations
- **Search**: O(h) where h is height
- **Insert**: O(h)
- **Delete**: O(h)
- **Traversal**: O(n)

### Pseudocode

```
Node Structure:
    key: node value
    left: pointer to left child
    right: pointer to right child

Search(root, key):
    if root == null or root.key == key:
        return root
    
    if key < root.key:
        return Search(root.left, key)
    else:
        return Search(root.right, key)

Insert(root, key):
    if root == null:
        return new Node(key)
    
    if key < root.key:
        root.left = Insert(root.left, key)
    else if key > root.key:
        root.right = Insert(root.right, key)
    
    return root

Delete(root, key):
    if root == null:
        return root
    
    if key < root.key:
        root.left = Delete(root.left, key)
    else if key > root.key:
        root.right = Delete(root.right, key)
    else:
        // Node with one child or no child
        if root.left == null:
            return root.right
        else if root.right == null:
            return root.left
        
        // Node with two children
        // Get inorder successor (smallest in right subtree)
        root.key = MinValue(root.right)
        root.right = Delete(root.right, root.key)
    
    return root

InorderTraversal(root):
    if root != null:
        InorderTraversal(root.left)
        print(root.key)
        InorderTraversal(root.right)
```

**Problem with BST:** Can become unbalanced (O(n) height in worst case)

## 6. AVL Trees (Self-Balancing BST)

### Definition
An AVL tree is a self-balancing BST where the heights of left and right subtrees of any node differ by at most 1.

### Balance Factor
```
BF(node) = height(left subtree) - height(right subtree)
```
For AVL tree: BF ∈ {-1, 0, 1}

### Rotations

#### Left Rotation
```
    y                x
   / \              / \
  x   C    →       A   y
 / \                  / \
A   B                B   C
```

#### Right Rotation
```
  y                  x
 / \                / \
A   x      →       y   C
   / \            / \
  B   C          A   B
```

### Pseudocode

```
LeftRotate(y):
    x = y.right
    B = x.left
    
    x.left = y
    y.right = B
    
    // Update heights
    y.height = 1 + max(height(y.left), height(y.right))
    x.height = 1 + max(height(x.left), height(x.right))
    
    return x

RightRotate(y):
    x = y.left
    B = x.right
    
    x.right = y
    y.left = B
    
    // Update heights
    y.height = 1 + max(height(y.left), height(y.right))
    x.height = 1 + max(height(x.left), height(x.right))
    
    return x

AVL_Insert(root, key):
    // 1. Standard BST insertion
    if root == null:
        return new Node(key)
    
    if key < root.key:
        root.left = AVL_Insert(root.left, key)
    else if key > root.key:
        root.right = AVL_Insert(root.right, key)
    else:
        return root  // Duplicate keys not allowed
    
    // 2. Update height
    root.height = 1 + max(height(root.left), height(root.right))
    
    // 3. Get balance factor
    balance = height(root.left) - height(root.right)
    
    // 4. Rebalance if needed
    
    // Left Left Case
    if balance > 1 and key < root.left.key:
        return RightRotate(root)
    
    // Right Right Case
    if balance < -1 and key > root.right.key:
        return LeftRotate(root)
    
    // Left Right Case
    if balance > 1 and key > root.left.key:
        root.left = LeftRotate(root.left)
        return RightRotate(root)
    
    // Right Left Case
    if balance < -1 and key < root.right.key:
        root.right = RightRotate(root.right)
        return LeftRotate(root)
    
    return root
```

**Time Complexity:** O(log n) for all operations (guaranteed)

## 7. Red-Black Trees

### Definition
A red-black tree is a self-balancing BST with these properties:

1. Every node is either red or black
2. Root is black
3. All leaves (NIL) are black
4. If a node is red, both children are black (no two consecutive red nodes)
5. All paths from node to descendant leaves contain same number of black nodes

### Properties
- Height ≤ 2·log₂(n + 1)
- Guarantees O(log n) for insert, delete, search

### Operations
More complex rotations and recoloring than AVL, but:
- Fewer rotations on average during insertion/deletion
- Preferred in many standard libraries (e.g., C++ std::map, Java TreeMap)

### Insert Pseudocode (Simplified)

```
RB_Insert(T, z):
    // Standard BST insert
    y = NIL
    x = T.root
    while x != NIL:
        y = x
        if z.key < x.key:
            x = x.left
        else:
            x = x.right
    
    z.parent = y
    if y == NIL:
        T.root = z
    else if z.key < y.key:
        y.left = z
    else:
        y.right = z
    
    z.left = NIL
    z.right = NIL
    z.color = RED
    
    RB_Insert_Fixup(T, z)

RB_Insert_Fixup(T, z):
    while z.parent.color == RED:
        if z.parent == z.parent.parent.left:
            y = z.parent.parent.right  // Uncle
            if y.color == RED:
                // Case 1: Uncle is red
                z.parent.color = BLACK
                y.color = BLACK
                z.parent.parent.color = RED
                z = z.parent.parent
            else:
                if z == z.parent.right:
                    // Case 2: z is right child
                    z = z.parent
                    LeftRotate(T, z)
                // Case 3: z is left child
                z.parent.color = BLACK
                z.parent.parent.color = RED
                RightRotate(T, z.parent.parent)
        else:
            // Symmetric cases
            ...
    
    T.root.color = BLACK
```

## Code Examples

### Stack Implementation (C++)

```cpp
#include <iostream>
#include <stdexcept>

template <typename T>
class Stack {
private:
    T* items;
    int top;
    int capacity;

public:
    Stack(int size = 100) : capacity(size), top(-1) {
        items = new T[capacity];
    }
    
    ~Stack() {
        delete[] items;
    }
    
    void push(T x) {
        if (top == capacity - 1) {
            throw std::overflow_error("Stack Overflow");
        }
        items[++top] = x;
    }
    
    T pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack Underflow");
        }
        return items[top--];
    }
    
    T peek() const {
        if (isEmpty()) {
            throw std::underflow_error("Stack Empty");
        }
        return items[top];
    }
    
    bool isEmpty() const {
        return top == -1;
    }
};

int main() {
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    
    std::cout << "Top: " << s.peek() << std::endl;  // 30
    std::cout << "Pop: " << s.pop() << std::endl;   // 30
    std::cout << "Top: " << s.peek() << std::endl;  // 20
    
    return 0;
}
```

### Binary Search Tree (C++)

```cpp
#include <iostream>

struct Node {
    int key;
    Node* left;
    Node* right;
    
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;
    
    Node* insertHelper(Node* node, int key) {
        if (node == nullptr) {
            return new Node(key);
        }
        
        if (key < node->key) {
            node->left = insertHelper(node->left, key);
        } else if (key > node->key) {
            node->right = insertHelper(node->right, key);
        }
        
        return node;
    }
    
    Node* searchHelper(Node* node, int key) {
        if (node == nullptr || node->key == key) {
            return node;
        }
        
        if (key < node->key) {
            return searchHelper(node->left, key);
        }
        return searchHelper(node->right, key);
    }
    
    void inorderHelper(Node* node) {
        if (node != nullptr) {
            inorderHelper(node->left);
            std::cout << node->key << " ";
            inorderHelper(node->right);
        }
    }

public:
    BST() : root(nullptr) {}
    
    void insert(int key) {
        root = insertHelper(root, key);
    }
    
    bool search(int key) {
        return searchHelper(root, key) != nullptr;
    }
    
    void inorder() {
        inorderHelper(root);
        std::cout << std::endl;
    }
};

int main() {
    BST tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    
    std::cout << "Inorder traversal: ";
    tree.inorder();  // 20 30 40 50 60 70 80
    
    std::cout << "Search 40: " << (tree.search(40) ? "Found" : "Not found") << std::endl;
    std::cout << "Search 25: " << (tree.search(25) ? "Found" : "Not found") << std::endl;
    
    return 0;
}
```

## Exercises

### Easy

1. **Stack Applications**: Implement a function to check if parentheses in an expression are balanced using a stack.

2. **Queue Reversal**: Write a function to reverse a queue using only queue operations and a stack.

3. **Linked List**: Implement a function to find the middle element of a singly linked list in one pass.

### Medium

4. **LRU Cache**: Implement an LRU (Least Recently Used) cache using a hash table and doubly linked list. Support get() and put() in O(1) time.

5. **BST Validation**: Write a function to check if a binary tree is a valid BST.

6. **Level Order Traversal**: Implement level-order (breadth-first) traversal of a binary tree using a queue.

7. **Hash Table**: Implement a hash table with chaining collision resolution. Include insert, search, and delete operations.

### Hard

8. **AVL Tree**: Implement a complete AVL tree with insertion and all four rotation cases.

9. **Lowest Common Ancestor**: Find the lowest common ancestor of two nodes in a BST. Can you do it in O(h) time?

10. **Serialize/Deserialize BST**: Design an algorithm to serialize and deserialize a binary search tree.

### Challenge

11. **Red-Black Tree**: Implement insertion in a red-black tree with proper fixup.

12. **Two Stacks in One Array**: Implement two stacks in a single array such that operations on both stacks are O(1).

## Complexity Comparison

| Data Structure | Access | Search | Insert | Delete | Space |
|----------------|--------|--------|--------|--------|-------|
| Array | O(1) | O(n) | O(n) | O(n) | O(n) |
| Stack | O(n) | O(n) | O(1) | O(1) | O(n) |
| Queue | O(n) | O(n) | O(1) | O(1) | O(n) |
| Linked List | O(n) | O(n) | O(1)* | O(1)* | O(n) |
| Hash Table | - | O(1)† | O(1)† | O(1)† | O(n) |
| BST | O(h) | O(h) | O(h) | O(h) | O(n) |
| AVL Tree | O(log n) | O(log n) | O(log n) | O(log n) | O(n) |
| Red-Black Tree | O(log n) | O(log n) | O(log n) | O(log n) | O(n) |

*At known position, †Average case

## References

### Books
- **Introduction to Algorithms (CLRS)** - Chapters 10-13
  - Chapter 10: Elementary Data Structures
  - Chapter 11: Hash Tables
  - Chapter 12: Binary Search Trees
  - Chapter 13: Red-Black Trees

- **Data Structures and Algorithm Analysis in C++** by Mark Allen Weiss

### Online Resources
- [VisuAlgo - Data Structures](https://visualgo.net/) - Visualizations for all major data structures
- [GeeksforGeeks - Data Structures](https://www.geeksforgeeks.org/data-structures/)
- [CS50 - Data Structures](https://cs50.harvard.edu/x/)
- [Red-Black Tree Visualization](https://www.cs.usfca.edu/~galles/visualization/RedBlack.html)

### Video Lectures
- MIT 6.006 - Introduction to Algorithms (lectures on data structures)
- UC Berkeley CS61B - Data Structures

## Summary

In this module, we covered:
- ✅ Linear data structures: stacks, queues, linked lists
- ✅ Hash tables and collision resolution
- ✅ Binary search trees and operations
- ✅ Self-balancing trees: AVL and Red-Black trees
- ✅ Complexity analysis and trade-offs

**Next Steps:** Proceed to [Module 3: Dynamic Programming & Greedy Algorithms](03_dynamic_greedy.md) to learn advanced problem-solving techniques.

---

*💡 Tip: The right data structure can make the difference between an O(n²) and O(log n) solution. Always consider your use case!*
