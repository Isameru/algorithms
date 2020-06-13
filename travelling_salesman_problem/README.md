
# Travelling Salesman Problem

This is my approach to this classical problem, made as a response to the challenge thrown by my bro.
The solution leaves several opens for further optimization.
It may be unoptimal for sure; I wrote it without having any prior knowledge on the problem, just for pure fun.

## Algorithm

The algorithm first plots the initial **trail** as a convex hull.
Having that, iteratively includes the enclosed points one by one, greedily extracting the one with the least **cost of inclusion**, that is the overall trail length.

After this phase all the points are a part of a single trail (loop), yet its edges may intersect with each other, which manifests sub-optimality. Therefore, several optimization phases take place, which try to swap **a pair of edges**, only if it leads to e better (shorter) trail.
