import matplotlib.pyplot as plt

example_input = """
2		6e-06		             2.8e-05
4		4e-06		            0.000159
8		1.3e-05		            0.001141
16		3.9e-05		            0.007756
32		0.000235		             0.05441
64		0.001787		             0.38294
128		0.013578		              2.6604
256		0.1107		              18.702
"""

# this function receives a list of points and plots them
def plot_points(points):
    n = [p[0] for p in points]
    standard = [p[1] for p in points]
    fast = [p[2] for p in points]
    plt.plot(n, standard, 'ro')
    plt.plot(n, fast, 'bo')
    plt.yscale('log')
    plt.show()


if __name__ == '__main__':
    # parse the input
    points = []
    for line in example_input.splitlines():
        if line.strip():
            n, x, y = line.split()
            points.append((n, float(x), float(y)))

    plot_points(points)
