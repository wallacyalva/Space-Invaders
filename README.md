# Space Invaders (Versão Console)

Jogo estilo Space Invaders desenvolvido em **C++** com interface baseada em **terminal (CMD)**.  
Este projeto foi desenvolvido em equipe, com foco na modularização do código e nas funcionalidades clássicas do gênero.

## 📦 Funcionalidades principais

- Menu principal com opções: jogar, instruções e sobre
- Impressão do mapa em formato grid, com paredes e área jogável
- Controle do jogador: movimentação lateral e disparo de projétil (1 por vez)
- Geração e movimentação de inimigos no mapa
- Colisão entre tiros e inimigos (eliminação dos inimigos)
- Feedback visual com cores (ex: inimigos destacados em vermelho)
- Redução de vida do jogador ao ser atingido por projéteis
- Fim de jogo ao perder todas as vidas
- Salvamento do score em arquivo local
- Exibição de ranking ordenado por pontuação e nome
- Limpeza do terminal ao encerrar o jogo
- Interface de ajuda com instruções básicas
- Código modular (mapa, jogador, inimigos, sistema de save etc.)

> **Nota:** A lógica de vidas e fim de jogo está implementada, mas a **HUD com número de vidas e score em tempo real** ainda será adicionada.

---

## ✅ Checklist de funcionalidades avaliativas

| Funcionalidade                                                                 | Status  |
|--------------------------------------------------------------------------------|---------|
| Nave se move corretamente lateralmente                                        | ✅       |
| Um tiro é disparado ao pressionar espaço e segue para cima, um por vez        | ✅       |
| Inimigos se movem em grupo                                                    | ❌       |
| Inimigos mudam de direção e descem ao chegar nas bordas                       | ❌       |
| Inimigos atiram projéteis                                                     | ❌       |
| Score é exibido e atualizado em tempo real                                    | ❌       |
| Jogador perde vida ao ser atingido; jogo termina ao perder todas ou vencer    | ✅       |
| Menu com instruções, score, autores e opção de jogar                          | ✅       |
| Nave e inimigos visualmente distintos                                         | ✅       |
| Jogo não pisca ou apresenta problemas visuais                                 | ✅       |
| Velocidade dos inimigos aumenta conforme quantidade diminui                   | ❌       |
| O jogo salva o score em arquivo                                               | ✅       |
| Exibição do ranking ordenado por score e nome                                 | ✅       |
| Tempo de jogo visível na tela                                                 | ❌       |
| Início com 3 vidas e exibição de vidas na tela                                | ❌       |

**Total implementado:** 8 de 15  
**Progresso:** 53%

---

## 👨‍💻 Contribuidores principais

- Erick Marlon Mafra (`Erick Mafra`)
- Rodrigo Buratto Ribas
- Wallacy Alvarenga

---

## 📁 Estrutura de diretórios (exemplo)