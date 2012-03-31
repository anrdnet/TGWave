
#ifndef TGINTERFACE_H_
#define TGINTERFACE_H_

#include "core/TGDef.h"
#include "SDL/SDL.h"
#include <pthread.h>

struct SimParams
{
    static pthread_mutex_t Lock;
    SimParams()
    {
        DriftSpeed = 0.05;
        c = 10;
        mu = 0.1;
        NewHeight = 1;
        Shape = 100;
        Scale = 1;
        Color = 20;
        Reset = false;
        Shaded = false;
    }
    real DriftSpeed;
    real c;
    real mu;
    real NewHeight;
    real Shape;
    real Scale;
    real Color;
    bool Reset;
    bool Shaded;
};

SimParams &Initialize();
void Create(const char *vs, const char *fs, const char *bl, const char *envvs, const char *envfs, const char *colvs, const char *colfs);

void Draw();

void ChangeSize(int width, int height);

void Orbit(float dx, float dy);

void Zoom(float factor);

void Touch(float x, float y);

#endif
