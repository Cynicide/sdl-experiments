#include <Paddle.h>

Paddle::Paddle() {

}

Paddle::Paddle(int px, int py, int vx, int vy, int _width, int _height, int _score) {
    pos.x = px;
    pos.y = py;
    vel.x = vx;
    vel.y = vy;
    width = _width;
    height = _height;
    score = _score;
}

void Paddle::Destroy() {
    scoreText.Destroy();
}

void Paddle::ResetPos(int sHeight) {
    pos.y = sHeight / 2 - height / 2;
}

void Paddle::ResetScore() {
    score = 0;
}

void Paddle::MoveUp(float dt) {
    if (pos.y > 0) 
    {
        pos.y -= vel.y * dt;
    }
}

void Paddle::MoveDown(int sHeight, float dt) {
    if (pos.y < sHeight - height) 
    {
        pos.y += vel.y * dt;
    }
}

void Paddle::Render() {
    //SDL_Log("Rendering Paddle.\n");
    SDL_RenderDrawRectF(gRenderer, &rect);
    SDL_RenderCopy(gRenderer, scoreText.texture, NULL, &scoreText.textRect);
}

void Paddle::UpdateRect() {
    rect.x = pos.x;
    rect.y = pos.y;
    rect.w = (float)width;
    rect.h = (float)height;
}