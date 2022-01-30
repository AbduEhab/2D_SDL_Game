#include "Constants.h"
#include "Game.h"

int main(int argc, char *arg[])
{

    Game game = Game();

    game.Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

    game.ticks_last_frame = Clock::now();

    while (game.IsRunning())
    {

        auto ticks_since_last_frame = Clock::now() - game.ticks_last_frame;

        float waitTime = FRAME_TIME_TARGET - (ticks_since_last_frame.count() * 1e-9); // calculate time to wait between frames

        if (waitTime > 0 && waitTime <= FRAME_TIME_TARGET)
            // SDL_Delay(waitTime); // hold exec until the specified ms has passed
            std::this_thread::sleep_for(std::chrono::milliseconds((int)waitTime));

        float delta_time = ticks_since_last_frame.count() * 1e-9; // diffrence between the time since the last frame and the current frame in seconds

        game.ticks_last_frame = Clock::now(); // update the lastFrameTime time to be used in the next pass

        game.ProcessInput();
        game.Update(delta_time);
        game.Render();
    }

    return 0;
}