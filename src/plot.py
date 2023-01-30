import matplotlib.pyplot as plt

example_input = """
        2               2e-06             1.8e-05             1.5e-05
        4               1e-06            0.000154            0.000103
        8               8e-06            0.001001            0.000789
        16             3.3e-05            0.006733            0.005386
        32            0.000253             0.04709            0.038305
        64            0.001799             0.33193             0.26556
        128            0.013248              2.2849              1.8596
        256              0.1079              16.111              13.146
"""

# this function receives a list of points and plots them
def plot_points(points):
    n = [p[0] for p in points]
    standard = [p[1] for p in points]
    strassen = [p[2] for p in points]
    faster = [p[3] for p in points]

    plt.plot(n, standard, 'ro')
    plt.plot(n, strassen, 'go')
    plt.plot(n, faster, 'bo')
    plt.yscale('log')
    plt.show()


if __name__ == '__main__':
    # parse the input
    points = []
    for line in example_input.splitlines():
        if line.strip():
            n, standard, strassen, faster = line.split()
            points.append((n, float(standard), float(strassen), float(faster)))

    plot_points(points)
