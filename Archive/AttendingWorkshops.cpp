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

const int dd[] = {1, 0, -1, 0};

struct Workshop
{
    int s;
    int d;
};

struct Available_Workshops
{
    int N;
    Workshop* a;
};

Available_Workshops* initialize(int start_time[], int duration[], int N)
{
    auto ret = new Available_Workshops();
    ret->N = N;
    ret->a = new Workshop[N];
    REP(i, N) {
        ret->a[i] = Workshop{start_time[i], duration[i]};
    }
    return ret;
}

int CalculateMaxWorkshops (Available_Workshops* ptr)
{
    int N = ptr->N;
    auto v = vector<pair<int, int>>(N);
    REP(i, N) {
        auto& w = ptr->a[i];
        v[i] = make_pair(w.s + w.d, w.s);
    }
    sort(ALL(v));
    int c = 0;
    int ret = 0;
    for (auto p : v) {
        if (c <= p.second) {
            ++ret;
            c = p.first;
        }
    }
    return ret;
}

int main( int argc, char* argv[] )
{
    int n;
    cin>>n;
    int start_time[n],duration[n];
    for(int i=0;i<n;i++)
    {
        cin>>start_time[i];
    }
    for(int i=0;i<n;i++)
    {
        cin>>duration[i];
    }

    Available_Workshops * ptr;
    ptr=initialize(start_time,duration,n);
    cout<<CalculateMaxWorkshops(ptr)<<endl;
    return 0;
}

