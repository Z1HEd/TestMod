//#define DEBUG_CONSOLE // Uncomment this if you want a debug console to start. You can use the Console class to print. You can use Console::inStrings to get input.

#include <4dm.h>
#include "4do/4do.h"

using namespace fdm;
using namespace fdo;

// Initialize the DLLMain
initDLL

MeshRenderer renderer;
const Shader* shader;

$hook(void, WorldManager, render, const m4::Mat5& MV, bool glasses, glm::vec3 worldColor) {
	original(self, MV, glasses, worldColor);

	m4::Mat5 mat = MV;
	mat.translate(glm::vec4{0,5,0,0.0001});
	shader->use();
	glUniform1fv(glGetUniformLocation(shader->id(), "MV"), sizeof(m4::Mat5) / sizeof(float), &mat[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shader->id(), "P"), 1, false, &StateGame::instanceObj->projection3D[0][0]);
	renderer.render();
}

$hook(void, StateIntro, init, StateManager& s)
{
	original(self, s);

	// initialize opengl stuff
	glewExperimental = true;
	glewInit();
	glfwInit();

	// initialization somewhere like stateintro::init
	shader = ShaderManager::load("assets/shader.vs", "assets/shader.fs", "assets/shader.gs");

	std::vector<Point> pos;
	std::vector<Point> norm;
	std::vector<TexCoord> uvw;
	std::vector<fdo::Color> col;
	std::vector<uint32_t> indexBuffer;

	Object obj;
	obj.load4DOFromFile(std::format("../../{}/assets/test.4do", fdm::getModPath(fdm::modID)));
	obj.tetrahedralize(pos, norm, uvw, col, indexBuffer);

	MeshBuilder mesh{ (GLsizei)indexBuffer.size() };

	mesh.addBuff(pos.data(),(GLsizei) pos.size() * sizeof(fdo::Point));
	mesh.addAttr(GL_FLOAT, 4, sizeof(fdo::Point));

	//mesh.addBuff(norm.data(), norm.size() * sizeof(fdo::Point));
	//mesh.addAttr(GL_FLOAT, 4, sizeof(fdo::Point));

	mesh.addBuff(col.data(),(GLsizei) col.size() * sizeof(fdo::Color));
	mesh.addAttr(GL_UNSIGNED_BYTE, 4, sizeof(fdo::Color));

	renderer.setMesh(&mesh);
}