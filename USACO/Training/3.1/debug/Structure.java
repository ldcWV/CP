import bc.*;

public class Structure extends Player {
    
    static boolean isStructure(Unit U) { // is unit a structure
    		if (U == null) return false;
    		if (U.unitType() == UnitType.Factory) return true;
    		if (U.unitType() == UnitType.Rocket) return true;
    		return false;
    }
    
    
    static int getNum(Unit U, UnitType u) {
		VecUnitID V = U.structureGarrison();
		int num = 0;
		for (int i = 0; i < V.size(); ++i) 
			if (gc.unit(V.get(i)).unitType() == u)
				num ++;
		return num;
	}
    
    static void unload(Unit U) {
    		for (int d = 1; d < 9; ++d)
	        if (gc.canUnload(U.id(),directions[d])) {
	            gc.unload(U.id(),directions[d]);
	            if(gc.hasUnitAtLocation(mapLoc(U).add(directions[d])))
            			UNITS.add(gc.senseUnitAtLocation(mapLoc(U).add(directions[d])));
	            System.out.println("Unloaded!");
	        }
	}
}
