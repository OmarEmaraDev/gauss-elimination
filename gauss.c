#include <math.h>
#include <stdio.h>

#define SIZE 3

void printMatrix(double matrix[SIZE][SIZE + 1]) {
  puts("\\begin{equation*}");
  puts("\\begin{bmatrix}");
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE + 1; j++) {
      printf("%.1f", matrix[i][j]);
      if (j != SIZE) {
        printf(" & ");
      }
    }
    puts(" \\\\");
  }
  puts("\\end{bmatrix}");
  puts("\\end{equation*}");
}

int columnArgMax(double matrix[SIZE][SIZE + 1], int x) {
  double max = fabs(matrix[0][x]);
  int argmax = 0;
  for (int i = x; i < SIZE; i++) {
    if (fabs(matrix[i][x]) > max) {
      max = fabs(matrix[i][x]);
      argmax = i;
    }
  }
  return argmax;
}

_Bool isSingular(double matrix[SIZE][SIZE + 1], int x) {
  for (int i = x; i < SIZE; i++) {
    if (matrix[x][i] != 0.0) {
      return 0;
    }
  }
  return 1;
}

void exchangeRows(double matrix[SIZE][SIZE + 1], int x, int y) {
  puts("");
  printf("By exchanging $R_%i$ and $R_%i$\n", x + 1, y + 1);
  puts("");
  for (int i = 0; i < SIZE + 1; i++) {
    double tmp = matrix[x][i];
    matrix[x][i] = matrix[y][i];
    matrix[y][i] = tmp;
  }
  printMatrix(matrix);
}

void subtractRows(double matrix[SIZE][SIZE + 1], int x, int y) {
  double factor = matrix[y][x] / matrix[x][x];
  puts("");
  printf("By subtracting $%.1f R_%i$ from $R_%i$\n", factor, x + 1, y + 1);
  puts("");
  for (int i = 0; i < SIZE + 1; i++) {
    matrix[y][i] -= factor * matrix[x][i];
  }
  printMatrix(matrix);
}

void elimnate(double matrix[SIZE][SIZE + 1]) {
  for (int i = 0; i < SIZE - 1; i++) {
    if (isSingular(matrix, i)) {
      puts("No unique solution exists.");
      return;
    }
    int argmax = columnArgMax(matrix, i);
    if (argmax != i) {
      exchangeRows(matrix, i, argmax);
    }
    for (int j = i + 1; j < SIZE; j++) {
      if (matrix[j][i] == 0) {
        continue;
      }
      subtractRows(matrix, i, j);
    }
  }
}

void backSubstitute(double matrix[SIZE][SIZE + 1], double solution[SIZE]) {
  puts("\n\\begin{equation*}");
  puts("\\begin{aligned}");
  for (int i = SIZE - 1; i >= 0; i--) {
    printf("x_%i &= \\frac{%.1f", i + 1, matrix[i][SIZE]);
    double sum = matrix[i][SIZE];
    for (int j = i + 1; j < SIZE; j++) {
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

void guass(double matrix[SIZE][SIZE + 1], double solution[SIZE]) {
  elimnate(matrix);
  if (matrix[SIZE - 1][SIZE - 1] == 0.0) {
    puts("No unique solution exists.");
    return;
  }
  puts("\nWe reached the echelon form. We start back substituting");
  backSubstitute(matrix, solution);
}

int main(int argc, char **args) {
  double matrix[SIZE][SIZE + 1] = {{0, 8, 2, -7}, {3, 5, 2, 8}, {6, 2, 8, 26}};
  printMatrix(matrix);
  double solution[SIZE];
  guass(matrix, solution);
  return 0;
}
