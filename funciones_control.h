#ifndef FUNCIONES_CONTROL_H_INCLUDED
#define FUNCIONES_CONTROL_H_INCLUDED

struct fecha2{
int dia2;
int mes2;
int anio2;
};

struct control{
   int dni_control;
   int id;
   int matricula_control;
   fecha2 f2;
   float costo;
   int duracion;
   bool estado2;
};





///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||




bool cargar_nuevo_control(control *c){
    c->id++;
  cout<<"EL ID ASIGNADO ES: "<<c->id<<endl;
  cout << "DNI: ";
  cin >> c->dni_control;
  while(buscar_paciente(c->dni_control)==-1){
    cout<<"ESE DNI NO SE ENCUENTRA EN NUESTROS REGISTROS, INTENTAR NUEVAMENTE: ";
    cin>>c->dni_control;
  }
  cout << "NUMERO DE MATRICULA: ";
  cin >> c->matricula_control;
    while(buscar_medico(c->matricula_control)==-1){
    cout<<"ESA MATRICULA NO SE ENCUENTRA EN NUESTROS REGISTROS, INTENTAR NUEVAMENTE: ";
    cin>>c->matricula_control;
  }
  cout<<"COSTO: ";
  cin>>c->costo;
        while (c->costo<=0){
    cout << "INGRESE UN COSTO MAYOR A CERO: "<<endl;
    cin >>c->costo;
  }
    cout << "INGRESE EL DIA: ";
  cin >> c->f2.dia2;
  while(c->f2.dia2<=0 || c->f2.dia2>31){
    cout<<"POR FAVOR INGRESAR UN DIA VALIDO: ";
    cin >> c->f2.dia2;
  }
    cout << "INGRESE EL MES: ";
  cin >> c->f2.mes2;
    while(c->f2.mes2<=0 || c->f2.mes2>12){
    cout<<"POR FAVOR INGRESAR UN MES VALIDO: ";
    cin >> c->f2.mes2;
  }
    cout << "INGRESE EL ANIO: ";
  cin >> c->f2.anio2;
    while(c->f2.anio2<=0){
    cout<<"POR FAVOR INGRESAR UN ANIO VALIDO: ";
    cin >> c->f2.anio2;
  }
  cout << "DURACION: ";
  cin >> c->duracion;
          while (c->duracion<=0){
    cout << "LA DURACION DEBE SER MAYOR A CERO: "<<endl;
    cin >>c->duracion;
  }
  c->estado2=true;
  return true;
}



///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||



void mostrar_controles(control c){
    if (c.estado2==true){

  cout << "ID :";
  cout << c.id << endl;
  cout << "DNI :";
  cout << c.dni_control << endl;
  cout << "NUMERO DE MATRICULA: ";
  cout << c.matricula_control << endl;
  cout << "COSTO: ";
  cout << c.costo << endl;
  cout << "FECHA: ";
  cout << c.f2.dia2<<"/"<<c.f2.mes2<<"/"<<c.f2.anio2 << endl;
  cout << "DURACION: ";
  cout << c.duracion << endl;
  cout << endl;
}
}



///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


bool guardar_control(control c){
  FILE *p2;
  p2 = fopen("controles.dat", "ab");
  if (p2 == NULL){
    return false;
  }
  bool i=fwrite(&c, sizeof(control), 1, p2);
  fclose(p2);
  return i;
}



///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void listar_controles(){
  control c;
  FILE *p2;
  p2 = fopen("controles.dat", "rb");
  if (p2 == NULL){
    cout << "ERROR AL ABRIR EL ARCHIVO..."<<endl;
    return;
  }
  while(fread(&c, sizeof(control), 1, p2) == 1){
    mostrar_controles(c);
    cout << endl;
  }
  fclose(p2);
}

///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

int buscar_control(int codigo){
  FILE *p2;
  p2 = fopen("controles.dat", "rb");
  if (p2 == NULL){
    return -2;
  }
  control c;
  int i=0;
  while(fread(&c, sizeof(control), 1, p2)){
    if (codigo == c.id){
      fclose(p2);
      return i;
    }
    i++;
  }
  fclose(p2);
  return -1;
}

