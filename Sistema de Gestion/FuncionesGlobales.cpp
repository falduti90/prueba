#include <iostream>
#include <string>
#include <cstdlib>
#include "rlutil.h"
#include "FuncionesGlobales.h"
#include "Usuario.h"
#include "Agencia.h"
#include "Fecha.h"
#include "Buque.h"
#include "Region.h"
#include "Cronograma.h"
#include "Terminal.h"
#include "Listados.h"
#include "CargarDatos.h"
#include "EliminarRegistro.h"
#include "BaseCalculo.h"
#include <sstream> //Libredias para
#include <fstream> // el importador
#include "Validaciones.h"
#define NOMBRE_ARCHIVO "Prueba.csv" // Archivo para importador

using namespace std;

int MenuPrincipal(){

    int opc, pos = 0;

    Usuario obj;

    do{
        system("color 9F");
        cout << "\t\t\t\t\t\t***TITULO***" << endl << endl;
        cout << "\t\t\t\t*******************************************" << endl << endl;
        cout << "\t\t\t\t\t1 - INICIAR SESION. " << endl << endl;
        cout << "\t\t\t\t\t0 - SALIR. " << endl << endl << endl;
        cout << "\t\t\t\t*******************************************" << endl << endl;
        cout << "\t\t\t\t\tSELECCIONE OPCION: ";
        rlutil::locate(60,12);
        cin  >> opc;

        if(opc >= 0 && opc < 3){
            system("cls");
        }

        switch(opc){
            case 1 : InicioSesion();
                break;
            case 0 : exit (-1);
                break;

            default : rlutil::locate(41,12);
                    cout << "OPCION INVALIDA!!!" << endl << endl;
                    system("pause > nul");
                    system("cls");
                break;
        }
    }
    while(opc >= 0 || opc < 3);
}

void InicioSesion(){

    int  intentos = 0, pos = 0;
    char usuario[30] = " ";
    char contrasenia [30] = " ";
    Usuario obj;

    do{
        cout << "\t\t\t\t\t\t***TITULO***" << endl << endl;
        cout << "\t\t\t\t*******************************************" << endl << endl;
        cout << "\t\t\t\t\t - USUARIO : ";
        cargarCadena(usuario,30);
        cout << endl;
        cout << "\t\t\t\t\t - PASSWORD: ";
        rlutil::setColor(rlutil::LIGHTBLUE);
        cargarCadena(contrasenia,30);
        rlutil::setColor(rlutil::WHITE);

        pos = buscarPosicionPorUsuario(usuario);

        obj.leerDeDisco(pos);

        if(strcmp(obj.getContrasenia(), contrasenia) == 0){
            cout << endl << "\t\t\t\t\t   BIENVENIDO!!! " << endl << endl;
            system("pause > nul");
            system("cls");
            switch(obj.getCategoria()){
                case 1 : Consultas();
                    break;
                case 2 : DataEntry();
                    break;
                case 3 : Admin();
                    break;
            }
        }
        else{
            cout << endl << "\t\t\t\t\tUSUARIO NO ENCONTRADO!!!" << endl << endl;
            system("pause > nul");
            system("cls");
        }
        intentos++;
        if(intentos == 3){
            cout << endl << endl << "\t\t\t\t\tDEMASIADOS INTENTOS FALLIDOS!!!" << endl << endl;
            cout << "\t\t\t\t\t" << system("pause > nul");
            system("cls");
            MenuPrincipal();
        }
    }while(intentos < 3);
}

