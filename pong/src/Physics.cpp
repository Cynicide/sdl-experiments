#include <Physics.h>
#include <Ball.h>
#include <Paddle.h>
#include <iostream>

Physics::Physics() {

}

bool Physics::BallVsPaddleCollision(Ball &ball, Paddle paddle) {
    // Is the left side of the ball to the left of the right side of the paddle
    float ballLeft = ball.pos.x;
    float ballRight = ball.pos.x + ball.width;
    float ballTop = ball.pos.y;
    float ballBottom = ball.pos.y + ball.height;

    float paddleLeft = paddle.pos.x;
    float paddleRight = paddle.pos.x + paddle.width;
    float paddleTop = paddle.pos.y;
    float paddleBottom = paddle.pos.y + paddle.height;

     // Is the left side of the ball to the left of the right side of the paddle
    if (ballLeft < paddleRight &&
        // Is the right side of the ball to the right of the left side of the paddle 
        ballRight > paddleLeft &&
        // Is the top of the ball above the bottom of the paddle
        ballTop < paddleBottom &&
        // Is the bottom of the ball below the top of the paddle
        ballBottom > paddleTop)
        {
            std::cout << "----- COLLISION -----\n";
            std::cout << "BallLeft: " << ballLeft << " BallRight: " << ballRight << " BallTop: " << ballTop << " BallBottom: " << ballBottom << "\n";
            std::cout << "PaddleLeft: " << paddleLeft << " PaddleRight: " << paddleRight << " PaddleTop: " << paddleTop << " PaddleBottom: " << paddleBottom << "\n";
            return true;
        } else {
            return false;
        }
}

float Physics::SweptAABB(Ball ball, Paddle paddle, float &normalx, float &normaly) {
    // https://www.gamedev.net/articles/programming/general-and-gameplay-programming/swept-aabb-collision-detection-and-response-r3084/
    // https://www.amanotes.com/post/using-swept-aabb-to-detect-and-process-collision


    float xInvEntry, yInvEntry;
    float xInvExit, yInvExit;

    float xEntry, yEntry;
    float xExit, yExit;

    // Find the distance between the objects on the near and far sides for both X and Y
    if (ball.vel.x > 0.0f) 
    {
        xInvEntry = paddle.pos.x - (ball.pos.x + ball.width);
        xInvExit = (paddle.pos.x + paddle.width) - ball.pos.x;

    }
    else
    {
        xInvEntry = (paddle.pos.x + paddle.width) - ball.pos.x;
        xInvExit = paddle.pos.x - (ball.pos.x + ball.width);
    }

    if (ball.vel.y > 0.0f)
    {
        yInvEntry = paddle.pos.y - (ball.pos.y + ball.height);
        yInvExit = (paddle.pos.y + paddle.height) - ball.pos.y;
    }
    else
    {
        yInvEntry = (paddle.pos.y + paddle.height) - ball.pos.y;
        yInvExit = paddle.pos.y - (ball.pos.y + ball.height);
    }

    // Find time of collision and time of leaving for each axis (if statement to prevent divide by zero)

    if (ball.vel.x == 0.0f)
    {
        xEntry = -std::numeric_limits<float>::infinity();
        xExit = std::numeric_limits<float>::infinity();
    }
    else
    {
        xEntry = xInvEntry / ball.vel.x;
        xExit = xInvExit / ball.vel.x; 
    }

    if (ball.vel.y == 0.0f)
    {
        yEntry = -std::numeric_limits<float>::infinity();
        yExit = std::numeric_limits<float>::infinity();
    }
    else
    {
        yEntry = yInvEntry / ball.vel.y;
        yExit = yInvExit / ball.vel.y; 
    } 

    // Find the earliest/latest times of collision
    float entryTime = std::max(xEntry, yEntry);
    float exitTime = std::min(xExit, yExit);

    // If there was no collision
    if (entryTime > exitTime || (xEntry < 0.0f && yEntry < 0.0f) || xEntry > 1.0f || yEntry > 1.0f)
    {
        normalx = 0.0f;
        normaly = 0.0f;
        return 1.0f;
    }
    // if there was a collision
    else
    {
        // Calculate the Normal of the collided surface
        if (xEntry > yEntry)
        {
            if (xInvEntry < 0.0f)
            {
                normalx = 1.0f;
                normaly = 0.0f;
            }
            else
            {
                normalx = -1.0f;
                normaly = 0.0f;

            }
        }
        else
        {
            if (yInvEntry < 0.0f) 
            {
                normalx = 0.0f;
                normaly = 1.0f;
            }
            else
            {
                normalx = 0.0f;
                normaly = -1.0f;
            }
        }
        // return the time of collision
        return entryTime;
    }
}

void Physics::ProcessCollision(Ball &ball, Paddle paddle) {

    float normalx, normaly;
    float collisiontime = SweptAABB(ball, paddle, normalx, normaly);

    ball.pos.x += ball.vel.x * collisiontime;
    ball.pos.y += ball.vel.y * collisiontime;

    if (abs(normalx) > 0.0001f) {
        // Change the angle a bit if we hit the paddle on the front.

        ball.vel.x = -ball.vel.x;

        int ball_mid = ball.pos.y + (ball.height / 2);
        int paddle_mid = paddle.pos.y + (paddle.height / 2);
        int hitLocation = paddle_mid - ball_mid;

        ball.ChangeAngle(hitLocation);
    } 
    if (abs(normaly) > 0.0001f) {
        ball.vel.y = -ball.vel.y;
    } 
}

Ball Physics::GetSweptBroadphaseBox(Ball b) 
{ 
  Ball broadphasebox;  
  broadphasebox.pos.x = b.vel.x > 0 ? b.pos.x : b.pos.x + b.vel.x;  
  broadphasebox.pos.y = b.vel.y > 0 ? b.pos.y : b.pos.y + b.vel.y;  
  broadphasebox.width = b.vel.x > 0 ? b.vel.x + b.width : b.width - b.vel.x;  
  broadphasebox.height = b.vel.y > 0 ? b.vel.y + b.height : b.height - b.vel.y;  

  return broadphasebox; 
}

bool Physics::AABBCheck(Ball ball, Paddle paddle) 
{ 
  return !(ball.pos.x + ball.width < paddle.pos.x || ball.pos.x > paddle.pos.x + paddle.width || ball.pos.y + ball.height < paddle.pos.y || ball.pos.y > paddle.pos.y + paddle.height); 
}

void Physics::Render() {
    
}