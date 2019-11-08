#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int n;
double **matrix;
double *solution;

void printMatrix() {
  puts("\\begin{equation*}");
  puts("\\begin{bmatrix}");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n + 1; j++) {
      printf("%.1f", matrix[i][j]);
      if (j != n) {
        printf(" & ");
      }
    }
    puts(" \\\\");
  }
  puts("\\end{bmatrix}");
  puts("\\end{equation*}");
}

int columnArgMax(int x) {
  double max = fabs(matrix[0][x]);
  int argmax = 0;
  for (int i = x; i < n; i++) {
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
  puts("");
  printf("By exchanging $R_%i$ and $R_%i$\n", x + 1, y + 1);
  puts("");
  for (int i = 0; i < n + 1; i++) {
    double tmp = matrix[x][i];
    matrix[x][i] = matrix[y][i];
    matrix[y][i] = tmp;
  }
  printMatrix();
}

void subtractRows(int x, int y) {
  double factor = matrix[y][x] / matrix[x][x];
  puts("");
  printf("By subtracting $%.1f R_%i$ from $R_%i$\n", factor, x + 1, y + 1);
  puts("");
  for (int i = 0; i < n + 1; i++) {
    matrix[y][i] -= factor * matrix[x][i];
  }
  printMatrix();
}

void elimnate() {
  for (int i = 0; i < n - 1; i++) {
    if (isSingular(i)) {
      puts("No unique solution exists.");
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
}

void backSubstitute() {
  puts("");
  puts("\\begin{equation*}");
  puts("\\begin{aligned}");
  for (int i = n - 1; i >= 0; i--) {
    printf("x_%i &= \\frac{%.1f", i + 1, matrix[i][n]);
    double sum = matrix[i][n];
    for (int j = i + 1; j < n; j++) {
      printf(" - %.1f x_%i", matrix[i][j], j + 1);
      sum -= matrix[i][j] * solution[j];
    }
    printf("}{%.1f}", matrix[i][i]);
    solution[i] = sum / matrix[i][i];
    printf(" = %.1f \\\\\n", solution[i]);
  }
  puts("\\end{aligned}");
  puts("\\end{equation*}");
}

void guass() {
  elimnate();
  if (matrix[n - 1][n - 1] == 0.0) {
    puts("No unique solution exists.");
    return;
  }
  puts("");
  puts("We reached the echelon form. We start back substituting");
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
