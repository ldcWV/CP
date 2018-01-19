import bc.*;
import java.util.*;

public class Movable extends Player {
	static Unit getPri (Unit U) { // sense closest with lowest health
		MapLocation cloc = mapLoc(U);
		Unit bes1 = null, bes2 = null;
		int r = (int)Math.sqrt(70); 
		if (U.unitType() == UnitType.Ranger) {
			for (int i = -r; i <= r; ++i) // gen
		    		for (int j = -r; j <= r; ++j) if (i*i+j*j >= 10 && i*i+j*j <= 50) {
		    			int X = cloc.getX()+i, Y = cloc.getY()+j;
		    			if (onBoard(X,Y) && tmp[X][Y] != null && tmp[X][Y].team() == oteam) {
		    				if (isAttacker(tmp[X][Y])) {
		    					if (bes1 == null) bes1 = tmp[X][Y];
		    					else if (tmp[X][Y].health() < bes1.health()) bes1 = tmp[X][Y];
		    				} else {
		    					if (bes2 == null) bes2 = tmp[X][Y];
		    					else if (tmp[X][Y].health() < bes2.health()) bes2 = tmp[X][Y];
		    				}
		    			}
		    		}
		} else if (U.unitType() == UnitType.Knight) {
			for (int i = 1; i < 9; i += 2) {
    				int X = cloc.getX()+xdir[i], Y = cloc.getY()+ydir[i];
	    			if (onBoard(X,Y) && tmp[X][Y] != null && tmp[X][Y].team() == oteam) {
	    				if (isAttacker(tmp[X][Y])) {
	    					if (bes1 == null) bes1 = tmp[X][Y];
	    					else if (tmp[X][Y].health() < bes1.health()) bes1 = tmp[X][Y];
	    				} else {
	    					if (bes2 == null) bes2 = tmp[X][Y];
	    					else if (tmp[X][Y].health() < bes2.health()) bes2 = tmp[X][Y];
	    				}
	    			}
			}
		} else {
			for (int i = -r; i <= r; ++i) // gen
		    		for (int j = -r; j <= r; ++j) if (i*i+j*j <= 50) {
		    			int X = cloc.getX()+i, Y = cloc.getY()+j;
		    			if (onBoard(X,Y) && tmp[X][Y] != null && tmp[X][Y].team() == oteam) {
		    				if (isAttacker(tmp[X][Y])) {
		    					if (bes1 == null) bes1 = tmp[X][Y];
		    					else if (tmp[X][Y].health() < bes1.health()) bes1 = tmp[X][Y];
		    				} else {
		    					if (bes2 == null) bes2 = tmp[X][Y];
		    					else if (tmp[X][Y].health() < bes2.health()) bes2 = tmp[X][Y];
		    				}
		    			}
		    		}
		}
		if (bes1 != null) return bes1;
		return bes2;
	}

    static Unit firstPriority(Unit U) {
    		Unit u = getPri(U);
        if (u != null) return u;
        return get(U,closeEnemyGround);
    }

    static boolean canMove(Unit U, Direction D) {
    		if (!valid(mapLoc(U).add(D))) return false;
    		return gc.canMove(U.id(),D);
    }
    
    static boolean moveRandom(Unit U) {
        if (!gc.isMoveReady(U.id())) return false;

        List<Integer> dirs = new ArrayList<>();
        for (int i = 1; i < 9; ++i) dirs.add(i);
        Collections.shuffle(dirs);

        int des = -1;
        for (int i = 0; i < 8; ++i) {
        		int x = dirs.get(i);
	        if (canMove(U,directions[x])) {
	            if (good(mapLoc(U).add(directions[x]))) {
	            		gc.moveRobot(U.id(),directions[x]);
		            return true;
	            } else des = x;
	        }
        }

        if (des != -1) {
    			gc.moveRobot(U.id(),directions[des]);
    			return true;
        }
        return false;
    }

