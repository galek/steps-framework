#
# Makefile to build OpenGL 3.3/4.1 examples for Linux
#
# Author: Alex V. Boreskoff, <steps3d@narod.ru>, <steps3d@gmail.com>
#

GLUTPATH   = /usr/include/GL
CFLAGS     = -x c++ -g -I/usr/include/GL -Wall -I$(GLUTPATH)/include/GL
CONLYFLAGS = -g -I/usr/include/GL -Wall -I$(GLUTPATH)/include/GL
LIBS       = -L/usr/X11R6/lib -L$(GLUTPATH)/lib -lglut -lGL -lXt -lX11 -lm -ljpeg -lz -lpng -lGLEW

MATH = vec2.o vec3.o vec4.o mat2.o mat3.o mat4.o quat.o plane.o bbox.o randUtils.o eig3.o
TEXT = Texture.o TexImage.o TgaEncoder.o TgaDecoder.o DdsDecoder.o BmpDecoder.o JpegDecoder.o PngDecoder.o Resources.o FileSystem.o ZipFileSystem.o TexFormat.o
WRAP = Data.o Program.o VertexBuffer.o Framebuffer.o stringUtils.o glUtilities.o UbAccessor.o Sampler.o half.o ScreenQuad.o

ALL = 1 2 3 4 5 6 geom-1 geom-2 geom-3 geom-4 light light-ub bezier phong tex-cube tex-3d tex-2d knot test-half test-quad test-sphere test-box test-camera

all: $(ALL)

1: 1.o $(MATH) $(TEXT) $(WRAP)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS) -lc

2: 3.o $(MATH) $(TEXT) $(WRAP)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS) -lc

3: 3.o $(MATH) $(TEXT) $(WRAP)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS) -lc

4: 4.o $(MATH) $(TEXT) $(WRAP)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS) -lc

5: 5.o $(MATH) $(TEXT) $(WRAP)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS) -lc

6: 6.o $(MATH) $(TEXT) $(WRAP)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS) -lc

geom-1: geom-1.o $(MATH) $(TEXT) $(WRAP)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS) -lc

geom-2: geom-2.o  $(MATH) $(TEXT) $(WRAP)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS) -lc

geom-3: geom-3.o  $(MATH) $(TEXT) $(WRAP)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS) -lc

geom-4: geom-4.o  $(MATH) $(TEXT) $(WRAP)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS) -lc

light: light.o  $(MATH) $(TEXT) $(WRAP)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS) -lc

light-ub: light-ub.o  $(MATH) $(TEXT) $(WRAP)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS) -lc

bezier: bezier.o  $(MATH) $(TEXT) $(WRAP)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS) -lc

phong: phong.o  $(MATH) $(TEXT) $(WRAP)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS) -lc

tex-cube: tex-cube.o  $(MATH) $(TEXT) $(WRAP)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS) -lc

tex-3d: tex-3d.o  $(MATH) $(TEXT) $(WRAP)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS) -lc

tex-2d: tex-2d.o  $(MATH) $(TEXT) $(WRAP)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS) -lc

knot: knot.o  $(MATH) $(TEXT) $(WRAP)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS) -lc

test-quad: test-quad.o  $(MATH) $(TEXT) $(WRAP)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS) -lc

test-box: test-box.o  $(MATH) $(TEXT) $(WRAP)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS) -lc

test-sphere: test-sphere.o  $(MATH) $(TEXT) $(WRAP)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS) -lc

test-half: test-half.o  $(MATH) $(TEXT) $(WRAP)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS) -lc

test-camera: test-camera.o  $(MATH) $(TEXT) $(WRAP)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS) -lc


clean:
	rm -r -f $(ALL) *.o 2> /dev/null

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $<


%.o: eig3x3/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $<


