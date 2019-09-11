/*
Universidad de Oriente 
Nucleo Nueva Esparta
Escuela de Hoteleria y Turismo

Programa de Algoritmo y Estructura de Datos III 

Autores: 
         Gian Franco Marcano
     
Seccion: 35

 */

#include <iostream>

using namespace std;

struct Arbol {
    int x;
    Arbol*izq, *der;

};

struct Nodo {
    int id;
    char nombre[5];
    Nodo *sig;
    Arbol*A;

    void almacenar(Nodo*nodo_nuevo, int identi) {
        nodo_nuevo->id = identi;
        cout << "Ingrese Nombre" << endl;
        cin >> nodo_nuevo->nombre;
        nodo_nuevo->sig = NULL;
        nodo_nuevo->A = NULL;

    }

} *L; //apuntador cabezera de la lista

Nodo*Pa = NULL;
//-------------------Pila--Cola------------------------------

bool buscar_id(Nodo*aux, int identi) {
    if (aux == NULL) {
        return false;
    } else {
        if (aux->id == identi) {
            return true;
        } else {
            return buscar_id(aux->sig, identi);
        }
    }
}

void push(int identi) {
    Nodo *nodo_nuevo = new Nodo;
    bool buscar = false;
    while (buscar == false) {
        cout << "Ingrese Id" << endl;
        cin >> identi;
        if (buscar_id(L, identi)) {
            cout << "id ya existe" << endl;
        } else {
            nodo_nuevo->almacenar(nodo_nuevo, identi);
            buscar = true;
        }
    }
    if (L != NULL) {
        nodo_nuevo->sig = L;

    }
    L = nodo_nuevo;

}

void mostrar(Nodo*aux) {
    if (aux != NULL) {
        cout << "Id: " << aux->id << endl;
        mostrar(aux->sig);
    }
}

void pop_pila(Nodo*aux) {
    if (L != NULL) {
        aux = L;
        L = L->sig;
        cout << "tope: " << aux->id << endl;
        delete aux;
    } else {
        cout << "Underflow" << endl;
    }
}

void pop_cola(Nodo*aux) {
    if (aux != NULL) {
        if (aux->sig == NULL) {
            L = aux->sig;
            cout << "frente: " << aux->id << endl;
            delete aux;
        } else {
            if (aux->sig->sig == NULL) {
                cout << "frente: " << aux->sig->id << endl;
                delete aux->sig;
                aux->sig = NULL;

            } else {
                pop_cola(aux->sig);

            }
        }
    } else {
        cout << "Underflow" << endl;
    }
}

void push_aux(int identi) {//Llenar en la pila auxiliar
    Nodo *nodo_aux = new Nodo;

    nodo_aux->id = identi;
    nodo_aux->sig = NULL;
    if (Pa != NULL) {
        nodo_aux->sig = Pa;
    }
    Pa = nodo_aux;
}

void pop_aux(Nodo*aux) {//Eliminar elementos de la Pila auxiliar

    if (Pa != NULL) {
        aux = Pa;
        Pa = Pa->sig;
        delete aux;
    }
}

void push_cargar_incial(int identi) {//Ingresar Elementos en la lista inicial

    Nodo *nodo_aux = new Nodo;

    nodo_aux->id = identi;
    nodo_aux->sig = NULL;
    if (L != NULL) {
        nodo_aux->sig = L;
    }
    L = nodo_aux;
}

void EliminarCualquiera(Nodo*aux, int Ident) {

    if (L != NULL) {
        if (aux->id == Ident) {          
            pop_pila(aux);
            cout << "Eliminado: " << Ident << endl;

        } else {
            if (aux->sig != NULL) {

                push_aux(aux->id);
                pop_pila(aux);
                EliminarCualquiera(aux->sig, Ident);

            } else {
                //system("cls");
                cout << "No se encontro el elemento" << endl;
            }
        }
    } else
        cout << "lista vacia" << endl;

}

void CargarPilaInicial(Nodo*aux, int Ident) {//cargar elementos en la lista inicial y borrar elementos de la pila auxiliar
    if (aux != NULL) {
        push_cargar_incial(aux->id);
        pop_aux(aux);
        CargarPilaInicial(aux->sig, Ident);
    }
}
//-----------------------------ARBOL--------------------------------

struct Arbol*InsertarArbol(struct Arbol*A, int x) {

    if (A != NULL) {
        if (x > A->x)
            A->der = InsertarArbol(A->der, x);
        else
            A->izq = InsertarArbol(A->izq, x);
    } else {
        A = new Arbol();
        A->x = x;
        A->izq, A->der = NULL;
    }
    return A;
}

int Peso(struct Arbol*A) {

    if (A == NULL)
        return 0;
    else
        return Peso(A->izq) + Peso(A->der) + 1;

}

