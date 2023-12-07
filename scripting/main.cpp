#include "../core/engine/logic.cpp"

Triangle triangle(_engine);
Triangle triangle2(_engine);

int main()
{
    InitGlfw();
    InitWindow(800, 600, "MESA");
    InitOpengl();

    InitObjects([](){
        triangle.Init(_engine);
        triangle.SetSize(0.1);
        triangle.SetPos(0.0, 0.0);

        triangle2.Init(_engine);
        triangle2.SetSize(0.1);
        triangle2.SetPos(0.0, 0.0);
    });

    Update([](){
        triangle.UpdatePos(-0.0002, 0.00);
        triangle2.UpdatePos(+0.0002, 0.00);
    });

    QuitOpengl();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
