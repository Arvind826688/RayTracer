#include "renderer.h"
#include "scene.h"

int main(int argc, char* argv[]) {
    std::string outputFile = (argc > 1) ? argv[1] : "output.png";

    Scene scene;
    scene.CreateSampleScene();

    Renderer renderer(scene);
    renderer.Render(outputFile);

    return 0;
}
