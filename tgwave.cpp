
#include <iostream>
#include "visual/TGRender.h"
#include "visual/TGCamera.h"
#include "visual/TGMesh.h"
#include "core/TGMessagePump.h"
#include "core/TGResourceManager.h"
#include "visual/TGShader.h"

int main(int argc, char *argv[])
{
    TGMessagePump pump;
    TGRender render(0,0);
    TGMesh mesh(12,12);

    pump.AddHandler(&render);

    TGCamera camera;
    TGVectorF4 myMovement;
    myMovement.Z = 30;
    myMovement.Y = 10;
    myMovement.X = 12;
    camera.LookAt(TGVectorF4(12,0,0));
    camera.Move(myMovement);
    Debug("View is: "<<(string)camera.GetView());
    Debug("View dir:"<<(string)camera.GetViewDirection());

    TGResourceManager rec;
    TGResource vs = rec.CreateResource(TGResourceType::Shader, "cubeshader.vs");
    TGResource fs = rec.CreateResource(TGResourceType::Shader, "cubeshader.fs");
    TGResource bfs = rec.CreateResource(TGResourceType::Shader, "black.fs");
    Debug("Got shaders");
    TGShader shader;
    shader.SetShader(TGVertexShader, rec.GetData(vs));
    shader.SetShader(TGFragmentShader, rec.GetData(fs));
    shader.Link();
    TGShader black;
    black.SetShader(TGVertexShader, rec.GetData(vs));
    black.SetShader(TGFragmentShader, rec.GetData(bfs));
    black.Link();

    TGMatrix4 meshTransform;

    meshTransform(1,1) = 0;
    meshTransform(2,1) = 1;
    meshTransform(2,2) = 0;
    meshTransform(1,2) = 1;

    while(pump.Run())
    {
        //glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        shader.Use();
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(camera.GetView());

        glMultMatrixf(meshTransform);
        mesh.Draw();
        black.Use();
        glTranslatef(0,0,0.1);
        mesh.DrawLines();
        
        glDisableClientState(GL_VERTEX_ARRAY);
        //glDisableClientState(GL_COLOR_ARRAY);
        render.Present();
    }
}
