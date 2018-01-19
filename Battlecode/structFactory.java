import bc.*;

public class structFactory extends Structure {
	static void testAlarm(Unit U) {
		if (existsEnemy7(U)) killMode = 2;
	}
	
	static void tryAttacker(Unit U) {
		if (gc.canProduceRobot(U.id(),UnitType.Ranger)) {
			// gc.produceRobot(U.id(),UnitType.Ranger);
			// System.out.println("Produced ranger!");
			double r = (double)(gc.round());
			r /= 1500.0;
			if (Math.random() > r) { // for testing
				gc.produceRobot(U.id(),UnitType.Ranger);
				System.out.println("Produced ranger!");
			} else {
				gc.produceRobot(U.id(),UnitType.Healer);
				System.out.println("Produced healer!");
			}
		}
	}

	static void tryWorker(Unit U) {
		if (gc.canProduceRobot(U.id(),UnitType.Worker)) {
			gc.produceRobot(U.id(),UnitType.Worker);
			workerProfit[(int)gc.round()] -= 25;
			System.out.println("Factory produced worker!");
			work[comp(U)] ++;
		}
	}
	
	static void produce(Unit U) {
		int c = comp(U);
		Unit u = get(U,closeEnemyEuclid);
		
		if ((u != null && mapLoc(U).distanceSquaredTo(mapLoc(u)) <= 196) || attack < 1.5*minFac[c]) {
			tryAttacker(U);
		} else if (botWorker.needsWorker(U) > 0) { 
			tryWorker(U);
		} else {
			if ((fac[c] >= minFac[c] && work[c] >= minWork[c]) || gc.round() > 100) {
				if (structRocket.needsRocket())  {
					if (gc.karbonite() > 150) tryAttacker(U);
				} else tryAttacker(U);
			}
		}
	}
	
	static boolean existsFac(MapLocation M) {
		for (int i = 1; i < 8; i += 2) {
			int x = M.getX()+xdir[i], y = M.getY()+ydir[i];
			if (!onBoard(x,y)) continue;
			MapLocation cloc = new MapLocation(cPlanet,x,y);
			if (gc.hasUnitAtLocation(cloc)) {
				Unit U = gc.senseUnitAtLocation(cloc);
				if (U.team() == cteam && isStructure(U)) return true;
			}
		}
		return false;
	}
	
	static boolean startFac(Unit U) {
		if (gc.karbonite() < bc.bcUnitTypeBlueprintCost(UnitType.Factory)) return false;
		int c = comp(U);
		if (fac[c] > minFac[c]) return false;
		if (fac[c] > 0 && existsEnemy7(U)) {
			if (gc.round() <= 50 && 1.5*fac[comp(U)] <= minFac[comp(U)]) {
				
			} else {
				return false;
			}
		}
		
		MapLocation cloc = mapLoc(U);
		for (int i = 1; i < 9; ++i) if (gc.canBlueprint(U.id(), UnitType.Factory, directions[i])) {
			if (existsFac(cloc.add(directions[i]))) continue;
			gc.blueprint(U.id(), UnitType.Factory, directions[i]);
			fac[comp(U)] ++;
			return true;
		}
		return false;
	}

	static void run(Unit U) {
		produce(U);
		unload(U);
	}
}	
