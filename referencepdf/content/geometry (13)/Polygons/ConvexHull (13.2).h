/**
 * Description: Top-bottom convex hull
 * Time: O(N\log N)
 * Source: Wikibooks, KACTL
 * Verification:
	* https://open.kattis.com/problems/convexhull
 */

struct convexHull {
    set<pair<ld,ld>> dupChecker;
    vector<pair<ld,ld>> points;
    vector<pair<ld,ld>> dn, up, hull;
    
    convexHull() {}
    bool cw(pd o, pd a, pd b) {
        return ((a.f-o.f)*(b.s-o.s)-(a.s-o.s)*(b.f-o.f) <= 0);
    }
    void addPoint(pair<ld,ld> p) {
        if(dupChecker.count(p)) return;
        points.pb(p);
        dupChecker.insert(p);
    }
    void addPoint(ld x, ld y) {
        addPoint(mp(x,y));
    }
    void build() {
        sort(points.begin(), points.end());
        if(sz(points) < 3) {
            for(pair<ld,ld> p: points) {
                dn.pb(p);
                hull.pb(p);
            }
            M00d(i, sz(points)) {
                up.pb(points[i]);
            }
        } else {
            for(int i = 0; i < (int)points.size(); i++) {
                while(dn.size() >= 2 && cw(dn[dn.size()-2], dn[dn.size()-1], points[i])) {
                    dn.erase(dn.end()-1);
                }
                dn.push_back(points[i]);
            }
            for(int i = (int)points.size()-1; i >= 0; i--) {
                while(up.size() >= 2 && cw(up[up.size()-2], up[up.size()-1], points[i])) {
                    up.erase(up.end()-1);
                }
                up.push_back(points[i]);
            }
            sort(dn.begin(), dn.end());
            sort(up.begin(), up.end());
            
            for(int i = 0; i < up.size()-1; i++) hull.pb(up[i]);
            for(int i = sz(dn)-1; i > 0; i--) hull.pb(dn[i]);
        }
    }
};
