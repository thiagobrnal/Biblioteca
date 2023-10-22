#include <stdio.h>
#include <string.h>

struct datLibro{
		int id, anio;
		char nombre[20], editorial[20];
	}libro;
	
struct datPersonas{
		int id, edad;
		char nombre[20], apellido[20], domicilio[50];
		long dni, telefono;	
	}personas;
	
struct datPrestamos{
	int id, id_libro, id_persona;
	char estado[15];
}prestamo;
	
void carga();
void cargaPrestamo();

int main() {
	int op, band=1;
	
	printf("-------------------------------------------------------------------------------\n");
	printf("\t\t\tMENU BIBLIOTECA\n");
	printf("-------------------------------------------------------------------------------\n");
	
	while(band!=0) {
		
		printf("Ingrese 1 para agregar un libro.\n");
		printf("Ingrese 2 para realizar un prestamo.\n");
		printf("\nIngrese 0 para salir.\n");
		scanf("%d", &op);
		
	
	switch(op) {
		
		case 0:
			band=0;
		break;
		
		case 1:
			carga();
		break;
			
		case 2:
			cargaPrestamo();
		break;
		
		default:
			printf("\n-------------------------------------------------------------------------------");
			puts("\n\t\tOpcion no valida, intente nuevo.");
			printf("-------------------------------------------------------------------------------\n\n");
	}
		
	}
	
	return 0;
}

void carga() {
	
	FILE *arch;
	int ultId = 0;
	
	if((arch=fopen("libro.dat","a+b"))!=NULL ){
			
		fread(&libro, sizeof(libro),1,arch);
		while(!feof(arch)){
			ultId = libro.id;
			fread(&libro, sizeof(libro),1,arch);
		}
		
		libro.id = ultId + 1;
		fflush(stdin);
		printf("Ingrese nombre: ");
		gets(libro.nombre);
		strlwr(libro.nombre);
		fflush(stdin);
		printf("Ingrese editorial: ");
		gets(libro.editorial);
		strlwr(libro.editorial);
		fflush(stdin);
		printf("Ingrese a%co de lanzamiento: ",164);
		scanf("%ld", &libro.anio);
		fflush(stdin);

		fwrite(&libro,sizeof(libro),1,arch);
		
		
		fclose(arch);
		
	}else{
		printf("Error de apertura de archivo");
		printf("\n");
	}
	
}

void cargaPrestamo(){
	
	FILE *arch;
	char nombreAux[20], nomLibroAux[20];
	int ultId = 0, ultIdP = 0;
	int encontro = 0;
	int idAuxPersona, idAuxLibro;
	long dniAux;
	int encontroP = 0, encontroL = 0;
	
	fflush(stdin);
	printf("Ingrese el nombre de la persona ");
	gets(nombreAux);
	strlwr(nombreAux);
	fflush(stdin);
	printf("Ingrese el dni: ");
	scanf("%ld", &dniAux);
	fflush(stdin);
	
	
	arch=fopen("personas.dat","r+b");
	if(arch==NULL){
		printf("\nError al crear el archivo.");
		
	}else{
	
	
	fread(&personas,sizeof(personas),1,arch);
	
	while((!feof(arch))&&(encontro==0)){
		
		if((strcmp(personas.nombre,nombreAux)==0) && (personas.dni == dniAux)){
			encontro=1;
			
		}
		
		if (encontro==0){
			fread(&personas,sizeof(personas),1,arch);
		}	
	}
	
	if (encontro==1){
		
		fseek(arch,sizeof(personas)*(-1),SEEK_CUR);
			idAuxPersona = personas.id;
		fclose(arch);
		
	}else{
		
		rewind(arch);
		while(!feof(arch)){
			ultId = personas.id;
			fread(&personas, sizeof(personas),1,arch);
		}
		
		personas.id = ultId + 1;
		idAuxPersona = personas.id;
		strcpy(personas.nombre,nombreAux);
		printf("Ingrese apellido: ");
		gets(personas.apellido);
		fflush(stdin);
		personas.dni = dniAux;
		fflush(stdin);
		printf("Ingrese telefono: ");
		scanf("%ld", &personas.telefono);
		fflush(stdin);
		printf("Ingrese domicilio: ");
		gets(personas.domicilio);
		fflush(stdin);
		printf("Ingrese edad: ");
		scanf("%d", &personas.edad);
		fflush(stdin);
		
		fwrite(&personas,sizeof(personas),1,arch);
		
		fclose(arch);
	}
	}
	
	printf("Ingrese el nombre del libro ");
	gets(nomLibroAux);
	strlwr(nomLibroAux);
	fflush(stdin);
	
	arch=fopen("libro.dat","r+b");
	if(arch==NULL){
		printf("\nError al crear el archivo.");	
	}else{
		
		fread(&libro,sizeof(libro),1,arch);
			
		while((!feof(arch))&&(encontroL==0)){

			if(strcmp(libro.nombre,nomLibroAux)==0){
				encontroL=1;
				puts("ENTRO AL ENCONTROOOO 1 \n");
			}
			puts("\nENTRO\n");
			if (encontroL==0){
				puts("ENTOR AL NOOOOOO ENCONTRO\n");
				fread(&libro,sizeof(libro),1,arch);
			}	
		}
		
		if (encontroL==1){
		
			fseek(arch,sizeof(libro)*(-1),SEEK_CUR);
				idAuxLibro = libro.id;
			fclose(arch);
			
			arch=fopen("prestamos.dat","a+b");
			
			if(arch==NULL){
				printf("\nError al crear el archivo.");
				
			}else{
				
				//estructura prestamos
				fread(&prestamo, sizeof(prestamo),1,arch);
				while((!feof(arch)) && (encontroP == 0)){
					
					if(idAuxLibro == prestamo.id_libro){
						if((strcmp(prestamo.estado,"prestado")==0)){
							encontroP = 1;
						}else{
							encontroP = 2;
						}
					}
					ultIdP = prestamo.id;
					fread(&prestamo, sizeof(prestamo),1,arch);
				}
		
				if(encontroP == 1){
					puts("El libro no esta disponible");
				}
				if(encontroP == 2 || encontroP == 0){
					
					puts("El libro esta disponible");
					
					prestamo.id = ultIdP + 1;
					prestamo.id_libro = idAuxLibro;
					prestamo.id_persona = idAuxPersona;
					strcpy(prestamo.estado,"prestado");
				
					fwrite(&prestamo,sizeof(prestamo),1,arch);
	
					fclose(arch);
				}
		
				
			}
		}
		if(encontroL == 0){
			fclose(arch);
			puts("No contamos con ese libro en la biblioteca.");
		}
			

	}	
}


