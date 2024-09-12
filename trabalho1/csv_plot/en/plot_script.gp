# Define os tamanhos das margens dos gráficos
set tmargin 4
set bmargin 4
set rmargin 7
set lmargin 10
set grid
show grid

# Define o tamanho do gráfico
set terminal png size 2048,1152 enhanced font "Arial, 32"

# Define o caminho e o nome do arquivo de saída
set output 'en.png'

# Define o titulo e os nomes dos eixos no gráfico
set title "Comportamento da taxa de ocupação [E[N]] em relação ao tempo" font "Arial, 32"
set xlabel "Tempo (s)" font "Arial, 24"
set ylabel "E[N]" font "Arial, 24"

# Define a escala dos eixos
set xtics 0, 86400, 864000 font "Arial, 18"
set ytics 0, 25, 225 font "Arial, 18"
set y2tics 0, 25, 225 font "Arial, 18"

# Espelhar eixo Y
set y2tics mirror

# Define a posição e legenda do gráfico
set key at 860000, 30 font "Arial, 24" right bottom

# set axis x, y 
# set xrange [0:864000]
set yrange [0:234]
set y2range [0:235]

# Define os dados a serem lidos do arquivo
datafile = "en_transposto.csv"

# Define as cores das curvas
set style line 1 lc rgb "#6a3d9a" lw 4
set style line 2 lc rgb "#33a02c" lw 4
set style line 3 lc rgb "#1f78b4" lw 4
set style line 4 lc rgb "#ff7f00" lw 4

# Define os rótulos das colunas
set datafile separator ","
plot datafile using 1:2 with lines ls 1 title "60%", \
     datafile using 1:3 with lines ls 2 title "80%", \
     datafile using 1:4 with lines ls 3 title "90%", \
     datafile using 1:5 with lines ls 4 title "99%"
