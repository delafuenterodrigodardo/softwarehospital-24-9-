#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

struct fecha{
int dia;
int mes;
int anio;
};

struct paciente{
   int dni;
  char nombre[30];
  char apellido[30];
  char genero;
  fecha f;
  int obrasocial;
  bool estado;
};





///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||



int buscar_paciente(int codigo){
  FILE *p;
  p = fopen("pacientes.dat", "rb");
  if (p == NULL){
    exit(1);
  }
  paciente a;
  int i=0;
  while(fread(&a, sizeof(paciente), 1, p)){
    if (codigo == a.dni){
            if (a.estado==false){
                return -10;
            }
      fclose(p);
      return i;
    }
    i++;
  }
  fclose(p);
  return -1;
}

///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||




paciente leer_paciente(int pos){
  paciente reg;
  FILE *p;
  p = fopen("pacientes.dat", "rb");
  if (p==NULL){
    reg.obrasocial = -1;
    return reg;
  }
  fseek(p, sizeof(paciente)*pos, SEEK_SET);
  bool leyo=fread(&reg, sizeof(paciente), 1, p);
  if (leyo == false){
    reg.obrasocial = -1;
  }
  fclose(p);
  return reg;
}

///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||






void mostrar_pacientes(paciente a){
    if (a.estado==true){
  cout << "DNI:";
  cout << a.dni << endl;
  cout << "NOMBRE: ";
  cout << a.nombre << endl;
  cout << "APELLIDO: ";
  cout << a.apellido << endl;
  cout << "GENERO: ";
  cout << a.genero << endl;
  cout << "FECHA: ";
  cout << a.f.dia<<"/"<<a.f.mes<<"/"<<a.f.anio << endl;
  cout << "OBRA SOCIAL: ";
  cout << a.obrasocial << endl;
  cout << endl;
}
}



///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


bool guardar_paciente(paciente a){
  FILE *p;
  p = fopen("pacientes.dat", "ab");
  if (p == NULL){
    return false;
  }
  bool i=fwrite(&a, sizeof(paciente), 1, p);
  fclose(p);
  return i;
}



///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void listar_pacientes(){
  paciente a;
  FILE *p;
  p = fopen("pacientes.dat", "rb");
  if (p == NULL){
    cout << "ERROR AL ABRIR EL ARCHIVO..."<<endl;
    return;
  }
  while(fread(&a, sizeof(paciente), 1, p) == 1){
    mostrar_pacientes(a);
    cout << endl;
  }
  fclose(p);
}

///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||










///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||



void listar_paciente_x_dni(){
  int codigo;
  int pos;
  cout << "DNI DEL PACIENTE: ";
  cin >> codigo;
  pos = buscar_paciente(codigo);
  if (pos >= 0){
    paciente reg;
    reg = leer_paciente(pos);
    mostrar_pacientes(reg);
  }
  else{
    cout << "NO EXISTE EL REGISTRO..."<<endl;
  }
}



///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||




bool sobreescribir_paciente(paciente reg, int pos){
  FILE *p;
  p = fopen("pacientes.dat", "rb+");
  if (p == NULL){
    return false;
  }
  fseek(p, sizeof(paciente)*pos, 0);
  bool i=fwrite(&reg, sizeof(paciente), 1, p);
  fclose(p);
  return i;
}

///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void modificar_paciente(){
   int codigo;
  int pos;
  cout << "DNI DEL PACIENTE A MODIFICAR: ";
  cin >> codigo;
  pos = buscar_paciente(codigo);
  if (pos >= 0){
    paciente reg;
    reg = leer_paciente(pos);
    if(reg.estado==true){
    mostrar_pacientes(reg);
    cout << endl << "NUEVO NUMERO DE OBRA SOCIAL: ";
    cin >> reg.obrasocial;
    while (reg.obrasocial<1||reg.obrasocial>50){
    cout << "INGRESE UN NUMERO DE OBRA SOCIAL VALIDO (1 a 50)"<<endl;
    cin >>reg.obrasocial;
  }
    if (sobreescribir_paciente(reg, pos) == true){
      cout << endl << "PACIENTE MODIFICADO."<<endl;
    }
  }
  else{
    cout << "NO EXISTE EL PACIENTE" << endl;
  }
  }
}


///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void eliminar_paciente(){
   int codigo;
  int pos;
  cout << "DNI DEL PACIENTE A ELIMINAR: ";
  cin >> codigo;
  pos = buscar_paciente(codigo);
  if (pos >= 0){
    paciente reg;
    reg = leer_paciente(pos);
    mostrar_pacientes(reg);
    cout << endl << "ELIMINANDO PACIENTE... "<<endl;
    reg.estado=false;
    if (sobreescribir_paciente(reg, pos) == true){
      cout << endl << "PACIENTE ELIMINADO."<<endl;
    }
  }
  else{
    cout << "NO EXISTE EL PACIENTE."<<endl;
  }
}


