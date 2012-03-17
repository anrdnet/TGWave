
#include <iostream>
#include "visual/TGRender.h"
#include "visual/TGCamera.h"
#include "visual/TGMesh.h"
#include "core/TGMessagePump.h"
#include "core/TGResourceManager.h"
#include "visual/TGShader.h"
#include "model/TGMeshSystem.h"
#include "model/TGSolver.h"
#include <cmath>

real init(real x, real y)
{
    return exp(-40*((x-0.4)*(x-0.4) + y*y));
}

int main(int argc, char *argv[])
{
    uint h = 70;
    uint w = h;
    TGMessagePump pump;
    TGRender render(0,0);
    TGMesh mesh(h,w);

    pump.AddHandler(&render);

    TGCamera camera;
    TGVectorF4 myMovement;
    myMovement.Z = -60;
    myMovement.Y = 50;
    myMovement.X = -50;
    camera.LookAt(TGVectorF4(35,0,35));
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
    TGExplicitSolver solver(2./float(w),2./float(h), 0.2);

    real *state = new real[h*w];
    for(uint i = 0; i < h; i++)
    {
        for(uint j = 0; j < w; j++)
        {
            state[i*w+j] = w/2*init((2*i/float(h)) - 1,(2*j/float(w)) - 1 );
        }
    }

    meshSystem.SetData(state);
    meshSystem.Commit();
    meshSystem.SetData(state);

    delete [] state;

    while(pump.Run())
    {
        //glEnableClientState(GL_COLOR_ARRAY);
        //glEnableClientState(GL_VERTEX_ARRAY);
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(camera.GetView());

        glMultMatrixf(meshTransform);
        shader.Use();
        real *data = meshSystem.Commit();
        mesh.Draw(shader, data, false);
        glTranslatef(0,0,0.1);
        black.Use();
        mesh.Draw(black, data, true);
        solver.Advance(meshSystem, 1./120);
        meshSystem.Commit();
        solver.Advance(meshSystem, 1./120);
        
        //glDisableClientState(GL_VERTEX_ARRAY);
        //glDisableClientState(GL_COLOR_ARRAY);
        render.Present();
    }
}
