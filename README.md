# get_next_line is a project at 42

 The function reads a newline from a file into a buffer

 Bonus function manages multiple files at once

 The algorithm is built without the abuse of functions that search for an endline character, such as strlen, for sake of speed optimization
 
 Use -D BUFFER_SIZE=x to manually set the buffer size of read function
 
 ## Usage example
 
 int main()
 {
   int  fd;
   char *line;
   
   fd = open("test.txt", O_RDONLY);
   while (get_next_line(fd, &line) > 0)
   {
     printf("%s\n", line);              // Read file line by line and print the result
     free(line);
   }
   free(line);
   close(fd);
   return (0);
 }
