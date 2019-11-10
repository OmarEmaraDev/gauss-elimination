#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIGNIFICANT_FIGURES 3

int n;
double **matrix;
double *solution;
_Bool singular = 0;

int significantFigures(double x) {
  double multiplier = 1.0;
  for (int i = 0; i < MAX_SIGNIFICANT_FIGURES; i++) {
    if (fabs(fmod(x * multiplier, 1.0)) < 1e-5) {
      return i;
    }
    multiplier *= 10.0;
  }
  return MAX_SIGNIFICANT_FIGURES;
}

void printMatrix() {
  puts("\\begin{bmatrix}");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n + 1; j++) {
      printf("%.*f", significantFigures(matrix[i][j]), matrix[i][j]);
      if (j != n) {
        printf(" & ");
      }
    }
    puts(" \\\\");
  }
  puts("\\end{bmatrix}");
}

int columnArgMax(int x) {
  int argmax = x;
  double max = matrix[x][x];
  for (int i = x + 1; i < n; i++) {
    if (fabs(matrix[i][x]) > max) {
      max = fabs(matrix[i][x]);
      argmax = i;
    }
  }
  return argmax;
}

_Bool isSingular(int x) {
  for (int i = x; i < n; i++) {
    if (matrix[x][i] != 0.0) {
      return 0;
    }
  }
  return 1;
}

void exchangeRows(int x, int y) {
  printf("R_%i &\\Longleftrightarrow R_%i\n", x + 1, y + 1);
  puts("&&\\qquad");
  for (int i = 0; i < n + 1; i++) {
    double tmp = matrix[x][i];
    matrix[x][i] = matrix[y][i];
    matrix[y][i] = tmp;
  }
  printMatrix();
  puts("\\\\");
}

void subtractRows(int x, int y) {
  double factor = matrix[y][x] / matrix[x][x];
  printf("R_%i &\\Longleftarrow R_%i - %.*f R_%i\n", y + 1, y + 1,
         significantFigures(factor), factor, x + 1);
  puts("&&\\qquad");
  for (int i = 0; i < n + 1; i++) {
    matrix[y][i] -= factor * matrix[x][i];
  }
  printMatrix();
  puts("\\\\");
}

void elimnate() {
  puts("\\begin{equation*}");
  puts("\\begin{aligned}");
  for (int i = 0; i < n - 1; i++) {
    if (isSingular(i)) {
      singular = 1;
      return;
    }
    int argmax = columnArgMax(i);
    if (argmax != i) {
      exchangeRows(i, argmax);
    }
    for (int j = i + 1; j < n; j++) {
      if (matrix[j][i] == 0) {
        continue;
      }
      subtractRows(i, j);
    }
  }
  puts("\\end{aligned}");
  puts("\\end{equation*}");
}

void backSubstitute() {
  puts("");
  puts("\\begin{equation*}");
  puts("\\begin{aligned}");
  for (int i = n - 1; i >= 0; i--) {
    printf("x_%i &= \\frac{%.*f", i + 1, significantFigures(matrix[i][n]),
           matrix[i][n]);
    double sum = matrix[i][n];
    for (int j = i + 1; j < n; j++) {
      printf(" - %.*f x_%i", significantFigures(matrix[i][j]), matrix[i][j],
             j + 1);
      sum -= matrix[i][j] * solution[j];
    }
    printf("}{%.*f}", significantFigures(matrix[i][i]), matrix[i][i]);
    solution[i] = sum / matrix[i][i];
    printf(" = %.*f \\\\\n", significantFigures(solution[i]), solution[i]);
  }
  puts("\\end{aligned}");
  puts("\\end{equation*}");
}

void guass() {
  elimnate();
  if (matrix[n - 1][n - 1] == 0.0 || singular) {
    puts("No unique solution exists.");
    return;
  }
  puts("");
  puts("We start back substituting.");
  solution = (double *)malloc(n * sizeof(double));
  backSubstitute();
}

void parseArgs(char **args) {
  n = strtol(args[1], NULL, 10);
  matrix = (double **)malloc(n * sizeof(double *));
  for (int i = 0; i < n; i++) {
    matrix[i] = (double *)malloc((n + 1) * sizeof(double));
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n + 1; j++) {
      matrix[i][j] = strtod(args[2 + i * (n + 1) + j], NULL);
    }
  }
}

void clean() {
  free(solution);
  for (int i = 0; i < n; i++) {
    free(matrix[i]);
  }
  free(matrix);
}

int main(int argc, char **args) {
  parseArgs(args);
  guass();
  clean();
  return 0;
}
