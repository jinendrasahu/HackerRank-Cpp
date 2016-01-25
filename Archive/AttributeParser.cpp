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

struct Tag;
using TagPtr = shared_ptr<Tag>;

struct Tag
{
    weak_ptr<Tag> p;
    map<string, TagPtr> c;
    map<string, string> a;
};

sstrm input(R"(10 12
<tag0 id = "blah">
<tag1 value = "Hello World !">
<tag2 name = "Name1">
<tag3>
<tag4 name = " bb " value = " val " size = " 66">
</tag4>
</tag3>
</tag2>
</tag1>
</tag0>
tag0.tag1.tag2~name
tag0.tag1~name
tag0.tag1~value
tag0~name
tag0~id
tag0.tag1~value
tag0.tag1.tag2~name
tag0.tag1.tag100.tag3.tag4~name
tag0.tag1.tag2.tag3.tag4~value
tag0.tag1.tag2.tag3.tag4~size
tag0~
abc)");

vector<string>& split(const string& s, char delim, vector<string>& elems)
{
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<string> split(const string& s, char delim)
{
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

int main( int argc, char* argv[] )
{
    auto& strm = input;
    int N, Q;
    strm >> N >> Q;
    string s;
    getline(strm, s);
    regex new_tag(R"( *<(\w+)(.*)> *)");
    regex end_tag(R"( *</(\w+) *> *)");
    auto root = make_shared<Tag>();
    auto curr = root;
    REP(i, N) {
        getline(strm, s);
        smatch g;
        if (regex_match(s, g, new_tag)) {
            assert(g.size() == 2 || g.size() == 3);
            const string tag = g[1];
            // cerr << "New tag: " << tag << endl;
            auto new_tag = make_shared<Tag>();
            curr->c[tag] = new_tag;
            new_tag->p = curr;
            curr = new_tag;
            if (g.size() == 3) {
                string attribs = g[2];
                regex attrib(R"( *(\w+) *= *\"([^\"]+)\" *)");

                auto words_begin = sregex_iterator(ALL(attribs), attrib);
                auto words_end = sregex_iterator();
                for (auto i = words_begin; i != words_end; ++i) {
                    auto g2 = *i;
                    assert(3 == g2.size());
                    curr->a[g2[1]] = g2[2];
                }
            }
        }
        else if (regex_match(s, g, end_tag)) {
            // cerr << "End tag!" << endl;
            assert(!curr->p.expired());
            curr = curr->p.lock();
        }
    }
    regex query(R"((.+)~(.+))");
    REP(i, Q) {
        strm >> s;
        smatch g;
        if (regex_match(s, g, query)) {
            int n = g.size();

            // assert(3 == n);
            if (3 != n) cout << "Not Found!" << endl;

            auto tags = split(g[1], '.');
            const string name = g[n - 1];
            auto curr = root;
            bool found = true;
            for (auto& tag : tags) {
                auto it = curr->c.find(tag);
                if (it == curr->c.end()) {
                    found = false;
                    break;
                }
                curr = it->second;
            }
            if (found) {
                auto it = curr->a.find(name);
                if (it == curr->a.end()) {
                    found = false;
                }
                else {
                    cout << it->second << endl;
                }
            }
            if (!found) {
                cout << "Not Found!" << endl;
            }
        }
        else {
            // assert(false);
            cout << "Not Found!" << endl;
        }
    }
    return 0;
}

