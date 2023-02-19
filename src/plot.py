import matplotlib.pyplot as plt

example_input = """
            2      3.8e-05        1e-06        3e-06    
            4        2e-06        1e-06        2e-05      
            8            0        3e-06     0.000121      
           16        8e-06      1.8e-05     0.000855     
           32        3e-06     0.000145     0.006133     
           64        8e-06     0.001004     0.041283      
          128      2.9e-05     0.007761      0.28759      
          256      0.00016     0.062289       1.9759   
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
            n, dgemm, standard, strassen = line.split()
            points.append((n, float(dgemm), float(standard), float(strassen)))

    plot_points(points)
