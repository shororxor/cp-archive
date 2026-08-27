import java.io.File;
import java.io.FileNotFoundException;
import java.io.BufferedReader;
import java.io.PrintWriter;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.Scanner;
import java.util.StringTokenizer;
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
import java.util.Comparator;
import java.util.function.Consumer;
import java.util.AbstractMap.SimpleEntry;
import java.math.BigInteger;

public class Main {
	static class FastScanner {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer("");
		String next() {
			while (!st.hasMoreTokens())
				try { st=new StringTokenizer(br.readLine());				               
				} catch (IOException e) {}
			return st.nextToken();
		}
		int nextInt() {
			return Integer.parseInt(next());
		}
		long nextLong() {
			return Long.parseLong(next());
		}
	}

	static class Query {
		int l, r, k, id, ans;
		Query(int l, int r, int k, int id) {
			this.l = l;
			this.r = r;
			this.k = k;
			this.id = id;
		}
	}

	static int MAX = 30000;
	static int[] a = new int[MAX + 1];
	static Integer[] id = new Integer[MAX + 1];
	static Query[] q = new Query[200001];

	static class SegTree {
		int n;
		int[] node;

		SegTree(int n) {
			this.n = n;
			node = new int[4 * n + 1];
		}

		private void update(int i, int l, int r, int u, int v, int c) {
	        if (r < u || l > v || l > r || u > v) return;
	        if (u == l && r == v) {
	            node[i] = c;
	            return;
	        }

	        int m = (l + r) >> 1;
	        update(i << 1, l, m, u, v, c);
	        update(i << 1 | 1, m + 1, r, u, v, c);
	        node[i] = node[i << 1] + node[i << 1 | 1];
	    }

	    private int query(int i, int l, int r, int u, int v) {
	        if (r < u || l > v || l > r || u > v) return 0;
	        if (u <= l && r <= v) return node[i];

	        int m = (l + r) >> 1;
	        int L = query(i << 1, l, m, u, v);
	        int R = query(i << 1 | 1, m + 1, r, u, v);
	        return L + R;
	    }

	    public void update(int u, int v, int c) {
	        this.update(1, 1, n, u, v, c);
	    }

	    public int query(int u, int v) {
	        return this.query(1, 1, n, u, v);
	    }
	}

	static class Comp implements Comparator<Integer> {
		public int compare(Integer id1, Integer id2) {
			if (a[id1] < a[id2]) return -1;
			if (a[id1] > a[id2]) return 1;
			return 0;
		}
	}

	static class Comp1 implements Comparator<Query> {
		public int compare(Query q1, Query q2) {
			if (q1.k < q2.k) return -1;
			if (q1.k > q2.k) return 1;
			return 0;
		}
	}

	static class Comp2 implements Comparator<Query> {
		public int compare(Query q1, Query q2) {
			if (q1.id < q2.id) return -1;
			if (q1.id > q2.id) return 1;
			return 0;
		}
	}

	public static void main(String[] args) throws IOException {
	    FastScanner sc = new FastScanner();
	    PrintWriter out = new PrintWriter(System.out);

		int n = sc.nextInt();
		SegTree tree = new SegTree(n);

		for(int i = 1; i <= n; i++) {
			a[i] = sc.nextInt();
			id[i] = i;
			tree.update(i, i, 1);
		}
		 
		Arrays.sort(id, 1, n + 1, new Comp());
		// Arrays.sort(id, 1, n + 1, Comparator.comparingInt((Integer x) -> a[x]));

		int m = sc.nextInt();
		for(int i = 1; i <= m; i++) {
			q[i] = new Query(0, 0, 0, 0);
			q[i].l = sc.nextInt();
			q[i].r = sc.nextInt();
			q[i].k = sc.nextInt();
			q[i].id = i;
		}

		Arrays.sort(q, 1, m + 1, new Comp1());
		// Arrays.sort(q, 1, m + 1, Comparator.comparingInt((Query q) -> q.k));

		int j = 1;
	    for(int i = 1; i <= m; i++) {
	        for( ; j <= n && a[id[j]] <= q[i].k; j++) {
	            tree.update(id[j], id[j], 0);
	        }
	        q[i].ans = tree.query(q[i].l, q[i].r);
	    }

	    Arrays.sort(q, 1, m + 1, new Comp2());
	    // Arrays.sort(q, 1, m + 1, Comparator.comparingInt((Query q) -> q.id));

	    for(int i = 1; i <= m; i++) out.printf("%d\n", q[i].ans);
		out.close();
	}
}