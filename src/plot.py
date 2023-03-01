import matplotlib.pyplot as plt

example_input = """
               2         4.5e-05               0           3e-06           3e-06      1.1102e-16      1.1102e-16
               4           9e-06           2e-06         3.4e-05         3.8e-05      4.7184e-16       9.992e-16
               8           5e-06           2e-06        0.000105        0.000113      1.2212e-15      5.5511e-15
              16         2.8e-05         2.2e-05        0.000727        0.000754      8.8818e-15      1.8541e-14
              32         1.8e-05        0.000426        0.012541        0.009634      4.5131e-14      9.8588e-14
              64         1.6e-05        0.001612        0.044344        0.034519      1.2967e-13      5.0671e-13
             128         3.3e-05        0.008071         0.23439         0.23121      5.4245e-13      2.6972e-12
             256        0.000138        0.062187          1.5477          1.5909      2.0446e-12      1.6866e-11  
"""

# this function receives a list of points and plots them
def plot_points(points):
    f1 = plt.figure(1)
    n = [p[0] for p in points]
    dgemm = [p[1] for p in points]
    standard = [p[2] for p in points]
    strassen = [p[3] for p in points]
    ks = [p[4] for p in points]

    strassen_n_error = [p[5] for p in points]
    ks_n_error = [p[6] for p in points]

    plt.xlabel('matrix size')
    plt.ylabel('time (s)')
    plt.plot(n, dgemm, 'ro', label='dgemm')
    plt.plot(n, standard, 'go', label='standard')
    plt.plot(n, strassen, 'bo', label='strassen')
    plt.plot(n, ks, 'b+', label='ks')
    plt.yscale('log')
    plt.legend()

    f2 = plt.figure(2)
    plt.xlabel('matrix size')
    plt.ylabel('error')
    plt.plot(n, strassen_n_error, 'bo', label='strassen')
    plt.plot(n, ks_n_error, 'b+', label='ks')
    plt.yscale('log')
    plt.legend()
    plt.show()

if __name__ == '__main__':
    # parse the input
    points = []
    for line in example_input.splitlines():
        if line.strip():
            values = list(float(v) for v in line.split())
            points.append(values)

    plot_points(points)
