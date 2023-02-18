import matplotlib.pyplot as plt

example_input = """
            2        2e-06      1.2e-05      1.2e-05
            4        1e-06      9.1e-05      9.3e-05
            8        6e-06     0.000685     0.000656
           16      2.9e-05     0.004698     0.004709
           32     0.000219     0.032731     0.032889
           64     0.001754      0.23261      0.22935
          128      0.01347       1.5227       1.5448
          256      0.10854        10.48       10.809
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
