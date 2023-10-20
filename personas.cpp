#include <stdio.h>
#include <string.h>


main(){
	
	struct datPersonas{
		int id, edad;
		char nombre[20], apellido[20], domicilio[50];
		long dni, telefono;	
	}personas;
	
	FILE *arch;
	int ultId = 0;
	
	if((arch=fopen("personas.dat","w+b"))!=NULL ){
			
		fread(&personas, sizeof(personas),1,arch);
		while(!feof(arch)){
			ultId = personas.id;
			fread(&personas, sizeof(personas),1,arch);
		}
		
		personas.id = ultId + 1;
		printf("Ingrese nombre: ");
		gets(personas.nombre);
		fflush(stdin);
		printf("Ingrese apellido: ");
		gets(personas.apellido);
		fflush(stdin);
		printf("Ingrese dni: ");
		scanf("%dl", &personas.dni);
		fflush(stdin);
		printf("Ingrese telefono: ");
		scanf("%dl", &personas.telefono);
		fflush(stdin);
		printf("Ingrese domicilio: ");
		gets(personas.domicilio);
		fflush(stdin);
		printf("Ingrese edad: ");
		scanf("%dl", &personas.edad);
		fflush(stdin);

		fwrite(&personas,sizeof(personas),1,arch);
		
		
		
		fclose(arch);
		
	}else{
		printf("Error de apertura de archivo");
		printf("\n");
	}
}
	
