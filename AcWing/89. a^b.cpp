#include <bits/stdc++.h>

using namespace std;

int a, b, p;

int pow(int a, int b, int p) {
    int ans = 1 % p;
    
    while (b) {
        if (b & 1) ans = (long long)ans * a % p;
        a = (long long)a * a % p;
        b >>= 1;
    }
    
    return ans;
}

int main() {
	cin >> a >> b >> p;

    int ans = pow(a, b, p);
	
	cout << ans << endl;
	
	return 0;
}