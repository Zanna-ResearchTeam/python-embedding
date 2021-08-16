# python-embedding

This adapt Shenlong's version to be able to call the nn on an array of fixed shape.
We replace test.py by testNN.py and in particular we call the function my_testNN(x, y),
where x is the input, and y is the array where the output will be stored.

At the moment both the input and output must have a fixed size. In Fortran they are flat,
reshaping of the input happens in python code. Similarly the ouput is flattenned (in Fortran order)
before being copied to y's memory. 

To run the code with the nn you also need to 
- create a conda environment using the provided environment.yaml
- download the subgrid package (where the structure of the nn is defined) from Laure's repository and add /mypath/ to your PYTHONPATH if subgrid is in /mypath/
The package can be found here: https://github.com/Zanna-ResearchTeam/subgrid 
- You will also need to update the MakeFile to put the correct paths for python and numpy


LZ comment Aug 13: The weights for the network are saved in 2 different files:  
- ... has the weights from all layers, but the last one
-  ... has the weights for the last layer. 
