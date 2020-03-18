#include <iostream>
#include <vector>
#include <algorithm>
#include "time.h"

using namespace std;

struct Point
{
    int x, y, z;

    Point(int _x = 0, int _y = 00, int _z = 0)
    { x = _x; y = _y; z = _z ;}
};

bool operator==(const Point& p, const Point &q)
{
    return (p.x == q.x) && (p.y == q.y) && (p.z == q.z);
}
Point operator+(const Point& p, const Point &q)
{
    return Point{p.x + q.x, p.y + q.y, p.z + q.z};
}
Point operator-(const Point& p, const Point &q)
{
    return Point{p.x - q.x, p.y - q.y, p.z - q.z};
}
Point operator/(const Point& p, int d)
{
    return Point{p.x/d, p.y/d, p.z/d};
}

int prod(Point p, Point q)
{
    return p.x*q.x + p.y*q.y + p.z*q.z;
}

unsigned norm(Point p)
{
    return prod(p, p);
}


void print(Point const& p)
{
    cout << "<" << p.x << ", " << p.y << ", " << p.z << ">\n";
}
void print_set(vector<Point> const& set)
{
    cout << "\nSET\n";
    for (Point i : set)
    {
        print(i);
    }
    cout << endl;
}
void print_subset(vector<Point> const& set, vector<bool> const& m)
{
    cout << endl << "first subset:" << endl;
    for (size_t i = 0; i < set.size(); ++i)
    {
        if(m[i])
        {
            print(set[i]);
        }
    }
    cout << endl << "second subset:" << endl;
    for (size_t i = 0; i < set.size(); ++i)
    {
        if(!m[i])
        {
            print(set[i]);
        }
    }
}

Point rand_point()
{
    srand(rand());
    Point p{rand()%101, rand()%101, rand()%101};
    return p;
}
void get_random_set(vector<Point>& set, size_t cap)
{
    for (unsigned int i = 0; i < cap; ++i)
    {
        Point p = rand_point();

        while(set.end() != find(set.begin(), set.end(), p))
        {
            p = rand_point();
        }

        set.push_back(p);
    }
}

void bt(vector<Point> const& set, vector<bool>& perm, vector<bool>& best, unsigned& min_dist, unsigned pos = 0)
{
    if(pos == set.size())
    {
        unsigned dist, cnt = 0;
        Point centre_0, centre_1;

        for (unsigned i = 0; i < set.size(); ++i)
        {
            if(perm[i])
            {
                centre_0 = centre_0 + set[i];
                ++cnt;
            }
            else
            {
                centre_1 = centre_1 + set[i];
            }
        }

        if(cnt == set.size() || cnt == 0)
        {
            return;
        }

        centre_0 = centre_0/cnt;
        centre_1 = centre_1/(set.size() - cnt);
        dist = norm(centre_1 - centre_0);

        if(dist < min_dist)
        {
            min_dist = dist;
            best = perm;
        }
        return;
    }

    bt(set, perm, best, min_dist, pos+1);
    perm[pos] = true;
    bt(set, perm, best, min_dist, pos+1);
    perm[pos] = false;
}

int main()
{
    size_t set_cap;
    cout <<"Enter the number of elements in the set:\n>";
    cin >> set_cap;

    vector<Point> set;
    get_random_set(set, set_cap);

    vector<bool> perm;
    vector<bool> best;
    perm.resize(set_cap);
    best.resize(set_cap);

    print_set(set);
    cout << "\n<<---output-->>\n";

    unsigned min_dist = -1;
    bt(set, perm, best, min_dist);

    cout << "Minimum distance : "<< min_dist << endl;
    print_subset(set, best);

    cout << "\nPress any key to exit...\n";
    cin.get();
}