struct pipe_t{
 int start_point;
 int end_point;
}

int pipe_create(pipe_t* pipe);

int pipe_close(pipe_t* pipe);

int pipe_write(pipe_t* pipe,const void* buf,int nbytes);

int pipe_read(pipe_t* pipe,const void* buf,int nbytes);