int MaxAltura(struct Arbol*A, int x) {
    if (A == NULL)
        return 0;
    else
        if (A->x > x)
        return MaxAltura(A->der, x) + 1;
    else
        return MaxAltura(A->izq, x) + 1;

}

int Altura(struct Arbol*A, int x) {

    if (A == NULL)
        return 0;
    else
        if (A->x == x) {
        if (MaxAltura(A->der, x) > MaxAltura(A->izq, x))
            return MaxAltura(A->der, x);
        else
            return MaxAltura(A->izq, x);
    } else
        if (A->x > x)
        return Altura(A->der, x);
    else
        return Altura(A->izq, x);
}

int Profundidad(struct Arbol*A, int x) {

    if (A == NULL) {
        return 0;
    } else
        if (x == A->x)
        return 0;
    else
        if (x > A->x)
        return Profundidad(A->der, x) + 1;
    else
        return Profundidad(A->izq, x) + 1;
}

int Mayor_Der(Arbol * A) {
    if (A == NULL) return 0;

    if (A->der != NULL) {
        return Mayor_Der(A->der);
    }

    return A->x;
}

struct Arbol *Eliminar(Arbol *A, int x) {
    Arbol * Aux;
    int Mayor;
    if (A->x == x) {
        if ((A->izq == NULL) && (A->der == NULL)) {
            delete A;
            return NULL;
        } else {
            if (A->izq == NULL) {
                Aux = A->der;
                delete A;
                return Aux;
            } else {
                Mayor = Mayor_Der(A->izq);
                A->x = Mayor;
                A->izq = Eliminar(A->izq, Mayor);
            }
        }
    } else {
        if (A->x > x) {
            A->izq = Eliminar(A->izq, x);
        } else {
            A->der = Eliminar(A->der, x);
        }
    }
    return A;
}

int Hojas(struct Arbol*A) {

    if (A == NULL)
        return 0;
    else
        if ((A->der == NULL) && (A->izq == NULL))
        return 1;
    else
        return Hojas(A->izq) + Hojas(A->der);
}

bool Buscar(struct Arbol*A, int x) {
    if (A == NULL)
        return false;
    else
        if (A->x == x)
        return true;
    else
        return Buscar(A->izq, x) || Buscar(A->der, x);
}

void Mostrar(struct Arbol*A) {

    if (A != NULL) {
        Mostrar(A->izq);
        cout << A->x << endl;
        Mostrar(A->der);
    }

}

//-----------------------Operaciones En El ARBOL----------------------------------------

void Insertar(struct Nodo*aux, int x) {

    if (aux != NULL) {
        if (aux->id == x) {
            if (aux->A == NULL) {
                cout << "Ingrese Raiz del Arbol" << endl;
            } else {
                cout << "Ingrese Desendiente del Arbol" << endl;
            }
            cin >> x;
            if (Buscar(aux->A, x) == false) {
                aux->A = InsertarArbol(aux->A, x);
            } else
                cout << "Elemento Ya Existe" << endl;
        } else
            return Insertar(aux->sig, x);
    } else
        cout << "No Se Encontro el Id" << endl;
}

int PesoArbol(struct Nodo*aux, int x) {
    if (aux != NULL) {
        if (aux->id == x) {
            return Peso(aux->A);
        } else
            return PesoArbol(aux->sig, x);
    } else
        return 0;
}

int AlturaArbol(struct Nodo*aux, int x) {
    if (aux != NULL) {
        if (aux->id == x) {
            cout << "Elemento del Arbol Para Altura " << endl;
            cin >> x;
            return Altura(aux->A, x);
        } else
            return AlturaArbol(aux->sig, x);
    } else
        return 0;
}

int ProfundidadArbol(struct Nodo*aux, int x) {
    if (aux != NULL) {
        if (aux->id == x) {
            cout << "Elemento del Arbol Para Profundidad" << endl;
            cin >> x;
            return Profundidad(aux->A, x);
        } else
            return ProfundidadArbol(aux->sig, x);
    } else
        return 0;
}

void EliminarArbol(struct Nodo*aux, int x) {
    if (aux != NULL) {
        if (aux->id == x) {
            cout << "Elemento del Arbol Para Eliminar" << endl;
            cin >> x;
            aux->A = Eliminar(aux->A, x);
        } else
            return EliminarArbol(aux->sig, x);
    } else
        cout << "No Se Encontro el Id" << endl;
}

int HojaArbol(struct Nodo*aux, int x) {
    if (aux != NULL) {
        if (aux->id == x) {
            return Hojas(aux->A);
        } else
            return HojaArbol(aux->sig, x);
    }
}

bool BuscarArbol(Nodo*aux, int x) {

    if (aux != NULL) {
        if (aux->id == x) {
            cout << "Ingrese Elemento Del Arbol A Buscar" << endl;
            cin >> x;
            return Buscar(aux->A, x);
        } else
            return BuscarArbol(aux->sig, x);

    } else
        return false;
}

