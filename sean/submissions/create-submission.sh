#!/bin/bash
echo "Truecased output: $1"
echo "Saving SGM as: $2.sgm"
/opt/moses/scripts/tokenizer/deescape-special-chars.perl < $1 > tmpout
/opt/moses/scripts/tokenizer/detokenizer.perl -q -l en < tmpout > tmpout2
/opt/moses/scripts/ems/support/wrap-xml.perl en /data/parallel/test/newstest2015-fien-src.fi.sgm UIUC < tmpout2 > $2.sgm
rm tmpout tmpout2
