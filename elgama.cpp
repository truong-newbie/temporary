#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef long long ll;

// Tính GCD
ll gcd(ll a, ll b) {
    if (a < b)
        return gcd(b, a);
    else if (a % b == 0)
        return b;
    else
        return gcd(b, a % b);
}

// Hàm sinh khóa bí m?t (key)
ll gen_key(ll q) {
    ll key = rand() % q;
    while (gcd(q, key) != 1) {
        key = rand() % q;
    }
    return key;
}

// Luy th?a modulo (a^b mod c)
ll power(ll a, ll b, ll c) {
    ll x = 1;
    ll y = a;
    while (b > 0) {
        if (b % 2 != 0)
            x = (x * y) % c;
        y = (y * y) % c;
        b /= 2;
    }
    return x % c;
}

// Hàm mã hóa ElGamal
pair<vector<ll>, ll> encrypt(string msg, ll q, ll h, ll g) {
    vector<ll> en_msg;

    ll k = gen_key(q);        // khóa bí m?t c?a ngu?i g?i
    ll s = power(h, k, q);    // s = h^k mod q
    ll p = power(g, k, q);    // p = g^k mod q

    cout << "g^k used : " << p << endl;
    cout << "g^ak used : " << s << endl;

    for (char ch : msg) {
        en_msg.push_back(s * int(ch));
    }

    return make_pair(en_msg, p);
}

// Hàm gi?i mã ElGamal
string decrypt(vector<ll> en_msg, ll p, ll key, ll q) {
    string dr_msg;
    ll h = power(p, key, q);  // h = p^key mod q
    for (ll val : en_msg) {
        char ch = char(val / h);
        dr_msg.push_back(ch);
    }
    return dr_msg;
}

// Hàm chính
int main() {
    srand(time(0));
    
    string msg = "encryption";
    cout << "Original Message: " << msg << endl;

    ll q = rand() % 100000 + 10000;  // gi?i h?n nh? hon d? ch?y du?c
    ll g = rand() % q;

    ll key = gen_key(q);      // khóa bí m?t ngu?i nh?n
    ll h = power(g, key, q);  // g^a mod q

    cout << "g used : " << g << endl;
    cout << "g^a used : " << h << endl;

    pair<vector<ll>, ll> encrypted = encrypt(msg, q, h, g);
    vector<ll> en_msg = encrypted.first;
    ll p = encrypted.second;

    string decrypted = decrypt(en_msg, p, key, q);
    cout << "Decrypted Message: " << decrypted << endl;

    return 0;
}

