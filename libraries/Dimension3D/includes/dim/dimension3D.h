#ifndef DIMENSION3D_H
#define DIMENSION3D_H

#include "dim/utils/libraries.h"
#include "dim/utils/Mesh.h"
#include "dim/objects/Light.h"
#include "dim/utils/Material.h"
#include "dim/Menu.h"
#include "dim/objects/Object.h"
#include "dim/opengl/Shader.h"
#include "dim/opengl/Texture.h"
#include "dim/vectors/Vector2.h"
#include "dim/vectors/Vector3.h"
#include "dim/vectors/Vector4.h"
#include "dim/opengl/VertexBuffer.h"
#include "dim/windows/Window.h"
#include "dim/objects/Camera.h"
#include "dim/utils/utils.h"
#include "dim/opengl/FrameBuffer.h"
#include "dim/windows/Scene.h"

namespace dim
{
	void			init_opengl();
	void			init_imgui();
	void			init();

	void			unbind_all();
	void			shut_down();
}

#endif
