// latest: https://www.battlecode.org/#/materials/releases
// specs: https://s3.amazonaws.com/battlecode-2018/specs/battlecode-specs-2018.html
// javadocs: https://s3.amazonaws.com/battlecode-2018/api/java/index.html
// COMMON ERROR: if unit is in garrison it can't do anything ...

import bc.*;
import java.util.*;

public class Player extends Globals {
	static void initialize() { // initialize teams, variables, etc
        gc = new GameController();

        if (gc.team() == Team.Red) {
            cteam = Team.Red; oteam = Team.Blue;
        } else {
            cteam = Team.Blue; oteam = Team.Red;
        }

        if (gc.planet() == Planet.Earth) {
            cPlanet = Planet.Earth; oPlanet = Planet.Mars;
        } else {
        		cPlanet = Planet.Mars; oPlanet = Planet.Earth; 
        }
        
        C = gc.startingMap(cPlanet); O = gc.startingMap(oPlanet);
        
        for (int X = 0; X < C.getWidth(); ++X)
            for (int Y = 0; Y < C.getHeight(); ++Y) {
            		MapLocation cloc = new MapLocation(cPlanet,X,Y);
                if (C.initialKarboniteAt(cloc) <= 1) visit[X][Y] = true;
            }

        for (int X = 0; X < C.getWidth(); ++X)
            for (int Y = 0; Y < C.getHeight(); ++Y) 
            		genComp(X,Y,50*X+Y+1);
        
        VecUnit V = gc.myUnits();
        for (int i = 0; i < V.size(); ++i) {
        		MapLocation cloc = mapLoc(V.get(i));
        		ok[comp[cloc.getX()][cloc.getY()]] = true;
        }
        
        for (int X = 0; X < C.getWidth(); ++X)
            for (int Y = 0; Y < C.getHeight(); ++Y) 
            		sz[comp[X][Y]] ++;
        
        for (int i = 1; i <= 2500; ++i) {
        		minFac[i] = (int)Math.ceil(Math.pow(sz[i],2.0/3)/20);
            minWork[i] = 4*minFac[i];
        }
    }

	static boolean bad(Unit U) { // on same team and can act
		if (U.team() == oteam) return true;
		if (!U.location().isOnMap() || U.location().isInGarrison()) return true;
		return false;
	}
	
    static void initializeEarth() { 	// research ranger!
        gc.queueResearch(UnitType.Worker);
        gc.queueResearch(UnitType.Ranger);
        gc.queueResearch(UnitType.Healer);
        gc.queueResearch(UnitType.Ranger);
        gc.queueResearch(UnitType.Rocket);
        gc.queueResearch(UnitType.Worker);
        gc.queueResearch(UnitType.Worker);
        gc.queueResearch(UnitType.Rocket);
        gc.queueResearch(UnitType.Rocket);
        
        structRocket.genVal();
		nextDestination = structRocket.chooseDestination();
    }
    
    public static void main(String[] args) { // runs program
        initialize();
        if (cPlanet == Planet.Earth) initializeEarth();
        while (true) turn();
    }

    
    static void propagate(Unit U) { // update isSense
    		MapLocation cloc = mapLoc(U);
    		int r = (int)Math.sqrt(U.visionRange());
    		for (int i = -r; i <= r; ++i) {
        		for (int j = -r; j <= r; ++j) if (i*i+j*j <= U.visionRange()) {
	    			int X = cloc.getX()+i, Y = cloc.getY()+j;
	    			if (onBoard(X,Y)) {
	    				lastSense[X][Y] = (int)gc.round();		    			
	    				if (tmp[X][Y] != null && tmp[X][Y].team() == oteam 
		    				&& getDistGround(cloc, new MapLocation(cPlanet,X,Y)) != INF)		    				
	    					lastSeen = (int)gc.round();

	    			}
        		}
    		}
    }
    
    static void testStuck() {
        for (int i = 0; i < units.size(); i++) {
        		Unit unit = units.get(i);
    			if (unit.team() == cteam) propagate(unit);
        }
    }
    
    static void clear() {
		for (int i = 0; i < 50; ++i)
			for (int j = 0; j < 50; ++j) 
				tmp[i][j] = null;

		for (int i = 1; i <= 2500; ++i) work[i] = fac[i] = cNum[i] = 0;
        rocket = numFriendly = attack = 0; cFac.clear();
        worker = 0;
        
        startTime = System.nanoTime();
    }
    
