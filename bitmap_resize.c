/*
 * Thomas Tetz
 * December 2015
 *
 * Utility to resize bitmap images while keeping sharp edges
 */ 

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    
    if (argc != 3){
        printf("Expected 2 parameters, got %d\n", argc-1);
        exit(EXIT_FAILURE);
    }
    
    FILE* input_file;  // the original file to be resized
    FILE* output_file; // the output file
    
    input_file = fopen(argv[1], "r");
    if (input_file == NULL){
        fprintf(stderr, "Could not open %s for input\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    
    output_file = fopen(argv[2], "w");
    if (output_file == NULL){
        fprintf(stderr, "Could not open %s for output\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    
    printf("\nFiles successfully opened.\n\n");

    int length = 2999999;
    char buf[length];
    int line = 1;
    int map_width = 4;

    char* str = fgets(buf, length, input_file);

    int header_size = 78;

    printf("Beginning file write\n");

    int new_size = 128;
    int old_size = 32;
    int ratio = new_size/old_size; 
    int i, j, k, l, p;
	int count = 0;
	int line_count[new_size];
	
	for (i = 0; i < old_size*old_size; ++i){
		
		for(j = 0; j < ratio; ++j){
			fprintf(output_file,"%.9s",str+ (9*(i)));
		}

		if ((i+1)%old_size == 0){
			for(p = 0; p < ratio-1; ++p){
				for (l = i-(old_size-1); l < i+1; ++l){
					for(k = 0; k < ratio; ++k){
						fprintf(output_file,"%.9s",str+ (9*(l)));
					}
				}
			}	
		}
	}	
    fclose(input_file);
    
    return 0;
}