///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void recuperar_paciente(int codigo){
  int pos;
  bool x=true;
  cout << "DNI DEL PACIENTE A RECUPERAR: "<<codigo<<endl;
  while (x==true){
  pos = buscar_paciente(codigo);
  if (pos == -1){
        cout << "EL DNI INGRESADO NO EXISTE" << endl;
  }
  else {
    x=false;
  }
  }
  pos=buscar_paciente(codigo);
    paciente reg;
    reg = leer_paciente(pos);
    mostrar_pacientes(reg);
    cout << endl << "RECUPERANDO PACIENTE... "<<endl;
    reg.estado=true;
    if (sobreescribir_paciente(reg, pos) == true){
      cout << endl << "PACIENTE RECUPERADO."<<endl;
    }
  else{
    cout << "NO EXISTE EL PACIENTE."<<endl;
  }
}


///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void backup_pacientes (){
FILE *p, *p1;
paciente a;
fecha f;
p=fopen("pacientes.dat","rb");
if(p==NULL){
    cout << "ERROR DE ARCHIVO PACIENTES" << endl;
    return;
}
p1=fopen("pacientes.bkp", "wb");
if (p1==NULL){
    cout << "ERROR DE ARCHIVO PACIENTES" << endl;
    return;
}
while(fread(&a,sizeof (paciente), 1, p)==1){
    fwrite(&a, sizeof (paciente), 1, p1);
}
fclose(p1);
fclose(p);
}




///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void backup_pacientes_restaurar (){
FILE *p, *p1;
paciente a;
fecha f;
p=fopen("pacientes.bkp","rb");
if(p==NULL){
    cout << "ERROR DE ARCHIVO PACIENTES" << endl;
    return;
}
p1=fopen("pacientes.dat", "wb");
if (p1==NULL){
    cout << "ERROR DE ARCHIVO PACIENTES" << endl;
    return;
}
while(fread(&a,sizeof (paciente), 1, p)==1){
    fwrite(&a, sizeof (paciente), 1, p1);
}
fclose(p1);
fclose(p);
}




///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||




int restricciones_dni_pacientes(int x){
FILE *p;
paciente a;
fecha f;
int s=3,ss=3;
p=fopen("pacientes.dat","rb");
if(p==NULL){
    fopen("pacientes.dat","ab");
}
while(fread(&a,sizeof (paciente),1,p)==1){
if(a.dni==x&&a.estado==false){
    return 1;
    s=1;

}
else{
    if(a.dni==x&&a.estado==true){
        return -1;
        ss=2;
}
}
}
fclose(p);
if(s==3&&ss==3){
    return 0;

}
}

///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||





bool cargar_nuevo_paciente(paciente *a){


int punteroDNI;
int y;
char recuperar;

bool z=true;
while(z==true){
cout<<"INGRESE EL DNI: ";
cin>>punteroDNI;
y=restricciones_dni_pacientes(punteroDNI);

cout<<"VALOR DE PUNTERO DNI:  "<<punteroDNI<<endl;
cout<<"VALOR DE Y: "<<y<<endl;
cout<<"Y=0 (NUEVO)| Y=1 (ELIMINADO)| Y=-1 (ACTIVO) "<<endl;
if(y==0){
    a->dni=punteroDNI;
    z=false;
}
else {
        if(y==1){
        cout<<"PACIENTE DADO DE BAJA. RECUPERAR? (S/N)"<<endl;
        cin>>recuperar;
        if(recuperar=='S'){
         recuperar_paciente(punteroDNI);
         y=1;
         z=false;
         return true;
        }
        else z=false;
        }
    else {
    cout<<"EL PACIENTE YA EXISTE."<<endl;
    cout<<endl;
    cout<<"VOLVER A INGRESAR UN DNI"<<endl;}
    }

}
///cout<<"esto es y "<<y<<endl;
if(y==0){
cin.ignore();
z=true;
while(z==true){

cout<<"INGRESE EL APELLIDO: ";
cin.getline(a->apellido,  50);
if(strlen(a->apellido)==0){
    cout<<"EL APELLIDO NO PUEDE ESTAR VACIO"<<endl;
}
else {
    z=false;
}
}


z=true;
while(z==true){
cout<<"INGRESE EL NOMBRE: ";
cin.getline(a->nombre, 50);
if(strlen(a->nombre)==0){
    cout<<"EL NOMBRE NO PUEDE ESTAR VACIO"<<endl;
}
else {
    z=false;
}
}

z=true;
while(z==true){
cout<<"INGRESE EL GENERO: ";
cin>>a->genero;
if(a->genero=='F'||a->genero=='M'||a->genero=='O'){
    z=false;
}
else cout<<"INGRESE UN GENERO CORRECTO..."<<endl;
}


z=true;
while (z==true){
    cout << "INGRESE EL DIA: ";
    cin >> a->f.dia;
    cout << "INGRESE EL MES: ";
    cin >>  a->f.mes;
    cout << "INGRESE EL ANIO: ";
    cin >>  a->f.anio;
    if(a->f.dia>=1 && a->f.dia<=31 && a->f.mes>=1 && a->f.mes<=12 && a->f.anio>=1){
        z=false;
    }
    else cout << "INGRESE UNA FECHA VALIDA" << endl;
}



z=true;
while(z==true){
cout<<"INGRESE EL NUMERO DE OBRA SOCIAL"<<endl;
cin>>a->obrasocial;
if(a->obrasocial>=1&&a->obrasocial<=50){
    z=false;
}
else cout<<"NUMERO DE OBRA SOCIAL DEBE SER ENTRE 1 Y 50"<<endl;
}

a->estado=true;
return true;

}
return false;

}














///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||



///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

#endif // FUNCIONES_H_INCLUDED


