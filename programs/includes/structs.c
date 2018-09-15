typedef struct __attribute__((packed)) _Window {
	char * caption;
	unsigned char type;
	unsigned int wwidth;
	unsigned int wheight;
	unsigned int x;
	unsigned int y;
	unsigned int lastx;
	unsigned int lasty;
	unsigned int lastUpdate;
	unsigned int id;
	 short cursorX;
	 short cursorY;
	unsigned char cursorState;
	void (* handler)(void * event);
	struct _Window * next;
	unsigned char * video;
} Window;
typedef struct WindowEvent_ {
	unsigned int code;
	void * data;
} WindowEvent;


#define DIRECTORY_FLAG 0x10
typedef struct __attribute__((packed)) _Dentry {
    unsigned char name[11];
    unsigned char attributes;
    unsigned char _some;
    unsigned char deletedChar;
    unsigned short createdTime;
    unsigned short createdDate;
    unsigned short _some2;
    unsigned short clusterHi;
    unsigned short lastEditedTime;
    unsigned short lastEditedDate;
    unsigned short clusterLo;
    unsigned int size;
}
Dentry;

typedef struct __attribute__((packed)) _D {
    Dentry entries[16];
    struct _D * next;
    unsigned char f;
}
dirEntry;