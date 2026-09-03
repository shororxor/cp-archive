import java.util.Scanner;
import java.util.List;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Collections;
import java.math.BigInteger;

class Complex {
	double real, imag;

	public Complex(double real, double imag) {
		this.real = real;
		this.imag = imag;
	}

	public Complex add(Complex o) {
        return new Complex(this.real + o.real, this.imag + o.imag);
    }

	public Complex subtract(Complex o) {
        return new Complex(this.real - o.real, this.imag - o.imag);
    }

	public Complex multiply(Complex o) {
        return new Complex(this.real * o.real - this.imag * o.imag,
                           this.real * o.imag + this.imag * o.real);
    }

	public Complex divide(double val) {
		return new Complex(this.real / val, this.imag / val);
	}

	public Complex conjugate() {
		return new Complex(this.real, -this.imag);
	}

	public static Complex polar(double r, double theta) {
		return new Complex(r * Math.cos(theta), r * Math.sin(theta));
	}

	public double getReal() {
		return this.real;
	}

	public double getImag() {
		return this.imag;
	}
}

class FFT {
	boolean check(int n) {
		return n > 0 && (n & (n - 1)) == 0;
	}

	List<Complex> resize(List<Complex> A) {
		int n = 1;
		while(n < A.size()) n <<= 1;
		while(A.size() < n) A.add(new Complex(0, 0));
		return A;
	}

	List<Complex> inverse(List<Complex> FA) {
		int n = FA.size();
		if (!check(n)) FA = resize(FA);

		for(int i = 0; i < FA.size(); i++) {
			FA.set(i, FA.get(i).conjugate());
		}

		List<Complex> A = transform(FA, false);
		for(int i = 0; i < A.size(); i++) {
			A.set(i, A.get(i).conjugate().divide(n));
		}
		return A;
	}

	List<Complex> transform(List<Complex> A, boolean inv) {
		int n = A.size();
		if (n == 1) return new ArrayList<>(A);

		List<Complex> A0 = new ArrayList<>(Collections.nCopies(n/2, new Complex(0,0)));
		List<Complex> A1 = new ArrayList<>(Collections.nCopies(n/2, new Complex(0,0)));

		for(int d = 0; d < n/2; d++) {
			A0.set(d, A.get(2*d));
			A1.set(d, A.get(2*d + 1));
		}

		List<Complex> F0 = transform(A0, inv);
		List<Complex> F1 = transform(A1, inv);

		List<Complex> F = new ArrayList<>(Collections.nCopies(n, new Complex(0,0)));

		for(int k = 0; k < n/2; k++) {
			double angle = Math.acos(-1.0) / n * k * (inv ? -2 : 2);
			Complex w = Complex.polar(1.0, angle);
			F.set(k, F0.get(k).add(w.multiply(F1.get(k))));
			F.set(k + n/2, F0.get(k).subtract(w.multiply(F1.get(k))));
		
			if (inv) {
				F.set(k, F.get(k).divide(2));
				F.set(k + n/2, F.get(k + n/2).divide(2));
			}
		}

		return F;
	}

	List<Complex> conv(List<Complex> A, List<Complex> B) {
		if (A.isEmpty() || B.isEmpty()) return new ArrayList<>();

		int n = 1;
		while (n < A.size() + B.size() - 1) n <<= 1;
		while(A.size() < n) A.add(new Complex(0, 0));
		while(B.size() < n) B.add(new Complex(0, 0));

		List<Complex> FA = transform(A, false);
		List<Complex> FB = transform(B, false);

		for(int i = 0; i < n; i++) FA.set(i, FA.get(i).multiply(FB.get(i)));
		return transform(FA, true);
	}
}

public class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int N = sc.nextInt();
		int M = sc.nextInt();

		List<Complex> A = new ArrayList<>();
		List<Complex> B = new ArrayList<>();

		for(int i = 0; i < N; i++) {
			A.add(new Complex(sc.nextDouble(), 0));
		}

		for(int i = 0; i < M; i++) {
			B.add(new Complex(sc.nextDouble(), 0));
		}

		FFT fft = new FFT();
		List<Complex> C = fft.conv(A, B);

		for(Complex c : C) {
			System.out.printf((int)(c.getReal() + 0.5) + " ");
		}
	}
}