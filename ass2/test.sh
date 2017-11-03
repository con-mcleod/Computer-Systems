#!/bin/sh


if (($# != 4))
then
	echo "Usage: ./test.sh policy #pages #frames trace_file"
else
	./vmsim $1 $2 $3 < $4 > mine_out

	if (diff mine_out out-$1-$2-$3-$4.txt)
	then
		echo correct
	else
		echo not correct
	fi
fi
