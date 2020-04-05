#define _LARGEFILE_SOURCE
#define _FILE_OFFSET_BITS 64

#define DEVFILE "/dev/sdx1"
#define BAKUPDIR "/root/dynamic_ctrl_mod/swaped"
#define BLKSIZE 4096LL

#include <stdio.h>

int main( int argc, char **argv ){  /* ( String groupno, String blockno ) */
	int blockbitmap, i;
	FILE *fp;
	unsigned char str[4096];
	unsigned char buf[4096];
	char tmp[128];
	int grpno;
	unsigned long blkno;

	if ( argc != 3 ) {
		printf( "err : %s <ext2 or ext3 fs groupno> <bitmap_blockno>\n", argv[0] );
		return 0;
	}

	grpno = atoi( argv[1] );
	blkno = (unsigned long)atol( argv[2] );
	fp = fopen( DEVFILE, "rb+" );

	for( i=0; i<4096; i++ ){
		buf[i] = 0xff;
	}
	
	if ( fseeko( fp, blkno*BLKSIZE, SEEK_SET ) < 0 ) {
		printf( "err!!\n\n" );
		return 0;
	}
	fread( str, 4096, 1, fp );
	if ( fseeko( fp, blkno*BLKSIZE, SEEK_SET ) < 0 ) {
		printf( "err!!\n\n" );
		return 0;
	}
	fwrite( buf, 4096, 1, fp );
	fclose( fp );

	sprintf( tmp, BAKUPDIR "/bitmap_%05d_%s.bin", atoi( argv[1] ), argv[2] );
	fp = fopen( tmp, "wb" ); // "wb" is create file -> ok
	fwrite( str, 4096, 1, fp );
	fclose( fp );

	printf( "\rApply to swap bitmap with grpno=%s blkno=%s. ", argv[1], argv[2] );
	fflush( stdout );

	return 0;
}
