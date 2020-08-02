<p align="center">
  <img src="https://res.cloudinary.com/dqqh1oigi/image/upload/v1596382616/bomberman_jza1y3.png" 
       width="180"/> </br>
</p>

<h3 align="center">
  Bomberman: Battle Mode
</h3>

<p align="center">
  <a href="#Introdução-memo"> Introdução </a>
   | 
  <a href="#Visualização-mag"> Visualização </a>
   | 
  <a href="#Execução-rocket"> Execução </a>
   | 
  <a href="#Tecnologias-computer"> Tecnologias </a>
</p>

## Introdução :memo:

Este projeto foi motivado pelo trabalho final da disciplina Computação Gráfica e consiste na implementação do Battle Mode do 
famoso e clássico jogo Bomberman. Foi implementado o primeiro cenário do game, com dois personagens jogáveis. O player 1 se 
movimenta através das teclas WASD e o player 2 através das teclas de direção.

Este projeto encontra-se dividido em 4 pastas:

<p>
  <ol>
    <li> Battle Game: implementação do modo batalha; </li>
    <li> Bomba: implementação gráfica da bomba; </li>
    <li> Character: implementação gráfica dos dois personagens; </li>
    <li> Textures: arquivos de textura utilizados nas implementações. </li>
  </ol>
</p>

## Visualização :mag:

O Battle Mode é um modo de jogo que consiste na batalha entre dois ou mais players, que devem tentar derrotar um ao outro. Para garantir a 
distinção entre os dois jogadores, foram implementados dois personagens. O primeiro deles, disposto na Figura 01, apresenta o personagem 
jogável do player 1:

<h6 align="center"> Figura 01 - Player 1 </h6>
<p align="center">
  <img src="https://res.cloudinary.com/dqqh1oigi/image/upload/v1592168587/Boneco_ufojuf.gif"
       width="300"/> </br>
</p>

O segundo personagem, que representa o player 2, é apresentado na Figura 02:

<h6 align="center"> Figura 02 - Player 2 </h6>
<p align="center">
  <img src="https://res.cloudinary.com/dqqh1oigi/image/upload/v1592168587/Player2_gk5lki.gif" 
       width="300"/> </br>
</p>

O cenário foi implementado de acordo com os moldes do Battle Mode do Bomberman, utilizando dois tipos de texturas capazes 
de diferenciar um obstáculo quebrável (tijolos) e um obstáculo fixo (bloco metálico). Na implementação do cenário, foi utilizada 
também uma terceira textura, para representar o chão (piso cinza):

<h6 align="center"> Figura 03 - Cenário </h6>
<p align="center">
  <img src="https://res.cloudinary.com/dqqh1oigi/image/upload/v1592168587/Cen%C3%A1rio_xh4wdp.png" /> </br>
</p>

Um outro aspecto que merece destaque em relação aos cenários é que a cada nova partida iniciada, os obstáculos quebráveis 
(blocos de tijolo) são dispostos no cenário de forma aleatória - compare as Figuras 03 e 04 para notar as diferenças: 

<h6 align="center"> Figura 04 - Aleatoriedade de obstáculos do cenário </h6>
<p align="center">
  <img src="https://res.cloudinary.com/dqqh1oigi/image/upload/v1592168587/Cen%C3%A1rio1.1_g5wnrn.png" /> </br>
</p>

Para atingir o grau máximo de semelhança do Battle Mode, os players foram dispostos em duas extremidades opostas, conforme 
aponta a Figura 05:

<h6 align="center"> Figura 05 - Disposição dos players </h6>
<p align="center">
  <img src="https://res.cloudinary.com/dqqh1oigi/image/upload/v1592168587/Cen%C3%A1rio2_mquhbx.png" /> </br>
</p>

A Figura 06 apresenta a movimentação do personagem pelo cenário. Note que além do respeito aos obstáculos (é impossível atravessá-lo), 
o personagem realiza rotações em torno do seu eixo para dar mais dinamicidade ao jogo:

<h6 align="center"> Figura 06 - Movimentação pelo cenário </h6>
<p align="center">
  <img src="https://res.cloudinary.com/dqqh1oigi/image/upload/v1592168587/Movimento2_qwc9wd.gif" /> </br>
</p>

## Execução :rocket:

Para executar o Battle Mode, siga as instruções:

<p>
  <ol>
    <li> Siga as instruções de instalação do OpenGL no link apresentado na seção Tecnologias; </li>
    <li> Abra a pasta Battle Game e execute o arquivo main.cpp </li>
  </ol>
</p>

## Tecnologias :computer:

Este projeto foi desenvolvido com a seguinte tecnologia:

- [OpenGL](https://www.opengl.org/)


