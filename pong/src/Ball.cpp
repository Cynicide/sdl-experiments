
#include <Ball.h>

Ball::Ball() {

}

Ball::Ball(int px, int py, int vx, int vy, int _width, int _height) {
    pos.x = px;
    pos.y = py;
    vel.x = vx;
    vel.y = vy;
    width = _width;
    height = _height;
}

void Ball::Move() {
    pos.x += vel.x;
    pos.y += vel.y;

    rect.x = pos.x;
    rect.y = pos.y;
    rect.w = width;
    rect.h = height;
}

void Ball::RandSetBallVelocity() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> speed(3.0, 3.5);
    std::uniform_int_distribution<int> direction(0, 1);

    vel.x = speed(gen);
    vel.y = speed(gen);

    if (direction(gen) == 1) {
        vel.x = vel.x * -1; 
    }

    if (direction(gen) == 1) {
        vel.y = vel.y * -1; 
    }
}

void Ball::ResetVel() {
    current_vel = starting_vel;
    vel.x = current_vel;
    vel.y = current_vel;
}

void Ball::ResetPosition(int sWidth, int sHeight) {
    pos.x = sWidth / 2;
    pos.y = sHeight / 2;
}

void Ball::SpeedUp() 
{
    if ( current_vel < 5.f) {
        current_vel = current_vel * speedup_vel;
        std::cout << "Speeding Up by " << speedup_vel << " new speed "  << current_vel << "\n";
    } else {
        std::cout << "Not Speeding Up. " << current_vel << "\n";
    }
}

void Ball::Render() {
    SDL_RenderDrawRectF(gRenderer, &rect);
}

void Ball::UpdateRect() {
    rect.x = pos.x;
    rect.y = pos.y;
    rect.w = (float)width;
    rect.h = (float)height;
}