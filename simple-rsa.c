#include <stdio.h>

struct extended_euclidian_result {
  int gcd;
  int x;
  int y;
};

typedef struct extended_euclidian_result gcd_and_quotients;

struct factorize_result {
  int p;
  int q;
};

typedef struct factorize_result factors;

gcd_and_quotients extended_euclidian (int a, int b, gcd_and_quotients *recursion_context);
factors factorize (int n);

int square_multiply (int x, int k, int n);

int main (int argc, char *argv[]) {
  int n, e, c;

  scanf("%d %d %d", &n, &e, &c);

  factors f = factorize(n);

  int phi_n = (f.p - 1) * (f.q - 1);

  gcd_and_quotients recursion_context;
  gcd_and_quotients res = extended_euclidian(e, phi_n, &recursion_context);

  int mult_inverse = 0;

  if (res.x < 0) mult_inverse = (res.x % phi_n + phi_n) % phi_n;
  else mult_inverse = res.x;

  int decripted = square_multiply(c, mult_inverse, n);
  
  printf("%d\n", decripted);

  return 0;
}

int square_multiply (int x, int k, int n) {
  int r = 1;

  while (k > 0) {
    if (k % 2 == 1) r = (r * x) % n;

    k = k >> 1;
    x = (x * x) % n;
  }

  return r;
}

gcd_and_quotients extended_euclidian (int a, int b, gcd_and_quotients *recursion_context) {  
  if (a == 0) {
    recursion_context->gcd = b;
    recursion_context->x = 0;
    recursion_context->y = 1;

    return *recursion_context;
  }

  gcd_and_quotients prev = extended_euclidian(b % a, a, recursion_context);

  recursion_context->x = prev.y - (b / a) * prev.x;
  recursion_context->y = prev.x;

  return *recursion_context;
}

factors factorize (int n) {
  for (int i = 2; i <= n / 2; i++) {
    if (n % i == 0) {
      factors res;

      res.p = i;
      res.q = n / i;

      return res;
    }
  }
}
