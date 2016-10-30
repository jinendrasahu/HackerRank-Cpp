#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <memory>
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
#include <unordered_map>
#include <unordered_set>

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
#define RFOR(k, a, b) for (decltype(a) k = (a); (b) <= k; --k)
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

/*
12.0
8.0
5.0
4.5
5.0
6.0
 */
sstrm testData2(R"(6
12
4
5
3
8
7)");

sstrm testData3(R"(3
12
4
5)");

sstrm testData4(R"(4
3
3
3
10)");

int main()
{
    auto& input = testData4;
    int n;
    input >> n;
    vector<int> c(101);
    vector<int> b(100001);
    auto find_ith = [&](int i) {
        //cerr << i << "\n";
        int j = 0;
        int jc = 0;
        const int skip = i + 1;
        while (jc < skip) jc += c[j++];
        //cerr << "j: " << j << ", jc:" << jc << endl;
        assert(j <= 100);
        jc -= c[--j];
        assert(jc < skip);
        int k = j * 1000;
        //cerr << "k:" << k << endl;
        while (jc < skip) if (b[k++]) jc += b[k - 1];
        --k;
        return k;
    };
    int x;
    for(int i = 1; i <= n; i++) {
        input >> x;
        ++c[x / 1000];
        ++b[x];
        if (i % 2 == 1) cout << find_ith(i / 2) << ".0\n";
        else {
            int m1 = find_ith(i / 2 - 1);
            int m2 = find_ith(i / 2);
            cout << (m1 + m2) / 2;
            if ((m1 + m2) % 2 == 1) cout << ".5\n";
            else cout << ".0\n";
        }
    }
    return 0;
}
