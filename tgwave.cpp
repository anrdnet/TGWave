
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
    TGMesh mesh(24,24);

    pump.AddHandler(&render);

    TGCamera camera;
    TGVectorF4 myMovement;
    myMovement.Z = 34;
    myMovement.Y = 5;
    myMovement.X = 0;
    //camera.LookAt(TGVectorF4(12,0,12));
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

    while(pump.Run())
    {
        //glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        shader.Use();
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(camera.GetView());
        glPushMatrix();
        glRotated(90, 1,0,0);

        mesh.Draw();
        black.Use();
        glTranslatef(0,0,-0.01);
        mesh.DrawLines();
        
        glPopMatrix();
        glDisableClientState(GL_VERTEX_ARRAY);
        //glDisableClientState(GL_COLOR_ARRAY);
        render.Present();
    }
}
