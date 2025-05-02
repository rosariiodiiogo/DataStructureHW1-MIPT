#include <iostream>

using ll = long long;

inline int max(int a, int b) { return (a > b) ? a : b; }

static const int MAXN = 300000 + 5;

ll keyArr[MAXN];
int heightArr[MAXN];
int leftArr[MAXN];
int rightArr[MAXN];
int nodes = 0;

int newNode(ll k) {
    ++nodes;
    keyArr[nodes] = k;
    heightArr[nodes] = 1;
    leftArr[nodes] = 0;
    rightArr[nodes] = 0;
    return nodes;
}

int getHeight(int u) {
    return u ? heightArr[u] : 0;
}

void updateHeight(int u) {
    heightArr[u] = 1 + max(getHeight(leftArr[u]), getHeight(rightArr[u]));
}

int balanceFactor(int u) {
    return getHeight(leftArr[u]) - getHeight(rightArr[u]);
}

int rotateRight(int y) {
    int x = leftArr[y];
    int T2 = rightArr[x];
    rightArr[x] = y;
    leftArr[y] = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

int rotateLeft(int x) {
    int y = rightArr[x];
    int T2 = leftArr[y];
    leftArr[y] = x;
    rightArr[x] = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

int insertNode(int u, ll k) {
    if (!u) return newNode(k);
    if (k < keyArr[u])
        leftArr[u] = insertNode(leftArr[u], k);
    else if (k > keyArr[u])
        rightArr[u] = insertNode(rightArr[u], k);
    else
        return u;

    updateHeight(u);
    int bf = balanceFactor(u);

    if (bf > 1 && k < keyArr[leftArr[u]])
        return rotateRight(u);
    if (bf < -1 && k > keyArr[rightArr[u]])
        return rotateLeft(u);
    if (bf > 1 && k > keyArr[leftArr[u]]) {
        leftArr[u] = rotateLeft(leftArr[u]);
        return rotateRight(u);
    }
    if (bf < -1 && k < keyArr[rightArr[u]]) {
        rightArr[u] = rotateRight(rightArr[u]);
        return rotateLeft(u);
    }
    return u;
}

bool lowerBoundNode(int u, ll x, ll &ans) {
    bool found = false;
    while (u) {
        if (keyArr[u] >= x) {
            ans = keyArr[u];
            found = true;
            u = leftArr[u];
        } else {
            u = rightArr[u];
        }
    }
    return found;
}

int main() {

    int n;
    if (!(std::cin >> n)) return 0;

    int root = 0;
    ll lastAns = 0;
    bool prevWasQuery = false;
    const ll MOD = 1000000000LL;

    for (int i = 0; i < n; ++i) {
        char op;
        ll x;
        std::cin >> op >> x;
        if (op == '+') {
            if (prevWasQuery) x = (x + lastAns) % MOD;
            root = insertNode(root, x);
            prevWasQuery = false;
        } else if (op == '?') {
            ll ans;
            if (lowerBoundNode(root, x, ans)) {
                std::cout << ans << '\n';
                lastAns = ans;
            } else {
                std::cout << -1 << '\n';
                lastAns = -1;
            }
            prevWasQuery = true;
        }
    }
    return 0;
}
