import bc.*;
import java.util.*;

public class botHealer extends Movable {
	static Unit healPriority(Unit U) {
		VecUnit nearby = gc.senseNearbyUnitsByTeam(mapLoc(U),100,cteam);
		ArrayList<Unit> A = new ArrayList<>();
		
		for (int i = 0; i < nearby.size(); i++) 
			if (nearby.get(i).maxHealth() - nearby.get(i).health() > 0)
				A.add(nearby.get(i));
		
		Collections.sort(A,new HealthComparator());
		for (int i = 0; i < A.size(); ++i) if (mapLoc(U).distanceSquaredTo(mapLoc(A.get(i))) <= 30) return A.get(i);
		return getClosest(U,A);
	}
	
	static void heal(Unit U, Unit u) { // heals 
		if (u == null) return;
		MapLocation cloc = mapLoc(u);
		if (gc.canHeal(U.id(),u.id()) && gc.isHealReady(U.id())) {
	        gc.heal(U.id(), u.id());
	        if (gc.hasUnitAtLocation(cloc)) tmp[cloc.getX()][cloc.getY()] = gc.senseUnitAtLocation(cloc);
	        else tmp[cloc.getX()][cloc.getY()] = null;
		}
	}
	
	static MapLocation closeUnseen(Unit U) {
		MapLocation cloc = mapLoc(U);
    		int t = closeLastSense[cloc.getX()][cloc.getY()];
    		if (t == -1) return null;
    		int x = t/50, y = t%50;
    		
    		return new MapLocation(cPlanet,x,y);
    }
	
	static void position(Unit U, Unit u) { // make U out of range of u
    		if (mapLoc(U).distanceSquaredTo(mapLoc(u)) <= 50) {
    			tryMoveAway(U,mapLoc(u));
    			return;
    		}
        
        tryMove(U,mapLoc(u));
    }

	static Unit closeAttackerFriend(Unit U) {
		MapLocation cloc = mapLoc(U);
		Unit bes = null;
		int r = (int)Math.sqrt(70); 
		for (int i = -r; i <= r; ++i) // gen
			for (int j = -r; j <= r; ++j) if (i*i+j*j <= 50) {
	    			int X = cloc.getX()+i, Y = cloc.getY()+j;
	    			if (onBoard(X,Y) && tmp[X][Y] != null && tmp[X][Y].team() == cteam) {
	    				if (isAttacker(tmp[X][Y]) && !tmp[X][Y].location().isInGarrison()) {
	    					if (bes == null) bes = tmp[X][Y];
	    					else if (tmp[X][Y].health() < bes.health()) bes = tmp[X][Y];
	    				}
	    			}
    		}
		return bes;
	}
	
	static boolean findTeammate(Unit U) {
        Unit u = closeAttackerFriend(U);
        if (u == null) return false;
        
        int d = getDistGround(mapLoc(U),mapLoc(u));
        	if (d > 3 || (d > 1 && Math.random() < 0.5)) {
        		tryMove(U, mapLoc(u));
        		Unit u1 = firstPriority(U);
        		heal(U, u1);
        		return true;
        	} 
        	
        	return false;
    }
	
    static void run(Unit U) {
		structRocket.runRocket(U);
        Unit u = firstPriority(U); 
        Unit h = healPriority(U);
        if (u != null && mapLoc(U).distanceSquaredTo(mapLoc(u)) > 144) u = null;
		
        if (u == null) {
	        	if (!gc.isMoveReady(U.id())) return;
	        	if (findTeammate(U)) return;
        		switch(killMode) {
	        		case 1:	
	        			MapLocation M = close(U,UnitType.Factory,oteam);
	        			if (M != null) {
	        				tryMove(U,M); 
		        			break;
	        			}
	        		case 0:
	        			tryMove(U,closeUnseen(U));
	                	break;
	        		case 2:
	        			tryMove(U,close(U,UnitType.Factory,cteam));
        		}
        } else {
            position(U,u); heal(U,h);
        }
    }

	/*static Unit farthestFromBase() { //find furthest worker/healer from base
		VecUnit units = gc.myUnits();
		long hi = 0; int ind = -1;
		for(int i = 0; i < units.size(); i++) {
			if(units.get(i).unitType() == UnitType.Healer || units.get(i).unitType() == UnitType.Worker) {
				MapLocation fac = close(units.get(i),UnitType.Factory,cteam);
				long dist = mapLoc(units.get(i)).distanceSquaredTo(fac);
				if(dist > hi) {
					hi = dist;
					ind = i;
				}
			}
		}
		if(ind == -1) return null;
		return units.get(ind);
	}*/
}