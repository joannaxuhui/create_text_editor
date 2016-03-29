 #include "editor.h"
#include "document.h"
#include "format.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
char *get_filename(int argc, char *argv[]) {
	if(argc!=2)
		return NULL;
	else
		return argv[1];
}
size_t min(size_t i, size_t  j){
	if (i>j)
	return j;
	else
	return i;
}
size_t max(size_t i, size_t j) {
	if (i < 6)
	return 0;

else	if ( i-6 >j)
	return (i-6);
	else
	return j;
}
void handle_display_command(Document *document, const char *command) {
	if(Document_size(document)== 0)
	print_document_empty_error(); // empty fileee 

	char* sentence = strdup(command);
	char com[10];
	size_t line = 0;
     size_t size = Document_size(document);

	char* rec = sentence;
     char* rec2 = strsep (&sentence," ");
     if(rec2 != NULL)
     strcpy(com,rec2);
 	if(sentence!=NULL) 	{
		char * num = strsep(&sentence," ");
		line = atoi(num);
		sentence = rec;

		if(strcmp(com, "p")==0 && line!=0){
			size_t min_s = min(line+5, size);
			size_t max_t = max(line,0);
			if(  line > size ) {
				invalid_line();
				free(rec);
				return;
		        
			} else {
				   for(size_t i=max_t; i< min_s; i++)
				  	 print_line(document,i);
		
					free(rec);
				  }	
		} else if(strcmp(com, "p")==0 && line==0){
			free(rec);
			invalid_command(com);
			}
		}  else if( sentence==NULL && strcmp(com,"p")==0) {
			for(size_t i = 0; i < size; i++)
			{
				print_line(document,i); //print them all
			}
			free(rec);
			
			} 
	
}

void handle_write_command(Document *document, const char *command) {
	
	/*char * s= strdup(command);
     char name[100];
	strcpy(name,s);
	char com[10];
	size_t line=0;
     char* start=NULL;
	char* rec = s;
     char* rec2 = strsep (&s," ");
     if(rec2 != NULL)
     strcpy(com,rec2);
	if(s==NULL){
		invalid_command(name);
		free(rec);
		return;
		} else {
    		start=s;
		while(*start!=' ')
		start=start+1;
		start=start+1;
		char * num = strsep(&s," ");
		//printf("num %s\n", num);
		line = atoi(num);
	} 
        if(s==NULL) {
		
		invalid_command(name);
		free(rec);
		return;
		}
	else
	s=rec;
     
	if(strcmp(com,"w")==0 && line !=0) {
		Document_set_line(document, line-1, start);
		free(s);
		s=NULL;
	} else {
		
		invalid_command(name);
		free(rec);
		return;
		
		}*/
	char* s=strdup(command);
	char name[100];
	strcpy(name,s);
	char com[10];
	size_t line = 0;
	char* start=NULL;
	char* rec = s;
     char* rec2 = strsep(&s," ");
     strcpy(com,rec2);
	if(s==NULL){
		free(rec);
		invalid_command(name);
		return;
		}  else {
    		start=s;
		while(*start!=' ')
			start=start+1;
		start=start+1;
		char * num = strsep(&s," ");
     	line = atoi(num);
	} 
	if(s==NULL) {
		free(rec);
		invalid_command(name);
		return;
	}
	else
	s=rec;
	size_t size = Document_size(document);   
	if( strcmp(com, "w") == 0 &&  line != 0){
          if(line > size )
		Vector_resize(document->vector, line);
		char* cstart= strchr(start, '$');
		if(cstart == NULL)
			{
				//const char* original=Document_get_line(document, line-1);
				char* new =NULL;
				//if(original != NULL) {
                  //  	 new =(char*) malloc(strlen(original) + strlen (start) +10);
					// strcpy(new, original);
					 //strcat(new,start);
				//}
				//else{
					new =(char*) malloc(strlen(start) + 10);
					strcpy(new, start);
				//}
				int i= strlen(new);
				new[i]='\0';
				Document_set_line(document, line-1, new);
				free (new);
				new = NULL;
				
			} else {
					//const char* original=Document_get_line(document, line-1);
					char* new =NULL;
					//if(original != NULL) {
		              // 	 new =(char*) malloc(strlen(original) + strlen (start) +10);
						// strcpy(new, original);
						 //int i = strlen(new);
						 //new[i] = '\0';
					//	 strncat(new,start,cstart-start);
					//}
					//else{
						new =(char*) malloc(strlen(start) + 10);
						new[0]='\0';
						strncat(new, start,cstart-start);
					//	}
				int i= strlen(new);
				new[i]='\0';
				Document_set_line(document, line-1, new);
				free (new);

				while(cstart!=NULL)
					{
						char * insert= cstart+1;
						cstart = strchr(insert,'$');
						char* ins = NULL;
						if(cstart!=NULL){
						     ins = (char*)malloc(cstart-insert +10);
							ins[0]='\0';
							strncat(ins, insert, cstart- insert);
							int i=strlen(ins);
							ins[i] = '\0';
							Document_insert_line(document, line, ins);
							free(ins);
							ins=NULL;
							line= line +1;
						} else {
							if(*insert != '\0'){	
								ins= (char*)malloc(strlen (insert )+10);
								strcpy(ins, insert );
								int i = strlen (ins);
								ins[i] = '\0';
								Document_insert_line(document, line, ins);
							}
							else
							Document_insert_line(document, line, "\0");

							free(ins);
							ins=NULL;
						}
					}
		}
		free(rec);
		rec=NULL;
	} else {
			free(rec);
			invalid_command(name);
			return;
		   }

}
void handle_append_command(Document *document, const char *command){
	
	char* s=strdup(command);
	char name[100];
	strcpy(name,s);
	char com[10];
	size_t line = 0;
	char* start=NULL;
	char* rec = s;
     char* rec2 = strsep(&s," ");
     strcpy(com,rec2);
	if(s==NULL){
		free(rec);
		invalid_command(name);
		return;
		}  else {
    		start=s;
		while(*start!=' ')
			start=start+1;
		start=start+1;
		char * num = strsep(&s," ");
     	line = atoi(num);
	} 
	if(s==NULL) {
		free(rec);
		invalid_command(name);
		return;
	}
	else
	s=rec;
	size_t size = Document_size(document);   
	if( strcmp(com, "a") == 0 &&  line != 0){
          if(line > size )
		Vector_resize(document->vector, line);
		char* cstart= strchr(start, '$');
		if(cstart == NULL)
			{
				const char* original=Document_get_line(document, line-1);
				char* new =NULL;
				if(original != NULL) {
                    	 new =(char*) malloc(strlen(original) + strlen (start) +10);
					 strcpy(new, original);
					 strcat(new,start);
				}
				else{
					new =(char*) malloc(strlen(start) + 10);
					strcpy(new, start);
				}
				int i= strlen(new);
				new[i]='\0';
				Document_set_line(document, line-1, new);
				free (new);
				new = NULL;
				
			} else {
					const char* original=Document_get_line(document, line-1);
					char* new =NULL;
					if(original != NULL) {
		               	 new =(char*) malloc(strlen(original) + strlen (start) +10);
						 strcpy(new, original);
						 int i = strlen(new);
						 new[i] = '\0';
						 strncat(new,start,cstart-start);
					}
					else{
						new =(char*) malloc(strlen(start) + 10);
						new[0]='\0';
						strncat(new, start,cstart-start);
						}
				int i= strlen(new);
				new[i]='\0';
				Document_set_line(document, line-1, new);
				free (new);
				while(cstart!=NULL)
					{
						char * insert= cstart+1;
						cstart = strchr(insert,'$');
						char* ins = NULL;
						if(cstart!=NULL){
						     ins = (char*)malloc(cstart-insert +10);
							ins[0]='\0';
							strncat(ins, insert, cstart- insert);
							int i=strlen(ins);
							ins[i] = '\0';
							Document_insert_line(document, line, ins);
							free(ins);
							ins=NULL;
							line= line +1;
						} else {
							if(*insert != '\0'){	
								ins= (char*)malloc(strlen (insert )+10);
								strcpy(ins, insert );
								int i = strlen (ins);
								ins[i] = '\0';
								Document_insert_line(document, line, ins);
							}
							else
							Document_insert_line(document, line, "\0");

							free(ins);
							ins=NULL;
						}
					}
		}
		free(rec);
		rec=NULL;
	} else {
			free(rec);
			invalid_command(name);
			return;
		   }
			
		
}

