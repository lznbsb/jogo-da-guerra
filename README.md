 Jogo da Guerra (em C)

Descrição
Este é um jogo de cartas baseado no clássico "Guerra". Dois jogadores se enfrentam comparando cartas, e quem tiver a carta de maior valor vence a rodada.

Regras
- Cada jogador recebe metade do baralho (26 cartas).
- Em cada rodada, ambos jogam uma carta.
- Quem tiver a carta de maior valor ganha 1 ponto.
- No final das 26 rodadas, vence quem tiver mais pontos.

Compilação e Execução

 Compilar:
```bash
gcc guerra.c -o guerra
```

 Executar:
```bash
./guerra
```

 Interface
- Exclusivamente via terminal.
- Menu com opções:
  - Iniciar novo jogo
  - Ver placar (carregado de `placar.txt`)
  - Sair
 Estrutura do Código
- `guerra.c`: código principal
- `placar.txt`: arquivo gerado automaticamente com resultados das partidas

Autor(es):Luiz Carlos, Guilherme Andrade, Yuri da Costa, Myguel Arcanjo, Icaro de Oliveira
