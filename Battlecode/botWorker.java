import java.util.ArrayList;
import java.util.Collections;

import bc.*;

public class botWorker extends Movable {
	static Unit threat(Unit U) { //get most threatening unit
		MapLocation cloc = mapLoc(U);
		Unit bes = null;
		int r = (int)Math.sqrt(70); 
		for (int i = -r; i <= r; ++i) // gen
			for (int j = -r; j <= r; ++j) if (i*i+j*j <= 50) {
	    			int X = cloc.getX()+i, Y = cloc.getY()+j;
	    			if (onBoard(X,Y) && tmp[X][Y] != null && tmp[X][Y].team() == oteam) {
	    				if (isAttacker(tmp[X][Y])) {
	    					if (bes == null) bes = tmp[X][Y];
	    					else if (tmp[X][Y].health() < bes.health()) bes = tmp[X][Y];
	    				}
	    			}
    		}
		return bes;
	}
	
	static boolean spamTime() {
		if (cPlanet != Planet.Mars) return false;
		if (gc.round() > 750 || gc.getTeamArray(oPlanet).get(0) == 1) return true;
		return false;
	}

	static int needsWorker(Unit U) {		
		if (spamTime()) return 2;
		MapLocation cloc = mapLoc(U);
		int c = comp[cloc.getX()][cloc.getY()];
		int des = minWork[c];
		if (rocket > 0) des = (int)Math.ceil(1.2*des);
		if (getWorkerProfit((int)gc.round()-30,(int)gc.round()) < 0) des = (int)Math.ceil(des/3);
		if (work[c] < 2.0/3*des) return 2;
		if (work[c] < des) return 1;
		return 0;
	}
	
    static boolean repli(Unit U, Unit u) {
		int t = needsWorker(U); 
		if (t == 0) return false;
		
		int c = comp(U);
    		if (u != null && mapLoc(U).distanceSquaredTo(mapLoc(u)) > 81) u = null;
    		
    		ArrayList<Direction> shuff = new ArrayList<>();
    		shuff.add(Direction.East); // 1 indexing
    		for(int i = 0; i < 8; i++) shuff.add(directions[i]);
    		Collections.shuffle(shuff);
    		
    		if ((gc.round() <= 50 && t == 2) || u == null) {
    			for (int d = 1; d < 9; ++d) {
		        if (gc.canReplicate(U.id(),shuff.get(d))) {
		            gc.replicate(U.id(),shuff.get(d));
		            work[c] ++;
		            if(gc.hasUnitAtLocation(mapLoc(U).add(shuff.get(d))))
		            		UNITS.add(gc.senseUnitAtLocation(mapLoc(U).add(shuff.get(d))));
		            workerProfit[(int)gc.round()] -= 15;
		            System.out.println("Produced worker!");
		            return true;
		        }
    			}
    		}
	    return false;
    }

    static boolean harvest(Unit U) {
        for (int i = 0; i < 9; ++i) if (gc.canHarvest(U.id(), directions[i])) {
        		int initial = (int)gc.karbonite();
            gc.harvest(U.id(),directions[i]);
            workerProfit[(int)gc.round()] += (int)gc.karbonite() - initial;
            return true;
        }
        return false;
    }

    static boolean needHeal(Unit U) {
    		Unit u = get(U,closeDamageStructure);
        if (u == null || getDistGround(mapLoc(U),mapLoc(u)) > 3) return false;
        if (getDistGround(mapLoc(U),mapLoc(u)) > 1) tryMove(U,mapLoc(u));
        if (gc.canRepair(U.id(),u.id())) {
        		gc.repair(U.id(),u.id());
        		return true;
        }
        if (gc.canBuild(U.id(),u.id())) {
        		gc.build(U.id(),u.id());
        		return true;
        }
        return false;
    }

    static boolean make_structure(Unit U) {
    		if (cPlanet != Planet.Earth || gc.round() < 10) return false;
        structRocket.runRocket(U);
        if ((fac[comp(U)] < minFac[comp(U)]) && structFactory.startFac(U)) return true;
        if (structRocket.needsRocket() && structRocket.startRocket(U)) return true;
        return false;
    }

    static void run(Unit U) {
        Unit u = threat(U);
        repli(U, u);
        if (needHeal(U)) return;
        if (u != null && isAttacker(u) && mapLoc(U).distanceSquaredTo(mapLoc(u)) <= 64) retreat(U);

        if (make_structure(U)) return;
        if (harvest(U)) return;
        
        MapLocation cloc = mapLoc(U);
        if (gc.karboniteAt(cloc) == 0) {
            visit[cloc.getX()][cloc.getY()] = true;
            tryMove(U,closeUnvisited(mapLoc(U)));
        }
        
        if (make_structure(U)) return;
        harvest(U);
    }
}