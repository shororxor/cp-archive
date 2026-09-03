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
import java.util.AbstractMap.SimpleEntry;
import java.math.BigInteger;

class Pair {
    int first, second;
    Pair(int first, int second) {
        this.first = first;
        this.second = second;
    }
}

class SegmentTree {
	int n;
	double[] sum;
	double[] lazy;

	private static int CNT(int l, int r) { return r - l + 1; }
	private static int SERIES(int n) { return ((1 << (n + 1)) - 1); }
	private static int SUM(int l, int r) { return SERIES(r) - SERIES(l - 1); }

	public SegmentTree(int n) {
		this.n = n;
		sum = new double[4 * n + 1];
		lazy = new double[4 * n + 1];
	}

	private void pushDown(int i, int l, int r) {
        if (lazy[i] == 0) return;
 
 		int m = (l + r) >> 1;
        sum[i << 1] += lazy[i] * SUM(l, m);
        sum[i << 1 | 1] += lazy[i] * SUM(m + 1, r);
	 
	 	lazy[i << 1] += lazy[i];
	 	lazy[i << 1 | 1] += lazy[i];
	 	lazy[i] = 0;
	}

	private void update(int i, int l, int r, int u, int v, double x) {
		if (r < u || l > v || l > r || u > v) return;
        if (u <= l && r <= v) {
        	sum[i] += x * SUM(l, r);
        	lazy[i] += x;
            return;
        }
 
        this.pushDown(i, l, r);
        int m = (l + r) >> 1;
        update(i << 1, l, m, u, v, x);
        update(i << 1 | 1, m + 1, r, u, v, x);
        sum[i] = sum[i << 1] + sum[i << 1 | 1]; // pushup
	}

	private double query(int i, int l, int r, int u, int v) {
        if (r < u || l > v || l > r || u > v) return 0;
        if (u <= l && r <= v) return sum[i];

		this.pushDown(i, l, r);
        int m = (l + r) >> 1;
        double L = query(i << 1, l, m, u, v);
        double R = query(i << 1 | 1, m + 1, r, u, v);
		return L + R;
	}

	public void update(int u, int v, double x) {
		this.update(1, 1, n, u, v, x / (1 << u));
	}

	public double query(int u, int v) {
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
				int x = sc.nextInt();
				tree.update(u, v, x);

				for(int i = 1; i <= n; i++) System.out.printf("%.0f ", tree.query(i,i));
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