    static MapLocation closerLocation(Unit U, MapLocation M) {
    		int bes = INF;
    		MapLocation BES = null;
    		
    		for (int i = -7; i <= 7; i++)
    			for (int j = -7; j <= 7; j++) if (i*i+j*j <= 50) {
    				MapLocation t = new MapLocation(cPlanet,M.getX()+i,M.getY()+j);
    				if (!valid(t)) continue;
    				if (i*i+j*j < bes && getDistGround(t,M) < INF) {
    					bes = i*i+j*j;
    					BES = t;
    				}
    			}
    		return BES;
    }
    
    static Unit closeFactoryThatNeedsRepair(Unit U) {
        VecUnit near = gc.senseNearbyUnitsByType(mapLoc(U), 30, UnitType.Factory);
        Unit ans = null;
        long minDist = INF;
        for(int i = 0; i < near.size(); i++) {
        		if(near.get(i).health() < 300 && mapLoc(near.get(i)).distanceSquaredTo(mapLoc(U)) < minDist) {
        			minDist = mapLoc(near.get(i)).distanceSquaredTo(mapLoc(U));
        			ans = near.get(i);
        		}
        }
        return ans;
    }
    
    static boolean tryMove(Unit U, MapLocation M) {
        if (!gc.isMoveReady(U.id())) return false;
        if (M == null) { moveRandom(U); return true; }
        if (getDistGround(mapLoc(U),M) == INF) M = closerLocation(U,M);
        if (M == null) { moveRandom(U); return true; }
        
        MapLocation cloc = mapLoc(U);
        List<Integer> dirs = new ArrayList<>();
        for (int i = 0; i < 9; ++i) dirs.add(i);
        Collections.shuffle(dirs);
        
        int des = -1;
        for (int i = 0; i < 9; ++i) {
            int t = dirs.get(i);
            int ok = nextStep(cloc.getX(),cloc.getY(),M.getX(),M.getY(),t);
            if (ok == 2 && canMove(U,directions[t])) {
                if (good(cloc.add(directions[t]))) {
                		gc.moveRobot(U.id(), directions[t]);
                		return true;
                } else des = t;
            }
        }

        if (des != -1) {
    			gc.moveRobot(U.id(),directions[des]);
    			return true;
        }
        
        for (int i = 0; i < 9; ++i) {
            int t = dirs.get(i);
            int ok = nextStep(cloc.getX(),cloc.getY(),M.getX(),M.getY(),t);
            if (ok == 1 && canMove(U,directions[t])) {
                if (good(cloc.add(directions[t]))) {
                		gc.moveRobot(U.id(), directions[t]);
                		return true;
                } else des = t;
            }
        }

        if (des != -1) {
    			gc.moveRobot(U.id(),directions[des]);
    			return true;
        }
        
        return false;
    }

    static void retreat(Unit U) { // go to closest factory
        if (U.location().isInGarrison()) return;
        MapLocation M = close(U,UnitType.Factory,cteam);
        if (M != null) {
        		if (mapLoc(U).distanceSquaredTo(M) > 50) tryMove(U,M);
        		else moveRandom(U);
        } else {
            Unit u = firstPriority(U);
        		if (u == null) moveRandom(U);
        		else tryMoveAway(U,mapLoc(U));
        }
    }

    static MapLocation closeUnvisited(MapLocation M) {
        int x = -1, y = -1, dist = INF;
        for (int i = -10; i <= 10; ++i)
            for (int j = -10; j <= 10; ++j) if (i*i+j*j <= 100) {
            		int X = M.getX()+i;
            		int Y = M.getX()+j;
                if (i*i+j*j < dist && valid(X,Y) 
                		&& !visit[X][Y] 
                		&& tmp[X][Y] == null) {
                    x = X; y = Y;
                    dist = i*i+j*j;
                }
            }
        if (x != -1) return new MapLocation(cPlanet,x,y);
        return null;
    }

    static boolean isAttacker(Unit U) {
        if (U == null) return false;
        switch (U.unitType()) {
            case Rocket:
            case Factory:
            case Healer:
            case Worker:
                return false;
            default:
                return true;
        }
    }

