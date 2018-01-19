import java.util.ArrayList;

import bc.*;

public class structRocket extends Structure {
	static boolean onBoardMars(int x, int y) {
		return x >= 0 && x < O.getWidth() && y >= 0 && y < O.getHeight();
	}
	
	static void genVal() { // generate value of each spot on mars
		for (int i = 0; i < O.getWidth(); ++i) 
			for (int j = 0; j < O.getHeight(); ++j) {
				int sum = 0;
				for (int x = i-2; x <= i+2; ++x) 
					for (int y = j-2; y <= j+2; ++y) if ((x != i || y != j) && onBoardMars(x,y)) {
						sum += O.initialKarboniteAt(new MapLocation(oPlanet,x,y));
					}
				marsVal[i][j] = sum;
			}
	}
	
	static boolean startRocket(Unit U) {
		if (gc.karbonite() < bc.bcUnitTypeBlueprintCost(UnitType.Rocket)) return false;
		if (existsEnemy7(U)) return false;
		for (int i = 0; i < 9; ++i) if (gc.canBlueprint(U.id(), UnitType.Rocket, directions[i])) {
			gc.blueprint(U.id(), UnitType.Rocket, directions[i]);
			rocket ++; totRocket ++;
			System.out.println("Produced rocket!");
			return true;
		}
		return false;
	}

	static void prep(Unit U) {
		System.out.println("Preparing "+U.id());
		R.put(U.id(),(int)gc.round());
	}

	static MapLocation randomDestination() {
		ArrayList<MapLocation> A = new ArrayList<>();
		for (int i = 0; i < O.getWidth(); ++i)
			for (int j = 0; j < O.getHeight(); ++j) {
				MapLocation cloc = new MapLocation(Planet.Mars,i,j);
				if (O.isPassableTerrainAt(cloc) == 1) A.add(cloc);
			}
		
		if (A.size() == 0) return null;
		return A.get(ran.nextInt(A.size()));
	}
	
	static MapLocation chooseDestination() {
		MapLocation bes = null;
		int bestSum = -INF;
		
		for (int i = 0; i < O.getWidth(); ++i)
			for (int j = 0; j < O.getHeight(); ++j) {
				if (O.isPassableTerrainAt(new MapLocation(Planet.Mars,i,j)) == 1 
					&& marsVal[i][j] > bestSum) {
					boolean bad = false;
					for (int I = i-2; I <= i+2; ++I) if (0 <= I && I < 50)
						for (int J = j-2; J <= j+2; ++J) if (0 <= J && J < 50)
							if (sentRocket[I][J] == true) {
								bad = true;
								break;
							}
					if (!bad) {
						bes = new MapLocation(Planet.Mars,i,j);
						bestSum = marsVal[i][j];
					}
				}
			}
		
		if (bes == null) bes = randomDestination();		
		if (bes != null) sentRocket[bes.getX()][bes.getY()] = true;
		return bes;
	}

	static boolean focusRocket() {
		return gc.round() >= 300 && lastSeen <= gc.round()-20;
	}

	static void runRocket(Unit U) {
		if (cPlanet == Planet.Mars) return;
		
		Unit u = get(U,closeRocket);
		if (u != null && getDistGround(mapLoc(U),mapLoc(u)) > 7) u = null;
			
		if (u == null) {			
			if (focusRocket() && U.unitType() != UnitType.Worker) Movable.retreat(U);
			return;
		}

		if (!R.containsKey(u.id()) && getNum(gc.unit(u.id()),U.unitType()) <= 5) {
			if (dist(U,u) > 2) Movable.tryMove(U,mapLoc(u));
			if (gc.canLoad(u.id(),U.id())) gc.load(u.id(),U.id());
		} else Movable.tryMoveAway(U,mapLoc(u));
	}

	static void launchRocket(Unit U) {
		R.remove(U.id()); wait.remove(U.id());
		MapLocation M = nextDestination;
		if (M == null) return;
		if (gc.canLaunchRocket(U.id(),M)) {
			System.out.println("Launching "+U.id());
			gc.launchRocket(U.id(), M);
			nextDestination = structRocket.chooseDestination();
		} 
	}

	static boolean shouldLaunch(Unit U) {
		if (U.structureGarrison().size() > 6) return true;
		if (U.structureGarrison().size() > 0 && wait.get(U.id())+20 < gc.round()) return true;
		return false;
	}
	
	static void run(Unit U) {
		if (wait.get(U.id()) == null) wait.put(U.id(),(int)gc.round());
		if (cPlanet == Planet.Earth) {
			if (R.get(U.id()) == null) {
				if (shouldLaunch(U)) prep(U);
			} else if (R.get(U.id()) <= gc.round()-5) {
				launchRocket(U);
			} 
		} else {
			unload(U);
		}
	}

	static boolean needsRocket() {
		if (nextDestination == null) return false;		
		if ((focusRocket() || gc.round() >= 600) && rocket < 4) return true;
		return totRocket < (gc.round()-450)/50+1;
	}
}