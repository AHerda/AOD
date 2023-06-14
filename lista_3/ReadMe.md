## Kompilacja programów źródłowych

* `make all` - kompiluje wszystkie programy
* `make dijkstra` - kompiluje jedynie program z algorytmem dijkstry
* `make dial` - kompiluje jedynie program z algorytmem dijkstry z implementacją bucket queue
* `make radix` - kompiluje jedynie program z algorytmem dijkstry z implementacją radix heap

## Używanie programów

```
./dijkstra -d <graph file> -ss <sources file> -oss <results file>
./dial -d <graph file> -ss <sources file> -oss <results file>
./radix -d <graph file> -ss <sources file> -oss <results file>

./dijkstra -d <graph file> -p2p <sources file> -op2p <results file>
./dial -d <graph file> -p2p <sources file> -op2p <results file>
./radix -d <graph file> -p2p <sources file> -op2p <results file>
```