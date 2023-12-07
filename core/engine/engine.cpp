#include "engine.h"
#include <iostream>
#include<vector>

using namespace std;

void print(std::vector <float> &a) {
   std::cout << "The vector elements are : ";

   for(float i=0; i < a.size(); i++)
   std::cout << a.at(i) << ' ';
}

void Engine::AddVertexToPool(vector<float> &data)
{
	vertex.insert(vertex.end(), data.begin(), data.end());
	//vertex = data;
}

void Engine::AddVertexCountToPool(int data)
{
	vertex_count += data;
}

void Engine::ChangeVertices(vector<float> &data)
{
	vertex = data;
	//vertex = data;
}

void Engine::Update()
{
	vector<float> vertexArrVect = GetVertexFromPool();
    float *vertices = &vertexArrVect[0];

	glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6*triangle_count, vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);
}

void Engine::IncreaseTriangleCount()
{
	triangle_count += 1;
}

void Engine::Draw(GLuint &VAO, GLuint& shdrProgram)
{
    vector<float> vertexArrVect = GetVertexFromPool();
    float *vertices = &vertexArrVect[0];

    glBufferSubData(GL_ARRAY_BUFFER,0 , sizeof(float)*6*triangle_count, vertices);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}


int Engine::GetVertexCountFromPool()
{
	return vertex_count;
}

vector<float> Engine::GetVertexFromPool()
{
	return vertex;
}