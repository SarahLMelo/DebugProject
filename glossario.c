#include <raylib.h>

void inimigos(Texture2D libelulaverde, Texture2D libelulaamarela, Texture2D libelulavermelha, Texture2D esqueletoimg)
{

    char sintaxe[] = "ERRO DE SINTAXE";
    char descsintaxe[] = "O bug menos danoso. Graças ao trabalho\ndos compiladores, é cada vez mais raro sua\nsobrevivência nos códigos atuais. Mas não\nse engane: graças a sua alta mobilidade, é\nfácil perdê-lo de vista. Portanto, tenha\ndestreza com a sua mira caso veja este bug.";

    char execucao[] = "ERRO DE EXECUÇÃO";
    char descexecucao[] = "Será que todas as variáveis foram manipu-\nladas corretamente? Nerdola deve ter cuidado\nao ver esse bug, pois ele é mais difícil de derter\nque o erro de sintaxe por que vida é maior,\nalém de causar muito mais dano ao código.\nNunca perca esse bug de vista!";

    char logica[] = "ERRO DE LÓGICA";
    char desclogica[] = "Um dos bugs mais perigosos, causando es-\ntrago nos mais diferentes códigos. Sacrifica\nmobilidade para ter um dano e resistência\nmuito maior que os outros bugs normais,\n por isso tenha cautela ao ver este bug.\nFaça os tiros valerem a pena.";
    //
    char vazamento[] = "VAZAMENTO DE MEMÓRIA";
    char descvazamento[] = "O bug mais temido de todo programador.\nO vazamento de memória é o maior inimigo de\nNerdola na sua prova de Introdução a Programação.\nPor ser tão letal como nenhum outro bug, Nerdola\ndeve manipular o free e alocar memória corretamente.\nSendo o bug mais difícil de lidar por seu alto poder\ndestrutivo, é considerado o Chefão de todos os bugs.";

    DrawText(sintaxe, 70, 230, 25, DARKGREEN);
    DrawTexture(libelulaverde, 70, 245, WHITE);
    DrawText(descsintaxe, 210, 280, 20, LIGHTGRAY);

    DrawText(execucao, 665, 230, 25, YELLOW);
    DrawTexture(libelulaamarela, 665, 265, WHITE);
    DrawText(descexecucao, 815, 280, 20, LIGHTGRAY);

    DrawText(logica, 70, 480, 25, RED);
    DrawTexture(libelulavermelha, 70, 510, WHITE);
    DrawText(desclogica, 210, 530, 20, LIGHTGRAY);

    DrawText(vazamento, 665, 480, 25, DARKBROWN);
    DrawTexture(esqueletoimg, 630, 510, WHITE);
    DrawText(descvazamento, 805, 530, 20, LIGHTGRAY);
}

void formas(Texture2D formaazul, Texture2D formaamarela)
{

    char forma1[] = "Forma Recursiva";
    char forma2[] = "Forma Iterativa";
    char descforma1[] = "Nessa forma, Nerdola abdica de um pouco de velocidade para melhorar seu dano. Assim como a recursividade,\na forma azul é um artificio poderoso, porém deve ser usado com cautela devido ao possível malefício que\n podem trazer, afinal de contas não é tão bom perder velocidade e ficar suscetível a um dos possíveis bugs.";
    char descforma2[] = "Assim como a iteração possibilita velocidade e otimização a um codigo, a forma iterativa oferece mais possibi-\nlidade ao Nerdola, facilitando o personagem a desviar e correr dos inimigos com mais tranquilidade,\nenquanto atira. Ideal para jogadores que não querem correr risco, pois apesar de ser bastante segura,\né efetivamente menos danoso que a forma recursiva.";

    DrawText(forma1, 65, 250, 25, BLUE);
    DrawTexture(formaazul, 70, 285, WHITE);
    DrawText(descforma1, 220, 320, 20, LIGHTGRAY);

    DrawText(forma2, 65, 470, 25, ORANGE);
    DrawTexture(formaamarela, 70, 495, WHITE);
    DrawText(descforma2, 220, 530, 20, LIGHTGRAY);
}

void lore()
{

    const char historia[] = "Como outro dia qualquer um estudante de Engenharia da Computação da Universidade Federal de Pernambuco tem uma\nmissão a cumprir: fazer sua prova de Introdução a Programação, disciplina ministrada pelo professor Alexandre\nCabral Mota, compilar para tirar a nota máximada prova e conseguir seguir para o próximo período.\n\nEntretanto, dois enormes problemas aparecem em seu sistema: os bugs e o maior inimigo de todo novato da\nlinguagem C, o temido vazamento de memória. Nerdola deve de acordo com suas habilidades adquiridas pelo Juiz,\npopularmente conhecido como The Huxley, eliminar todos os bugs existentes e derrotar o maior perigo ao seu código,\nresponsável pela morte de milhões de memórias ram por todo o globo terrestre.\n\nÉ sabido que esse é um desafio em tanto, mas Nerdola tem um grande aliado ao seu lado, que é todo o conhecimento\nadquirido pela monitoria de IP, os guardiões da boa prática de programação durante todo o curso. É fato que a\nhumanidade depende de Nerdola e seus dedos ágeis, mas será que ele fará o suficiente para o seu código compilar?\nBem, isso só você jogador pode responder. A aventura de Nerdola pode trazer alegria ou pode trazer medo, nesse\ncaso abrace o que quer que ela traga.";

    DrawText(historia, 65, 250, 20, LIGHTGRAY);
}

