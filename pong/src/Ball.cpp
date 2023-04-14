
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

void Ball::Move(float dt) {
    pos.x += vel.x * dt;
    pos.y += vel.y * dt;

    rect.x = pos.x;
    rect.y = pos.y;
    rect.w = width;
    rect.h = height;
}

void Ball::RandSetBallVelocity() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> direction(0, 1);

    vel.x = current_vel;
    vel.y = current_vel;

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
    if ( current_vel < max_vel) {
        current_vel = current_vel * speedup_vel;
        std::cout << "current_vel: " << current_vel << "\n";
    } else {
        std::cout << "current_vel: " << current_vel << "\n";
    }
    // Check the sign on the velocity before applying the new velocity
    if (sgn(vel.y) == 1) {
        vel.y = current_vel;
    }
    else
    {
        vel.y = current_vel * -1;
    }
    
    if (sgn(vel.x) == 1) {
        vel.x = current_vel;
    }
    else
    {
        vel.x = current_vel * -1;
    }
}

void Ball::Render() {
    SDL_RenderDrawRectF(gRenderer, &rect);
}

void Ball::ChangeAngle(int hitLocation) {
    
    // Hit Location should be between 50 and -50
    std::cout << "HitLocation: " << hitLocation << "\n";
    
    // Remove the sign
    int sgnHitLocation =  abs(hitLocation);

    // Divide the hitlocation by it's max value to get a number between 0 and 1.
    float angle = (float)sgnHitLocation / 50.0f;
    std::cout << "Angle: " << angle << "\n";


    // Clamp the top and bottom values as the midsection of the ball can strike a little above paddle
    if ( angle > 1.0f ) {
        angle = 1.0f;
    }

    if ( angle < 0.0f ) {
        angle = 0.0f;
    }    

    // Check the sign and apply the Y Velocity to make an angle
    if (sgn(vel.y) == 1) {
        vel.y = vel.y + (angle * 2);
    }
    else
    {
        vel.y = vel.y - (angle * 2);
    }

    std::cout << "Bounce Resolved: VX: " << vel.x <<" VY: " << vel.y << "\n";
}

void Ball::UpdateRect() {
    rect.x = pos.x;
    rect.y = pos.y;
    rect.w = (float)width;
    rect.h = (float)height;
}