void CrearUsuario(){

    char usuario[30] = {};
    char contrasenia [30] = {};
    int  categoria;
    Usuario obj;

    if(pedirContrasenia() == true){
        cout << "\t\t\t\t\t\t***TITULO***" << endl << endl;
        cout << "\t\t\t\t*******************************************" << endl << endl;
        cout << "\t\t\t\t\t - USUARIO  : ";
        cin.getline(usuario,30);
        obj.setUsuario(usuario);
        cout << endl << endl;
        cout << "\t\t\t\t\t - PASSWORD : ";
        cin.getline(contrasenia,30);
        obj.setContrasenia(contrasenia);
        cout << endl << endl;
        cout << "\t\t\t\t\t - CATEGORIA: " << endl << endl;
        cout << "\t\t\t\t\t 1. Consultas." << endl;
        cout << "\t\t\t\t\t 2. Data Entry." << endl;
        cout << "\t\t\t\t\t 3. Admin." << endl << endl;
        cout << "\t\t\t\t*******************************************" << endl << endl;
        cout << "\t\t\t\t\t Seleccione opcion: ";
        cin  >> categoria;
        obj.setCategoria(categoria);
        obj.grabarEnDisco();
        if(categoria < 0 || categoria > 3){
            cout << "\t\tCATEGORIA INVALIDA!!!" << endl;
            cout << "\t\t Seleccione opcion: ";
            cin  >> categoria;
        }
        cout << "\t\t\t\t\t" << system("pause");
        system("cls");
        MenuPrincipal();
    }
    else{
        MenuPrincipal();
    }
}

bool pedirContrasenia(){
    char usuario [30]     =  {};
    char contrasenia [30] =  {};
    char usuarioAdmin [30]     =  "admin";
    char contraseniaAdmin [30] =  "admin";
    Usuario obj;
    cout << "\t\t\t\t\tINGRESE USUARIO DE ADMINISTRADOR" << endl << endl;
    cin.ignore();
    cout << "\t\t\t\t\tUSUARIO    : ";
    rlutil::setColor(rlutil::LIGHTBLUE);
    cin.getline(usuario, 30);
    cout << endl;
    rlutil::setColor(rlutil::WHITE);
    cout << "\t\t\t\t\tCONTRASENIA: ";
    rlutil::setColor(rlutil::LIGHTBLUE);
    cin.getline(contrasenia, 30);
    rlutil::setColor(rlutil::WHITE);

    if(strcmp(usuarioAdmin, usuario) == 0 && strcmp(contraseniaAdmin, contrasenia) == 0){
        cout << endl;
        cout << "\t\t\t\t\tBIENVENIDO!!! " << endl << endl;
        system("pause > nul");
        system("cls");
        return true;
    }
    else{
        cout << endl << "\t\t\t\t\tUSUARIO INVALIDO!!!" << endl << endl;
        system("pause > nul");
        system("cls");
        return false;
    }
}

void Consultas(){

    Usuario reg;
    int opc;

    while(true){
        system("color 9F");
        cout << "\t\t\t\t\t\t***TITULO***" << endl << endl;
        cout << "\t\t\t\t*******************************************" << endl << endl;
        cout << "\t\t\t\t\t1. CRONOGRAMA COMPLETO. " << endl << endl;
        cout << "\t\t\t\t\t2. APLICAR FILTROS. " << endl << endl;
        cout << "\t\t\t\t\t0. CERRAR SESION. " << endl << endl;
        cout << "\t\t\t\t*******************************************" << endl << endl;
        cout << "\t\t\t\t\tSELECCIONE OPCION: ";
        rlutil::locate(60,13);
        cin  >> opc;

        if(opc >= 0 && opc < 3){
            system("cls");
        }

        switch(opc){
            case 1 : ListadoCronograma();
                break;
            case 2 : pedirOpcionesDeFiltrado();
                break;
            case 0 : if(reg.getCategoria() != 3){
                        MenuPrincipal();
                     }
                     else{
                        Admin();
                     }
                break;
            default : rlutil::locate(41,13);
                      cout << "OPCION INVALIDA!!!" << endl;
                      system("pause > nul");
                      rlutil::locate(1,1);
                break;
        }
    }
}

void DataEntry(){
    int opc;


    while(true){
        cout << "\t\t\t\t\t\t***TITULO***" << endl << endl;
        cout << "\t\t\t\t*******************************************" << endl << endl;
        cout << "\t\t\t\t\t1 - LISTADOS. " << endl << endl;
        cout << "\t\t\t\t\t2 - CARGAR DATOS. " << endl << endl;
        cout << "\t\t\t\t\t0 - CERRAR SESION." << endl << endl;
        cout << "\t\t\t\t*******************************************" << endl << endl;
        cout << "\t\t\t\t\tSELECCIONE OPCION: ";
        cin  >> opc;

        system("cls");

        switch(opc){
            case 1 : Listados();
               break;
            case 2 : CargarDatos();
               break;
            case 0 : MenuPrincipal();
               break;
        }
    }
    cout << "\t\t\t\t\t" << system("pause");
    system("cls");
}

