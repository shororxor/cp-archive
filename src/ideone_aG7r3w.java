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

class SegmentTree {
	static int NEGINF = (int)-1e9;
	int n;
	int[] max, lazy;

	public SegmentTree(int n) {
		this.n = n;
		max = new int[4 * n + 1];
		lazy = new int[4 * n + 1];
	}

	private void pushDown(int i) {
        if (lazy[i] == 0) return;
 
        max[i << 1] = lazy[i];
        max[i << 1 | 1] = lazy[i];
 
        lazy[i << 1] = lazy[i];
        lazy[i << 1 | 1] = lazy[i];
        lazy[i] = 0;
	}

	private void update(int i, int l, int r, int u, int v, int c) {
		if (r < u || l > v || l > r || u > v) return;
        if (u <= l && r <= v) {
            max[i] = c;
            lazy[i] = c;
            return;
        }
 
        this.pushDown(i);
        int m = (l + r) >> 1;
        update(i << 1, l, m, u, v, c);
        update(i << 1 | 1, m + 1, r, u, v, c);

		max[i] = Math.max(max[i << 1], max[i << 1 | 1]); // pushup
	}

	private int query(int i, int l, int r, int u, int v) {
        if (r < u || l > v || l > r || u > v) return NEGINF;
        if (u <= l && r <= v) return max[i];

		this.pushDown(i);
        int m = (l + r) >> 1;
        int L = query(i << 1, l, m, u, v);
        int R = query(i << 1 | 1, m + 1, r, u, v);
		return Math.max(L, R);
	}

	public void update(int u, int v, int c) {
		this.update(1, 1, n, u, v, c);
	}

	public int query(int u, int v) {
		return this.query(1, 1, n, u, v);
	}
}

public class Main {
	public static void main(String[] args) throws IOException {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int q = sc.nextInt();

		SegmentTree tree = new SegmentTree(n);

		while(q-- > 0) {
			int t = sc.nextInt();
			if (t == 1) {
				int u = sc.nextInt();
				int v = sc.nextInt();
				int c = sc.nextInt();
				tree.update(u, v, c);

				for(int i = 1; i <= n; i++) System.out.printf("%d ", tree.query(i, i));
				System.out.println();
			}
			else if (t == 2) {
				int u = sc.nextInt();
				int v = sc.nextInt();
				System.out.println(tree.query(u, v));
			}
		}
		sc.close();
	}
}