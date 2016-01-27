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
#include <memory>
#include <regex>
#include <iomanip>

using namespace std;

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using sstrm = stringstream;

#define ZERO(a) std::memset((a), 0, sizeof(a))
#define FILL1D(a, v) std::fill_n(a, sizeof(a) / sizeof(a[0]), v)
#define FILL2D(a, v) std::fill_n(&a[0][0], sizeof(a) / sizeof(a[0][0]), v)
#define FILL3D(a, v) std::fill_n(&a[0][0][0], sizeof(a) / sizeof(a[0][0][0]), v)
#define FILL4D(a, v) std::fill_n(&a[0][0][0][0], sizeof(a) / sizeof(a[0][0][0][0]), v)
#define COPY1D(a, b) std::copy_n(a, sizeof(a) / sizeof(a[0]), b)
#define COPY2D(a, b) std::copy_n(&a[0][0], sizeof(a) / sizeof(a[0][0]), &b[0][0])
#define COPY3D(a, b) std::copy_n(&a[0][0][0], sizeof(a) / sizeof(a[0][0][0]), &b[0][0][0])
#define COPY4D(a, b) std::copy_n(&a[0][0][0][0], sizeof(a) / sizeof(a[0][0][0][0]), &b[0][0][0][0])
#define FOR(k, a, b) for (decltype(a) k = (a); k <= (b); ++k)
#define REP(k, a) for (int k = 0; k < (a); ++k)
#define SQR(x) ((x) * (x))
#define PW(x) (1ll << (x))
#define BCNT(x) __builtin_popcountll(x)
#define LZC(x) ((x) == 0 ? sizeof(x) * 8 : __builtin_clzll(x))
#define RZC(x) ((x) == 0 ? sizeof(x) * 8 : __builtin_ctzll(x))
#define ALL(c) (c).begin(),(c).end()
#define HAS(c, x) ((c).find(x) != (c).end())
#define CHAS(c,x) (find(ALL(c), x) != (c).end())

template<typename S, typename T> inline void chmin(S& a, T b) { if (b < a) a = b; }
template<typename S, typename T> inline void chmax(S& a, T b) { if (a < b) a = b; }

// Throw the die, and record the outcome as d[1].
//
// For i from 2 to N:
//     Repeatedly throw the die until the outcome is different from d[i-1].
//     Record the outcome as d[i].
//
// Output d[1] + d[2] + ... + d[N].

constexpr int R = 6;
double p[R];
double r[R][R];
int N;

constexpr int L = 100000 + 1;
constexpr int RL = R * L + 1;
double dp[2][R][RL] = {};

void solve()
{
    REP(i, R) dp[1][i][i + 1] = p[i];
    FOR(i, 2, N) {
        int ip = (i - 1) & 1;
        int ic = i & 1;
        REP(j, R) REP(k, R) {
            if (j == k) continue;
            FOR(l, 1, (i - 1) * R) {
                dp[ic][k][l + k + 1] += dp[ip][j][l] * r[k][j];
            }
        }
        REP(j, R) FOR(k, 1, (i - 1) * R) dp[ip][j][k] = 0;
    }
}

sstrm testData(R"(0.16666666667
0.16666666666
0.16666666667
0.16666666667
0.16666666666
0.16666666667
300)");

int main( int argc, char* argv[] )
{
    auto& input = testData;
    for (auto& pi : p) input >> pi;
    REP(i, R) REP(j, 6) r[i][j] = p[i] / (1 - p[j]);
    input >> N;
    solve();
    double ev = 0;
    double ev2 = 0;
    int ic = N & 1;
    REP(i, R) REP(j, RL) {
        ev += j * dp[ic][i][j];
        ev2 += SQR(j) * dp[ic][i][j];
    }
    cout << fixed << setprecision(6) << ev << '\n' << ev2 - SQR(ev) << endl;
    return 0;
}