void Admin(){

    int opc;

    while(true){
        cout << "\t\t\t\t\t\t***TITULO***" << endl << endl;
        cout << "\t\t\t\t*******************************************" << endl << endl;
        cout << "\t\t\t\t\t1 - CONSULTAS. " << endl << endl;
        cout << "\t\t\t\t\t2 - DATA-ENTRY. " << endl << endl;
        cout << "\t\t\t\t\t3 - CREAR USUARIO. " << endl << endl;
        cout << "\t\t\t\t\t4 - ELIMINAR REGISTRO. " << endl << endl;
        cout << "\t\t\t\t\t0 - CERRAR SESION." << endl << endl;
        cout << "\t\t\t\t*******************************************" << endl << endl;
        cout << "\t\t\t\t\tSELECCIONE OPCION: ";
        cin  >> opc;

        system("cls");

        switch(opc){
            case 1 : DataEntry();
                break;
            case 2 : Consultas();
                break;
            case 3 : CrearUsuario();
                break;
            case 4 : EliminarRegistro();
                break;
            case 0 : MenuPrincipal(); ;
              break;
        }
    }
    cout << "\t\t\t\t\t" << system("pause");
    system("cls");
}

bool importarCronograma(){
    int lineaImp = 0;
   ifstream archivo(NOMBRE_ARCHIVO);
        string linea;

        char delimitador = ';';
        getline(archivo, linea);

        while(getline(archivo, linea)){
            stringstream stream (linea);
            string numDeSemana, idDeAgencia,  idDeRegion, idDeBuque,   numeroDeViaje;
            getline(stream, numDeSemana, delimitador);
            getline(stream, idDeAgencia, delimitador);
            getline(stream, idDeRegion, delimitador);
            getline(stream, idDeBuque, delimitador);
            getline(stream, numeroDeViaje, delimitador);
            int numSemana, idAgencia,  idRegion, idBuque;
            char numViaje[11];
            istringstream(numDeSemana) >> numSemana;
            istringstream(idDeAgencia) >> idAgencia;
            istringstream(idDeRegion) >> idRegion;
            istringstream(idDeBuque) >> idBuque;
            strcpy(numViaje, numeroDeViaje.c_str());



            if (validaNroSemana(numSemana)&& validaIdAgencia(idAgencia) && validaIdRegion(idRegion) && validaIdBuque(idBuque)){

                Cronograma reg;
                reg.cargar(idAgencia, idRegion, idBuque, numSemana, numViaje);
                reg.grabarEnDisco();
                lineaImp ++;


                //c.mostrar();
            }
            else{
                lineaImp++;
                cout << endl << "Error en la linea" << lineaImp << ". No se importo la informacion de la misma";
                return false;
            }

            cout << endl;


	}

	return true;

}


int buscarPosicionPorUsuario(char *usuario){

    Usuario u;
    int pos = 0;

    while(u.leerDeDisco(pos)){
        if(strcmp(usuario,u.getUsuario())== 0){
            return pos;
        }
        pos++;
    }
}

void cargarCadena(char *pal, int tam){
  int i;
  fflush(stdin);
  for(i=0;i<tam;i++){
      pal[i]=cin.get();
	  if(pal[i]=='\n') break;
	  }
  pal[i]='\0';
  fflush(stdin);
}

void ListarPorSemana(){
    system("color 9F");
    int pos = 0;
    Cronograma obj;
    int opc;
    cout << "\t\t\t\t\tSELECCIONE SEMANA: " << endl << endl;
    cout << "\t\t\t\t*******************************************" << endl << endl;
    rlutil::locate(61,1);
    cin >> opc;

    while(obj.leerDeDisco(pos++)){
        if (opc == obj.getNumSemana()){
                rlutil::locate(3,5);
                obj.mostrar();
                cout << endl << endl << endl;
                cout << "\t\t\t\t\t" <<system("pause");
                system("cls");
        }
    }
}

