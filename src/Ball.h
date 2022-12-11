struct Ball
{
    float x,y;
    float speedX, speedY;
    float radius;

    void Draw()
    {
        //Texture2D ballTexture = LoadTexture("../resources/ball.png");
        DrawCircle(x+1.7, y+1.5, radius, DARKGRAY);
        DrawCircle(x, y, radius, BLACK);
        DrawCircle(x, y, radius-2, WHITE);
        //DrawTexture(ballTexture, x, y, WHITE);
    }
};