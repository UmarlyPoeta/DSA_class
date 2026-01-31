#include <bits/stdc++.h>
using namespace std;

// 3
struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

bool isValidBST(Node* root, long long minVal = LLONG_MIN, long long maxVal = LLONG_MAX) {
    if (!root) return true;
    if (root->val <= minVal || root->val >= maxVal) return false;
    return isValidBST(root->left, minVal, root->val) && 
           isValidBST(root->right, root->val, maxVal);
}

// 4
long long mergeAndCount(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp;
    int i = left, j = mid + 1;
    long long invCount = 0;
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp.push_back(arr[i++]);
        } else {
            temp.push_back(arr[j++]);
            invCount += (mid - i + 1);
        }
    }
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);
    
    for (int i = left; i <= right; i++) arr[i] = temp[i - left];
    return invCount;
}

long long mergeSortAndCount(vector<int>& arr, int left, int right) {
    long long invCount = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        invCount += mergeSortAndCount(arr, left, mid);
        invCount += mergeSortAndCount(arr, mid + 1, right);
        invCount += mergeAndCount(arr, left, mid, right);
    }
    return invCount;
}

long long countInversions(vector<int> arr) {
    return mergeSortAndCount(arr, 0, arr.size() - 1);
}

// 5

const int N = 1005;
const int M = 2005;

int head[N], to[M], nxt[M], ecnt = 0;
int dist[N], par[N];
int q[N];

void add(int u, int v) {
    to[ecnt] = v;
    nxt[ecnt] = head[u];
    head[u] = ecnt++;
}

void graph() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        head[i] = dist[i] = par[i] = -1;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }

    int s;
    cin >> s;

    int l = 0, r = 0;
    dist[s] = 0;
    q[r++] = s;

    while (l < r) {
        int u = q[l++];
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                par[v] = u;
                q[r++] = v;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << dist[i];
        if (i < n) cout << " ";
    }
    cout << "\n";

    int qn;
    cin >> qn;
    while (qn--) {
        int t;
        cin >> t;

        cout << "dist(s,t) = " << dist[t] << "\n";
        cout << "path: ";

        if (dist[t] == -1) {
            cout << "NONE\n";
        } else {
            int p[N], k = 0;
            while (t != -1) {
                p[k++] = t;
                t = par[t];
            }
            for (int i = k - 1; i >= 0; i--) {
                cout << p[i];
                if (i) cout << " -> ";
            }
            cout << "\n";
        }
    }
}

int main() {
    graph();
}
