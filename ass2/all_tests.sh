#!/bin/sh

# usage: ./all_tests.sh

./vmsim lru 5 4 < trace1 > mine_out

if (diff mine_out out-lru-5-4-trace1.txt)
then
	echo correct
else
	echo not correct
fi



./vmsim fifo 5 4 < trace1 > mine_out

if (diff mine_out out-fifo-5-4-trace1.txt)
then
	echo correct
else
	echo not correct
fi



./vmsim lru 8 4 < trace2 > mine_out

if (diff mine_out out-lru-8-4-trace2.txt)
then
	echo correct
else
	echo not correct
fi


./vmsim fifo 8 4 < trace2 > mine_out

if (diff mine_out out-fifo-8-4-trace2.txt)
then
	echo correct
else
	echo not correct
fi