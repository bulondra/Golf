struct Tile
{
    float x,y;

    Rectangle GetRect()
    {
        return Rectangle{x, y, 32, 32};
    }

    void Draw()
    {
        Texture2D tileTexture = LoadTexture("../resources/tile32_dark.png");
        DrawTexture(tileTexture, x, y, GREEN);
    }
};