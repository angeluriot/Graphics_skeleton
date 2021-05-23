#ifndef SCENE_H
#define SCENE_H

namespace dim
{
	class Scene
	{
	public:

		FrameBuffer frame_buffer;

		Scene();

		void draw();
		bool can_interact();
	};
}

#endif
