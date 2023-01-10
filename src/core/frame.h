#pragma once 

struct frame
{
	uint32_t before = 0; //< time before frame start
	uint32_t lag    = 0; //< frame lag
	uint32_t delta  = 0; //< frame delta

	void apply_delay(uint32_t fr)
	{
		if (before != 0)
		{
			delta = SDL_GetTicks() - before;

			if (delta <= fr) // if process is ahead of framerate
			{
				lag = 0;
				delta = (delta - fr) * -1;
//				LOG_INFO("delaying frame by {}ms", delta);
				SDL_Delay(delta);
			}
			else // if process is behind or lagging
			{
				lag = delta - fr;
//				LOG_ERROR("frame lagging by {}ms", lag);
			}
		}
	}
};