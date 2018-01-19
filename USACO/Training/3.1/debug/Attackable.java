import bc.*;

public class Attackable extends Movable {
    static void position(Unit U, Unit u) { // make U in best position to attack unit at M
        if (gc.canAttack(U.id(), u.id())) {
	        	attack(U, u);
	        	tryMoveAway(U,mapLoc(u));
        }
    		if (U.unitType() == UnitType.Ranger && isBad(u)
    			&& mapLoc(U).distanceSquaredTo(mapLoc(u)) <= 30) {
    			tryMoveAway(U,mapLoc(u));
    			return;
    		}
    		
        if (U.unitType() == UnitType.Knight && mapLoc(U).distanceSquaredTo(mapLoc(u)) == 2) {
            for (int i = 1; i < 9; ++i) {
                MapLocation U1 = mapLoc(U).add(directions[i]);
                if (isAdj(U1,mapLoc(u))) tryMove(U,U1);
            }
            return;
        }
        
        tryMove(U,mapLoc(u));
    }

    static boolean isBad(Unit u) {
    		if (u.unitType() == UnitType.Knight 
    			|| u.unitType() == UnitType.Mage) return true;
    		return false;
    }
    
    static void attack(Unit U, Unit u) { // attacks 
    		if (u == null) return;
    		MapLocation cloc = mapLoc(u);
    		if (gc.canAttack(U.id(),u.id()) && gc.isAttackReady(U.id())) {
            gc.attack(U.id(), u.id());
            if (gc.hasUnitAtLocation(cloc)) tmp[cloc.getX()][cloc.getY()] = gc.senseUnitAtLocation(cloc);
            else tmp[cloc.getX()][cloc.getY()] = null;
    		}
    }
    
    static boolean disintegrate(Unit U) {
    		int c = comp(U);
    		if (sz[c] == cNum[c]) {
    			gc.disintegrateUnit(U.id());
    			return true;
    		}
    		return false;
    }
    
    static MapLocation closeUnseen(Unit U) {
		MapLocation cloc = mapLoc(U);
    		int t = closeLastSense[cloc.getX()][cloc.getY()];
    		if (t == -1) return null;
    		int x = t/50, y = t%50;
    		
    		return new MapLocation(cPlanet,x,y);
    }
    
    static boolean findTeammate(Unit U) {
        Unit u = get(U,closeFriendGround);
        if (u == null) return false;
        
        int d = getDistGround(mapLoc(U),mapLoc(u));
        	if (d > 3 || (d > 1 && Math.random() < 0.433)) {
        		tryMove(U, mapLoc(u));
        		Unit u1 = firstPriority(U);
        		attack(U, u1);
        		return true;
        	} 
        	
        	return false;
    }
        	
    static void decide(Unit U) {
    		if (!gc.isMoveReady(U.id())) return;
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
    }
    
    static void attack(Unit U) {
    		if (disintegrate(U)) return;
		structRocket.runRocket(U);
        Unit u = firstPriority(U); 
        if (u == null) { decide(U); 	return; }
        
        int d = (int)mapLoc(U).distanceSquaredTo(mapLoc(u));
        if (d > 81 && findTeammate(U)) {
    			u = firstPriority(U); 
        		d = (int)mapLoc(U).distanceSquaredTo(mapLoc(u));
        }
        
        if (d > 144) u = null;
        if (u == null) { decide(U); return; }
        position(U,u); attack(U,u);
    }
}
