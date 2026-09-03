import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.List;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.PriorityQueue;
import java.util.Map;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Collections;
import java.util.function.Consumer;
import java.math.BigInteger;

public class Main {
	static final int[] MODS = {(int)1e9 + 2277, (int)1e9 + 5277, (int)1e9 + 8277, (int)1e9 + 9277};
	static final int NMOD = 2;
	static final int BASE = 256;
	static final int MAX = (int)1e5;

	static int[][] HS = new int[NMOD][MAX + 1];
	static int[][] POW = new int[NMOD][MAX + 1];	

	static void calHash(String s, int len) {
		for(int j = 0; j < NMOD; j++) for(int i = 1; i <= len; i++)
				HS[j][i] = (int)(((long)HS[j][i - 1] * BASE + s.charAt(i - 1)) % MODS[j]);
	}

	static void prepare() {
		for(int j = 0; j < NMOD; j++) {
			POW[j][0] = 1;
			for(int i = 1; i <= MAX; i++) POW[j][i] = (int)(((long)POW[j][i - 1] * BASE) % MODS[j]);
		}
	}

	static int getHash(int j, int l, int r) {
		int res = (int)((HS[j][r] - (long)HS[j][l - 1] * POW[j][r - l + 1]) % MODS[j]);
		return res < 0 ? res + MODS[j] : res;
	}

	public static void solve(Scanner sc) {
		for (int j = 0; j < NMOD; j++) Arrays.fill(HS[j], 0);
		int n = sc.nextInt();
		int k = sc.nextInt();
		String s = sc.next();
		calHash(s, s.length());

		s = "0" + s;
		int ans = 0;
		HashMap<Integer, Integer> used = new HashMap<>();
		for(int i = 1; i <= n - k + 1; i++) {
			boolean update = false;
			for(int j = 0; j < NMOD; j++) {
				int hash = getHash(j, i, i + k - 1);
				if (!used.containsKey(hash) && !update) {
					ans++;
					update = true;
				}
				used.put(hash, 1);
			}
		}
		System.out.println(ans);
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		prepare();
		int T = sc.nextInt();
		for(int t = 1; t <= T; t++) solve(sc);
	}
}