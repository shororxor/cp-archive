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

class Node {
	int val, pref, suff;
	Node(int val_, int pref_, int suff_) {
		this.val = val;
		this.pref = pref_;
		this.suff = suff_;
	}

	static Node base() { return new Node(0, 0, 0); }
	static Node merge(Node L, Node R) {
		Node ans = Node.base();
        int k = Math.min(L.suff, R.pref);
        ans.val = L.val + R.val + 2 * k;
        ans.pref = R.pref - k + L.pref;
        ans.suff = L.suff - k + R.suff;
        return ans;
	}
}

class SegTree {
	int n;
	Node[] node;

	SegTree(int n_) {
		this.n = n_;
		node = new Node[4 * n + 1];
	}

	public void build(int i, int l, int r, char[] s) {
		if (l == r) {
			node[i] = Node.base();
			if (s[l] == '(') node[i].suff = 1;
			else node[i].pref = 1;
			return;
		}

		int m = (l + r) >> 1;
		build(i << 1, l, m, s);
		build(i << 1 | 1, m + 1, r, s);
		node[i] = Node.merge(node[i << 1], node[i << 1 | 1]);
	}

	public Node query(int i, int l, int r, int u, int v) {
		if (r < u || l > v || l > r || u > v) return Node.base();
		if (u <= l && r <= v) return node[i];

		int m = (l + r) >> 1;
		Node L = query(i << 1, l, m, u, v);
		Node R = query(i << 1 | 1, m + 1, r, u, v);
		return Node.merge(L, R);
	}
}

public class Main {
	static char[] s;

	public static void main(String[] args) throws IOException {
		Scanner sc = new Scanner(System.in);
		String input = sc.next();
		int n = input.length();
		s = ('0' + input).toCharArray();

		SegTree tree = new SegTree(n);
		tree.build(1, 1, n, s);

		int q = sc.nextInt();
		while(q-- > 0) {
			int l = sc.nextInt();
			int r = sc.nextInt();
			System.out.printf("%d\n", tree.query(1, 1, n, l, r).val);
		}

		sc.close();
	}
}