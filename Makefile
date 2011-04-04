#
# Makefile to build StepsFramework for Linux
#
# Author: Alex V. Boreskoff, <steps3d@narod.ru>, <steps3d@gmail.com>
#

GLUTPATH   = /usr/include/GL
CFLAGS     = -x c++ -g -I/usr/include/GL -Wall -Ilibs -Iinclude
CONLYFLAGS = -g -I/usr/include/GL -Wall -Ilibs -Iinclude
LIBS       = -L/usr/X11R6/lib -L$(GLUTPATH)/lib -lglut -lGL -lXt -lX11 -lm -ljpeg -lz -lpng -lGLEW

MATH = vec2.o vec3.o vec4.o mat2.o mat3.o mat4.o quat.o plane.o bbox.o randUtils.o eig3.o
TEXT = Texture.o TexImage.o TgaEncoder.o TgaDecoder.o DdsDecoder.o BmpDecoder.o JpegDecoder.o PngDecoder.o Resources.o FileSystem.o ZipFileSystem.o TexFormat.o
WRAP = Data.o Program.o VertexBuffer.o Framebuffer.o stringUtils.o glUtilities.o UbAccessor.o Sampler.o half.o ScreenQuad.o Sync.o Query.o

ALL = 1 2 3 4 5 6 geom-1 geom-2 geom-3 geom-4 light light-ub bezier phong tex-cube tex-3d tex-2d knot test-half test-quad test-sphere test-box test-camera

all: steps.a

steps.a: $(MATH) $(TEXT) $(WRAP)
	ar -rcv steps.ar $^ -o $@


clean:
	rm -r -f $(ALL) *.o 2> /dev/null

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $<


%.o: eig3x3/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $<


