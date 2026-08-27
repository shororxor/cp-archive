import java.util.Scanner;
import java.util.Arrays;
import java.util.ArrayList;
import java.math.BigInteger;

class Node {
	Node[] child = new Node[26];
	int real = 0, fake = 0;

	Node() {
		Arrays.fill(child, null);
	}
}

public class Main {
	static final int MAX_N = (int)1e6;
	static final int MAX_NODES = (int)2e6;
	static final int MAX_ALPHABET = 26;
	static final int[] MOD = { (int)1e9 + 2277, (int)1e9 + 5277, (int)1e9 + 8277, (int)1e9 + 9277 };
	static final int NMOD = 1;
	static final int BASE = 256;

	static int numWords;
	static String[] words = new String[MAX_N + 1];
	static int[] len = new int[MAX_N + 1];
	static int[][] POW = new int[NMOD][MAX_N + 1];
	static int[][] HS = new int[NMOD][MAX_N << 1 + 1];
	static int[][] RHS = new int[NMOD][MAX_N << 1 + 1];
	static int[] sta = new int[MAX_N + 1];
	static int[] fin = new int[MAX_N + 1];

	static long ans = 0;
	static int cnt = 0;
	static Node[] nodes = new Node[MAX_NODES + 1];
	static Node root;

	static Node createNode() {
		nodes[cnt] = new Node();
		return nodes[cnt++];
	}

	static void addString(String s, boolean isRev) {
		Node cur = root;
		for(char ch : s.toCharArray()) {
			int c = ch - 'a';
			if (cur.child[c] == null) cur.child[c] = createNode();
			cur = cur.child[c];
		}
		if (isRev) cur.fake++;
		else cur.real++;
	}

	static void calHash(String s, int[][] hs, int start, int len) {
        for(int j = 0; j < NMOD; ++j) {
            hs[j][start] = 0;
            for (int i = 1; i <= len; ++i) {
                hs[j][start + i] = (int)(((long)hs[j][start + i - 1] * BASE + s.charAt(i - 1)) % MOD[j]);
            }
        }
    }

    static int getHash(int[][] hs, int j, int start, int l, int r) {
        int res = (int)((hs[j][start + r] - (long)hs[j][start + l - 1] * POW[j][r - l + 1]) % MOD[j]);
        return res < 0 ? res + MOD[j] : res;
    }

    static boolean isPalin(int i, int u, int v) {
        for(int j = 0; j < NMOD; j++) {
            if (getHash(HS, j, sta[i], u, v) != getHash(RHS, j, sta[i], len[i] - v + 1, len[i] - u + 1))
                return false;
        }
        return true;
    }

	static void traverse(int id, boolean isRev) {
		Node cur = root;
		String s = words[id];

		if (!isRev) {
			for(int j = 1; j < len[id]; j++) {
				cur = cur.child[s.charAt(j - 1) - 'a'];
				if (isPalin(id, j + 1, len[id])) ans += cur.fake;
			}
		}
		else {
			for(int j = len[id]; j >= 2; j--) {
				cur = cur.child[s.charAt(j - 1) - 'a'];
				if (isPalin(id, 1, j - 1)) ans += cur.real;
			}
		}

		if (!isRev) {
			cur = cur.child[s.charAt(s.length() - 1) - 'a'];
			ans += cur.fake;
		}
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		numWords = sc.nextInt();
		for(int i = 1; i <= numWords; i++) {
			len[i] = sc.nextInt();
			words[i] = sc.next();
		}

		for(int j = 0; j < NMOD; j++) {
            POW[j][0] = 1;
            for(int i = 1; i <= MAX_N; i++)
                POW[j][i] = (int)(((long)POW[j][i - 1] * BASE) % MOD[j]);
        }

		root = createNode();
		sta[0] = fin[0] = -1;
		for(int i = 1; i <= numWords; i++) {
			sta[i] = fin[i - 1] + 1;
			fin[i] = sta[i] + len[i];

			calHash(words[i], HS, sta[i], len[i]);
			addString(words[i], false);

			String revWord = new StringBuilder(words[i]).reverse().toString();
			calHash(revWord, RHS, sta[i], len[i]);
			addString(revWord, true);
		}

		for(int i = 1; i <= numWords; i++) {
			traverse(i, false);
			traverse(i, true);
		}

		System.out.println(ans);
	}
}