#include <iostream>
#include <string>
using namespace std;
const int librosmax = 100;
class Libro{
    private:
    string autor;
    string titulo;
    public:
    Libro(string _titulo =" ", string  _autor= " "){
        autor = _autor;
        titulo = _titulo;
    }
    friend class Biblioteca;
    friend bool operator==(const Libro& l1, const Libro& l2);

    friend ostream& operator<<(ostream& os , const Libro& libro);
};

class Biblioteca{
    private:
    Libro Disponibles[librosmax];
    Libro Prestados[librosmax];
    int numDisponibles;
    int numPrestados;
    public:
    
    Biblioteca(){
        numDisponibles=0;
        numPrestados=0;
    }
    void agregarLibro(const Libro& libro);
    void prestarLibro(const Libro& libro);
    void devolverLibro(const Libro& libro);
    void mostrarLibrosDisponibles();
    void mostrarLibrosPrestados();
    const Libro& obtenerLibroDisponible(int indice) const {
        if (indice >= 0 && indice < numDisponibles) {
            return Disponibles[indice];
        } else {
            // Puedes lanzar una excepción, imprimir un mensaje de error o realizar cualquier otra acción adecuada
            throw out_of_range("El índice del libro disponible está fuera de rango.");
        }
    }
    const Libro& obtenerLibroPrestado(int indice) const {
        if (indice >= 0 && indice < numPrestados) {
            return Prestados[indice];
        } else {
            // Puedes lanzar una excepción, imprimir un mensaje de error o realizar cualquier otra acción adecuada
            throw out_of_range("El índice del libro Prestado está fuera de rango.");
        }
    }

};


ostream& operator<<(ostream& os, const Libro& libro){
    os<<"Libro: "<<libro.titulo<<", el autor es: "<<libro.autor<<endl;
    return os;
};
bool operator==(const Libro& l1, const Libro& l2){
    return l1.titulo==l2.titulo && l1.autor==l2.autor;
}
void Biblioteca::agregarLibro(const Libro& libro) {
    if (numDisponibles < librosmax) {
        Disponibles[numDisponibles] = libro;
        numDisponibles++;
        cout << "Libro agregado a la biblioteca: " << libro.titulo << " | Autor: " << libro.autor << endl;
    } else {
        cout << "La biblioteca está llena. No se puede agregar más libros." << endl;
    }
};
void Biblioteca::prestarLibro(const Libro& libro){
    for (int i = 0; i < numDisponibles; i++){
        if (Disponibles[i] == libro){
            if (numPrestados < librosmax){
                Prestados[numPrestados] = Disponibles[i];
                numPrestados++;
                cout << "Libro prestado: " << Disponibles[i] << endl;

                // Mover el libro prestado al final del arreglo Disponibles
                for (int j = i; j < numDisponibles - 1; j++){
                    Disponibles[j] = Disponibles[j + 1];
                }
                numDisponibles--;

                return;
            }
            else{
                cout << "No se puede prestar el libro. No hay más espacio en la lista de libros prestados." << endl;
                return;
            }
        }
    }
    cout << "El libro no está disponible en la biblioteca." << endl;
}
void Biblioteca::devolverLibro(const Libro& libro){
    for (int i = 0; i < numPrestados; i++){
        if (Prestados[i] == libro){
            if (numDisponibles < librosmax){
                Disponibles[numDisponibles] = Prestados[i];
                numDisponibles++;

                // Mover el libro devuelto al final del arreglo Prestados
                for (int j = i; j < numPrestados - 1; j++){
                    Prestados[j] = Prestados[j + 1];
                }
                numPrestados--;

                cout << "Libro devuelto: " << libro << endl;
                return;
            }
            else{
                cout << "No se puede devolver el libro. No hay más espacio en la lista de libros disponibles." << endl;
                return;
            }
        }
    }
    cout << "El libro no está prestado en la biblioteca." << endl;
}

void Biblioteca::mostrarLibrosDisponibles() {
    cout << "Libros disponibles:" << endl;
    for (int i = 0; i < numDisponibles; ++i) {
        cout << Disponibles[i];
    }
}

void Biblioteca::mostrarLibrosPrestados() {
    cout << "Libros prestados:" << endl;
    for (int i = 0; i < numPrestados; ++i) {
        cout << Prestados[i];
    }
}

int main(){
    int z=0;
    int opcion =0;
    Biblioteca b1;
    Libro libro1("1984","George Orwell");
    Libro libro2("Orgullo y Prejuicio","Jane Austen");
    Libro libro3("El gran Gatsby", "Scott Fitzgerald");
    Libro libro4("Matar a un ruisenor", "Harper Lee");
    Libro libro5("Don Quijote de la Mancha","Miguel de Cervantes Saavedra");
    b1.agregarLibro(libro1);
    b1.agregarLibro(libro2);
    b1.agregarLibro(libro3);
    b1.agregarLibro(libro4);
    b1.agregarLibro(libro5);
    cout<<"BIBLIOTECA" <<endl;
    cout<<"1. ver libros disponibles"<<endl;
    cout<<"2. ver libros prestados"<<endl;
    cout<<"3. pedir un libro disponible"<<endl;
    cout<<"4. devolver un libros prestado"<<endl;
    cout<<"5. salir"<<endl;

    while(opcion <6 || opcion > 1){
        cout<<"que desea hacer"<<endl;
        cin>>opcion;
        
        switch(opcion){
            case 1:
                b1.mostrarLibrosDisponibles();
            break;  
            case 2:
                b1.mostrarLibrosPrestados();
            break;
            case 3:
                cout << "Indique el numero del libro de la lista que desea pedir: ";
                b1.mostrarLibrosDisponibles();
                cin >> z;
                try {
                    const Libro& libroPedido = b1.obtenerLibroDisponible(z);
                    b1.prestarLibro(libroPedido);
                } catch (const out_of_range& e) {
                    cout << "Error: " << e.what() << endl;
                }
            break;
            case 4:
                cout << "Indique el numero del libro de la lista que desea devolver ";
                b1.mostrarLibrosPrestados();
                cin >> z;
                try {
                    const Libro& libroPedido = b1.obtenerLibroPrestado(z);
                    b1.devolverLibro(libroPedido);
                } catch (const out_of_range& e) {
                    cout << "Error: " << e.what() << endl;
                }
            break;
            case 5:
                cout<<"salida exitosa "<<endl;
                return 0;
            break;
        }
    }
}