void handle_delete_command(Document *document, const char *command) {

	size_t size = Document_size(document);
	char* s = strdup(command);
	char* rec=s;
	char* co = strsep(&s," ");
	char com[10];
	strcpy(com,co);
     size_t line=0;
	char name[100];
	strcpy(name,rec);
	if(s==NULL){
			free(rec);
			invalid_command(name);
			return;
		}
      else{
			char* num= strsep(&s," ");
			line=0;
			line = atoi(num);
			
		}
	
	if(s!=NULL){
		free(rec);
		invalid_command(name);
		return;
	}
	if( strcmp(com,"d")==0 && line!= 0){
		if ( line > size){
			free(rec);
			invalid_line();
			return;		

		} else {
			Document_delete_line(document, line-1);
			free(rec);
			}
	} else {
		     free(rec);
			invalid_command(name);
		  }
}

void handle_search_command(Document *document, const char *command) {

	size_t size = Document_size(document);
	char* s= strdup(command);
     char* rec=s;
	if(s[0] == '/' && strlen(s)>1 ){
		char* start = s+1;
		int b=0;
	     b = strlen(start);
		char * search =(char*)malloc(b+1);
		strcpy( search , start);
		int k = strlen(search);
		search[k] = '\0';
		
		for( size_t i = 0 ; i < size ; i++ ) {
                 
			const char* string = Document_get_line(document, i);
     		
			const char* one_line = string;

               if ( string != NULL ) {
    					
                      int length = strlen(string);
				  int m = 0;
    					
					while(m<length) {
						
		    				char* compare = (char*) malloc(k+1);
						compare[0] = '\0';
						strncat(compare,string, k);
						int p=strlen(compare);
						compare[p]='\0';
						if(strcmp(compare, search) == 0) {
							print_search_line(i+1,one_line, string, search);
							
							m=length;									
						} 	else {
									string=string+1;
									
								}
						m = m+1;
						if(compare != NULL)
						free(compare);
						compare = NULL;
			
					}
	
			}
		  

	  }
		free(search);
	}
   free(rec);
}

void handle_save_command(Document *document, const char *filename) {

	Document_write_to_file(document, filename);
	
}
