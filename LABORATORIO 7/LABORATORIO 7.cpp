#include <iostream>
#include <iomanip>

using namespace std;

// Definición de colores ANSI
#define RESET   "\033[0m"     // Restablece color
#define RED     "\033[31m"    // Rojo
#define GREEN   "\033[32m"    // Verde
#define BLUE    "\033[36m"    // Celeste

class CuentaBancaria {
private:
    double saldo;
    int numeroCuenta;
    bool activa;
    int intentosFallidos;
    string titular;  // Titular de la cuenta

public:
    CuentaBancaria(int num, double saldoInicial = 0, string nombreTitular = "Sin_Titular") {
        numeroCuenta = num;
        saldo = saldoInicial;
        activa = true;
        intentosFallidos = 0;
        titular = nombreTitular;
    }

    void depositar(double monto) {
        if (!activa) {
            cout << RED << "Error: La cuenta #" << numeroCuenta << " esta inactiva. No se puede depositar." << RESET << endl;
            return;
        }
        saldo += monto;
        cout << GREEN << "Deposito exitoso. Nuevo saldo: Q" << saldo << RESET << endl;
    }

    void retirar(double monto) {
        if (!activa) {
            cout << RED << "Error: La cuenta #" << numeroCuenta << " esta inactiva. No se puede retirar dinero." << RESET << endl;
            return;
        }
        if (monto > saldo) {
            intentosFallidos++;
            cout << RED << "Fondos insuficientes. Intento #" << intentosFallidos << " de 3." << RESET << endl;
            if (intentosFallidos >= 3) {
                activa = false;
                cout << RED << "La cuenta ha sido BLOQUEADA por exceder intentos de retiro sin fondos." << RESET << endl;
            }
        }
        else {
            saldo -= monto;
            cout << GREEN << "Retiro exitoso. Nuevo saldo: Q" << saldo << RESET << endl;
            intentosFallidos = 0;  // Reiniciar intentos si el retiro es exitoso
        }
    }

    void mostrarDetallesCuenta() {
        string estadoTexto;
        string estadoColor;

        if (intentosFallidos >= 3) {
            estadoTexto = "BLOQUEADA";
            estadoColor = RED;
        }
        else if (activa) {
            estadoTexto = "ACTIVA";
            estadoColor = GREEN;
        }
        else {
            estadoTexto = "INACTIVA";
            estadoColor = RED;
        }

        cout << "\n+--------------------------------+" << endl;
        cout << "|       DETALLES DE LA CUENTA    |" << endl;
        cout << "+--------------------------------+" << endl;
        cout << "| Titular:       " << BLUE << setw(15) << titular << RESET << " |" << endl;
        cout << "| Numero Cuenta:      " << setw(10) << numeroCuenta << " |" << endl;
        cout << "| Saldo:               Q" << setw(8) << saldo << " |" << endl;
        cout << "| Estado:           " << estadoColor << setw(12) << estadoTexto << RESET << " |" << endl;
        cout << "+--------------------------------+" << endl;
    }

    void asignarTitular(string nombre) {
        titular = nombre;
        cout << "Titular asignado correctamente." << endl;
    }

    void inhabilitarCuenta() {
        activa = false;
        cout << RED << "La cuenta #" << numeroCuenta << " ha sido INHABILITADA." << RESET << endl;
    }

    void habilitarCuenta() {
        activa = true;
        intentosFallidos = 0;  // Reiniciar intentos si se habilita
        cout << GREEN << "La cuenta #" << numeroCuenta << " ha sido HABILITADA." << RESET << endl;
    }

    int getNumeroCuenta() {
        return numeroCuenta;
    }

    bool estaActiva() {
        return activa;
    }
};

int main() {
    int numCuenta, opcion;
    double monto;
    string nombreTitular;
    bool salir = false;
    CuentaBancaria cuenta(0, 0); // Cuenta inicial sin número válido

    do {
        cout << "\nIngrese el numero de cuenta (1-30) o 0 para salir: ";
        cin >> numCuenta;

        if (numCuenta == 0) {
            salir = true;
            break;
        }

        if (numCuenta < 1 || numCuenta > 30) {
            cout << RED << "Numero de cuenta invalido." << RESET << endl;
            continue;
        }

        // Solicitar el titular al crear la cuenta (sin espacios)
        cout << "Ingrese el nombre del titular (sin espacios): ";
        cin >> nombreTitular;

        // Crear la cuenta con saldo inicial de Q1,800.00 y el titular ingresado
        cuenta = CuentaBancaria(numCuenta, 1800, nombreTitular);

        do {
            cout << "\nCuenta #" << cuenta.getNumeroCuenta();
            cout << (cuenta.estaActiva() ? GREEN " (ACTIVA)" RESET : RED " (INACTIVA)" RESET) << endl;
            cout << "Ingrese la opcion: " << endl;
            cout << "1. DEPOSITAR" << endl;
            cout << "2. RETIRAR" << endl;
            cout << "3. CONSULTAR SALDO" << endl;
            cout << "4. CAMBIAR DE CUENTA" << endl;
            cout << "5. HABILITAR/INHABILITAR CUENTA" << endl;
            cout << "6. ASIGNAR NUEVO TITULAR" << endl;
            cout << "7. SALIR" << endl;
            cin >> opcion;

            switch (opcion) {
            case 1:
                cout << "Ingrese monto a depositar: ";
                cin >> monto;
                cuenta.depositar(monto);
                break;
            case 2:
                cout << "Ingrese monto a retirar: ";
                cin >> monto;
                cuenta.retirar(monto);
                break;
            case 3:
                cuenta.mostrarDetallesCuenta();
                break;
            case 4:
                cout << "Cambiando de cuenta..." << endl;
                break;
            case 5:
                if (cuenta.estaActiva()) {
                    cuenta.inhabilitarCuenta();
                }
                else {
                    cuenta.habilitarCuenta();
                }
                break;
            case 6:
                cout << "Ingrese el nuevo nombre del titular (sin espacios): ";
                cin >> nombreTitular;
                cuenta.asignarTitular(nombreTitular);
                break;
            case 7:
                cout << "Saliendo del sistema..." << endl;
                salir = true;
                break;
            default:
                cout << RED << "Opcion invalida." << RESET << endl;
            }
        } while (opcion != 4 && opcion != 7);

    } while (!salir);

    return 0;
}
