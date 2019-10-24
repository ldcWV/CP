/**
 * Description: geo template that Howard uses
 * Source: own
 * Verification: ?
 */

#include <bits/stdc++.h>
using namespace std;
#define ld long double
#define cd complex<ld>
#define all(v) v.begin(), v.end()

const ld PI = acos(-1.0);
const ld EPS = 1e-7;

bool eq(cd a, cd b) { return abs(a-b) < EPS; }
cd normalize(cd z) { return z / norm(z); }

// reflects z over the line through a and b
cd reflect(cd z, cd a, cd b) { return conj((z-a)/(b-a)) * (b-a) + a; }

// projects z onto the line through a and b
cd proj(cd z, cd a, cd b) { return (z + reflect(z, a, b))/(ld)2; }

// check collinearity
bool collinear(cd a, cd b, cd c) { return abs(imag((b-a)/(c-a))) < EPS; }

// intersection of the line through a,b with the line through c,d
cd intersect(cd a, cd b, cd c, cd d) {
    cd num = (conj(a)*b - a*conj(b))*(c-d) - (a-b)*(conj(c)*d - c*conj(d));
    cd den = (conj(a) - conj(b))*(c-d) - (a-b)*(conj(c) - conj(d));
    return num / den;
}

cd circumcenter(cd a, cd b, cd c) {
    b -= a, c -= a;
    return (b*norm(c) - c*norm(b))/(b*conj(c) - c*conj(b)) + a;
}

// Convex Hull

bool cmpAngle(cd a, cd b) { return arg(a / b) < 0; }
bool cmpImag(cd a, cd b) { return imag(a) < imag(b); }
vector<cd> ConvexHull(vector<cd> pts) {
    if (pts.size() <= 3) return pts;
    sort(all(pts), cmpImag);
    cd O = pts[0];
    for (cd &p : pts) p -= O;
    sort(pts.begin() + 1, pts.end(), cmpAngle);
    for (cd &p : pts) p += O;
    vector<cd> h{ pts[0], pts[1] };
    for (int i = 2; i < pts.size(); i++) {
        cd a = h[h.size() - 2];
        cd b = h[h.size() - 1];
        cd c = pts[i];
        while (arg((a - b) / (c - b)) <= EPS) { // If angle ABC is concave, remove B
            h.pop_back();
            a = h[h.size() - 2];
            b = h[h.size() - 1];
        }
        h.push_back(c);
    }
    return h;
}

int main() {
    cd z = cd(3, 4); // 3 + 4i
    real(z); // 3.0
    imag(z); // 4.0
    abs(z); // 5.0
    norm(z); // 25.0
    arg(z); // angle in [-pi, pi]
    conj(z); // 3 - 4i
    polar(r, theta); // r * e^theta
}
