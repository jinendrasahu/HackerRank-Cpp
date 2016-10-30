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

int lti(char c)
{
    return c - 'a';
}

struct Trie
{
    int count = 0;
    std::array<std::unique_ptr<Trie>, 26> desc;
    void add(const std::string s) {
        if (s == "") return;
        auto& chld = desc[lti(s[0])];
        if (!chld) {
            chld = std::make_unique<Trie>();
        }
        ++(chld->count);
        chld->add(s.substr(1));
    }
    int find(const std::string s) const {
        if (s == "") return count;
        auto& chld = desc[lti(s[0])];
        if (!chld) return 0;
        return chld->find(s.substr(1));
    }
};

sstrm testData2(R"(3
{[()]}
{[(])}
{{[[(())]]}})");

bool isBalanced(const string& s)
{
    vector<char> v;
    auto isOpen = [&s](int j) {
        return s[j] == '(' || s[j] == '{' || s[j] == '[';
    };
    auto getClose = [](char c) {
        switch (c) {
            case '(': return ')';
            case '{': return '}';
            case '[': return ']';
        }
        throw exception();
    };
    for (int i = 0; i < s.size(); ++i) {
        if (isOpen(i)) v.push_back(s[i]);
        else if (0 < v.size() && getClose(v[v.size() - 1]) == s[i]) v.pop_back();
        else return false;
    }
    return 0 == v.size();
}

int main()
{
    auto& input = testData2;
    int t;
    input >> t;
    for(int a0 = 0; a0 < t; a0++){
        string expression;
        input >> expression;
        bool answer = isBalanced(expression);
        if(answer)
            cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