int mostrarGlossario(
    Texture2D botaoLore,
    Texture2D botaoInimigos,
    Texture2D botaoFormas,
    Texture2D botaoVoltar,
    Texture2D libelulaverde,
    Texture2D libelulaamarela,
    Texture2D libelulavermelha,
    Texture2D esqueletoimg,
    Texture2D formaazul,
    Texture2D formaamarela)
{

    //ToggleFullscreen();
    Camera2D menu;
    menu.zoom = GetScreenWidth() / 1366.0f;
    menu.target = (Vector2){0.0f, 0.0f};
    menu.offset = (Vector2){0.0f, 0.0f};
    menu.rotation = 0.0f;

    const char titulo[] = "GLOSSÁRIO";

    Vector2 posicaoMouse = {0.0f, 0.0f};
    int sair = 1;
    int mousebotaoLore = 0;
    int mousebotaoFormas = 0;
    int mousebotaoInimigos = 0;
    posicaoMouse.x = GetMouseX();
    posicaoMouse.y = GetMouseY();
    double p = GetScreenWidth() / (double)1366;
    SetMouseScale(1 / p, 1 / p);
    Rectangle mouse = {(float)posicaoMouse.x, (float)posicaoMouse.y, 20, 20};
    SetTargetFPS(60);
    //posicao do mause

    //CHECANDO O MOUSE
    if (posicaoMouse.x >= 130 && posicaoMouse.x <= 430 && posicaoMouse.y >= 120 && posicaoMouse.y <= 220)
    {
        mousebotaoLore = 1;
    }
    else
        mousebotaoLore = 0;

    if (posicaoMouse.x >= 530 && posicaoMouse.x <= 830 && posicaoMouse.y >= 120 && posicaoMouse.y <= 220)
    {
        mousebotaoFormas = 1;
    }
    else
        mousebotaoFormas = 0;

    if (posicaoMouse.x >= 930 && posicaoMouse.x <= 1230 && posicaoMouse.y >= 120 && posicaoMouse.y <= 220)
    {
        mousebotaoInimigos = 1;
    }
    else
        mousebotaoInimigos = 0;

    int abrirLore = 0;
    int abrirFormas = 0;
    int abrirInimigos = 0;

    BeginDrawing();
    BeginMode2D(menu);
    //DrawRectangleRec(mouse, PINK);
    ClearBackground(BLACK);
    DrawText(titulo, 460, 20, 75, DARKGREEN); // 0 (x), 0 (y) = cant.sup.esq.
    if (mousebotaoLore)
    {
        DrawTexture(botaoLore, 130, 105, WHITE);
        DrawTexture(botaoFormas, 530, 105, DARKGREEN);
        DrawTexture(botaoInimigos, 930, 105, DARKGREEN);
    }
    else if (mousebotaoFormas)
    {
        DrawTexture(botaoLore, 130, 105, DARKGREEN);
        DrawTexture(botaoFormas, 530, 105, WHITE);
        DrawTexture(botaoInimigos, 930, 105, DARKGREEN);
    }
    else if (mousebotaoInimigos)
    {
        DrawTexture(botaoLore, 130, 105, DARKGREEN);
        DrawTexture(botaoFormas, 530, 105, DARKGREEN);
        DrawTexture(botaoInimigos, 930, 105, WHITE);
    }
    else
    {
        DrawTexture(botaoLore, 130, 105, DARKGREEN);
        DrawTexture(botaoFormas, 530, 105, DARKGREEN);
        DrawTexture(botaoInimigos, 930, 105, DARKGREEN);
    }

    if (mousebotaoLore)
    {
        abrirLore = 1;
        if (abrirLore)
        {
            lore();
            if (!mousebotaoLore)
            {
                abrirLore = 0;
            }
        }
    }
    else if (mousebotaoFormas)
    {
        abrirFormas = 1;
        if (abrirFormas == 1)
        {
            formas(formaazul, formaamarela);
        }
    }

    else if (mousebotaoInimigos)
    {
        abrirInimigos = 1;
        if (abrirInimigos == 1)
        {
            inimigos(libelulaverde, libelulaamarela, libelulavermelha, esqueletoimg);
        }
    }

    EndDrawing();
    EndMode2D();
}