///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||




control leer_control(int pos){
  control reg;
  FILE *p2;
  p2 = fopen("controles.dat", "rb");
  if (p2==NULL){
    reg.duracion = -1;
    return reg;
  }
  fseek(p2, sizeof(control)*pos, SEEK_SET);
  bool leyo=fread(&reg, sizeof(control), 1, p2);
  if (leyo == false){
    reg.duracion = -1;
  }
  fclose(p2);
  return reg;
}






///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||



void listar_control_x_id(){
  int codigo;
  int pos;
  cout << "ID DEL CONTROL A BUSCAR: ";
  cin >> codigo;
  pos = buscar_control(codigo);
  if (pos >= 0){
    control reg;
    reg = leer_control(pos);
    mostrar_controles(reg);
  }
  else{
    cout << "NO EXISTE EL REGISTRO..."<<endl;
  }
}



///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||




bool sobreescribir_control(control reg, int pos){
  FILE *p2;
  p2 = fopen("controles.dat", "rb+");
  if (p2 == NULL){
    return false;
  }
  fseek(p2, sizeof(control)*pos, 0);
  bool i=fwrite(&reg, sizeof(control), 1, p2);
  fclose(p2);
  return i;
}

///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void modificar_control(){
   int codigo;
  int pos;
  cout << "ID DEL CONTROL A MODIFICAR: ";
  cin >> codigo;
  pos = buscar_control(codigo);
  if (pos >= 0){
    control reg;
    reg = leer_control(pos);
    mostrar_controles(reg);
    cout << endl << "NUEVA DURACION DE CONTROL: ";
    cin >> reg.duracion;
             while (reg.duracion<=0){
    cout << "LA DURACION DEBE SER MAYOR A CERO: ";
    cin >> reg.duracion;
  }
    if (sobreescribir_control(reg, pos) == true){
      cout << endl << "CONTROL MODIFICADO."<<endl;
    }
  }
  else{
    cout << "NO EXISTE EL CONTROL."<<endl;
  }
}


///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void eliminar_control(){
   int codigo;
  int pos;
  cout << "ID DEL CONTROL A ELIMINAR: ";
  cin >> codigo;
  pos = buscar_control(codigo);
  if (pos >= 0){
    control reg;
    reg = leer_control(pos);
    mostrar_controles(reg);
    cout << endl << "ELIMINANDO CONTROL... "<<endl;
    reg.estado2=false;
    if (sobreescribir_control(reg, pos) == true){
      cout << endl << "CONTROL ELIMINADO."<<endl;
    }
  }
  else{
    cout << "NO EXISTE EL CONTROL."<<endl;
  }
}

///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void backup_controles (){
FILE *p, *p1;
control c;
fecha f;
p=fopen("controles.dat","rb");
if(p==NULL){
    cout << "ERROR DE ARCHIVO CONTROL" << endl;
    return;
}
p1=fopen("controles.bkp", "wb");
if (p1==NULL){
    cout << "ERROR DE ARCHIVO CONTROL" << endl;
    return;
}
while(fread(&c,sizeof (control), 1, p)==1){
    fwrite(&c, sizeof (control), 1, p1);
}
fclose(p1);
fclose(p);
}




///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void backup_controles_restaurar (){
FILE *p, *p1;
control c;
fecha f;
p=fopen("controles.bkp","rb");
if(p==NULL){
    cout << "ERROR DE ARCHIVO CONTROL" << endl;
    return;
}
p1=fopen("controles.dat", "wb");
if (p1==NULL){
    cout << "ERROR DE ARCHIVO CONTROL" << endl;
    return;
}
while(fread(&c,sizeof (control), 1, p)==1){
    fwrite(&c, sizeof (control), 1, p1);
}
fclose(p1);
fclose(p);
}



#endif // FUNCIONES_CONTROL_H_INCLUDED

