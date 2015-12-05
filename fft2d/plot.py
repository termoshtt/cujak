#!/usr/bin/env python
# -*- coding: utf-8 -*-

import fft2d

import numpy as np
import matplotlib.pyplot as plt
import argparse


def main(args):
    arr, prop = fft2d.load(args.filename)
    Nx, Ny = arr.shape
    Lx = prop.Lx if prop.Lx > 0 else 1.0
    Ly = prop.Ly if prop.Ly > 0 else 1.0
    X, Y = np.meshgrid(np.linspace(0, Ly, Ny), np.linspace(0, Lx, Nx))
    plt.pcolormesh(X, Y, arr)
    plt.colorbar()
    plt.axis("image")
    ext = args.extenion if args.extenion[0] == "." else "." + args.extenion
    plt.savefig(args.filename + ext)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("filename")
    parser.add_argument("-e", "--extenion", default=".png")
    args = parser.parse_args()
    main(args)
