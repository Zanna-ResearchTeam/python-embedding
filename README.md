# python-embedding

This adapt Shenlong's version to be able to call the nn on an array of fixed shape.
We replace test.py by testNN.py and in particular we call the function my_testNN(x, y),
where x is the input, and y is the array where the output will be stored.

At the moment both the input and output must have a fixed size. In Fortran they are flat,
reshaping of the input happens in python code. Similarly the ouput is flattenned (in Fortran order)
before being copied to y's memory. 

