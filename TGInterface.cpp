
#include "TGInterface.h"
#include "visual/TGCamera.h"
#include "visual/TGMesh.h"
#include "core/TGResourceManager.h"
#include "visual/TGShader.h"
#include "model/TGMeshSystem.h"
#include "model/TGSolver.h"
#include "model/TGClick.h"
#include <cmath>
#include <GL/gl.h>
#include <SDL/SDL.h>

uint h = 75*2;
uint w = 128*2;
real th = 2.0;
real tw = 3.4;
real driftSpeed = 0.01;
real dx = tw/float(w);
real dy = th/float(h);
TGExplicitSolver solver(dx, dy, 10, 0.01);
TGMeshSystem meshSystem(h,w, 3);
TGClick Clicker(meshSystem, dx, dy);
TGMesh mesh(h,w, dx, dy);
TGCamera camera;
TGMatrix4 meshTransform;
TGShader shader;
TGShader black;
real LastTime = 0;
real LastFPS = 0;
uint wWidth;
uint wHeight;

void Initialize()
{
    Debug("Initialize native");
    Debug("h: %d, w: %d, th:%g, tw:%g", h, w, th, tw);
    TGVectorF4 myMovement;
    myMovement.Z = -2;
    myMovement.Y = 3;
    myMovement.X = -2;
    camera.LookAt(TGVectorF4(tw/2,0,th/2));
    camera.SetPosition(myMovement);

    meshTransform(1,1) = 0;
    meshTransform(2,1) = 1;
    meshTransform(2,2) = 0;
    meshTransform(1,2) = 1;

    real *state = new real[h*w];
    for(uint i = 0; i < h; i++)
    {
        for(uint j = 0; j < w; j++)
        {
            state[i*w+j] = 0; //init((tw*j/float(w)) - 1,(th*i/float(h)) - 1);
        }
    }

    meshSystem.SetData(state);
    meshSystem.Commit();
    meshSystem.SetData(state);

    delete [] state;
}

void Create(const char *vs, const char *fs, const char *bl)
{
    Debug("Create resources");
    shader.Create();
    black.Create();
    mesh.Create();
    black.SetShader(TGVertexShader, vs);
    shader.SetShader(TGVertexShader, vs);
    shader.SetShader(TGFragmentShader, fs);
    black.SetShader(TGFragmentShader, bl);

    shader.Link();
    black.Link();
    Debug("Got shaders");
    shader.Use();
    shader.SetUniformf("ColorScale", 1);

    glClearColor(100.0/256,149.0/256,237.0/256,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

inline real GetTime()
{
    return SDL_GetTicks() / 1000.0;
}

uint frameCount = 0;
real CurrentAdjustment = 0;

void Draw()
{
    real time = GetTime();
    real elapsed = 1./60;
    if(LastTime != 0)
        elapsed = time - LastTime;
    LastTime = time;
    if(elapsed > 1./30)
    {
        Debug("Late frame");
        elapsed = 1./60;
    }
    if(time - LastFPS > 5)
    {
        Debug("FPS: %g", frameCount/(time-LastFPS));
        LastFPS = time;
        frameCount = 0;
    }
    frameCount++;
    solver.Advance(meshSystem, elapsed/2);
    meshSystem.Commit();
    solver.Advance(meshSystem, elapsed/2);
    
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    shader.Use();
    meshTransform(1,3) = 0;
    shader.SetTransform(camera.GetProjection()*camera.GetView()*meshTransform);

    real adjdiff = meshSystem.Drift() - CurrentAdjustment;
    CurrentAdjustment += ((adjdiff < 0 ? -1 : 1) * fminf(fabsf(adjdiff), driftSpeed*elapsed));
    Debug("Avg: %g\nDiff: %g", meshSystem.Drift(), adjdiff);

    shader.SetUniformf("ZAdjustment", -CurrentAdjustment);
    real *data = meshSystem.Commit();
    mesh.Draw(shader, data, false);
    //black.Use();
    //meshTransform(1,3) = 0.01;
    //black.SetTransform(camera.GetProjection()*camera.GetView()*meshTransform);
    //mesh.Draw(black, data, true);
}

void ChangeSize(int width, int height)
{
    wWidth = width;
    wHeight = height;

    glViewport(0,0,width,height);
    camera.MakeProjection(width, height);
}

void Orbit(float dx, float dy)
{
    camera.Orbit(dx*0.005,dy*0.005);
}

void Zoom(float factor)
{
    camera.Zoom(factor);
}

int glhUnProjectf(float winx, float winy, float winz, TGMatrix4 &modelview, TGMatrix4 &projection, int *viewport, TGVectorF4 &result);

bool Unproject(real x, real y, TGVectorF4 &result)
{
    y = wHeight - y;
    TGMatrix4 A = camera.GetProjection() * camera.GetView();
    if(!A.Invert())
    {
          Debug("Invert failed");
          return false;
    }
    real normx = 2.*x/wWidth - 1.;
    real normy = 2.*y/wHeight - 1.;
    //Debug("x: %g; y: %g", normx, normy);
    TGVectorF4 far(normx, normy, 1);
    far = A*far;
    if(far.W == 0)
        return false;
    far.W = 1./far.W;
    far *= far.W;

    TGVectorF4 near(normx, normy, 0);
    near = A*near;
    if(near.W == 0)
        return false;
    near.W = 1./near.W;
    near *= near.W;

    TGVectorF4 dir = far - near;
    real t = -near.Y / dir.Y;
    result = near + dir*t;
    return true;
}

void Touch(float x, float y)
{
    Debug("Click at %g;%g", x,y);
    TGVectorF4 click;
    Bug(!Unproject(x,y, click), "Unproject failed");
    Debug("Got: %g; %g; %g", click.X, click.Y, click.Z);

    Clicker.Click(click.X, click.Z);
}
