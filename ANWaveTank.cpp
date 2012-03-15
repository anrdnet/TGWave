
#include <iostream>
#include "visual/ANRender.h"
#include "visual/ANCamera.h"
#include "visual/ANMesh.h"
#include "core/ANMessagePump.h"
#include "core/ANResourceManager.h"
#include "visual/ANShader.h"

int main(int argc, char *argv[])
{
    ANMessagePump pump;
    ANRender render(0,0);
    ANMesh mesh(24,24);

    pump.AddHandler(&render);

    ANCamera camera;
    ANVectorF4 myMovement;
    ANVectorF4 myRotation;
    myMovement.Z = -30;
    myMovement.Y = 5;
    //myRotation.Y = 3.14156;
    //myRotation.X = -3.14156 / 3;
    //myRotation.Y = 3.14156 / 4;
    camera.Move(myMovement);
    camera.Rotate(myRotation);
    Debug("View is: "<<(string)camera.GetView());

    ANResourceManager rec;
    ANResource vs = rec.CreateResource(ANResourceType::Shader, "cubeshader.vs");
    ANResource fs = rec.CreateResource(ANResourceType::Shader, "cubeshader.fs");
    ANResource bfs = rec.CreateResource(ANResourceType::Shader, "black.fs");
    Debug("Got shaders");
    ANShader shader;
    shader.SetShader(ANVertexShader, rec.GetData(vs));
    shader.SetShader(ANFragmentShader, rec.GetData(fs));
    shader.Link();
    ANShader black;
    black.SetShader(ANVertexShader, rec.GetData(vs));
    black.SetShader(ANFragmentShader, rec.GetData(bfs));
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