void pedirOpcionesDeFiltrado(){
    int buque, semana, agencia, terminal;
    buque = semana = agencia = terminal = -1;
    bool op;
    bool orden = true;
    cout << "\t\t\t\t\tSELECCIONE FILTROS: " << endl << endl;
    cout << "\t\t\t\t*******************************************" << endl << endl;
    cout << "\t\t\t\tBUQUE - 1. FILTRAR / 0. NO FILTRAR: ";
    cin >> op;

    if (op){

        Buque reg;
        Cronograma obj;
        int pos = 0, opc;
        char *posicion;
        cout << endl << endl;
        cout << "\t\t\t\t\tSELECCIONE BUQUE: " << endl << endl;
        cout << "\t\t\t\t*******************************************" << endl << endl;
        while(reg.leerDeDisco(pos++)){
            if(pos < 10){
             cout << "\t\t\t\t\t" << pos << ".  " << reg.getnombreBuque() << endl;
            }
            else{
             cout << "\t\t\t\t\t" << pos << ". " << reg.getnombreBuque() << endl;
            }
        }
        rlutil::locate(60,8);
        cin >> buque;
        system("cls");
    }
    system("cls");
    cout << "\t\t\t\t\tSELECCIONE FILTROS: " << endl << endl;
    cout << "\t\t\t\t*******************************************" << endl << endl;
    cout << "\t\t\t\tNUMERO DE SEMANA - 1. FILTRAR / 0. NO FILTRAR: ";
    cin >> op;
    if (op){
        cout << endl << "\t\t\t\tINGRESE NUMERO DE SEMANA: ";
        rlutil::locate(59,7);
        cin >> semana;
        system("cls");
    }
    system("cls");
    cout << "\t\t\t\t\tSELECCIONE FILTROS: " << endl << endl;
    cout << "\t\t\t\t*******************************************" << endl << endl;
    cout << "\t\t\t\tAGENCIA - 1. FILTRAR / 0. NO FILTRAR: ";
    cin >> op;

    if (op){

        FILE *p;
        Agencia reg;
        p = fopen("Agencias.dat","rb");
        if( p == NULL ){
            cout << "No se pudo abrir el archivo";
        return ;
        }
        cout << endl << endl;
        cout << "\t\t\t\t\tSELECCIONE AGENCIA: " << endl << endl;
        cout << "\t\t\t\t*******************************************" << endl << endl;
        while ( fread( &reg , sizeof(Agencia) , 1 , p ) == 1 ){
            reg.mostrar();
            cout << "\t\t\t\t*******************************************" << endl;
        }
        rlutil::locate(62,8);
        cin >> agencia;
        system("cls");
        fclose(p);


    }
    system("cls");
    cout << "\t\t\t\t\tSELECCIONE FILTROS: " << endl << endl;
    cout << "\t\t\t\t*******************************************" << endl << endl;
    cout << "\t\t\t\tTERMINAL - 1. FILTRAR / 0. NO FILTRAR: ";
    cin >> op;
    if (op){

        FILE *p;
        Terminal reg;
        p = fopen("Terminales.dat","rb");
        if ( p == NULL ){
            cout << "No se pudo abrir el archivo";
        return ;
        }
        cout << endl << endl;
        cout << "\t\t\t\t\tSELECCIONE TERMINAL: " << endl << endl;
        cout << "\t\t\t\t*******************************************" << endl << endl;
        while( fread ( &reg , sizeof(Terminal) , 1 ,  p) == 1){
            reg.mostrar();
            cout << "\t\t\t\t*******************************************" << endl;
        }
        rlutil::locate(62,8);
        cin >> agencia;
        fclose(p);
    }
        cout << endl << endl;
        cout << "\t\t\t\t\tDESEA ORDENAR POR ETA?:  1-SI   0-NO" << endl << endl;
        cin >> op;
        if (op){
            cout << endl << "1- Ascendente  0-Descendente";
            cin >> orden;
        }


    Listado(buque, semana, agencia, terminal, orden, op);
    system("cls");
}

