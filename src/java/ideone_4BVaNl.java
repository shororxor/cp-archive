import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.List;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.PriorityQueue;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Collections;
import java.util.function.Consumer;
import java.math.BigInteger;

public class Main {
	static final int MODS[] = { (int)1e9 + 2277, (int)1e9 + 5277, (int)1e9 + 8277, (int)1e9 + 9277 };
	static final int NMOD = 1;
	static final int BASE = 256;
	static final int MAX = 100;

	static int[][] HS1 = new int[NMOD][MAX + 1];
	static int[][] HS2 = new int[NMOD][MAX + 1];
	static int[][] POW = new int[NMOD][MAX + 1];
	static int n, m;

	static void buildHash(String s, String t) {
		for(int j = 0; j < NMOD; j++) {
			POW[j][0] = 1;
			for(int i = 1; i <= n; i++) POW[j][i] = (int)(((long)POW[j][i - 1] * BASE) % MODS[j]);
		}

		for(int j = 0; j < NMOD; j++) {
			HS1[j][0] = 0;
			for(int i = 1; i <= n; i++) HS1[j][i] = (int)(((long)HS1[j][i - 1] * BASE + s.charAt(i - 1)) % MODS[j]);

			HS2[j][0] = 0;
			for(int i = 1; i <= m; i++) HS2[j][i] = (int)(((long)HS2[j][i - 1] * BASE + t.charAt(i - 1)) % MODS[j]);
		}
	}

	static int getHash(int[][] hs, int j, int l, int r) {
		int res = (int)(((long)hs[j][r] - (long)hs[j][l - 1] * POW[j][r - l + 1]) % MODS[j]);
		return res < 0 ? res + MODS[j] : res;
	}

	static boolean compareHash(int l, int r) {
		for(int j = 0; j < NMOD; j++) {
			if (getHash(HS1, j, l, r) != getHash(HS2, j, 1, m)) {
				return false;
			}
		}

		return true;
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		String s = sc.next();
		String t = sc.next();

		n = s.length();
		m = t.length();

		buildHash(s, t);
		for(int i = 1; i <= n - m + 1; i++) {
			if (compareHash(i, i + m - 1)) {
				System.out.printf("Found at %d\n", i - 1);
			}
		}
	}
}