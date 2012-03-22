
#ifndef TGINTERFACE_H_
#define TGINTERFACE_H_

void Initialize();
void Create(const char *vs, const char *fs, const char *bl);

void Draw();

void ChangeSize(int width, int height);

void Orbit(float dx, float dy);

void Zoom(float factor);

void Touch(float x, float y);

#endif
