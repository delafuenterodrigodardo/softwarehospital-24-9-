#ifndef FUNCIONES_MEDICOS_H_INCLUDED
#define FUNCIONES_MEDICOS_H_INCLUDED

struct medico{
   int matricula;
  char nombre[50];
  char apellido[50];
  int especialidad;
  float sueldo;
};




int buscar_medico(int codigo){
  FILE *p1;
  p1 = fopen("medicos.dat", "rb");
  if (p1 == NULL){
    return -2;
  }
  medico b;
  int i=0;
  while(fread(&b, sizeof(medico), 1, p1)){
    if (codigo == b.matricula){
      fclose(p1);
      return i;
    }
    i++;
  }
  fclose(p1);
  return -1;
}










///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||




bool cargar_nuevo_medico(medico *b){
  cout << "MATRICULA: ";
  cin >> b->matricula;
   while(buscar_medico(b->matricula)>=0){
    cout<<"ESA MATRICULA YA SE ENCUENTRA EN NUESTROS REGISTROS, INTENTAR NUEVAMENTE: ";
    cin>>b->matricula;
  }
  cout << "NOMBRE: ";
  cin.ignore();
  cin.getline(b->nombre, 50);
  while(strlen(b->nombre)<=0){
    cout << "EL NOMBRE NO PUEDE ESTAR VACIO, INTENTAR NUEVAMENTE: ";
    cin.getline(b->nombre, 50);
  }
    cout << "APELLIDO: ";

  cin.getline(b->apellido, 50);
  while(strlen(b->apellido)<=0){
    cout << "EL APELLIDO NO PUEDE ESTAR VACIO, INTENTAR NUEVAMENTE: ";
    cin.getline(b->apellido, 50);
  }
  cout << "ESPECIALIDAD: ";
  cin >> b->especialidad;
  while (b->especialidad<1||b->especialidad>20){
    cout << "INGRESE UN NUMERO DE ESPECIALIDAD (1 a 20)"<<endl;
    cin >>b->especialidad;
  }
    cout << "SUELDO: ";
  cin >> b->sueldo;
  while (b->sueldo<=0){
    cout << "INGRESE UN SUELDO MAYOR A CERO: "<<endl;
    cin >>b->sueldo;
  }
  return true;
}



///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||



void mostrar_medicos(medico b){
cout << "MATRICULA: ";
cout << b.matricula<<endl;
cout << "NOMBRE: ";
cout << b.nombre<<endl;
cout << "APELLIDO: ";
cout << b.apellido<<endl;
cout << "ESPECIALIDAD: ";
cout << b.especialidad<<endl;
cout << "SUELDO: ";
cout << b.sueldo<<endl;
}



///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


bool guardar_medico(medico b){
  FILE *p1;
  p1 = fopen("medicos.dat", "ab");
  if (p1 == NULL){
    return false;
  }
  bool i=fwrite(&b, sizeof(medico), 1, p1);
  fclose(p1);
  return i;
}



///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void listar_medicos(){
  medico b;
  FILE *p1;
  p1 = fopen("medicos.dat", "rb");
  if (p1 == NULL){
    cout << "ERROR AL ABRIR EL ARCHIVO..."<<endl;
    return;
  }
  while(fread(&b, sizeof(medico), 1, p1) == 1){
    mostrar_medicos(b);
    cout << endl;
  }
  fclose(p1);
}

///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||






medico leer_medico(int pos){
  medico reg;
  FILE *p1;
  p1 = fopen("medicos.dat", "rb");
  if (p1==NULL){
    reg.sueldo = -1;
    return reg;
  }
  fseek(p1, sizeof(medico)*pos, SEEK_SET);
  bool leyo=fread(&reg, sizeof(medico), 1, p1);
  if (leyo == false){
    reg.sueldo = -1;
  }
  fclose(p1);
  return reg;
}






///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||



void listar_medico_x_matricula(){
  int codigo;
  int pos;
  cout << "MATRICULA A BUSCAR: ";
  cin >> codigo;
  pos = buscar_medico(codigo);
  if (pos >= 0){
    medico reg;
    reg = leer_medico(pos);
    mostrar_medicos(reg);
  }
  else{
    cout << "NO EXISTE EL REGISTRO..."<<endl;
  }
}



///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||




bool sobreescribir_medico(medico reg, int pos){
  FILE *p1;
  p1 = fopen("medicos.dat", "rb+");
  if (p1 == NULL){
    return false;
  }
  fseek(p1, sizeof(medico)*pos, 0);
  bool i=fwrite(&reg, sizeof(medico), 1, p1);
  fclose(p1);
  return i;
}

///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void modificar_medico(){
   int codigo;
  int pos;
  cout << "MATRICULA DEL MEDICO A MODIFICAR: ";
  cin >> codigo;
  pos = buscar_medico(codigo);
  if (pos >= 0){
    medico reg;
    reg = leer_medico(pos);
    mostrar_medicos(reg);
    cout << endl << "NUEVO SUELDO: ";
    cin >> reg.sueldo;
      while (reg.sueldo<=0){
    cout << "INGRESE UN SUELDO MAYOR A CERO: "<<endl;
    cin >>reg.sueldo;
  }
    if (sobreescribir_medico(reg, pos) == true){
      cout << endl << "SUELDO MODIFICADO."<<endl;
    }
  }
  else{
    cout << "NO EXISTE LA MATRICULA."<<endl;
  }
}
///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void backup_medicos (){
FILE *p, *p1;
medico b;
fecha f;
p=fopen("medicos.dat","rb");
if(p==NULL){
    cout << "ERROR DE ARCHIVO MEDICOS" << endl;
    return;
}
p1=fopen("medicos.bkp", "wb");
if (p1==NULL){
    cout << "ERROR DE ARCHIVO MEDICOS" << endl;
    return;
}
while(fread(&b,sizeof (medico), 1, p)==1){
    fwrite(&b, sizeof (medico), 1, p1);
}
fclose(p1);
fclose(p);
}




///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void backup_medicos_restaurar (){
FILE *p, *p1;
medico b;
fecha f;
p=fopen("medicos.bkp","rb");
if(p==NULL){
    cout << "ERROR DE ARCHIVO MEDICOS" << endl;
    return;
}
p1=fopen("medicos.dat", "wb");
if (p1==NULL){
    cout << "ERROR DE ARCHIVO MEDICOS" << endl;
    return;
}
while(fread(&b,sizeof (medico), 1, p)==1){
    fwrite(&b, sizeof (medico), 1, p1);
}
fclose(p1);
fclose(p);
}

///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


#endif // FUNCIONES_MEDICOS_H_INCLUDED
