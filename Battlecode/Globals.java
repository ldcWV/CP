import java.util.*;
import bc.*;

public class Globals {
    static int[][] marsVal = new int[50][50];
    static int co = 0, rocket = 0, totRocket = 0, numFriendly = 0;
    static boolean[][] sentRocket = new boolean[50][50];
    static long mxTime = 0, totTime = 0; 
    static int killMode = 0, worker = 0, attack = 0, lastSeen = 0;

    
    static int[] minFac = new int[2501], fac = new int[2501];
    static int[] minWork = new int[2501], work = new int[2501];
    static int[] sz = new int[2501], cNum = new int[2501];
    static boolean[] ok = new boolean[2501];
    
    static long startTime;
    
    static GameController gc;
    
    static final int INF = 1000000000;
    static Random ran = new Random();
    
    static final int[] xdir = {0,1,1,0,-1,-1,-1,0,1};
    static final int[] ydir = {0,0,1,1,1,0,-1,-1,-1};
    static Direction[] directions = {Direction.Center,
                                     Direction.East,Direction.Northeast,Direction.North,Direction.Northwest,
                                     Direction.West,Direction.Southwest,Direction.South,Direction.Southeast};


    static boolean[][] visit = new boolean[50][50];

    ////////////////////
    
    static boolean[][] done = new boolean[50][50];
    static int[][][][] distGround = new int[50][50][50][50]; 

    ////////////////////
    static int[] workerProfit = new int[1001];

    static int getWorkerProfit(int l, int r) { // get total worker profit from rounds l..r
    		int ans = 0;
    		if (l <= 0) {
    			ans -= 5*l;
    			l = 1;
    		}
    		for (int i = l; i <= r; i++) ans += workerProfit[i];
    		return ans;
    }
    ////////////////////
    
    static void genDist(int initx, int inity) {
        if (done[initx][inity] == true) return;
        done[initx][inity] = true;
        
        for (int i = 0; i < C.getWidth(); ++i)
            for (int j = 0; j < C.getHeight(); ++j) 
                distGround[initx][inity][i][j] = INF;
        
        if (!valid(initx,inity)) return;

        distGround[initx][inity][initx][inity] = 0;
        LinkedList<Integer> L = new LinkedList<>();
        L.add(hsh(initx,inity));

        while (L.size() > 0) {
            int y = (int)L.poll();
            int x = y/50; y %= 50;
            for (int i = 0; i < 9; ++i) {
                int X = x+xdir[i], Y = y+ydir[i];
                if (valid(X,Y) && distGround[initx][inity][X][Y] == INF) {
                    distGround[initx][inity][X][Y] = distGround[initx][inity][x][y]+1;
                    L.add(hsh(X,Y));
                }
            }
        }
    }

    static int getDistGround(MapLocation A, MapLocation B) {
        genDist(B.getX(),B.getY());
        return distGround[B.getX()][B.getY()][A.getX()][A.getY()];
    }
    
    ////////////////////
    
    static int[][] comp = new int[50][50];
    
	static int comp(Unit U) {
		MapLocation M = mapLoc(U);
		return comp[M.getX()][M.getY()];
	}
	
	static void genComp(int X, int Y, int num) {
		if (!onBoard(X,Y) || comp[X][Y] != 0
				|| C.isPassableTerrainAt(new MapLocation(cPlanet,X,Y)) == 0) return;
		comp[X][Y] = num;
		for (int i = 1; i < 9; ++i) genComp(X+xdir[i],Y+ydir[i],num);
	}

    ////////////////////
	
    static int[][] lastSense = new int[50][50];
    static int[][] closeLastSense = new int[50][50];

    static void genCloseLastSense() {
    		LinkedList<Integer> L = new LinkedList<>();
    		for (int i = 0; i < C.getWidth(); ++i)
    			for (int j = 0; j < C.getHeight(); ++j)
    				if (valid(i,j)) {
    					if (lastSense[i][j] < gc.round()-10) {
    						closeLastSense[i][j] = hsh(i,j);
    						L.add(hsh(i,j));
    					} else closeLastSense[i][j] = -1;
    				} else closeLastSense[i][j] = -2;
            
    		while (!L.isEmpty()) {
    			int t = (int)L.poll();
    			int x = t/50, y = t%50;
    			for (int i = 1; i < 9; ++i) {
    				int X = x+xdir[i], Y = y+ydir[i];
    				if (valid(X,Y) && closeLastSense[X][Y] == -1) {
    					closeLastSense[X][Y] = closeLastSense[x][y];
    					L.add(hsh(X,Y));
    				}
    			}
    		}
    }
    
    static ArrayList<MapLocation> cFac = new ArrayList<>(), oFac = new ArrayList<>();
    
