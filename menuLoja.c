//loja
                    int loja=1;

                    if(IsKeyPressed(KEY_I))
                    {
                        while(loja)
                        {
                            ShowCursor();
                            Vector2 posicaoMouse={0,0};
                            posicaoMouse.x=GetMouseX();
                            posicaoMouse.y=GetMouseY();

                            int compraAzul=0;
                            int compraAmarela=0;
                            int compraVida=0;

                            if(posicaoMouse.x>=80 && posicaoMouse.x<=1780 && posicaoMouse.y>=370 && posicaoMouse.y<=440)
                                compraAzul=1;
                            if(posicaoMouse.x>=80 && posicaoMouse.x<=1780 && posicaoMouse.y>=490 && posicaoMouse.y<=560)
                                compraAmarela=1;
                            if(posicaoMouse.x>=80 && posicaoMouse.x<1780 && posicaoMouse.y>=610 && posicaoMouse.y<=680)
                                compraVida=1;
        

                            BeginDrawing();
                            ClearBackground(BLACK);
                            DrawText("loja", 750, 50, 200, BLUE);
                            DrawText("arma azul ------ +5 dano", 95, 375, 50, WHITE);
                            DrawText("40 moedas", 1500, 375, 50, WHITE);
                            DrawText("arma amarela ------ +5 dano", 95, 495, 50, WHITE);
                            DrawText("25 moedas", 1500, 495, 50, WHITE);
                            DrawText("armadura ------ +1", 95, 615, 50, WHITE);
                            DrawText("20 moedas", 1500, 615, 50, WHITE);
                            DrawText("Para SAIR aperte APAGAR", 1450, 1000, 30, WHITE);

                            if(compraAzul==1)
                            {
                                DrawRectangleLines(80, 370, 1700, 70, GRAY);
                                if(moeda>=40)
                                {
                                    if(IsKeyPressed(MOUSE_LEFT_BUTTON))
                                        aumentoDanoPistola(&modPistola, &moeda);  
                                }    
                                else DrawRectangleLines(80, 370, 1700, 70, RED);        
                            } 
                            else DrawRectangleLines(80, 370, 1700, 70, BLUE);

                            if(compraAmarela==1)
                            {
                                DrawRectangleLines(80, 490, 1700, 70, GRAY);
                                if(moeda>=25)
                                {
                                    if(IsKeyPressed(MOUSE_LEFT_BUTTON))
                                        aumentoDanoRifle(&modRifle, &moeda); 
                                }
                                else DrawRectangleLines(80, 490, 1700, 70, RED);
                            } 
                            else DrawRectangleLines(80, 490, 1700, 70, ORANGE);

                            if(compraVida==1)
                            {
                                DrawRectangleLines(80, 610, 1700, 70, GRAY);
                                if (moeda>=20)
                                {
                                    if(IsKeyPressed(MOUSE_LEFT_BUTTON))
                                        aumentoArmadura(&jogador, &moeda);
                                }     
                                else DrawRectangleLines(80, 610, 1700, 70, RED);
                            } 
                            else DrawRectangleLines(80, 610, 1700, 70, LIME);

                            DrawText(TextFormat("moedas: %i", moeda), 1500, 60, 50, YELLOW);
            
                            EndDrawing();
                        
                            if(IsKeyPressed(KEY_BACKSPACE))
                                HideCursor();
                                loja=0;
                        }
                    }