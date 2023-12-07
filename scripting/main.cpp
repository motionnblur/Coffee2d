#include "../core/engine/logic.cpp"

int main()
{
    InitGlfw();
    InitWindow(800, 600, "MESA");
    InitOpengl();

    Update([](){
        triangle.UpdatePos(-0.0002, 0.00);
        triangle2.UpdatePos(+0.0002, 0.00);
    });

    QuitOpengl();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
