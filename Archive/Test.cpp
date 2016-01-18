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

constexpr int N1 = 10;
constexpr int N2 = 20;
constexpr int N3 = 30;
constexpr int N4 = 40;

int dp1[N1];
int dp2[N1][N2];
int dp3[N1][N2][N3];
int dp4[N1][N2][N3][N4];

bool verify(int v)
{
    bool ok = true;
    REP(i, N1) {
        if (dp1[i] != v) {
            ok = false;
            cerr << "dp1[" << i << "]" << dp1[i] << endl;
        }
        REP(j, N2) {
            if (dp2[i][j] != v) {
                ok = false;
                cerr << "dp2[" << i << "][" << j << "] = " << dp2[i][j] << endl;
            }
            REP(k, N3) {
                if (dp1[i] != v) {
                    ok = false;
                    cerr << "dp3[" << i << "][" << j << "][" << k << "] = " << dp3[i][j][k] << endl;
                }
                REP(l, N4) {
                    if (dp4[i][j][k][l] != v) {
                        ok = false;
                        cerr << "dp4[" << i << "][" << j << "][" << k << "][" << l << "] = " << dp4[i][j][k][l] << endl;
                    }
                }
            }
        }
    }
    return ok;
}

int tmp1[N1];
int tmp2[N1][N2];
int tmp3[N1][N2][N3];
int tmp4[N1][N2][N3][N4];

int main( int argc, char* argv[] )
{
    ZERO(dp1);
    ZERO(dp2);
    ZERO(dp3);
    ZERO(dp4);
    verify(0);
    FILL1D(dp1, 1);
    FILL2D(dp2, 1);
    FILL3D(dp3, 1);
    FILL4D(dp4, 1);
    verify(1);
    FILL1D(dp1, 1);
    FILL2D(dp2, 1);
    FILL3D(dp3, 1);
    FILL4D(dp4, 1);
    verify(1);
    ZERO(dp1);
    ZERO(dp2);
    ZERO(dp3);
    ZERO(dp4);
    verify(0);
    FILL1D(tmp1, 1);
    FILL2D(tmp2, 1);
    FILL3D(tmp3, 1);
    FILL4D(tmp4, 1);
    COPY1D(tmp1, dp1);
    COPY2D(tmp2, dp2);
    COPY3D(tmp3, dp3);
    COPY4D(tmp4, dp4);
    verify(1);
    cout << "Done!" << endl;
    return 0;
}
