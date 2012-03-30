#ifndef TILESTEXTUREDATA_H_
#define TILESTEXTUREDATA_H_

extern const struct TilesData {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 3:RGB, 4:RGBA */ 
  unsigned char	 pixel_data[512 * 512 * 3 + 1];
} TilesTexture;

#endif