void Listado(int buque, int numsemana , int idagencia , int idterminal, bool orden, bool op){

    Cronograma *vecList;
    //bool *mostrar;

    int tam = tamanoCronogramas();
    vecList = new Cronograma [tam];

    //mostrar = new bool [tam] {};

    generarVecCronograma(vecList, tam);



    if (op){

        ordenarCronograma(vecList, tam, orden);
    }

    /*
    FILE *p;
    Cronograma reg;
    p = fopen("Cronograma.dat","rb");
    if(p == NULL){
        cout<< "\t\t\t\tNO SE PUDO ABRIR EL ARCHIVO.";
    return ;
    }
    */
    //cout << "\t\t\t\t\t" << system("pause");
    system("cls");
    cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    cout << " WEEK   AGENCIA   REGION   BUQUE    GIRO   VIAJE     ETA     ETD     CUT OFF DOC   CUT OFF FISICO   INICIO DE RECEPCION" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;

    /*
    while(fread(&reg,sizeof(Cronograma),1,p)==1){ */
    for (int i=0; i<tam; i++){


        bool v1 = (buque == -1) || (buque == vecList[i].getIdBuque());
        //cout << endl << "Esto devuelve buque: " << v1;
        bool v2 = (numsemana == -1) || (numsemana == vecList[i].getNumSemana());
        //cout << endl << "Esto devuelve semana: " << v2;
        bool v3 = (idagencia == -1 )|| (idagencia == vecList[i].getIdAgencia());
        //cout << endl << "Esto devuelve agencia: " << v3;
        bool v4 = (idterminal == -1) || (idterminal == vecList[i].getIdGiro());
       // cout << endl << "Esto devuelve terminal: " << v4;

       /*
       bool v1 = (buque == -1) || (buque == reg.getIdBuque());
        //cout << endl << "Esto devuelve buque: " << v1;
        bool v2 = (numsemana == -1) || (numsemana == reg.getNumSemana());
        //cout << endl << "Esto devuelve semana: " << v2;
        bool v3 = (idagencia == -1 )|| (idagencia == reg.getIdAgencia());
        //cout << endl << "Esto devuelve agencia: " << v3;
        bool v4 = (idterminal == -1) || (idterminal == reg.getIdGiro());
       // cout << endl << "Esto devuelve terminal: " << v4;


       */

        if (v1 && v2 && v3 && v4 ){

            vecList[i].mostrar();

            cout << endl << endl;
        }

    }


    /*
    }
    fclose(p);
    cout << endl << endl; */

    bool rta;
    cout << endl << endl;
    cout << "\t\t\t\t�DESEA EXPORTAR DATOS? - 1. EXPORTAR / 0. NO EXPORTAR: ";
    cin >> rta;

    if (rta){
        ExportarCronograma(buque, numsemana , idagencia , idterminal, vecList, tam);
    }

    system("pause");


}

string converToString(char *vec, int tam){
    int i;
    string s = "";
    for (i = 0; i<tam; i++){
        s = s + vec[i];
    }

    return s;

}

