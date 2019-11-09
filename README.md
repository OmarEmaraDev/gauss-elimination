# Gauss Elimination

A program to solve systems of linear equations using Gauss Elimination
with detailed steps. The solution is printed to standard output in LaTeX.

## Usage

The first argument is an integer representing the number of unknowns `N`.
The next `N * (N + 1)` decimals represents the values of the augmented
matrix in row-major order.

### Example

To solve the system represented using the following augmented matrix:

```latex
\begin{bmatrix}
0 & 8 & 2 & -7 \\
3 & 5 & 2 & 8 \\
6 & 2 & 8 & 26 \\
\end{bmatrix}
```

We execute:

```cmd
gauss 3 0 8 2 -7 3 5 2 8 6 2 8 26
```

Which outputs:

```latex
\begin{equation*}
\begin{aligned}
R_1 &\Longleftrightarrow R_3
&&\qquad
\begin{bmatrix}
6 & 2 & 8 & 26 \\
3 & 5 & 2 & 8 \\
0 & 8 & 2 & -7 \\
\end{bmatrix}
\\
R_2 &\Longleftarrow R_2 - 0.5 R_1
&&\qquad
\begin{bmatrix}
6 & 2 & 8 & 26 \\
0 & 4 & -2 & -5 \\
0 & 8 & 2 & -7 \\
\end{bmatrix}
\\
R_2 &\Longleftrightarrow R_3
&&\qquad
\begin{bmatrix}
6 & 2 & 8 & 26 \\
0 & 8 & 2 & -7 \\
0 & 4 & -2 & -5 \\
\end{bmatrix}
\\
R_3 &\Longleftarrow R_3 - 0.5 R_2
&&\qquad
\begin{bmatrix}
6 & 2 & 8 & 26 \\
0 & 8 & 2 & -7 \\
0 & 0 & -3 & -1.5 \\
\end{bmatrix}
\\
\end{aligned}
\end{equation*}

We start back substituting.

\begin{equation*}
\begin{aligned}
x_3 &= \frac{-1.5}{-3} = 0.5 \\
x_2 &= \frac{-7 - 2 x_3}{8} = -1 \\
x_1 &= \frac{26 - 2 x_2 - 8 x_3}{6} = 4 \\
\end{aligned}
\end{equation*}
```
