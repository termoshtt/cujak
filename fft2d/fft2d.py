# -*- coding: utf-8 -*-

import fft2d_pb2
import numpy


def _load(pb_type, filename):
    pb = pb_type()
    with open(filename, "rb") as f:
        pb.ParseFromString(f.read())
    return pb

_loader = {
    "ff": lambda fn: _load(fft2d_pb2.fField, fn),
    "fc": lambda fn: _load(fft2d_pb2.fCoefficient, fn),
    "df": lambda fn: _load(fft2d_pb2.dField, fn),
    "dc": lambda fn: _load(fft2d_pb2.dCoefficient, fn),
}


def load(filename):
    """ Load binary file encoded in cujak.fft2d.pb

    Parameters
    -----------
    filename : str
        file name with extention (.ff, .fc, .df, .dc)

    Returns
    --------
    (numpy.array, cujak.fft2d.pb.Option)

    """
    ext = filename[-2:]
    pb = _loader[ext](filename)
    return numpy.array(pb.value).reshape(pb.Nx, pb.Ny), pb.property
