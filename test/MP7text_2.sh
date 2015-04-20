#!/bin/bash
# use predefined variables to access passed arguments
#echo arguments to the shell
echo $1 $2 ' -> echo $1 $2'

# use $# variable to print out
# number of arguments passed to the bash script
echo Number of arguments passed: $# ' -> echo Number of arguments passed: $#' 

rm rx_summary_final.txt rm tx_summary_final.txt

sed 's/0s//g' $1 >>rx_summary_100events_1.txt
sed 's/1s//g' rx_summary_100events_1.txt >> rx_summary_nostrobe.txt

sed 's/0s//g' $2 >>tx_summary_100events_1.txt
sed 's/1s//g' tx_summary_100events_1.txt >> tx_summary_nostrobe.txt

echo >> rx_summary_nostrobe.txt
echo >> rx_summary_nostrobe.txt

echo >> tx_summary_nostrobe.txt
echo >> tx_summary_nostrobe.txt

cat rx_summary_nostrobe.txt rx_summary_nostrobe.txt > rx_summary_nostrobe_concatenated.txt
cat tx_summary_nostrobe.txt tx_summary_nostrobe.txt > tx_summary_nostrobe_concatenated.txt

#grep -vwE "(Frame 0000|Frame 0001|Frame 0002|Frame 0003)" rx_summary_nostrobe_concatenated.txt > rx_summary_final.txt
mv rx_summary_nostrobe_concatenated.txt rx_summary_final.txt
mv tx_summary_nostrobe_concatenated.txt tx_summary_final.txt

rm rx_summary_100events_1.txt rx_summary_nostrobe.txt rx_summary_nostrobe_concatenated.txt tx_summary_100events_1.txt tx_summary_nostrobe.txt