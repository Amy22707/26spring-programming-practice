import numpy as np
from scipy.optimize import linprog
import matplotlib.pyplot as plt
import os
base_dir = os.path.dirname(os.path.abspath(__file__))
tree_path = os.path.join(base_dir, "tree.txt")
with open(tree_path, "r") as f:
    img = np.array([
        [int(ch) for ch in line.strip()]
        for line in f
        if line.strip()
    ])
# print(img.shape)
x = img.flatten().astype(float)
n = len(x)
k = int(np.sum(x))
# print("k =", k)
# print("n =", n)
print("k/n =", k / n)

np.random.seed(0)
A = np.random.randn(n, n)
def recover(A_r, b_r):
    r, n = A_r.shape
    c = np.concatenate([
        np.zeros(n),
        np.ones(n)
    ])
    Aeq = np.hstack([
        A_r,
        np.zeros((r, n))
    ])
    beq = b_r
    Aub = np.vstack([
        np.hstack([
            np.eye(n),
            -np.eye(n)
        ]),
        np.hstack([
            -np.eye(n),
            -np.eye(n)
        ])
    ])
    bub = np.zeros(2 * n)
    bounds = [(None, None)] * n + [(0, None)] * n
    res = linprog(
        c,
        A_ub=Aub,
        b_ub=bub,
        A_eq=Aeq,
        b_eq=beq,
        bounds=bounds,
        method="highs"
    )
    return res.x[:n]

# 第2问
r = 600
A600 = A[:r]
b600 = A600 @ x
x600 = recover(A600, b600)
err600 = np.linalg.norm(x600 - x, 1)
print("||x600 - x||1 =", err600)

# 第3问
def error_at(r):
    Ar = A[:r]
    br = Ar @ x
    xr = recover(Ar, br)
    return np.linalg.norm(xr - x, 1)
L = 1
R = n
while L < R:
    mid = (L + R) // 2
    err = error_at(mid)
    if err <= 0.001:
        R = mid
    else:
        L = mid + 1
r_star = L
print("r* =", r_star)


# 第4问
xs = []
ys = []
for r in range(r_star - 10, r_star + 3):
    err = error_at(r)
    xs.append(r)
    ys.append(err)
plt.figure(figsize=(8,5))
plt.plot(xs, ys, marker="o")
plt.xlabel("r")
plt.ylabel("L1 Error")
plt.title("Compressive Sensing Recovery Error")
plt.grid()
plt.savefig("trend.png")
plt.show()