void MostrarArbolNodo(Nodo*aux, int x) {

    if (aux != NULL) {
        if (aux->id == x) {
            Mostrar(aux->A);
        } else
            MostrarArbolNodo(aux->sig, x);
    }
}

int main() {

    int opcion = 0, x = 0;

    while (opcion != 6) {
        cout << "--  Menu  --" << endl << endl;
        cout << "1. Push" << endl;
        cout << "2. Pop" << endl;
        cout << "3. Mostrar" << endl;
        cout << "4. Eliminar Cualquiera" << endl;
        cout << "5. Arbol" << endl;
        cout << "6. Salir" << endl;
        cin >> opcion;

        switch (opcion) {

            case 1:
                while (opcion != 3) {
                    cout << "1. Push_pila" << endl;
                    cout << "2. Push_cola" << endl;
                    cout << "3. Salir" << endl;
                    cin >> opcion;

                    switch (opcion) {
                        case 1:
                            push(0);

                            break;
                        case 2:
                            push(0);

                            break;
                        case 3:
                            cout << "...." << endl;
                            break;

                        default:
                            cout << "Opcion No  Disponible" << endl;
                    }
                }
                break;

            case 2:
                if (L != NULL) {
                    while (opcion != 3) {
                        cout << "1. Pop pila" << endl;
                        cout << "2. Pop Cola" << endl;
                        cout << "3. Salir" << endl;
                        cin >> opcion;

                        switch (opcion) {
                            case 1:
                                mostrar(L);
                                pop_pila(L);
                                break;
                            case 2:
                                mostrar(L);
                                pop_cola(L);
                                break;
                            case 3:
                                cout << "...." << endl;

                                break;

                            default:
                                cout << "Opcion No  Disponible" << endl;
                        }
                    }
                } else {
                    cout << "Lista vacia" << endl;
                }
                break;
            case 3:
                if (L != NULL) {
                    cout << "Lista :" << endl;
                    mostrar(L);

                } else {
                    cout << "Lista Vacia" << endl;
                }

                break;
            case 4:
                cout << "Ingrese id a Eliminar" << endl;
                cin >> x;

                EliminarCualquiera(L, x);
                CargarPilaInicial(Pa, x);

                break;
            case 5:

                cout << "1. Insertar" << endl;
                cout << "2. Peso " << endl;
                cout << "3. Altura" << endl;
                cout << "4. Profundidad " << endl;
                cout << "5. Eliminar" << endl;
                cout << "6. Hojas" << endl;
                cout << "7. Inorden" << endl;

                /*
                    cout << "6: Longitud" << endl         
                    cout << "10: LTI" << endl;
                    cout << "11: LTE" << endl;**/
                cin >> opcion;

                switch (opcion) {

                    case 1:
                        cout << "Id del Nodo" << endl; //Id a buscar
                        cin >> x;
                        Insertar(L, x);
                        break;

                    case 2:
                        cout << "Id del Nodo" << endl; //Id a buscar
                        cin >> x;
                        if (buscar_id(L, x) == true)
                            cout << "Peso: " << PesoArbol(L, x) << endl;
                        else
                            cout << "No Se Encontro el Id" << endl;
                        break;

                    case 3:
                        cout << "Id del Nodo" << endl;
                        cin >> x;
                        if (buscar_id(L, x) == true)
                            cout << "Altura: " << AlturaArbol(L, x) << endl;
                        else
                            cout << "No Se Encontro el Id" << endl;
                        break;

                    case 4:
                        cout << "Id del Nodo" << endl;
                        cin >> x;
                        if (buscar_id(L, x) == true)
                            cout << "Profundidad: " << ProfundidadArbol(L, x) << endl;
                        else
                            cout << "No Se Encontro el Id" << endl;
                        break;

                    case 5:
                        cout << "Id del Nodo" << endl; //Id a buscar
                        cin >> x;
                        EliminarArbol(L, x);
                        break;

                    case 6:
                        cout << "Id del Nodo" << endl; //Id a buscar
                        cin >> x;
                        if (buscar_id(L, x) == true)
                            cout << "Cantidad de Hojas del Arbol: " << HojaArbol(L, x) << endl;
                        else
                            cout << "No Se Encontro el Id" << endl;
                        break;

                    case 7:
                        cout << "Id Para Mostrar El Arbol" << endl;
                        cin >> x;
                        if (buscar_id(L, x) == true)
                            MostrarArbolNodo(L, x);
                        else
                            cout << "No Se Encontro el Id" << endl;
                        break;

                    default:
                        cout << " Opcion No  Disponible" << endl;
                        break;

                }
                break;
            case 6:
                cout << "Hasta Luego" << endl;
                break;
            default:
                cout << "Opcion No  Disponible" << endl;
                break;

        }
    }

    return 0;

}