    static void processTime() {
		long cTime = System.nanoTime() - startTime;
		mxTime = Math.max(mxTime, cTime);
		totTime += Math.max(0, cTime-50000000);

        // System.out.println(System.nanoTime() - startTime);
		// System.out.println("Additional time used: "+(double)totTime/1000000000);
    }
    
    static void testAlarm() {
        for (int i = 0; i < units.size(); i++) {
        		Unit unit = units.get(i);
    			if (unit.team() == cteam && unit.unitType() == UnitType.Factory) 
    				structFactory.testAlarm(unit);
        }
    }
    
    static void printInfo() {
		System.out.println("Current round: "+gc.round());
		System.out.println("Karbonite: "+gc.karbonite());
		System.out.println("Time: "+(double)gc.getTimeLeftMs()/1000);
		System.out.println("Units: "+numFriendly);
		System.out.println("WP "+getWorkerProfit((int)gc.round()-30,(int)gc.round()));
		System.out.println("KM "+killMode);
		System.out.println();
    }
    
    static void turn() { // turn by turn
    		if (gc.getTimeLeftMs() < 1000) {
    			gc.nextTurn();
    			return;
    		}
		units = gc.senseNearbyUnits(new MapLocation(cPlanet,0,0),INF);
    		clear();
    		
    		if (units.size() == 0) {
    			gc.writeTeamArray(0, 1);
    			gc.nextTurn();
    			return;
    		}

        if (gc.round() % 100 >= 50 || gc.round() <= 100) killMode = 0;
        else killMode = 1;
        
        for (int i = 0; i < units.size(); i++) {
            Unit unit = units.get(i);
        		if (units.get(i).team() == cteam) {
        			numFriendly ++;
        			cNum[comp(unit)] ++;
	            if (unit.unitType() == UnitType.Worker) {
	            		work[comp(unit)] ++;
	            		worker ++;
	            } else if (unit.unitType() == UnitType.Factory) {
	                fac[comp(unit)] ++;
	                cFac.add(mapLoc(unit));
	            } else if (unit.unitType() == UnitType.Rocket) {
	            		rocket ++;
		            cFac.add(mapLoc(unit));
	            } else {
	            		attack ++;
	            }
	        }
        		MapLocation cloc = mapLoc(unit);
        		tmp[cloc.getX()][cloc.getY()] = unit;
        }
        
        printInfo();
        testStuck();
        testAlarm();
        gen();
        
        UNITS.clear();
        for (int i = 0; i < units.size(); i++) if (units.get(i).team() == cteam) UNITS.add(units.get(i));
        Collections.sort(UNITS, new UnitComparator());
        
        int num = 0, MXUNITS = 6*gc.getTimeLeftMs()/1000+20;
        for (int i = 0; i < UNITS.size(); i++) {
	    		if (processUnit(UNITS.get(i))) num ++;
	    		if (num == MXUNITS) {
	    			System.out.println("OOPS");
	    			break;
	    		}
        }
        
        processTime();
		gc.nextTurn();
    }

    static int dist(Unit a, Unit b) { // distance between two units
    		if (a == null || b == null) return INF;
        return (int)mapLoc(a).distanceSquaredTo(mapLoc(b));
    }

    static Unit getClosest(Unit U, ArrayList<Unit> V) { // closest unit in V to U (Euclidean)
        int ind = -1, dist = INF;
        for (int i = 0; i < V.size(); ++i) {
            if (mapLoc(U).distanceSquaredTo(mapLoc(V.get(i))) < dist) {
                ind = i;
                dist = (int)mapLoc(U).distanceSquaredTo(mapLoc(V.get(i)));
            }
        }
        if (ind == -1) return null;
        return V.get(ind);
    }

    static MapLocation getClosest2(Unit U, ArrayList<MapLocation> V) { // same as above
        int ind = -1, dist = INF;
        for (int i = 0; i < V.size(); ++i) {
            if (mapLoc(U).distanceSquaredTo(V.get(i)) < dist) {
                ind = i;
                dist = (int)mapLoc(U).distanceSquaredTo(V.get(i));
            }
        }
        if (ind == -1) return null;
        return V.get(ind);
    }

    static boolean processUnit(Unit U) { // run a unit
    		if (bad(U)) return false;
        switch (U.unitType()) {
            case Factory:
                structFactory.run(U);
                break;
            case Healer:
                botHealer.run(U);
                break;
            case Knight:
                botKnight.run(U);
                break;
            case Mage:
                botMage.run(U);
                break;
            case Ranger: 
                botRanger.run(U);
                break;
            case Rocket:
                structRocket.run(U);
                break;
            case Worker:
                botWorker.run(U);
                break;
        }
        return true;
    }
}