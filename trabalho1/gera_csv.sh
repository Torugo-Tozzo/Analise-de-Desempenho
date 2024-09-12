gcc gera_seq.c -o gera_seq 
gcc simulacao.c -o simulacao -lm
./gera_seq 86400 > ./csv_plot/$1.csv

for i in 0.6 0.8 0.9 0.99 ; do echo $i | ./simulacao; done >> ./csv_plot/$1.csv