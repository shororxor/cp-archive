import java.io.File;
import java.io.FileNotFoundException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
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
	static final int NMOD = 1;
	static final int BASE = 256;
	static final int MAX = (int)5e6;

	static int[][] HS = new int[NMOD][MAX + 1];
	static int[][] RHS = new int[NMOD][MAX + 1];
	static int[][] POW = new int[NMOD][MAX + 1];
	static int[] F = new int[MAX + 1];

	static boolean isPalin(int l, int r, int len) {
		for(int j = 0; j < NMOD; j++) {
			int hash = (int)(((long)HS[j][r] - (long)HS[j][l - 1] * POW[j][r - l + 1]) % MODS[j]);
			int rhash = (int)(((long)RHS[j][len - l + 1] - (long)RHS[j][len - r] * POW[j][r - l + 1]) % MODS[j]);
			hash = hash < 0 ? hash + MODS[j] : hash;
			rhash = rhash < 0 ? rhash + MODS[j] : rhash;
			if (hash != rhash) return false;
		}
		return true;
	}

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		char[] s = br.readLine().toCharArray();
		int length = s.length;

		for(int j = 0; j < NMOD; j++) {
			POW[j][0] = 1;
			for(int i = 1; i <= length; i++) {
				POW[j][i] = (int)(((long)POW[j][i - 1] * BASE) % MODS[j]);
				HS[j][i] = (int)(((long)HS[j][i - 1] * BASE + s[i - 1]) % MODS[j]);
				RHS[j][i] = (int)(((long)RHS[j][i - 1] * BASE + s[length - i]) % MODS[j]);
			}
		}

		int ans = 0;
		for(int i = 1; i <= length; i++) {
			if (isPalin(1, i, length)) F[i] = F[i / 2] + 1;
			ans += F[i];
		}

		System.out.println(ans);
	}
}