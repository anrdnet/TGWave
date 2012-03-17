
#include <iostream>
#include "visual/TGRender.h"
#include "visual/TGCamera.h"
#include "visual/TGMesh.h"
#include "core/TGMessagePump.h"
#include "core/TGResourceManager.h"
#include "visual/TGShader.h"
#include "model/TGMeshSystem.h"

int main(int argc, char *argv[])
{
    uint h = 12;
    uint w = h;
    TGMessagePump pump;
    TGRender render(0,0);
    TGMesh mesh(h,w);

    pump.AddHandler(&render);

    TGCamera camera;
    TGVectorF4 myMovement;
    myMovement.Z = 30;
    myMovement.Y = 10;
    myMovement.X = 12;
    camera.LookAt(TGVectorF4(6,0,0));
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
    TGMeshSystem meshSystem(h,w, 3);

    while(pump.Run())
    {
        //glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(camera.GetView());

        glMultMatrixf(meshTransform);
        shader.Use();
        mesh.Draw(shader, meshSystem.Commit(), false);
        glTranslatef(0,0,0.1);
        black.Use();
        mesh.Draw(black, meshSystem.Commit(), true);
        
        glDisableClientState(GL_VERTEX_ARRAY);
        //glDisableClientState(GL_COLOR_ARRAY);
        render.Present();
    }
}
