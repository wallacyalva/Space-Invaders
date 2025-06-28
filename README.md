# 🚀 Space Invaders (Versão Console)

Jogo inspirado no clássico **Space Invaders**, desenvolvido em **C++** com interface no **terminal (CMD)**.  
Este projeto foi feito em equipe, com foco em aprendizado, modularização e fidelidade à mecânica original.

---

## 🎮 Sobre o Jogo

O jogador controla uma nave que se move lateralmente e dispara projéteis contra ondas de inimigos. O objetivo é sobreviver, derrotar os inimigos e alcançar a maior pontuação possível.

---

## 📦 Funcionalidades principais

- Menu principal com opções: jogar, instruções e sobre
- Impressão do mapa em grid com paredes e área jogável
- Controle da nave: movimentação lateral e disparo (1 tiro por vez)
- Geração e movimentação dos inimigos no mapa
- Colisões entre tiros e inimigos (inimigos eliminados)
- Redução de vida ao ser atingido por projéteis inimigos
- Fim de jogo ao perder todas as vidas
- Exibição de **HUD com score e número de vidas**
- Feedback visual com cores (ex: inimigos em vermelho)
- Salvamento automático do score em arquivo
- Exibição de ranking ordenado por pontuação e nome
- Interface “Como jogar” com instruções básicas
- Código modular (mapa, jogador, inimigos, sistema de save etc.)
- Limpeza do terminal ao encerrar o jogo

---

## ✅ Checklist de funcionalidades avaliativas

| Funcionalidade                                                                 | Status  |
|--------------------------------------------------------------------------------|---------|
| Nave se move corretamente lateralmente                                        | ✅       |
| Um tiro é disparado ao pressionar espaço e segue para cima, um por vez        | ✅       |
| Inimigos se movem em grupo                                                    | ✅       |
| Inimigos mudam de direção e descem ao chegar nas bordas                       | ✅       |
| Inimigos atiram projéteis                                                     | ✅       |
| Score é exibido e atualizado em tempo real                                    | ✅       |
| Jogador perde vida ao ser atingido; jogo termina ao perder todas ou vencer    | ✅       |
| Menu com instruções, score, autores e opção de jogar                          | ✅       |
| Nave e inimigos visualmente distintos                                         | ✅       |
| Jogo não pisca ou apresenta problemas visuais                                 | ✅       |
| Velocidade dos inimigos aumenta conforme quantidade diminui                   | ✅       |
| O jogo salva o score em arquivo                                               | ✅       |
| Exibição do ranking ordenado por score e nome                                 | ✅       |
| Tempo de jogo visível na tela                                                 | ✅       |
| Início com 3 vidas e exibição de vidas na tela                                | ✅       |

**Total implementado:** 15 de 15  
**Progresso:** 100%

---

## 👨‍💻 Contribuidores

- **Erick Marlon Mafra** (`Erick Mafra`)
- **Rodrigo Buratto Ribas**
- **Wallacy Alvarenga**

---

## 📁 Estrutura do Projeto (exemplo)

