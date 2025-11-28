#include <iostream>

typedef struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr), parent(nullptr) {}
} TreeNode;


class BSTree {
public:
    BSTree() : root(nullptr) {}

    static TreeNode* insert(TreeNode* node, int val) {
        if (node == nullptr) {
            return new TreeNode(val);
        }
        if (val < node->val) {
            TreeNode* l = insert(node->left, val);
            node->left = l;
            l->parent = node;
        }
        else {
            TreeNode* r = insert(node->right, val);
            node->right = r;
            r->parent = node;
        }
        return node;
    }

    static void PreOrder(TreeNode* node) {
        if (node == nullptr) {
            return;
        }
        std::cout << node->val << " ";
        PreOrder(node->left);
        PreOrder(node->right);
    }

    static void InOrder(TreeNode* node) {
        if (node == nullptr) {
            return;
        }
        InOrder(node->left);
        std::cout << node->val << " ";
        InOrder(node->right);
    }

    static void PostOrder(TreeNode* node) {
        if (node == nullptr) {
            return;
        }
        PostOrder(node->left);
        PostOrder(node->right);
        std::cout << node->val << " ";
    }

    int min() {
        if (root == nullptr) {
            std::cout << "empty" << std::endl;
            return -1;
        }
        TreeNode* curr = root;
        while(curr->left != nullptr) {
            curr = curr->left;
        }
        return curr->val;
    }

    int max() {
        if (root == nullptr) {
            std::cout << "empty" << std::endl;
            return -1;
        }
        TreeNode* curr = root;
        while(curr->right != nullptr) {
            curr = curr->right;
        }
        return curr->val;
    }

    int height(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return std::max(leftHeight, rightHeight) + 1;
    }

    TreeNode* nastepnik(TreeNode* node) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->right != nullptr) {
            TreeNode* curr = node->right;
            while (curr->left != nullptr) {
                curr = curr->left;
            }
            return curr;
        }
        TreeNode* curr = node;
        TreeNode* p = node->parent;
        while (p != nullptr && curr == p->right) {
            curr = p;
            p = p->parent;
        }
        return p;
    }

    TreeNode* poprzednik(TreeNode* node) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->left != nullptr) {
            TreeNode* curr = node->left;
            while (curr->right != nullptr) {
                curr = curr->right;
            }
            return curr;
        }
        TreeNode* curr = node;
        TreeNode* p = node->parent;
        while (p != nullptr && curr == p->left) {
            curr = p;
            p = p->parent;
        }
        return p;
    }

    bool remove(int val) {
        TreeNode* curr = root;
        TreeNode* parent = nullptr;

        while (curr != nullptr && curr->val != val) {
            parent = curr;
            if (val < curr->val) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }

        if (curr == nullptr) {
            return false; 
        }

        if (curr->left == nullptr && curr->right == nullptr) {
            if (curr == root) {
                root = nullptr;
            } else if (parent->left == curr) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
            delete curr;
        } else if (curr->left != nullptr && curr->right != nullptr) {
            TreeNode* succ = nastepnik(curr);
            int succVal = succ->val;
            remove(succVal);
            curr->val = succVal;
        } else {
            TreeNode* child = (curr->left != nullptr) ? curr->left : curr->right;
            if (curr == root) {
                root = child;
            } else if (parent->left == curr) {
                parent->left = child;
            } else {
                parent->right = child;
            }
            child->parent = parent;
            delete curr;
        }
        return true;
    }

private:
    TreeNode* root;
};

#include <string>

struct BookData {
    std::string title;
    std::string author;
    int year;
    int count;

    BookData(std::string t, std::string a, int y, int c) 
        : title(t), author(a), year(y), count(c) {}
};

struct BookNode {
    BookData data;
    BookNode* left;
    BookNode* right;
    BookNode* parent;

