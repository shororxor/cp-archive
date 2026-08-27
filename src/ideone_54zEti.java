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
	static int[][][] dp = new int[11][1001][1 << 10];

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		n = sc.nextInt();
		m = sc.nextInt();
		
		dp[0][0][0] = 1;
		for(int j = 0; j < m; j++) {
			for(int i = 0; i < n; i++) {
				for(int state = 0; state < (1 << n); state++) {
					if ((state & (1 << i)) == 0) {
						dp[i + 1][j][state ^ (1 << i)] += dp[i][j][state] % MOD;
						if (i <= n - 2 && (state & (1 << (i + 1))) == 0) {
							dp[i + 1][j][state ^ (1 << (i + 1))] += dp[i][j][state] % MOD;
						}
					}
					else {
						dp[i + 1][j][state ^ (1 << i)] += dp[i][j][state] % MOD;
					}
				}
				if (i == n - 1) {
					for(int state = 0; state < (1 << n); state++) {
						dp[0][j + 1][state] = dp[n][j][state];
					}
				}
			}
		}

		System.out.println(dp[0][m][0]);
	}
}