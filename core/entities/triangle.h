#include <vector>
#include "../engine/engine.h"
#include <cstddef>
using namespace std;

class Triangle{
	public:
		Triangle(Engine& eng);

		void Init(Engine& en);
		void InitShaders(const char*, const char*, GLuint&, GLuint&, GLuint&);
		void SetPos(float, float);
		void UpdatePos(float, float, GLuint&, GLuint&);
		void SetVerticlePos(vector<float>);
		void SetFragmentVal(vector<float>);
		void SetSize(float);
		void SendTriangleDataToEngine(GLuint VBO, GLuint VAO);

		vector<float> GetVerticlePos(void);
		vector<float> GetFragmentVal(void);
		float GetSize();
	private:
		float size;
		vector<float> verticle_pos;
		vector<float> fragment_val;
		Engine& engine;
};