    BookNode(BookData d) : data(d), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BookBSTree {
public:
    BookBSTree() : root(nullptr) {}

    void addBook(std::string title, std::string author, int year, int count) {
        root = insert(root, nullptr, title, author, year, count);
    }
    
    void removeBook(std::string title) {
        root = deleteNode(root, title);
    }

    void searchBook(std::string title) {
        BookNode* node = find(root, title);
        if (node != nullptr) {
            std::cout << "f: " << node->data.title 
                      << ", a: " << node->data.author 
                      << ", y: " << node->data.year 
                      << ", c: " << node->data.count << std::endl;
        } else {
            std::cout << "not found: " << title << std::endl;
        }
    }

    void displayCatalog() {
        if (root == nullptr) {
            std::cout << "empty" << std::endl;
            return;
        }
        inOrderDisplay(root);
    }

    void findFirstTitle() {
        if (root == nullptr) {
            std::cout << "empty" << std::endl;
            return;
        }
        BookNode* curr = root;
        while (curr->left != nullptr) {
            curr = curr->left;
        }
        std::cout << "First t: " << curr->data.title << std::endl;
    }

    void findLastTitle() {
        if (root == nullptr) {
            std::cout << "empty" << std::endl;
            return;
        }
        BookNode* curr = root;
        while (curr->right != nullptr) {
            curr = curr->right;
        }
        std::cout << "Last t" << curr->data.title << std::endl;
    }

    void displayBooksInYearRange(int startYear, int endYear) {
        displayRange(root, startYear, endYear);
    }

private:
    BookNode* root;

    BookNode* insert(BookNode* node, BookNode* parent, std::string title, std::string author, int year, int count) {
        if (node == nullptr) {
            BookNode* newNode = new BookNode(BookData(title, author, year, count));
            newNode->parent = parent;
            return newNode;
        }

        if (title == node->data.title) {
            node->data.count += count;
            return node;
        }

        if (title < node->data.title) {
            node->left = insert(node->left, node, title, author, year, count);
        } else {
            node->right = insert(node->right, node, title, author, year, count);
        }
        return node;
    }

    BookNode* find(BookNode* node, std::string title) {
        if (node == nullptr || node->data.title == title) {
            return node;
        }
        if (title < node->data.title) {
            return find(node->left, title);
        }
        return find(node->right, title);
    }

    BookNode* minNode(BookNode* node) {
        BookNode* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    BookNode* deleteNode(BookNode* root, std::string title) {
        if (root == nullptr) return root;

        if (title < root->data.title) {
            root->left = deleteNode(root->left, title);
        } else if (title > root->data.title) {
            root->right = deleteNode(root->right, title);
        } else {
            
            if (root->data.count > 1) {
                root->data.count--;
                std::cout << "Decreased: " << title << std::endl;
                return root;
            }

            if (root->left == nullptr) {
                BookNode* temp = root->right;
                if (temp) temp->parent = root->parent;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                BookNode* temp = root->left;
                if (temp) temp->parent = root->parent;
                delete root;
                return temp;
            }

            BookNode* temp = minNode(root->right);
            root->data = temp->data;
            int originalCount = temp->data.count;
            temp->data.count = 1; 
            root->right = deleteNode(root->right, temp->data.title);
            root->data.count = originalCount;
        }
        return root;
    }

    void remove(BookNode*& node, std::string title) {
        node = deleteNode(node, title);
    }

    void inOrderDisplay(BookNode* node) {
        if (node == nullptr) return;
        inOrderDisplay(node->left);
        std::cout << "T: " << node->data.title 
                  << ", a: " << node->data.author 
                  << ", y: " << node->data.year 
                  << ", c: " << node->data.count << std::endl;
        inOrderDisplay(node->right);
    }

    void displayRange(BookNode* node, int start, int end) {
        if (node == nullptr) return;
        displayRange(node->left, start, end);
        if (node->data.year >= start && node->data.year <= end) {
            std::cout << "T: " << node->data.title 
                      << " (" << node->data.year << ")" << std::endl;
        }
        displayRange(node->right, start, end);
    }
};



// tutaj czat pisał
int main() {
    // --- 1. Testowanie BSTree (Drzewo liczb - metody statyczne) ---
    std::cout << "=== TEST BSTree (Integer Tree) ===" << std::endl;
    
    // Tworzymy drzewo ręcznie, ponieważ klasa BSTree ma prywatny root bez settera
    TreeNode* rootInt = nullptr;
    rootInt = BSTree::insert(rootInt, 50);
    rootInt = BSTree::insert(rootInt, 30);
    rootInt = BSTree::insert(rootInt, 20);
    rootInt = BSTree::insert(rootInt, 40);
    rootInt = BSTree::insert(rootInt, 70);
    rootInt = BSTree::insert(rootInt, 60);
    rootInt = BSTree::insert(rootInt, 80);

    std::cout << "PreOrder: ";
    BSTree::PreOrder(rootInt);
    std::cout << "\nInOrder:  ";
    BSTree::InOrder(rootInt);
    std::cout << "\nPostOrder: ";
    BSTree::PostOrder(rootInt);
    
    // Używamy instancji tylko do wywołania metody height (która nie jest statyczna)
    BSTree tempTree;
    std::cout << "\nHeight: " << tempTree.height(rootInt) << std::endl;


    // --- 2. Testowanie BookBSTree (Katalog książek) ---
    std::cout << "\n\n=== TEST BookBSTree (Book Catalog) ===" << std::endl;
    BookBSTree library;

    // Dodawanie książek
    library.addBook("The Witcher", "Sapkowski", 1993, 5);
    library.addBook("Harry Potter", "Rowling", 1997, 1);
    library.addBook("The Hobbit", "Tolkien", 1937, 2);
    library.addBook("Clean Code", "Martin", 2008, 1);
    
    // Test inkrementacji licznika (dodajemy istniejącą książkę)
    library.addBook("The Hobbit", "Tolkien", 1937, 3); 

    std::cout << "--- Catalog after adding books ---" << std::endl;
    library.displayCatalog();

    std::cout << "\n--- Searching for 'The Hobbit' ---" << std::endl;
    library.searchBook("The Hobbit");

    std::cout << "\n--- Searching for missing book ---" << std::endl;
    library.searchBook("Cyberpunk 2077");

    std::cout << "\n--- Min and Max Titles ---" << std::endl;
    library.findFirstTitle(); // Powinno być "Clean Code"
    library.findLastTitle();  // Powinno być "The Witcher"

    std::cout << "\n--- Books in range 1990-2000 ---" << std::endl;
    library.displayBooksInYearRange(1990, 2000);

    std::cout << "\n--- Removing 'The Hobbit' (count > 1, should decrease) ---" << std::endl;
    library.removeBook("The Hobbit");
    library.displayCatalog();

    std::cout << "\n--- Removing 'Harry Potter' (count = 1, should delete node) ---" << std::endl;
    library.removeBook("Harry Potter");
    library.displayCatalog();

    return 0;
}