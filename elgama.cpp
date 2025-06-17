#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef long long ll;

// Kiem tra so nguyen to
bool isPrime(ll n) {
    if (n <= 1) return false;
    for (ll i = 2; i <= sqrt(n); i++)
        if (n % i == 0) return false;
    return true;
}

// Luy thua co mod
ll power(ll a, ll b, ll m) {
    ll result = 1;
    a = a % m;
    while (b > 0) {
        if (b % 2 == 1)
            result = (result * a) % m;
        a = (a * a) % m;
        b /= 2;
    }
    return result;
}

// Uoc chung lon nhat
ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Ham ma hoa
pair<vector<ll>, ll> encrypt(string msg, ll q, ll h, ll g, ll k) {
    vector<ll> encrypted;
    ll s = power(h, k, q);
    ll p = power(g, k, q);

    cout << "g^k dung (p): " << p << "\n";
    cout << "h^k dung (chia khoa chung s): " << s << "\n";

    for (int i = 0; i < msg.length(); i++) {
        encrypted.push_back(s * (ll)msg[i]);
    }

    return make_pair(encrypted, p);
}

// Ham giai ma
string decrypt(const vector<ll>& encrypted, ll p, ll key, ll q) {
    string decrypted = "";
    ll h = power(p, key, q);

    for (int i = 0; i < encrypted.size(); i++) {
        decrypted += (char)(encrypted[i] / h);
    }

    return decrypted;
}

int main() {
    ll q, g, a, k;
    string msg;

    // Nhap q
    do {
        cout << "Nhap so nguyen to q (>1000): ";
        cin >> q;
        if (!isPrime(q) || q <= 1000)
            cout << "q khong hop le. Vui long nhap lai.\n";
    } while (!isPrime(q) || q <= 1000);

    // Nhap g
    do {
        cout << "Nhap g (2 <= g < q): ";
        cin >> g;
        if (g < 2 || g >= q)
            cout << "g khong hop le. Vui long nhap lai.\n";
    } while (g < 2 || g >= q);

    // Nhap khoa rieng a
    do {
        cout << "Nhap khoa rieng a (2 <= a < q): ";
        cin >> a;
        if (a < 2 || a >= q || gcd(a, q) != 1)
            cout << "Khoa a khong hop le. Vui long nhap lai.\n";
    } while (a < 2 || a >= q || gcd(a, q) != 1);

    // Tinh h = g^a mod q
    ll h = power(g, a, q);

    // Nhap khoa tam thoi k
    do {
        cout << "Nhap khoa tam thoi k (2 <= k < q, gcd(k, q) = 1): ";
        cin >> k;
        if (k < 2 || k >= q || gcd(k, q) != 1)
            cout << "Khoa k khong hop le. Vui long nhap lai.\n";
    } while (k < 2 || k >= q || gcd(k, q) != 1);

    // Nhap thong diep
    cin.ignore();
    cout << "Nhap thong diep can ma hoa: ";
    getline(cin, msg);

    // Goi ham ma hoa
    pair<vector<ll>, ll> result = encrypt(msg, q, h, g, k);
    vector<ll> encrypted = result.first;
    ll p = result.second;

    // Hien thi ma hoa
    cout << "Thong diep da ma hoa: ";
    for (int i = 0; i < encrypted.size(); i++) {
        cout << encrypted[i] << " ";
    }
    cout << "\n";

    // Giai ma
    string decrypted = decrypt(encrypted, p, a, q);
    cout << "Thong diep sau khi giai ma: " << decrypted << "\n";

    return 0;
}

