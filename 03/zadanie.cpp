#include <iostream>
#include <string>

// STACK USING TABLE
const int MAX = 1000;

template<typename T>
class MyStack {
    int t; 
public:
    MyStack() : t(-1) {}
    T a[MAX];
    bool push(const T& val);
    T pop();
    T top() const;
    bool isEmpty() const { return (t < 0); }
    bool isFull() const { return (t >= MAX - 1); }
    void odwracanieElementow();
};

template<typename T>
bool MyStack<T>::push(const T& val) {
    if (isFull()) {
        std::cout << "Stack overflow!\n";
        return false;
    } else {
        a[++t] = val;
        return true;
    }
}

template<typename T>
void MyStack<T>::odwracanieElementow() {
    int start = 0;
    int end = t;
    while (start < end) {
        T temp = a[start];
        a[start] = a[end];
        a[end] = temp;
        start++;
        end--;
    }
}

template<typename T>
T MyStack<T>::pop() {
    if (isEmpty()) {
        std::cout << "Stack underflow!\n";
        return T();
    } else {
        return a[t--];
    }
}

template<typename T>
T MyStack<T>::top() const {
    if (isEmpty()) {
        std::cout << "Stack underflow!\n";
        return T();
    } else {
        return a[t];
    }
}

bool czyNawiasyPoprawneokrogle(const std::string& str) {
    MyStack<char> stack;

    for (char ch : str) {
        if (ch == '(') {
            stack.push(ch);
        } else if (ch == ')') {
            if (stack.isEmpty()) {
                return false; 
            }
            stack.pop();
        }
    }
    return stack.isEmpty();
}

bool czyNawiasyPoprawneRozne(const std::string& str) {
    MyStack<char> stack;

    for (char ch : str) {
        if (ch == '(' || ch == '{' || ch == '[') {
            stack.push(ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (stack.isEmpty()) {
                return false; 
            }
            char top = stack.pop();
            if ((ch == ')' && top != '(') ||
                (ch == '}' && top != '{') ||
                (ch == ']' && top != '[')) {
                return false; 
            }
        }
    }
    return stack.isEmpty();
}

std::string zamianaNaLiczbeBinarna(int n) {
    MyStack<int> stack;
    if (n == 0) {
        return "0";
    }
    while (n > 0) {
        stack.push(n % 2);
        n /= 2;
    }
    std::string binary;
    while (!stack.isEmpty()) {
        binary += std::to_string(stack.pop());
    }
    return binary;
}

int ocenianieWyrazenInfiksowych(const std::string& expr) {
    MyStack<int> values;
    MyStack<char> ops;
    auto precedence = [](char op) -> int {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    };
    auto applyOp = [](int a, int b, char o) -> int {
        switch (o) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return b != 0 ? a / b : 0;
            default: return 0;
        }
    };

    for (size_t i = 0; i < expr.size(); ++i) {
        char ch = expr[i];
        if (isspace(static_cast<unsigned char>(ch))) continue;
        if (isdigit(static_cast<unsigned char>(ch))) {
            int val = 0;
            while (i < expr.size() && isdigit(static_cast<unsigned char>(expr[i]))) {
                val = val * 10 + (expr[i] - '0');
                ++i;
            }
            values.push(val);
            --i;
        } else if (ch == '(') {
            ops.push(ch);
        } else if (ch == ')') {
            while (!ops.isEmpty() && ops.top() != '(') {
                int val2 = values.pop();
                int val1 = values.pop();
                char op = ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            if (!ops.isEmpty() && ops.top() == '(') ops.pop();
        } else {
            while (!ops.isEmpty() && precedence(ops.top()) >= precedence(ch)) {
                int val2 = values.pop();
                int val1 = values.pop();
                char op = ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(ch);
        }
    }

    while (!ops.isEmpty()) {
        int val2 = values.pop();
        int val1 = values.pop();
        char op = ops.pop();
        values.push(applyOp(val1, val2, op));
    }

    if (values.isEmpty()) return 0;
    return values.pop();
}

// Prosty test
int main() {
    std::string s = "(())()";
    std::cout << (czyNawiasyPoprawneokrogle(s) ? "OK\n" : "NIE\n");

    MyStack<int> si;
    si.push(10);
    si.push(20);
    std::cout << si.pop() << "\n"; // 20

    MyStack<std::string> ss;
    ss.push("hello");
    std::cout << ss.top() << "\n"; // hello

    return 0;
}