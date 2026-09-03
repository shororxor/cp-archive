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
	static int INF = Integer.MAX_VALUE;
	static int MAX = 101;

	static int[] par = new int[MAX];
	static int[][] cap = new int[MAX][MAX];
	static int[][] flow = new int[MAX][MAX];
	static List<Integer>[] graph = new ArrayList[MAX];

	static int bfs(int s, int t) {
		Arrays.fill(par, -1);
		Queue<int[]> q = new LinkedList<>();
		q.add(new int[]{s, INF});
		par[s] = -2;

		while(!q.isEmpty()) {
			int[] cur = q.poll();
			int u = cur[0];
			int f = cur[1];

			for(int v : graph[u]) {
				if (par[v] == -1 && cap[u][v] > flow[u][v]) {
					par[v] = u;
					f = Math.min(f, cap[u][v] - flow[u][v]);
					if (v == t) return f;
					q.add(new int[]{v, f});
				}
			}
		}
		return 0;
	}

	static int EdmondsKarp(int s, int t) {
		int sumflow = 0;
		int curflow = 0;

		while((curflow = bfs(s, t)) != 0) {
			sumflow += curflow;
			int p, u = t;
			while(u != s) {
				p = par[u];
				flow[p][u] += curflow;
				flow[u][p] -= curflow;
				u = p;
			}
		}
		return sumflow;
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int m = sc.nextInt();
		int s = sc.nextInt();
		int t = sc.nextInt();

		for(int i = 0; i < MAX; i++) graph[i] = new ArrayList<>();
		for(int i = 0; i < m; i++) {
			int u = sc.nextInt();
			int v = sc.nextInt();
			int w = sc.nextInt();
			graph[u].add(v);
			graph[v].add(u);
			cap[u][v] = w;
		}

		System.out.println(EdmondsKarp(s, t));
	}
}