// �������� 100 ������ ������ ����������� ����� ����� ������� ����� 5 ������� - https://youtu.be/rEHheWPSG-k?t=2826

/*
 * C++ Program to Implement Miller Rabin Primality Test
 */
#include <iostream>
#include <cstring>
#include <cstdlib>
#define ll long long
using namespace std;

/*
 * calculates (a * b) % c taking into account that a * b might overflow
 */
ll mulmod(ll a, ll b, ll mod)
{
    ll x = 0, y = a % mod;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b /= 2;
    }
    return x % mod;
}
/*
 * modular exponentiation
 */
ll modulo(ll base, ll exponent, ll mod)
{
    ll x = 1;
    ll y = base;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            x = (x * y) % mod;
        y = (y * y) % mod;
        exponent = exponent / 2;
    }
    return x % mod;
}

/*
 * Miller-Rabin primality test, iteration signifies the accuracy
 */
bool Miller(ll p, int iteration)
{
    if (p < 2)
    {
        return false;
    }
    if (p != 2 && p % 2 == 0)
    {
        return false;
    }
    ll s = p - 1;
    while (s % 2 == 0)
    {
        s /= 2;
    }
    for (int i = 0; i < iteration; i++)
    {
        ll a = rand() % (p - 1) + 1, temp = s;
        ll mod = modulo(a, temp, p);
        while (temp != p - 1 && mod != 1 && mod != p - 1)
        {
            mod = mulmod(mod, mod, p);
            temp *= 2;
        }
        if (mod != p - 1 && temp % 2 == 0)
        {
            return false;
        }
    }
    return true;
}

bool test(int a) {
    int cnt = 0;
    for (int i = a; i < a + 100; ++i) {
        if (Miller(i, 5)) {
            // std::cout << i << std::endl;
            ++cnt;
        }
    }
    return cnt == 5;
}

int main()
{
    int i = 0;
    for (; i < 18860; ++i) {
        if (test(i)) {
            std::cout << i << std::endl;
        }
    }
	return 0;
}
