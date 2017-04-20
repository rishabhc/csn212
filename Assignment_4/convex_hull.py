from random import random, sample, uniform
from functools import partial
import numpy
from math import atan2, pi, fabs, sqrt, sin, cos
import matplotlib.pyplot as plt
import time

def get_points(n):
    return [(random(), random()) for _ in range(n)]

def angle(p1, p2):
    x1, y1 = p1
    x2, y2 = p2

    return atan2(y2-y1, x2-x1)

def inward(p1, p2, p3):

    x1, y1 = p1
    x2, y2 = p2
    x3, y3 = p3

    return (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1) >= 0

def draw_hull(points, hull, output, width = 2000, height = 2000):
    import cairocffi as cairo

    surface  = cairo.ImageSurface(cairo.FORMAT_RGB24, height, width)
    context = cairo.Context(surface)

    with context:
        context.set_source_rgb(1, 1, 1)
        context.paint()

    context.scale(width, -height)
    context.translate(0, -1) 
    context.set_line_width(3.0/width)

    dot_radius = 0.005

    for (x,y) in points:
        context.move_to(x, y)
        context.arc(x, y, dot_radius, 0, 2*pi)
        context.fill()

    context.new_path()
    context.move_to(*hull[0])

    for point in hull:
        context.line_to(*point)

    context.close_path()
    path = context.copy_path()

    context.set_dash([0.01, 0.01])
    context.set_source_rgb(1, 0, 0)
    context.stroke()

    context.append_path(path)

    context.set_source_rgba(0, 1, 0, 0.5)
    context.fill()

    surface.write_to_png(output)


def find_hull(points, u, v):
    # Returns hull points between u and v
    # End recursion
    if points == []:
        return points
    
    # Calculate UV vector. Find W (farthest from UV).
    uv = list(y-x for (x, y) in zip(u,v))
    w = (0, 0)
    dst = 0.0
    # If vertical
    if uv[0] == 0:
        for pts in points:
            dist = fabs(u[0] - pts[0])
            if dist >= dst:
                w = pts
                dst = dist
    # If  horizontal
    elif uv[1] == 0:
        for pts in points:
            dist = fabs(u[1] - pts[1])
            if dist >= dst:
                w = pts
                dst = dist
    else:
        # Calculate UV line's cartesian equation (ax+by+c=0)
        a = float(uv[1])/float(uv[0])
        b = -1.0
        c = u[1] - a*u[0] #i.e: y_u - (a*x_u)
        for pts in points:
            dist = fabs(a*pts[0] + b*pts[1] + c)/sqrt(a**2 + b**2)
            if dist >= dst:
                w = pts
                dst = dist
    
    # Temporary list of points without W
    tmpts = [x for x in points if x != w]

    set1 = [] #Points left of UW
    for pts in tmpts:
        if inward(u, w, pts):
            set1.append(pts)
    
    set2 = [] #Points to the left of WV
    for pts in tmpts:
        if inward(w, v, pts):
            set2.append(pts)
            
    # Recurse
    p = find_hull(set1, u, w)
    q = find_hull(set2, w, v)

    hull_rec = p
    hull_rec.append(w)
    hull_rec += q
    
    return hull_rec

def graham(points):
    min_y, min_x = min((y,x) for x,y in points)

    sorted_points = sorted(points, key = partial(angle, (min_x, min_y)))

    hull = sorted_points[:2]
    i = 2
    while i<len(sorted_points):
        point = sorted_points[i]
        while len(hull)>1 and not inward(hull[-2], hull[-1], point):
            del hull[-1]
        hull.append(point)
        i+=1
    return hull

def wrap(points):
    point = min(points)
    i = 0
    endpoint = ''
    hull = [0]

    while endpoint != hull[0]:
        if hull == [0]:
            hull[0] = point
        else:
            hull.append(point)
        endpoint = points[0]
        for j in range(1, len(points)):
            if (endpoint == point) or not inward(hull[i], endpoint, points[j]):
                endpoint = points[j]
        i += 1
        point = endpoint
    return hull

def quickHull(pts):
    if len(pts) <= 3:
        return pts
    
    a = min(pts)
    b = max(pts)

    tmpts = [p for p in pts if p != a]
    tmpts = [p for p in tmpts if p != b]
    
    left_pts = []
    right_pts = []
    
    for c in tmpts:
        if inward(a, b, c):
            left_pts.append(c)
        else:
            right_pts.append(c)
    
    # Initiate recursion
    p = find_hull(left_pts, a, b)
    q = find_hull(right_pts, b, a)
    
    # Concatenate results
    hull = [a]
    hull += p
    hull.append(b)
    hull += q
    
    return hull

def calcTime(function, *args):
    startTime = time.time()
    result = function(*args)
    return time.time() - startTime



def plotResults(points, name):

    algorithms = {'Gift wrap':wrap, 'Graham scan': graham, 'Quick hull': quickHull}
    performance = {}
    for algo in algorithms:
        performance[algo] = calcTime(draw_hull, points, algorithms[algo](points), "{}-{}.png".format(algo.replace(' ', '_'), name))
        
    print performance
    y_pos = numpy.arange(len(algorithms))
    plt.bar(y_pos, [performance[algo] for algo in performance], align='center', alpha=0.5)
    plt.xticks(y_pos, algorithms)
    plt.ylabel('Time')
    plt.title('Convex hull algorithms comparison for {}'.format(name))
    plt.show()
    #plt.savefig('{}.png'.format(name), bbox_inches='tight')

    
    

if __name__ == "__main__":

    # For total n points
    number = {100, 1000, 2000, 5000, 10000}

    for n in number:
        plotResults(get_points(n), n)

    # For 20 points, all on hull
    points_on_hull = [(0.5 + 0.5*sin(x), 0.5 + 0.5*cos(x)) for x in {uniform(0, 2*3.14) for n in range(0, 20)}]
    plotResults(points_on_hull, "all_on_hull")

    # For total 1000 points, 100 on hull
    points_on_hull = [(0.5 + 0.5*sin(x), 0.5 + 0.5*cos(x)) for x in {uniform(0, 2*3.14) for n in range(0, 100)}] + get_points(900)
    plotResults(points_on_hull, "100_on_hull")

    # Total 500 points 50 on hull
    points_on_hull = [(0.5 + 0.5*sin(x), 0.5 + 0.5*cos(x)) for x in {uniform(0, 2*3.14) for n in range(0, 50)}] + get_points(450)
    plotResults(points_on_hull, "50_on_hull")
    