- 2025-06-27: Save (Erick Mafra)
- 2025-06-21: 100 Scores Save (Erick Mafra)
- 2025-06-21: Define Constant speedInputUpdate and fix input dont clean (Erick Mafra)
- 2025-06-21: Fix Errors in Multiplayer (Erick Mafra)
- 2025-06-21: Add Multiplayer Keyboard And Controller (Erick Mafra)
- 2025-06-21: merge (wallacyalva)
- 2025-06-21: end game (wallacyalva)
- 2025-06-21: Bug Save Inicializador Game() (Erick Mafra)
- 2025-06-21: Corrigindo Loop Player onde a verificação tava incorreta (Erick Mafra)
- 2025-06-21: Simplificando retorno de menu e mais correções no português (Erick Mafra)
- 2025-06-21: Corrigindo o Português de macaco (Erick Mafra)
- 2025-06-21: Fix Merge error dont Have Player (Erick Mafra)
- 2025-06-21: Items falling make (Erick Marlon Mafra)
- 2025-06-21: Merge branch 'master' into Test (Erick Marlon Mafra)
- 2025-06-21: Items falling make (Erick Mafra)
- 2025-06-21: Init add Items (Erick Mafra)
- 2025-06-21: Add suport to vibration (Erick Mafra)
- 2025-06-21: Suporte a Gamepad no Player 2 (Erick Marlon Mafra)
- 2025-06-21: Suporte a Gamepad no Player 2 (Erick Mafra)
- 2025-06-21: menu dinamico 2 (wallacyalva)
- 2025-06-21: menu dinamico (wallacyalva)
- 2025-06-21: merge com a master (wallacyalva)
- 2025-06-21: Correções de bugs e inicio do multiplayer (Erick Marlon Mafra)
- 2025-06-21: Corrigindo bugs relacionados a inicialização do jogo (Erick Mafra)
- 2025-06-21: dificuldade (wallacyalva)
- 2025-06-21: Corrigindo Save (Erick Mafra)
- 2025-06-20: Add Idiot Multiplayer (Erick Mafra)
- 2025-06-20: Add Sounds and Input get Async and multiple inputs (Erick Mafra)
- 2025-06-20: Fix bug with timestamp (Erick Mafra)
- 2025-06-20: Revert "timedellay para gameElements" (Erick Mafra)
- 2025-06-16: . (Wallacy Alvarenga)
- 2025-06-16: timedellay para gameElements (6916694)
- 2025-06-15: Arrumando o exit (RodrigoBurattoRibas)
- 2025-06-15: Arrumando os Cheat (RodrigoBurattoRibas)
- 2025-06-15: sobrecarga (wallacyalva)
- 2025-06-15: timer corrigido (wallacyalva)
- 2025-06-15: inimigos perto do player jogo acaba (wallacyalva)
- 2025-06-15: inimigos perto do player jogo acaba (wallacyalva)
- 2025-06-15: Int to Short (RodrigoBurattoRibas)
- 2025-06-15: rezetando inimigos (wallacyalva)
- 2025-06-15: score (wallacyalva)
- 2025-06-15: git push (wallacyalva)
- 2025-06-15: red.me atualizado (wallacyalva)
- 2025-06-15: red.me atualizado (wallacyalva)
- 2025-06-15: ataque saindo e acertando o player (wallacyalva)
- 2025-06-14: correcao inimigo nao morre (wallacyalva)
- 2025-06-13: Commit com bug!! Correção matriz com inimigo (Erick Mafra)
- 2025-06-13: inimigos andando em vermelho (6916694)
- 2025-06-12: Update README.md (Erick Marlon Mafra)
- 2025-06-12: Update README.md (Erick Marlon Mafra)
- 2025-06-12: Merge pull request #7 from wallacyalva/addTime (Erick Marlon Mafra)
- 2025-06-12: Adding time to HUD (Erick Marlon Mafra)
- 2025-06-11: 10 points to kill enemy (Erick Mafra)
- 2025-06-11: ReadMe check update (Erick Mafra)
- 2025-06-11: Add hud Print (Erick Mafra)
- 2025-06-11: Merge branch 'master' of https://github.com/wallacyalva/Space-Invaders (Erick Mafra)
- 2025-06-11: making the score screen more beautiful (Erick Mafra)
- 2025-06-11: Atualizar o README.md (Erick Marlon Mafra)
- 2025-06-11: Add scoreboard screen (Erick Mafra)
- 2025-06-11: Add Save Score (Erick Mafra)
- 2025-06-11: Add cheats to debug and gameover screen (Erick Mafra)
- 2025-06-11: Add readme with overview (Erick Mafra)
- 2025-06-11: Fix merge errors (Erick Mafra)
- 2025-06-11: Fix merge errors (Erick Mafra)
- 2025-06-11: Fix merge errors (Erick Mafra)
- 2025-06-11: Merge pull request #6 from wallacyalva/keRKa4Gr----8-criação-dos-inimigos (Erick Marlon Mafra)
- 2025-06-11: Merge branch 'master' into keRKa4Gr----8-criação-dos-inimigos (Erick Marlon Mafra)
- 2025-06-11: Merge branch 'master' into keRKa4Gr----8-criação-dos-inimigos (Erick Marlon Mafra)
- 2025-06-11: Kill Enemies (Erick Mafra)
- 2025-06-10: inimigos aparecendo em vermelho (6916694)
- 2025-06-10: merge inimigos (6916694)
- 2025-06-10: merge master (6916694)
- 2025-06-09: Mudando a cor da parede (RodrigoBurattoRibas)
- 2025-06-09: criacao inimigos no mapa (6916694)
- 2025-06-09: Agora limpa a tela após fechar o jogo :) (RodrigoBurattoRibas)
- 2025-06-09: Fix, warning na matriz (RodrigoBurattoRibas)
- 2025-06-09: Tirando os 9 da impressão do mapa (RodrigoBurattoRibas)
- 2025-06-09: arrumando o mapa, agora está imprimindo 23[L] x 33[C] (RodrigoBurattoRibas)
- 2025-06-08: Fix. (RodrigoBurattoRibas)
- 2025-06-08: Sobre e How to play, fix (RodrigoBurattoRibas)
- 2025-06-08: Sobre e How to play (RodrigoBurattoRibas)
- 2025-06-08: Map Print (Erick Mafra)
- 2025-06-08: IDIOT FIX (Erick Mafra)
- 2025-06-08: Merge branch 'master' of https://github.com/wallacyalva/Space-Invaders (Erick Mafra)
- 2025-06-08: IDIOT FIX (Erick Mafra)
- 2025-06-08: correção Gamemap.h (Erick Marlon Mafra)
- 2025-06-08: Fix Merge map.h (Erick Mafra)
- 2025-06-08: Merge branch 'master' of https://github.com/wallacyalva/Space-Invaders (Erick Mafra)
- 2025-06-08: Algo foi mudado (Erick Mafra)
- 2025-06-08: Player add Gameloop init and shot (Erick Mafra)
- 2025-06-08: Merge pull request #5 from wallacyalva/pSOmbOzO--CriacaoMapa (Erick Marlon Mafra)
- 2025-06-08: Fix Merge map.h (Erick Mafra)
- 2025-06-08: Fix Merge map.h (Erick Mafra)
- 2025-06-08: Vendo se o Merge funciona (RodrigoBurattoRibas)
- 2025-06-08: Algo foi muito mudado (RodrigoBurattoRibas)
- 2025-06-08: Algo não foi mudado (RodrigoBurattoRibas)
- 2025-06-08: Fixes (RodrigoBurattoRibas)
- 2025-06-08: Vai diacho (RodrigoBurattoRibas)
- 2025-06-08: Teste (RodrigoBurattoRibas)
- 2025-06-08: Fix logic errors (Erick Mafra)
- 2025-06-08: Merge pull request #4 from wallacyalva/keRKa4Gr----8-criação-dos-inimigos (Erick Marlon Mafra)
- 2025-06-08: Merge pull request #3 from wallacyalva/pSOmbOzO--CriacaoMapa (Erick Marlon Mafra)
- 2025-06-08: Merge pull request #2 from wallacyalva/Menu (Erick Marlon Mafra)
- 2025-06-08: Fix options in main Menu (Erick Mafra)
- 2025-06-06: Teste, veremos se funciona (RodrigoBurattoRibas)
- 2025-06-05: Retirando mais [lixo] do código antigo... (RodrigoBurattoRibas)
- 2025-06-02: criado arquivo (Wallacy Alvarenga)
- 2025-06-02: Mexendo no mapa, iniciando a implementação (RodrigoBurattoRibas)
- 2025-06-02: codigo criado (Wallacy Alvarenga)
- 2025-06-02: Merge pull request #1 from wallacyalva/Menu (Erick Marlon Mafra)
- 2025-06-02: Main Menu Add,Have problem in options (Erick Mafra)
- 2025-05-30: first commit (6916694)- 2025-06-27: Save (Erick Mafra)
- 2025-06-21: 100 Scores Save (Erick Mafra)
- 2025-06-21: Define Constant speedInputUpdate and fix input dont clean (Erick Mafra)
- 2025-06-21: Fix Errors in Multiplayer (Erick Mafra)
- 2025-06-21: Add Multiplayer Keyboard And Controller (Erick Mafra)
- 2025-06-21: merge (wallacyalva)
- 2025-06-21: end game (wallacyalva)
- 2025-06-21: Bug Save Inicializador Game() (Erick Mafra)
- 2025-06-21: Corrigindo Loop Player onde a verificação tava incorreta (Erick Mafra)
- 2025-06-21: Simplificando retorno de menu e mais correções no português (Erick Mafra)
- 2025-06-21: Corrigindo o Português de macaco (Erick Mafra)
- 2025-06-21: Fix Merge error dont Have Player (Erick Mafra)
- 2025-06-21: Items falling make (Erick Marlon Mafra)
- 2025-06-21: Merge branch 'master' into Test (Erick Marlon Mafra)
- 2025-06-21: Items falling make (Erick Mafra)
- 2025-06-21: Init add Items (Erick Mafra)
- 2025-06-21: Add suport to vibration (Erick Mafra)
- 2025-06-21: Suporte a Gamepad no Player 2 (Erick Marlon Mafra)
- 2025-06-21: Suporte a Gamepad no Player 2 (Erick Mafra)
- 2025-06-21: menu dinamico 2 (wallacyalva)
- 2025-06-21: menu dinamico (wallacyalva)
- 2025-06-21: merge com a master (wallacyalva)
- 2025-06-21: Correções de bugs e inicio do multiplayer (Erick Marlon Mafra)
- 2025-06-21: Corrigindo bugs relacionados a inicialização do jogo (Erick Mafra)
- 2025-06-21: dificuldade (wallacyalva)
- 2025-06-21: Corrigindo Save (Erick Mafra)
- 2025-06-20: Add Idiot Multiplayer (Erick Mafra)
- 2025-06-20: Add Sounds and Input get Async and multiple inputs (Erick Mafra)
- 2025-06-20: Fix bug with timestamp (Erick Mafra)
- 2025-06-20: Revert "timedellay para gameElements" (Erick Mafra)
- 2025-06-16: . (Wallacy Alvarenga)
- 2025-06-16: timedellay para gameElements (6916694)
- 2025-06-15: Arrumando o exit (RodrigoBurattoRibas)
- 2025-06-15: Arrumando os Cheat (RodrigoBurattoRibas)
- 2025-06-15: sobrecarga (wallacyalva)
- 2025-06-15: timer corrigido (wallacyalva)
- 2025-06-15: inimigos perto do player jogo acaba (wallacyalva)
- 2025-06-15: inimigos perto do player jogo acaba (wallacyalva)
- 2025-06-15: Int to Short (RodrigoBurattoRibas)
- 2025-06-15: rezetando inimigos (wallacyalva)
- 2025-06-15: score (wallacyalva)
- 2025-06-15: git push (wallacyalva)
- 2025-06-15: red.me atualizado (wallacyalva)
- 2025-06-15: red.me atualizado (wallacyalva)
- 2025-06-15: ataque saindo e acertando o player (wallacyalva)
- 2025-06-14: correcao inimigo nao morre (wallacyalva)
- 2025-06-13: Commit com bug!! Correção matriz com inimigo (Erick Mafra)
- 2025-06-13: inimigos andando em vermelho (6916694)
- 2025-06-12: Update README.md (Erick Marlon Mafra)
- 2025-06-12: Update README.md (Erick Marlon Mafra)
- 2025-06-12: Merge pull request #7 from wallacyalva/addTime (Erick Marlon Mafra)
- 2025-06-12: Adding time to HUD (Erick Marlon Mafra)
- 2025-06-11: 10 points to kill enemy (Erick Mafra)
- 2025-06-11: ReadMe check update (Erick Mafra)
- 2025-06-11: Add hud Print (Erick Mafra)
- 2025-06-11: Merge branch 'master' of https://github.com/wallacyalva/Space-Invaders (Erick Mafra)
- 2025-06-11: making the score screen more beautiful (Erick Mafra)
- 2025-06-11: Atualizar o README.md (Erick Marlon Mafra)
- 2025-06-11: Add scoreboard screen (Erick Mafra)
- 2025-06-11: Add Save Score (Erick Mafra)
- 2025-06-11: Add cheats to debug and gameover screen (Erick Mafra)
- 2025-06-11: Add readme with overview (Erick Mafra)
- 2025-06-11: Fix merge errors (Erick Mafra)
- 2025-06-11: Fix merge errors (Erick Mafra)
- 2025-06-11: Fix merge errors (Erick Mafra)
- 2025-06-11: Merge pull request #6 from wallacyalva/keRKa4Gr----8-criação-dos-inimigos (Erick Marlon Mafra)
- 2025-06-11: Merge branch 'master' into keRKa4Gr----8-criação-dos-inimigos (Erick Marlon Mafra)
- 2025-06-11: Merge branch 'master' into keRKa4Gr----8-criação-dos-inimigos (Erick Marlon Mafra)
- 2025-06-11: Kill Enemies (Erick Mafra)
- 2025-06-10: inimigos aparecendo em vermelho (6916694)
- 2025-06-10: merge inimigos (6916694)
- 2025-06-10: merge master (6916694)
- 2025-06-09: Mudando a cor da parede (RodrigoBurattoRibas)
- 2025-06-09: criacao inimigos no mapa (6916694)
- 2025-06-09: Agora limpa a tela após fechar o jogo :) (RodrigoBurattoRibas)
- 2025-06-09: Fix, warning na matriz (RodrigoBurattoRibas)
- 2025-06-09: Tirando os 9 da impressão do mapa (RodrigoBurattoRibas)
- 2025-06-09: arrumando o mapa, agora está imprimindo 23[L] x 33[C] (RodrigoBurattoRibas)
- 2025-06-08: Fix. (RodrigoBurattoRibas)
- 2025-06-08: Sobre e How to play, fix (RodrigoBurattoRibas)
- 2025-06-08: Sobre e How to play (RodrigoBurattoRibas)
- 2025-06-08: Map Print (Erick Mafra)
- 2025-06-08: IDIOT FIX (Erick Mafra)
- 2025-06-08: Merge branch 'master' of https://github.com/wallacyalva/Space-Invaders (Erick Mafra)
- 2025-06-08: IDIOT FIX (Erick Mafra)
- 2025-06-08: correção Gamemap.h (Erick Marlon Mafra)
- 2025-06-08: Fix Merge map.h (Erick Mafra)
- 2025-06-08: Merge branch 'master' of https://github.com/wallacyalva/Space-Invaders (Erick Mafra)
- 2025-06-08: Algo foi mudado (Erick Mafra)
- 2025-06-08: Player add Gameloop init and shot (Erick Mafra)
- 2025-06-08: Merge pull request #5 from wallacyalva/pSOmbOzO--CriacaoMapa (Erick Marlon Mafra)
- 2025-06-08: Fix Merge map.h (Erick Mafra)
- 2025-06-08: Fix Merge map.h (Erick Mafra)
- 2025-06-08: Vendo se o Merge funciona (RodrigoBurattoRibas)
- 2025-06-08: Algo foi muito mudado (RodrigoBurattoRibas)
- 2025-06-08: Algo não foi mudado (RodrigoBurattoRibas)
- 2025-06-08: Fixes (RodrigoBurattoRibas)
- 2025-06-08: Vai diacho (RodrigoBurattoRibas)
- 2025-06-08: Teste (RodrigoBurattoRibas)
- 2025-06-08: Fix logic errors (Erick Mafra)
- 2025-06-08: Merge pull request #4 from wallacyalva/keRKa4Gr----8-criação-dos-inimigos (Erick Marlon Mafra)
- 2025-06-08: Merge pull request #3 from wallacyalva/pSOmbOzO--CriacaoMapa (Erick Marlon Mafra)
- 2025-06-08: Merge pull request #2 from wallacyalva/Menu (Erick Marlon Mafra)
- 2025-06-08: Fix options in main Menu (Erick Mafra)
- 2025-06-06: Teste, veremos se funciona (RodrigoBurattoRibas)
- 2025-06-05: Retirando mais [lixo] do código antigo... (RodrigoBurattoRibas)
- 2025-06-02: criado arquivo (Wallacy Alvarenga)
- 2025-06-02: Mexendo no mapa, iniciando a implementação (RodrigoBurattoRibas)
- 2025-06-02: codigo criado (Wallacy Alvarenga)
- 2025-06-02: Merge pull request #1 from wallacyalva/Menu (Erick Marlon Mafra)
- 2025-06-02: Main Menu Add,Have problem in options (Erick Mafra)
- 2025-05-30: first commit (6916694)