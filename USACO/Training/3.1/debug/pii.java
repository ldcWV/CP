public class pii implements Comparable<pii> {
	public int f, s;
	pii(int F, int S) {
		f = F;
		s = S;
	}
	public int compareTo(pii x) {
		if (f != x.f) {
			if (f < x.f) return -1;
			if (f > x.f) return 1;
			return 0;
		}
		if (s < x.s) return -1;
		if (s > x.s) return 1;
		return 0;
	}
}
