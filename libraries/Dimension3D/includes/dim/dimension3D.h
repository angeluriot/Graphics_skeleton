#ifndef DIMENSION3D_H
#define DIMENSION3D_H

#include "dim/libraries.h"
#include "dim/Mesh.h"
#include "dim/Light.h"
#include "dim/Material.h"
#include "dim/Menu.h"
#include "dim/Object.h"
#include "dim/Shader.h"
#include "dim/Texture.h"
#include "dim/Vector2.h"
#include "dim/Vector3.h"
#include "dim/Vector4.h"
#include "dim/VertexBuffer.h"
#include "dim/Window.h"
#include "dim/Camera.h"
#include "dim/utils.h"
#include "dim/FrameBuffer.h"
#include "dim/Scene.h"

namespace dim
{
	void			init_opengl();
	void			init_imgui();
	void			init();

	void			unbind_all();
	void			shut_down();

	constexpr float	PI = 3.14159265359f; // Pi
}

#endif
