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

// This problem is to get you familiar with virtual functions. Create three classes Person, Professor and Student.
// The class Person should have data members name and age. The classes Professor and Student should inherit from the class Person.
//
// The class Professor should have two data members: publications and cur_{id}. There will be two member functions: getdata and putdata.
// The function getdata should get the input from the user: the name, age and publications of the professor. The function putdata should
// print the name, age, publications and the cur_{id} of the professor.
//
// The class Student should have two data members: marks, which is an array of size 6 and cur_{id}. It has two member functions:
// getdata and putdata. The function getdata should get the input from the user: the name, age, and the marks of the student in 6 subjects.
// The function putdata should print the name, age, sum of the marks and the cur_{id} of the student.
//
//For each object being created of the Professor or the Student class, sequential id's should be assigned to them starting from 1.
//
//Solve this problem using virtual functions, constructors and static variables. You can create more data members if you want.

struct Person
{
    virtual ~Person() {}

    virtual void getdata()
    {
        cin >> name >> age;
    }

    virtual void putdata()
    {
        cout << name << " " << age;
    }

    string name;
    int age;
};

struct Professor : Person
{
    Professor()
    : curid(id++)
    {}

    virtual ~Professor() {}

    virtual void getdata()
    {
        Person::getdata();
        cin >> publications;
    }

    virtual void putdata()
    {
        Person::putdata();
        cout << " " << publications << " " << curid << "\n";
    }

    int publications = 0;
    int curid = 0;

private:
    static int id;
};

int Professor::id = 1;

struct Student : Person
{
    Student()
    : curid(id++)
    {}

    virtual ~Student() {}

    virtual void getdata()
    {
        Person::getdata();
        REP(i, 6) cin >> marks[i];
    }

    virtual void putdata()
    {
        Person::putdata();
        int sum = 0;
        REP(i, 6) sum += marks[i];
        cout << " " << sum << " " << curid << "\n";
    }

    vector<int> marks{6, 0};
    int curid = 0;

private:
    static int id;
};

int Student::id = 1;

int main( int argc, char* argv[] )
{
    int n, val;
    cin>>n; //The number of objects that is going to be created.
    Person *per[n];

    for(int i = 0;i < n;i++){

        cin>>val;
        if(val == 1){
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        }
        else per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(); // Get the data from the user.

    }

    for(int i=0;i<n;i++)
        per[i]->putdata(); // Print the required output for each object.

    return 0;
}

