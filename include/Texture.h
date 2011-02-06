//
// Texture wrapper class for OpenGL 3.3 and higher
// Requires DevIL
//
// Author: Alexey V. Boreskov
//

#pragma once
#ifndef __TEXTURE_WRAPPER__
#define __TEXTURE_WRAPPER__

#include    <GL/glew.h>
#include    <string>
#include	"TexFormat.h"

using namespace std;

class	TexImage;

class	Texture
{
	GLuint		id;
	GLenum		target;
	TexFormat	fmt;
//	GLenum		format, internalFormat;
	int			width, height, depth;
	bool		cubemap;					// is it a cubemap
	bool		compressed;					// is it compressed
	bool		autoMipmaps;				// load mipmaps or create if cannot load
	
public:
	Texture  ( bool theAutoMipmaps = true );
	~Texture ();
	
	bool	isOk () const
	{
		return id != 0 && target != 0 && width > 0 && height > 0 && depth > 0;
	}
	
	bool	getAutoMipmaps () const
	{
		return autoMipmaps;
	}
	
	bool	getId () const
	{
		return id;
	}
	
	bool	getWidth () const
	{
		return width;
	}
	
	bool	getHeight () const
	{
		return height;
	}
	
	bool	getDepth () const
	{
		return depth;
	}
	
	bool	isCubemap () const
	{
		return cubemap;
	}
	
	bool	isCompressed () const
	{
		return compressed;
	}
	
	GLenum	getTarget () const
	{
		return target;
	}
/*	
	GLenum	getFormat () const
	{
		return format;
	}
	
	GLenum getInternalFormat () const
	{
		return internalFormat;
	}	
*/

	const TexFormat& getFormat () const
	{
		return fmt;
	}
							// create empty texture with given properties
	bool	create1D        ( int theWidth, GLenum fmt, GLenum intFmt );
	bool	create2D        ( int theWidth, int theHeight, GLenum fmt, GLenum intFmt );
	bool	createRectangle ( int theWidth, int theHeight, GLenum fmt, GLenum intFmt );
	bool	create3D        ( int theWidth, int theHeight, int theDepth, GLenum fmt, GLenum intFmt );
	bool	createCubemap   ( int theWidth, GLenum fmt, GLenum intFmt );
	
							// create empty texture arrays
	bool	createArray1D ( int theWidth, int numSlices, GLenum fmt, GLenum intFmt );
	bool	createArray2D ( int theWidth, int theHeight, int numSlices, GLenum fmt, GLenum intFmt );
	
	bool	load1D        ( const char * fileName );
	bool	load2D        ( const char * fileName );
	bool	loadRectangle ( const char * fileName );
	bool	load3D        ( const char * fileName );
	bool	loadCubemap   ( const char * fileName );
	bool	loadCubemap   ( const char * f1, const char * f2, const char * f3, const char * f4, const char * f5, const char * f6 );
	
							// load cubemap from a list of , or ; separated list of names
	bool	loadCubemapFromNames ( const char * fileNames );
	
	bool	load1DRaw   ( int theWidth, GLenum fmt, GLenum intFmt, GLenum dataType, const void * theData );
	bool	load2DRaw   ( int theWidth, int theHeight, GLenum fmt, GLenum intFmt, GLenum dataType, const void * theData );
	bool	loadRectRaw ( int theWidth, int theHeight, GLenum fmt, GLenum intFmt, GLenum dataType, const void * theData );
	bool	load3DRaw   ( int theWidth, int theHeight, int theDepth, GLenum fmt, GLenum intFmt, GLenum dataType, const void * theData );
	
	bool	saveAsTga ( const char * fileName );
	
	void	bind   ( int texUnit = 0 );
	void	unbind ();
	
	void	buildMipmaps ();
	void	setSwizzle ( GLenum red, GLenum green, GLenum blue, GLenum alpha );
	
// void	SamplerDepth :: copyFromDepthBuffer ()
	
	static int	maxSize ();

protected:
	void	setParamsFromTexImage ( TexImage * image, GLenum theTarget );

};

#endif