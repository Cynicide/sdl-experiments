#include <Physics.h>
#include <iostream>

Physics::Physics() {

}


float Physics::SweptAABB(SDL_FRect rectA, SDL_FRect rectB, Vector2d rectAVel, float &normalx, float &normaly) {
    // https://www.gamedev.net/articles/programming/general-and-gameplay-programming/swept-aabb-collision-detection-and-response-r3084/
    // https://www.amanotes.com/post/using-swept-aabb-to-detect-and-process-collision

    float xInvEntry, yInvEntry;
    float xInvExit, yInvExit;

    float xEntry, yEntry;
    float xExit, yExit;

    // Find the distance between the objects on the near and far sides for both X and Y
    if (rectAVel.x > 0.0f) 
    {
        xInvEntry = rectB.x - (rectA.x + rectA.w);
        xInvExit = (rectB.x + rectB.w) - rectA.x;
    }
    else
    {
        xInvEntry = (rectB.x + rectB.w) - rectA.x;
        xInvExit = rectB.x - (rectA.x + rectA.w);
    }

    if (rectAVel.y > 0.0f)
    {
        yInvEntry = rectB.y - (rectA.y + rectA.h);
        yInvExit = (rectB.y + rectB.h) - rectA.y;
    }
    else
    {
        yInvEntry = (rectB.y + rectB.h) - rectA.y;
        yInvExit = rectB.y - (rectA.y + rectA.h);
    }

    // Find time of collision and time of leaving for each axis (if statement to prevent divide by zero)

    if (rectAVel.x == 0.0f)
    {
        xEntry = -std::numeric_limits<float>::infinity();
        xExit = std::numeric_limits<float>::infinity();
    }
    else
    {
        xEntry = xInvEntry / (rectAVel.x);
        xExit = xInvExit / (rectAVel.x); 
    }

    if (rectAVel.y == 0.0f)
    {
        yEntry = -std::numeric_limits<float>::infinity();
        yExit = std::numeric_limits<float>::infinity();
    }
    else
    {
        yEntry = yInvEntry / (rectAVel.y);
        yExit = yInvExit / (rectAVel.y);
    } 

    // Find the earliest/latest times of collision
    float entryTime = std::max(xEntry, yEntry);
    float exitTime = std::min(xExit, yExit);

    // If there was no collision
    if (entryTime > exitTime || (xEntry < 0.0f && yEntry < 0.0f) || xEntry > 1.0f || yEntry > 1.0f)
    {
        Logger("There Was No Collision");
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

void Physics::ProcessCollision(SDL_FRect &rectA, SDL_FRect rectB, Vector2d &rectAVel, double dt) 
{

    spdlog::info("----------------------- COLLISION -----------------------");
    spdlog::info("Processing Collision for RectB Location: " + std::to_string(rectB.x) + " : " + std::to_string(rectB.y));     
    spdlog::info("RectA: " + std::to_string(rectA.x) + " : " + std::to_string(rectA.y) + " : " + std::to_string(rectA.w) + " : " + std::to_string(rectA.h));    
    spdlog::info("RectB: " + std::to_string(rectB.x) + " : " + std::to_string(rectB.y) + " : " + std::to_string(rectB.w) + " : " + std::to_string(rectB.h));    

    float normalx, normaly;
    float collisiontime = SweptAABB(rectA, rectB, rectAVel, normalx, normaly);

    // Do not need if we are not going to accelerate out of bounce
    //rectA.x += (rectAVel.x * dt) * collisiontime;
    //rectA.y += (rectAVel.y * dt) * collisiontime;

    if (abs(normalx) > 0.0001f) {
        rectAVel.x = -rectAVel.x;
    } 
    if (abs(normaly) > 0.0001f) {
        rectAVel.y = -rectAVel.y;
    } 
}

SDL_FRect Physics::GetSweptBroadphaseBox(SDL_FRect object, float velx, float vely) 
{ 
  SDL_FRect broadphasebox;  
  //broadphasebox.x = velx > 0.f ? object.x : object.x + velx;  
  if (velx > 0.f) {
      broadphasebox.x = object.x;
  }
  else 
  {
      broadphasebox.x = object.x + velx;
  }
  
  broadphasebox.y = vely > 0.f ? object.y : object.y + vely;  
  broadphasebox.w = velx > 0.f ? velx + object.w : object.w - velx;  
  broadphasebox.h = vely > 0.f ? vely + object.h : object.h - vely;  

  return broadphasebox; 
}

bool Physics::AABBCheck(SDL_FRect rectA, SDL_FRect rectB) 
{ 
  return !(rectA.x + rectA.w < rectB.x || rectA.x > rectB.x + rectB.w || rectA.y + rectA.h < rectB.y || rectA.y > rectB.y + rectB.h); 
}

void Physics::Render() {
    
}