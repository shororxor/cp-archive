import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.List;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Collections;
import java.util.function.Consumer;
import java.math.BigInteger;

public class Main {
	static int n, m;
	static int MOD = 1000000007;
	static int[][] dp = new int[2][1 << 10];

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		n = sc.nextInt();
		m = sc.nextInt();

		int cur = 0;
		dp[0][0] = 1;

		for(int j = 0; j < m; j++) {
			for(int i = 0; i < n; i++) {
				int next = cur ^ 1;
				Arrays.fill(dp[next], 0);
				for(int state = 0; state < (1 << n); state++) {
					dp[next][state ^ (1 << i)] += dp[cur][state] % MOD;
					if (i <= n - 2 && (state & (1 << i)) == 0 && (state & (1 << (i + 1))) == 0) {
						dp[next][state ^ (1 << (i + 1))] += dp[cur][state] % MOD;
					}
				}
				cur = next;
			}
		}

		System.out.println(dp[cur][0]);
	}
}