struct Hole
{
    float x,y;
    float radius;

    void Draw()
    {
        DrawCircle(x, y, radius, BLACK);
        DrawCircle(x, y, radius-2, DARKGRAY);
        DrawCircle(x-1, y-1, radius-2, BLACK);
    }
};