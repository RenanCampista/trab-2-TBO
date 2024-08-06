# trab-2-TBO
O objetivo deste trabalho é aplicar o algoritmo de Dijkstra em um contexto relacionado a redes de computadores para calcular o RTT (Round Trip Time) entre servidores e clientes. O RTT é a soma dos pesos dos caminhos mínimos entre o servidor e o cliente.

## Utilização
Primeiro, é necessário compilar o programa. Para isso, execute o comando:
```bash
make
```

Após compilar, o programa pode ser executado com o comando:
```bash
./trab2 <arquivo de entrada> <arquivo de saída>
```

Onde `<arquivo de entrada>` é o arquivo contendo a descrição da rede de computadores e `<arquivo de saída>` é o arquivo onde o programa irá escrever a saída.

## Formato de entrada
O arquivo de entrada deve seguir o seguinte formato:
```plaintext
<número de vértices> <número de arestas> 
<número de servidores> <número de clientes> <número de monitores>
<servidores>
<clientes>
<monitores>
<grafo>
```

Onde:
- `<número de vértices>` é o número de vértices do grafo.
- `<número de arestas>` é o número de arestas do grafo.
- `<número de servidores>` é o número de servidores.
- `<número de clientes>` é o número de clientes.
- `<número de monitores>` é o número de monitores.
- `<servidores>` é uma lista de vértices que são servidores.
- `<clientes>` é uma lista de vértices que são clientes.
- `<monitores>` é uma lista de vértices que são monitores.
- `<grafo>` é uma lista de arestas, onde cada aresta é representada por três inteiros: `u v w`, indicando que há uma aresta de peso `w` entre os vértices `u` e `v`.
Um exemplo de entrada pode ser visto clicando [aqui](input/N10_S3_C3_M3.txt).

## Formato de saída
A saída do programa contém <número de servidores><número de clientes> linhas e três colunas. As duas primeiras colunas terão todas as combinações de servidores e clientes. Já a terceira coluna, referente ao servidor a e cliente b dever ́a ter o valor de RTT (Round Trip Time) entre o servidor a e o cliente b. O RTT ́e a soma dos pesos dos caminhos mínimos entre o servidor e o cliente.
Um exemplo de saída pode ser visto clicando [aqui](output/N10_S3_C3_M3-output.txt).