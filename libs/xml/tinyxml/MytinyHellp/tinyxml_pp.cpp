//
//  tinyxml_pp.cpp
//  MyHokage
//
//  Created by silwings on 13-8-10.
//
//

#ifdef BS_PLATFORM_ZSY

#include "tinyxml.h"

FILE* TiXmlFOpen( const char* filename, const char* mode )
{
#if defined(_MSC_VER) && (_MSC_VER >= 1400 )
    FILE* fp = 0;
    errno_t err = fopen_s( &fp, filename, mode );
    if ( !err && fp )
        return fp;
    return 0;
#else
    return fopen( filename, mode );
#endif
}

bool TiXmlDocument::LoadFile( TiXmlEncoding encoding )
{
	return LoadFile( Value(), encoding );
}

bool TiXmlDocument::LoadFile( const char* _filename, TiXmlEncoding encoding )
{
	TIXML_STRING filename( _filename );
	value = filename;
    
	// reading in binary mode so that tinyxml can normalize the EOL
	FILE* file = TiXmlFOpen( value.c_str (), "rb" );
    
	if ( file )
	{
		bool result = LoadFile( file, encoding );
		fclose( file );
		return result;
	}
	else
	{
		SetError( TIXML_ERROR_OPENING_FILE, 0, 0, TIXML_ENCODING_UNKNOWN );
		return false;
	}
}

bool TiXmlDocument::LoadFile( FILE* file, TiXmlEncoding encoding )
{
	if ( !file )
	{
		SetError( TIXML_ERROR_OPENING_FILE, 0, 0, TIXML_ENCODING_UNKNOWN );
		return false;
	}
    
	// Delete the existing data:
	Clear();
	location.Clear();
    
	// Get the file size, so we can pre-allocate the string. HUGE speed impact.
	long length = 0;
	fseek( file, 0, SEEK_END );
	length = ftell( file );
	fseek( file, 0, SEEK_SET );
    
	// Strange case, but good to handle up front.
	if ( length <= 0 )
	{
		SetError( TIXML_ERROR_DOCUMENT_EMPTY, 0, 0, TIXML_ENCODING_UNKNOWN );
		return false;
	}
    
	// Subtle bug here. TinyXml did use fgets. But from the XML spec:
	// 2.11 End-of-Line Handling
	// <snip>
	// <quote>
	// ...the XML processor MUST behave as if it normalized all line breaks in external
	// parsed entities (including the document entity) on input, before parsing, by translating
	// both the two-character sequence #xD #xA and any #xD that is not followed by #xA to
	// a single #xA character.
	// </quote>
	//
	// It is not clear fgets does that, and certainly isn't clear it works cross platform.
	// Generally, you expect fgets to translate from the convention of the OS to the c/unix
	// convention, and not work generally.
    
	/*
     while( fgets( buf, sizeof(buf), file ) )
     {
     data += buf;
     }
     */
    
	char* buf = new char[ length+1 ];
	buf[0] = 0;
    
	if ( fread( buf, length, 1, file ) != 1 ) {
		delete [] buf;
		SetError( TIXML_ERROR_OPENING_FILE, 0, 0, TIXML_ENCODING_UNKNOWN );
		return false;
	}
    
	// Process the buffer in place to normalize new lines. (See comment above.)
	// Copies from the 'p' to 'q' pointer, where p can advance faster if
	// a newline-carriage return is hit.
	//
	// Wikipedia:
	// Systems based on ASCII or a compatible character set use either LF  (Line feed, '\n', 0x0A, 10 in decimal) or
	// CR (Carriage return, '\r', 0x0D, 13 in decimal) individually, or CR followed by LF (CR+LF, 0x0D 0x0A)...
	//		* LF:    Multics, Unix and Unix-like systems (GNU/Linux, AIX, Xenix, Mac OS X, FreeBSD, etc.), BeOS, Amiga, RISC OS, and others
    //		* CR+LF: DEC RT-11 and most other early non-Unix, non-IBM OSes, CP/M, MP/M, DOS, OS/2, Microsoft Windows, Symbian OS
    //		* CR:    Commodore 8-bit machines, Apple II family, Mac OS up to version 9 and OS-9
    
	const char* p = buf;	// the read head
	char* q = buf;			// the write head
	const char CR = 0x0d;
	const char LF = 0x0a;
    
	buf[length] = 0;
	while( *p ) {
		assert( p < (buf+length) );
		assert( q <= (buf+length) );
		assert( q <= p );
        
		if ( *p == CR ) {
			*q++ = LF;
			p++;
			if ( *p == LF ) {		// check for CR+LF (and skip LF)
				p++;
			}
		}
		else {
			*q++ = *p++;
		}
	}
	assert( q <= (buf+length) );
	*q = 0;
    
	Parse( buf, 0, encoding );
    
	delete [] buf;
	return !Error();
}

bool TiXmlDocument::LoadMemory( const char * pBuff, int length, TiXmlEncoding encoding ){
    if ( !pBuff || length == 0 )
    {
        SetError( TIXML_ERROR, 0, 0, TIXML_ENCODING_UNKNOWN );
        return false;
    }
    // If we have a file, assume it is all one big XML file, and read it in.
    // The document parser may decide the document ends sooner than the entire file, however.
    TIXML_STRING data;
    data.reserve( length );
    char* buf = new char[ length+1 ];
    buf[0] = 0;
    memcpy( buf, pBuff, length );
    const char* lastPos = buf ;
    const char* p = buf ;
    buf[length] = 0;
    while( *p ) {
        assert( p < (buf+length) );
        if ( *p == 0xa ) {
            // Newline character. No special rules for this. Append all the characters
            // since the last string, and include the newline.
            data.append( lastPos, (p-lastPos+1) );
            // append, include the newline
            ++p;
            // move past the newline
            lastPos = p;
            // and point to the new buffer (may be 0)
            assert( p <= (buf+length) );
        }
        else if ( *p == 0xd ) {
            // Carriage return. Append what we have so far, then
            // handle moving forward in the buffer.
            if ( (p-lastPos) > 0 ) {
                data.append( lastPos, p-lastPos );
                // do not add the CR
            }
            data += (char)0xa;
            // a proper newline
            if ( *(p+1) == 0xa ) {
                // Carriage return - new line sequence
                p += 2;
                lastPos = p;
                assert( p <= (buf+length) );
            }
            else {
                // it was followed by something else...that is presumably characters again.
                ++p;
                lastPos = p;
                assert( p <= (buf+length) );
            }
        }
        else {
            ++p;
        }
    }
    // Handle any left over characters.
    if ( p-lastPos ) {
        data.append( lastPos, p-lastPos );
    }
    delete [] buf;
    buf = 0;
    Parse( data.c_str(), 0, encoding );
    if (  Error() )
    {
        return false;
    }
    return true;
}

#endif