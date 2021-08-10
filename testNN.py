#!/bin/env python

import sys
from math import sin
import torch
import numpy
import subgrid

#load the neural network
device = torch.device("cuda:0")
nn = subgrid.load_paper_net()
nn = nn.to(device=device)


def my_testNN(x, y):
    print(x[:10])
    x = x.reshape((1, 2, 25, 25), order='F')
    x = x.astype(numpy.float32)
    x = torch.tensor(x).to(device=device)
    with torch.no_grad():
        out = nn(x)
    out = out.cpu().numpy().astype(numpy.float64)
    out = out.flatten(order='F')
    print(out[:10])
    y[:] = out[:]
    sys.stdout.flush()



def my_test(x) :
    print(' From Python test: {}'.format(x.size))
    for i in range(x.size) :
        x[i] += 1.0

    a = torch.from_numpy(x)
    print(a)

    b = torch.from_numpy(x.astype(numpy.float32))
    print(b)

    if torch.cuda.is_available() :
        b_dev = b.cuda()
        print(b_dev)

    my_test2()

    sys.stdout.flush()
    
def my_test2() :
    print(' **** From my_test2 ****')
    return

if __name__ == '__main__':
    import numpy as np
    import torch
    x = np.arange(1, 1251).astype(numpy.float32)
    x = x / 100
    print(x[:10])
    x = x.reshape((1, 2, 25, 25), order='F')
    x = torch.tensor(x)
    x = x.to(device=device)
    with torch.no_grad():
        out = nn(x)
    out = out.cpu().numpy()
    out = out.flatten(order='F')
    print("BEGINNING OF PYTHON")
    print(out[:10])
    print("END OF PYTHON")

