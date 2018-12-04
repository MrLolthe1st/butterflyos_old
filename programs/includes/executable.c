
void* stdin;
void* stderr;
void* stdout;
void *  getProcessSTDStream(int id);
void ____start(int argc, char ** argv)
{	
	stdin = getProcessSTDStream(0);
	stdout = getProcessSTDStream(1);
	stderr = getProcessSTDStream(2);
	_main(argc, argv);
}

