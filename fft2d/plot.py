#!/usr/bin/env python
# -*- coding: utf-8 -*-

import fft2d

import numpy as np
import matplotlib.pyplot as plt
import argparse


def _load_size(prop):
    Lx = prop.Lx if prop.Lx > 0 else 1.0
    Ly = prop.Ly if prop.Ly > 0 else 1.0
    return Lx, Ly


def plot_field(filename, figure_ext):
    arr, prop = fft2d.load(filename)
    Nx, Ny = arr.shape
    Lx, Ly = _load_size(prop)
    Y, X = np.meshgrid(np.linspace(0, Ly, Ny), np.linspace(0, Lx, Nx))
    plt.pcolormesh(X, Y, arr)
    plt.colorbar()
    plt.axis("image")
    plt.savefig(filename + figure_ext)


def plot_coef(filename, figure_ext):
    arr, prop = fft2d.load(filename)
    Nx, Ny = arr.shape
    Y, X = np.meshgrid(range(Ny), range(Nx))
    plt.subplot(211)
    plt.pcolormesh(X, Y, np.real(arr))
    plt.axis("tight")
    plt.colorbar()
    plt.title("Real")
    plt.subplot(212)
    plt.pcolormesh(X, Y, np.imag(arr))
    plt.axis("tight")
    plt.colorbar()
    plt.title("Imaginary")
    plt.savefig(filename + figure_ext)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("filename")
    parser.add_argument("-e", "--extenion", default=".png")
    args = parser.parse_args()
    ext = args.filename[-1]
    figure_ext = args.extenion if args.extenion[0] == "." else "." + args.extenion
    {
        "f": plot_field,
        "c": plot_coef,
    }[ext](args.filename, figure_ext)