    static void genOpposingFac() { // store / update opponent's factories
		ArrayList<MapLocation> A = oFac; oFac.clear();
		for (MapLocation M: A) if (lastSense[M.getX()][M.getY()] != gc.round()) oFac.add(M);
		for (int i = 0; i < units.size(); ++i) 
			if (units.get(i).team() == oteam && Structure.isStructure(units.get(i)))
				oFac.add(mapLoc(units.get(i)));
}
    
    static Unit[][] tmp = new Unit[50][50];
    static Unit[][] closeEnemyGround = new Unit[50][50];

    static void genCloseEnemyGround() {
		LinkedList<Integer> L = new LinkedList<>();
		
		for (int i = 0; i < C.getWidth(); ++i)
			for (int j = 0; j < C.getHeight(); ++j)
				if (tmp[i][j] != null && tmp[i][j].team() == oteam) {
					closeEnemyGround[i][j] = tmp[i][j];
					L.add(hsh(i,j));
				} else closeEnemyGround[i][j] = null;
		
		while (!L.isEmpty()) {
			int t = (int)L.poll();
			int x = t/50, y = t%50;
			for (int i = 1; i < 9; ++i) {
				int X = x+xdir[i], Y = y+ydir[i];
				if (valid(X,Y) && closeEnemyGround[X][Y] == null) {
					closeEnemyGround[X][Y] = closeEnemyGround[x][y];
					L.add(hsh(X,Y));
				}
			}
		}
    }

    static Unit[][] closeEnemyEuclid = new Unit[50][50];
    
    static void genCloseEnemyEuclid() {
		LinkedList<Integer> L = new LinkedList<>();
		
		for (int i = 0; i < C.getWidth(); ++i)
			for (int j = 0; j < C.getHeight(); ++j)
				if (tmp[i][j] != null && tmp[i][j].team() == oteam) {
					closeEnemyEuclid[i][j] = tmp[i][j];
					L.add(hsh(i,j));
				} else closeEnemyEuclid[i][j] = null;
		
		while (!L.isEmpty()) {
			int t = (int)L.poll();
			int x = t/50, y = t%50;
			for (int i = 1; i < 9; ++i) {
				int X = x+xdir[i], Y = y+ydir[i];
				if (onBoard(X,Y) && closeEnemyEuclid[X][Y] == null) {
					closeEnemyEuclid[X][Y] = closeEnemyEuclid[x][y];
					L.add(hsh(X,Y));
				}
			}
		}
    }

    static int absDist(Unit U, Unit u) {
    		MapLocation A = mapLoc(U);
    		MapLocation B = mapLoc(u);
    		return Math.max(Math.abs(A.getX()-B.getX()), Math.abs(A.getY()-B.getY()));
    }
    static boolean existsEnemy7(Unit U) {
    		Unit u = get(U,closeEnemyEuclid);
    		if (u != null && absDist(U,u) <= 7) return true;
    		return false;
    }
    
    static Unit[][] closeFriendGround = new Unit[50][50];
    
    static void genCloseFriendGround() {
		LinkedList<Integer> L = new LinkedList<>();
		
		for (int i = 0; i < C.getWidth(); ++i)
			for (int j = 0; j < C.getHeight(); ++j)
				if (tmp[i][j] != null && tmp[i][j].team() == cteam) {
					closeFriendGround[i][j] = tmp[i][j];
					L.add(hsh(i,j));
				} else closeFriendGround[i][j] = null;
		
		while (!L.isEmpty()) {
			int t = (int)L.poll();
			int x = t/50, y = t%50;
			for (int i = 1; i < 9; ++i) {
				int X = x+xdir[i], Y = y+ydir[i];
				if (valid(X,Y) && closeFriendGround[X][Y] == null) {
					closeFriendGround[X][Y] = closeFriendGround[x][y];
					L.add(hsh(X,Y));
				}
			}
		}
    }

    static Unit[][] closeRocket = new Unit[50][50];
    
    static boolean yourRocket(Unit U) {
    		if (U == null) return false;
    		return U.unitType() == UnitType.Rocket && U.team() == cteam && U.structureIsBuilt() == 1;
    }
    
    static void genCloseRocket() {
    		LinkedList<Integer> L = new LinkedList<>();
		
		for (int i = 0; i < C.getWidth(); ++i)
			for (int j = 0; j < C.getHeight(); ++j)
				if (yourRocket(tmp[i][j])) {
					closeRocket[i][j] = tmp[i][j];
					L.add(hsh(i,j));
				} else closeRocket[i][j] = null;
		
		while (!L.isEmpty()) {
			int t = (int)L.poll();
			int x = t/50, y = t%50;
			for (int i = 1; i < 9; ++i) {
				int X = x+xdir[i], Y = y+ydir[i];
				if (valid(X,Y) && closeRocket[X][Y] == null) {
					closeRocket[X][Y] = closeRocket[x][y];
					L.add(hsh(X,Y));
				}
			}
		}
    }
    
