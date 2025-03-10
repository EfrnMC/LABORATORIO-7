#include <iostream>
#include <iomanip>

using namespace std;

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
            cout << "Error: La cuenta #" << numeroCuenta << " esta inactiva. No se puede depositar." << endl;
            return;
        }
        saldo += monto;
        cout << "Deposito exitoso. Nuevo saldo: Q" << saldo << endl;
    }

    void retirar(double monto) {
        if (!activa) {
            cout << "Error: La cuenta #" << numeroCuenta << " esta inactiva. No se puede retirar dinero." << endl;
            return;
        }
        if (monto > saldo) {
            intentosFallidos++;
            cout << "Fondos insuficientes. Intento #" << intentosFallidos << " de 3." << endl;
            if (intentosFallidos >= 3) {
                activa = false;
                cout << "La cuenta ha sido BLOQUEADA por exceder intentos de retiro sin fondos." << endl;
            }
        }
        else {
            saldo -= monto;
            cout << "Retiro exitoso. Nuevo saldo: Q" << saldo << endl;
            intentosFallidos = 0;  // Reiniciar intentos si el retiro es exitoso
        }
    }

    void mostrarDetallesCuenta() {
        string estadoTexto;

        if (intentosFallidos >= 3) {
            estadoTexto = "BLOQUEADA";
        }
        else if (activa) {
            estadoTexto = "ACTIVA";
        }
        else {
            estadoTexto = "INACTIVA";
        }

        cout << "\n+--------------------------------+" << endl;
        cout << "|       DETALLES DE LA CUENTA    |" << endl;
        cout << "+--------------------------------+" << endl;
        cout << "| Titular:        " << setw(15) << titular << "|" << endl;
        cout << "| Numero Cuenta:      " << setw(10) << numeroCuenta << " |" << endl;
        cout << "| Saldo:               Q" << setw(8) << saldo << " |" << endl;
        cout << "| Estado:           " << setw(12) << estadoTexto << " |" << endl;
        cout << "+--------------------------------+" << endl;
    }

    void asignarTitular(string nombre) {
        titular = nombre;
        cout << "Titular asignado correctamente." << endl;
    }

    void inhabilitarCuenta() {
        activa = false;
        cout << "La cuenta #" << numeroCuenta << " ha sido INHABILITADA." << endl;
    }

    void habilitarCuenta() {
        activa = true;
        intentosFallidos = 0;  // Reiniciar intentos si se habilita
        cout << "La cuenta #" << numeroCuenta << " ha sido HABILITADA." << endl;
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
            cout << "Numero de cuenta invalido." << endl;
            continue;
        }

        // Solicitar el titular al crear la cuenta (sin espacios)
        cout << "Ingrese el nombre del titular (sin espacios): ";
        cin >> nombreTitular;

        // Crear la cuenta con saldo inicial de Q1,800.00 y el titular ingresado
        cuenta = CuentaBancaria(numCuenta, 1800, nombreTitular);

        do {
            cout << "\nCuenta #" << cuenta.getNumeroCuenta();
            cout << (cuenta.estaActiva() ? " (ACTIVA)" : " (INACTIVA)") << endl;
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
                cout << "Opcion invalida." << endl;
            }
        } while (opcion != 4 && opcion != 7);

    } while (!salir);

    return 0;
}
