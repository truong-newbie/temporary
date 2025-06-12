#include <bits/stdc++.h>
using namespace std;

// Luy th?a co s? base^expo mod m
int power(int base, int expo, int m) {
    int res = 1;
    base = base % m;
    while (expo > 0) {
        if (expo & 1)
            res = (res * 1LL * base) % m;
        base = (base * 1LL * base) % m;
        expo = expo / 2;
    }
    return res;
}

// Euclid m? r?ng d? tìm gcd và x, y sao cho ax + by = gcd(a, b)
int gcdExtended(int a, int b, int &x, int &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int x1, y1;
    int gcd = gcdExtended(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

// Tìm ngh?ch d?o modular: d sao cho (e * d) % phi == 1
int modInverse(int e, int phi) {
    int x, y;
    int g = gcdExtended(e, phi, x, y);
    if (g != 1)
        return -1; // Không t?n t?i
    else
        return (x % phi + phi) % phi;
}

// Sinh khóa RSA
void generateKeys(int &e, int &d, int &n) {
    int p = 7919;
    int q = 1009;
    n = p * q;
    int phi = (p - 1) * (q - 1);
    for (e = 2; e < phi; e++) {
        if (__gcd(e, phi) == 1)
            break;
    }
    d = modInverse(e, phi);
}

// Mã hóa s? nguyên
int encrypt(int m, int e, int n) {
    return power(m, e, n);
}

// Gi?i mã s? nguyên
int decrypt(int c, int d, int n) {
    return power(c, d, n);
}

// Mã hóa chu?i thành m?ng s?
vector<int> encryptString(const string &msg, int e, int n) {
    vector<int> encrypted;
    for (char ch : msg) {
        int m = (int)ch;
        encrypted.push_back(encrypt(m, e, n));
    }
    return encrypted;
}

// Gi?i mã chu?i t? m?ng s?
string decryptString(const vector<int> &cipher, int d, int n) {
    string decrypted = "";
    for (int c : cipher) {
        int m = decrypt(c, d, n);
        decrypted += (char)m;
    }
    return decrypted;
}

int main() {
    int e, d, n;
    generateKeys(e, d, n);
    
    cout << "Public Key (e, n): (" << e << ", " << n << ")\n";
    cout << "Private Key (d, n): (" << d << ", " << n << ")\n";

    //string message = "HELLO RSA";
    string message;
    cout << " Message : ";
    getline(cin, message);
    cout << "Original Message: " << message << endl;

    vector<int> cipher = encryptString(message, e, n);
    cout << "Encrypted Message (numbers): ";
    for (int c : cipher)
        cout << c << " ";
    cout << endl;

    string decrypted = decryptString(cipher, d, n);
    cout << "Decrypted Message: " << decrypted << endl;

    return 0;
}

