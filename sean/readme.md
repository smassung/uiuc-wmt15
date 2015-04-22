# Plans

- create different sized baselines
- Sean: preprocess Finnish data in different ways
 * hard stem
 * morphological segmenter
 * character translation
- standardize LM, train, dev, test sets? (per language?)
- translate into Finnish: recombine split output

# Morfessor

Investigate the following two parameters?

- Morph length (--morph-length) The corpusweight is tuned so that the average
  length of morphs in the lexicon will be as desired
- Num morph types (--num-morph-types) The corpusweight is tuned so that there
  will be approximate the number of desired morph types in the lexicon

[Not promising results](http://www.aclweb.org/anthology/W10-1729) with Morfessor
segmentation

# TO DO

-   baseline with larger maximum phrase size (8 and 10)
- x MF europarl default training with 10 MFS
- x set alpha to 1 for training
- x set alpha to 0.5 for training
- x train on finnish word list

```
morfessor-train wordlist-2010.fin --traindata-list --encoding=ISO_8859-1 -s mf-model-fin-wordlist.bin
```

# Experiments

## Small baseline

Small baseline has 10k training pairs and 1k dev pairs. 700MB LM.

- config: small-baseline.config
- time: ~50 min
- eval

```
test: 7.00 (0.957) BLEU-c ; 7.17 (0.957) BLEU
```

## Medium baseline

Medium has full training and full dev. 700MB LM.

- config: medium-baseline.config
- time: ~5 hours
- eval

```
test: 13.65 (0.923) BLEU-c ; 14.27 (0.923) BLEU
```

- with phrase size 8
```
test: 12.88 (0.920) BLEU-c ; 13.55 (0.920) BLEU
```

- with phrase size 5 and gigaword LM 6-gram
```
test: 12.52 (0.915) BLEU-c ; 13.54 (0.915) BLEU
```
- with phrase size 5 and gigaword LM 5-gram
```
test: 12.33 (0.883) BLEU-c ; 13.37 (0.883) BLEU
```

## Small Hard Stemming

- config: small-hard.config
- time: ~40 min
- eval

```
test: 4.04 (0.696) BLEU-c ; 5.13 (0.696) BLEU
```

## Small Hybrid Tokenization

- config: small-hybrid.config
- time: ~2.5 hours
- notes: changed max phrase size to 10 (from 5). It looks like character-based
  translation is not going to be possible due to the runtime. Bad performance
  anyway.
- eval

```
test: 2.16 (0.913) BLEU-c ; 3.37 (0.913) BLEU
```

## Small Morfessor 2.0 Tokenization

- config: small-mf.config
- time: ~1 hour
- notes: set max phrase size to 6 since words are split; ONLY TRAINED MF ON
  SMALL DATASET
-eval

```
test: 5.07 (1.167) BLEU-c ; 5.23 (1.167) BLEU
```

## Medium Morfessor 2.0

- config: medium-mf.config
- time:
- notes: MFS 6; TRAIN MF ON FULL EUROPARL
- eval

test: 10.97 (0.922) BLEU-c ; 11.82 (0.922) BLEU

- MFS 8
test: 11.76 (0.933) BLEU-c ; 12.66 (0.933) BLEU

- MFS 10
test: 11.44 (0.923) BLEU-c ; 12.36 (0.923) BLEU

- MFS 8, alpha=0.5
test: 11.99 (0.945) BLEU-c ; 12.66 (0.945) BLEU

- MFS 8, alpha=1.0
test: 11.73 (0.934) BLEU-c ; 12.42 (0.934) BLEU

- MFS 8, finnish word list
test: 11.85 (0.948) BLEU-c ; 13.35 (0.948) BLEU

- MFS 9 finnish word list
test: 11.39 (0.934) BLEU-c ; 12.60 (0.934) BLEU
