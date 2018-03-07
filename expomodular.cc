#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int quick_exponentiation(int x, int n, int m) {
    if (n == 0) return 1;
    else {
        int y = quick_exponentiation(x, n/2, m)%m;
        if (n%2 == 0) {
            return (y*y)%m;
        }
        else {
            return (((y*y)%m)*x)%m;
        }
    }
}
 
int main() {
 
    int x;
    while(cin >> x) {
        int n, m;
        cin >> n >> m;
        cout << quick_exponentiation(x, n, m) << endl;
    }
}