bool exportarBaseDeCalculo(){
    ofstream myFile;
    myFile.open("listadoBaseDeCalculo.csv");


    FILE *p;
    BaseCalculo reg;
    p=fopen("BasesCalculos.dat","rb");
    if(p==NULL){
        cout<< "No se pudo abrir el archivo";
    return false ;
    }

    myFile << "ID BDC" << ',' << "AGENCIA"<< ',' << "REGION" << ',' << "TERMINAL"  << ','  << "DIA ETA"  << ','  << "CUT OFF FISICO" << ','  << "CUT OFF DOC" << ',' << "DIAS QUE SUMA PARA ETD" << ',' << "IAS QUE RESTA PARA RECEPCION DEL CNT" << ',' << endl;

    while( fread ( &reg , sizeof(BaseCalculo) , 1 , p ) ){

        char  agencia[100]{} , region[100]{}, term[100]{};

        strcpy(agencia , BuscarAgencia(reg.getidAgencia(),1));
        strcpy(region , BuscarRegion(reg.getidRegion(),1));
        strcpy(term , BuscarTerminal(reg.getidGiro(),0));


        string agenciaStr = converToString(agencia, 100);
        string regionStr = converToString(region,100);
        string terminalStr = converToString(term, 100);

        myFile << reg.getIdBaseCalculo()[0] << ' ' << reg.getIdBaseCalculo()[1] << ' ' << reg.getIdBaseCalculo()[2] << ',' << agenciaStr << ',' << regionStr << ',' << terminalStr << ',' << diaSemanaStr(reg.getDiaETA(), 1) << ',' << diaSemanaStr(reg.getDiaCTF(), 1) << ' ' << reg.getHoraCTF() << "hs" << ',' << diaSemanaStr(reg.getDiaCTD(), 1) << ' ' << reg.getHoraCTD() << "hs" <<  ',' << reg.getCalculoETD() <<  ',' << reg.getCalculoRecepcionCnt() <<  ',' << endl;
        //myFile << reg.getIdBaseCalculo()[0] << ' ' << reg.getIdBaseCalculo()[1] << ' ' << reg.getIdBaseCalculo()[2] << ';' << agenciaStr << ';' << regionStr << ';' << terminalStr << ';' << diaSemanaStr(reg.getDiaETA(), 1) << ';' << diaSemanaStr(reg.getDiaCTF(), 1) << ' ' << reg.getHoraCTF() << "hs" << ';' << diaSemanaStr(reg.getDiaCTD(), 1) << ' ' << reg.getHoraCTD() << "hs" <<  ';' << reg.getCalculoETD() <<  ';' << reg.getCalculoRecepcionCnt() <<  ';' << endl;
    }

    return true;


}
bool importarBaseCalculo(){


    ifstream archivo("importadorBaseCalculo.csv");
    string linea;

        char delimitador = ','; //Cambiar a ;
        getline(archivo, linea);

        while(getline(archivo, linea)){
            stringstream stream (linea);
            string idDeAgencia,  idDeRegion, idDeTerminal, diaDeETA, diaDeCTF, horDeCTF, diaDeCTD, horaDeCTD, masDeETD, menosDeCNT ;
            getline(stream, idDeAgencia, delimitador);
            getline(stream, idDeRegion, delimitador);
            getline(stream, idDeTerminal, delimitador);
            getline(stream, diaDeETA, delimitador);
            getline(stream, diaDeCTF, delimitador);
            getline(stream, horDeCTF, delimitador);
            getline(stream, diaDeCTD, delimitador);
            getline(stream, horaDeCTD, delimitador);
            getline(stream, masDeETD, delimitador);
            getline(stream, menosDeCNT, delimitador);


            int idAgencia,  idRegion, idTerminall, diaETA, diaCTF, horCTF, diaCTD, horCTD, masETD, menosCNT ;
            //char numViaje[11];
            istringstream(idDeAgencia) >> idAgencia;
            istringstream(idDeRegion) >> idRegion;
            istringstream(idDeTerminal) >> idTerminall;
            istringstream(diaDeETA) >> diaETA;
            istringstream(diaDeCTF) >> diaCTF;
            istringstream(horDeCTF) >> horCTF;
            istringstream(diaDeCTD) >> diaCTD;
            istringstream(horaDeCTD) >> horCTD;
            istringstream(masDeETD) >> masETD;
            istringstream(menosDeCNT) >> menosCNT;
            //strcpy(numViaje, numeroDeViaje.c_str());


            BaseCalculo reg;

            if (validaIdAgencia (idAgencia) && validaIdRegion (idRegion) && validaIdTerminal (idTerminall) && validaDiaSemana ( diaETA) && validaDiaSemana (diaCTF) && validaHora (horCTF) && validaDiaSemana (diaCTD) && validaHora (horCTD) && validaPositivo (masETD) && validaPositivo (menosCNT)){

                reg.setidAgencia(idAgencia);
                reg.setidRegion(idRegion);
                reg.setidGiro(idTerminall);
                reg.setDiaETA(diaETA);
                reg.setDiaCTF(diaCTF);
                reg.setHoraCTF(horCTF);
                reg.setDiaCTD(diaCTD);
                reg.setHoraCTD(horCTD);
                reg.setCalculoETD(masETD);
                reg.setCalculoRecepcionCnt(menosCNT);
                reg.setIdBaseCalculo( idAgencia , idRegion , idTerminall );
                reg.setActivo (true);
                //reg.mostrar();
                reg.grabarEnDisco();

            }
            else{
                cout << endl << "Importacion finalizada con errores";
                return false;
            }

            cout << endl;


	}

	return true;



}

