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

constexpr int L = 100000 + 1;
constexpr int RL = R * L + 1;
double dp[2][R][RL] = {};
double r[R] = {};
double s[RL] = {};

void solve(int N)
{
    ZERO(dp);
    ZERO(s);
    REP(i, R) dp[1][i][i + 1] = p[i];
    FOR(i, 2, N) {
        const int ip = (i - 1) & 1;
        const int ic = i & 1;
        const int M = (i - 1) * R + 1;
        REP(j, R) REP(k, M) s[k] += dp[ip][j][k];
        REP(j, R) REP(k, M) dp[ic][j][j + k + 1] += (s[k] - dp[ip][j][k]) * r[j];
        REP(j, R) REP(k, M) dp[ip][j][k] = 0;
        REP(j, R) REP(k, M) s[k] = 0;
    }
}

void res(int N, double& mean, double& var)
{
    const int ic = N & 1;
    mean = 0;
    REP(i, R) REP(j, RL) mean += j * dp[ic][i][j];
    var = 0;
    ZERO(s);
    REP(i, R) REP(j, RL) s[j] += dp[ic][i][j];
    REP(i, RL) var += SQR(i - mean) * s[i];
}

void output(const double& mean, const double& var)
{
    cout << fixed << setprecision(6) << mean << '\n' << var << endl;
}

sstrm testData(R"(0.17000491340
0.15520686444
0.15219502924
0.19007939362
0.15583770397
0.17667609533
2999)");
// 10583.017732174100713109
// 5851.525476513932206592

//0.15044480060
//0.13409301419
//0.17442237068
//0.18807442672
//0.18225873540
//0.17070665241
//99999
//
//360598.884964320636408367
//191714.990006715491674631

int main( int argc, char* argv[] )
{
    auto& input = testData;
    for (auto& pi : p) input >> pi;
    REP(i, R) r[i] = p[i] / (1 - p[i]);
    int N;
    input >> N;
    if (N <= 3000) {
        double mean, var;
        solve(N);
        res(N, mean, var);
        output(mean, var);
    }
    else {
        const int N1 = 1000 + N % 1000;
        const int N2 = N1 + 1000;
        solve(N1);
        double mean1, var1;
        res(N1, mean1, var1);
        solve(N2);
        double mean2, var2;
        res(N2, mean2, var2);
        double dmean = mean2 - mean1;
        double dvar = var2 - var1;
        const int dN = (N - N1) / 1000;
        output(mean1 + dN * dmean, var1 + dN * dvar);
    }
    return 0;
}

