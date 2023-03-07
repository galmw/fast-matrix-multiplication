import matplotlib.pyplot as plt

example_input = """
               2           4e-05           1e-06           3e-06           2e-06      1.1102e-16      1.1102e-16
               4               0           1e-06           1e-05         1.1e-05      4.7184e-16      1.1102e-15
               8           1e-06           2e-06         6.4e-05         7.3e-05      1.2212e-15      9.1038e-15
              16         1.8e-05           2e-05        0.000451        0.000497      8.8818e-15      2.1538e-14
              32           4e-06        0.000128        0.003112        0.003125      4.5131e-14        1.39e-13
              64           6e-06        0.000975        0.021851           0.022      1.2967e-13      4.9538e-13
             128         3.2e-05        0.007943         0.14462         0.15127      5.4245e-13      2.3337e-12
             256        0.000194        0.063634           1.033          1.0336      2.0446e-12      1.1775e-11
"""

input2 = """
               3         2.6e-05      1.1102e-16
               9        0.000514      1.7764e-15
              27        0.009241      1.9096e-14
              81         0.13476       1.279e-13
             243          2.7275      7.8781e-13

"""

# this function receives a list of points and plots them
def plot_points(points_power2, points_power3):
    f1 = plt.figure(1)
    n2 = [p[0] for p in points_power2]
    dgemm = [p[1] for p in points_power2]
    standard = [p[2] for p in points_power2]
    strassen = [p[3] for p in points_power2]
    ks = [p[4] for p in points_power2]

    strassen_n_error = [p[5] for p in points_power2]
    ks_n_error = [p[6] for p in points_power2]

    plt.xlabel('matrix size')
    plt.ylabel('time (s)')
    plt.plot(n2, dgemm, 'ro', label='dgemm')
    plt.plot(n2, standard, 'go', label='standard')
    plt.plot(n2, strassen, 'bo', label='strassen')
    plt.plot(n2, ks, 'b+', label='ks')

    n3 = [p[0] for p in points_power3]
    sparse = [p[1] for p in points_power3]
    sparse_n_error = [p[2] for p in points_power3]

    plt.plot(n3, sparse, 'yo', label='sparse')

    plt.yscale('log')
    plt.legend()


    f2 = plt.figure(2)
    plt.xlabel('matrix size')
    plt.ylabel('error')
    plt.plot(n2, strassen_n_error, 'bo', label='strassen')
    plt.plot(n2, ks_n_error, 'b+', label='ks')
    plt.plot(n3, sparse_n_error, 'yo', label='sparse')
    plt.yscale('log')
    plt.legend()
    plt.show()

if __name__ == '__main__':
    # parse the input
    points_power2 = []
    points_power3 = []

    for line in example_input.splitlines():
        if line.strip():
            values = list(float(v) for v in line.split())
            points_power2.append(values)

    for line in input2.splitlines():
        if line.strip():
            values = list(float(v) for v in line.split())
            points_power3.append(values)

    plot_points(points_power2, points_power3)
