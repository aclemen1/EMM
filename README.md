# The Eilenberg-MacLane machine (EMM)

The Eilenberg-MacLane machine (EMM) is a program which computes the integral (co)homology groups of $1$-connected Eilenberg-MacLane spaces of the form $K(Z/2^s,n)$. 

This version, written in C++, is based on the results of my PhD thesis ([Integral Cohomology of Finite Postnikov Towers](https://github.com/aclemen1/integral-cohomology-of-finite-postnikov-towers/blob/master/main.pdf), see Appendix B, pp. 87-89).

## Get a container image of the EMM

You can pull an image from Docker Hub

```
docker pull aclemen1/emm
```

or build from Dockerfile and source

```
docker build -t aclemen1/emm .
```

## Start the EMM
```
docker run -it --rm aclemen1/emm
```

## Run the EMM with parameters
```
docker run -it --rm aclemen1/emm ./emm [s] [n] [range]
```
