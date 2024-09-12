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
set output 'erro_little.png'

# Define o titulo e os nomes dos eixos no gráfico
set title "Erro de Little (Exibindo 4 casos)" font "Arial, 32"
set xlabel "Tempo (s)" font "Arial, 32" offset 0
set ylabel "Erro de Little" font "Arial, 32" offset -1.5

# Define a escala dos eixos
set xtics 0, 86400, 864000 font "Arial, 18"
set ytics -0.00000003, 0.00000003, 0.000003 font "Arial, 18"  # Limite inferior e superior definidos proporcionalmente
set y2tics -0.00000003, 0.00000003, 0.000003 font "Arial, 18"  # Limite inferior e superior definidos proporcionalmente

# Espelhar eixo Y
set y2tics mirror

# Define a posição e legenda do gráfico
set key at 135000, 0.000000295 font "Arial, 24"

# set axis x, y 
set xrange [0:864000]
set yrange [-0.00000003:0.0000003]  # Limite inferior e superior definidos proporcionalmente
set y2range [-0.00000003:0.0000003]  # Limite inferior e superior definidos proporcionalmente



# Define os dados a serem lidos do arquivo
datafile = "erro_transposto.csv"

# Define as cores das curvas
set style line 1 lt rgb "#000000" lw 4
set style line 2 lt rgb "#33a02c" lw 4
set style line 3 lt rgb "#1f78b4" lw 4
set style line 4 lt rgb "#ff7f00" lw 4

# Define os rótulos das colunas
set datafile separator ","
plot datafile using 1:2 with lines lw 4 title columnhead(2), \
     datafile using 1:3 with lines lw 4 title columnhead(3), \
     datafile using 1:4 with lines lw 4 title columnhead(4), \
     datafile using 1:5 with lines lw 4 title columnhead(5)
