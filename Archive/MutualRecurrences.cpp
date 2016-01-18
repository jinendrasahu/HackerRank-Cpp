#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <numeric>
#include <tuple>
#include <valarray>
#include <cassert>
#include <cstring>
#include <typeinfo>
#include <functional>

using namespace std;

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using sstrm = stringstream;

#define FOR(k, a, b) for (decltype(a) k = (a); k <= (b); ++k)
#define RFOR(k, a, b) for (decltype(a) k = (a); (b) <= k; --k)
#define REP(k, a) for (int k = 0; k < (a); ++k)
#define PW(x) (1ll << (x))
#define COPY2D(a, b) std::copy_n(&a[0][0], sizeof(a) / sizeof(a[0][0]), &b[0][0])

constexpr int L = 24;
constexpr ll mod = (ll) 1e9;

void print(const ll X[L][L])
{
    REP(i, L) {
        REP (j, L) cerr << X[i][j] << " ";
        cerr << endl;
    }
    cerr << endl;
}

void printV(const ll U[0][L])
{
    REP (i, L) cerr << U[0][i] << " ";
    cerr << endl;
}

void mul(const ll A[L][L], const ll B[L][L], ll R[L][L])
{
    REP(i, L) REP(j, L) R[i][j] = 0;
    REP(i, L) REP(j, L) REP(k, L) {
        R[i][j] += A[i][k] * B[k][j];
        R[i][j] %= mod;
    }
    // print(R);
}

void mulV(const ll A[L][L], const ll U[1][L], ll V[1][L])
{
    REP(i, L) V[0][i] = 0;
    REP(i, L) REP(j, L) {
        V[0][i] += A[i][j] * U[0][j];
        V[0][i] %= mod;
    }
}

ll A[L][L];

void gen_A(ll a, ll b, ll c, ll d, ll e, ll f, ll g, ll h)
{
    REP(i, L) REP(j, L) A[i][j] = 0;
    REP(i, 9) {
        ll xi = i, yi = i + 10;
        A[xi][xi + 1] = 1;
        A[yi][yi + 1] = 1;
    }

    A[9][10 - a] = 1;
    if (b == c)
        A[9][20 - b] = 2;
    else {
        A[9][20 - b] = 1;
        A[9][20 - c] = 1;
    }
    A[9][20] = 1;

    A[19][20 - e] = 1;
    if (f == g)
        A[19][10 - f] = 2;
    else {
        A[19][10 - f] = 1;
        A[19][10 - g] = 1;
    }
    A[19][22] = 1;

    A[20][20] = d;
    A[20][21] = d;
    A[21][21] = d;

    A[22][22] = h;
    A[22][23] = h;
    A[23][23] = h;

    // print(A);
}

ll V[1][L];

void gen_V()
{
    REP(i, L) V[0][i] = 1;
    V[0][20] = 0;
    V[0][22] = 0;
}

ll X[L][L];
ll tmpX[L][L];
ll tmpV[1][L];

void fi()
{
    // cerr << "inc" << endl;
    mul(X, A, tmpX);
    COPY2D(tmpX, X);
}

void fm()
{
    // cerr << "mul" << endl;
    mul(X, X, tmpX);
    COPY2D(tmpX, X);
}

void fun(ll n)
{
    if (1 == n) return;
    COPY2D(A, X);
    int j = -1;
    RFOR(i, 63, 0) {
        if (PW(i) & n) {
            j = i;
            break;
        }
    }
    // printV(V);
    // print(X);
    while (0 < j) {
        --j;
        // cerr << j << endl;
        fm();
        if (PW(j) & n) fi();
        // printV(V);
        // print(X);
    }
    mulV(X, V, tmpV);
    COPY2D(tmpV, V);
}

int main( int argc, char* argv[] )
{
    ll N;
    // cin >> N;
    N = 1;
    REP(i, N) {
        ll a, b, c, d, e, f, g, h, n;
        // cin >> a >> b >> c >> d >> e >> f >> g >> h >> n;
        {
            sstrm ss("1 2 3 2 2 1 1 4 10");
            ss >> a >> b >> c >> d >> e >> f >> g >> h >> n;
        }
        gen_A(a, b, c, d, e, f, g, h);
        gen_V();
        fun(n + 1);
        cout << V[0][9] << " " << V[0][19];
    }
    return 0;
}
