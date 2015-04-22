#!/bin/bash
ls $1/*.gz | xargs -I% python parser.py %
rm $1/*.gz
ls $1/*.paragraphs | xargs -I% ./sentence-writer %
rm $1/*.paragraphs
