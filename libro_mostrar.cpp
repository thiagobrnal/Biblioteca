#include <stdio.h>
#include <string.h>

struct datLibro{
		int id, anio;
		char nombre[20], editorial[20];
	}libro;
	
int main(){
	
	FILE *arch;
	arch=fopen("libro.dat","rb");
	if(arch==NULL){
		printf("\nError al crear el archivo clase.bin");
		return 0;
	}
	else{
		fread(&libro, sizeof(libro),1,arch);
		
		while(!feof(arch)){

			printf("\nID: %d",libro.id);
			printf("\nNombre: ");
			puts(libro.nombre);
			printf("editorial: ");
			puts(libro.editorial);
			
			printf("a%co: %ld",164,libro.anio);
			printf("\n----------------");	
				
				
			fread(&libro, sizeof(libro),1,arch);
		}
		
	}
			
	fclose(arch);
	return 0;
}