    static Unit[][] closeDamageStructure = new Unit[50][50];
    
    static boolean yourDamageStructure(Unit U) {
		if (U == null) return false;
		return Structure.isStructure(U) && U.team() == cteam && U.health() < U.maxHealth() && U.structureIsBuilt() == 1;
    }
    static boolean yourUnbuiltStructure(Unit U) {
		if (U == null) return false;
		return Structure.isStructure(U) && U.team() == cteam && U.structureIsBuilt() == 0;
    }
    
    static void genCloseDamageStructure() {
		LinkedList<Integer> L = new LinkedList<>();

		for (int i = 0; i < C.getWidth(); ++i)
			for (int j = 0; j < C.getHeight(); ++j)
				closeDamageStructure[i][j] = null;

		for (int i = 0; i < C.getWidth(); ++i)
			for (int j = 0; j < C.getHeight(); ++j)
				if (yourUnbuiltStructure(tmp[i][j])) {
					closeDamageStructure[i][j] = tmp[i][j];
					L.add(hsh(i,j));
				}
		
		for (int i = 0; i < C.getWidth(); ++i)
			for (int j = 0; j < C.getHeight(); ++j)
				if (yourDamageStructure(tmp[i][j])) {
					closeDamageStructure[i][j] = tmp[i][j];
					L.add(hsh(i,j));
				} 
		
		while (!L.isEmpty()) {
			int t = (int)L.poll();
			int x = t/50, y = t%50;
			for (int i = 1; i < 9; ++i) {
				int X = x+xdir[i], Y = y+ydir[i];
				if (valid(X,Y) && closeDamageStructure[X][Y] == null) {
					closeDamageStructure[X][Y] = closeDamageStructure[x][y];
					L.add(hsh(X,Y));
				}
			}
		}
	}
    
    static Unit get(Unit U, Unit[][] arr) {
    		MapLocation cloc = mapLoc(U);
    		Unit u = arr[cloc.getX()][cloc.getY()];
    		return u;
    }
    
    static VecUnit units;
    static ArrayList<Unit> UNITS = new ArrayList<>();
    static MapLocation nextDestination;
    static Team cteam, oteam;
    static Planet cPlanet, oPlanet;
    static PlanetMap C, O;
    static Map<Integer,Integer> R = new HashMap<>(), wait = new HashMap<>();
    // 0 = follow workers
    // 1 = go to enemy base
    // 2 = retreat to base
    
    static void gen() {
        genOpposingFac();
        genCloseLastSense();
        genCloseEnemyGround();
        genCloseFriendGround();
        genCloseRocket();
        genCloseDamageStructure();
    }
    
    static boolean onBoard(int x, int y) {
        if (x < 0 || x >= C.getWidth() || y < 0 || y >= C.getHeight()) return false;
        return true;
    }

    static boolean valid(int X, int Y) { // generate passable stuff
        return onBoard(X,Y) && comp[X][Y] != 0; 
    }
    
	static boolean good(MapLocation M) {
		int t = M.getX()+M.getY();
		if (t % 2 == 0) return true;
		return false;
	}
    
    static boolean valid(MapLocation M) {
    		return valid(M.getX(),M.getY());
    }
    
    static MapLocation mapLoc(Unit U) { // convert unit to mapLoc
    		if (U == null) return null;
		Location L = U.location();
	    if (!L.isOnMap()) return null;
	    return L.mapLocation();
	}

    static int hsh(int a, int b) {
    		return 50*a+b;
    }
    
    static ArrayList<Unit> con(VecUnit V) {
		ArrayList<Unit> A = new ArrayList<>();
		for (int i = 0; i < V.size(); ++i) A.add(V.get(i));
		return A;
    }
    
    static boolean isAdj(MapLocation A, MapLocation B) {
		// check if two locations are exactly one square apart
	    if (!valid(A) || !valid(B)) return false;
	    if (A.distanceSquaredTo(B) == 1) return true;
	    return false;
	}
    
    static boolean isAdj2(MapLocation A, MapLocation B) {
    		// same as above but includes diagonals
	    	if (!valid(A) || !valid(B)) return false;
		if (A.distanceSquaredTo(B) <= 2) return true;
		return false;
	}
    
    static boolean isAttacker(Unit U) {
    		if (U == null) return false;
    		if (U.unitType() == UnitType.Ranger) return true;
    		if (U.unitType() == UnitType.Knight) return true;
    		if (U.unitType() == UnitType.Mage) return true;
    		return false;
    }
}
