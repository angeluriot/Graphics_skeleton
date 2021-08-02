#ifndef DIMENSION3D_H
#define DIMENSION3D_H

#include "dim/utils/libraries.hpp"
#include "dim/utils/Mesh.hpp"
#include "dim/objects/Light.hpp"
#include "dim/utils/Material.hpp"
#include "dim/Menu.hpp"
#include "dim/objects/Object.hpp"
#include "dim/opengl/Shader.hpp"
#include "dim/opengl/Texture.hpp"
#include "dim/vectors/Vector2.hpp"
#include "dim/vectors/Vector3.hpp"
#include "dim/vectors/Vector4.hpp"
#include "dim/opengl/VertexBuffer.hpp"
#include "dim/windows/Window.hpp"
#include "dim/cameras/Camera.hpp"
#include "dim/utils/utils.hpp"
#include "dim/opengl/FrameBuffer.hpp"
#include "dim/windows/Scene.hpp"
#include "dim/utils/Color.hpp"
#include "dim/controllers/Controller.hpp"
#include "dim/controllers/OrbitController.hpp"
#include "dim/controllers/FlyController.hpp"
#include "dim/controllers/DragController.hpp"
#include "dim/cameras/Camera2D.hpp"
#include "dim/cameras/OrthographicCamera.hpp"
#include "dim/cameras/PerspectiveCamera.hpp"

namespace dim
{
	void			init_opengl();
	void			init_imgui();
	void			init();
	void			shut_down();
}

#endif
