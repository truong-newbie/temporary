#include <bits/stdc++.h>
using namespace std;

// Kiem tra so nguyen to don gian
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= sqrt(n); ++i)
        if (n % i == 0) return false;
    return true;
}

// Luy thua co mod
int power(int base, int expo, int mod) {
    int res = 1;
    base = base % mod;
    while (expo > 0) {
        if (expo & 1)
            res = (res * 1LL * base) % mod;
        base = (base * 1LL * base) % mod;
        expo >>= 1;
    }
    return res;
}

// Euclid mo rong
int gcdExtended(int a, int b, int &x, int &y) {
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    int x1, y1;
    int g = gcdExtended(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return g;
}

// Tim nghich dao modular
int modInverse(int e, int phi) {
    int x, y;
    int g = gcdExtended(e, phi, x, y);
    if (g != 1) return -1;
    return (x % phi + phi) % phi;
}

// Sinh khoa RSA
bool generateKeys(int p, int q, int e, int &d, int &n) {
    if (!isPrime(p) || !isPrime(q)) {
        cout << "p va q phai la so nguyen to.\n";
        return false;
    }
    n = p * q;
    int phi = (p - 1) * (q - 1);
    if (__gcd(e, phi) != 1) {
        cout << "e khong nguyen to cung nhau voi phi(n).\n";
        return false;
    }
    d = modInverse(e, phi);
    if (d == -1) {
        cout << "Khong tim duoc d.\n";
        return false;
    }
    return true;
}

// Ma hoa ky tu
int encrypt(int m, int e, int n) {
    return power(m, e, n);
}

// Giai ma ky tu
int decrypt(int c, int d, int n) {
    return power(c, d, n);
}

// Ma hoa chuoi
vector<int> encryptString(const string &msg, int e, int n) {
    vector<int> encrypted;
    for (char ch : msg) {
        encrypted.push_back(encrypt((int)ch, e, n));
    }
    return encrypted;
}

// Giai ma chuoi
string decryptString(const vector<int> &cipher, int d, int n) {
    string res;
    for (int c : cipher) {
        res += (char)decrypt(c, d, n);
    }
    return res;
}
//61,53,17
int main() {
    int p, q, e, d, n;

    cout << "Nhap so nguyen to p: ";
    cin >> p;
    cout << "Nhap so nguyen to q: ";
    cin >> q;
    cout << "Nhap so nguyen e (nguyen to cung nhau voi (p-1)*(q-1)): ";
    cin >> e;

    if (!generateKeys(p, q, e, d, n)) return 1;

    cout << "\nKhoa cong khai (e, n): (" << e << ", " << n << ")";
    cout << "\nKhoa bi mat (d, n): (" << d << ", " << n << ")\n";

    cin.ignore(); // Xoa ky tu '\n' sau cin
    string message;
    cout << "\nNhap chuoi can ma hoa: ";
    getline(cin, message);

    vector<int> cipher = encryptString(message, e, n);
    cout << "Chuoi sau khi ma hoa (so): ";
    for (int c : cipher) cout << c << " ";
    cout << "\n";

    string decrypted = decryptString(cipher, d, n);
    cout << "Chuoi sau khi giai ma: " << decrypted << "\n";

    return 0;
}

