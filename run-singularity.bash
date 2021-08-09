#!/bin/bash

hostname=$(hostname -s)

if [[ $hostname =~ ^g[v,r] ]]; then nv="--nv"; fi

singularity \
    exec $nv \
    --overlay /scratch/ag7531/overlay \
    /scratch/work/public/singularity/cuda11.1.1-cudnn8-devel-ubuntu20.04.sif \
    /bin/bash


    
