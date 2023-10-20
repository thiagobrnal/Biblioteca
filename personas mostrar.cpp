#include <stdio.h>
#include <string.h>

int main(){
	
	struct datPersonas{	
		int id, edad;
		char nombre[20], apellido[20], domicilio[50];
		long dni, telefono;		
	}personas;
	
	FILE *arch;
	arch=fopen("personas.dat","rb");
	if(arch==NULL){
		printf("\nError al crear el archivo clase.bin");
		return 0;
	}
	else{
		fread(&personas,sizeof(personas),1,arch);
		while(!feof(arch)){

			printf("\nID: %d",personas.id);
			printf("\nNombre: ");
			puts(personas.nombre);
			printf("Apellido: ");
			puts(personas.apellido);
			printf("\nDNI: %dl",personas.dni);
			printf("\nTelefono: %dl",personas.telefono);
			printf("Domicilio: ");
			puts(personas.domicilio);
			printf("\nEdad: %d",personas.edad);
			printf("\n----------------");	
				
		
			fread(&personas,sizeof(personas),1,arch);
		}
		
	}
			
	fclose(arch);
	return 0;
}
