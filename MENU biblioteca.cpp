#include <stdio.h>
#include <string.h>

struct datLibro{
		int id, anio;
		char nombre[30], editorial[20];
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
void devolver();
void mostrarPrestamos();
void mostrarLibro(int);
void mostrarPersona(int);

int main() {
	int op, band=1;
	

	
	while(band!=0) {
		
		printf("\n-------------------------------------------------------------------------------\n");
		printf("\t\t\tMENU BIBLIOTECA\n");
		printf("-------------------------------------------------------------------------------\n");
		
		printf("Ingrese 1 para agregar un libro.\n");
		printf("Ingrese 2 para realizar un prestamo.\n");
		printf("Ingrese 3 para devolver un prestamo.\n");
		printf("Ingrese 4 para mostrar lista de prestamo.\n");
		printf("Ingrese 0 para salir.\n");
		scanf("%d", &op);
		printf("\n");
		
	
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
		
		case 3:
			devolver();
		break;
			
		case 4:
			mostrarPrestamos();
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
		puts("Libro cargado exitosamente.");
		
	}else{
		printf("Error de apertura de archivo libro.dat");
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
	printf("Ingrese el nombre de la persona: ");
	gets(nombreAux);
	strlwr(nombreAux);
	fflush(stdin);
	printf("Ingrese el dni: ");
	scanf("%ld", &dniAux);
	fflush(stdin);
	
	
	arch=fopen("personas.dat","a+b");
	if(arch==NULL){
		printf("\nError al crear el archivo personas.dat");
		
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
	
	printf("Ingrese el nombre del libro: ");
	gets(nomLibroAux);
	strlwr(nomLibroAux);
	fflush(stdin);
	
	arch=fopen("libro.dat","a+b");
	if(arch==NULL){
		printf("\nError al crear el archivo libro.dat");	
	}else{
		
		fread(&libro,sizeof(libro),1,arch);
			
		while((!feof(arch))&&(encontroL==0)){

			if(strcmp(libro.nombre,nomLibroAux)==0){
				encontroL=1;
			}
			if (encontroL==0){
				fread(&libro,sizeof(libro),1,arch);
			}	
		}
		
		if (encontroL==1){
		
			fseek(arch,sizeof(libro)*(-1),SEEK_CUR);
				idAuxLibro = libro.id;
			fclose(arch);
			
			arch=fopen("prestamos.dat","a+b");
			
			if(arch==NULL){
				printf("\nError al crear el archivo prestamos.dat");
				
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
					puts("El libro no esta disponible.");
				}
				if(encontroP == 2 || encontroP == 0){
					
					puts("El libro esta disponible.");
					
					prestamo.id = ultIdP + 1;
					prestamo.id_libro = idAuxLibro;
					prestamo.id_persona = idAuxPersona;
					strcpy(prestamo.estado,"prestado");
				
					fwrite(&prestamo,sizeof(prestamo),1,arch);
	
					fclose(arch);
					puts("Cargado exitosamente.");
				}
		
				
			}
		}
		if(encontroL == 0){
			fclose(arch);
			puts("\nNo contamos con ese libro en la biblioteca.");
		}
			

	}	
}

void devolver() {
	FILE *arch;
	long dniAux, idPerAux, idAuxLibro;
	int encontro=0, encontro2=0, band=0, encontro3=0;
	char libroAux[20];
	
	fflush(stdin);
	printf("\nIngrese el DNI: ");
	scanf("%ld", &dniAux);
	fflush(stdin);
	
	arch=fopen("personas.dat","r+b");
	if(arch==NULL){
		printf("\nError al crear el archivo personas.dat");
		
	}else{
		
			fread(&personas,sizeof(personas),1,arch);
			
			while((!feof(arch))&&(encontro==0)) {
				
				if(dniAux==personas.dni) {
					encontro=1;
					idPerAux=personas.id;
					fclose(arch);
				}
				else {
					fread(&personas,sizeof(personas),1,arch);
				}
				
			}
			
			if(encontro==0) {
				fclose(arch);
				printf("No se encontro su DNI.");	
			}
			else if (encontro==1) {
				
				do {
					printf("Ingrese el titulo del libro: ");
					gets(libroAux);
					strlwr(libroAux);
					fflush(stdin);
					
					printf("\n%cEsta seguro de que el titulo que ingreso es correcto?\n",168);
					printf("Ingrese 1 si es correcto, ingrese 0 si desea cambiar: \n");
					scanf("%d", &band);
					
					
				}while(band!=1);
				
				
					arch=fopen("libro.dat","r+b");
					if(arch==NULL){
					printf("\nError al crear el archivo libro.dat");
		
					}else{
						
						fread(&libro,sizeof(libro),1,arch);
						
							while((!feof(arch))&&(encontro2==0)) {
								
								if((strcmp(libroAux,libro.nombre))==0) {
									
									encontro2=1;
									idAuxLibro=libro.id;
									fclose(arch);
																																										
								}
								else {
									fread(&libro,sizeof(libro),1,arch);
								}
								
							}
							if(encontro2==0) {
								fclose(arch);
								printf("Titulo no encontrado.");
							}
							else {
								
								arch=fopen("prestamos.dat","r+b");
								if(arch==NULL){
								printf("\nError al crear el archivo prestamos.dat");
		
								}else{
									fread(&prestamo,sizeof(prestamo),1,arch);
									
									while((!feof(arch))&&(encontro3==0)) {
										
										if((idPerAux==prestamo.id_persona) && (idAuxLibro==prestamo.id_libro)) {										
										encontro3=1;
										
										
										strcpy(prestamo.estado,"devuelto");
										fseek(arch,sizeof(prestamo)*(-1),SEEK_CUR);
										fwrite(&prestamo,sizeof(prestamo),1,arch);
																			
										printf("\nPrestamo finalizado\n");
																				
										fclose(arch);
																			
										}
										else {
											fread(&prestamo,sizeof(prestamo),1,arch);											
										}
										
									}
									
									if(encontro3==0) {
									fclose(arch);
									printf("No salio.");
									}
									
									
																									
								}
								
				
							}
	
		
	
					}

			}

	}
	
}

void mostrarPrestamos(){
	
	int idAuxP, idAuxL;
	
	FILE *arch;
	arch=fopen("prestamos.dat","rb");
	if(arch==NULL){
		printf("\nError al abrir el archivo prestamos.dat");
	}
	else{
		fread(&prestamo, sizeof(prestamo),1,arch);
		
		while(!feof(arch)){
			
			if(strcmp(prestamo.estado, "prestado")==0) {
				
			printf("\n   MOVIMIENTO %d\n",prestamo.id);			
			printf("\n------Persona------");
			idAuxP = prestamo.id_persona;
			mostrarPersona(idAuxP);
			printf("\n------Libro------ ");
			idAuxL = prestamo.id_libro;
			mostrarLibro(idAuxL);
			printf("Estado: ");
			puts(prestamo.estado);
			printf("\n-----------------------\n");
				
			}
			
				
				
			fread(&prestamo, sizeof(prestamo),1,arch);
		}
		
	}
			
	fclose(arch);
}

void mostrarLibro(int idL){
	FILE *arch;
	arch=fopen("libro.dat","rb");
	if(arch==NULL){
		printf("\nError al abrir el archivo libro.dat");
	}
	else{
		fread(&libro, sizeof(libro),1,arch);
		
		while(!feof(arch)){

			if(idL == libro.id){
				printf("\nNombre: ");
				puts(libro.nombre);
				printf("Editorial: ");
				puts(libro.editorial);
				printf("A%co: %ld",164,libro.anio);
				printf("\n");	
				
			}
				fread(&libro, sizeof(libro),1,arch);
			
		}
		
	}
			
	fclose(arch);
}

void mostrarPersona(int idP){
	FILE *arch;
	arch=fopen("personas.dat","rb");
	if(arch==NULL){
		printf("\nError al abrir el archivo personas.dat");
	}
	else{
		fread(&personas,sizeof(personas),1,arch);
		
		while(!feof(arch)){

			if(idP == personas.id){
				printf("\nNombre: ");
				puts(personas.nombre);
				printf("Apellido: ");
				puts(personas.apellido);
				printf("DNI: %ld",personas.dni);
				printf("\nTelefono: %ld",personas.telefono);
				printf("\n");	
			}

			fread(&personas,sizeof(personas),1,arch);
		}
		
	}
			
	fclose(arch);
}
