#!/bin/bash

cat /data/parallel/training/europarl-v8.fi-en.fi | python uiuc-wmt15/sean/morfessor/mf-tokenizer.py /nas/data/scratch/mf-model.bin > $1
