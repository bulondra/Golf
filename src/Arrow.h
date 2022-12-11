struct Arrow
{
    float x,y;
    float endX,endY;
    float angle;

    void Draw()
    {
        //Texture2D arrowTexture = LoadTexture("../resources/point.png");
        DrawLine(x, y, endX, endY, BLACK);
        //DrawTextureEx(arrowTexture, Vector2{x, y}, angle, 1, WHITE);
    }


};