//
// Basic class to handle reading of static data
//
// Author: Alexey V. Boreskov
//

#pragma once
#ifndef	__DATA__
#define	__DATA__

#ifdef	_WIN32
	#pragma	warning (disable:4786 4996)
#endif

#include	<string>

using namespace std;

#include	"TypeDefs.h"

class	Data
{
	byte  * bits;
	int		length;
	int		pos;
	string	file;						// when data loaded from file, contains it's name

public:
	Data ( const string& fileName );
	Data ( void * ptr, int len );

	bool	isOk () const;

	const string&	getFileName () const
	{
		return file;
	}
	
	bool	isEmpty () const
	{
		return pos >= length;
	}

	int	getLength () const
	{
		return length;
	}

	int	getPos () const
	{
		return pos;
	}

	int	getByte ()
	{
		if ( pos < length )
			return bits [pos++];
		else
			return -1;
	}

	int16	getShort ()
	{
		if ( pos + 1 >= length )
			return -1;

		int16 	v = *(int16 *) (bits + pos);

		pos += 2;

		return v;
	}

	uint16	getUnsignedShort ()
	{
		if ( pos + 1 >= length )
			return -1;

		uint16 v = *(uint16 *) (bits + pos);

		pos += 2;

		return v;
	}

	long getLong ()
	{
		if ( pos + 3 >= length )
			return -1;

		long 	v = *(long *) (bits + pos);

		pos += 4;

		return v;
	}

	dword getUnsignedLong ()
	{
		if ( pos + 3 >= length )
			return -1;

		dword v = *(dword *) (bits + pos);

		pos += 4;

		return v;
	}

	float	getFloat ()
	{
		if ( pos + 3 >= length )
			return 0;

		float f = *(float *)(bits + pos);

		pos += 4;

		return f;
	}

	double	getDouble ()
	{
		if ( pos + 7 >= length )
			return 0;

		double d = *(double *)(bits + pos);

		pos += 8;

		return d;
	}

	void * getPtr () const
	{
		return bits + pos;
	}

	void * getPtr ( int offs ) const;

	int	seekCur ( int delta )
	{
		pos += delta;

		if ( pos > length )
			pos = length;

		if ( pos < 0 )
			pos = 0;

		return pos;
	}

	int	seekAbs ( int offs )
	{
		pos = offs;

		if ( pos > length )
			pos = length;

		if ( pos < 0 )
			pos = 0;

		return pos;
	}

	int		getBytes  ( void * ptr, int len );
	bool	getString ( string& str, char term );				// get a string with given terminator
	bool	saveToFile ( const char * name ) const;
};

#endif
