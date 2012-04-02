
#include "TGInterface.h"
#include "visual/TGCamera.h"
#include "visual/TGMesh.h"
#include "visual/TGEnv.h"
#include "visual/TGSkyMap.h"
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
real height = 0.3;
real depth = 1;
SimParams Params;
SimParams newParams;
TGExplicitSolver solver(dx, dy, Params);
TGMeshSystem meshSystem(h,w, 3);
TGClick Clicker(meshSystem, dx, dy, Params);
TGMesh mesh(h,w, dx, dy);
TGEnv envmesh;
TGSkyMap skybox(tw+0.6, TGVectorF4(tw/2,0,th/2));
TGCamera camera;
//TGMatrix4 meshTransform;
TGShader water;
TGShader black;
TGShader env;
TGShader colors;
TGRenderManager renderManager;
real LastTime = 0;
real LastFPS = 0;
uint wWidth;
uint wHeight;
pthread_mutex_t SimParams::Lock;
TGMatrix4 CubeViews[6];

uint FaceToIndex(GLenum face)
{
    switch(face)
    {
        case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
            return 0;
        case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
            return 1;
        case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
            return 2;
        case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
            return 3;
        case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
            return 4;
        case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
            return 5;
    }
    Bug(true, "Face out of range");
}
GLenum IndexToFace(uint index)
{
    switch(index)
    {
        case 0:
            return GL_TEXTURE_CUBE_MAP_POSITIVE_X;
        case 1:
            return GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
        case 2:
            return GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
        case 3:
            return GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
        case 4:
            return GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
        case 5:
            return GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
    }
    Bug(true, "Face index out of bounds");
}

SimParams &Initialize()
{
    Debug("Initialize native");
    Debug("h: %d, w: %d, th:%g, tw:%g", h, w, th, tw);

    TGMatrix4 orthoh; orthoh.CreateOrthogonal(-th/2., th/2., -(height-depth), height-depth, 0.1, 20);
    TGMatrix4 orthow; orthow.CreateOrthogonal(-tw/2., tw/2., -(height-depth), height-depth, 0.1, 20);
    TGMatrix4 orthoz; orthoz.CreateOrthogonal(-tw/2., tw/2., -th/2., th/2., 0.1, 20);

    TGVectorF4 pos(tw/2, 0, th/2);
    camera.SetPosition(pos);

    camera.LookAt(pos + TGVectorF4(1,0,0));
    CubeViews[FaceToIndex(GL_TEXTURE_CUBE_MAP_POSITIVE_X)] = orthoh * camera.GetView();
    camera.LookAt(pos + TGVectorF4(0,1,0));
    CubeViews[FaceToIndex(GL_TEXTURE_CUBE_MAP_POSITIVE_Y)] = orthoz * camera.GetView();
    camera.LookAt(pos + TGVectorF4(0,0,1));
    CubeViews[FaceToIndex(GL_TEXTURE_CUBE_MAP_POSITIVE_Z)] = orthow * camera.GetView();
    camera.LookAt(pos + TGVectorF4(-1,0,0));
    CubeViews[FaceToIndex(GL_TEXTURE_CUBE_MAP_NEGATIVE_X)] = orthoh * camera.GetView();
    camera.LookAt(pos + TGVectorF4(0,-1,0));
    CubeViews[FaceToIndex(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y)] = orthoz * camera.GetView();
    camera.LookAt(pos + TGVectorF4(0,0,-1));
    CubeViews[FaceToIndex(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z)] = orthow * camera.GetView();

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

void Create(const char *vs, const char *fs, const char *bl, const char *envvs, const char *envfs, const char *colvs, const char *colfs)
{
    Debug("Create resources");
    water.Create();
    black.Create();
    env.Create();
    colors.Create();
    mesh.Create();
    renderManager.Create();
    envmesh.Create(tw, th, 0.3, height, depth);
    skybox.Create("data/textures/Skybox.bmp");
    black.SetShader(TGVertexShader, vs);
    water.SetShader(TGVertexShader, vs);
    water.SetShader(TGFragmentShader, fs);
    black.SetShader(TGFragmentShader, bl);
    env.SetShader(TGVertexShader, envvs);
    env.SetShader(TGFragmentShader, envfs);
    colors.SetShader(TGVertexShader, colvs);
    colors.SetShader(TGFragmentShader, colfs);


    water.Link();
    black.Link();
    env.Link();
    colors.Link();
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
    GLuint backTex;
    env.Use();
    if(Params.Shaded)
    {
        for(uint i = 0; i < 6; i++)
        {
            env.SetTransform(CubeViews[i]);
            renderManager.BeginEnv(IndexToFace(i));
            skybox.Draw(env);
            envmesh.Draw(env);
            backTex = renderManager.BeginWater();
        }
    }
    env.SetTransform(camera.GetProjection()*camera.GetView());
    envmesh.Draw(env);

    real adjdiff = meshSystem.Drift() - CurrentAdjustment;
    real driftScale = fminf((2*adjdiff+1)*(2*adjdiff+1)*(2*adjdiff+1)*5,1);
    CurrentAdjustment += ((adjdiff < 0 ? -1 : 1) * fminf(fabsf(adjdiff), Params.DriftSpeed*elapsed*driftScale));

    if(Params.Shaded)
    {
        water.Use();
        water.SetUniformv4("CameraPosition", camera.GetPosition());
        water.SetTransform(camera.GetProjection()*camera.GetView());

        water.SetUniformf("ZAdjustment", -CurrentAdjustment);
        water.SetUniformf("RefractionFactor", 1.000293/1.333);
        water.SetTexture("Background", backTex, 2, GL_TEXTURE_CUBE_MAP);
        water.SetUniformv4("LightPosition", TGVectorF4(tw/2, 4, 4));
        TGVectorF4 *norms = meshSystem.Normals();
        real *data = meshSystem.Commit();
        mesh.Draw(water, data, norms, false);
        renderManager.End();
    }
    else
    {
        colors.Use();
        colors.SetUniformv4("LightPosition", TGVectorF4(tw/2, 4, 4));
        colors.SetTransform(camera.GetProjection()*camera.GetView());
        colors.SetUniformf("ColorScale", Params.Color);

        colors.SetUniformf("ZAdjustment", -CurrentAdjustment);
        TGVectorF4 *norms = meshSystem.Normals();
        real *data = meshSystem.Commit();
        mesh.Draw(water, data, norms, false);
    }
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
    if(Params.Zoom)
        Zoom(dy*0.01 + 1);
    else
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