void ExportarCronograma (int buque, int numsemana , int idagencia , int idterminal, Cronograma *vecList,int tam){


    ofstream myFile;
    myFile.open("listadoCronograma.csv");

    //myFile << "WEEK" << ',' << "AGENCIA"<< ',' << "REGION" << ',' << "BUQUE" << ',' << "GIRO" << ','  << "VIAJE" << ','  << "ETA" << ',' << "ETD" << ','  << "CUT OFF DOC" << ','  << "CUT OFF FISICO" << ',' << "INICIO DE RECEPCION" << ','  << endl;
    myFile << "WEEK" << ';' << "AGENCIA"<< ';' << "REGION" << ';' << "BUQUE" << ';' << "GIRO" << ';'  << "VIAJE" << ';'  << "ETA" << ';' << "ETD" << ';'  << "CUT OFF DOC" << ';'  << "CUT OFF FISICO" << ';' << "INICIO DE RECEPCION" << ';'  << endl;

//    FILE *p;
//    Cronograma reg;
//    p = fopen("Cronograma.dat","rb");
//    if(p == NULL){
//        cout<< "\t\t\t\tNO SE PUDO ABRIR EL ARCHIVO.";
//    return ;
//    }
//
//    while(fread(&reg,sizeof(Cronograma),1,p)==1){
//
//        bool v1 = (buque == -1) || (buque == reg.getIdBuque());
//        //cout << endl << "Esto devuelve buque: " << v1;
//        bool v2 = (numsemana == -1) || (numsemana == reg.getNumSemana());
//        //cout << endl << "Esto devuelve semana: " << v2;
//        bool v3 = (idagencia == -1 )|| (idagencia == reg.getIdAgencia());
//        //cout << endl << "Esto devuelve agencia: " << v3;
//        bool v4 = (idterminal == -1) || (idterminal == BuscarIdTerminal(reg.getIdBuque()));
//       // cout << endl << "Esto devuelve terminal: " << v4;
//
//        if (v1 && v2 && v3 && v4 ){
//
//                char viaje[11]{}, agencia[100]{} , region[100]{} , buque[100]{} , term[100]{};
//                strcpy(viaje,reg.getViaje());
//                strcpy(agencia , BuscarAgencia(reg.getIdAgencia(),1));
//                strcpy(region , BuscarRegion(reg.getIdRegion(),1));
//                strcpy(buque , BuscarBuque(reg.getIdBuque(),1));
//                strcpy(term , BuscarTerminal(reg.getIdBuque(),1));
//
//                string numViaje = converToString(viaje, 11);
//                string agenciaStr = converToString(agencia, 100);
//                string regionStr = converToString(region,100);
//                string buqueStr = converToString(buque, 100);
//                string terminalStr = converToString(term, 100);
//
//
//
//                //myFile << reg.getNumSemana() << ',' << reg.getIdAgencia() << ',' << reg.getIdRegion() << ','  << reg.getIdBuque() << ',' << reg.getIdGiro() << ',' << numViaje << ',' << reg.getFechaETA().getDia() << '/' << reg.getFechaETA().getMes() << '/' << reg.getFechaETA().getAnio() << ','  << reg.getFechaETD().getDia() << '/' << reg.getFechaETD().getMes() << '/' << reg.getFechaETD().getAnio() << ','  << reg.getFechaCutoffFisico().getDia() << '/' << reg.getFechaCutoffFisico().getMes() << '/' << reg.getFechaCutoffFisico().getAnio()  << ',' <<  reg.getFechaCutoffDoc().getDia() << '/' << reg.getFechaCutoffDoc().getMes() << '/' << reg.getFechaCutoffDoc().getAnio() << ',' <<  reg.getFechaRecepcionCnt().getDia() << '/' << reg.getFechaRecepcionCnt().getMes() << '/' << reg.getFechaRecepcionCnt().getAnio() << ','  << endl;
//                myFile << reg.getNumSemana() << ';' << agenciaStr << ';' << regionStr << ';'  << buqueStr << ';' << terminalStr << ';' << numViaje << ';' << reg.getFechaETA().getDia() << '/' << reg.getFechaETA().getMes() << '/' << reg.getFechaETA().getAnio() << ';'  << reg.getFechaETD().getDia() << '/' << reg.getFechaETD().getMes() << '/' << reg.getFechaETD().getAnio() << ';'  << reg.getFechaCutoffFisico().getDia() << '/' << reg.getFechaCutoffFisico().getMes() << '/' << reg.getFechaCutoffFisico().getAnio()  << ';' <<  reg.getFechaCutoffDoc().getDia() << '/' << reg.getFechaCutoffDoc().getMes() << '/' << reg.getFechaCutoffDoc().getAnio() << ';' <<  reg.getFechaRecepcionCnt().getDia() << '/' << reg.getFechaRecepcionCnt().getMes() << '/' << reg.getFechaRecepcionCnt().getAnio() << ';'  << endl;
//
//            }
//
//            cout << endl << endl;
//        }
//

        for (int i=0; i<tam; i++){


            bool v1 = (buque == -1) || (buque == vecList[i].getIdBuque());
            //cout << endl << "Esto devuelve buque: " << v1;
            bool v2 = (numsemana == -1) || (numsemana == vecList[i].getNumSemana());
            //cout << endl << "Esto devuelve semana: " << v2;
            bool v3 = (idagencia == -1 )|| (idagencia == vecList[i].getIdAgencia());
            //cout << endl << "Esto devuelve agencia: " << v3;
            bool v4 = (idterminal == -1) || (idterminal == BuscarIdTerminal(vecList[i].getIdBuque()));
           // cout << endl << "Esto devuelve terminal: " << v4;


            if (v1 && v2 && v3 && v4 ){

                    char viaje[11]{}, agencia[100]{} , region[100]{} , buque[100]{} , term[100]{};
                    strcpy(viaje,vecList[i].getViaje());
                    strcpy(agencia , BuscarAgencia(vecList[i].getIdAgencia(),1));
                    strcpy(region , BuscarRegion(vecList[i].getIdRegion(),1));
                    strcpy(buque , BuscarBuque(vecList[i].getIdBuque(),1));
                    strcpy(term , BuscarTerminal(vecList[i].getIdBuque(),1));

                    string numViaje = converToString(viaje, 11);
                    string agenciaStr = converToString(agencia, 100);
                    string regionStr = converToString(region,100);
                    string buqueStr = converToString(buque, 100);
                    string terminalStr = converToString(term, 100);

                    //myFile << reg.getNumSemana() << ',' << reg.getIdAgencia() << ',' << reg.getIdRegion() << ','  << reg.getIdBuque() << ',' << reg.getIdGiro() << ',' << numViaje << ',' << reg.getFechaETA().getDia() << '/' << reg.getFechaETA().getMes() << '/' << reg.getFechaETA().getAnio() << ','  << reg.getFechaETD().getDia() << '/' << reg.getFechaETD().getMes() << '/' << reg.getFechaETD().getAnio() << ','  << reg.getFechaCutoffFisico().getDia() << '/' << reg.getFechaCutoffFisico().getMes() << '/' << reg.getFechaCutoffFisico().getAnio()  << ',' <<  reg.getFechaCutoffDoc().getDia() << '/' << reg.getFechaCutoffDoc().getMes() << '/' << reg.getFechaCutoffDoc().getAnio() << ',' <<  reg.getFechaRecepcionCnt().getDia() << '/' << reg.getFechaRecepcionCnt().getMes() << '/' << reg.getFechaRecepcionCnt().getAnio() << ','  << endl;
                    myFile << vecList[i].getNumSemana() << ';' << agenciaStr << ';' << regionStr << ';'  << buqueStr << ';' << terminalStr << ';' << numViaje << ';' << vecList[i].getFechaETA().getDia() << '/' << vecList[i].getFechaETA().getMes() << '/' << vecList[i].getFechaETA().getAnio() << ';'  << vecList[i].getFechaETD().getDia() << '/' << vecList[i].getFechaETD().getMes() << '/' << vecList[i].getFechaETD().getAnio() << ';'  << vecList[i].getFechaCutoffFisico().getDia() << '/' << vecList[i].getFechaCutoffFisico().getMes() << '/' << vecList[i].getFechaCutoffFisico().getAnio()  << ';' <<  vecList[i].getFechaCutoffDoc().getDia() << '/' << vecList[i].getFechaCutoffDoc().getMes() << '/' << vecList[i].getFechaCutoffDoc().getAnio() << ';' <<  vecList[i].getFechaRecepcionCnt().getDia() << '/' << vecList[i].getFechaRecepcionCnt().getMes() << '/' << vecList[i].getFechaRecepcionCnt().getAnio() << ';'  << endl;

                cout << endl << endl;
            }

        }


//    fclose(p);
//    cout << endl << endl;
//    system("pause");
}



