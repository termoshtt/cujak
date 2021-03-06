# -*- coding: utf-8 -*-

import fft2d_pb2
import numpy


def _load(pb_type, filename):
    pb = pb_type()
    with open(filename, "rb") as f:
        pb.ParseFromString(f.read())
    return pb


def _load_field(filename):
    ext = filename[-2:]
    pb = {
        "ff": lambda fn: _load(fft2d_pb2.fField, fn),
        "df": lambda fn: _load(fft2d_pb2.dField, fn),
    }[ext](filename)
    return numpy.array(pb.value).reshape(pb.Nx, pb.Ny), pb.property


def _load_coef(filename):
    ext = filename[-2:]
    pb = {
        "fc": lambda fn: _load(fft2d_pb2.fCoefficient, fn),
        "dc": lambda fn: _load(fft2d_pb2.dCoefficient, fn),
    }[ext](filename)
    Nx = pb.Nx
    st = len(pb.value) // Nx
    return numpy.array([numpy.complex(c.real, c.imag)
                        for c in pb.value]).reshape(Nx, st), pb.property


def load(filename):
    """ Load binary file encoded in cujak.fft2d.pb

    Parameters
    -----------
    filename : str
        file name with extention (.ff, .fc, .df, .dc)

    Returns
    --------
    (numpy.array, cujak.fft2d.pb.Property)
        see fft2d.proto for `cujak.fft2d.pb.Property`

    """
    ext = filename[-1]
    return {
        "f": _load_field,
        "c": _load_coef,
    }[ext](filename)