    static MapLocation close(Unit U, UnitType unitType, Team te) {
    		if (unitType != UnitType.Factory) {
	        VecUnit V = gc.senseNearbyUnitsByType(mapLoc(U),INF,unitType);
	        ArrayList<Unit> v = new ArrayList<>();
	        for (int i = 0; i < V.size(); ++i) 
	            if (V.get(i).team() == te) 
	                v.add(V.get(i));
	                
	        Unit u = getClosest(U,v);
	        if (u == null) return null;
	        return mapLoc(u);
    		} else {
    	        MapLocation u;
    	        if (te == cteam) u = getClosest2(U,cFac);
    	        else u = getClosest2(U,oFac);
    	        
    	        if (u == null) return null;
    	        return u;
    		}
    }

    ///////////////////////////////////////////////////////////////// HELPER NAVIGATION

    static int nextStep(int x1, int y1, int x2, int y2, int dir) {
        if (x1 == x2 && y1 == y2) return 0;
        genDist(x2,y2);
        if (distGround[x2][y2][x1][y1] == INF) return 0;

        int X1 = x1+xdir[dir], Y1 = y1+ydir[dir];
        if (onBoard(X1,Y1) && distGround[x2][y2][X1][Y1]+1 == distGround[x2][y2][x1][y1]) return 2;
        if (onBoard(X1,Y1) && distGround[x2][y2][X1][Y1] == distGround[x2][y2][x1][y1]) return 1;
        return 0;
    }

    
    static boolean tryMoveAwayNaive(Unit U, MapLocation M) {
		if (!gc.isMoveReady(U.id())) return false;
        MapLocation cloc = mapLoc(U);
        List<Integer> dirs = new ArrayList<>();
        for (int i = 0; i < 9; ++i) dirs.add(i);
        Collections.shuffle(dirs);
        
        int mn = (int)cloc.distanceSquaredTo(M);
        Direction bes = null;
        
        for (int i = 0; i < 9; ++i) {
            int t = dirs.get(i);
            MapLocation CLOC = cloc.add(directions[t]);
            if (valid(CLOC) && CLOC.distanceSquaredTo(M) > mn 
            		&& gc.canMove(U.id(), directions[t])) {
            		bes = directions[t];
            		mn = (int)CLOC.distanceSquaredTo(M);
            }
        }
        
        if (bes == null) return false;
    		gc.moveRobot(U.id(), bes);
    		return true;
    }
    
    static boolean tryMoveAway(Unit U, MapLocation M) {
    		if (!gc.isMoveReady(U.id())) return false;
        if (M == null) return moveRandom(U);
        if (getDistGround(mapLoc(U),M) == INF) return tryMoveAwayNaive(U,M);
 
        MapLocation cloc = mapLoc(U);
        List<Integer> dirs = new ArrayList<>();
        for (int i = 0; i < 9; ++i) dirs.add(i);
        Collections.shuffle(dirs);
        
        int des = -1;
        for (int i = 0; i < 9; ++i) {
            int t = dirs.get(i);
            int ok = nextStep(cloc.getX(),cloc.getY(),M.getX(),M.getY(),t);
            if (ok == 0 && canMove(U,directions[t])) {
                if (good(cloc.add(directions[t]))) {
                		gc.moveRobot(U.id(), directions[t]);
                		return true;
                } else des = t;
            }
        }

        if (des != -1) {
    			gc.moveRobot(U.id(),directions[des]);
    			return true;
        }
        
        for (int i = 0; i < 9; ++i) {
            int t = dirs.get(i);
            int ok = nextStep(cloc.getX(),cloc.getY(),M.getX(),M.getY(),t);
            if (ok == 1 && canMove(U,directions[t])) {
                if (good(cloc.add(directions[t]))) {
                		gc.moveRobot(U.id(), directions[t]);
                		return true;
                } else des = t;
            }
        }

        if (des != -1) {
    			gc.moveRobot(U.id(),directions[des]);
    			return true;
        }
        
        return false;
    }
    
}
