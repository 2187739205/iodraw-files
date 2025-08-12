#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
int n, m, c;
bool isCricket[MAXN][MAXN];
int parent[MAXN * MAXN];
int rankArr[MAXN * MAXN];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (rankArr[rootX] > rankArr[rootY]) {
            parent[rootY] = rootX;
        } else if (rankArr[rootX] < rankArr[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rankArr[rootX]++;
        }
    }
}

bool isValid(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

int getId(int x, int y) {
    return (x - 1) * m + y;
}

int countComponents() {
    for (int i = 1; i <= n * m; ++i) {
        parent[i] = i;
        rankArr[i] = 0;
    }
    
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    
    // Build union-find structure for fleas
    for (int x = 1; x <= n; ++x) {
        for (int y = 1; y <= m; ++y) {
            if (!isCricket[x][y]) {
                for (int d = 0; d < 4; ++d) {
                    int nx = x + dx[d];
                    int ny = y + dy[d];
                    if (isValid(nx, ny) && !isCricket[nx][ny]) {
                        unite(getId(x, y), getId(nx, ny));
                    }
                }
            }
        }
    }
    
    set<int> uniqueParents;
    for (int x = 1; x <= n; ++x) {
        for (int y = 1; y <= m; ++y) {
            if (!isCricket[x][y]) {
                uniqueParents.insert(find(getId(x, y)));
            }
        }
    }
    
    return uniqueParents.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m >> c;
    memset(isCricket, false, sizeof(isCricket));
    
    for (int i = 0; i < c; ++i) {
        int x, y;
        cin >> x >> y;
        isCricket[x][y] = true;
    }
    
    // Count initial connected components
    int initialComponents = countComponents();
    
    // If already disconnected, answer is 0
    if (initialComponents >= 2) {
        cout << 0 << endl;
        return 0;
    }
    
    // Check if removing one flea can disconnect the graph
    for (int x = 1; x <= n; ++x) {
        for (int y = 1; y <= m; ++y) {
            if (!isCricket[x][y]) {
                // Temporarily make this position a cricket
                isCricket[x][y] = true;
                
                int newComponents = countComponents();
                
                // Restore the position
                isCricket[x][y] = false;
                
                if (newComponents > 1) {
                    cout << 1 << endl;
                    return 0;
                }
            }
        }
    }
    
    // Otherwise, we need to remove 2 fleas
    cout << 2 << endl;
    return 0;
}