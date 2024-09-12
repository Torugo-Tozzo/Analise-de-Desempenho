import csv


def transpose_csv(input_file, output_file):
# Abre o arquivo de entrada e leia os dados
    with open(input_file, 'r') as infile:
        reader = csv.reader(infile)
        data = list(reader)
    
    
    # Transpõe os dados (linhas se tornam colunas)
        transposed_data = list(map(list, zip(*data)))
    
    
    # Escreve os dados transpostos em um novo arquivo CSV
    with open(output_file, 'w', newline='') as outfile:
        writer = csv.writer(outfile)
        writer.writerows(transposed_data)


# Exemplo de uso da função
if __name__ == "__main__":
    import sys


    if len(sys.argv) != 3:
        print("Uso: python script.py <arquivo_entrada.csv> <arquivo_saida.csv>")
    else:
        input_file = sys.argv[1]
        output_file = sys.argv[2]
        transpose_csv(input_file, output_file)




# python3 p.py ocupacao/oc.csv ocupacao/oc_transposto.csv
# python3 p.py en/en.csv ocupacao/en_transposto.csv
# python3 p.py ew/ew.csv ocupacao/ew_transposto.csv
# python3 p.py erro_little/erro.csv ocupacao/el_transposto.csv
