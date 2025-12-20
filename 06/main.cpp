#include <iostream>
#include <string>

struct BookData {
    std::string author;
    int quantity;
    int year; // Added based on requirement 6
};

struct Node {
    std::string title;
    BookData data;
    Node* left = nullptr;
    Node* right = nullptr;
};

class BookstoreBST {
private:
    Node* root = nullptr;

    Node* insert(Node* node, const std::string& title, const std::string& author, int quantity, int year) {
        if (node == nullptr) {
            return new Node{title, {author, quantity, year}, nullptr, nullptr};
        }

        if (title < node->title) {
            node->left = insert(node->left, title, author, quantity, year);
        } else if (title > node->title) {
            node->right = insert(node->right, title, author, quantity, year);
        } else {
            // Book exists, increase quantity
            node->data.quantity += quantity;
        }
        return node;
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* remove(Node* node, const std::string& title) {
        if (node == nullptr) return nullptr;

        if (title < node->title) {
            node->left = remove(node->left, title);
        } else if (title > node->title) {
            node->right = remove(node->right, title);
        } else {
            // Found the node
            if (node->data.quantity > 1) {
                node->data.quantity--;
            } else {
                // Remove the node completely
                if (node->left == nullptr) {
                    Node* temp = node->right;
                    delete node;
                    return temp;
                } else if (node->right == nullptr) {
                    Node* temp = node->left;
                    delete node;
                    return temp;
                }
                
                // Node with two children
                Node* temp = findMin(node->right);
                node->title = temp->title;
                node->data = temp->data;
                node->right = remove(node->right, temp->title); // Remove the inorder successor
            }
        }
        return node;
    }

    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            std::cout << "Tytul: " << node->title 
                      << ", Autor: " << node->data.author 
                      << ", Ilosc: " << node->data.quantity 
                      << ", Rok: " << node->data.year << std::endl;
            inorder(node->right);
        }
    }

    void searchRange(Node* node, int startYear, int endYear) {
        if (node == nullptr) return;

        searchRange(node->left, startYear, endYear);
        if (node->data.year >= startYear && node->data.year <= endYear) {
            std::cout << "Tytul: " << node->title 
                      << ", Autor: " << node->data.author 
                      << ", Rok: " << node->data.year << std::endl;
        }
        searchRange(node->right, startYear, endYear);
    }

    void destroyTree(Node* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    ~BookstoreBST() {
        destroyTree(root);
    }

    // 1. Dodawanie książki
    void addBook(const std::string& title, const std::string& author, int quantity, int year) {
        root = insert(root, title, author, quantity, year);
    }

    // 2. Usuwanie książki
    void removeBook(const std::string& title) {
        root = remove(root, title);
    }

    // 3. Wyszukiwanie książki
    void findBook(const std::string& title) {
        Node* current = root;
        while (current != nullptr) {
            if (title == current->title) {
                std::cout << "Znaleziono - Tytul: " << current->title 
                          << ", Autor: " << current->data.author 
                          << ", Ilosc: " << current->data.quantity 
                          << ", Rok: " << current->data.year << std::endl;
                return;
            } else if (title < current->title) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        std::cout << "Ksiazka o tytule \"" << title << "\" nie zostala znaleziona." << std::endl;
    }

    // 4. Wyświetlanie katalogu (alfabetycznie)
    void displayCatalog() {
        std::cout << "--- Katalog Ksiegarni ---" << std::endl;
        inorder(root);
        std::cout << "-------------------------" << std::endl;
    }

    // 5. Najwcześniejszy i najpóźniejszy tytuł
    void findFirstTitle() {
        if (root == nullptr) {
            std::cout << "Katalog jest pusty." << std::endl;
            return;
        }
        Node* current = root;
        while (current->left != nullptr) {
            current = current->left;
        }
        std::cout << "Najwczesniejszy tytul (alfabetycznie): " << current->title << std::endl;
    }

    void findLastTitle() {
        if (root == nullptr) {
            std::cout << "Katalog jest pusty." << std::endl;
            return;
        }
        Node* current = root;
        while (current->right != nullptr) {
            current = current->right;
        }
        std::cout << "Najpozniejszy tytul (alfabetycznie): " << current->title << std::endl;
    }

    // 6. Wyświetlanie książek z zakresu lat
    void displayBooksInYearRange(int startYear, int endYear) {
        std::cout << "--- Ksiazki z lat " << startYear << "-" << endYear << " ---" << std::endl;
        searchRange(root, startYear, endYear);
        std::cout << "------------------------------------" << std::endl;
    }
};

int main() {
    BookstoreBST bookstore;

    // Testowanie funkcjonalności
    bookstore.addBook("Wiedzmin: Ostatnie Zyczenie", "Andrzej Sapkowski", 5, 1993);
    bookstore.addBook("Harry Potter i Kamien Filozoficzny", "J.K. Rowling", 10, 1997);
    bookstore.addBook("Pan Tadeusz", "Adam Mickiewicz", 2, 1834);
    bookstore.addBook("Lalka", "Boleslaw Prus", 3, 1890);
    bookstore.addBook("Wiedzmin: Ostatnie Zyczenie", "Andrzej Sapkowski", 2, 1993); // Zwiększenie ilości

    bookstore.displayCatalog();

    std::cout << "\nWyszukiwanie 'Lalka':" << std::endl;
    bookstore.findBook("Lalka");

    std::cout << "\nUsuwanie jednego egzemplarza 'Wiedzmin: Ostatnie Zyczenie':" << std::endl;
    bookstore.removeBook("Wiedzmin: Ostatnie Zyczenie");
    bookstore.findBook("Wiedzmin: Ostatnie Zyczenie");

    std::cout << "\nUsuwanie calkowite 'Pan Tadeusz' (2 egzemplarze, usuwamy 2 razy):" << std::endl;
    bookstore.removeBook("Pan Tadeusz");
    bookstore.removeBook("Pan Tadeusz");
    bookstore.displayCatalog();

    std::cout << "\nSkrajne tytuly:" << std::endl;
    bookstore.findFirstTitle();
    bookstore.findLastTitle();

    std::cout << "\nKsiazki z lat 1990-2000:" << std::endl;
    bookstore.displayBooksInYearRange(1990, 2000);

    return 0;
}