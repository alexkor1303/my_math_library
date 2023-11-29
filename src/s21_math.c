#include "s21_math.h"

int s21_abs(int x) {
  if (x < 0) x *= -1;
  return x;
}

long double s21_fabs(double x) {
  if (x < 0) x *= -1.0;
  return x;
}

long double s21_log(double x) {
  int ex_pow = 0;
  long double result = 0;
  long double compare = 0;
  if (S21_IS_NAN(x) || x < 0) {
    result = S21_NAN;
  } else if (x == S21_INF_P || x == S21_INF_N) {
    result = x;
  } else if (x == 0) {
    result = S21_INF_N;
  } else if (x == 1) {
    result = 0;
  } else {
    for (; x >= S21_E; ex_pow++) x /= S21_E;
    for (int i = 0; i < 100; i++) {
      compare = result;
      result = compare + 2 * (x - s21_exp(compare)) / (x + s21_exp(compare));
    }
    result += ex_pow;
  }
  return result;
}

long double s21_exp(double x) {
  long double add_value = 1;
  long double i = 1;
  long double result = 1;
  int sign_x = 0;
  if (x == S21_INF_P) {
    result = S21_INF_P;
  } else if (x == S21_INF_N) {
    result = S21_INF_N;
  } else if (x == S21_NAN) {
    result = S21_NAN;
  } else if (x == 0) {
    result = 1;
  } else {
    if (x < 0) {
      x = s21_fabs(x);
      sign_x = 1;
    }
    while (s21_fabs(add_value) > S21_EPS && result < S21_DBL_MAX) {
      add_value *= x / i;
      i += 1;
      result += add_value;
    }
    if (sign_x) result = 1 / result;
  }
  if (result > S21_DBL_MAX) {
    result = S21_INF_P;
  } else if (result < S21_EPS_E) {
    result = 0;
  }
  return result;
}

long double s21_ceil(double x) {
  long double tmp;
  if (x == S21_NAN) {
    tmp = x;
  } else if (x == S21_INF_P) {
    tmp = S21_INF_P;
  } else if (x == S21_INF_N) {
    tmp = S21_INF_N;
  } else if (x == S21_ZERO_P) {
    tmp = x;
  } else {
    if (x >= 0) {
      tmp = (long)x;
      if (x != (double)tmp) tmp++;
    } else {
      tmp = (long)x;
    }
  }
  return tmp;
}

long double s21_floor(double x) {
  double part = (long)x;
  if (x == S21_NAN) {
    part = x;
  } else if (x == S21_INF_P) {
    part = S21_INF_P;
  } else if (x == S21_INF_N) {
    part = S21_INF_N;
  } else if (x == S21_ZERO_P) {
    part = x;
  } else if (x <= 0 && part != x) {
    part--;
  }
  return part;
}
long double s21_fmod(double x, double y) {
  long double res = 0;
  if (S21_IS_NAN(x) || S21_IS_NAN(y) || y == 0) {
    res = S21_NAN;
  } else if (S21_IS_INF(x)) {
    res = S21_INF_P;
  } else if (S21_IS_INF(y)) {
    res = x;
  } else if (x == 0.0 && y != 0.0) {
    res = 0.0;
  } else {
    long long int nep_chastnoe = x / y;
    res = (long double)x - (long double)(nep_chastnoe * (long double)y);
  }
  return res;
}

long double s21_pow(double base, double exp) {
  long double result = 0;
  if (!exp) {
    return 1;
  } else if (base == S21_INF_N && exp == S21_INF_N) {
    return 0;
  } else if (base == S21_INF_N && exp == S21_INF_P) {
    return S21_INF_P;
  } else if (base < 0 && exp != (long long int)exp) {
    return S21_INF_N;
  } else if (base == S21_NAN || exp == S21_NAN) {
    return S21_NAN;
  } else {
    if (base > 0) {
      result = s21_exp(exp * s21_log(base));
    } else if (base < 0) {
      base = s21_fabs(base);
      result = s21_exp(exp * s21_log(base));
      if (((int)exp % 2) != 0) result = -result;
    }
  }
  return result;
}

long double s21_sqrt(double x) {
  long double result = 0;
  if (S21_IS_NAN(x) || x == S21_INF_N || x < 0) {
    return S21_NAN;
  } else if (x == S21_INF_P || x == 0) {
    return (long double)x;
  } else {
    result = s21_pow(x, 0.5);
  }
  return result;
}

long double s21_sin(double x) {
  long double sum = x, an = x, n = 0;
  if (S21_IS_NAN(x) || S21_IS_INF(x)) {
    sum = S21_NAN;
  }
  while (s21_fabs(an) > S21_EPS) {
    an *= (-1) * x * x / ((2 * n + 2) * (2 * n + 3));
    sum += an;
    n++;
  }
  return sum;
}
long double s21_asin(double x) {
  long double result = 0.0;
  if (x == 1.0) {
    result = S21_PI_BY_TWO;
  } else if (x == -1) {
    result = -S21_PI_BY_TWO;
  } else if (x > -1.0 && x < 1.0) {
    long double x_si = s21_sqrt(1.0 - s21_pow(x, 2));
    result = s21_atan(x / x_si);
  } else {
    result = S21_NAN;
  }

  return result;
}

long double s21_acos(double x) {
  long double result = 0.0;
  if (x == 1.0) {
    result = 0.0;
  } else if (x == -1.0) {
    result = S21_PI;
  } else if (x == 0.0) {
    result = S21_PI_BY_TWO;
  } else {
    long double x_si = s21_sqrt(1.0 - x * x);
    if (x > 0 && x < 1) {
      result = s21_atan(x_si / x);
    } else if (x > -1 && x < 0) {
      result = s21_atan(x_si / x) + S21_PI;
    } else {
      result = S21_NAN;
    }
  }

  return result;
}

long double s21_cos(double x) {
  long double sum = 1, an = 1, n = 1;

  if (S21_IS_NAN(x) || S21_IS_INF(x)) {
    sum = S21_NAN;
  } else {
    while (s21_fabs(an) > S21_EPS) {
      an *= (-1) * x * x / ((2 * n - 1) * (2 * n));
      sum += an;
      n++;
    }
  }
  return sum;
}

long double s21_tan(double x) { return (s21_sin(x) / s21_cos(x)); }

long double s21_atan(double x) {
  long double val = 0.0;
  double result = 0.0;
  double result_dif = 1.0;
  double xplus_exp = 1.0;
  int factorial = 1;
  int count = 1;
  if (x == 1) {
    result = S21_PI_BY_FOUR;
  } else if (x == -1) {
    result = -S21_PI_BY_FOUR;
  } else if (x == S21_INF_P) {
    result = S21_PI_BY_TWO;
  } else if (x == S21_INF_N) {
    result = -S21_PI_BY_TWO;
  } else if (x == S21_NAN) {
    result = S21_NAN;
  } else {
    val = s21_fabs(x) > 1.0 ? 1.0 / x : x;
    while (s21_fabs(result - result_dif) > S21_EPS) {
      result_dif = result;
      if (count % 2) {
        result += (s21_pow(val, xplus_exp) / factorial);
      } else {
        result -= (s21_pow(val, xplus_exp) / factorial);
      }
      xplus_exp += 2;
      factorial += 2;
      count++;
    }
    if (x > 1.0) {
      result = S21_PI_BY_TWO - result;
    } else if (x < -1.0) {
      result = -1.0 * (S21_PI_BY_TWO + result);
    }
  }
  return result;
}
