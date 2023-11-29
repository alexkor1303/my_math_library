#ifndef S21_MATH_H
#define S21_MATH_H

#define S21_NAN (0.0 / 0.0)
#define S21_INF_P (1.0 / 0.0)
#define S21_INF_N (-1.0 / 0.0)
#define S21_IS_INF(x) (x == S21_INF_N || x == S21_INF_P)
#define S21_IS_NAN(x) (x != x)
#define S21_EPS_E 1E-16
#define S21_EPS 1E-9
#define S21_DBL_MAX 1.7976931348623158e+308
#define S21_E 2.71828182845904523536
#define S21_ZERO_D 0.0000000000001
#define S21_ZERO_P 0.0 / 1.0
#define S21_ZERO_N -0.0 / 1.0
// angles
#define S21_PI 3.14159265358979323846
#define S21_PI_BY_TWO (S21_PI / 2)
#define S21_PI_BY_THREE (S21_PI / 3)
#define S21_PI_BY_FOUR (S21_PI / 4)
#define S21_PI_BY_SIX (S21_PI / 6)

#include <stdio.h>
#include <stdlib.h>

int s21_abs(int x);
long double s21_fabs(double x);
long double s21_ceil(double x);
long double s21_floor(double x);
long double s21_exp(double x);
long double s21_log(double x);
long double s21_pow(double base, double power);
long double s21_sqrt(double num);
long double s21_sin(double x);
long double s21_cos(double x);
long double s21_tan(double x);
long double s21_atan(double x);
long double s21_asin(double x);
long double s21_acos(double x);
long double s21_fmod(double x, double y);

#endif