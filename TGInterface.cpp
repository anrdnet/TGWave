
#include "TGInterface.h"
#include "visual/TGCamera.h"
#include "visual/TGMesh.h"
#include "visual/TGEnv.h"
#include "core/TGResourceManager.h"
#include "visual/TGShader.h"
#include "model/TGMeshSystem.h"
#include "model/TGSolver.h"
#include "model/TGClick.h"
#include "visual/TGRenderManager.h"
#include <cmath>
#include <GL/gl.h>
#include <SDL/SDL.h>
//HE IHE I EHI!
uint h = 75*2;
uint w = 128*2;
real th = 2.0;
real tw = 3.4;
real dx = tw/float(w-1);
real dy = th/float(h-1);
SimParams Params;
SimParams newParams;
TGExplicitSolver solver(dx, dy, Params);
TGMeshSystem meshSystem(h,w, 3);
TGClick Clicker(meshSystem, dx, dy, Params);
TGMesh mesh(h,w, dx, dy);
TGEnv envmesh;
TGCamera camera;
//TGMatrix4 meshTransform;
TGShader shader;
TGShader black;
TGShader env;
TGRenderManager renderManager(env, shader);
real LastTime = 0;
real LastFPS = 0;
uint wWidth;
uint wHeight;
pthread_mutex_t SimParams::Lock;

SimParams &Initialize()
{
    Debug("Initialize native");
    Debug("h: %d, w: %d, th:%g, tw:%g", h, w, th, tw);
    TGVectorF4 myMovement;
    myMovement.Z = -2;
    myMovement.Y = 3;
    myMovement.X = -2;
    camera.LookAt(TGVectorF4(tw/2,0,th/2));
    camera.SetPosition(myMovement);

    /*meshTransform(1,1) = 0;
    meshTransform(2,1) = 1;
    meshTransform(2,2) = 0;
    meshTransform(1,2) = 1;*/

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
    return newParams;
}

void Create(const char *vs, const char *fs, const char *bl, const char *envvs, const char *envfs)
{
    Debug("Create resources");
    shader.Create();
    black.Create();
    env.Create();
    mesh.Create();
    renderManager.Create();
    envmesh.Create(tw, th, 0.3, 0.1, 1);
    black.SetShader(TGVertexShader, vs);
    shader.SetShader(TGVertexShader, vs);
    shader.SetShader(TGFragmentShader, fs);
    black.SetShader(TGFragmentShader, bl);
    env.SetShader(TGVertexShader, envvs);
    env.SetShader(TGFragmentShader, envfs);

    shader.Link();
    black.Link();
    env.Link();
    Debug("Got shaders");

    //glClearColor(100.0/256,149.0/256,237.0/256,1);
    glClearColor(0.1,0.1,0.1,1);
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
    
    if(pthread_mutex_trylock(&SimParams::Lock) == 0)
    {
        Params = newParams;
        newParams.Reset = false;
        pthread_mutex_unlock(&SimParams::Lock);
    }

    if(Params.Reset)
    {
        meshSystem.Reset();
        meshSystem.Drift() = 0;
        CurrentAdjustment = 0;
        Params.Reset = false;
    }

    solver.Advance(meshSystem, elapsed/2);
    meshSystem.Commit();
    solver.Advance(meshSystem, elapsed/2);
    
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    renderManager.BeginEnv();
    env.SetTransform(camera.GetProjection()*camera.GetView());
    envmesh.Draw(env);
    renderManager.BeginWater();
    shader.SetUniformf("ColorScale", Params.Color);
    shader.SetUniformv4("CameraPosition", camera.GetPosition());
    //meshTransform(1,3) = 0;
    shader.SetTransform(camera.GetProjection()*camera.GetView()/*meshTransform*/);

    real adjdiff = meshSystem.Drift() - CurrentAdjustment;
    real driftScale = fminf((2*adjdiff+1)*(2*adjdiff+1)*(2*adjdiff+1)*5,1);
    CurrentAdjustment += ((adjdiff < 0 ? -1 : 1) * fminf(fabsf(adjdiff), Params.DriftSpeed*elapsed*driftScale));
    //Debug("Avg: %g\nDiff: %g", meshSystem.Drift(), adjdiff);

    shader.SetUniformf("ZAdjustment", -CurrentAdjustment);
    TGVectorF4 *norms = meshSystem.Normals();
    real *data = meshSystem.Commit();
    mesh.Draw(shader, data, norms, false);
    renderManager.End();
    //black.Use();
    //meshTransform(1,3) = 0.01;
    //black.SetTransform(camera.GetProjection()*camera.GetView()*meshTransform);
    //mesh.Draw(black, data, true);

    //real a = 0;
    //for (int i = 0; i < 1000000; i++)
    //{
    //    a = (a+1)*(a+1)/(a+2);
    //}
    //Debug("%g", a);
}

void ChangeSize(int width, int height)
{
    wWidth = width;
    wHeight = height;

    Debug("Height: %d; Width: %d", height, width);
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
