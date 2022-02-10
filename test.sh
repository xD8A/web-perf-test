#!/bin/bash

atop -PCPU,MEM,DSK,NET 1 > ./atop.log&
atop_pid=$!
n=${1:-100000}
echo "N=$n" | tee ./test.cfg
#{ time seq 1 $n | xargs -I % -P 4 curl -s -X POST -H 'Content-Type: application/json' --data '{"question_id":1,"answer":"42"}' http://localhost:5000 | grep -oP '"id":\s*\K\d+'; } 2> ./time.log
{ time seq 1 $n | xargs -I % -P 4 curl -s -X POST -H 'Content-Type: application/json' --data '{"question_id":1,"answer":"42"}' http://localhost:5000/answer 1>/dev/null 2>&1; } 2> ./time.log
kill $atop_pid
curl http://localhost:5000/answer
