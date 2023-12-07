#include "triangle.h"

using namespace std;

Triangle::Triangle(Engine& eng) : engine(eng){
	size = 0.3f;

	vector<float> verticles = {
		-size, -size,
        size, -size,
        0,  size,
	};

	verticle_pos = verticles;
}

vector<float> Triangle::GetVerticlePos(){
	return verticle_pos;
}

vector<float> Triangle::GetFragmentVal(){
	return fragment_val;
}

float Triangle::GetSize()
{
	return size;
}

void Triangle::Init(Engine& en)
{
	vector<float> vertexArrVect = GetVerticlePos();
	verticle_pos = vertexArrVect;
	engine = en;

	InitShaders(ReadFile("shaders/vert.shader"), ReadFile("shaders/frag.shader"), 
        vertexShader, fragmentShader, shader_program);

	SendTriangleDataToEngine(VBO, VAO);
}

void Triangle::SendTriangleDataToEngine(GLuint VBO, GLuint VAO)
{
	engine.AddVertexCountToPool(3);
    engine.AddVertexToPool(verticle_pos);
    engine.IncreaseTriangleCount();
}

void Triangle::InitShaders(const char* sourceVertShdr, const char* sourceFragShdr, 
	GLuint& vertShdr, 
	GLuint& fragShdr, 
	GLuint& shdrProgram)
{
	vertShdr = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShdr, 1, &sourceVertShdr, NULL);
    glCompileShader(vertShdr);

    fragShdr = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShdr, 1, &sourceFragShdr, NULL);
    glCompileShader(fragShdr);

    shdrProgram = glCreateProgram();
    glAttachShader(shdrProgram, vertShdr);
    glAttachShader(shdrProgram, fragShdr);
    glLinkProgram(shdrProgram);

    // Delete the shader objects as they are linked to the program and no longer needed
    glDeleteShader(vertShdr);
    glDeleteShader(fragShdr);

    glUseProgram(shdrProgram);
}

void Triangle::SetPos(float x, float y)
{
	float size = GetSize();
	vector<float> verticles = {
		-size+x, -size+y,
        size+x, -size+y,
        0+x,  size+y,
	};
	
	verticle_pos = verticles;
}

void Triangle::UpdatePos(float x, float y)
{
	verticle_pos[0] += x;
	verticle_pos[1] += y;
	//
	verticle_pos[2] += x;
	verticle_pos[3] += y;
	//
	verticle_pos[4] += x;
	verticle_pos[5] += y;

	engine.ChangeVertices(verticle_pos);
	engine.Draw(shader_program, VAO);
}

void Triangle::SetVerticlePos(vector<float> val){
	verticle_pos = val;
}

void Triangle::SetFragmentVal(vector<float> val){
	fragment_val = val;
}

void Triangle::SetSize(float val)
{
	size = val;

	vector<float> verticles = {
		-size, -size,
        size, -size,
        0,  size,
	};

	verticle_pos = verticles;
}